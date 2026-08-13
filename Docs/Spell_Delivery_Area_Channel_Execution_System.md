# Metaworld — Spell Delivery, Area & Channel Execution System

**Status:** Canonical / Approved Modern RPG Playlist Upgrade
**Engine:** Unreal Engine 5.8
**Runtime:** Blueprint-first / server-authoritative / ability-driven / data-driven

## Canonical Principle

Fireball, Poison Cloud, Chain Lightning, Ice Spike and future spells are different delivery profiles inside the same Ability/Magic architecture. They share activation, cost, cooldown, source snapshot, target validation, result, Status Effect and persistence rules.

> A spell definition chooses how an execution is delivered. Visual effects do not become separate gameplay systems.

Related canon:
- `Docs/Ability_Definition_Learning_Execution_Cooldown_System.md`
- `Docs/Ability_Targeting_Channel_Cancel_Commit_System.md`
- `Docs/Magic_Staff_Spell_Projectile_Combat_System.md`
- `Docs/Ranged_Action_Source_Snapshot_Provenance_System.md`
- `Docs/Combat_Status_Effect_Application_DoT_Resistance_Visual_System.md`

## 1. Delivery Profiles

Suggested delivery modes include:
- Projectile;
- Impact Area;
- Persistent Area;
- Channel/Beam;
- Target-Anchored;
- Self/Defensive;
- future cone/chain/utility modes.

The AbilityDefinition references a delivery profile rather than requiring one custom Ability component branch per spell.

## 2. Fireball Pattern

A Fireball execution can:
- validate cast/targeting state;
- commit cost/cooldown according to definition;
- capture a source snapshot;
- launch a transient projectile;
- validate impact;
- perform a bounded authoritative area query at the impact location;
- resolve each legitimate target once according to the execution/profile;
- emit explosion presentation.

Tutorial radius and multiplier values are tuning only.

Self-hit/owner eligibility is handled by relationship/target policy, not merely by a client-side ignore list.

## 3. Result Conversion / Single Channel

If an Ability intentionally converts its result into one channel such as Fire or Cold, that conversion is declared by the Ability/ResultProfile.

Do not accidentally sum every unrelated equipped damage channel into every spell.

A spell can also intentionally have multiple components, but that must be explicit and deterministic.

## 4. Persistent Area Pattern

Poison Cloud-style execution:
- commit one AbilityExecutionID;
- establish a validated area/volume and lifetime;
- schedule bounded authoritative pulse times;
- query legitimate occupants/targets at each pulse according to policy;
- produce canonical result/Condition attempts;
- stop when execution expires/cancels according to definition.

Niagara cloud particles are presentation. Particle overlap/collision events are not the sole gameplay authority.

Do not run one 100 Hz query loop for an entire long-lived area. Pulse cadence is gameplay/profile data.

## 5. Channel Pattern

Chain Lightning-style channel:
- activation enters Channeling phase;
- held input may sustain the execution;
- Mana/resource drains at explicit cadence or per committed pulse;
- each pulse/beam update validates current target/context;
- release, resource exhaustion, Stun, death or invalid state ends the exact execution;
- UI highlight reflects active channel state.

Mana regeneration delay/recovery belongs to canonical resource policy, not an arbitrary retriggerable delay buried in one spell Blueprint.

## 6. Beam / Chain Visuals

Beam Niagara may use start/end parameters, jitter, impact lights and overlays.

The server-authoritative execution determines the legal target/result. The beam renderer follows that state and cannot damage a target merely because its endpoint visually touches them.

If true chain-to-secondary-target behavior is later designed, target selection/order is explicit server logic rather than implicit Niagara branching.

## 7. Target-Anchored / Ground Spell Pattern

Ice Spike-style execution may use:
- explicit target lock;
- validated ground/target transform;
- authored spawn/impact location;
- one result against the intended target or bounded area according to definition;
- presentation that emerges from terrain.

Target Lock is assistance/intent, not guaranteed contact through walls or outside legal range.

## 8. Movement / Rotation

Spell definitions may allow:
- free movement;
- strafe while channeling;
- slowed movement;
- stationary cast;
- limited camera-facing correction;
- rotation lock after commitment.

The Character Action/Movement Resolver owns final movement behavior.

## 9. Status Effects

Spell results can attempt canonical Conditions such as:
- Burning;
- Poison;
- Chilled/Slow;
- Stun;
- future supernatural effects.

Application, resistance, stacking and periodic behavior remain owned by `BPC_MW_StatusEffects`.

## 10. Breakables / World Objects

Magic results route through shared target capabilities/profile rules. Characters and breakable world objects can both receive appropriate result handling without duplicating Apply/Take logic for each spell family.

## 11. Presentation Profiles

Attack/result presentation can differ by delivery family:
- melee flesh/metal impact;
- arrow hit;
- Fireball explosion;
- Poison Cloud pulse;
- Chain Lightning beam/impact;
- Ice Spike burst;
- breakable-object response.

Presentation is selected from committed result context rather than one giant hardcoded switch in every Actor.

## 12. Performance

- no inactive spell Tick;
- projectile Actors exist only during active flight;
- persistent areas use bounded pulse cadence;
- channel work exists only while channeling;
- target queries are spatial/bounded;
- VFX are pooled/capped/significance-aware;
- execution records are compact.

## Acceptance Tests

1. Fireball uses one committed source snapshot and valid impact-area query.
2. Switching equipment after release cannot alter a projectile spell source.
3. Poison Cloud gameplay pulses continue correctly even if VFX is culled.
4. Channel ends cleanly on input release/resource exhaustion/Stun.
5. Channel resource drain cannot invert into resource gain.
6. Spell result channel comes from definition, not current unrelated equipment at impact.
7. Target lock cannot guarantee a result through obstruction.
8. Persistent area cannot multiply results from excessive particle collision callbacks.
9. Breakable/world targets use shared capability/result routing.
10. Different delivery modes reuse one Ability/Magic architecture.

## Core Rule

Metaworld spells differ by delivery profile, not by gameplay authority. Projectiles, persistent areas, beams and target-anchored effects all execute through one Ability, source-snapshot, result and Status Effect architecture.