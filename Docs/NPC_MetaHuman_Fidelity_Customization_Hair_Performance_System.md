# Metaworld — NPC MetaHuman Fidelity, Customization, Hair & Performance System

**Status:** Canonical / Approved Modern RPG Playlist Upgrade

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first / data-driven / significance-scaled / performance-budgeted

## Canonical Principle

NPC visual fidelity scales with significance, distance, platform and performance budget. Metaworld may use high-fidelity MetaHuman presentation for important nearby characters while reducing texture, hair, simulation and component cost for less significant NPCs.

> NPC identity should remain recognizable as fidelity changes, but no ordinary background NPC is entitled to full player-character rendering cost at all times.

Related canon:

- `Docs/Playable_MetaHuman_Modular_Character_Assembly_Architecture.md`
- `Docs/Equipment_Armor_Weapon_Attachment_Avatar_Fitting_Architecture.md`
- `Docs/Performance_Smoothness_FrameTime_Architecture.md`
- `Docs/Character_Morph_Customization_System.md`

---

# 1. NPC Fidelity Profiles

Recommended stable profile:

`NPCFidelityProfileID`

Possible tiers:

- Hero / Story Critical;
- Nearby Interactive;
- Normal Crowd;
- Distant Crowd;
- Background / Simulated Only.

Profile may define:

- MetaHuman quality assembly/profile;
- texture maximums/streaming bias;
- skeletal mesh LOD policy;
- facial animation quality;
- groom strands/cards/mesh policy;
- hair simulation/interpolation policy;
- cloth/accessory simulation;
- material quality;
- animation update rate/budget;
- shadow policy;
- equipment presentation detail;
- significance distance thresholds.

Do not hardcode one tutorial value such as `Max Texture Size = 256` or `Min LOD = 4` for every NPC.

---

# 2. Texture Policy

Texture reduction is approved for NPC scalability, but authored values depend on:

- screen size;
- character significance;
- material region;
- platform memory budget;
- camera use/cinematics;
- skin/hair/equipment importance.

Use Unreal texture streaming/scalability/device profiles and asset-specific maxima where appropriate.

A 256 px limit may be acceptable for some distant/background assets but is not universal for all faces, clothing or hero NPCs.

---

# 3. MetaHuman LODSync

UE5.8 MetaHumans use LODSync to coordinate LODs across face/body/hair and related components.

Metaworld should configure LODSync/fidelity profiles intentionally rather than manually forcing unrelated components to inconsistent LODs.

Rules:

- avoid permanent Forced LOD for all contexts unless a specific profile needs it;
- choose Min LOD/quality based on significance/platform;
- allow normal screen-size transitions where practical;
- test face/body/hair continuity across transitions;
- profile component count and animation/deformer cost.

---

# 4. Hair Technology Profiles

NPC hair can use multiple presentation technologies.

## Groom Strands

Best for close/high-fidelity characters where budget permits.

Possible optimization:

- curve/point decimation;
- Auto LOD bias;
- reduced/no simulation;
- rigid binding where visual quality permits;
- controlled shadow/interpolation settings;
- significance-based activation.

## Groom Cards / Meshes

Approved for medium/lower fidelity NPCs where they preserve appearance with much lower cost.

## Static/Skeletal Mesh Hair

Approved for performant background characters or styles authored for mesh presentation.

Attach through semantic head/hair socket/profile and use normal LOD/material rules.

Do not assume a static mesh is automatically correct for every hairstyle; silhouette, deformation and animation must be validated.

---

# 5. Hair Data / Color Customization

Stable hair presentation definitions may include:

- HairStyleID;
- groom asset + binding;
- card/mesh fallback;
- compatible head/body profile;
- color/material profile;
- LOD/fidelity availability;
- attachment/socket rules;
- simulation profile.

A Data Table/Data Asset is approved for Blueprint-first authoring.

NPC appearance records should reference HairStyleID + color/profile rather than manually setting every component in each NPC Blueprint.

Material Instances are approved for color variants.

Do not run material reassignment loops every frame; apply when appearance/fidelity changes.

---

# 6. NPC Appearance Record

Suggested conceptual record:

`S_MW_NPCAppearance`

Possible fields:

- NPC CharacterID;
- face/body identity/profile;
- skin/body presentation;
- HairStyleID / hair color;
- base outfit/equipment ItemInstanceIDs or appearance definitions;
- helmet/headwear;
- morph/body parameters where NPC creator supports them;
- FidelityProfileID override where required;
- cosmetic variation seed/reference.

The NPC Blueprint resolves presentation from data. It does not make every mesh field independently authoritative.

---

# 7. NPC Armor / Clothing

NPC clothing/equipment should use the same approved fitting paths as players where practical:

- fixed skeletal armor;
- parametric/resizable MetaHuman Outfit Assets where suitable;
- rigid helmet/accessory sockets;
- body/hair coverage rules;
- equipment presentation profiles.

A one-piece armor set is allowed for content/performance reasons, but it is a presentation/composition choice. If gameplay needs separate chest/legs/gloves/boots ItemInstances, a fused visual mesh must still represent the underlying authoritative equipment composition correctly.

---

# 8. Construction Script Use

Construction Script is useful for editor-time preview/configuration of NPC appearance.

Runtime rules:

- expensive appearance rebuilding should occur only on initialization/appearance change/fidelity transition;
- do not repeatedly rebuild modular meshes every frame;
- persistent gameplay equipment/state remains separate from editor preview variables;
- runtime spawned NPCs resolve appearance through the same data-driven assembly function/service.

---

# 9. Significance / NPC Simulation Integration

Visual fidelity should align with NPC simulation fidelity.

Example:

Hero Nearby:
- full face/body animation;
- high-quality hair;
- full equipment presentation.

Normal Nearby:
- standard animation;
- reduced groom/cards;
- normal equipment.

Distant:
- lower LOD/material quality;
- reduced animation update;
- card/mesh hair;
- simplified accessories.

Unloaded:
- no visual Actor; persistent NPC state exists as data.

Do not keep full MetaHuman Actors active for NPCs outside streaming/significance needs.

---

# 10. Hair Physics

Hair physics/simulation is not universally enabled for NPCs.

Possible profile policies:

- Hero: enabled where budget permits;
- Nearby: limited/reduced;
- Crowd: disabled/cards/mesh;
- Distant: no simulation.

Disabling simulation can save cost, but exact visual result depends on groom/binding/interpolation settings and must be tested.

---

# 11. Two-Sided Hair Materials

Two-Sided may be appropriate for some card/mesh hair assets when backfaces must render, but it is not an automatic fix for every transparency problem.

Validate:

- geometry normals;
- material blend/masking;
- shadowing;
- overdraw;
- backface requirement;
- performance cost.

---

# 12. Player vs NPC Fidelity

Player characters and important close NPCs can use different fidelity budgets.

The same identity/appearance architecture may feed both, but background NPC optimization must never silently downgrade the local player's approved customization or morph range.

---

# 13. Performance Measurement

Profile with actual Metaworld scenes and target hardware.

Measure:

- GPU frame time;
- game/render thread cost;
- MetaHuman component count;
- groom passes/interpolation/simulation;
- texture memory/streaming;
- animation/deformer cost;
- shadows;
- nearby NPC density.

Do not lock tutorial-reported FPS gains or visual-loss claims as universal truth.

---

# 14. Editor/Python Validation

Future tooling can audit:

- missing HairStyleIDs/bindings;
- invalid fallback assets;
- NPCs forced to inappropriate LODs;
- high-cost grooms assigned to crowd profiles;
- unexpected hair simulation;
- oversized textures for background profiles;
- missing card/mesh fallback;
- armor skeleton incompatibility;
- socket/attachment issues;
- material Two-Sided usage;
- appearance definitions missing required assets.

---

# 15. Acceptance Tests

1. Important close NPC retains intended appearance at high fidelity.
2. Background NPC profile reduces cost without breaking identity/silhouette unacceptably.
3. LODSync transitions face/body/hair coherently.
4. No universal 256 texture/MinLOD4 rule is applied blindly.
5. Groom simulation disables according to profile.
6. Hair cards/mesh fallback works where configured.
7. Hair color changes through data/material profile without per-frame work.
8. NPC armor follows current appearance/equipment state.
9. Runtime appearance change does not rebuild continuously.
10. Unloaded NPC exists as persistent data without visual MetaHuman cost.
11. Fidelity transitions do not alter NPC gameplay identity/inventory.
12. Target NPC crowd remains inside Metaworld frame-time budget.

## Core Rule

> Metaworld treats MetaHuman fidelity as a scalable presentation budget. Important characters can look exceptional up close, while ordinary NPCs use coordinated LOD, hair, texture and simulation profiles so a living population never destroys frame time.