# Metaworld — Flooring & Multi-Story Structural Construction System

**Status:** Canonical / Approved Upgrade

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first

## Canonical Principle

Metaworld supports real vertical construction. Floors are structural buildable pieces that can be used at ground level and as upper-story floor/ceiling platforms when the world rules, property volume, support path and construction validation permit it.

Core rule:

> A second floor is not a free-floating placement. It must snap into a valid structural relationship and remain inside the property/build volume.

This system extends the existing `BPC_MW_BuildComponent`, `BPI_MW_BuildSnapProvider`, stable Buildable/Snap Point IDs, controller support and server-authoritative construction rules.

---

# 1. Floor Buildable Family

Recommended canonical family:

`Build.Family.Floor`

Initial variants can include:

- `Floor.Standard`
- `Floor.Reinforced`
- `Floor.Opening.Stair`
- `Floor.Opening.Utility` later
- additional sizes/material variants as approved

A Floor definition can include:

- Buildable ID
- Family/Variant ID
- width/length/thickness
- exact pivot/orientation standard
- collision geometry
- material/resource cost
- durability
- structural/support requirements
- provided Snap Types
- accepted Snap Types
- wall-edge snap points
- upper/lower support points
- stair/opening metadata where applicable
- property/build-volume cost
- Nanite/performance metadata
- persistence schema

Adding new floor styles should primarily add definitions/variants rather than duplicate the entire build system.

---

# 2. Ground-Level and Upper-Level Placement

A floor may be placed in more than one legitimate structural context.

## Ground / Foundation Context

A floor can snap to:

- approved foundation surface/edge points
- an existing structural grid
- another compatible floor edge

## Upper-Story Context

An upper floor can snap to:

- top-of-wall support points
- beams/columns/support frames later
- compatible floor-edge continuation points
- other approved structural support nodes

The exact allowed relationships come from Buildable Definition data and support metadata.

---

# 3. Multi-Story Snap Types

Use the existing tag/data-driven snap system rather than creating a permanent dedicated `FloorTrace` dependency for every floor type.

Useful snap types can include:

- `Build.Snap.Floor`
- `Build.Snap.Floor.Edge`
- `Build.Snap.Floor.Support`
- `Build.Snap.Wall.Top`
- `Build.Snap.Wall`
- `Build.Snap.Foundation`
- `Build.Snap.Stair`
- `Build.Snap.Roof` later

Example structural relationship:

`Foundation`
-> wall-edge snap
-> `Wall`
-> top support snap
-> `Upper Floor`
-> new wall-edge snaps
-> `Second-Story Wall`

The same `BPI_MW_BuildSnapProvider` contract exposes compatible floor/support points.

---

# 4. Floor Snap Provider

Floor actors can implement `BPI_MW_BuildSnapProvider` and expose stable snap points such as:

- `FloorEdge_North`
- `FloorEdge_East`
- `FloorEdge_South`
- `FloorEdge_West`
- `WallEdge_North`
- `WallEdge_East`
- `WallEdge_South`
- `WallEdge_West`
- `FloorSupport_Center` where relevant
- stair/opening points where relevant

Exact transforms are represented by Scene Components/sockets or equivalent data.

Query-Only Box Collision or another lightweight query volume can make those snap targets easier to acquire with both mouse and controller.

The acquisition box is not the structural truth. Stable IDs, exact transforms, compatibility tags and server validation are the structural truth.

---

# 5. Wall-to-Floor Vertical Snapping

Walls can expose top support snap points for upper floors.

Possible IDs:

- `FloorTop_North`
- `FloorTop_East`
- `FloorTop_South`
- `FloorTop_West`
- or a consolidated top-support grid depending on the modular kit

These points provide a compatible type such as:

`Build.Snap.Floor.Support`

A selected upper-floor definition accepts that type.

Flow:

`Camera/reticle targets upper wall/support`
-> query hit structure through `BPI_MW_BuildSnapProvider`
-> request compatible floor points
-> filter occupied/invalid candidates
-> choose best candidate
-> preview floor transform
-> validate support/property/collision
-> server revalidates
-> place persistent floor

---

# 6. Structural Support Chain

Multi-story buildings need a lightweight support model.

Initial support rule:

`Foundation / approved base support`
-> `Wall / Column / Beam support`
-> `Upper Floor`
-> `Higher Wall / Roof`

Every structural piece can store parent/support relationships.

The system does not need full real-world finite-element engineering, but it must prevent obvious invalid construction such as:

- upper floors floating with no support
- unsupported multi-story stacks
- floors surviving after all required supports are destroyed when the configured structural rules say they should fail

Future upgrades can add support graphs, beams, columns, load classes and structural damage propagation.

---

# 7. Property Height & Air-Rights Validation

Vertical building remains inside Metaworld's 3D property system.

Server checks can include:

- parcel footprint
- maximum build height
- vertical air-right volume
- zoning height restriction
- floor/story limits where configured
- neighboring/road/public-space encroachment
- parcel construction/performance budget
- permits for taller structures

Owning the ground does not automatically allow infinite height.

---

# 8. Floor Collision

Floor gameplay collision must:

- support walking where intended
- block falling through solid floor areas
- preserve intentional stair/elevator/utility openings
- work with NPC navigation where applicable
- not be confused with Query-Only snap acquisition collision

Simple collision is preferred where it correctly represents gameplay space.

Snap query volumes are separate from walkable/blocking floor collision.

---

# 9. Collision / Snap-Volume Tuning

The tutorial's manual Box Extent adjustment is approved as a content-tuning technique, not as a universal numeric rule.

Rules:

- keep snap-volume component scale at `1,1,1` where practical
- tune Box Extent per modular kit/piece
- avoid snap boxes reaching through walls/floors into unrelated targets
- prevent ambiguous overlapping snap zones where practical
- controller targeting must remain forgiving enough to use comfortably
- final validity comes from exact transform, occupancy, bounds, structural support and server collision validation

Do not rely on one magic extent value to make multi-story construction correct.

---

# 10. Floor Occupancy & Duplicate Prevention

Floor snap points and structural cells can track occupancy/reservation.

Reject:

- two normal floors occupying the same structural slot
- floor clipping through existing structural geometry
- duplicate placement caused by overlapping snap volumes
- floor placement into a space reserved for a stair/opening variant unless compatible

The server owns final occupancy state.

---

# 11. Floor Openings & Stairs

A complete multi-story system eventually needs vertical access.

Approved future floor variants include:

- stair opening
- ladder opening
- elevator shaft opening
- utility shaft opening

Like Door/Window wall openings, an opening-floor variant owns the structural opening while the stair/elevator/ladder can be a separate installed object when that architecture provides better replacement, damage and persistence behavior.

This prevents the player from creating a second story with no practical access unless that is deliberately allowed.

---

# 12. Controller Compatibility

Flooring and multi-story building must work with:

- keyboard/mouse
- Xbox-style controllers
- PlayStation-style controllers

Required controller-capable actions include:

- select Floor family/variant
- target upper support snap points
- cycle candidates where needed
- rotate
- toggle snapping
- confirm/cancel
- navigate floor/opening variants in the catalog

The system uses camera/reticle targeting and Enhanced Input rather than mouse-only cursor logic.

---

# 13. Multiplayer Authority

Client:

- previews floor locally
- selects Floor Buildable/Variant ID
- detects a candidate parent support/Snap Point ID
- displays green/red feedback

Server:

- resolves authoritative floor definition
- resolves authoritative parent/support Structure ID and Snap Point ID
- verifies snap compatibility and occupancy
- verifies support chain
- verifies property height/air rights/zoning
- verifies collision/obstruction
- verifies Builder/permit requirements
- verifies resources/cost
- places and persists the floor

A hacked client cannot create a second floor by sending arbitrary Z coordinates without a valid authoritative structural relationship.

---

# 14. Persistence

Upper floors require persistent structural relationships.

Store at minimum:

- Structure ID
- Buildable/Family/Variant ID
- transform
- property/owner ID
- story/floor-level metadata where useful
- parent/support Structure IDs
- Snap Point IDs
- occupancy relationships
- condition/damage
- openings
- construction state
- timestamp / Builder/contract data where relevant

Save/load must rebuild the multi-story support/snap graph consistently.

---

# 15. Story / Level Metadata

Metaworld may track a lightweight building-level identifier for UI, construction tools and persistence.

Example:

- Ground / Level 0
- Level 1
- Level 2
- etc.

This is descriptive metadata, not the structural authority by itself.

A valid support path and world transform remain authoritative.

Story metadata can later help:

- build catalog filters
- renovation
- utilities
- fire/emergency systems
- elevators/stairs
- property rental units
- room ownership
- NPC navigation
- HLOD/building management

---

# 16. Performance

Multi-story construction follows the existing smoothness rules:

- no build queries outside build mode
- query only hit/relevant structures
- no world-wide floor/snap scans
- Query-Only acquisition volumes
- timer/event-driven preview updates
- soft references/catalog caching
- support validation on meaningful placement/damage events rather than every frame
- idle structural pieces do not Tick merely because they are part of a support graph
- persistent finished structures participate in World Partition/HLOD/relevancy systems

---

# 17. Python Editor Tooling

Python can later audit:

- floor pivot/orientation consistency
- floor dimensions
- collision coverage
- intentional openings
- snap-point IDs
- wall-top/floor-edge compatibility
- duplicate snap points
- snap-volume extents
- missing support metadata
- invalid floor/opening definitions
- Nanite settings
- performance-cost metadata

Python remains Editor tooling, not runtime gameplay logic.

---

# 18. Initial Vertical-Slice Multi-Story Test

The first construction vertical slice should prove:

1. Ground foundation can be placed.
2. Standard wall can snap to foundation/floor edge.
3. Wall exposes upper-floor support points.
4. Floor ghost can target those support points.
5. Floor snaps at the correct height/orientation with no visible gap.
6. Query volume is easy to acquire with mouse and Xbox/PlayStation-style controllers.
7. Floor collision is walkable after placement.
8. Floor snap volume does not block movement.
9. Unsupported floating floor is rejected.
10. Duplicate floor in the same occupied structural slot is rejected.
11. Floor outside property vertical build volume is rejected.
12. Floor exceeding configured height/story/zoning rule is rejected.
13. Server resolves authoritative parent support/Snap Point rather than trusting raw client Z position.
14. Successful upper floor receives persistent Structure ID and support relationship.
15. Save/load restores the second story correctly.
16. Second-story walls can snap to the new upper floor.
17. At least a basic stair/opening path is reserved/tested for future vertical access.
18. Keyboard/mouse construction succeeds.
19. Xbox-style controller construction succeeds.
20. PlayStation-style controller construction succeeds.
21. Performance remains stable while building multiple stories.

---

# Core Rule

> Metaworld floors are real structural pieces, not decorative planes. Ground floors, upper floors and future floor openings use the same data-driven, interface-driven, controller-compatible and server-authoritative construction architecture. Multi-story buildings grow through valid support relationships inside the owner's legal 3D build volume, not through arbitrary floating placement.