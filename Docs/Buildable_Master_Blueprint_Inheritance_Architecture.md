# Metaworld — Buildable Master Blueprint & Inheritance Architecture

**Status:** Canonical / Approved Phase 20 Upgrade

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first

## Canonical Principle

Metaworld uses a shared Blueprint parent for common buildable lifecycle behavior, but keeps specialized systems modular through Actor Components, Blueprint Interfaces and data-driven definitions.

Core rule:

> `BP_MW_Buildable_Master` centralizes what every persistent buildable truly shares; family-specific behavior remains composed, data-driven or overridden in shallow child classes.

The UE4 tutorial concept of creating one `BuildMaster`, reparenting Foundation/Wall/Floor/Door/House children, removing duplicated interface logic, and calling parent implementations before child-specific behavior is approved. Metaworld upgrades it into a shallow-inheritance architecture designed for a large persistent multiplayer world.

---

# 1. Canonical Parent

Recommended canonical actor:

`BP_MW_Buildable_Master`

It is the base Blueprint Actor for persistent placeable/buildable world objects that share the common construction lifecycle.

Typical descendants can include:

- foundations
- walls
- floors
- roofs
- stairs
- support piers/columns
- installable doors/windows where the common lifecycle is useful
- utility devices
- furniture/placeable equipment where appropriate
- prefab root actors
- future construction families

Not every lightweight logical prefab sub-piece needs to be an Actor merely to inherit from this class. Prefabs may keep noninteractive sections as data records.

---

# 2. What Belongs in the Master

The parent should contain only behavior/data that is genuinely common across most persistent buildables.

Recommended shared responsibilities:

- stable persistent `StructureID` / `ObjectID`
- authoritative `BuildableID`
- Family / Variant identity
- resolved Buildable Definition reference or lightweight cached definition data
- owner / property / organization relationship hooks
- construction-state lifecycle
- basic condition/damage-state hooks where universal
- construction-site vs completed-state flag/state machine
- common persistence serialization/deserialization hooks
- common server-authoritative placement completion hook
- generic management/selection/highlight hooks
- common deletion/deconstruction transaction hooks
- common relocation transaction hooks
- common creator/material identity hooks where applicable
- common replication/dormancy setup where appropriate
- generic event dispatchers for lifecycle changes
- shared debug identity output

The parent should not assume that every child has exactly one Static Mesh Component, one snap box, one door panel or one collision layout.

---

# 3. Suggested Shared Component Layout

A minimal parent can expose a stable component structure such as:

- `SceneRoot`
- `BuildVisualRoot` — Scene Component parent for visual components
- optional `BuildCollisionRoot` — Scene Component parent for gameplay collision components
- optional `BuildQueryRoot` — Scene Component parent for snap/interaction/query-only components

Child Blueprints may add:

- Static Mesh Components
- Skeletal Mesh Components where justified
- multiple door/window panels
- Box/Sphere/Capsule query volumes
- Scene Components/sockets for snap points
- support sample markers
- utility connectors
- audio/VFX components

Do not force every child to carry unused components merely because another family needs them.

---

# 4. Composition Over Giant Inheritance Trees

Metaworld prefers shallow inheritance plus reusable components.

Approved examples:

`BP_MW_Buildable_Master`

+ construction lifecycle/state component if separated

+ support component for terrain/support-bearing pieces

+ snap-provider component/data where useful

+ utility connection component for powered/plumbed devices

+ security/lock component for doors/windows where useful

+ inventory/container component for storage objects

+ damage/condition component where system complexity justifies it

The architecture should avoid deep chains such as:

`BuildMaster -> StructuralMaster -> WallMaster -> OpeningWallMaster -> DoorWallMaster -> ReinforcedDoorWallMaster -> ...`

when data/variants/components can express the same differences more cleanly.

One or two shallow family layers are acceptable when they remove real duplicated behavior.

---

# 5. Blueprint Interfaces Remain Important

A parent class does not replace Metaworld's Blueprint Interfaces.

Interfaces remain the correct contract when unrelated classes can provide the same capability.

Existing examples:

- `BPI_MW_BuildSnapProvider`
- `BPI_MW_Interactable`

Future capability interfaces may be added where useful.

Reason:

- a wall, floor, prefab and utility rack may all expose snap points without sharing a specific family child class
- a door, ATM, appliance and terminal may all be interactable without sharing a construction subclass
- interface callers should not need to cast through every buildable family

The master handles shared lifecycle. Interfaces describe capabilities.

---

# 6. Parent Function / Event Discipline

The tutorial's `Call to Parent Function` pattern is approved and becomes a formal rule for lifecycle overrides.

When a child overrides a master lifecycle event/function, the child must preserve required parent behavior unless the override is explicitly documented as replacing it.

Examples:

`OnDefinitionResolved`

Parent:
- cache canonical identity/state
- apply shared metadata
- initialize generic lifecycle state

Child Foundation:
- call Parent
- initialize support sample configuration

`OnConstructionStageChanged`

Parent:
- persist stage
- update generic construction state
- dispatch lifecycle notification

Child Door:
- call Parent
- enable/disable panel interaction if the current stage physically permits it

`OnAuthoritativePlacementCommitted`

Parent:
- assign persistent relationship data
- register generic persistence/ownership state

Child Prefab:
- call Parent
- register prefab logical sections/openings/service points

A child should not silently bypass parent ownership, persistence or server-state logic merely because it has custom visuals.

---

# 7. Prefer Template Hooks Over Copy/Paste

Where children need customization, the master can expose intentionally small overridable hooks rather than forcing children to duplicate the full event.

Examples:

- `ApplyDefinitionVisuals`
- `ApplyConstructionStageVisuals`
- `RefreshFamilySpecificCollision`
- `OnBuildableActivated`
- `OnBuildableDeactivated`
- `OnSupportRelationshipsChanged`
- `OnInstalledAttachmentChanged`
- `OnRelocationCommitted`
- `OnDemolitionCommitted`

The parent can run the universal transaction and then invoke the hook.

This pattern is preferred over copying a large parent graph into every child.

---

# 8. Data-Driven Family Differences

Many differences should remain Buildable Definition data rather than child Blueprint code.

Examples:

- Buildable ID
- Family / Variant ID
- mesh/visual assets
- material configuration
- Nanite/performance metadata
- footprint volumes
- rotation policy
- relocation policy
- snap compatibility
- support requirements
- construction recipe/work units
- demolition/salvage policy
- durability/condition values
- opening definitions
- utility service points
- catalog information

A new wall color/material/size variant should normally not require another new child Blueprint if data can represent it safely.

---

# 9. Family-Specific Behavior

Child/family Blueprint logic remains valid when behavior is truly different.

Examples:

## Foundation

- terrain support sampling
- automatic support extensions
- support-chain registration

## Wall

- wall-edge relationships
- structural opening metadata

## Door / Window

- runtime open/close motion
- multi-panel movement
- lock/security state
- opening attachment relationship

## Floor

- upper-story support relationships
- floor/wall snap points
- walkable/opening collision

## Prefab

- prefab logical section registration
- multiple support samples
- openings/utility/service points
- logical damage/renovation zones

These behaviors may call shared parent lifecycle hooks and then run their specialized logic.

---

# 10. Build Preview Is Separate

`BP_MW_Buildable_Master` is the persistent world-object parent. The temporary placement ghost should remain a low-cost preview representation rather than spawning the full finished object with every expensive runtime system enabled.

The ghost can use:

- selected Buildable/Variant identity
- simplified mesh/material representation
- placement footprint
- rotation policy
- snap/support preview data
- required extension previews
- blocked reason

Do not instantiate every persistent component, inventory, utility, security or NPC-related behavior merely to preview placement.

---

# 11. Server Authority

The shared parent architecture does not move authority to clients.

Server-authoritative operations remain responsible for:

- resolving Buildable/Variant definition
- creating persistent identity
- ownership/property assignment
- construction-state progress
- placement completion
- relocation commit
- demolition/deconstruction commit
- authoritative damage/condition state where applicable
- support/snap/opening relationship mutation
- persistence updates

A client calling a child Blueprint function cannot grant itself ownership, completion, relocation or deletion authority.

---

# 12. Replication & Performance

The master must not become a reason every buildable Actor ticks or replicates continuously.

Rules:

- no default permanent Tick unless a specific child truly needs it
- idle structures should use dormancy/relevancy/streaming-friendly state where appropriate
- state changes are event-driven
- Timeline/motion only runs for active moving parts such as doors/windows
- support calculations run on placement/damage/relationship events, not continuously
- Build Mode preview logic remains on the player's Build Component/ghost path, not every finished structure
- data shared by thousands of pieces should come from definitions rather than duplicated expensive runtime state where possible
- Nanite/HLOD/World Partition compatibility remains a priority

---

# 13. Asset/Blueprint Organization

Suggested structure:

`Content/Metaworld/Blueprints/Construction/Core/BP_MW_Buildable_Master`

Possible family areas:

`.../Construction/Foundation/`

`.../Construction/Wall/`

`.../Construction/Floor/`

`.../Construction/Openings/`

`.../Construction/Prefab/`

`.../Construction/Utilities/`

Exact folders can be adjusted to the project, but the master/family distinction should remain clear.

---

# 14. Migration Strategy

Existing tutorial-derived or prototype buildables should be migrated deliberately.

Recommended order:

1. create `BP_MW_Buildable_Master`
2. move only truly common lifecycle logic into it
3. identify duplicated interface/function graphs
4. reparent one simple class first, e.g. Foundation or basic Wall
5. test construction, persistence, ownership, removal and relocation
6. reparent remaining compatible families
7. for every override, verify required Parent call
8. remove duplicated child graphs only after behavior is confirmed
9. move configurable differences into definitions/data
10. move reusable capability behavior into components/interfaces where appropriate

Do not mass-reparent every class and delete all child logic in one unverified pass.

---

# 15. Python Editor Audit

Python Editor tooling can later audit:

- construction Blueprints not deriving from the expected master where policy requires it
- deep inheritance chains
- duplicate lifecycle implementation patterns
- child overrides missing documented parent-call requirements where detectable
- invalid Buildable IDs/definitions
- components that should be data-driven
- accidental default Tick on large static families
- inappropriate mobility settings
- missing persistence/relocation/removal policies

Python remains Editor automation, not packaged runtime gameplay.

---

# 16. Controller Compatibility

This architecture is input-neutral.

Buildable Actors expose world capabilities/state; player input remains in Enhanced Input contexts/components.

Therefore no buildable child should hardcode keyboard keys such as Q/E/1 internally for placement, relocation, demolition or interaction.

Keyboard/mouse, Xbox-style controller and PlayStation-style controller all invoke the same high-level actions and authoritative buildable lifecycle.

---

# 17. Initial Acceptance Test

The Phase 20 vertical slice should prove:

1. Foundation, Wall, Floor, Door/Window and one Prefab all share the common master lifecycle where appropriate.
2. Changing a common lifecycle behavior in `BP_MW_Buildable_Master` affects compatible children without editing each child.
3. Foundation-specific terrain support still works.
4. Wall opening/snap behavior still works.
5. Floor multi-story support still works.
6. Door/window interaction/motion still works.
7. Prefab logical openings/supports still work.
8. Child-specific overrides preserve required parent behavior.
9. Buildable identity/ownership/persistence survives save/load.
10. Relocation and demolition use the same shared lifecycle without bypassing family-specific validation.
11. No finished static structure gains unnecessary permanent Tick merely because it inherits from the master.
12. Keyboard/mouse, Xbox-style and PlayStation-style controller workflows remain unchanged because input is not hardcoded in the buildable hierarchy.

---

# Core Rule

> Use inheritance for true identity/lifecycle reuse, interfaces for capabilities, components for reusable systems, and data for variants. `BP_MW_Buildable_Master` should make Metaworld construction easier to maintain—not become the place where every construction feature is piled into one Blueprint.