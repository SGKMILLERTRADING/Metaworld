# Metaworld — Combat Weapon Handling & Animation Profile System

**Status:** Canonical / Approved Modern RPG Playlist Upgrade

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first / data-driven / ItemInstance-aware / server-authoritative combat / modular animation

## Canonical Principle

Weapon families do not receive separate combat engines. One-handed, dual-wield, weapon-and-shield, two-handed, bow, firearms, improvised tools and future handling styles provide data/animation/trace profiles to the same Combat, Equipment, Movement and Damage systems.

> A handling profile tells Metaworld how the currently equipped ItemInstances are held, animated and allowed to attack or defend. It does not duplicate CombatComponent logic for every weapon family.

Related canon:

- `Docs/Combat_Action_Gameplay_Tag_State_System.md`
- `Docs/Weapon_Draw_Stow_Switch_Combat_Handling_System.md`
- `Docs/Combat_Combo_Action_Windows_Attack_Timing_System.md`
- `Docs/Combat_Hit_Detection_Damage_Resistance_Feedback_System.md`
- `Docs/Combat_Locomotion_Facing_Root_Motion_System.md`
- `Docs/Combat_Defense_Block_Dodge_Guard_Stamina_Input_Buffer_System.md`
- `Docs/Equipment_Armor_Weapon_Attachment_Avatar_Fitting_Architecture.md`

---

# 1. Stable Handling Profile Identity

Suggested IDs/tags:

- `Combat.Handling.Unarmed`
- `Combat.Handling.OneHanded`
- `Combat.Handling.TwoHanded`
- `Combat.Handling.DualWield`
- `Combat.Handling.WeaponShield`
- `Combat.Handling.Bow`
- `Combat.Handling.Handgun`
- `Combat.Handling.Rifle`
- `Combat.Handling.Improvised`
- future profiles without redesign.

Do not use opaque tutorial labels such as `100`, `200`, or one closed forever enum as the canonical identity.

---

# 2. Profile Resolution

`BPC_MW_Equipment`
-> exact MainHand ItemInstanceID
-> exact OffHand ItemInstanceID
-> item capability/handling metadata
-> character restrictions/state
-> resolve `HandlingProfileID`
-> `BPC_MW_Combat` + `ABP_MW_Master` consume profile.

Profile resolution is derived from authoritative equipment state.

Example:

Main Hand = one-handed sword
Off Hand = empty
-> `Combat.Handling.OneHanded`

Main Hand = one-handed sword
Off Hand = compatible sword/dagger
-> `Combat.Handling.DualWield`

Main Hand = one-handed sword
Off Hand = shield
-> `Combat.Handling.WeaponShield`

Main Hand = two-handed greatsword
Off Hand reserved
-> `Combat.Handling.TwoHanded`

---

# 3. Suggested Handling Profile Data

A profile may define/reference:

- HandlingProfileID;
- locomotion animation profile;
- idle/walk/run/sprint presentation;
- draw/stow profile;
- combo/AttackDefinition sets;
- MainHand trace/contact profile;
- OffHand trace/contact profile;
- guard/block profile;
- dodge profile compatibility;
- attack-facing/root-motion policy;
- IK/grip profile;
- weapon socket/attachment presentation contracts;
- attack sound profile;
- allowed combo branching;
- movement restrictions;
- Stamina/Guard multipliers where explicitly designed;
- controller/input action bindings remain logical, not hardcoded keys.

The profile references reusable definitions rather than embedding giant Blueprint graphs.

---

# 4. One-Handed Handling

One-handed handling is the baseline for compatible swords, axes, clubs, knives/tools and similar weapons.

Possible characteristics:

- MainHand is primary attack source;
- OffHand may be empty or reserved for other compatible equipment according to Equipment rules;
- one-handed locomotion/profile;
- one-handed combo graph;
- one-handed block/parry profile where weapon permits;
- weapon-specific AttackDefinitions supply actual damage/reach/timing.

A one-handed animation set does not imply all one-handed weapons share identical attacks.

A knife, machete, hammer and longsword can all use the same broad handling family while selecting different attack definitions/animation variants.

---

# 5. Dual-Wield Handling

Dual Wield requires two compatible equipped ItemInstances.

Suggested state:

MainHand ItemInstanceID = Weapon A
OffHand ItemInstanceID = Weapon B
HandlingProfileID = `Combat.Handling.DualWield`

Both weapons retain independent:

- ItemInstanceID;
- condition/durability;
- upgrades;
- generated affixes;
- damage capabilities;
- material/sound profile;
- provenance/ownership.

Do not merge two weapons into one anonymous `DualWieldWeapon` object.

---

# 6. Dual-Wield Attack Source Ownership

Each AttackDefinition/attack phase explicitly declares which source participates:

- MainHand only;
- OffHand only;
- MainHand then OffHand;
- simultaneous/both where deliberately authored;
- unarmed/body source where a mixed attack permits it.

Example:

`Attack.Dual.01`
- active window A -> MainHand trace
- active window B -> OffHand trace

`Attack.Dual.02`
- active window -> OffHand only

`Attack.Dual.03`
- two distinct windows, one per hand.

The Combat system does not start a second permanent off-hand trace timer simply because Dual Wield is equipped.

Only the currently active AttackDefinition/window activates its declared contact source(s).

---

# 7. Per-Source Hit Provenance

A dual-wield hit preserves which exact weapon made contact.

DamagePacket may therefore contain:

- WeaponItemInstanceID = MainHand weapon; or
- WeaponItemInstanceID = OffHand weapon.

This matters because the two weapons may have different:

- damage;
- condition;
- affixes;
- poison/status payload;
- evidence/provenance;
- durability effects.

If both weapons legitimately contact the same target during one authored multi-hit attack, each legal hit is evaluated independently according to the AttackDefinition's repeat-hit policy.

Do not globally prevent a second legitimate weapon from hitting simply because the target appeared once in an attack-wide set. Conversely, do not allow repeated trace samples from the same authored hit window to multiply damage accidentally.

Recommended hit tracking can distinguish:

`AttackActionID + HitWindowID + SourceWeaponItemInstanceID + TargetID`.

---

# 8. One Feedback Event Per Physical Contact

The tutorial's DoOnce cleanup intent is approved, but presentation deduplication belongs to feedback/contact identity rather than one global DoOnce Boolean.

A physical contact can emit one primary impact feedback event even if the resulting DamagePacket contains multiple damage channels.

Dual Wield may legitimately produce two impact feedback events when two separate weapons physically contact at different authored times.

---

# 9. Weapon + Shield Handling

Suggested profile:

`Combat.Handling.WeaponShield`

Main Hand:
- primary weapon attacks.

Off Hand:
- shield ItemInstance;
- Guard/Block source;
- shield bash/attack source only when an AttackDefinition explicitly uses it.

The shield remains a persistent OffHand ItemInstance and retains its own condition, upgrades, weight, protection/Guard metadata and provenance.

Weapon+Shield locomotion can use its own stance/blend-space/motion-matching subset without creating a separate Movement system.

Blocking remains owned by the canonical Defense system.

---

# 10. Root Motion / Force Root Lock

Animation-authoring settings are selected according to each asset/action's purpose.

Locomotion cycles normally should not inject unintended world displacement. Techniques such as Force Root Lock may be appropriate for specific locomotion assets when they contain unwanted root translation.

Attack sequences may intentionally use root motion when their AttackDefinition permits authored combat movement.

Do not apply one root-motion setting blindly across every asset in a handling profile.

---

# 11. Rate Scale / Attack Speed

Tutorial values such as `Rate Scale = 1.4` are content-tuning examples only.

Canonical flow:

AttackDefinition base playback rate
x authorized AttackSpeed modifier
-> clamp to attack-family legal range
-> montage/animation playback rate.

Dual Wield can feel faster than a heavy weapon because its attack definitions/profile have different legal timings; it does not receive a universal permanent 1.4 multiplier.

Added transition frames and authored blend times are animation-content decisions and can be adjusted per asset.

---

# 12. Blend Spaces / Locomotion

Handling profiles may reference focused Blend Spaces where they are practical.

Examples:

- One-Handed locomotion;
- Dual Wield locomotion;
- Weapon+Shield locomotion.

The canonical movement resolver still owns actual character speed and legal movement.

Blend Space axes/ranges are presentation inputs and do not set gameplay movement speed.

Foot IK/Control Rig may refine contact and pose quality according to current handling/action state.

---

# 13. Combo Integration

Each handling profile references one or more Combo/AttackDefinition graphs.

Examples:

`Combat.Handling.OneHanded`
-> sword combo set
-> axe combo set
-> club combo set

`Combat.Handling.DualWield`
-> sword+sword profile
-> sword+dagger profile
-> dagger+dagger profile

Selection may depend on weapon capability tags and compatibility data.

Do not permanently assume every Dual Wield setup uses the same three attacks or every Weapon+Shield setup uses the same three attacks.

---

# 14. Animation Notifies

Approved notify uses include:

- candidate hit-window begin/end;
- hand/source-specific contact phase;
- swing audio request;
- footstep/effort presentation;
- combo/cancel window cues;
- draw/stow presentation transitions.

Gameplay authority must validate the matching CombatActionInstance and phase.

A client notify cannot create a hit, spend/refund stamina, change ItemInstance ownership or bypass action legality by itself.

---

# 15. AI Compatibility

NPCs use the same HandlingProfileID system.

AI decision layer can reason from:

- available attacks in current handling profile;
- distance/reach;
- stamina/Guard;
- target state;
- weapon condition;
- desired defensive/offensive behavior.

NPC Dual Wield does not require an NPC-only off-hand damage implementation.

---

# 16. Multiplayer / Replication

Server owns authoritative equipment ItemInstances, handling-profile resolution and combat actions.

Replicate compact state sufficient to reconstruct presentation, for example:

- MainHand ItemInstanceID;
- OffHand ItemInstanceID;
- ready/stowed state;
- current HandlingProfileID;
- current CombatActionID/phase as needed.

Clients do not submit a trusted `I am Dual Wielding so apply two hits` result.

---

# 17. Performance

- only active handling animation layers evaluate at full detail;
- inactive weapon trace sources do nothing;
- no permanent second off-hand trace timer;
- lower-significance NPCs use reduced animation/IK fidelity;
- asset selection occurs on equipment/handling changes, not per frame;
- impact feedback is event-driven and deduplicated by contact/result identity;
- Control Rig authoring cost is editor-side unless a runtime rig feature is explicitly needed.

---

# Acceptance Tests

1. One-handed weapon selects OneHanded profile without changing gameplay speed directly.
2. Compatible two weapons resolve DualWield profile.
3. Incompatible off-hand combination is rejected or resolves another valid profile.
4. Dual attack can activate MainHand and OffHand hit windows independently.
5. OffHand trace is inactive outside an authored off-hand hit window.
6. Same trace sample cannot repeatedly damage one target accidentally.
7. Deliberate MainHand then OffHand contacts can both damage the same target when AttackDefinition allows it.
8. DamagePacket records the exact weapon ItemInstance that contacted.
9. Weapon+Shield profile uses shield through canonical Guard/Block system.
10. Shield bash only occurs through an explicit AttackDefinition.
11. Rate scale/AttackSpeed remains inside legal profile bounds.
12. Locomotion Blend Space does not overwrite movement resolver output.
13. Root-motion attack respects world collision/action restrictions.
14. NPCs use the same handling profiles.
15. Multiplayer client cannot fake an extra off-hand hit.
16. Stowing/switching weapons resolves the correct new handling profile without destroying ItemInstances.

## Core Rule

> Metaworld has one combat engine and many handling profiles. The exact equipped ItemInstances decide the handling context; the profile selects locomotion, attacks, guard and source-specific hit windows; the shared Combat system validates every action and hit.