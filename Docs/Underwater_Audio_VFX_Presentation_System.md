# Metaworld — Underwater Audio, VFX & Environmental Presentation System

**Status:** Canonical / Approved Modern RPG Playlist Upgrade

**Engine:** Unreal Engine 5.8

**Extends:** `Docs/Swimming_Water_Breath_Drowning_Survival_System.md`

## Canonical Principle

Underwater audio and visual effects present the current environment state; they do not determine whether the character is swimming, submerged or drowning.

> The environment resolver says the airway/camera is underwater. Audio, Niagara and post-process systems make that state feel underwater.

---

# 1. Presentation Inputs

Underwater presentation may consume:

- ActiveWaterBodyID;
- camera/head submerged state;
- water depth;
- surface proximity;
- current/flow intensity;
- environment biome/profile;
- weather/time-of-day;
- character state;
- accessibility/audio settings.

Do not create an unrelated `IsUnderwaterAudio` Boolean that can become stale after ladder/ledge/teleport transitions.

---

# 2. Audio State

When the listener/camera becomes legitimately submerged:

- activate underwater ambience/loop according to water profile;
- apply an underwater audio mix/filter to appropriate external sound classes;
- preserve critical UI/accessibility/emergency audio according to policy;
- transition smoothly rather than hard-cut where possible.

On surfacing:

- remove/reverse the underwater mix;
- stop/fade underwater ambience;
- restore normal world audio.

The audio mix is local presentation and never controls Breath/drowning.

---

# 3. Water-Type Profiles

Different water can sound/look different:

- lake;
- river;
- ocean;
- pool;
- sewer;
- cave water;
- polluted/toxic water;
- supernatural water where later designed.

A presentation profile can choose:

- ambience;
- filtering;
- bubble density;
- suspended particles;
- fish/fauna presentation;
- color/post-process;
- caustics/fog policy;
- splash/entry/exit effects.

---

# 4. Niagara / Environmental VFX

Approved presentation includes:

- bubbles;
- fish/fauna schools;
- sediment/particulates;
- entry/exit splashes;
- wake/trail effects;
- underwater disturbance effects.

Rules:

- Niagara systems are significance/scalability controlled;
- do not spawn expensive fish/bubble systems everywhere merely because water exists;
- local player/nearby camera can receive richer effects;
- distant/unseen water uses reduced/no presentation cost.

---

# 5. Breath Balance Is Gameplay Data

Tutorial values such as a Breath drain rate of `0.05` are prototype tuning only.

Final Breath behavior remains owned by the survival resource definition and may depend on:

- EffectiveMaxBreath;
- drain cadence;
- skill/fitness;
- equipment;
- conditions;
- supernatural state;
- exertion;
- water/environment hazards.

Audio/VFX cannot alter Breath merely because an underwater effect is active.

---

# 6. Water Body Reuse / Authoring

Water bodies may share presentation components/profiles while retaining their own valid Water-system configuration.

Do not assume duplicating every Water actor subtype preserves all functional behavior automatically.

Authoring validation should confirm:

- correct water body/profile type;
- gameplay water query works;
- physics/swim volume behavior is valid;
- presentation profile is assigned;
- entry/exit effects are bounded;
- collision/nav/traversal integration remains correct.

---

# 7. Transitions

Underwater presentation must handle:

- walking into deep water;
- diving below surface;
- surfacing;
- climbing a ladder from water;
- mantling onto shore;
- entering/exiting a boat;
- teleport/respawn;
- camera switching if supported.

Every transition re-resolves current environment truth instead of relying on the prior presentation state.

---

# 8. Performance

- audio loops exist only while needed;
- sound mixes are toggled from state changes, not polled every frame;
- Niagara uses Effect Types/scalability/culling where appropriate;
- fish are presentation agents, not automatically full persistent NPCs unless a gameplay system requires it;
- underwater post-process complexity scales with quality settings;
- no global scan of every water body for local visual effects.

---

# 9. Accessibility

Allow settings where practical for:

- underwater audio intensity;
- reduced visual particles;
- reduced motion/distortion;
- subtitles/critical sound cues unaffected by heavy filtering where needed;
- high-contrast Breath/drowning feedback.

---

# Acceptance Tests

1. Submerging activates underwater presentation only when current environment state says submerged.
2. Surfacing removes underwater presentation cleanly.
3. Ladder exit from water cannot leave muffled audio active on land.
4. Breath logic works even if underwater audio/VFX are disabled.
5. Audio filtering does not hide critical UI/accessibility feedback unintentionally.
6. Niagara effects scale/cull without changing swim gameplay.
7. Different water profiles can use different ambience/VFX.
8. Teleport/respawn reconciles presentation with actual water state.

## Core Rule

> Underwater sound, bubbles, fish and visual treatment are presentation layers over the canonical water-contact state. They make submersion believable without becoming another source of swim or Breath truth.