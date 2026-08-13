# Metaworld — Lift, Elevator, Lever & Traversal System

**Status:** Canonical / Approved Modern RPG Playlist Upgrade

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first / server-authoritative / data-driven / performance-budgeted

## Canonical Principle

Lifts/elevators are persistent interactive world mechanisms whose controls, movement path and safety state are authoritative. Levers/buttons are interaction endpoints, not the movement authority themselves.

> A lever requests a lift action. The lift state machine decides whether movement is legal, moves along a configured path, carries valid passengers and replicates/persists the meaningful result.

Related canon:

- `Docs/Interaction_Hold_Progress_Modal_Input_State_System.md`
- `Docs/Performance_Smoothness_FrameTime_Architecture.md`
- `Docs/Controller_Input_Compatibility_Architecture.md`
- `Docs/Household_Property_Access_Lock_Permissions_System.md`

---

# 1. Lift / Control Separation

Recommended identities:

- `LiftObjectID`
- `LiftControlID`
- `LiftPathProfileID`

One Lift can have multiple controls:

- lever at bottom;
- lever at top;
- call buttons;
- cabin controls;
- remote/security controls.

A control references the LiftObjectID and requests an action such as:

- MoveToStop(A)
- MoveToStop(B)
- CallLift
- Stop/EmergencyStop where supported.

The control does not own the authoritative platform transform.

---

# 2. Lift State Model

Recommended states:

- IdleAtStop
- Starting
- Moving
- Stopping
- Blocked
- Disabled
- Broken
- EmergencyStopped

Possible direction/target state is stored separately.

Avoid simple FlipFlop-only authority for scalable lifts because it cannot represent blockers, multiple stops, interruptions or late-join state safely.

---

# 3. Path / Travel Definition

A lift profile may define:

- stop IDs / relative/world transforms;
- travel duration or speed;
- motion curve;
- acceleration/deceleration presentation;
- platform orientation policy;
- allowed directions;
- doors/gates/interlocks;
- passenger capacity;
- weight/mass limit where gameplay uses it;
- control permissions;
- audio/VFX profile.

The tutorial's editor-exposed horizontal/vertical travel distances are approved as a simple two-stop prototype.

For more complex systems, use authored stop/path data rather than duplicating Timelines per variant.

---

# 4. Timeline / Movement Presentation

Blueprint Timeline motion is approved for simple lifts.

Rules:

- Timeline runs only while moving;
- replicate meaningful motion state/start time/target, not per-frame transform spam by default;
- late/relevant clients reconstruct current position from authoritative motion state/time;
- no permanent Tick for idle lifts;
- motion interruption/reversal is intentional, not overlapping Timeline calls.

Other movement solutions may replace Timelines if profiling/networking/physics proves them better.

---

# 5. Passenger Handling

A lift must correctly carry characters/objects that are legitimately standing on it.

Requirements:

- stable movement-base behavior or equivalent character/platform solution;
- avoid teleporting/launching passengers;
- respect collision while moving;
- handle jump/fall/exit during travel;
- do not attach every overlapping world Actor blindly;
- physics items use significance/interaction rules appropriate to moving platforms.

Multiplayer tests must include multiple players/NPCs riding simultaneously.

---

# 6. Interaction Targeting

Lever/button implements the common interaction contract.

`BPC_MW_Interaction`
-> current control candidate
-> request Lift action
-> server validates
-> lift state changes.

Do not let extra decorative/platform meshes generate interaction overlaps/prompts accidentally.

The tutorial fix disabling unnecessary Generate Overlap Events on extra lift meshes is approved as collision/query cleanup.

Only intended interaction/query components should participate in prompt targeting.

---

# 7. Permissions / Locks

A lift may be:

- public;
- property-private;
- employee-only;
- prison/security restricted;
- maintenance-only;
- disabled by power failure;
- locked behind physical/digital credentials.

Use the existing property/access/credential systems rather than hardcoded booleans when ownership/security matters.

---

# 8. Power / Utility Integration

Where the world design requires electricity/fuel:

- powered lift requires valid utility state;
- outage can stop/prevent operation according to safety profile;
- emergency/manual mechanisms may exist;
- restoring power does not duplicate or teleport lift state.

Utility integration is event/state based, not per-frame account checks.

---

# 9. Safety / Obstruction

Possible rules:

- gate/door interlock before travel;
- obstruction prevents start;
- emergency stop;
- crush/pinch damage only if explicitly designed and server-authoritative;
- platform cannot phase through blocking world geometry;
- overloaded lift may refuse operation where capacity is gameplay-relevant.

Do not run broad world scans every frame; query relevant collision/occupancy only when needed.

---

# 10. Persistence / Replication

Persist meaningful settled/system state:

- LiftObjectID;
- current stop/target;
- enabled/broken/locked state;
- current motion state/start time if persistence during movement is required;
- access/security state.

On server restart, reconcile safely to a valid position/state without duplicating or trapping passengers.

---

# 11. NPC Compatibility

NPC navigation/behavior can request lift service through the same system.

An NPC should not walk through a missing lift platform or sealed gate.

Distant NPC traversal can abstract the trip when world simulation tier permits, while nearby players see the physical lift.

---

# 12. Controller / Feedback

Interaction works with KBM/Xbox-style/PlayStation-style input.

Feedback may include:

- lever/button animation;
- lift moving audio;
- floor/stop indicator;
- unavailable reason;
- power/locked/blocked state;
- haptics where useful.

UI/animation presents authoritative state; it does not decide movement.

---

# 13. Performance

- idle lift has no permanent Timeline/Tick work;
- only intentional collision/query components generate overlaps;
- movement updates exist only during travel;
- distant lifts may use lower-cost settled state;
- audio/VFX stop when irrelevant;
- path/control data is shared rather than duplicated in many bespoke Actors.

---

# 14. Acceptance Tests

1. Lever requests lift and does not directly own platform state.
2. Lift moves between configured stops correctly.
3. Extra platform meshes do not create false interaction prompts.
4. Two players ride lift without desync/launching.
5. Late client sees correct current lift state/position.
6. Rapid interaction cannot start overlapping movement.
7. Locked/powered/blocked policies reject with correct reason.
8. Save/load restores safe lift state.
9. NPC can use authorized lift path.
10. Idle lift consumes no unnecessary per-frame work.
11. KBM/Xbox-style/PlayStation-style control works.

## Core Rule

> Metaworld lifts are shared world traversal machines with persistent authoritative state. Controls request movement, configured paths define it, passengers ride it safely, and idle systems stay cheap.