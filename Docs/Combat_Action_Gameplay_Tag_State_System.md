# Metaworld — Combat Action, Gameplay Tag & State Coordination System

**Status:** Canonical / Approved Modern RPG Playlist Upgrade

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first / server-authoritative / Gameplay-Tag-driven / componentized

## Canonical Principle

Combat state is coordinated through a reusable Combat Component plus semantic Gameplay Tags and explicit action instances. Tags describe what the character is doing or what is blocked; they do not replace authoritative combat transactions, equipped ItemInstances, stamina/resources, animation state, or damage validation.

> Gameplay Tags answer questions such as “is this character attacking?” or “is weapon changing blocked?” The Combat system still owns the actual action, timing, cost, target and result.

Related canon:

- `Docs/Avatar_Communication_Character_Animation_Architecture.md`
- `Docs/Equipment_Armor_Weapon_Attachment_Avatar_Fitting_Architecture.md`
- `Docs/Character_Action_Movement_State_Resolver_System.md`
- `Docs/Stats_Attributes_Item_Modifiers_Encumbrance_System.md`
- `Docs/Status_Effects_Conditions_Buffs_Debuffs_System.md`

---

# 1. Combat Component

Recommended component:

`BPC_MW_Combat`

Shared across players, NPCs and other compatible humanoid/creature actors where practical.

Responsibilities can include:

- request/validate combat actions;
- resolve current combat/handling profile;
- action state and action-instance ownership;
- attack/block/dodge timing contracts;
- hit-attempt requests;
- damage-packet construction/dispatch;
- combat target/context hooks;
- stamina/resource costs;
- combat event dispatch to animation/UI/AI;
- authoritative combat-state replication.

Do not put all combat logic directly into `BP_MW_PlayerCharacter`.

---

# 2. Combat Interface

A Blueprint Interface is approved for owner/target communication where it prevents direct casting and preserves reusable contracts.

Possible interface operations:

- query combat-capable state;
- request owner animation/presentation event;
- receive combat hit/damage event;
- resolve combat transform/sockets;
- query faction/hostility/targetability presentation where appropriate.

Interfaces expose contracts; they do not bypass server validation.

---

# 3. Gameplay Tag Hierarchy

Suggested semantic examples:

- `Action.Combat.Attacking`
- `Action.Combat.Blocking`
- `Action.Combat.Dodging`
- `Action.Combat.ChangingWeapon`
- `Action.Combat.DrawingWeapon`
- `Action.Combat.StowingWeapon`
- `Action.Combat.Recovering`
- `State.Combat.WeaponReady`
- `State.Combat.Unarmed`
- `State.Combat.Guarding`
- `State.Combat.Stunned`
- `Restriction.Combat.NoAttack`
- `Restriction.Combat.NoDodge`
- `Restriction.Combat.NoWeaponChange`

Hierarchy enables broad checks such as `Action.Combat.*` while retaining specific intent.

---

# 4. Tags Are Not the Action Instance

A tag like `Action.Combat.Attacking` is not enough to identify:

- which attack;
- which equipped weapon ItemInstance;
- start time;
- combo index;
- stamina cost;
- active hit window;
- already-hit targets;
- damage packet/profile;
- interruption state.

Use an explicit authoritative combat action record/instance alongside tags.

Possible fields:

- CombatActionInstanceID
- ActionDefinitionID
- CharacterID
- WeaponItemInstanceID / Unarmed profile
- StartTime
- CurrentPhase
- ComboStep
- Target/context where applicable
- Cost/reservation state
- interruption/cancel reason
- revision.

---

# 5. Action Eligibility

A combat action may require/check:

- current action tags/state;
- equipped weapon/handling profile;
- Stamina/Mana/other resource cost;
- Encumbrance;
- injury/status effects;
- movement/traversal/environment state;
- weapon condition/ammo where applicable;
- target/range/context;
- cooldown/recovery windows;
- hands/slots availability.

Do not treat “tag absent” as the only eligibility condition.

---

# 6. Blocking / Dodging / Attacking

Each action family owns a data profile.

Attack profile may define:

- montage/animation reference;
- hit windows;
- stamina cost;
- movement/rotation policy;
- damage profile;
- combo links;
- recovery/cancel windows.

Block profile may define:

- valid blocking equipment/stance;
- block angle;
- stamina/guard cost;
- damage-type coverage;
- perfect/parry window where later designed.

Dodge profile may define:

- directional options;
- stamina cost;
- movement/root-motion profile;
- invulnerability policy if any;
- recovery.

No assumption is made that every character receives the same block/dodge behavior.

---

# 7. Action Mutual Exclusion / Compatibility

Combat state should be data-driven enough to answer questions such as:

- can drink while walking? maybe;
- can attack while drinking? normally no;
- can weapon-change during attack recovery? depends on cancel window;
- can dodge while blocking? profile dependent;
- can attack from ladder/ledge? normally restricted unless specific action exists;
- can fight while swimming? weapon/action dependent.

The shared Character Action/Movement resolver consumes these restrictions so systems do not fight over speed/input.

---

# 8. Input

Use Enhanced Input logical intents, for example:

- `IA_MW_AttackPrimary`
- `IA_MW_AttackSecondary`
- `IA_MW_Block`
- `IA_MW_Dodge`
- `IA_MW_WeaponReadyToggle`
- future aim/lock-on/alternate actions.

Keyboard, Xbox-style and PlayStation-style mappings remain separate physical mappings.

Input requests an action; it does not directly apply damage or change authoritative weapon state.

---

# 9. Animation Integration

Combat action state feeds `ABP_MW_Master` / Linked Combat Animation Layers.

Animation may use:

- Montages;
- Montage Sections;
- Notify/Notify States;
- Motion Warping;
- Root Motion;
- combat locomotion profiles;
- IK/weapon grip;
- hit reactions.

Notifies expose phase/timing signals but gameplay action state remains authoritative.

---

# 10. AI Compatibility

NPC AI submits the same conceptual combat requests through its decision layer.

AI does not receive a second damage system.

StateTree/behavior can decide:

- attack;
- block;
- dodge;
- switch weapon;
- retreat;
- use item;

while `BPC_MW_Combat` applies the same legality/timing/damage contracts.

---

# 11. Multiplayer / Authority

Server owns gameplay-relevant action acceptance, resource costs, weapon state, hit validation and damage.

Clients may predict responsive animation/movement where safe, but cannot grant themselves:

- zero recovery;
- infinite stamina;
- impossible weapon changes;
- damage by locally adding an attack tag.

Replicate compact action/tag state required for remote presentation and reconciliation.

---

# 12. Performance

- no combat Tick solely to inspect tags;
- evaluate eligibility when input/state changes;
- action windows schedule only while active;
- tags remain compact semantic state;
- distant NPC combat presentation can reduce fidelity while server combat state stays valid;
- expensive target/hit checks occur only during relevant combat phases.

---

# 13. Acceptance Tests

1. Player and NPC can use the same Combat Component contract.
2. `Action.Combat.Attacking` blocks incompatible actions according to policy.
3. Adding/removing a tag alone cannot create damage.
4. Attack action retains exact equipped WeaponItemInstanceID.
5. Stamina/Encumbrance/status restrictions are respected.
6. Weapon change cannot overlap illegal attack/dodge phases.
7. Combat actions work with KBM/Xbox-style/PlayStation-style Enhanced Input.
8. Interrupt/cancel clears owned tags and action state exactly once.
9. Remote clients see correct combat-ready/attack/block presentation.
10. Modified client cannot self-authorize impossible actions by changing local tags.

## Core Rule

> Metaworld uses Gameplay Tags as the shared combat vocabulary and an authoritative Combat Action instance as the shared combat truth. The tags keep systems readable and composable; the component owns legality, timing, resources, weapon identity and outcomes.