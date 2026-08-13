# Metaworld — Combat Combo, Action Windows & Attack Timing System

**Status:** Canonical / Approved Modern RPG Playlist Upgrade

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first / montage-driven presentation / authoritative action timing / data-driven combos

## Canonical Principle

Combat responsiveness comes from explicit action phases and input windows, not from clearing all combat state as soon as an animation has visually passed its useful frames. Animation Notifies/Notify States mark candidate phases, while the authoritative combat action decides whether a follow-up, cancel or hit is legal.

> A combo is a sequence of legal combat actions joined by authored windows. It is not unrestricted attack-button spam and it is not merely “jump to the next montage section.”

Related canon:

- `Docs/Combat_Action_Gameplay_Tag_State_System.md`
- `Docs/Weapon_Draw_Stow_Switch_Combat_Handling_System.md`
- `Docs/Animation_Authoring_Control_Rig_Root_Motion_Workflow.md`
- `Docs/Character_Action_Movement_State_Resolver_System.md`

---

# 1. Attack Definition / Combo Graph

Use stable AttackDefinitionID / CombatActionDefinitionID.

Possible data:

- AttackDefinitionID;
- handling/weapon capability requirements;
- montage + section;
- stamina/resource cost;
- startup phase;
- active hit window(s);
- combo-input window;
- cancel window(s);
- recovery duration;
- movement/root-motion profile;
- facing/rotation policy;
- damage profile;
- next legal AttackDefinitionIDs;
- AI weighting/context.

A four-section tutorial montage is an acceptable content setup, not the permanent maximum combo structure.

---

# 2. Action Phases

Suggested phases:

- Startup;
- Active;
- Recovery;
- ComboWindowOpen/Buffered;
- CancelWindow;
- Finished/Interrupted.

Not every attack needs the exact same timings.

Heavy attacks can have long startup/recovery; quick knife strikes may have short windows.

---

# 3. Animation Notifies / Notify States

Approved uses:

- open/close hit window;
- open/close combo input window;
- enable selected follow-up actions;
- weapon trail/audio/VFX;
- foot/impact events;
- presentation attachment events.

A notify such as `CanExecuteAction` is interpreted as an authored action-window signal, not permission to delete all current action truth prematurely.

Server/action state verifies the active action and window before accepting a transition.

---

# 4. Input Buffering

If the player presses Attack during an approved combo window, store a bounded follow-up request.

Example:

`Attack 1`
-> combo window opens
-> player presses Attack
-> buffer `Attack 2`
-> current section reaches transition phase
-> validate current state/resource/weapon
-> start Attack 2.

If input is too early/late, policy can ignore it or buffer only within a configured grace window.

No unbounded command queue.

---

# 5. Spam Prevention

Repeated attack input cannot:

- restart Startup every frame;
- skip required recovery unless an authored cancel exists;
- duplicate stamina charges or damage windows;
- start multiple combat action instances;
- produce multiple item-consumption commits.

Action-window state provides responsiveness without abandoning restrictions.

---

# 6. Cross-Action Fluidity

The same action-window framework can apply to:

- draw/stow;
- dodge;
- block/parry transitions;
- consumable use;
- selected interactions.

But each action declares which follow-ups are compatible.

Example:

- drink potion may allow Walk during use;
- after commitment/recovery window it may allow Dodge;
- it may not allow Attack before the committed use phase.

Do not use one universal notify that blindly clears every action restriction.

---

# 7. Attack Speed

Attack Speed may modify authored timing only through bounded/profile-approved scaling.

Possible policy:

- montage play-rate multiplier from effective AttackSpeed;
- minimum/maximum play rate per attack family;
- hit/combo/recovery windows scale consistently with the montage/action timeline;
- gameplay costs and damage remain independently balanced.

Do not allow extreme AttackSpeed to collapse startup/recovery to zero or create trace/network cadence beyond supported limits.

---

# 8. Root Motion / Forward Commitment

Root Motion is approved for committed melee steps/lunges where authored.

Rules:

- action validates movement eligibility before start;
- root motion belongs to the attack's movement profile;
- Motion Warping may align to a valid target/context where appropriate;
- client root motion does not authorize a hit or teleport through blocked geometry;
- Encumbrance/status/action restrictions can alter which attacks are legal.

---

# 9. Potion Bug Lesson

The tutorial fixes multiple potion consumption by moving logic to the correct notify callback.

Metaworld already treats consumable use as an authoritative action with a single commit phase.

Therefore:

- one active UseActionInstance;
- one reserved ItemInstance/quantity;
- one approved commit;
- duplicate notify callbacks are idempotent/ignored after commit.

The combo/action-window system shares that same phase discipline.

---

# 10. AI

NPC combat can select from the same AttackDefinitions/combo links according to skill/AI context.

AI is not forced to execute every combo to completion; it can choose allowed follow-ups, block, retreat or recover according to decision logic.

---

# 11. Multiplayer / Authority

Server owns action transition legality, costs and active windows used for gameplay.

Clients can predict animation/input buffering for responsiveness but cannot:

- jump to a forbidden combo section;
- ignore recovery;
- claim an active hit window outside authoritative timing;
- apply damage because a local notify fired.

---

# 12. Acceptance Tests

1. Attack input before a valid window cannot illegally skip startup.
2. Buffered input during a valid window chains to the configured next attack.
3. Missing follow-up ends combo cleanly.
4. Spam cannot create two active attack instances.
5. Action tags/windows clear exactly once on finish/interruption.
6. AttackSpeed changes feel responsive but remain within profile bounds.
7. Hit window stays synchronized with scaled attack timing.
8. Weapon switching/drinking respects compatible cancel windows.
9. Root-motion attack cannot bypass server collision/target validation.
10. NPC can use the same attack definitions without Player Blueprint logic.

## Core Rule

> Metaworld combat chains actions through explicit authored windows. Notifies tell the Combat system when a phase is available; the authoritative action instance verifies the transition, preserves resource and hit timing, and keeps responsiveness without turning combat into unrestricted montage skipping.