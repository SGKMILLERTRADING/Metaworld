# Metaworld — Base-Building Playlist Phase 20 Roadmap Addendum — Part 2

**Status:** Canonical / Approved Phase 20 Intake Log Continuation

**Continues:** `Docs/Base_Building_Playlist_Phase20_Roadmap_Addendum.md`

**Base Master Roadmap:** `Docs/Master_Development_Roadmap.md` v2.9

**Purpose:** Continue recording approved tutorial-playlist upgrades without repeatedly replacing the very large first addendum. This continuation is equally canonical Phase 20 material and will be consolidated with Part 1 into the Master Roadmap after the playlist review is complete.

## Permanent Rules Carried Forward

All permanent rules from Part 1 remain active, including:

- Blueprint-first runtime architecture.
- `BPC_MW_BuildComponent` owns build-mode flow.
- stable Buildable/Family/Variant IDs and data-driven definitions.
- server-authoritative permanent construction state.
- controller support for keyboard/mouse, Xbox-style controllers and PlayStation-style controllers.
- property, profession, permit, resource, support, collision, persistence and performance validation.
- explicit placement footprints and logical snap/slot occupancy.
- valid terrain/structural support chains instead of arbitrary floating structures.
- tutorial-specific keys, constants, channels and delay values are examples, not permanent Metaworld architecture.
- construction removal is an authorized transaction, never a universal delete command.
- relocation is an authorized construction transaction, never unrestricted transform editing.
- permanent structural pieces should remain in the most efficient appropriate settled mobility/rendering state wherever practical; relocation uses a temporary movable ghost rather than forcing all finished structure components to remain engine-Movable.
- visual mesh merging/optimization never erases authoritative logical construction data needed for openings, supports, utilities, ownership, damage, renovation, persistence or server validation.
- common persistent-buildable lifecycle belongs in a shallow shared Blueprint parent; capabilities remain interface/component/data driven so the parent never becomes a giant all-purpose construction Blueprint.

---

# Playlist Intake Status — Continued

## Episode Upgrade 12 — Construction Removal, Deconstruction & Demolition

**Classification:** UPGRADE — APPROVED

Approved:

- tutorial hold-to-remove concept retained as an intentional-action safety mechanism
- radial/circular progress UI retained for hold confirmation
- hardcoded keyboard `1` key replaced by Enhanced Input action/context architecture
- hold action must have keyboard/mouse, Xbox-style controller and PlayStation-style controller paths
- radial UI is hidden/collapsed when removal is inactive and resets on release, target loss, mode exit, rejection or completion
- construction removal is **not** a universal `Destroy Actor` command
- three removal paths are separated:
  1. cancel/dismantle unfinished construction
  2. authorized deconstruction/demolition of completed structures
  3. normal world damage/destruction through combat, accidents, fire, weather, war, crime, etc.
- tutorial `IsBuildFinished` concept is upgraded into richer construction-state + removal-policy data
- unfinished construction can be cancelled/dismantled only by authorized users/contracts/roles
- completed structures are removable through an authorized demolition/deconstruction workflow rather than being permanently undeletable
- unauthorized players cannot use construction tools to delete somebody else's finished or unfinished structure
- hostile/illegal destruction must use durability/damage/crime/evidence systems instead of construction removal
- hold duration is data-driven per removal mode/object where appropriate
- holding to confirm can start a removal job; large structures do not instantly vanish after a short hold
- structural removal can require Demolition/Construction Work Units, Builder qualification, tools, machinery, workers, permits and utility safety where applicable
- server owns final removal authorization, hold/work completion, dependency handling, salvage/refund and persistent cleanup
- client cannot fake unfinished state, ownership, hold duration, salvage amount or arbitrary actor deletion
- removing an unfinished site releases its reserved snap/placement slot only after authoritative removal transaction succeeds
- refunds/salvage are server-authoritative and cannot exceed legitimately committed materials; removal must never mint resources
- unused reserved materials may be returned according to policy
- installed/consumed materials may provide partial salvage according to material/state/damage rules
- labor/time already consumed is not automatically refunded
- removal checks structural dependencies before deleting a support-bearing piece
- walls, floors, columns, piers, foundation extensions and other supports cannot silently disappear while dependent structures remain treated as valid
- possible dependency outcomes include safe removal, blocked removal, explicit cascade-removal preview or deliberate unsafe demolition path where world rules allow it
- removing support triggers event-driven structural support revalidation
- installed doors/windows/attachments must be resolved atomically when a parent wall/opening is removed
- opening/snap/support occupancy and parent-child relationships are cleaned up as part of the removal transaction
- property/build-budget state is updated after successful removal
- demolition/deconstruction can create legitimate Builder jobs and daily role duties
- NPC Builders can perform authorized dismantling/demolition under valid contracts, tools/resources and persistent job rules
- demolition can later connect to debris cleanup, salvage, repair, inspections, insurance and public-safety duties
- no permanent removal Tick; target/progress checks only run while the relevant removal action/mode is active

Detailed companion: `Docs/Construction_Deconstruction_Demolition_Removal_System.md`

## Episode Upgrade 13 — Construction Relocation / Move System

**Classification:** UPGRADE — APPROVED

Approved:

- tutorial concept of selecting an existing finished buildable and reusing Build Mode for repositioning is retained
- hardcoded keyboard `Q` and right-click are replaced by Enhanced Input actions/context mappings
- relocation must work with keyboard/mouse, Xbox-style controllers and PlayStation-style controllers
- tutorial `MovableActor` / `IsMoving` state is generalized into an explicit relocation session with persistent Structure/Object ID and authoritative reservation state
- `ReturnBuildID`-style lookup becomes authoritative stable Buildable/Variant identity resolution rather than trusting preview mesh/class data
- relocation is **not** unrestricted transform editing
- Buildable Definitions carry data-driven `RelocationPolicy` and related requirements
- relocation categories are separated:
  1. freely relocatable placed objects
  2. restricted installed objects
  3. structural pieces
- furniture, decorations and other approved non-structural placed objects may often move directly after normal permission/footprint/destination checks
- doors/windows and other installed objects may require compatible destination opening/attachment slots and may preserve or resolve security/state through the authoritative move transaction
- utility-connected appliances/equipment can require disconnect/reconnect rules
- containers can require emptying or explicitly permit contents to move with them according to authoritative data
- foundations, walls, floors, columns, beams, stairs, roofs, piers and other support-bearing pieces are not treated like ordinary furniture
- structural direct move can be blocked when parent/dependent support relationships exist
- structural pieces may instead require dismantle + rebuild, Builder relocation work, tools/machinery, or an explicitly designed grouped/module move
- moving a support-bearing wall or pier cannot silently leave dependent upper floors/foundations valid
- future prefab/module relocation is approved when a complete module has authored combined footprint, support, utility, mass/size and machinery rules
- selecting a move target does not immediately move the authoritative finished Actor
- server/authority grants a relocation session and reserves the original object/relationships against conflicting move/demolition/renovation transactions
- client creates a temporary low-cost movable relocation ghost from the authoritative Buildable/Variant definition
- original persistent structure remains authoritative at the original location until commit succeeds
- relocation ghost reuses normal placement rotation, snapping, footprint, overlap, property, support and blocked-reason feedback
- destination validation includes relocation policy, permission, footprint, collision, snap/opening/support occupancy, property/deed/build volume, zoning, support, utilities, contents, dependencies, tools/profession, cost and work requirements
- old snap/opening/support slots remain reserved until successful commit so another player cannot steal the original slot mid-move
- cancel/failure leaves the original structure unchanged and clears temporary reservation/ghost state
- successful relocation is an atomic server transaction: validate destination -> reserve destination -> resolve attachments/utilities/contents -> update persistent transform/relationships -> release old relationships -> replicate settled state
- moved eligible objects normally preserve their persistent Object/Structure ID rather than being destroyed/recreated as unrelated identity
- direct relocation may have data-driven cost, labor, tool, machinery or profession requirements according to object size/type
- moving a chair can be trivial while relocating heavy machinery or a prefab module can become real Builder/Mechanic/Engineer/mover work
- client cannot move another player's object, shrink footprint, ignore dependencies, bypass utility rules, forge destination support or claim a structural piece is freely movable
- concurrent Move/Demolish/Renovate operations on the same object are serialized/reserved rather than racing
- tutorial instruction to set all foundations/floors permanently engine `Movable` is rejected as universal architecture
- finished settled structural pieces remain in the most efficient appropriate mobility/rendering state wherever practical
- relocation preview uses a temporary movable ghost; permanent objects do not pay continuous Move-system cost while idle
- move system must not unnecessarily sacrifice Nanite/HLOD/streaming/scalability benefits
- relocation UI communicates why a move is blocked and any utility, contents, Builder, machinery, cost or dependency requirement
- no permanent relocation Tick/query work while Move mode is inactive
- Python Editor tooling can audit relocation policy, structural objects incorrectly marked freely movable, footprints, mobility setup, utilities/attachments and group/module metadata

Detailed companion: `Docs/Construction_Relocation_Move_System.md`

## Episode Upgrade 14 — Prefab / Pre-Built House Construction

**Classification:** UPGRADE — APPROVED

Approved:

- players can choose modular piece-by-piece construction or a pre-designed prefab/full-house buildable
- prefab construction is convenience/design choice, not a bypass around property, zoning, Builder, permit, resource, support, construction-work, persistence or multiplayer rules
- tutorial merged-house mesh is retained as an optional visual/editor optimization, not the full gameplay truth
- a prefab uses a stable authoritative Prefab/Buildable Definition with placement footprint, support samples, construction recipe, openings, utilities, damage/renovation metadata, relocation policy and persistence version
- visual representation may use one merged shell, several optimized shell meshes, Nanite-compatible geometry where appropriate, HLOD/streamed representations and a simpler placement ghost
- logical representation keeps Structure/Prefab Instance ID, owner/property, support relationships, openings, installed objects, utilities, damage/condition zones, construction progress, attachments and history
- rendering may be merged while gameplay remains logically structured
- not every decorative wall/piece needs its own Actor; lightweight substructure records are preferred where independent Actor behavior is unnecessary
- interactive/replaceable elements such as doors, windows, utility/security devices and appropriate appliances can remain separate persistent objects
- tutorial "select bottom-front mesh first for pivot" remains a quick authoring trick but is not a permanent asset rule
- every prefab has a deliberate canonical origin/pivot, forward axis, base elevation and authored local transforms
- Python Editor tools can audit prefab pivots/origins, footprints, support samples, opening slots, collision and heavy references
- Prefab Definition is registered in the scalable Build Catalog using stable IDs rather than requiring a unique hardcoded selection graph
- prefab ghost reuses normal rotation/orientation, placement-footprint, overlap, property, support, blocked-reason and controller systems
- large/irregular prefabs can use multiple authoritative placement-footprint volumes instead of one raw merged-mesh bounds box
- prefab terrain support uses authored `SupportSamplePoints[]`; larger/irregular homes can sample corners, centers, bearing lines, porch/garage wings and other required locations
- required footing/pier/foundation-extension previews, costs and Construction Work Units come from the existing terrain-support system
- prefab cannot float merely because it is visually one mesh
- Door/Window snap boxes are upgraded into stable authoritative Opening/Attachment Slot IDs with transform, dimensions, facing, compatibility tags, occupancy and installed Object ID
- Query-Only Box Collision or equivalent volumes may make opening slots easier to target but are not the authoritative compatibility rule
- no permanent new trace channel per Door/Window/prefab attachment category; general query profiles plus IDs/tags/data remain canonical
- installed doors/windows stay separate persistent objects and use the existing opening/interaction systems
- standalone prefab does not need dense modular snap points everywhere, but it may expose authored expansion/add-on slots for decks, porches, garages, stairs/ramps, utilities, awnings, solar/battery equipment, balconies or future compatible extensions
- player-placed prefab can create a persistent Construction Site and progress through stages instead of spawning instantly complete
- prefab construction recipe can include site/permit, support/foundation, shell/frame, floors/roof, walls/openings, utilities, doors/windows, finishes and inspection/completion stages
- prefab cannot bypass material/resource or Builder labor requirements because it is one catalog entry
- prefab construction can generate Builder/company/supplier/delivery/electrician/plumber/inspection work
- prefab may expose stable utility service points; structural completion does not automatically provide electricity/water/service without valid Phase 21 connections
- prefab damage/renovation can use logical sections/zones so one damaged wall/roof area does not automatically require treating the whole visual shell as one indivisible health bar
- normal completed houses are not freely draggable; relocation follows the existing relocation policy, utility disconnection, machinery, combined footprint/support and authoritative child-relationship rules
- small portable prefab/modules may explicitly permit grouped relocation
- demolition resolves prefab root, logical substructure, openings, installed doors/windows, utilities, support relationships and persistence atomically
- server independently resolves Prefab ID, footprint, support requirements/extensions, recipe/cost, opening slots and legal placement before creating the prefab site/instance
- modified clients cannot substitute a cheaper prefab, shrink footprint, omit supports, invent openings, claim completion or bypass property/work requirements
- save/load restores prefab ID/version, transform, owner/property, construction progress, support/extensions, openings, installed objects, utilities, damage/condition and attachments
- prefab construction/placement/opening workflows must work with keyboard/mouse, Xbox-style controllers and PlayStation-style controllers
- performance rules: low-cost ghost, Nanite where compatible, optimized shell meshes where beneficial, no Actor per decorative sub-piece, no idle placement/snap Tick, World Partition/HLOD/relevancy integration

Detailed companion: `Docs/Prefab_PreBuilt_House_Construction_System.md`

## Episode Upgrade 15 — Buildable Master Blueprint & Shared Inheritance

**Classification:** UPGRADE — APPROVED

Approved:

- tutorial `BuildMaster` concept is adopted as canonical `BP_MW_Buildable_Master`
- common persistent-buildable lifecycle behavior moves into the master instead of being copied into Foundation/Wall/Floor/Door/Window/Prefab classes
- master centralizes stable Structure/Object ID, Buildable/Family/Variant identity, authoritative definition link, ownership/property hooks, construction-state lifecycle, persistence hooks, shared placement/removal/relocation lifecycle hooks, generic management/highlight hooks and other truly universal state
- master does **not** assume every child owns exactly one Static Mesh or one collision/snap layout
- suggested shared component roots are a generic Scene Root plus optional Visual/Collision/Query roots; children add the geometry/query components they actually need
- Blueprint inheritance remains shallow; Metaworld avoids deep chains of FoundationMaster -> WallMaster -> OpeningWallMaster -> variant-specific subclasses when components/data can express the same behavior
- Actor Components are preferred for reusable systems such as support, utilities, inventory/container behavior, security/locks, condition/damage or other cross-family capabilities when componentization reduces duplication
- Blueprint Interfaces remain canonical capability contracts and are not replaced by inheritance; `BPI_MW_BuildSnapProvider` and `BPI_MW_Interactable` continue to let unrelated classes expose common capabilities without cast chains
- data remains the preferred source for mesh/variant/configuration differences such as footprint, rotation, relocation, snap compatibility, support requirements, recipes, demolition policy, opening definitions, utility points and catalog metadata
- true family-specific behavior remains in specialized children/components: Foundation terrain support, Wall openings, Floor multi-story support, Door/Window runtime motion/security, Prefab logical sections/service points, etc.
- tutorial `Call to Parent Function` pattern becomes a formal lifecycle rule: child overrides must preserve required parent ownership/persistence/state logic unless a replacement is explicitly documented
- parent can expose small template hooks such as `ApplyDefinitionVisuals`, `ApplyConstructionStageVisuals`, `OnSupportRelationshipsChanged`, `OnRelocationCommitted` and `OnDemolitionCommitted` so children customize behavior without copying the full parent graph
- build preview/ghost remains a separate low-cost placement representation; preview does not instantiate every persistent component/system from `BP_MW_Buildable_Master`
- buildable children do not hardcode keyboard keys; input remains in Enhanced Input contexts/components so keyboard/mouse, Xbox-style and PlayStation-style controller paths invoke the same world lifecycle
- server authority remains unchanged: client child functions cannot grant ownership, completion, relocation, deletion or forged persistent state
- parent has no default permanent Tick requirement; idle structures remain event-driven/dormancy/relevancy/streaming friendly
- shared definition data should prevent thousands of placed pieces from duplicating heavy configuration state unnecessarily
- settled structures retain Nanite/HLOD/World Partition/scalability compatibility where applicable
- migration is incremental: create master -> move only truly common logic -> reparent one simple family -> test placement/persistence/ownership/removal/relocation -> migrate the rest -> remove duplicated child graphs only after verification
- mass-reparenting every buildable and deleting child logic in one unverified pass is rejected
- Python Editor tooling can later audit expected parent inheritance, overly deep inheritance chains, duplicated lifecycle graphs, accidental Tick, invalid mobility setup, missing policies and other architecture drift
- vertical slice must prove Foundation, Wall, Floor, Door/Window and one Prefab can share the common master lifecycle without breaking their specialized systems

Detailed companion: `Docs/Buildable_Master_Blueprint_Inheritance_Architecture.md`

---

# Current Phase 20 Construction Stack — Continued

`BP_MW_Buildable_Master + Components / Interfaces / Data`

`-> Build Catalog / Selection / Prefab Plans`

`-> Ghost Placement / Rotation / Orientation`

`-> Placement Footprint / Overlap / Slot-Occupancy Validation`

`-> Terrain / Foundation Support Sampling & Required Extensions`

`-> Property / Profession / Resource Validation`

`-> Foundation / Floor / Wall Snap Architecture`

`-> Modular Build OR Prefab Logical Structure`

`-> Wall Families & Structural Openings`

`-> Door / Window Installation`

`-> Supported Multi-Story Construction`

`-> Persistent Construction Site / Work Stages`

`-> Completed Structure / Prefab Shell + Logical World Data`

`-> Interactive Door / Window Runtime`

`-> Authorized Relocation / Move`

`-> Cancel / Dismantle / Authorized Demolition`

`-> Damage / Repair / Renovation / Utilities / Contracts later`

---

# Removal Principle

> Metaworld never treats removal as a universal delete key. Unfinished construction can be cancelled or dismantled under real permissions and salvage rules; completed structures use authorized deconstruction/demolition; hostile or accidental destruction uses the normal world damage/crime system. Structural dependencies, persistence, resources and multiplayer authority are always respected.

---

# Relocation Principle

> Metaworld lets players reorganize property without turning construction into unrestricted transform editing. Lightweight placed objects may move directly when authorized; installed and structural pieces respect attachments, support, utilities, property, labor and persistence. The client previews the destination, but the server commits the relocation transaction.

---

# Prefab Principle

> A pre-built house is a convenient construction plan, not a dumb giant prop. Metaworld may merge visual geometry for performance, but the authoritative prefab instance still knows its footprint, supports, construction recipe, openings, installed objects, utilities, ownership, damage/renovation zones and persistent relationships.

---

# Buildable Master Principle

> Use inheritance for true shared buildable identity and lifecycle, interfaces for capabilities, Actor Components for reusable systems, and data for variants. `BP_MW_Buildable_Master` exists to remove duplication—not to become a giant Blueprint containing every construction feature.

---

# Playlist Continuation Rule

Future playlist episodes can be appended to this Part 2 continuation until consolidation. Part 1 and Part 2 together are the canonical Phase 20 playlist intake log.