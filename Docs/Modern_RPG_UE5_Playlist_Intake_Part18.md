# Metaworld — Modern RPG UE5 Playlist Intake — Part 18

**Status:** Canonical Playlist Intake Log Continuation

**Continues:** `Docs/Modern_RPG_UE5_Playlist_Intake_Part17.md`

**Playlist Source:** Unreal Engine RPG tutorial series

**Metaworld Target Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first

All permanent intake rules from Part 1 remain active.

This Part contains **Episodes 165–168**.

---

# Episode 165 — Dual-Wield Combo Animation Authoring

**Classification:** UPGRADE — DUAL-WIELD HANDLING PROFILE CONTENT.

**Phase Ownership:** Combat + Animation + Combo + Root Motion + Audio/Hit Windows.

Detailed companion:

`Docs/Combat_Weapon_Handling_Animation_Profile_System.md`

## Approved Tutorial Intent

- slice a dual-wield source animation into usable attack sequences;
- add authored transition/recovery frames so attacks do not snap unnaturally;
- use Control Rig to repair poses during added frames;
- enable root motion where attack movement requires it;
- tune playback rate/blend in/out;
- place hit-trace, combat-sound and action/input notifies accurately.

## Metaworld Upgrades

- Dual Wield is a `HandlingProfileID`, not a second CombatComponent implementation;
- tutorial `1.4` rate scale is content tuning only;
- AttackSpeed modifies playback within legal attack-profile bounds;
- root motion belongs to the specific AttackDefinition and cannot authorize a hit;
- each attack defines whether MainHand, OffHand or both weapons own the active hit windows;
- Notifies mark authored phases but CombatActionInstance/server state remains authoritative;
- extra blend/transition frames are asset-level polish rather than a gameplay-state delay hack.

### Episode 165 Principle

> Dual-wield animation defines when and how each hand attacks; the shared Combat system still owns action legality, ItemInstance identity and damage.

---

# Episode 166 — Dual-Wield Locomotion / Off-Hand Hit Detection / Feedback Deduplication

**Classification:** LOCKED + UPGRADE — DUAL-HAND COMBAT INTEGRATION.

**Phase Ownership:** Combat Handling + Hit Detection + Locomotion + Feedback.

Detailed companions:

- `Docs/Combat_Weapon_Handling_Animation_Profile_System.md`
- `Docs/Combat_Hit_Detection_Damage_Resistance_Feedback_System.md`
- `Docs/Combat_Feedback_Audio_Blood_VFX_System.md`

## Approved Tutorial Intent

- dedicated dual-wield locomotion presentation;
- foot-IK refinement;
- OffHand weapon contact support;
- prevent accidental repeated hits;
- avoid duplicate hit audio/VFX when several damage channels resolve from one contact.

## Metaworld Upgrades

- do not create a permanent second OffHand trace timer merely because Dual Wield is equipped;
- each AttackDefinition/HitWindow declares its active source weapon;
- hit identity can distinguish `Action + HitWindow + SourceWeaponItemInstanceID + Target`;
- a MainHand and a later OffHand strike may both hit the same target when intentionally authored;
- repeated samples from one physical hit window do not multiply damage;
- DamagePacket records the exact MainHand or OffHand ItemInstance responsible for contact;
- feedback deduplication is tied to committed physical contact/result identity, not one fragile global `Do Once`;
- locomotion Blend Space reads the movement resolver and cannot set gameplay speed.

### Episode 166 Principle

> Two weapons mean two possible physical damage sources, not two combat engines and not two always-running trace loops.

---

# Episode 167 — Weapon + Shield Locomotion / Combo / Root Motion

**Classification:** UPGRADE — WEAPON-SHIELD HANDLING PROFILE CONTENT.

**Phase Ownership:** Equipment + Combat Handling + Defense + Animation.

Detailed companion:

`Docs/Combat_Weapon_Handling_Animation_Profile_System.md`

## Approved Tutorial Intent

- weapon-and-shield locomotion Blend Space;
- combat-specific idle/walk/run animation;
- shield-compatible attack combo;
- Control Rig/Sequencer/root-motion cleanup;
- hit traces/rotation/combat sound notifies.

## Metaworld Upgrades

- profile resolves from exact MainHand weapon + exact OffHand shield ItemInstances;
- OffHand shield remains the canonical Guard/Block source through the Defense system;
- shield does not automatically deal damage unless an explicit shield-bash/attack definition uses it;
- `Force Root Lock` is an asset-specific locomotion correction, not a universal combat setting;
- attack root motion is authored separately from locomotion root handling;
- combo size/count is data-driven and not fixed to three attacks;
- movement speeds come from the Character Movement State Resolver.

### Episode 167 Principle

> Weapon-and-shield is one equipment-derived handling profile: the weapon attacks, the shield guards or attacks only when explicitly authored, and both remain persistent ItemInstances.

---

# Episode 168 — One-Handed Locomotion / Combo / Root Motion

**Classification:** UPGRADE — ONE-HANDED HANDLING PROFILE CONTENT.

**Phase Ownership:** Combat Handling + Animation + Combo + Hit Detection.

Detailed companion:

`Docs/Combat_Weapon_Handling_Animation_Profile_System.md`

## Approved Tutorial Intent

- one-handed idle/walk/run/sprint locomotion;
- animation pose/wrist cleanup in Sequencer;
- one-handed combo implementation;
- rate-scale tuning;
- hit-trace/audio/action notifies;
- root-motion attack movement.

## Metaworld Upgrades

- `Combat.Handling.OneHanded` is a broad family, not one universal sword move set;
- individual weapon capability/profile can select sword, axe, knife, club, hammer or other attack definitions;
- locomotion presentation reads actual resolver speed instead of treating a Blend Space axis maximum as gameplay truth;
- AttackSpeed remains bounded per attack family;
- root motion cannot bypass collision or hit validation;
- weapon contact preserves exact MainHand ItemInstance provenance.

### Episode 168 Principle

> One-handed handling is a reusable family with weapon-specific content, not a hardcoded sword-only combat mode.

---

# Part 18 Consolidation

Episodes 165–168 strengthen one shared rule:

`Authoritative Equipment ItemInstances`
-> `HandlingProfileID`
-> `Combat Locomotion / Attack Definitions / Guard Profile`
-> `CombatActionInstance`
-> `Source-specific Hit Window`
-> `Validated Contact`
-> `DamagePacket`
-> `Feedback`.

Dual Wield, Weapon+Shield and One-Handed use the same Combat, Damage, Movement and Feedback services.

## Current Playlist Count

**168 unique Modern RPG tutorial episodes reviewed.**

## Next Intake

The next unique tutorial should be recorded as **Episode 169**.