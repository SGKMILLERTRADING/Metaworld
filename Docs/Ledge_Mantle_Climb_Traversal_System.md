# Metaworld — Ledge, Mantle & Climb Traversal System

**Status:** Canonical / Approved Modern RPG Playlist Upgrade

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first / server-authoritative traversal state / animation-integrated / controller-complete

## Canonical Principle

Ledge climbing is a contextual traversal action with validated entry, hang, climb-up, drop and interruption states. Authored overlap volumes may be used for specific known ledges, but the character never gains unrestricted flight because an engine movement mode is used underneath the traversal.

> Ledges are traversal affordances, not teleport boxes. Gameplay validates the target; animation/root motion/Motion Warping present the move.

Related canon:

- `Docs/Ladder_Climbing_Traversal_System.md`
- `Docs/Animation_Authoring_Control_Rig_Root_Motion_Workflow.md`
- `Docs/Avatar_Communication_Character_Animation_Architecture.md`
- `Docs/Movement_Sprint_Stamina_Regeneration_Exertion_System.md`
- `Docs/Controller_Input_Compatibility_Architecture.md`

---

# 1. Ledge Traversal Identity

Authored ledges may use a stable TraversalObjectID/Profile with:

- ledge type/tag;
- approach volume / candidate bounds;
- facing direction;
- grab target transform;
- hang line/path;
- climb-over landing target;
- clearance bounds;
- animation profile;
- stamina/encumbrance requirements;
- allowed directions/actions;
- visual-marker profile.

Dynamic ledge detection through traces/geometry analysis may be added later under the same traversal contract. The tutorial's overlap-based authored ledges are a valid first implementation, not the only future form.

---

# 2. State Model

Suggested semantic states:

- NotTraversing
- ApproachingLedge
- GrabbingLedge
- Hanging
- ClimbingUp
- Dropping/Falling
- Interrupted.

The traversal component owns this state.

`MOVE_Flying` or other engine movement modes may be temporarily used to suppress gravity/constrain movement while hanging, but they never mean the player possesses free-flight capability.

---

# 3. Eligibility

Server/gameplay can validate:

- ledge candidate is reachable;
- character is facing/approaching correctly;
- grab target is clear;
- top landing space is clear;
- character state allows traversal;
- carried load/Encumbrance permits it;
- Stamina/injury/status rules permit it;
- hands are available where required;
- target is not destroyed/invalid;
- other traversal/action locks do not conflict.

Do not allow another interaction to start while the character is in a non-interruptible ledge montage/state.

---

# 4. Entry / Grab

Preferred flow:

`Request Ledge Grab`
-> validate ledge/target
-> align to authored/detected grab transform
-> apply traversal movement/collision policy
-> play grab montage/transition
-> enter Hanging.

Motion Warping/root motion can align the character to the exact ledge rather than relying on hardcoded world offsets.

---

# 5. Hanging

While Hanging:

- normal locomotion is suspended;
- gravity/movement follows traversal policy;
- character remains constrained to valid hang position/path;
- camera remains usable according to profile;
- Stamina may drain if the final design requires it;
- heavy load can increase drain or disallow hanging;
- animation/IK can maintain hand contact.

Future shimmying can extend the hang path without changing the state contract.

---

# 6. Climb Up

`Request Climb Up`
-> revalidate landing clearance
-> set Motion Warp/root-motion target
-> play climb-up montage
-> restore normal movement/collision at the authored phase
-> exit traversal state.

Root motion determines authored body movement; gameplay still validates the destination.

---

# 7. Drop / Let Go

Drop is an explicit action.

`Request Drop`
-> release ledge constraint
-> restore Falling movement/collision
-> apply appropriate initial velocity/state
-> normal fall/damage rules resume.

Do not teleport the character downward or leave the character in Flying/no-gravity state.

---

# 8. Visual Ledge Markers / Decals

Decals are approved as an optional readability/accessibility layer.

Possible marker policies:

- authored paint/chalk/brush mark;
- subtle environmental wear;
- accessibility-highlight mode;
- mission/tutorial-specific marker;
- no marker for realistic/hardcore profiles where deliberate.

Marker presentation must not be the actual traversal eligibility test. A decal can be hidden/disabled while the ledge remains usable, or displayed decoratively only where the traversal profile says it is climbable.

Character materials/meshes should be configured so projected decals do not produce unwanted artifacts on the player where necessary.

---

# 9. Controller / Input

Required actions can include:

- interact/grab where authored interaction is used;
- climb up;
- drop/let go;
- future shimmy left/right;
- camera look;
- cancel where valid.

All must support KBM, Xbox-style and PlayStation-style mappings through Enhanced Input.

---

# 10. Multiplayer / Authority

Server owns traversal state and validates grab/climb/landing.

Clients can animate responsively but cannot declare a successful mantle onto an invalid/blocked ledge simply by playing root motion locally.

Compact traversal target/state data is replicated; normal character movement/networking handles position reconciliation.

---

# 11. NPC / AI Compatibility

Authored ledges can later expose navigation/Smart Object traversal links for capable NPCs.

NPCs that cannot use the ledge respect it as blocked terrain.

Distant NPC traversal may resolve abstractly when off-screen rather than evaluating expensive animation.

---

# 12. Performance

- authored ledge volumes do not Tick;
- eligibility checks happen for bounded/current candidates;
- IK/root-motion work runs only during traversal;
- decals are budgeted/cullable and not required on every ledge;
- dynamic detection, if added later, uses bounded traces rather than global scans.

---

# 13. Acceptance Tests

1. Invalid-facing/blocked ledge cannot be grabbed.
2. Character aligns to the ledge without arbitrary free-flight movement.
3. Hanging state cannot trigger unrelated interactions accidentally.
4. Climb-up revalidates landing space.
5. Drop restores Falling and normal gravity cleanly.
6. Interruption cannot leave no-collision/Flying state stuck.
7. Encumbrance/Stamina rules can affect traversal.
8. Decal can be disabled without changing traversal truth.
9. Player mesh does not receive unwanted ledge decal artifacts where configured.
10. KBM/Xbox-style/PlayStation-style traversal works.
11. Multiplayer client cannot mantle to an invalid target by faking animation.

## Core Rule

> A Metaworld ledge is a validated traversal opportunity. Overlap volumes, decals, root motion and Motion Warping are tools for detection/presentation; the authoritative traversal state decides whether the character may grab, hang, climb or drop.