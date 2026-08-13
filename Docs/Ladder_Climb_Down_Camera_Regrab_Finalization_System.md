# Metaworld — Ladder Climb-Down, Camera, Regrab & Finalization System

**Status:** Canonical / Approved Modern RPG Playlist Upgrade

**Extends:** `Docs/Ladder_Climbing_Traversal_System.md`

**Engine:** Unreal Engine 5.8

## Canonical Principle

Ladder traversal must work from both ends, enter from a stable character state, orient the player/camera predictably, and restore movement/environment state without immediate accidental re-entry.

> Entering, climbing, dropping and exiting are explicit traversal transitions. Overlap timing and held movement/input must not decide the state accidentally.

---

# 1. Top Entry / Climb Down

The ladder exposes a top-entry region/transform separately from the bottom entry.

Eligibility resolves from authored traversal data and relative position/approach rather than a magic world-Z threshold alone.

Useful checks can include:

- character near top entry;
- valid side/facing;
- clear mount position;
- character state permits climbing;
- ladder is valid/usable;
- landing/hang space is clear.

The player's Z relation can be one input, but ladders may be rotated/sloped/placed at different world elevations, so authored local-space entry targets are preferred.

---

# 2. Stop Residual Movement Before Mount

On accepted ladder entry:

- cancel Sprint state where required;
- stop/consume ground locomotion velocity according to traversal policy;
- suppress further ground movement during entry alignment;
- recompute Stamina/Encumbrance traversal state;
- align to the ladder entry target.

This prevents a sprinting player from carrying lateral momentum past the mount point.

Do not use this as a blanket teleport; the traversal state owns the transition.

---

# 3. Exit Trigger Discipline

Top/bottom exit volumes are candidate signals, not automatic proof that the exit montage should fire.

Exit requires:

- character currently in the correct ladder traversal state;
- moving/reaching the correct end;
- exit target still clear;
- no conflicting interruption;
- one active transition only.

This prevents premature exit montages from incidental overlap.

Accessory/static meshes should not generate irrelevant overlap events that pollute traversal eligibility.

---

# 4. Camera Orientation

On mount, camera/character orientation can transition toward the ladder's authored facing profile.

Possible policies:

- character snaps/warps to face ladder while camera keeps player control;
- camera interpolates to a preferred mount yaw;
- camera remains freer during climb but clamps extreme angles;
- accessibility option reduces forced camera motion.

Do not hardcode one world rotation. Use ladder-local forward/right axes.

Forced camera rotation must avoid nausea-inducing abruptness where a smooth transition works better.

---

# 5. Drop / Fall / Regrab Guard

Letting go transitions to `Falling` and releases the ladder traversal context.

The character must not immediately re-enter because the same overlap volume is still touching the capsule.

Use explicit re-entry eligibility such as:

- traversal state has fully exited;
- originating interact press completed/canceled;
- optional short regrab lockout or minimum separation where needed;
- fresh interaction intent required;
- character is again in a valid approach/grab condition.

A lockout is a traversal-state rule, not an arbitrary UI Delay used everywhere.

Future deliberate mid-fall regrab can be supported as a separate skilled action/profile if desired.

---

# 6. Water / Other Environment Exit

Ladder entry/exit must notify/reconcile environment contact state.

Example:

`Swimming -> Ladder`
- stop active swim movement state;
- Breath logic still evaluates actual airway/water contact during transition;
- mount ladder;
- on exiting above water, environment resolver confirms character is no longer submerged;
- stop breath drain / allow recovery;
- restore Walking.

The ladder does not manually leave stale WaterVolume/Swimming flags behind.

---

# 7. Blueprint Organization

Collapsing a complex ladder graph is useful for editor readability, but canonical ownership remains:

- traversal state/component;
- ladder object/profile;
- interaction component;
- animation layer/montages;
- environment state service.

`Collapse Nodes -> Climbing Ladder` does not justify placing the entire traversal architecture permanently inside the Player Blueprint.

---

# 8. Acceptance Tests

1. Player can mount from bottom and top.
2. Top entry uses ladder-local authored target rather than one global Z assumption.
3. Sprint momentum cannot push character past ladder after accepted mount.
4. Exit animation cannot trigger from incidental overlap before reaching the end.
5. Character/camera faces ladder predictably from different initial approach angles.
6. Dropping transitions to Falling.
7. Same held interaction/overlap cannot instantly regrab after drop.
8. A later fresh valid interaction can re-enter.
9. Climbing out of water reconciles swim/Breath state correctly.
10. Different ladder rotations/heights use the same architecture.

## Core Rule

> A finished ladder system is bidirectional and state-safe: it consumes the entry movement, uses ladder-local orientation, guards exits/re-entry, and hands the character cleanly between Walking, Falling, Swimming and Ladder traversal without stale flags.