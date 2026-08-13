# Metaworld — Modern RPG UE5 Playlist Intake — Part 16

**Status:** Canonical Playlist Intake Log Continuation

**Continues:** `Docs/Modern_RPG_UE5_Playlist_Intake_Part15.md`

**Playlist Source:** Unreal Engine RPG tutorial series

**Metaworld Target Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first

All permanent intake rules from Part 1 remain active.

This Part contains **Episodes 137–151**.

---

# Episode 137 — MetaHuman Facial Animation / Expressions / Sleep Face

**Classification:** UPGRADE — FACIAL ANIMATION EXTENSION.

**Phase Ownership:** Avatar + Animation + Dialogue/Social + Rest.

Detailed companion:

`Docs/MetaHuman_Facial_Expression_LipSync_Runtime_System.md`

## Approved Tutorial Intent

- MetaHuman facial Control Rig/Sequencer authoring;
- custom blink/closed-eye sleep expression;
- pose library expressions and visemes;
- reusable facial animation playback;
- Live Link/captured performance as higher-complexity option.

## Metaworld Upgrades

- facial animation is a layered presentation system, separate from gameplay authority;
- semantic facial intents such as sleep/pain/anger/speech drive runtime presentation;
- do not universally disconnect face Leader Pose or disable MetaHuman post-process processing merely because the tutorial prototype required it;
- current UE5.8 MetaHuman face/component configuration is validated per avatar/fidelity profile;
- speech visemes can layer with emotion/blink/look-at;
- hero/nearby/crowd facial fidelity scales by significance.

### Episode 137 Principle

> Gameplay says what the character is expressing; the MetaHuman facial layer decides how that expression is rendered at the current fidelity tier.

---

# Episode 138 — Combat Chapter Preview / Scope Map

**Classification:** RESEARCH — COMBAT SCOPE MAP.

**Phase Ownership:** Combat + Animation + Ranged + Magic + Feedback.

## Captured Scope

Tutorial chapter intends to cover:

- melee attacks;
- blocking;
- dodging;
- damage calculation;
- hit reactions;
- audiovisual combat feedback;
- weapon trails/blood/camera response;
- bows/arrows/bone hits;
- ranged collision;
- ranged magic/custom spells.

## Metaworld Rule

This preview does not lock implementation details by itself.

Metaworld combat remains capability/equipment driven and must support:

- unarmed/body combat;
- improvised weapons;
- swords/blunt/piercing tools;
- shields;
- bows/crossbows;
- firearms subject to finite ammunition supply;
- supernatural/magic abilities;
- player and NPC use of common combat contracts.

### Episode 138 Principle

> The tutorial defines the upcoming research surface; Metaworld's authoritative combat architecture is established by the implementation episodes and existing world canon.

---

# Episode 139 — Gameplay Tags / Combat Component / Interface

**Classification:** LOCKED + UPGRADE — COMBAT FOUNDATION.

**Phase Ownership:** Combat + Character State + AI + Multiplayer.

Detailed companion:

`Docs/Combat_Action_Gameplay_Tag_State_System.md`

## Approved Tutorial Intent

- hierarchical Gameplay Tags instead of sprawling combat booleans;
- reusable Combat Component for players/enemies;
- Blueprint Interface for owner communication;
- modular shared combat logic.

## Metaworld Upgrades

- `BPC_MW_Combat` becomes the reusable combat authority/coordinator;
- tags such as `Action.Combat.Attacking`, `Blocking`, `Dodging`, `ChangingWeapon` form a semantic vocabulary;
- tags describe/gate state but do not replace explicit CombatActionInstance data;
- action instance retains weapon ItemInstance, timing, costs, phases and hit state;
- AI requests the same action contracts rather than using a second combat implementation;
- no requirement to adopt a paid/external service or a C++-only combat baseline.

### Episode 139 Principle

> Gameplay Tags keep combat state readable; the Combat Component and explicit action instance own what is actually happening and whether it is legal.

---

# Episode 140 — Weapon Handling Types / Hand Sockets / Equipped Presentation

**Classification:** UPGRADE — COMBAT HANDLING PROFILE FOUNDATION.

**Phase Ownership:** Equipment + Combat + Animation + Attachment.

Detailed companion:

`Docs/Weapon_Draw_Stow_Switch_Combat_Handling_System.md`

## Approved Tutorial Intent

- determine current weapon handling from equipped Main/Off Hand state;
- separate stowed and hand attachment sockets;
- correct weapon pivots/attachment transforms;
- update attachment logic for held combat presentation.

## Metaworld Upgrades

- reject numeric `100/200` combat enum as permanent identity;
- use data/tags such as OneHanded/TwoHanded/DualWield/Shield/Bow/Handgun/Rifle/Improvised;
- exact equipped ItemInstances determine handling profile;
- semantic attachment targets map to avatar-specific actual sockets;
- combat preview uses the same equipment state without becoming a second owner.

### Episode 140 Principle

> Weapon handling is derived from the exact equipped items and their capabilities, while socket names and attachment transforms remain presentation data.

---

# Episode 141 — Draw / Equip Weapon Montages

**Classification:** UPGRADE — APPROVED DRAW/READY ACTION.

**Phase Ownership:** Combat + Equipment + Animation.

Detailed companion:

`Docs/Weapon_Draw_Stow_Switch_Combat_Handling_System.md`

## Approved Tutorial Intent

- draw/equip Montages by weapon family;
- upper-body slots so locomotion can continue where allowed;
- Gameplay Tag for weapon-ready state;
- Montage Notify for moving weapon from stowed socket to hand.

## Metaworld Upgrades

- draw is an authoritative Combat Action with Drawing phase/tag;
- same ItemInstance remains equipped before/during/after the montage;
- notify changes visual attachment at approved phase but never creates ownership;
- weapon family chooses data-driven handling/animation profile;
- interruption reconciles attachment from authoritative readiness state.

### Episode 141 Principle

> Drawing a weapon changes readiness and visual attachment of the same equipped ItemInstance; animation controls timing, not ownership.

---

# Episode 142 — Weapon Stow / Unequip / Anti-Spam

**Classification:** LOCKED + UPGRADE — ACTION GATING.

**Phase Ownership:** Combat + Equipment + Animation + Input.

Detailed companions:

- `Docs/Weapon_Draw_Stow_Switch_Combat_Handling_System.md`
- `Docs/Combat_Action_Gameplay_Tag_State_System.md`

## Approved Tutorial Intent

- stow/unequip montages;
- notify for moving held weapons back to storage attachment;
- `ChangingWeapons` Gameplay Tag;
- reject conflicting repeated input while changing weapon;
- clear action restriction after montage completion/action-open phase.

## Metaworld Upgrades

- Stowing is readiness state, not removing the ItemInstance from Equipment unless a separate Unequip transaction was requested;
- anti-spam comes from shared combat action state, not isolated booleans;
- completion/interruption cleanup is idempotent;
- montage-specific Blend Out tuning remains asset-specific rather than universal project law.

### Episode 142 Principle

> Weapon-change spam is prevented by the same explicit action-state system that protects attacks, dodges and other committed actions.

---

# Episode 143 — Weapon Switching / Off-Hand Preservation

**Classification:** UPGRADE — APPROVED SWITCH TRANSACTION.

**Phase Ownership:** Combat + Equipment + Animation.

Detailed companion:

`Docs/Weapon_Draw_Stow_Switch_Combat_Handling_System.md`

## Approved Tutorial Intent

- switch directly between weapon configurations;
- stow current presentation then ready new presentation;
- preserve Off-Hand/shield state;
- integrate switching with attachment/equipment updates;
- improve montage blending.

## Metaworld Upgrades

- do not destroy authoritative current item and mint a replacement when switching;
- Equipment owns all exact ItemInstances throughout transition;
- two-handed/off-hand conflicts resolve through canonical Equipment rules;
- presentation Actor recreation, if used, is not ownership replacement;
- switch animation profile is selected by handling transition data.

### Episode 143 Principle

> Switching changes which equipped ItemInstances are combat-ready; it never erases the identity/history of the weapons being switched.

---

# Episode 144 — Fluid Action Windows / Can Execute Notify

**Classification:** UPGRADE — ACTION WINDOW FOUNDATION.

**Phase Ownership:** Combat + Animation + Character Actions.

Detailed companion:

`Docs/Combat_Combo_Action_Windows_Attack_Timing_System.md`

## Approved Tutorial Intent

- custom animation notify/notify state to reopen legal action input before the montage's unused tail frames finish;
- use Gameplay Tags to block conflicting actions;
- apply action-window concept to draw/stow and potion use;
- improve responsiveness without uncontrolled spam.

## Metaworld Upgrades

- a notify opens a specific authored action/cancel/follow-up window; it does not blindly clear every action restriction;
- authoritative action instance validates the requested transition;
- startup/active/recovery/cancel phases remain explicit;
- each action profile defines which follow-ups are legal.

### Episode 144 Principle

> Responsiveness comes from authored legal transition windows, not from pretending the current action ended earlier than it actually did.

---

# Episode 145 — Melee Attack Combo / Attack Speed / Potion Commit Fix

**Classification:** UPGRADE — COMBO SYSTEM APPROVED.

**Phase Ownership:** Combat + Animation + Stats + Item Use.

Detailed companion:

`Docs/Combat_Combo_Action_Windows_Attack_Timing_System.md`

## Approved Tutorial Intent

- montage sections for multi-hit combo sequence;
- input window via Notify State;
- reset when combo ends;
- spam prevention through action windows;
- Root Motion for slight committed advance;
- Attack Speed affects montage playback;
- potion consumption corrected to one notify phase.

## Metaworld Upgrades

- combo links are data-driven AttackDefinitions, not permanently fixed to exactly four attacks;
- input buffering is bounded to legal combo windows;
- server/action state validates each transition and resource cost;
- Attack Speed is profile-bounded so extreme values cannot eliminate all recovery/hit timing;
- potion use already has one authoritative commit, making duplicate notify callbacks harmless after commit;
- root motion affects movement presentation but never authorizes hits.

### Episode 145 Principle

> A combo is a graph of legal timed attacks with buffered follow-ups, not repeated montage-section jumps driven directly by button spam.

---

# Episode 146 — Melee Line/Sphere Trace Hit Detection

**Classification:** UPGRADE — AUTHORITATIVE HIT-DETECTION FOUNDATION.

**Phase Ownership:** Combat + Collision + Animation + Performance.

Detailed companion:

`Docs/Combat_Hit_Detection_Damage_Resistance_Feedback_System.md`

## Approved Tutorial Intent

- Notify State marks active swing frames;
- Combat Component performs hit detection;
- sphere/swept trace is more forgiving than one thin line;
- trace endpoints live on reusable weapon presentation;
- per-swing ignore set prevents repeated hit damage;
- debug tracing during development.

## Metaworld Upgrades

- tutorial 100 Hz timer is prototype tuning only;
- use bounded swept weapon contact across previous/current trace-point motion during active windows;
- exact CombatActionInstance owns `AlreadyHitTargets`;
- collision channel broadly filters candidates but server gameplay validates actual target legality;
- no permanent traces outside attack windows;
- trace finds contact only; damage is resolved separately.

### Episode 146 Principle

> Attack windows generate bounded swept contact candidates; the server Combat system decides which contacts are valid once-per-attack hits.

---

# Episode 147 — Enemy Health Bar / Stats Events

**Classification:** UPGRADE — APPROVED COMBAT HUD PRESENTATION.

**Phase Ownership:** Vitals + Combat + HUD + NPC.

Detailed companion:

`Docs/Combat_Hit_Detection_Damage_Resistance_Feedback_System.md`

## Approved Tutorial Intent

- enemies use reusable Stats/Vitals Health;
- enemy health widget;
- Blueprint Interface/component communication;
- event-driven Health updates.

## Metaworld Upgrades

- enemy Health uses canonical Resource Current/Max semantics;
- UI visibility can depend on targeting/damage/knowledge/profile rather than always exposing every NPC exact Health;
- no per-frame Health binding;
- health bar remains presentation and cannot edit Health.

### Episode 147 Principle

> Enemy health is authoritative Vitals state; the combat HUD subscribes to the permitted presentation of that state.

---

# Episode 148 — Damage Calculation / Armor / Floating Damage Numbers

**Classification:** UPGRADE — NEW AUTHORITATIVE DAMAGE PIPELINE.

**Phase Ownership:** Combat + Stats + Equipment + HUD/VFX.

Detailed companion:

`Docs/Combat_Hit_Detection_Damage_Resistance_Feedback_System.md`

## Approved Tutorial Intent

- point-hit damage context;
- reusable damage calculation in Combat Component;
- armor mitigation;
- floating damage indicators;
- offset/fade/cleanup presentation.

## Metaworld Upgrades

- validated hit builds `S_MW_DamagePacket` with attacker/action/exact WeaponItemInstanceID/hit result/body zone;
- server resolves source damage and target armor/resistance; clients never submit trusted final damage;
- tutorial diminishing-return formula is a balancing candidate, not universal law;
- floating numbers use committed result events, may merge/cap, and never own damage;
- combat result can feed injury/evidence/death systems later.

### Episode 148 Principle

> Contact creates a damage request; the server resolves the exact weapon, attack and target defenses; UI only reports the committed result.

---

# Episode 149 — Damage Types / Elemental Resistances

**Classification:** UPGRADE — APPROVED DATA-DRIVEN DAMAGE CHANNELS.

**Phase Ownership:** Combat + Stats + Status Effects + Magic.

Detailed companion:

`Docs/Combat_Hit_Detection_Damage_Resistance_Feedback_System.md`

## Approved Tutorial Intent

- Physical/Fire/Cold/Poison/Lightning-style damage categories;
- pass damage-type information through shared combat logic;
- type-specific presentation;
- resistance-based mitigation.

## Metaworld Upgrades

- stable hierarchical IDs/tags replace a closed forever enum;
- physical can further distinguish Slash/Pierce/Blunt;
- a single hit may contain multiple damage components;
- poison/burning can additionally apply Status Effects rather than only one raw damage number;
- body armor coverage, condition and resistance sources participate in mitigation;
- color is secondary to icon/text/style for accessibility.

### Episode 149 Principle

> Damage type is semantic combat data used by mitigation, status effects and presentation—not merely the color chosen for the floating number.

---

# Episode 150 — Weapon-Specific Combat Locomotion Blend Space

**Classification:** UPGRADE — COMBAT LOCOMOTION PROFILE.

**Phase Ownership:** Animation + Equipment + Movement + Combat.

Detailed companion:

`Docs/Combat_Locomotion_Facing_Root_Motion_System.md`

## Approved Tutorial Intent

- ready-weapon state changes idle/locomotion pose;
- weapon handling selects appropriate locomotion set;
- two-handed Blend Space covers idle/walk/run/sprint;
- reduce weapon/body overlap.

## Metaworld Upgrades

- combat locomotion comes from HandlingProfile rather than numeric enum;
- Blend Space is valid for focused profiles but Motion Matching/Linked Layers remain preferred options where appropriate;
- animation reads effective movement speed from the Movement Resolver rather than setting gameplay speed;
- body customization/socket/IK/Control Rig all participate in clipping QA;
- distant NPCs may use simpler combat locomotion.

### Episode 150 Principle

> Equipment chooses the combat stance/animation profile; the movement system still decides how fast and where the character can actually move.

---

# Episode 151 — Attack Rotation / Root Motion Forward Movement / Spacing

**Classification:** UPGRADE — COMBAT FACING + COMMITMENT POLISH.

**Phase Ownership:** Combat + Movement + Animation + Collision.

Detailed companion:

`Docs/Combat_Locomotion_Facing_Root_Motion_System.md`

## Approved Tutorial Intent

- authored attack-phase rotation toward control/camera direction;
- clamp maximum turn during an attack;
- smooth interpolation rather than abrupt snap;
- Control Rig/Sequencer-authored slight forward attack movement;
- Root Motion-enabled attack sequences;
- tune combat spacing.

## Metaworld Upgrades

- facing correction exists only in an attack-defined RotationWindow;
- max angle/turn curve is per AttackDefinition, not universally 90 degrees;
- camera direction is player intent but action state/collision decide legal rotation;
- root motion belongs to the attack movement profile and cannot authorize damage;
- Motion Warping can align committed actions to valid targets where useful;
- enemy capsule size is not the universal fix for one animation's spacing problem;
- reach, action root motion, AI range and body/collision profiles are balanced together.

### Episode 151 Principle

> Attacks can rotate and step forward to feel committed and responsive, but those movements remain bounded by the attack profile, world collision and authoritative combat state.

---

# Part 16 Consolidated Additions

New companions introduced in this Part:

- `Docs/MetaHuman_Facial_Expression_LipSync_Runtime_System.md`
- `Docs/Combat_Action_Gameplay_Tag_State_System.md`
- `Docs/Weapon_Draw_Stow_Switch_Combat_Handling_System.md`
- `Docs/Combat_Combo_Action_Windows_Attack_Timing_System.md`
- `Docs/Combat_Hit_Detection_Damage_Resistance_Feedback_System.md`
- `Docs/Combat_Locomotion_Facing_Root_Motion_System.md`

Core combat chain:

`Enhanced Input / AI Intent`
-> `Combat Action Request`
-> `Gameplay Tags + Explicit CombatActionInstance`
-> `Exact Equipped ItemInstance / Handling Profile`
-> `Montage / Action Windows`
-> `Active Hit Window`
-> `Swept Contact Candidate`
-> `Authoritative Damage Packet`
-> `Armor / Resistance / Status Resolution`
-> `Vitals Consequence`
-> `HUD / Blood / Sound / Reaction Presentation`.

Facial chain:

`Dialogue / Emotion / Rest State`
-> `Semantic Facial Intent`
-> `MetaHuman Facial Layer / Control Rig / Captured Performance`
-> `Fidelity-scaled expression/lip sync`.

## Part 16 Core Rule

> Metaworld combat is built from authoritative action state, exact persistent equipment and data-driven timing. Gameplay Tags organize the state, animation exposes authored windows, traces find contacts, the server resolves damage, and every visual—from weapon draw to floating numbers to facial reactions—presents rather than replaces that truth.