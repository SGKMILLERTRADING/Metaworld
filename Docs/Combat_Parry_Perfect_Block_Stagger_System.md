# Metaworld — Perfect Block, Parry, Stagger & Counter Window System

**Status:** Canonical / Approved Modern RPG Playlist Upgrade

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first / server-authoritative / action-window-driven / equipment-profile aware

## Canonical Principle

A perfect block/parry is a short, authored defensive timing window inside a valid block/parry action. If an eligible incoming attack contacts the defender during that window, the server resolves a parry result that may stagger the attacker, alter Guard/Stamina and open a counter opportunity.

> Parry is a timing result, not a permanent status tag. The window belongs to one defensive action, the incoming hit must be eligible, and the server decides whether the parry succeeded.

Related canon:

- `Docs/Combat_Defense_Block_Dodge_Guard_Stamina_Input_Buffer_System.md`
- `Docs/Combat_Action_Gameplay_Tag_State_System.md`
- `Docs/Combat_Hit_Detection_Damage_Resistance_Feedback_System.md`
- `Docs/Combat_Feedback_Audio_Blood_VFX_System.md`

---

# 1. Parry Window

A Block/Parry profile can define:

- parry window start/end;
- eligible incoming attack tags/types;
- allowed equipment/handling profiles;
- Guard/Stamina cost;
- attacker stagger strength/duration/profile;
- defender recovery/counter advantage;
- VFX/audio/camera feedback profile;
- cooldown/anti-spam policy where desired.

Tutorial timing such as `0.1 seconds` is prototype tuning only.

---

# 2. Window Ownership

Suggested semantic state:

`Defense.Window.Parry`

But the actual authority is the active defensive CombatActionInstance with authoritative phase/timestamps.

Animation Notify State may mark the expected parry window for presentation/timing alignment.

Client-added tags cannot create a successful parry.

---

# 3. Incoming Attack Eligibility

Not every attack must be parryable.

Parry validation can consider:

- attack definition/tag;
- melee/ranged/magic type;
- impact direction;
- defender equipment;
- attacker/defender state;
- attack power/weight class;
- unblockable/unparryable profile tags;
- weapon/item condition where designed.

A giant creature slam may behave differently from a sword cut.

---

# 4. Successful Parry Flow

`Incoming validated hit candidate`
-> target currently has legal parry window?
-> attack eligible?
-> direction/equipment valid?
-> server commits ParryResult
-> incoming Health/Guard damage resolved according to profile
-> attacker receives Stagger/Parried reaction
-> defender receives counter/recovery benefit if defined
-> feedback event emitted.

The parry is resolved once for that contact/action.

---

# 5. Stagger

Attacker stagger is an explicit combat action/state, not merely an animation.

Possible semantic tags:

- `State.Combat.Staggered`
- `State.Combat.Stunned`

Stagger profile can define:

- duration/recovery phase;
- movement/action restrictions;
- montage/animation layer;
- Guard effect;
- target-lock behavior;
- counter-vulnerability profile.

A character cannot cancel stagger by forcing another montage locally.

---

# 6. Parry Animations

Different handling profiles may use different parry reactions:

- one-handed;
- two-handed;
- shield;
- dual-wield;
- unarmed/special martial profile where later designed.

Selection comes from the active equipment/handling profile, not a closed tutorial CombatType enum.

Root motion may be used for authored reaction/spacing where safe and validated.

---

# 7. Counter Window

A successful parry may open a short counter opportunity.

Counter profile can influence:

- action priority;
- allowed follow-up attacks;
- target facing/lock assistance;
- damage/Guard bonus only if intentionally designed;
- AI decision opportunity.

It does not automatically guarantee a critical hit unless the combat definition says so.

---

# 8. Guard / Stamina Interaction

Parry can:

- spend Stamina;
- reduce incoming Guard damage;
- prevent ordinary Guard loss;
- restore/benefit Guard where designed;
- damage the attacker's Guard/stability.

Exact policy is data-driven.

Perfect block does not create free infinite defense.

---

# 9. Audio / VFX / Camera

Approved feedback:

- weapon/shield-specific parry sound;
- sparks/flash Niagara;
- localized camera shake/haptics;
- hit-stop style animation emphasis where appropriate;
- HUD feedback/counter cue.

Feedback derives from the committed parry result.

---

# 10. Time Dilation Correction

Tutorial global `0.1x for 2 seconds` time dilation is **not** canonical for persistent multiplayer Metaworld.

Preferred dramatic emphasis can use:

- local camera/post-process;
- local animation emphasis;
- bounded hit-stop on participating presentation where technically safe;
- sound design/haptics;
- special instanced/single-player contexts if later designed.

Do not globally slow every unrelated player, NPC, physics system and world simulation because one player parried an attack.

---

# 11. AI Parry

NPCs can use the same parry rules when their combat AI/profile allows it.

AI decides when to request Block/Parry; the same authoritative window/eligibility rules apply.

Difficulty can influence decision quality/reaction policy without giving AI impossible hidden parry windows.

---

# 12. Multiplayer / Anti-Cheat

Server validates:

- defensive action exists;
- parry window timing;
- incoming attack timing/contact;
- angle/equipment/attack eligibility;
- attacker stagger result;
- Guard/Stamina/resource changes.

Client cannot report `PerfectParry = true` as trusted truth.

---

# 13. Acceptance Tests

1. Parry succeeds only inside the configured window.
2. Same attack outside window resolves as ordinary Block/Hit.
3. Unparryable attack cannot be parried by adding a tag.
4. Successful parry staggers attacker exactly once.
5. Stagger blocks incompatible attacker actions until recovery.
6. Parry animation matches current handling profile.
7. Root-motion parry reaction cannot bypass collision/state validation.
8. Parry feedback can be disabled/reduced without changing result.
9. Global world time is not slowed by ordinary multiplayer parry.
10. AI and player parries follow the same timing/eligibility rules.
11. Client cannot forge a parry outcome.

## Core Rule

> Metaworld perfect block/parry is an authoritative timing contest between one defensive action and one incoming attack. Equipment and attack profiles define what can be parried, the successful result can stagger and open a counter window, and dramatic feedback never replaces the underlying combat transaction.