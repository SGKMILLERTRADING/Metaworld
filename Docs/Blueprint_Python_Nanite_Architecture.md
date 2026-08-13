# Metaworld — Blueprint-First, Python Tooling & Nanite-First Architecture

## Canonical Technical Rule

Metaworld is a **Blueprint-first Unreal Engine 5.8 project**.

Project gameplay, world systems, characters, interactions, economy, survival, property, businesses, law, NPC behavior hooks, vehicles, UI, communication, and other runtime game logic should be implemented with Unreal Engine Blueprints wherever practical.

Python is also part of the Metaworld development pipeline, but Python is used for **Editor tooling and automation**, not packaged runtime gameplay.

Nanite is the default geometry path for every asset category that Unreal Engine 5.8 supports and that remains compatible with the required gameplay, animation, material, customization, and target-platform behavior.

Core rules:

> Blueprint is the primary gameplay language of Metaworld.

> Python automates the Unreal Editor and content pipeline.

> If an asset can properly use Nanite, it should use Nanite unless profiling or a required feature proves that it should not.

This document supersedes older Metaworld implementation assumptions that describe the project as requiring a custom C++ gameplay foundation. Existing experimental/starter C++ files may remain temporarily while equivalent Blueprint systems are built and verified, but new Metaworld gameplay architecture should not depend on project-specific C++ unless the project owner later explicitly changes this rule.

---

# 1. Blueprint-First Runtime Architecture

Metaworld runtime gameplay should be organized through Blueprint assets such as:

- Blueprint Classes
- Blueprint Actor Components
- Blueprint Interfaces
- Blueprint Function Libraries
- Animation Blueprints
- Linked Animation Layers
- Blueprint Structs / Enums
- Data Assets / Primary Data Assets where appropriate
- Data Tables where appropriate
- Gameplay Tags
- Blueprint-accessible Subsystems where supported
- Editor Utility Blueprints for editor-only work
- UMG / Common UI Blueprint widgets where appropriate

The goal is not to put every node in one Event Graph. The goal is to keep the entire project **Blueprint-owned and Blueprint-maintainable** while still splitting systems into reusable modules.

---

# 2. Master Third-Person Character Is the Root

The canonical humanoid parent is:

`BP_MW_Character_Master`

It should derive from Unreal Engine's standard Character class through Blueprint and act as the authoritative master Blueprint for humanoid gameplay.

All suitable humanoid children derive from it, for example:

- `BP_MW_PlayerCharacter`
- `BP_MW_Civilian`
- `BP_MW_Ally`
- `BP_MW_Enemy`
- `BP_MW_Companion`
- `BP_MW_Guard`
- `BP_MW_Police`
- `BP_MW_Worker`
- `BP_MW_Mage`
- Other human/humanoid role or faction variants

The master Blueprint owns or attaches the shared Blueprint systems and exposes the common contracts all child characters use.

---

# 3. One Master Source Without One Giant Blueprint

The owner's rule remains that all humanoid characters come from the one master third-person Blueprint.

To make that scale, the master should contain and route modular Blueprint components instead of putting every system directly in the parent Event Graph.

Recommended structure:

`BP_MW_Character_Master`

- `BPC_MW_Vitals`
- `BPC_MW_Needs`
- `BPC_MW_Inventory`
- `BPC_MW_Equipment`
- `BPC_MW_Interaction`
- `BPC_MW_Combat`
- `BPC_MW_Skills`
- `BPC_MW_Profession`
- `BPC_MW_Reputation`
- `BPC_MW_AvatarCustomization`
- `BPC_MW_Communication`
- `BPC_MW_Ownership`
- `BPC_MW_EvidenceIdentity`
- `BPC_MW_MotionWarping`
- Other shared Blueprint components as systems are added

The parent still remains the single authoritative character family. Components simply keep the implementation organized.

A fix to a shared component is inherited through the master by all children that use it.

---

# 4. Blueprint Interfaces Are the Shared World Language

Metaworld should favor Blueprint Interfaces for cross-system communication instead of hard-casting every object to specific classes.

Examples:

- `BPI_MW_Interactable`
- `BPI_MW_Damageable`
- `BPI_MW_Ownable`
- `BPI_MW_UsableObject`
- `BPI_MW_Container`
- `BPI_MW_ProfessionAction`
- `BPI_MW_EvidenceSource`
- `BPI_MW_MediaSource`
- `BPI_MW_VehicleSeat`
- `BPI_MW_SmartInteraction`

This keeps players, NPCs, buildings, vehicles, objects, businesses, cameras, and world systems interoperable without creating giant dependency chains.

---

# 5. Python Is Development/Editor Automation

Python is approved for Metaworld development as an Unreal Editor automation and content-pipeline language.

Good Python jobs include:

- Batch importing assets
- Batch renaming and organizing assets
- Validating naming conventions
- Validating folder rules
- Checking creator assets
- Checking texture dimensions/formats
- Building reports
- Processing metadata
- Generating data rows/files
- Mass-editing supported asset properties
- Finding assets that should have Nanite enabled
- Enabling/configuring Nanite in supported editor workflows where the Unreal Python API exposes the required property
- Verifying Nanite exceptions
- Generating asset-audit lists
- Level/content placement automation
- Repetitive editor setup
- Creator-marketplace validation tools
- Animation asset auditing
- Retargeting pipeline helpers where exposed
- Build/preflight content checks

Python must not become a hidden runtime gameplay dependency.

Packaged Metaworld gameplay should continue to work without the Unreal Editor Python environment.

---

# 6. Editor Utility Blueprints + Python

Metaworld can combine Editor Utility Blueprints/Widgets with Python for internal production tools.

Examples:

## Nanite Audit Tool

A custom editor utility can:

1. Scan selected assets/folders.
2. Classify whether the asset type supports Nanite.
3. Check whether Nanite is enabled.
4. Flag unsupported materials/features.
5. Flag morph-target-dependent skeletal meshes.
6. Apply approved Nanite settings in batch.
7. Produce a report of exceptions.

## Creator Texture Validator

A tool can:

1. Read the selected approved base asset.
2. Check its locked texture channels.
3. Validate uploaded textures.
4. Check dimensions, naming, compression and color space.
5. Reject unsupported files.
6. Build marketplace metadata.

## Animation Audit Tool

A tool can:

1. Scan animation folders.
2. Check skeleton compatibility.
3. Check naming/tags.
4. Detect missing montage/notifies/metadata.
5. Build reports for profession/social/combat animation coverage.

---

# 7. Nanite-First Rule

Nanite should be enabled by default on every supported Metaworld asset where it works correctly and profiling does not show a reason to disable it.

The question for each new mesh should normally be:

> Why is this asset NOT using Nanite?

rather than:

> Should we bother enabling Nanite?

A documented exception is required when a supported-looking asset intentionally uses the traditional rendering path.

---

# 8. High-Priority Nanite Categories

Metaworld should aggressively use Nanite for supported assets such as:

## Static World Geometry

- Buildings
- Houses
- Shops
- Banks
- Bars
- Clubs
- Hospitals
- Police stations
- Roads/roadside structures where implemented as supported meshes
- Bridges
- Street furniture
- Walls
- Fences
- Rocks
- Debris
- Interior architecture
- Furniture
- Props
- Weapons when represented by compatible geometry
- Tools
- Creator-enabled base meshes
- Signs/billboards
- High-detail decorative geometry

## Instanced Geometry

Use Nanite where supported for:

- Instanced Static Meshes
- Hierarchical Instanced Static Meshes
- Repeated environmental props
- Repeated architecture pieces
- Large prop populations

## Destruction

Geometry Collections that support the required destruction behavior should use Nanite where appropriate.

## Landscapes

Use Nanite landscapes where they fit the world and performance profile.

## Splines

Nanite-compatible spline meshes can be used for suitable roads, paths, pipes, cables, barriers, and other spline-built geometry where the implementation supports it.

## Foliage

Use Nanite for suitable foliage, but foliage must be authored and profiled for Nanite rather than simply converting old masked-card foliage blindly.

Prefer geometry-based foliage where practical, use Preserve Area where appropriate, and monitor overdraw/WPO cost.

## Skeletal Meshes

Unreal Engine 5.8 supports Nanite Skeletal Meshes, so compatible characters/animated assets should be evaluated for Nanite instead of assuming skeletal meshes cannot use it.

However, skeletal meshes that depend on unsupported Nanite deformation features must use an exception path.

---

# 9. Avatar Customization Nanite Exception

Metaworld requires deep player customization.

Unreal Engine 5.8 Nanite currently does not support Morph Target deformation.

Therefore:

- If the Metaworld body/face customization system relies on morph targets, that deforming skeletal mesh cannot simply be forced onto the Nanite path.
- Hair, clothing, accessories, armor, and other compatible parts should still be independently evaluated for Nanite.
- If a future customization architecture avoids morph targets for a particular mesh and the mesh is otherwise Nanite-compatible, Nanite should be reconsidered.
- If Epic expands Nanite deformation support in a later Unreal version, Metaworld should re-evaluate the exception.

The principle is:

> Never disable character customization merely to satisfy a blanket Nanite checkbox rule.

Nanite serves Metaworld; Metaworld does not sacrifice required gameplay features to Nanite.

---

# 10. Nanite Material Rules

Nanite assets must use material features supported by the current engine path.

For UE5.8, the project must pay particular attention to:

- Opaque materials
- Masked materials
- Unsupported translucent mesh-material use cases
- Mesh decals requiring translucency
- World Position Offset limits
- Material complexity
- Custom-expression artifacts
- Aggregate geometry overdraw

If an asset requires a material feature that prevents correct Nanite rendering, that asset receives a documented exception or an alternate material/mesh solution.

---

# 11. Nanite Foliage Rules

Do not blindly convert legacy foliage cards and assume performance improves.

Metaworld foliage guidelines:

- Prefer actual geometry over large masked-card stacks where practical.
- Use Preserve Area for foliage meshes when appropriate.
- Clamp and profile World Position Offset.
- Inspect Nanite Overdraw visualization.
- Profile dense forests and layered vegetation.
- Treat UE5.8 Nanite foliage features according to their current production/beta/experimental status.

---

# 12. Nanite Is Not an Excuse to Ignore Performance

Nanite removes many traditional geometry/LOD constraints, but Metaworld still must profile:

- Material cost
- Pixel/shader cost
- Overdraw
- WPO
- Instance counts
- Streaming
- texture memory
- Virtual Shadow Maps
- lighting
- animation cost
- CPU gameplay cost
- replication
- World Partition streaming
- target hardware

The project should use Unreal profiling tools and Nanite visualization modes throughout production.

---

# 13. Nanite + Creator Marketplace

Metaworld controls all creator-enabled base meshes.

Therefore Metaworld can guarantee that each base mesh is authored and validated against the proper Nanite policy before creators receive texture templates.

Creators still only upload approved textures.

They cannot:

- Toggle Nanite
- Replace the mesh
- Change material slots
- Change the shader graph
- Alter LOD/Nanite structure
- Alter collision
- Change performance settings

This lets Metaworld maintain a consistent high-performance rendering foundation while players create visual texture variations.

---

# 14. Nanite Asset Validation States

Every major mesh asset should eventually have an internal technical status such as:

- `Nanite.Required`
- `Nanite.Enabled`
- `Nanite.Exception.MorphTargets`
- `Nanite.Exception.Material`
- `Nanite.Exception.Platform`
- `Nanite.Exception.Performance`
- `Nanite.Exception.Feature`
- `Nanite.NeedsReview`

The exact metadata implementation can use Gameplay Tags, asset metadata, naming rules, Data Assets, Python-generated reports, or another editor-only validation system.

---

# 15. Blueprint Performance Discipline

Blueprint-first does not mean careless Blueprint graphs.

Metaworld Blueprints should follow rules such as:

- Prefer events over unnecessary Tick logic.
- Disable Tick where not required.
- Use timers/event dispatchers where suitable.
- Avoid expensive Get All Actors patterns in recurring gameplay loops.
- Cache references when safe.
- Use interfaces/components instead of repeated deep casts.
- Keep server-authoritative economy/ownership actions explicit.
- Use replication deliberately rather than replicating every variable.
- Use data-driven definitions instead of giant switch statements.
- Split complex logic into functions/macros/components.
- Profile Blueprint execution rather than assuming it is cheap or expensive.

The project remains Blueprint-first while still being engineered like a large persistent multiplayer game.

---

# 16. Master Blueprint Development Order

Recommended foundation order:

1. Create/lock `BP_MW_Character_Master`.
2. Move shared character behavior into Blueprint Actor Components.
3. Create core Blueprint Interfaces.
4. Build `ABP_MW_Master` and modular animation layers.
5. Build player child Blueprint.
6. Build civilian/ally/enemy test children.
7. Verify all children receive fixes/features from the master family.
8. Build editor validation utilities.
9. Enable Python Editor Script Plugin for pipeline automation.
10. Build Nanite asset audit/enablement workflow.
11. Convert eligible world assets to Nanite by default.
12. Track exceptions instead of silently leaving supported assets non-Nanite.
13. Profile representative city/interior/wilderness scenes.
14. Expand Blueprint systems without introducing project-specific C++ dependencies unless the owner later explicitly approves them.

---

# 17. Existing Starter C++ Files

Older Metaworld starter work may contain files such as a custom C++ character or module scaffolding.

Those files are now considered **legacy starter implementation**, not the canonical future gameplay architecture.

Do not build new Metaworld gameplay systems on top of those files solely because they already exist.

Migration rule:

1. Build the Blueprint equivalent.
2. Verify the Blueprint system works.
3. Redirect child assets/systems to the Blueprint architecture.
4. Only then remove obsolete starter code in a deliberate cleanup pass.

No destructive cleanup should happen merely because this document exists; migration should be verified first.

---

# 18. Final Technical Principle

Metaworld should be built so its gameplay can be understood, modified, extended, and inherited through Blueprint.

Python should reduce repetitive editor work.

Nanite should carry as much supported geometry as Unreal Engine 5.8 allows without breaking required gameplay or visual features.

The target architecture is:

`Blueprint Runtime Game`

+

`Python / Editor Utility Production Tools`

+

`Nanite-First Geometry Pipeline`

+

`One Master Third-Person Blueprint Character Family`

=

**Metaworld's canonical UE5.8 technical foundation.**
