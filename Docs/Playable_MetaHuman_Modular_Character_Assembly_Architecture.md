# Metaworld — Playable MetaHuman / Modular Character Assembly Architecture

**Status:** Canonical / Approved Modern RPG Playlist Upgrade

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first

## Canonical Principle

Metaworld may use MetaHuman technology and modular skeletal body parts as a high-quality humanoid implementation path, but the playable character still obeys the existing `BP_MW_Character_Master`, morph-customization, animation, controller, networking and performance contracts.

> The avatar assembly method serves Metaworld's character system; it does not replace the character system.

Related canonical documents:

- `Docs/Character_Morph_Customization_System.md`
- `Docs/Avatar_Communication_Character_Animation_Architecture.md`
- `Docs/Blueprint_Python_Nanite_Architecture.md`
- `Docs/Performance_Smoothness_FrameTime_Architecture.md`

---

# 1. UE5.8 MetaHuman Direction

The UE5.4 tutorial's manual copying of Face/Torso/Legs/Feet components is retained as a useful explanation of modular character composition, but it is not the only canonical import/assembly workflow.

For UE5.8:

- use MetaHuman Character assets and the matching UE5.8 assembly pipeline where appropriate;
- do not assume assets assembled for an older engine version are the final shipping setup;
- keep experimental MetaHuman Collection/Instance/Crowd workflows behind explicit evaluation until proven suitable for production;
- MetaHuman-specific assembly remains an implementation layer under the Metaworld avatar contract.

---

# 2. Master Character Integration

Playable humanoids still derive from or integrate through:

`BP_MW_Character_Master`

The master retains shared gameplay components such as:

- `BPC_MW_AvatarCustomization`
- inventory/equipment
- interaction
- vitals/needs
- combat
- skills/professions
- reputation
- communication
- ownership/evidence identity
- networking/persistence hooks

A MetaHuman Blueprint is not allowed to become a separate parallel player-character architecture.

Recommended pattern:

`BP_MW_Character_Master`
-> avatar/mesh assembly contract
-> Body / Face / Torso / Legs / Feet / Hair / clothing components as required
-> `ABP_MW_Master` / linked animation layers
-> avatar customization/equipment systems

---

# 3. Modular Pose Strategy

`Set Leader Pose Component` is an approved method for compatible modular skeletal sections that share the required bone hierarchy.

Use it when:

- child sections should follow one leader animation;
- child sections do not require independent animation/physics;
- profiling shows the render cost is acceptable for the target character significance tier.

Do not assume Leader Pose is automatically the cheapest complete solution. Multiple skeletal components still create separate rendering work.

Where a part needs independent post-processing, physics or special animation, evaluate a more appropriate method such as Copy Pose / post-process animation rather than forcing every part into the same Leader Pose rule.

Do not adopt runtime Skeletal Mesh Merge as the default player-avatar solution if it removes morph-target functionality required by Metaworld's creator.

---

# 4. Animation Contract

Tutorial-specific `ABP_Manny` / `ABP_Quinn` assignments are prototype examples only.

Metaworld uses the canonical animation architecture:

- `ABP_MW_Master`
- Motion Matching / Pose Search where appropriate
- Linked Animation Layers
- IK Rig / IK Retargeter
- Motion Warping
- Control Rig where appropriate
- Animation Budget Allocator

Body animation drives compatible MetaHuman body parts through the approved assembly setup.

Face animation remains compatible with MetaHuman facial animation/post-processing where used.

Asset-specific Control Rig/root fixes must be documented as content fixes, not copied as universal character rules.

---

# 5. Morph / Character Creator Protection

Metaworld's broad body/face customization remains mandatory.

A MetaHuman implementation must not reduce the approved creator to a few fixed body presets.

`BPC_MW_AvatarCustomization` remains the authoritative compact customization profile and may drive:

- supported body/face morph targets;
- material/skin parameters;
- hair/color options;
- age presentation;
- clothing corrective morphs;
- compatible skeleton/IK adjustment profiles.

If a MetaHuman pipeline cannot support a required identity range directly, Metaworld may extend/customize the pipeline or use another compatible skeletal implementation for the player while still using MetaHuman technology elsewhere.

Player identity correctness has priority over forcing one character technology everywhere.

---

# 6. Hair / Groom / LOD

The tutorial's `Forced LOD = 0` can be used as a diagnostic to identify a bad LOD transition, but it is rejected as a universal shipping fix.

Permanent policy:

- investigate the actual groom/LOD/material/visibility issue;
- use appropriate LODSync/groom/scalability configuration;
- preserve high fidelity for the local player where budget permits;
- reduce distant/non-critical character cost;
- never force every MetaHuman hair asset to maximum LOD merely to hide one flicker.

Character LOD policy participates in Metaworld's significance/performance architecture.

---

# 7. Clothing / Hidden Starter Pieces

Hiding tutorial starter clothing such as flip-flops is acceptable during setup, but shipping equipment uses the canonical equipment/clothing system.

Clothing visibility should ultimately be driven by:

- equipment slot state;
- body coverage/hide rules;
- morph-fitting/corrective data;
- outfit/uniform/armor definition;
- damage/wet/dirty state later;
- replication/persistence.

Do not leave one-off viewport visibility edits as the final equipment architecture.

---

# 8. Nanite Direction

Use Nanite on compatible character parts/accessories where Unreal Engine 5.8 support and profiling make it beneficial.

Do not force Nanite onto morph-dependent meshes when required deformation is unsupported or incorrect.

Each part is evaluated separately:

- body/face
- clothing
- armor
- shoes
- accessories
- hair/grooms

Gameplay, morphs and visual correctness beat a blanket Nanite checkbox.

---

# 9. Multiplayer / Persistence

Avatar assembly is presentation derived from authoritative identity/customization/equipment data.

Persist/replicate compact data such as:

- Character ID
- avatar profile ID/version
- morph/customization parameters
- equipped ItemInstance IDs / equipment definitions
- hair/material IDs
- lineage/body compatibility profile

Do not replicate full skeletal vertex data or rebuild the character from client-trusted asset choices.

The server validates legal/owned equipment and persistent identity state; clients assemble the visual representation from approved data.

---

# 10. Performance Tests

The vertical slice must profile:

- one local high-fidelity player avatar;
- several nearby customized players/NPCs;
- many distant modular characters;
- separate component/draw-call cost;
- groom cost;
- animation budget behavior;
- morph/equipment changes;
- multiplayer avatar reconstruction;
- character streaming/LOD transitions without flicker.

Leader Pose, Copy Pose and other assembly approaches are selected by measured use case, not tutorial habit.

---

# Core Rule

> MetaHuman is a character technology inside Metaworld, not Metaworld's identity architecture. The master character, morph-driven customization, equipment, animation, persistence and performance rules remain authoritative.