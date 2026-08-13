# Metaworld — Pushable Object, Pressure Plate & Physics Puzzle System

**Status:** Canonical / Approved Modern RPG Playlist Upgrade

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first / server-authoritative world state / physics-aware / puzzle-integrated / controller-complete

## Canonical Principle

Pushable blocks and pressure plates are reusable world-object capabilities that feed persistent puzzle/world logic. Physics and animation make the interaction physical; the world-state system decides whether a valid block occupies a valid plate and which output changes.

> The player pushes a real world object. The plate observes a valid occupancy condition. Puzzle outputs react to committed world state—not to one fragile overlap branch in a Player Blueprint.

---

# 1. Pushable Object Identity

Suggested world capability:

`Object.Capability.Pushable`

A pushable object may define:

- WorldObjectID;
- mass/weight class;
- allowed translation axes;
- rotation restrictions;
- friction/physics material;
- push interaction profile;
- required strength/skill/team size;
- allowed surfaces;
- condition/damage state;
- puzzle tags/accepted plate classes;
- attached traversal features where valid.

---

# 2. Push Eligibility

A push begins only if:

- player is grounded when required;
- player is correctly positioned/facing the valid push side;
- object is movable and not reserved/locked;
- destination direction is not immediately blocked;
- character state permits pushing;
- strength/stamina/encumbrance rules allow it;
- property/crime rules permit or record the action where relevant.

The tutorial's `Not IsFalling` check is locked as a useful rule: ordinary grounded pushing cannot start while airborne.

---

# 3. Push Interaction State

Suggested semantic state:

`Action.WorldObject.Push`

Flow:

`Request Push`
-> validate object/side
-> reserve current push interaction
-> align player to push contact target
-> activate pushing animation/profile
-> movement input is constrained/projected according to object axes
-> server/world physics resolves block movement
-> stamina/work/audio presentation updates
-> release/cancel ends push state.

Do not make the player's animation authoritative over the block's final transform.

---

# 4. Physics Constraints

For grid/puzzle blocks, profiles may constrain:

- Z movement;
- roll/pitch/yaw;
- X-only / Y-only / grid-axis movement;
- maximum slope;
- snap/settle behavior.

Other movable objects may use less constrained physics.

Tutorial-specific constraints are content choices, not universal law for every movable object.

---

# 5. Animation / IK

Approved:

- push locomotion state/layer;
- Control Rig/Sequencer correction;
- hand contact IK;
- body lean based on effort/mass;
- foot correction;
- Motion Warping/entry alignment where useful.

Animation reads push velocity/effort and does not directly teleport the block.

Low-ledge IK/foot trace can be disabled or reconfigured while ledge traversal/pushing states require different contact logic; this is state-driven through the animation stack rather than a permanent global disable.

---

# 6. Pushing Audio

Looping scrape/stone sound is approved while the block is genuinely moving.

Preferred behavior:

- movement begins -> fade/start scrape loop;
- velocity/physics state updates presentation;
- movement stops -> fade/stop loop;
- sound profile depends on object + surface material where later implemented.

Do not leave audio looping because one push Boolean failed to reset.

---

# 7. Movable Ledges / Traversal Surfaces

A pushable block may also expose traversal affordances such as authored ledges.

Rules:

- ledge/traversal targets are children/attachments of the world object's transform or derived dynamically;
- moving the block moves the ledge target coherently;
- traversal collision does not interfere with push physics unnecessarily;
- server validates current ledge transform at grab/mantle time;
- moving block cannot leave stale detached ledge Actors behind.

This lets puzzle objects become climbable platforms without creating a separate fake ledge world state.

---

# 8. Pressure Plate / Placeholder Identity

Suggested capability/profile:

`Puzzle.Input.PressurePlate`

A plate may define:

- PuzzleInputID;
- accepted object tags/classes;
- required count;
- weight/mass threshold where used;
- occupied state;
- reversible/latching policy;
- visual/audio profile;
- linked PuzzleInstanceID.

The tutorial's glowing placeholder is an approved presentation.

---

# 9. Occupancy Validation

An overlap is only a candidate signal.

The authoritative puzzle/world system verifies:

- accepted block/object identity/type;
- block is sufficiently within the plate bounds;
- required weight/count conditions;
- object has not been destroyed/removed;
- current puzzle state permits update.

This reduces false activation from incidental overlap corners/accessories.

---

# 10. Reversible Puzzle Outputs

Pressure plates can feed the general puzzle system.

Example:

`Plate A occupied`
+
`Plate B occupied`
-> puzzle satisfied
-> Door opens.

Removing one block:

-> puzzle no longer satisfied
-> Door closes

when the PuzzleDefinition is reversible.

Other outputs can include:

- lower/raise ladder;
- move lift;
- unlock gate;
- activate bridge;
- reveal passage;
- disable trap.

---

# 11. Dynamic Material Feedback

Creating a Dynamic Material Instance per plate/object for state feedback is approved where appropriate.

Possible states:

- inactive;
- candidate overlap;
- correctly activated;
- locked/disabled;
- solved.

Material transitions and timeline color fades are presentation only; they do not own puzzle truth.

---

# 12. Sound Feedback

Activation/deactivation sounds are approved.

Different pitch/profile can communicate enter/leave state, but accessibility should not rely on pitch alone.

Visual state/icon/environmental feedback may accompany sound.

---

# 13. Persistence

Persist meaningful world state where the puzzle/object is persistent:

- pushable object transform/state;
- plate occupancy can be reconstructed from current authoritative object transforms;
- puzzle solved/latched state;
- output state;
- destroyed/missing object state.

Do not save one stale overlap Boolean if the physical block's saved location proves otherwise.

---

# 14. Multiplayer / Concurrency

Server owns pushable object world transform/physics truth and puzzle occupancy.

Multiple players may push one object only where the profile supports cooperative pushing.

Clients cannot locally drag a block onto a plate and open a server door without authoritative movement/puzzle validation.

---

# 15. Controller / Accessibility

Required:

- enter/leave Push through logical actions;
- directional push movement;
- cancel;
- KBM/Xbox-style/PlayStation-style support;
- readable plate state beyond color alone where necessary.

---

# 16. Performance

- pressure plates do not Tick;
- occupancy updates from overlap/state/physics settle events plus bounded validation;
- push audio runs only while moving;
- dormant settled blocks can sleep;
- traversal attachments update naturally from parent transforms, not global scans;
- puzzle evaluation occurs on input changes.

---

# Acceptance Tests

1. Airborne player cannot start normal grounded push interaction.
2. Player must use a valid push side/orientation.
3. Block respects configured movement/rotation constraints.
4. Block stops/settles without stale push audio.
5. Moving climbable block keeps its ledge target aligned.
6. Plate rejects invalid objects.
7. Correct block placement updates puzzle exactly once.
8. Removing block reverses output when puzzle is configured reversible.
9. Save/load restores block transform and reconstructs correct puzzle state.
10. Multiplayer client cannot fake pressure-plate activation.
11. Dynamic material/audio feedback follows puzzle truth.
12. Controllers can push/exit interaction cleanly.

## Core Rule

> Metaworld push puzzles connect real movable world objects to reusable puzzle inputs. Physics determines where objects actually are, puzzle rules determine whether placements count, and doors/ladders/lifts respond to authoritative state; animation, scraping audio and glowing materials make the interaction understandable.