# Metaworld — Combat Feedback, Audio, Blood & VFX System

**Status:** Canonical / Approved Modern RPG Playlist Upgrade

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first / event-driven / authoritative-result-driven / scalable presentation

## Canonical Principle

Combat audio, blood, decals, camera effects and weapon trails present committed combat state; they do not decide whether an attack hit or how much damage occurred.

> Combat produces an authoritative result first. Presentation then selects the correct sound, blood/VFX, decal, camera feedback and UI response for that result.

Related canon:

- `Docs/Combat_Hit_Detection_Damage_Resistance_Feedback_System.md`
- `Docs/Combat_Action_Gameplay_Tag_State_System.md`
- `Docs/Equipment_Armor_Weapon_Attachment_Avatar_Fitting_Architecture.md`
- `Docs/Performance_Smoothness_FrameTime_Architecture.md`

---

# 1. Combat Feedback Event

Recommended conceptual event/snapshot:

`S_MW_CombatFeedbackEvent`

Possible fields:

- DamageEventID / CombatActionInstanceID;
- source CharacterID;
- target CharacterID / WorldObjectID;
- WeaponItemInstanceID / handling profile;
- hit body zone / bone mapping;
- surface/material response profile;
- blocked/parried/absorbed/damaged result;
- committed damage amount where authorized;
- damage-channel tags;
- hit location/normal;
- local-player relevance;
- presentation priority.

Feedback consumers never mutate the authoritative damage result.

---

# 2. Weapon Swing / Whoosh Audio

Animation Notifies may request authored swing/weapon-motion sounds during expected attack phases.

Sound selection can derive from:

- weapon handling/profile;
- weapon material/size;
- attack definition;
- actual action playback rate;
- character strength/effort profile where useful.

Small bounded pitch/volume variation is approved for naturalness.

Do not tie pitch directly and unboundedly to arbitrary Attack Speed values; use a clamped audio mapping so extreme stats do not create unusable sound.

A swing sound is presentation of motion and does not imply a hit.

---

# 3. Hit / Impact Audio

Impact audio triggers from the committed/validated hit result and can distinguish:

- flesh/body impact;
- metal armor;
- wood shield;
- stone/world object;
- glass;
- supernatural/material responses;
- blocked/parried hits.

Use semantic impact/surface profiles instead of one universal `FleshHit` sound.

Avoid duplicate sound spam when one hit contains several damage channels. One contact event may produce one primary impact sound plus specifically-authored secondary layers where justified.

---

# 4. Swing Sound Interruption

The tutorial's goal of reducing overlapping swoosh/hit clutter is approved, but do not assume every hit must hard-stop every swing sound.

Audio profile can define:

- continue;
- duck/fade;
- stop on impact;
- transition to impact tail.

This is sound design, not combat authority.

---

# 5. Blood / Biological Hit VFX

Blood VFX are generated only for targets/materials whose anatomy/content profile permits blood.

Possible responses:

- blood burst;
- mist/spray;
- wound/gash decal;
- clothing/armor blood presentation later;
- surface splatter later;
- no blood for robots/objects/non-blood anatomy.

Damage type, body zone, armor coverage and content/accessibility settings may change the effect.

---

# 6. Wound / Gash Decals

Attached decals may follow a semantic body/bone attachment derived from the hit result.

Rules:

- decal is presentation, not persistent injury truth;
- target mesh/material must explicitly allow the decal;
- weapons/equipment can opt out where inappropriate;
- fade/lifetime is bounded;
- decal count per character is capped/pooled/merged according to performance profile;
- distant/crowd characters may use reduced/no wound decals.

Persistent wounds/scars, if later designed, belong to injury/avatar persistence and are not the same thing as a temporary combat decal.

---

# 7. Niagara / Weapon Trails / Sparks

Approved effects include:

- blood bursts;
- metal/wood block sparks/debris;
- weapon trails;
- parry flashes;
- impact particles;
- magic/supernatural combat effects later.

Effects use Niagara scalability/significance policies and should not spawn unlimited expensive systems in large fights.

---

# 8. Camera Shake / Haptics

Camera shake and controller haptics can react to:

- successful heavy hit;
- block;
- guard break;
- parry;
- explosion/large impact.

Rules:

- local presentation only;
- magnitude derives from a feedback profile, not raw damage alone;
- accessibility allows reduced/disabled shake/haptics;
- do not stack unlimited shakes from one multi-channel damage event.

---

# 9. Slow Motion / Time Effects

Global time dilation is not a default combat-feedback tool in persistent multiplayer Metaworld.

If dramatic slow-motion is later used, prefer:

- local camera/presentation effects;
- animation/playback emphasis;
- controlled instanced/single-player contexts;
- server-approved special mechanics that do not globally freeze unrelated players/world systems.

Tutorial-specific global slow motion must never become an automatic multiplayer parry effect.

---

# 10. Performance

- no permanent combat-audio/VFX Tick;
- trigger from action/result events;
- pool/reuse widgets/effects where beneficial;
- cap wound decals/particle density;
- distance/significance controls for NPC combat presentation;
- use soft references/profile assets where practical;
- do not spawn redundant identical feedback for multiple damage channels from one contact.

---

# 11. Acceptance Tests

1. Swing sound can play without creating damage.
2. One committed hit produces one correct primary impact response.
3. Blocked hit selects block material feedback rather than flesh feedback where appropriate.
4. One physical hit with Physical+Poison does not double-play the same hit sound.
5. Blood never appears on non-blood targets unless their anatomy profile says so.
6. Temporary wound decals cannot delete/damage the target Actor.
7. Weapon meshes can reject inappropriate blood decals.
8. Distant NPC combat scales presentation cost down.
9. Camera shake can be reduced/disabled without changing combat.
10. Global world time is not slowed by an ordinary multiplayer parry feedback event.

## Core Rule

> Metaworld combat feedback follows authoritative combat results. Audio, blood, decals, Niagara, camera shake and haptics make contact readable and satisfying while remaining bounded, scalable and completely separate from hit/damage authority.