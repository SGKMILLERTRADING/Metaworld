# Metaworld — Construction Rotation & Orientation Control System

**Status:** Canonical / Approved Phase 20 Upgrade

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first

## Canonical Principle

Buildable rotation is an explicit part of placement, snapping and accessibility rather than a pair of hardcoded keyboard keys.

Core rule:

> The Build Component owns requested placement orientation; the selected Buildable Definition and current snap relationship decide which rotations are legal.

The UE4 tutorial concepts of checking build mode, validating the ghost, rotating in both directions, and supporting held rotation are approved. Metaworld upgrades them for Enhanced Input, controllers, snapping, multiplayer authority, data-driven definitions and performance.

---

# 1. Input Architecture

Recommended Enhanced Input actions:

- `IA_MW_BuildRotateLeft`
- `IA_MW_BuildRotateRight`
- optional `IA_MW_BuildFineRotate`
- optional `IA_MW_BuildResetRotation`

Do not permanently bind construction logic to Q/E.

Keyboard/mouse, Xbox-style controllers and PlayStation-style controllers require equivalent rotation actions. Suggested defaults can use keyboard keys, gamepad shoulder/trigger buttons, D-pad actions or stick-based fine rotation, but physical bindings remain rebindable.

Rotation input is consumed by Build Mode before normal world interaction when the construction input context is active, preventing conflicts such as a key attempting both Rotate and Interact/Build Work at the same time.

---

# 2. Rotation Preconditions

Rotation requests are processed only when:

1. Build Mode is active.
2. A valid selected Buildable Definition exists.
3. A ghost/placement candidate exists where required.
4. The selected buildable permits player rotation.
5. The current placement/snap mode permits the requested rotation.

Invalid requests do nothing and should provide a clear reason where useful.

---

# 3. Step Rotation

Structural pieces should normally use deterministic step rotation.

Definition fields can include:

- `RotationMode`
- `RotationStepDegrees`
- `AllowedYawValues`
- `AllowPitchRotation`
- `AllowRollRotation`
- `ResetRotationOnSelectionChange`

Examples:

- foundation: 90° step
- modular wall: orientation primarily determined by snap edge, optional compatible flip
- floor: 90° step
- stair: configured orientations
- rectangular furniture: 15° / 45° / 90° according to product

Step rotation is preferred for modular structural systems because it preserves alignment and deterministic server validation.

---

# 4. Fine / Continuous Rotation

Eligible free-placement objects may support held or analog rotation.

Definition fields can include:

- `AllowFineRotation`
- `FineRotationSpeedDegreesPerSecond`
- `FineRotationAxis`
- `FineRotationClamp/Range` where applicable

The tutorial's gate + delay loop is not the canonical implementation. Enhanced Input provides pressed/held/axis state; the Build Component updates orientation only while relevant input is active and Build Mode is active.

Do not create a permanent `0.01 second` timer loop for every player. Rotation responsiveness and update cadence are profile-driven.

---

# 5. Snap-Aware Rotation

Snapping does not automatically disable rotation.

Each Snap Point/Buildable relationship can define orientation behavior such as:

- `SnapRotation.Locked`
- `SnapRotation.Flip180`
- `SnapRotation.QuarterTurn`
- `SnapRotation.AllowedVariants`
- `SnapRotation.FreeYaw` for special cases

Examples:

- wall snapped to foundation edge: edge determines base orientation; player may flip inward/outward if allowed
- door/window installed in an opening: opening defines alignment; hinge side/inside-outside variant can be selectable if data allows
- floor snapped to support: limited quarter-turns may be allowed
- furniture snapped to wall socket: orientation may be locked to the surface normal

The Build Component combines the authoritative snap transform with an allowed user orientation offset instead of letting raw arbitrary rotation break the snap relationship.

---

# 6. Placement Transform Model

Recommended placement orientation state:

- `BasePlacementTransform`
- `SnapBaseRotation`
- `UserRotationOffset`
- `ResolvedPlacementRotation`

Concept:

`Resolved Rotation = Legal Snap/Base Rotation + Validated User Rotation Offset`

Do not accumulate uncontrolled floating-point rotation forever through repeated raw `Combine Rotators` calls. Normalize/clamp rotation and derive the final orientation from explicit state.

---

# 7. Ghost Feedback

When rotation changes:

- ghost orientation updates immediately
- collision/footprint validation reruns
- snap compatibility/occupancy reruns where rotation matters
- property/build-volume bounds rerun where orientation changes footprint
- green/red/warning state refreshes

A rotation that makes a previously valid placement collide with a wall or leave the property volume must turn the preview invalid.

---

# 8. Multiplayer Authority

Client rotation is responsive preview state only.

Placement request includes the selected Buildable/Variant identity, parent/snap identity where used, and proposed orientation/transform.

Server independently resolves:

- Buildable Definition
- allowed rotation mode
- allowed step/axis/range
- parent Snap Point/orientation rules
- final normalized orientation
- collision/property/support validation

A modified client cannot place a wall at an illegal arbitrary angle simply by sending a forged transform.

---

# 9. Persistence

Completed/persistent structures store their authoritative final transform/orientation.

Where meaningful, records may also store:

- selected orientation variant
- hinge/facing choice
- parent Snap Point
- rotation offset relative to parent

Save/load restores identical orientation and snap relationships.

---

# 10. Controller UX

Controller construction must support:

- rotate left/right
- held rotation where allowed
- step rotation
- fine rotation where allowed
- reset orientation where provided
- visible device-appropriate prompts

Structural build rotation should remain predictable on gamepad. Analog fine rotation must have configurable sensitivity/dead zone and must not be required for pieces designed around discrete snapping.

---

# 11. Performance

- no rotation update when Build Mode is off
- no high-frequency timer loop solely to poll rotation input
- use Enhanced Input events/active-axis state
- rerun only the placement checks affected by orientation
- snap candidate searches remain targeted to relevant structures
- normalize rotation rather than accumulating unlimited deltas

---

# 12. Initial Vertical-Slice Tests

1. Enter Build Mode and rotate a valid ghost left/right.
2. Rotation input is ignored outside Build Mode.
3. Structural foundation rotates in configured steps.
4. Wall snapped to an edge obeys snap orientation and only exposes permitted flip/rotation choices.
5. Free-placement prop supports smooth held/fine rotation if its definition allows it.
6. Rotating into an obstruction changes preview to invalid.
7. Rotating outside property/build volume is rejected.
8. Server rejects a forged illegal rotation.
9. Save/load preserves final orientation.
10. Keyboard/mouse rotation works.
11. Xbox-style controller rotation works.
12. PlayStation-style controller rotation works.
13. Rotation input does not accidentally trigger Build Work/Interact while Build Mode owns that control context.
14. No permanent high-frequency rotation polling occurs while idle.

---

# Core Rule

> Metaworld rotation is data-driven, snap-aware, controller-compatible and server-validated. Structural pieces favor deterministic rotation steps; eligible free-placement pieces may use fine/continuous rotation; snapping constrains orientation rather than disabling rotation outright.