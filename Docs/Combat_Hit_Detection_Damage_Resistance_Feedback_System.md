# Metaworld — Combat Hit Detection, Damage, Resistance & Feedback System

**Status:** Canonical / Approved Modern RPG Playlist Upgrade

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first / server-authoritative / weapon-instance-aware / data-driven / event-driven

## Canonical Principle

A combat hit is an authoritative event produced by a valid active attack against a valid target. Animation/traces determine candidate contact; the Combat system constructs a damage packet from the attacker, exact weapon ItemInstance, attack definition, hit location and target defenses; VFX/UI present the committed result.

> A trace detects contact. It does not decide final damage. A floating number reports damage. It does not create damage.

Related canon:

- `Docs/Combat_Action_Gameplay_Tag_State_System.md`
- `Docs/Combat_Combo_Action_Windows_Attack_Timing_System.md`
- `Docs/Equipment_Armor_Weapon_Attachment_Avatar_Fitting_Architecture.md`
- `Docs/Stats_Attributes_Item_Modifiers_Encumbrance_System.md`
- `Docs/Status_Effects_Conditions_Buffs_Debuffs_System.md`
- `Docs/Generated_Item_Base_Stats_Affixes_Quality_System.md`

---

# 1. Hit Windows

Melee hit detection runs only during active attack windows.

Animation Notify States may mark the expected active window, but the authoritative CombatActionInstance must also be in a legal Active phase.

Do not trace continuously while the character is merely holding a weapon.

---

# 2. Weapon Trace Profiles

Weapon/attack profiles may define:

- trace shape: line/sphere/capsule/sweep;
- start/end semantic points;
- radius;
- sampling policy;
- collision/trace channel/profile;
- max targets per swing;
- repeat-hit policy;
- debug policy;
- attack-specific hit zones.

Semantic trace points can resolve from weapon presentation components/sockets such as `Trace.Start` and `Trace.End` through the Attachment/Combat profile.

Do not require every weapon mesh to expose identical hardcoded skeleton sockets when a reusable weapon presentation profile can provide the endpoints.

---

# 3. Swept Contact Instead of Universal 100 Hz Timer

The tutorial's 100 traces/second is a prototype tuning value, not a canonical requirement.

Preferred melee contact detection uses a bounded swept-volume strategy across weapon motion during the active window so fast movement does not leave large gaps.

Possible implementation:

- remember previous trace-point transforms;
- sample current trace points during active attack evaluation;
- sphere/capsule sweep from previous to current positions;
- add candidate hit results;
- update previous transforms;
- stop immediately when the hit window closes.

Sampling cadence depends on animation/network/weapon speed and profiling. Do not globally schedule 100 Hz work for every attacker.

---

# 4. Per-Attack Hit Set

Each CombatActionInstance maintains a bounded `AlreadyHitTargets` set where the attack profile says one hit per target.

This prevents a sword sweep from applying damage repeatedly to the same character because several trace samples intersect them.

The set clears with the action/hit window according to definition.

Multi-hit attacks can explicitly permit repeated hits with their own cadence/rules.

---

# 5. Target Filtering

Candidate contact must validate:

- target is damageable;
- target is not the attacker unless self-damage is designed;
- faction/friendly-fire rules;
- attack profile allows target class/type;
- target has not already been hit where prohibited;
- collision result is current/valid;
- range/world obstruction is plausible;
- server owns/accepts the action.

Use collision channels/profiles as broad filtering, not the only gameplay authorization rule.

---

# 6. Damage Packet

Recommended conceptual record:

`S_MW_DamagePacket`

Possible fields:

- DamageEventID;
- CombatActionInstanceID;
- AttackerCharacterID;
- Instigator/controller identity;
- WeaponItemInstanceID / projectile ItemInstance provenance where relevant;
- AttackDefinitionID;
- DamageProfileID;
- base damage components;
- damage type/channel tags;
- hit result/location/normal;
- hit bone / body-zone ID;
- critical/weak-point state if valid;
- source modifier snapshot/references;
- timestamp/revision.

The packet preserves enough provenance for combat, evidence, kill/death, logging and UI.

---

# 7. Damage Types / Channels

Do not use one closed forever enum as the only damage catalog.

Use stable IDs/tags such as:

- `Damage.Physical.Slash`
- `Damage.Physical.Pierce`
- `Damage.Physical.Blunt`
- `Damage.Fire`
- `Damage.Cold`
- `Damage.Poison`
- `Damage.Electric`
- future supernatural/magic channels.

A hit may contain more than one component, for example physical piercing + poison condition application.

Unreal DamageType classes or `ApplyPointDamage` may be used as part of Blueprint event delivery where useful, but Metaworld's canonical damage meaning remains in its data-driven damage packet/tags.

---

# 8. Damage Resolution

Conceptual pipeline:

`Validated Hit`
-> build source damage from attack + exact weapon instance
-> resolve hit body zone / armor coverage
-> resolve target defenses/resistances/conditions
-> apply block/parry/guard policy where active
-> apply damage formulas/clamps
-> commit Health/other consequences
-> apply valid secondary Conditions/effects
-> emit combat feedback/events.

Do not trust a client-submitted final damage number.

---

# 9. Armor / Resistance

Armor and resistance use source-aware effective stats and equipment coverage.

Possible defense inputs:

- equipped armor ItemInstances;
- body zone/coverage;
- armor condition/durability;
- shield/block state;
- `Stat.Resistance.*` values;
- conditions/buffs/debuffs;
- attack penetration/profile;
- environmental/contextual effects.

The tutorial's diminishing-return armor equation is a useful balancing pattern, not a universal locked formula.

Every damage family can define appropriate mitigation/penetration rules.

---

# 10. Body/Bone-Specific Hits

HitResult bone/physical body can map into stable body zones such as:

- Head;
- Torso;
- Arm.Left/Right;
- Leg.Left/Right;
- other anatomy profiles.

Body zone may affect:

- damage multiplier where designed;
- armor coverage;
- injury/bleeding chance;
- reaction animation;
- evidence/projectile placement.

Do not assume every skeleton shares identical raw bone names; avatar/anatomy profile can map skeleton bones to semantic zones.

---

# 11. Health / Enemy HUD

Enemy Health uses the canonical Vitals/Stats resource system.

HUD flow:

`Authoritative Health changes`
-> replicated/local authorized event
-> enemy health presentation updates.

Possible visibility policies:

- always for targeted combatant;
- after damage for a duration;
- boss/important NPC profile;
- accessibility option;
- hidden when player should not know exact values.

UI never owns enemy Health.

---

# 12. Floating Damage Indicators

Floating damage numbers are local presentation generated from authorized combat-result events.

They can display:

- final damage amount;
- healing/absorb/block where designed;
- damage-type icon/style;
- critical/weak-point marker;
- randomized screen-space offset for readability.

Rules:

- color is not the only damage-type cue;
- do not expose hidden damage breakdown the player is not authorized to know;
- cap/merge indicators under high hit frequency;
- widget removes/pools after animation;
- no gameplay logic depends on the number widget.

---

# 13. Damage-Type Presentation

Fire/Cold/Poison/etc. can use different colors/icons/effects, but use semantic style profiles rather than hardcoding damage rules inside widgets.

Example:

`Damage.Fire`
-> presentation style Fire
-> orange/red + flame icon + optional impact VFX.

Resistance calculation happens before presentation and is not inferred from color.

---

# 14. Reactions / Conditions

A committed hit can trigger secondary systems according to damage profile and result:

- hit reaction/stagger;
- Bleeding;
- Burning;
- Poison;
- stun/knockdown;
- armor durability loss;
- weapon durability effects;
- blood/VFX;
- evidence/crime/combat logging;
- death pipeline.

Secondary effects remain server-authoritative and use the Status Effect/Item/World systems.

---

# 15. Ranged Compatibility

The damage packet is shared with bows/firearms/magic.

Ranged contact may come from projectile or validated traces rather than melee weapon sweeps, but final resolution uses the same target defense/damage framework.

This supports:

- arrow bone hits;
- sticking projectiles;
- ammunition provenance;
- finite ammunition rules;
- spell damage channels.

---

# 16. Multiplayer / Anti-Cheat

Server validates:

- active attack/window;
- attacker position/orientation plausibility;
- weapon/equipment state;
- candidate hit;
- per-action hit set;
- source stats/damage;
- target defenses;
- final resource change.

Client can assist prediction/presentation but cannot send `Target takes 500 damage` as trusted truth.

---

# 17. Performance

- traces exist only during active windows;
- no universal permanent trace timer;
- per-action hit sets are short-lived;
- debug traces disabled outside development;
- damage calculations operate on compact snapshots/data;
- floating indicator creation is capped/pooled/merged where necessary;
- distant/nonrelevant combat presentation scales down while server result remains accurate.

---

# 18. Acceptance Tests

1. Weapon cannot deal melee damage outside active hit window.
2. One normal swing cannot damage the same target repeatedly from multiple trace samples.
3. Fast weapon sweep does not miss obvious contact due to trace gaps.
4. Exact WeaponItemInstanceID influences source stats without trusting the client.
5. Armor coverage/body zone affects mitigation where designed.
6. Different damage channels use their own resistance rules.
7. Health clamps/updates authoritatively and enemy HUD follows events.
8. Floating number cannot alter Health.
9. Poison/fire secondary effects use the Status Effect system.
10. Debug/offline presentation can be disabled without changing combat result.
11. Melee, bow, firearm and magic can share damage-resolution contracts.
12. Client cannot apply damage by firing a local notify or fake trace alone.

## Core Rule

> Metaworld separates contact, damage and feedback. Attack windows generate valid contact candidates; the server resolves an evidence-rich damage packet from the exact weapon/action and target defenses; Stats/Conditions commit the consequence; health bars, numbers, blood and sounds merely present the result.