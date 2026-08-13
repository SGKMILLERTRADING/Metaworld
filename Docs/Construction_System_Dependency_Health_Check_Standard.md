# Metaworld — Construction System Dependency & Health-Check Standard

**Status:** Canonical / Approved Playlist Tooling & QA Upgrade

**Engine Direction:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first

## Canonical Principle

Metaworld is **not** being migrated to another project. This standard extracts the useful engineering lesson from a UE4 migration tutorial: a large construction system must make its project-level dependencies explicit, testable, recoverable and auditable so hidden settings do not silently break gameplay.

Core rule:

> Construction dependencies must be declared and validated as part of the project, not remembered as a list of manual editor fixes.

The tutorial's project-migration steps are therefore not adopted as a current Metaworld task. The useful ideas are converted into dependency hygiene, editor recovery procedures, automated audits and a repeatable construction-system health check.

---

# 1. Classification

**Playlist classification:** RESEARCH / TOOLING UPGRADE — APPROVED

This episode does **not** add a new gameplay mechanic and does **not** move Metaworld to another Unreal project.

It contributes:

- dependency inventory;
- project-settings hygiene;
- Blueprint recovery/validation procedures;
- input/UI integration checks;
- collision/query-profile validation;
- plugin/feature validation;
- automated Editor/Python audits;
- construction-system smoke tests.

---

# 2. Plugin / Engine Feature Dependencies

Any engine feature that construction relies on must be explicitly documented and validated.

Examples can include:

- Enhanced Input;
- Chaos / Geometry Collection tooling when destruction content uses it;
- relevant Editor scripting/Python tooling;
- UI framework features used by build menus;
- World Partition/HLOD/Nanite-related project features where applicable.

The tutorial's requirement to enable **APEX Destruction** is **not** adopted for new Metaworld content. Episode 16 already established that new destruction content uses the approved UE5.8 Chaos/Geometry Collection path when real-time fracture is justified.

A plugin dependency must never exist only as tribal knowledge such as:

`"remember to enable this or the Blueprint breaks"`.

It belongs in the documented project dependency list and health-check tooling.

---

# 3. Construction Dependency Manifest

Maintain a human-readable construction dependency manifest covering at least:

## Blueprint Architecture

- `BP_MW_Buildable_Master`
- `BPC_MW_BuildComponent`
- `BP_MW_Character_Master` integration
- `BPI_MW_BuildSnapProvider`
- `BPI_MW_Interactable`
- `BPI_MW_Damageable` where used
- structural relationship interfaces/components/services
- construction progress/demolition/relocation components or services

## Data

- Buildable Definitions
- Family/Variant IDs
- Data Tables / Primary Data Assets
- construction recipes
- placement footprints
- support sample definitions
- opening/attachment definitions
- damage/destruction profiles
- relocation/demolition policies
- persistence version/schema references

## Input

- build-mode Mapping Context
- interaction Mapping Context
- move/rotate/confirm/cancel actions
- demolition/remove action
- keyboard/mouse mappings
- Xbox-style mappings
- PlayStation-style mappings

## Collision / Query

- general Build Placement/Obstruction profile/channel
- general Build Snap/Acquisition profile/channel where required
- gameplay collision profiles
- query-only snap/opening volumes
- simple collision requirements
- destroyed/breached collision states

## UI

- Build Catalog
- ghost valid/blocked feedback
- construction progress UI
- removal/demolition hold-progress UI
- blocked-reason display
- controller focus/navigation
- contextual input prompts

## Persistence / Multiplayer

- stable Structure/Object IDs
- relationship IDs
- opening/snap occupancy
- construction progress state
- damage/destruction state
- relocation/demolition transaction state where persisted
- authoritative server validation contracts

---

# 4. Project Settings Must Not Be Hidden Manual Knowledge

The tutorial manually recreates trace channels after migration. Metaworld should minimize that failure mode.

Canonical rule:

> Project-level construction settings must be reproducible from version-controlled configuration, canonical setup instructions, data, or tooling wherever Unreal permits.

We do not maintain a growing list such as:

- `FoundationTrace`
- `WallTrace`
- `DoorTrace`
- `WindowTrace`
- `FloorTrace`
- one new global channel for every future buildable family.

Existing Phase 20 canon remains:

- use a small general construction query family;
- determine semantic compatibility through stable IDs, Gameplay Tags and data;
- use dedicated global channels only when genuinely justified.

A health check should detect missing or unexpected construction collision/query profiles before gameplay testing.

---

# 5. Collision Validation

The tutorial correctly highlights that migrated assets can appear broken when their collision assumptions differ.

Metaworld validation should check:

- required simple collision exists where needed;
- placement footprints exist and align with the asset;
- query-only snap/opening volumes have expected responses;
- gameplay collision is separate from snap acquisition;
- unfinished construction uses stage-appropriate collision;
- doorway/window openings are not blocked by hidden collision;
- destroyed/breached states apply correct collision;
- no buildable relies accidentally on unrelated `Visibility` behavior;
- custom collision responses match the canonical small query-profile design.

Complex/per-poly collision should not silently become construction-placement truth unless deliberately approved for a specific use.

---

# 6. Blueprint Recovery: Refresh Nodes Is a Tool, Not Architecture

The tutorial uses `Refresh All Nodes` to repair broken Blueprint connections after migration.

That is retained as a useful **recovery/debugging procedure**, but not as normal runtime architecture.

Recommended recovery sequence when a Blueprint becomes stale after engine/data/signature changes:

1. identify the missing/changed dependency;
2. restore/fix the dependency first;
3. Refresh Nodes / Refresh All Nodes where appropriate;
4. compile the affected Blueprint;
5. inspect warnings/errors;
6. test parent-function calls and interfaces;
7. test derived child Blueprints;
8. run the construction smoke test.

Do not treat `Refresh All Nodes` as proof that the feature is correct. It only repairs/reconstructs node connections where Unreal can resolve them.

---

# 7. Character Integration Must Stay Modular

The tutorial copies build logic from one ThirdPersonCharacter into another.

Metaworld rejects character-graph copy/paste as the permanent pattern.

Canonical architecture remains:

`BP_MW_Character_Master`
+ `BPC_MW_BuildComponent`
+ `BPC_MW_Interaction`
+ Enhanced Input Mapping Contexts

The character owns/hosts the reusable components and high-level input routing; construction logic stays inside the appropriate reusable component/system.

This prevents future player/NPC/avatar variants from requiring repeated copies of:

- placement traces;
- rotation logic;
- move logic;
- demolition logic;
- build-selection state;
- interaction traces.

Input conflicts are solved through contextual Mapping Context priority and explicit action ownership rather than manually duplicating key logic around inventory/combat systems.

---

# 8. Input Dependency Health Check

Validate that every required construction action exists and is mapped for all supported input families.

Minimum checks include:

- Enter/Exit Build Mode
- Interact / Build Work
- Confirm Placement
- Cancel Placement
- Rotate Left
- Rotate Right
- Next / Previous Buildable
- Build Catalog navigation
- Move/Relocate where supported
- Demolish/Remove hold action
- contextual UI confirm/back/tab navigation

Required input families:

- keyboard/mouse;
- Xbox-style controller;
- PlayStation-style controller.

A feature is not considered healthy when only the keyboard path survived a refactor.

---

# 9. HUD / UI Dependencies Must Be Decoupled From Fragile Direct References

The tutorial rebuilds HUD visibility bindings and variable references after migration.

Metaworld should minimize direct brittle coupling between widgets and one Character Blueprint's internal variables.

Prefer:

- stable view-model/state structs;
- event dispatchers;
- interfaces;
- Player Controller/UI subsystem mediation where appropriate;
- explicit widget update functions;
- device-aware input-prompt service;
- shared data-driven styles/material references.

Construction UI should query/receive canonical state such as:

- Build Mode active;
- Selected Buildable ID;
- valid/blocked state;
- blocked reason;
- cost/resources;
- construction progress;
- relocation/demolition state;
- contextual input prompts.

Do not require a widget to know the internal graph layout of `BPC_MW_BuildComponent`.

---

# 10. Material / Asset Reference Validation

The tutorial exposes a common failure mode: moved assets can lose expected material or reference assumptions.

Health checks should detect where practical:

- missing ghost material;
- missing valid/blocked preview presentation;
- missing construction-stage material/profile;
- missing final material/creator-texture restoration path;
- missing destruction presentation reference;
- broken soft references;
- redirector/path drift;
- assets stored outside expected folders;
- hard references that unexpectedly pull large content sets into memory.

Heavy buildable assets should favor soft references/data-driven loading where already established by Phase 20 canon.

---

# 11. Blueprint Inheritance / Interface Audit

After refactors, verify:

- buildable family inherits from the expected parent when appropriate;
- child overrides still call required parent implementations;
- no duplicate legacy Build Interface logic remains where parent/component now owns it;
- Interfaces are implemented by classes that advertise the capability;
- no stale class casts remain where an Interface/component contract replaced them;
- `BP_MW_Buildable_Master` has not accumulated family-specific God-Blueprint logic;
- no accidental permanent Tick was introduced.

---

# 12. Data Identity Validation

The building system must never depend on a mesh reference as its sole identity.

Validate:

- unique stable Buildable IDs;
- Family/Variant IDs resolve;
- Prefab IDs resolve;
- Opening/Snap IDs are unique in their intended scope;
- Structure relationship definitions reference valid IDs;
- Build Catalog entries point to valid definitions;
- server-side authoritative definition exists for anything the client can select.

This prevents migration/refactor-like failures where the correct mesh appears but the object has lost its authoritative gameplay identity.

---

# 13. Persistence Compatibility Check

Any construction architecture refactor must verify existing persistent fields still resolve or have a migration/version path.

Check:

- Buildable ID/version;
- Structure/Object ID;
- transform;
- owner/property;
- construction stage/progress;
- snap/opening relationships;
- structural support relationships;
- installed doors/windows;
- damage/destruction state;
- utility links;
- relocation policy/state where relevant;
- prefab logical sections/attachments.

A Blueprint compiling successfully is not enough if old saves load incorrect buildings.

---

# 14. Construction Health-Check Command / Editor Utility

Create an Editor-side health-check workflow over time using Python and/or Editor Utility Blueprints.

Suggested command concept:

`MW Construction Health Check`

Possible output sections:

- Plugins / required engine features
- Blueprint parent/interface/component architecture
- Buildable data definitions
- duplicate/missing IDs
- collision/query profiles
- placement footprints
- support samples
- opening/snap metadata
- input actions/mappings
- controller coverage
- UI dependencies
- material/reference validity
- Nanite compatibility/exception status
- damage/Chaos references
- persistent schema/version metadata
- forbidden legacy patterns
- performance warnings

Severity levels:

- ERROR — feature cannot work correctly;
- WARNING — likely architecture/performance/authoring problem;
- INFO — recommendation or expected exception.

Python remains Editor tooling only, consistent with existing Metaworld canon.

---

# 15. Forbidden / Legacy Pattern Detection

The health check can flag patterns we have already rejected from playlist tutorials, including:

- APEX Destruction dependency for new content;
- one trace channel per buildable family;
- `Visibility` as universal placement-obstruction truth;
- `BuildChildren[]` as the only persistent structural relationship model;
- massive-damage child cascades;
- arbitrary Delay for destruction ordering;
- all structural pieces permanently engine-Movable just to support relocation;
- hardcoded Q/E/1/right-click gameplay controls;
- one giant Character Event Graph containing every construction system;
- one giant `BP_MW_Buildable_Master` containing every family-specific behavior;
- permanent Tick on idle buildables;
- client-authoritative placement/damage/removal state.

---

# 16. Construction Smoke-Test Map / Test Suite

Maintain a small repeatable construction validation environment that can be run after major refactors.

Minimum smoke test:

1. enter Build Mode;
2. select a Foundation;
3. rotate with keyboard/mouse;
4. rotate with Xbox-style controller;
5. rotate with PlayStation-style controller;
6. valid placement turns valid/green;
7. obstruction turns blocked/red;
8. terrain support/extensions calculate correctly;
9. place Foundation authoritatively;
10. place/snap Wall;
11. place upper Floor with valid support;
12. install Door into DoorOpening;
13. interact/open/close Door;
14. save/load structure;
15. relocate an eligible free-standing object;
16. verify structural move is blocked when dependents prevent it;
17. damage/break Window independently;
18. destroy support and verify relationship/support reevaluation;
19. cancel/dismantle unfinished construction;
20. authorized demolition cleans relationships/occupancy;
21. prefab house places and restores logical openings/support data;
22. no unexpected permanent Tick/network/physics spike appears in the test scene.

This test does not prove the entire game is finished; it proves the construction stack survived the architecture/content change.

---

# 17. Portability Without Project Migration

Even though Metaworld is not moving projects, a clean dependency boundary is valuable.

Good modularity means:

- systems are easier to debug;
- test maps can load only construction dependencies;
- future engine upgrades are easier to validate;
- asset creators can be given clear requirements;
- broken settings can be detected automatically;
- accidental cross-system coupling is reduced;
- another AI/developer can understand what the feature requires without guessing.

Therefore **portability is treated as architecture quality**, not as a plan to relocate the project.

---

# Core Rule

> Metaworld stays in its project. The lesson from migration tooling is dependency discipline: every construction feature should declare what it needs, validate those requirements automatically where practical, and fail with clear diagnostics instead of hidden editor-state assumptions.