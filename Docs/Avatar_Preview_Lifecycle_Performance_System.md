# Metaworld — Avatar Preview Lifecycle & Performance System

**Status:** Canonical / Approved Performance Upgrade

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first / local-presentation-only / performance-budgeted

## Canonical Principle

The inventory/equipment avatar preview exists only to serve visible UI presentation. When the preview is not visible, it must not continue expensive rendering, animation, groom, cloth or capture work.

> No hidden always-rendering character preview is allowed. Destroy, pool or fully dormancy-disable it according to measured performance and lifecycle reliability.

Related canon:

- `Docs/Inventory_Equipment_UI_Preview_Tooltip_Rarity_Interaction_Prompt_Architecture.md`
- `Docs/Performance_Smoothness_FrameTime_Architecture.md`
- `Docs/Equipment_Armor_Weapon_Attachment_Avatar_Fitting_Architecture.md`

---

# 1. Approved Lifecycle Strategies

Metaworld may use one of these implementations after profiling:

## Spawn On Open / Destroy On Close

- create `BP_MW_AvatarPreviewActor` when a preview-bearing menu opens;
- apply current AvatarCustomization + Equipment presentation snapshot;
- enable SceneCapture/animation only while needed;
- on close, release attached presentation objects/resources and destroy the preview actor cleanly.

Advantages can include eliminating all hidden actor/capture cost.

## Pool / Dormant Reuse

- create or retain one local preview actor;
- when hidden, SceneCapture stops entirely;
- expensive animation/groom/cloth/preview effects stop;
- actor is hidden/disabled and consumes negligible work;
- reactivate and refresh from current authoritative snapshot on reopen.

Advantages can include reducing spawn/asset setup churn.

Neither strategy is universally mandated. Profile both on target hardware and choose the lower-cost, more reliable result.

---

# 2. No Guaranteed FPS Claim

A tutorial reporting an approximately 20 FPS improvement after removing an always-active preview actor demonstrates that constant preview rendering can be expensive in that project.

Metaworld does **not** record `+20 FPS` as an expected performance gain.

Measure with Metaworld's actual:

- avatar complexity;
- MetaHuman/groom settings;
- equipment component count;
- SceneCapture resolution/rate;
- preview lighting;
- UI resolution;
- hardware/scalability profile.

The canonical requirement is measurable frame-time improvement/no hidden cost, not a fixed FPS number.

---

# 3. Preview Is Reconstructed From Authoritative Presentation State

On activation/open:

`Current CharacterID`
+
`AvatarCustomizationSnapshot`
+
`EquipmentSnapshot`
-> `BP_MW_AvatarPreviewActor`

The preview does not need to remain alive to preserve equipment.

Equipment state is already authoritative elsewhere.

Destroying the preview actor therefore never unequips/destroys real items.

On recreation, the preview re-resolves:

- body/face profile;
- morph/customization values;
- hair/groom presentation;
- equipped ItemInstance presentation assets;
- body/hair coverage;
- current preview animation profile.

---

# 4. Attached Preview Equipment

Preview weapon/armor Actors/components are presentation-only representations of real ItemInstanceIDs.

When preview closes/destroys:

- remove/release preview-only attachment Actors/components;
- do not call gameplay Unequip;
- do not mutate ItemInstance container/equipment ownership;
- do not create persistent world drops.

When preview reopens, reconstruct from EquipmentSnapshot.

---

# 5. Safe References

Gameplay/inventory/equipment functions must not assume a preview actor always exists.

Preferred architecture:

- preview controller/view owns optional valid reference;
- presentation update events check whether preview is active;
- if inactive, authoritative gameplay still completes normally;
- on next activation, preview rebuilds from current snapshot.

Do not make Item Use / Equip / Remove success depend on a valid preview actor.

Validated references are useful defensively, but system ownership should already separate gameplay from optional preview presentation.

---

# 6. SceneCapture Policy

SceneCapture Component 2D is enabled only while required.

Possible modes:

- capture once on open for static preview;
- capture on equipment/avatar change;
- bounded/capped capture rate for animated preview;
- pause capture when preview is occluded/another tab is active;
- disable capture before preview close/dormancy/destruction.

Do not run an invisible SceneCapture every frame behind gameplay.

---

# 7. Groom / Cloth / Physics

Preview fidelity may differ from gameplay avatar fidelity.

Possible preview policy:

- disable expensive hair physics;
- disable/reduce cloth simulation where unnecessary;
- use preview-safe animation;
- lower fidelity/capture resolution on lower scalability levels;
- use simplified accessory physics;
- stop all simulation when hidden.

The preview's purpose is readable appearance/equipment inspection, not a second full-fidelity world simulation.

---

# 8. Soft Asset Loading / Open Latency

Spawn-on-open can trade runtime cost for menu-open asset/setup latency.

Mitigations may include:

- soft references + async prefetch for current avatar/equipment;
- retained lightweight presentation caches;
- pooling where profiling proves superior;
- temporary placeholder/loading presentation rather than blocking the game thread.

Do not solve hidden-render cost by causing unacceptable synchronous hitching on every inventory open.

---

# 9. Lifecycle Events

Suggested UI flow:

`Open Player Interface`
-> determine whether visible tab needs avatar preview
-> Activate/Create Preview
-> apply snapshot
-> enable bounded capture

`Switch to tab without preview`
-> Suspend/Release Preview according to policy

`Equipment/Avatar change while visible`
-> refresh only affected presentation

`Close Interface`
-> stop capture/simulation first
-> release/destroy/dormancy-disable preview
-> clear local references safely.

---

# 10. Multiplayer / Authority

Preview actor is local-only presentation.

It does not:

- replicate as another character;
- own ItemInstances;
- affect world collision;
- participate in combat;
- consume real ammunition;
- alter NPC/world AI;
- own currency/needs/stats.

Its creation/destruction has no authoritative gameplay consequence.

---

# 11. Performance Acceptance Tests

1. Closing inventory leaves no active SceneCapture for the avatar preview.
2. Hidden preview performs no groom/cloth/animation work beyond explicitly measured negligible lifecycle overhead.
3. Destroying preview cannot unequip or delete real equipment.
4. Reopening reconstructs exact current avatar/equipment state.
5. Equipment changed while preview is inactive appears correctly on next open.
6. Gameplay Equip/Use functions succeed when preview actor does not exist.
7. No orphan preview equipment Actors remain after close/destroy.
8. Spawn-on-open does not introduce unacceptable frame hitch; if it does, pooling/async strategy is evaluated.
9. Pool/dormant strategy, if selected, demonstrates negligible hidden frame-time cost.
10. Animated capture uses a bounded/quality-scaled rate rather than an unnecessary unlimited hidden render.
11. No fixed `+20 FPS` assumption is used for performance budgeting; measured frame time decides.

## Core Rule

> The avatar preview is disposable local UI presentation. Keep it only while it earns its frame-time cost, rebuild it from authoritative avatar/equipment state whenever needed, and never let hidden SceneCapture or character simulation tax normal gameplay.