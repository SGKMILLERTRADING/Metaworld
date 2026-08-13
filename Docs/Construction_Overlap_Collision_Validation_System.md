# Metaworld — Construction Overlap & Collision Validation System

**Status:** Canonical / Approved Phase 20 Upgrade

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first

## Canonical Principle

Metaworld prevents buildables from occupying invalid physical space by using explicit, data-driven placement footprints and authoritative obstruction validation.

Core rule:

> The ghost may predict whether a placement is clear, but the server decides whether the requested construction volume is actually free.

The UE4 tutorial concepts of checking overlap, turning the ghost red/green, preferring simple collision, validating build mode before selection updates, and fixing pivot-related false positives are approved. Metaworld upgrades them into a scalable placement-footprint system that does not depend on the Visibility channel, one magic bounds multiplier, or render-mesh bounds as the final truth.

---

# 1. Placement Footprint vs Render Mesh

A buildable's visible mesh is not automatically its authoritative placement volume.

Each Buildable Definition may provide explicit construction-obstruction data such as:

- `PlacementFootprintType`
- one or more local Box volumes
- Capsule volumes where useful
- simple convex collision where justified
- local offset
- local rotation
- clearance margin
- allowed penetration/tolerance where intentionally needed
- ignored overlap categories
- blocking overlap categories
- support/contact zones
- opening/attachment exclusion zones
- construction-stage footprint override where required

Examples:

- a floor may use a shallow footprint volume that does not penetrate the ground below it
- a wall may use a thin rectangular obstruction volume matching the actual wall thickness
- a door may use both a closed-body footprint and a separate movement-swing clearance test
- a staircase may require a compound footprint rather than one giant bounding box
- decoration may allow limited surface intersection while a structural foundation does not

The render mesh bounds remain useful for authoring/debugging, but they are not the universal placement rule.

---

# 2. Local Ghost Validation

While Build Mode is active, `BPC_MW_BuildComponent` may run a lightweight candidate obstruction check for the current ghost.

Recommended flow:

`Candidate Transform`
-> resolve selected Buildable Definition/Variant
-> transform configured placement footprint into world space
-> query Build Obstruction profile/channel
-> ignore the local preview actor itself
-> ignore explicitly permitted support/snap parent geometry where the snap contract allows contact
-> inspect blocking results
-> set local placement reason/state
-> update ghost material/feedback

Minimum visual feedback:

- Green = locally valid candidate
- Red = blocked/invalid
- optional Yellow/Amber = conditional/warning state

The local result is advisory only.

---

# 3. Authoritative Server Revalidation

When the client confirms placement, the server independently resolves:

- Buildable ID
- Variant ID
- parent Structure ID where used
- Snap Point / Opening / Support ID where used
- requested transform/orientation
- authoritative placement footprint
- property/build-volume rules
- authoritative world obstruction state

The server reruns obstruction validation before consuming resources or creating the permanent Construction Site/Structure.

The client cannot make an overlapping build valid by changing its local `CanBuild`, ghost color, collision responses, bounds or trace result.

---

# 4. Query Profile Policy

The tutorial uses the Visibility channel for overlap testing. Metaworld should instead use a small dedicated construction-query family where practical.

Recommended profiles/channels can include:

- Build Placement Query
- Build Snap Query
- Build Obstruction Query

High-level decisions remain data/tag/relationship driven.

Do not overload Visibility merely because it is convenient in a prototype. Construction queries should avoid interfering with cameras, weapons, ordinary interaction and unrelated traces.

---

# 5. Simple Collision Preference

Simple collision is preferred for construction obstruction and ordinary gameplay where it accurately represents the required shape.

Benefits:

- cheaper queries
- predictable placement behavior
- easier debugging
- cleaner server/client consistency
- fewer surprises from detailed decorative geometry

Complex/per-poly collision may still be used where deliberately justified, but construction validity should not accidentally depend on tiny decorative triangles, bevels, bolts, trim or invisible mesh detail.

A buildable with no reliable simple/explicit placement footprint is an asset-authoring problem, not something the runtime system should hide forever with arbitrary trace multipliers.

---

# 6. No Magic Bounds Multiplier

The tutorial's idea of shrinking component bounds with a value such as `0.2` can reduce false positives in a specific kit, but no global multiplier is canonical.

Metaworld instead supports explicit per-definition tolerances such as:

- `ClearanceMargin`
- `ContactTolerance`
- `SnapPenetrationTolerance`
- per-volume extents

A foundation that intentionally contacts terrain needs different tolerance from a wall, floor, pipe, door, furniture item or utility fixture.

---

# 7. Snap-Aware Overlap Validation

Valid snapping often means two structures intentionally touch.

Therefore overlap validation must understand the selected structural relationship.

Examples:

- wall touching foundation edge = expected contact
- upper floor touching wall-top support = expected contact
- door frame occupying its designated wall opening = expected contact
- door panel embedded through neighboring solid wall = invalid
- two walls occupying the same exclusive edge = invalid
- two floors occupying the same structural slot = invalid

When a snap relationship is used, the validator receives the authoritative parent Structure ID and Snap/Open/Support ID so approved contact can be distinguished from illegal overlap.

---

# 8. Occupancy vs Physical Overlap

Metaworld uses both concepts.

## Occupancy

Logical reservation of an exclusive structural slot.

Examples:

- wall edge already occupied
- door opening already contains a door
- floor support cell already owns a floor

## Physical Overlap

World-space geometry/footprint conflicts.

A placement can fail either test.

This prevents a client from passing a geometric gap while still trying to use an already-reserved logical snap slot.

---

# 9. Pivot & Origin Standards

Bad asset pivots can cause valid objects to appear embedded into terrain or other structures.

Every construction asset should follow consistent authoring standards for:

- pivot/origin location
- forward axis
- up axis
- bottom/contact plane
- snap-origin transform
- closed/default transform where interactive
- placement-footprint local offsets

Per-asset offsets are allowed when intentionally recorded in data, but unexplained pivot fixes scattered through Blueprints are not the normal workflow.

Python Editor tooling can later audit suspicious pivots, placement volumes and footprint-to-mesh alignment.

---

# 10. Build Mode / Selection Safety

Selection, cycling and preview-update functions must validate that Build Mode and the required selected/ghost state exist before accessing construction-preview references.

Approved checks include:

- Build Mode active
- selected Buildable ID valid
- selected definition resolved
- preview/ghost exists where the action requires it

This prevents mouse-wheel/controller cycling or other build inputs from dereferencing a missing preview actor while Build Mode is inactive.

The same rule applies to keyboard/mouse, Xbox-style and PlayStation-style controller inputs.

---

# 11. Rotation Revalidation

Every meaningful ghost rotation/orientation change reruns obstruction validation using the rotated placement footprint.

A long rectangular object may be valid at 0 degrees and invalid at 90 degrees.

The validator must therefore use the resolved final candidate transform rather than checking only the original unrotated bounds.

---

# 12. Construction-Stage Integration

Placement obstruction determines whether an authorized Construction Site may reserve the location.

Once placed:

- the site retains logical reservation/occupancy
- stage-specific physical collision follows what is actually constructed
- later construction stages do not reopen the reserved slot for another overlapping build

This integrates with `Docs/Construction_Progress_Build_To_Completion_System.md`.

---

# 13. Doors, Windows & Moving Clearance

Installed doors/windows require two distinct ideas:

1. placement footprint / opening compatibility
2. runtime motion clearance

A door can fit correctly into its opening yet have something placed directly in its swing arc later.

Future validation can include a `MotionClearanceVolume` for applicable movable objects.

This does not need to block all neighboring placement universally; each object definition can decide whether motion clearance must remain free, whether the door may stop against an obstruction, or whether another movement model applies.

---

# 14. Performance Rules

- no construction overlap queries when Build Mode is inactive
- query only the current candidate footprint, not every buildable in the area manually
- use targeted shape overlaps/traces and filtered collision profiles
- prefer simple collision/explicit lightweight footprint shapes
- do not run world-wide overlap scans
- do not recompute static footprint metadata every update
- cache selected definition footprint data
- server revalidates only meaningful placement/renovation requests
- finished static structures do not run continuous overlap checks

---

# 15. Python Editor Validation

Python tooling can later audit:

- Buildable Definitions missing placement footprint data
- footprint volumes extending far outside the visible mesh without an explicit reason
- floor footprints extending below the intended contact plane
- duplicate/invalid footprint IDs if compound shapes use IDs
- missing simple collision on structural buildables
- construction assets set to unsuitable collision complexity
- suspicious pivot/origin placement
- placement footprint vs snap transform mismatch
- door/window footprint intruding into required opening space
- missing obstruction profile assignment
- inconsistent collision responses

Python remains Editor tooling, not packaged runtime validation logic.

---

# 16. Initial Vertical-Slice Tests

The first construction slice should prove:

1. Ghost turns red when a wall physically overlaps another occupied wall/structure.
2. Ghost remains green for valid wall-to-foundation contact through an approved snap point.
3. Rotating a rectangular piece can change Green -> Red or Red -> Green based on the real footprint.
4. A floor resting correctly on its support does not remain permanently red because its render bounds slightly penetrate the support plane.
5. A floor with an intentionally bad test pivot is detected by asset QA rather than patched with a universal runtime multiplier.
6. Duplicate occupied snap slot is rejected even if raw geometric overlap would otherwise pass.
7. Server rejects an overlap that a modified client falsely reports as valid.
8. Client cannot change the authoritative footprint by modifying its preview mesh.
9. Build selection/cycling while Build Mode is off does not cause missing-ghost errors.
10. Simple collision/explicit footprint queries remain stable with many nearby modular pieces.
11. Keyboard/mouse, Xbox-style controller and PlayStation-style controller can all select, rotate and confirm/reject candidates correctly.
12. Save/load preserves the resulting non-overlapping authoritative structures and slot occupancy.

---

# Core Rule

> Metaworld does not decide construction validity from a mesh's appearance alone. Every buildable has an explicit physical placement footprint and structural occupancy rules; the local ghost predicts obstruction for responsive feedback, and the server independently validates the authoritative world before construction is allowed.