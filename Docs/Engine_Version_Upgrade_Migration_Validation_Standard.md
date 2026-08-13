# Metaworld — Engine Version Upgrade, Migration & Validation Standard

**Status:** Canonical / Approved Project Maintenance Standard

**Target Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first / Python editor tooling / migration-gated

## Canonical Principle

Engine upgrades are controlled project migrations, not casual editor-open events. Every upgrade must preserve a recoverable source project, validate plugins/content/data, rebuild derived artifacts, and run a defined gameplay acceptance suite before the upgraded branch becomes canonical.

> Opening successfully is not the same as migrating successfully. Metaworld adopts a new engine version only after its critical systems, content and performance pass verification.

---

# 1. Source Protection

Before any engine migration:

- commit/tag the last known-good source state;
- create a separate migration branch/copy;
- back up non-source-controlled project assets/settings that matter;
- record current engine/plugin versions;
- record known warnings/failures before migration;
- never overwrite the only working project copy.

A migration failure must be recoverable without guessing which files changed.

---

# 2. Plugin / Dependency Audit

Before opening the project in a newer engine, audit required plugins and integrations, including where applicable:

- MetaHuman;
- Water;
- Niagara;
- Chaos/Geometry Collection;
- Enhanced Input;
- Common UI if enabled;
- Motion Warping;
- IK Rig / Control Rig;
- Python Editor Script Plugin;
- Fab/content integrations;
- project-specific plugins/tools.

For each dependency record:

- required/optional status;
- version compatibility;
- migration notes;
- fallback/disable path if nonessential.

Do not accept a plugin dialog blindly in production migration without confirming the project still builds/loads and the dependent systems work afterward.

---

# 3. Fonts / External Project Assets

Custom fonts, config files, editor tooling data and other project-adjacent assets must be explicitly tracked or documented.

Do not rely on manually remembering to copy a font from an old installation every engine upgrade.

Preferred rule:

- project-required assets live inside source-controlled/project-managed locations where licensing permits;
- Python/editor validation can report missing expected fonts/assets;
- migration checklist names any external dependency that genuinely cannot live in the repository.

---

# 4. Derived Data / Shader Rebuild

A new engine version may rebuild shaders, derived data and generated assets.

Rules:

- treat initial long compile/rebuild time as a migration task, not evidence of runtime performance;
- allow the editor to finish required compilation before judging systems;
- clear/rebuild derived data only when justified by migration/debugging policy;
- never commit machine-specific cache artifacts as gameplay truth.

---

# 5. Asset / Material Validation

Migration can expose broken/stale materials, instances, references or serialization.

Validation should cover:

- materials/material instances compile;
- texture references are valid;
- Nanite flags remain appropriate;
- skeletal assets/animations retarget correctly;
- Geometry Collections/destruction materials remain intact;
- Water materials/rendering remain correct;
- MetaHuman components/LODs/hair remain valid;
- UI fonts/icons/style assets load;
- Data Tables/Row Handles resolve;
- Blueprint compile errors/warnings are reviewed.

A manual disconnect/reconnect trick may repair one migrated material, but the canonical process is to identify whether other assets share the same failure class.

---

# 6. Blueprint / Data Schema Validation

After migration:

- compile canonical Blueprint systems;
- validate structs/enums/data tables/data assets;
- inspect warnings from deprecated/changed nodes;
- test stable IDs and persistence schemas;
- verify widget focus/input behavior;
- run Python/editor audits for stale references where practical.

Do not silence warnings merely to obtain a green compile if the semantics changed.

---

# 7. Critical Gameplay Smoke Suite

Minimum migration smoke tests should include representative systems such as:

- player spawn/character customization;
- walking/run/sprint/stamina;
- swimming/Breath/drowning;
- ladder/ledge traversal;
- inventory/equipment/quickslots;
- item pickup/drop/stacking;
- crafting/upgrading;
- NPC interaction/dialogue/trading;
- GrimKoin/PromoKoin transactions;
- loot/chests/locks/keys;
- resource gathering/Chaos presentation;
- construction/persistence where available;
- save/load/reconnect;
- controller input/focus;
- animation/IK/Motion Warping;
- multiplayer authority paths where implemented.

The suite expands as Metaworld grows.

---

# 8. Performance Baseline

Record representative pre-upgrade and post-upgrade measurements rather than relying on impression.

Track as available:

- frame time/FPS in standard scenes;
- memory/VRAM;
- shader/asset load behavior;
- animation cost;
- Niagara/Chaos cost;
- NPC/crowd cost;
- networking/server cost;
- UI/SceneCapture cost.

A migration is not approved merely because the editor opens if frame time regresses significantly without understood benefit.

---

# 9. Editor Preferences

Editor-only preferences such as Asset Editor placement may be documented for team/user convenience but are not gameplay architecture.

Keep workflow preferences separate from required project settings so one developer's editor layout does not become a hidden runtime dependency.

---

# 10. Migration Sign-Off

The upgraded branch becomes canonical only when:

1. required plugins/dependencies load;
2. critical Blueprints compile;
3. critical content passes validation;
4. persistence/data IDs survive;
5. gameplay smoke suite passes at the current implementation level;
6. controller/input behavior remains valid;
7. known regressions are documented/accepted;
8. performance is measured;
9. the source rollback point remains available.

---

# 11. Python Editor Automation

Python may automate/report:

- Blueprint compile/audit queues where supported;
- missing asset references;
- naming/folder validation;
- material/texture metadata checks;
- Data Table/ID validation;
- Nanite flags;
- animation/profile metadata;
- migration reports/checklists.

Python remains editor tooling only.

---

# Core Rule

> Metaworld upgrades Unreal deliberately. Preserve the old working state, audit dependencies, migrate in isolation, validate content/data/gameplay/performance, and only then declare the newer engine version canonical.