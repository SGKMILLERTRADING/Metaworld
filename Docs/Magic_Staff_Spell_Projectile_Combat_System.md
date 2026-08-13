# Metaworld — Magic Staff, Spell Projectile & Combat System

**Status:** Canonical / Approved Modern RPG Playlist Upgrade
**Engine:** Unreal Engine 5.8
**Runtime:** Blueprint-first / server-authoritative / ability-driven / ItemInstance-aware

## Canonical Principle

Magic/staff gameplay uses the same Equipment, Ability, Combat, Status, Movement and projectile-result architecture as other Metaworld actions. A staff is a persistent ItemInstance and a spell is a stable Ability/Spell definition; visual projectiles and impact effects present the committed execution.

> The staff is equipment, the spell is the action definition, and the projectile is a transient delivery/presentation object. None replaces the shared gameplay systems.

Related canon:
- `Docs/Ability_Definition_Learning_Execution_Cooldown_System.md`
- `Docs/Ability_Targeting_Channel_Cancel_Commit_System.md`
- `Docs/Combat_Weapon_Handling_Animation_Profile_System.md`
- `Docs/Ranged_Action_Source_Snapshot_Provenance_System.md`
- `Docs/Combat_Status_Effect_Application_DoT_Resistance_Visual_System.md`

## 1. Staff Equipment

Staff uses normal ItemDefinition/ItemInstance identity and an equipment handling profile such as `Combat.Handling.Staff`.

Its ItemInstance may carry condition, quality, upgrades, creator/provenance, value and approved modifiers. Hand/back sockets and offsets are presentation profiles.

Do not create a special inventory/equipment authority for magic items.

## 2. Staff Locomotion / Animation

Staff handling profile can supply:
- idle/walk/run presentation;
- aim/ready pose;
- upper/lower-body layer policy;
- cast/combo montages;
- turn/facing profile;
- camera/crosshair profile;
- attachment presentation.

Sequencer/Control Rig edits are approved for hand alignment and animation cleanup.

Animation does not authorize gameplay results.

## 3. Spell / Ability Definition

Stable IDs such as:
- `Ability.Magic.Projectile.Cold`
- `Ability.Magic.Projectile.Fire`
- `Ability.Magic.Projectile.Lightning`
- future healing/control/utility/supernatural spells.

Definition may specify:
- Mana/resource cost;
- cooldown;
- required staff/equipment capability;
- cast/charge profile;
- result/effect channels;
- targeting style;
- projectile/presentation profile;
- interruption policy.

## 4. Staff Attacks and Resource Costs

Tutorial removal of Stamina cost from staff attacks is not universal canon.

A magical cast may primarily spend Mana; a physical staff strike may spend Stamina; hybrid actions can use explicit profiles. The Ability/Combat definition owns the cost policy.

## 5. Source Snapshot

At cast/release commitment, create the canonical ranged source snapshot using:
- AbilityExecutionID;
- Staff ItemInstanceID;
- approved effective source stats/modifiers;
- spell/result profile;
- active item effects/infusions if relevant.

Switching equipment after release cannot rewrite the in-flight spell result.

## 6. Aiming / Camera

Camera direction can define player intent, but the projectile/cast originates from the approved staff/character origin and must respect nearby world obstruction.

Target lock may assist spells whose definition allows it. Bow/manual-aim and magic/soft-target profiles can differ without changing the global targeting architecture.

Target lock never guarantees a valid result through walls or outside legal range.

## 7. Projectile Representation

A spell projectile may use a lightweight Blueprint Actor with collision and Projectile Movement where suitable.

It carries compact source provenance and result profile. It does not need a full persistent ItemInstance because it is not ordinary inventory ammunition.

Collision shape can use a sphere/capsule/swept policy according to the spell profile. Close-range correction must not turn the projectile into an unavoidable homing result unless that spell explicitly supports homing.

## 8. Result Channels

Magic result tags may include:
- `Damage.Fire`
- `Damage.Cold`
- `Damage.Electric`
- `Damage.Poison` where appropriate;
- direct Condition applications;
- non-damage utility/control outcomes later.

The SpellDefinition/Ability result profile is authoritative. Do not read whatever equipment stat happens to be active at impact after the projectile was released.

## 9. Status Effects

A valid result can attempt canonical Conditions such as Burning, Chilled/Slow, Poison or Stun according to definition and target resistance/immunity.

Visual color does not create the Condition.

## 10. Impact Presentation

Approved presentation:
- Niagara/Cascade-derived effect upgraded as appropriate;
- sound;
- light;
- temporary material/outline overlay;
- camera/haptic feedback when locally relevant.

Temporary overlays use bounded lifetime/state and clean up safely. They are presentation only and do not become a second status system.

## 11. World Objects / Breakables

Valid world objects use shared Damageable/Breakable capability/profile checks. Do not permanently route magic results by raw actor tags alone.

## 12. Character Rotation / QoL

Cast-facing behavior comes from the action/facing profile and Movement Resolver. A staff combo may permit responsive camera-facing correction while another heavy cast may lock rotation after commitment.

Tutorial unrestricted rotation changes are tuning/animation policy, not a bypass of action state.

## 13. Dodge / Movement Integration

Dodge direction follows the shared combat/movement input resolver. Magic aiming/casting may allow or block dodge according to AbilityDefinition/action phase.

After dodge, aim/cast state resumes only when the original input/state remains legal.

## 14. Performance

- projectiles exist only during active casts;
- no permanent trace loop when staff is idle;
- VFX/overlays are pooled/capped/significance-aware;
- source snapshots are compact;
- crosshair/camera targeting updates only while relevant;
- distant presentation can scale without altering authoritative result.

## Acceptance Tests

1. Staff remains same ItemInstance through equip/stow/save/load.
2. Spell requires valid Ability/equipment/resource state.
3. Equipment switch after release cannot change an in-flight spell source snapshot.
4. Camera aim cannot bypass a nearby obstruction.
5. Target lock assistance does not guarantee impact.
6. Fire/Cold/etc. route through canonical result/resistance/Condition systems.
7. Temporary impact overlay cannot modify authoritative stats/state.
8. Breakable objects use shared capability routing.
9. Staff cast costs follow definition rather than universal free-Stamina rule.
10. Controller and KBM use the same ability/aim requests.

## Core Rule

Metaworld magic is an extension of the shared Ability and ranged-result architecture. Persistent staff equipment and stable spell definitions create authoritative cast executions; projectile, crosshair and impact visuals communicate those executions without becoming gameplay authority.