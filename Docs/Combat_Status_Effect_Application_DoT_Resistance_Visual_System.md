# Metaworld — Combat Status Effect Application, DoT, Resistance & Visual System

**Status:** Canonical / Approved Modern RPG Playlist Upgrade

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first / server-authoritative / data-driven / event-driven / shared player-NPC effects

## Canonical Principle

Combat can attempt to apply Conditions such as Poison, Burning or Stun through the existing Status Effect system. Application chance, potency, duration, periodic damage, resistance, interruption and visuals are all derived from authoritative effect definitions and combat results; no separate combat-only condition framework is created.

> A hit can carry an effect application attempt. The Status Effect manager decides whether a Condition becomes active. Periodic damage re-enters the canonical damage pipeline. Niagara/UI present the active effect but never own it.

Related canon:

- `Docs/Status_Effects_Conditions_Buffs_Debuffs_System.md`
- `Docs/Combat_Hit_Detection_Damage_Resistance_Feedback_System.md`
- `Docs/Combat_Action_Gameplay_Tag_State_System.md`
- `Docs/NPC_Combat_AI_Engagement_Death_System.md`
- `Docs/Combat_Feedback_Audio_Blood_VFX_System.md`

---

# 1. Effect Application Entry

An AttackDefinition, weapon ItemInstance, ammunition profile, magic effect or environmental source may contribute one or more effect application entries.

Suggested fields:

- ConditionDefinitionID;
- base application chance;
- potency/magnitude profile;
- duration profile;
- source ItemInstanceID / CharacterID / EnvironmentID;
- required damage/contact tags;
- immunity/resistance tags;
- body-zone restrictions where relevant;
- stacking policy reference;
- visual/audio presentation profile.

Do not store effect truth in a closed enum plus giant Switch graph.

---

# 2. Authoritative Application Flow

`Validated combat result`
-> collect effect application entries from attack/weapon/ammo/source
-> verify target eligibility/immunity
-> calculate effective application chance/potency
-> authoritative roll if probabilistic
-> call `BPC_MW_StatusEffects`
-> manager applies configured stack/refresh/reject policy
-> replicate active condition state
-> emit feedback/UI events.

The client cannot submit `PoisonApplied=true` as trusted truth.

---

# 3. Chance / Resistance

Application chance is not simply `Random 0..100 <= EffectChance` with no context forever.

Possible inputs:

- source base chance;
- target resistance/immunity;
- armor/body-zone protection;
- item quality/condition;
- poison coating potency;
- skill/profession/magic modifiers where legitimate;
- active target Conditions;
- environment/context.

Final chance is bounded and resolved server-side.

A target can have:

- reduced chance to receive Poison;
- reduced Poison damage after application;
- reduced duration;
- full immunity;

as distinct policies where the ConditionDefinition supports them.

---

# 4. Damage-over-Time Uses Damage Pipeline

Periodic effects such as Burning, Poison and Bleeding use scheduled pulses/timestamps from `BPC_MW_StatusEffects`.

Each damaging pulse creates or routes through an authoritative damage event/profile so relevant defenses/resistances and death handling remain consistent.

Example:

`Condition.Debuff.Burning`
-> pulse due
-> build DoT DamagePacket with ActiveConditionID/source provenance
-> resolve Fire resistance/other allowed defenses
-> commit Health loss
-> emit one authorized damage indicator/feedback event.

Do not directly subtract Health in a UI/condition widget.

---

# 5. DoT Defense Semantics

Not every defense applies identically to periodic damage.

Examples:

- Fire resistance can reduce Burning damage;
- Poison resistance may reduce Poison damage/potency/duration according to definition;
- physical armor may not reduce internal poison unless explicitly designed;
- active Block normally does not block a Poison already in the bloodstream;
- invulnerability/dodge policies can define whether already-active DoTs continue.

The DamageProfile/ConditionDefinition declares the interaction.

---

# 6. Stun

`Condition.State.Stunned` is a gameplay Condition/state with action/movement restrictions.

On application:

- Status Effect manager commits ActiveConditionID;
- Character Action coordinator cancels or interrupts only incompatible active actions with a reason such as `Interrupted.Stun`;
- movement resolver consumes stun restrictions;
- NPC AI perception/decision behavior changes appropriately;
- animation system selects Stun reaction/loop/recovery;
- target cannot locally clear the state by playing another montage.

On expiry/removal:

- exact condition source/restrictions are removed;
- AI/action/movement systems re-evaluate current state;
- animation exits stun cleanly.

Do not use one blanket `ResetAllActions` operation that removes unrelated persistent states/tags.

---

# 7. Death Ownership

Health/Vitals/death state owns the transition to death when Health reaches the legal death condition.

Combat, Status Effects, drowning, hazards and other damage sources all feed the same Vitals/death path.

This avoids separate:

- combat death check;
- poison death check;
- burn death check;
- drowning death check.

Death remains idempotent and authoritative.

---

# 8. Enemy / Player Condition HUD

Enemy and player HUDs may display authorized active Conditions from the same manager.

Presentation can include:

- icon;
- stack count;
- remaining time;
- condition name/type;
- local radial duration visualization;
- damage ticks where authorized.

Hidden health/condition widgets still receive state through event-driven snapshots when they become visible; visibility does not own the underlying Condition.

Do not use raw UMG property binding every frame when change events/snapshots suffice.

---

# 9. Niagara / Visual Status Effects

Visual effect profile may define:

- Niagara system;
- attachment strategy;
- body/armor coverage tags;
- socket/bone target;
- material/post-process hooks;
- significance tier;
- cleanup behavior.

A status effect may attach presentation to relevant skeletal mesh presentation components, including armor/clothing where needed.

Use semantic component/presentation tags/profiles rather than hardcoding one array of exact mesh component names forever.

The visual effect exists only while the relevant active condition/presentation state requires it.

---

# 10. GPU Niagara / Scalability

GPU Niagara can be used where appropriate, but GPU simulation is not automatically the best choice for every effect/platform.

Rules:

- profile actual cost;
- significance/distance can reduce/omit effect presentation;
- gameplay condition remains active even if distant visuals are culled;
- cleanup exact spawned components/systems on condition removal;
- avoid one expensive full-body effect per distant NPC when a cheaper representation suffices.

---

# 11. Effect Feedback Deduplication

One physical hit that applies several Conditions should not blindly replay identical contact audio/blood several times.

Separate:

- one contact feedback event;
- zero or more condition-applied feedback events;
- later periodic pulse feedback events.

Example:

`Sword hit + Poison application`
-> one sword/flesh impact
-> optional Poison-applied cue
-> later Poison pulse indicator(s).

---

# 12. AI Integration

NPC AI reacts to active Conditions through state/utility logic.

Examples:

- Stunned -> cannot choose normal attack until recovered;
- Burning -> seek safety/extinguish behavior where designed;
- Poisoned -> consider antidote/retreat;
- severe debuff -> alter threat/escape decisions.

AI does not manually remove Conditions just because its behavior state changes.

---

# 13. Persistence

Long-lived Conditions follow their canonical persistence policy and timestamps.

Save/load/reconnect cannot:

- reroll whether an already-active Poison was applied;
- reset its full duration accidentally;
- duplicate pulse schedules;
- leave orphan Niagara after effect removal.

---

# Acceptance Tests

1. Combat hit can attempt a Condition application only after valid combat result.
2. Application chance/resistance is server-authoritative.
3. Reapplication follows Condition stacking policy.
4. Burning/Poison DoT uses the canonical damage pipeline and resistance rules.
5. DoT can kill through the same Vitals/death path as direct combat.
6. Stun interrupts only incompatible actions and does not erase unrelated tags/state.
7. NPC AI cannot resume incompatible combat actions while authoritative Stun remains.
8. Condition HUD follows active manager state even if widget was previously hidden.
9. Niagara visuals attach to valid body/armor presentation and clean up on removal.
10. Distant visual culling does not remove the gameplay Condition.
11. One multi-effect hit does not spam duplicate impact audio/VFX.
12. Save/load preserves active effect timing without rerolling application.

## Core Rule

> Metaworld combat Conditions are applications of the shared Status Effect architecture. Hits can attempt to apply them, scheduled pulses use the same damage/death pipeline, Stun coordinates action and movement restrictions, and UI/Niagara merely present authoritative active-condition state.