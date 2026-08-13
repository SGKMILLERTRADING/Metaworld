# Metaworld — Prefab / Pre-Built House Construction System

**Status:** Canonical / Approved Phase 20 Upgrade

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first

## Canonical Principle

Metaworld supports placing complete pre-designed houses and other prefab structures without forcing every player to construct every wall, floor and roof piece manually.

Core rule:

> A prefab is one convenient construction choice, not one opaque gameplay object. It may use an optimized combined visual shell, but ownership, supports, openings, utilities, construction progress, attachments, persistence, damage and renovation remain explicit world data.

The UE4 tutorial concepts of merging static meshes, registering a full house in the build database, placing it as one buildable and exposing Door/Window snap locations are approved. Metaworld upgrades them into a data-driven Prefab Definition and logical structure system integrated with the rest of Phase 20.

---

# 1. Player Construction Choices

Metaworld can support both:

1. **Modular construction** — foundation/floor/wall/roof/opening pieces assembled by the player.
2. **Prefab construction** — a pre-designed approved building plan placed as a single construction selection.

Prefab placement does not bypass normal rules for:

- property/deed/build volume
- zoning/story/height restrictions
- Builder/profession/permit requirements
- material/resource/GrimKoin cost
- Construction Work Units
- terrain/foundation support
- overlap/footprint validation
- utilities
- persistence
- multiplayer authority
- controller compatibility

A prefab is convenience and design choice, not free instant construction.

---

# 2. Prefab Definition

Recommended data-driven definition fields include:

- `PrefabID`
- `BuildableID`
- `FamilyID`
- `VariantID`
- display name/category/icon
- preview/ghost representation
- optimized visual shell or assembly reference
- authoritative placement footprint
- authored support sample points
- minimum/maximum terrain/support rules
- foundation/support-extension policy
- property footprint/build-volume requirements
- story/height metadata
- zoning/permit requirements
- Builder/profession requirements
- total material/resource requirements
- total Construction Work Units
- stage recipe
- logical substructure/section records
- opening/attachment slots
- utility service points
- optional expansion/add-on snap points
- collision profile data
- durability/damage-section data
- relocation policy
- demolition policy
- Nanite/HLOD/performance metadata
- persistence schema/version

The build catalog references stable Prefab/Buildable IDs rather than relying on one duplicated Actor class per house style.

---

# 3. Visual Merge vs Gameplay Structure

The tutorial's merged static mesh is approved as an Editor/content-production optimization where useful.

Metaworld separates:

## Visual Representation

May use:

- one merged static mesh
- several optimized shell meshes
- Nanite-compatible geometry where supported/appropriate
- HLOD/streamed representations at distance
- simplified ghost/preview mesh during placement

## Logical Representation

Stores gameplay data for:

- Structure ID / Prefab Instance ID
- owner/property
- foundation/support relationships
- stories/sections/rooms where needed
- opening slots
- installed doors/windows
- utility connection points
- damage/condition zones
- renovation/attachment permissions
- construction stage/progress
- history/persistence

A rendering merge must never erase gameplay information needed by the persistent world.

---

# 4. Actor / Data Architecture

A prefab may use a Blueprint root such as:

`BP_MW_PrefabStructure`

or another approved shared prefab root.

The root should avoid giant duplicated Event Graphs. Common construction logic remains in shared Blueprint Components, Interfaces and data definitions.

Not every logical wall/section needs a full permanent Actor if that would create unnecessary Actor/replication overhead. Metaworld may store lightweight substructure records and only instantiate separate Actors/components for elements that need independent interaction, movement, damage, attachment or replication.

Examples that commonly remain separate persistent objects:

- doors
- windows where interactive/breakable
- utility devices
- security devices
- movable/replaceable appliances
- special interactive structural elements

This preserves performance while keeping important world state explicit.

---

# 5. Pivot / Origin Standard

The tutorial's "select the bottom-front mesh first" technique is useful for quickly getting a workable pivot, but it is not the canonical asset rule.

Every Prefab Definition must have a deliberate canonical placement origin.

Recommended standard:

- root/origin aligned to an authored foundation/base reference
- consistent forward axis
- predictable ground/base elevation
- explicit local transform for the visual shell
- authored support sample points relative to the same origin
- authored opening/attachment slots relative to the same origin

Per-asset exceptions are data, not hidden Blueprint correction hacks.

Python Editor tooling can later audit:

- pivot/origin placement
- forward orientation
- ground/base elevation
- support samples
- opening-slot transforms
- footprint alignment
- collision alignment

---

# 6. Placement Workflow

Prefab placement reuses the normal Build Component.

Flow:

`Select Prefab`
-> resolve authoritative Prefab Definition
-> spawn low-cost ghost/preview
-> place/rotate within allowed orientation rules
-> validate placement footprint
-> sample terrain/support requirements
-> preview required support extensions where needed
-> validate property/build volume/zoning
-> validate cost/Builder/permit requirements
-> preview openings/important anchors where useful
-> client confirms
-> server resolves definition independently
-> server reruns all validation
-> create persistent prefab Construction Site or completed prefab only when the construction mode/rules allow it

The client never authoritatively submits the prefab's mesh, cost, required support count or finished state.

---

# 7. Terrain & Foundation Support

Prefab houses integrate with `Docs/Foundation_Terrain_Support_Extension_System.md`.

A prefab can define many authored `SupportSamplePoints[]`, not just four corners.

Possible sample patterns:

- corners
- center
- load-bearing wall lines
- porch/deck supports
- garage wing
- stair tower
- irregular footprint sections

The support system determines:

- direct terrain support
- required footing/pier/extension support
- excessive unsupported depth
- invalid slope/support material
- property/subsurface-right conflicts
- support material/work requirements

A prebuilt house cannot float merely because the visual mesh was placed as one object.

---

# 8. Placement Footprint & Collision

Prefab houses use explicit placement footprint data from the canonical overlap system.

A large/irregular prefab can use multiple footprint volumes rather than one oversized render-mesh bounds box.

Placement validation distinguishes:

- building footprint
- porch/deck footprint
- garage wing
- support/pier positions
- required clearance areas
- intentional terrain contact
- internal voids/courtyards where relevant

Finished gameplay collision is authored separately from the placement footprint.

Use simple collision where it correctly represents gameplay space. Complex/per-poly collision must not become the authoritative construction-placement rule merely because the visual shell is merged.

---

# 9. Door & Window Opening Slots

The tutorial's Door/Window Box Collision concept is approved as an acquisition aid, but Metaworld uses the existing authoritative opening/attachment architecture.

Prefab definitions expose stable opening slots such as:

- `Opening.FrontDoor`
- `Opening.BackDoor`
- `Opening.Bedroom01.WindowA`
- `Opening.Kitchen.WindowA`

Each opening can store:

- stable Opening ID
- local transform
- width/height/depth
- facing
- opening type
- compatibility tags
- occupancy
- installed Object ID
- obstruction bounds
- security/renovation metadata

Query-Only Box Collision or another lightweight acquisition volume can help players target the opening.

High-level compatibility uses stable IDs/tags/data rather than creating permanent `DoorTrace`, `WindowTrace`, `GarageDoorTrace`, etc. channels for every future attachment type.

Installed doors and windows remain separate persistent objects according to `Docs/Doors_Windows_Openings_Construction_System.md`.

---

# 10. Prefab Expansion / Add-On Slots

A prefab does not need to be permanently isolated after placement.

Approved optional external snap/add-on points can support later:

- deck/porch extensions
- garage additions
- stairs/ramps
- fences/gates
- utility units
- awnings
- solar/battery equipment
- balconies where structurally allowed
- compatible room/wing expansion systems later

The prefab may omit normal dense modular snap boxes if it is intended to be standalone, but authored expansion slots remain possible through `BPI_MW_BuildSnapProvider` or the appropriate attachment contract.

---

# 11. Construction Progress

Player-placed prefabs integrate with `Docs/Construction_Progress_Build_To_Completion_System.md`.

A prefab may be placed as a persistent construction plan/site instead of instantly becoming a finished house.

Example stages:

1. site/permit
2. footings/supports
3. foundation
4. structural shell/frame
5. floors/roof
6. walls/openings
7. utilities rough-in
8. doors/windows
9. interior/exterior finish
10. inspection/completion

The visual representation can change by stage through:

- stage-specific meshes
- visibility groups
- material state
- partial shell sections
- construction scaffolding/props where useful

Work/material requirements remain server-authoritative.

A prefab cannot bypass material costs or Builder labor just because the player selected one catalog entry.

---

# 12. Economy & Builder Integration

Prefab construction can create real work for:

- Builders
- construction companies
- suppliers
- delivery drivers
- electricians
- plumbers
- inspectors
- equipment operators
- future specialists

The Prefab Definition can reference an authoritative construction recipe containing all required resources/work.

Large prefab homes may be faster/easier for players to plan than manual construction while still costing appropriate materials, labor, fees and time.

---

# 13. Utilities

Prefab houses may expose stable utility service points such as:

- `Utility.Power.Main`
- `Utility.Water.Main`
- `Utility.Waste.Main`
- `Utility.Gas.Main` where supported
- `Utility.Data.Main` later

Placement does not automatically grant active service.

Utilities must connect according to Phase 21 rules, property availability, installation work and billing.

A prefab can therefore be structurally complete but still lack electricity/water until proper service is connected.

---

# 14. Damage, Renovation & Replacement

A prefab visual shell must not force the whole house to behave as one indivisible health bar unless a deliberately simple prefab is designed that way.

Logical damage/renovation zones can represent:

- foundation/support section
- exterior wall section
- roof section
- porch/deck
- garage section
- doors/windows
- utility equipment

High-value interactive/replaceable elements remain separate objects where appropriate.

Possible future renovation actions include:

- replace door/window
- upgrade security
- add approved extension
- repair roof/section
- renovate room/finish
- modify an approved structural section under Builder rules

Full structural modification may require conversion to modular renovation data rather than arbitrary editing of the merged visual shell.

---

# 15. Relocation & Demolition

Prefab houses integrate with:

- `Docs/Construction_Relocation_Move_System.md`
- `Docs/Construction_Deconstruction_Demolition_Removal_System.md`

A small portable prefab/module may have an approved grouped relocation policy.

A normal completed house is not freely draggable like furniture.

Relocation can require:

- disconnecting utilities
- valid machinery/transport method
- Builder/Engineer or other profession
- destination property/build-volume validation
- combined footprint/support checks
- movement cost/work
- authoritative handling of all child/slot/object relationships

Demolition resolves the prefab root plus its logical substructure, attachments, utilities and persistent records without leaving orphaned doors/windows or stale occupancy.

---

# 16. Multiplayer Authority

Client:

- selects Prefab ID
- previews shell
- rotates/positions
- sees local footprint/support/cost warnings
- selects compatible door/window attachments later

Server:

- resolves Prefab Definition
- verifies property/build volume
- verifies footprint/overlap
- verifies terrain/support samples/extensions
- verifies zoning/permit
- verifies Builder/profession
- verifies resources/cost/work
- creates authoritative Prefab Instance / Construction Site
- creates/records opening slots
- creates required logical substructure/support relationships
- assigns persistent IDs

A modified client cannot:

- substitute a cheaper prefab definition
- omit required support extensions
- shrink the footprint
- invent opening slots
- claim finished state
- bypass resource/work requirements
- place outside legal property

---

# 17. Persistence

Store at minimum:

- Prefab Instance / Structure ID
- Prefab/Buildable/Variant ID
- transform
- owner/property
- construction stage/progress
- condition/damage state
- support relationships
- foundation extensions
- opening slot state
- installed Door/Window IDs
- utility connections
- attachment/add-on relationships
- renovation/version state
- relevant history/timestamps

The visual shell can be regenerated from the authoritative prefab definition and instance data.

---

# 18. Controller Compatibility

Prefab construction must work with:

- keyboard/mouse
- Xbox-style controllers
- PlayStation-style controllers

Controller-capable flow includes:

- open Build Catalog
- select Prefab category/house
- preview
- rotate
- inspect placement/support warnings
- confirm/cancel
- target Door/Window openings
- install/replace attachments
- navigate construction-progress UI
- understand blocked reasons

No required prefab placement or attachment action may depend on a mouse-only editor-style transform workflow.

---

# 19. Performance

Prefab houses are a strong performance opportunity when authored carefully.

Rules:

- low-cost ghost/preview representation
- Nanite where compatible
- optimized shell/section meshes where beneficial
- avoid one Actor per decorative sub-piece
- keep separate Actors only where gameplay/persistence/interaction requires them
- no permanent snap/overlap queries after placement
- no idle Tick just because the prefab has many logical sections
- compact substructure records where full Actors are unnecessary
- World Partition/HLOD/relevancy support
- only relevant interactive attachments replicate at necessary fidelity

Merged rendering is an optimization choice, not a reason to erase gameplay state.

---

# 20. Editor / Python Tooling

Python Editor tooling can later validate Prefab Definitions for:

- canonical pivot/origin
- footprint bounds
- support sample coverage
- opening-slot IDs/transforms
- duplicate/missing slots
- door/window size compatibility
- utility service points
- collision coverage
- Nanite settings
- material assignments
- heavy references
- construction recipe completeness
- missing persistence/version metadata
- relocation/demolition policy

Python remains editor-side tooling, not packaged runtime gameplay logic.

---

# 21. Initial Vertical-Slice Prefab Test

The first prefab test should prove:

1. A small pre-designed house appears in the Build Catalog.
2. Keyboard/mouse can place it.
3. Xbox-style controller can place it.
4. PlayStation-style controller can place it.
5. Ghost uses explicit prefab footprint rather than raw merged-mesh bounds.
6. Invalid property boundary placement is rejected.
7. Invalid overlap is rejected.
8. Uneven terrain calculates required support extensions.
9. Missing support resources block placement.
10. Server independently resolves Prefab ID, footprint, support and construction recipe.
11. Placement creates a persistent construction site rather than free instant completion when the recipe requires construction.
12. Construction stages consume real materials/work.
13. Front Door opening slot exists with stable ID.
14. Window opening slot exists with stable ID.
15. Compatible Door installs into Door slot.
16. Wrong-size/type Door is rejected.
17. Compatible Window installs into Window slot.
18. Installed Door/Window remain separate persistent objects.
19. Save/load restores prefab, support, progress, slots and attachments.
20. Finished prefab does not require every decorative sub-piece to exist as a separate Actor.
21. Prefab remains compatible with authorized demolition and configured relocation policy.
22. Performance remains within Phase 20/Smoothness budgets.

---

# Core Rule

> Metaworld prefab houses give players the convenience of placing a complete design without sacrificing the living-world rules underneath it. Visual geometry may be merged for performance, but the authoritative prefab definition still knows what the building is, where it is supported, what openings and utilities it owns, what it costs to construct, what can be replaced or damaged, and how it persists in the world.
