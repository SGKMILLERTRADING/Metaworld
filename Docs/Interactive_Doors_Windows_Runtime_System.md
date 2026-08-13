# Metaworld — Interactive Doors & Windows Runtime System

**Status:** Canonical / Approved Upgrade

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first

## Canonical Principle

Installed doors and windows are persistent world objects that can also be interactive runtime objects.

Core rule:

> Construction installs the object; the interaction system operates it; server authority decides whether the operation is allowed; local animation presents the state smoothly.

This system extends `Docs/Doors_Windows_Openings_Construction_System.md`. Structural openings remain separate from the installed Door/Window object.

---

# 1. Common Interaction Contract

Do not place door/window-specific interaction logic directly in `BP_MW_Character_Master`.

Use Metaworld's common interaction language, preferably:

- `BPI_MW_Interactable`
- `BPC_MW_Interaction` on `BP_MW_Character_Master`
- camera/reticle interaction trace or other approved interaction targeting

Doors and interactive windows implement the same interface used by other world objects.

Possible interface calls:

- `CanInteract(Interactor)`
- `GetInteractionOptions(Interactor)`
- `RequestInteract(Interactor, InteractionAction)`
- `GetInteractionPrompt(Interactor)`

Door/window-specific actions can include:

- Open
- Close
- ToggleOpen
- Lock
- Unlock
- Force/Breach later
- Repair later

The interface requests an action; it does not let the client authoritatively change world state.

---

# 2. Interaction Targeting

A player may target a door/window through a camera/view interaction trace.

Recommended flow:

`Enhanced Input Interact`
-> `BPC_MW_Interaction`
-> camera/reticle trace
-> hit object implements `BPI_MW_Interactable`
-> query interaction options
-> send authoritative interaction request

Do not create a second unrelated interaction system only for buildables.

Interaction targeting must work with:

- keyboard/mouse
- Xbox-style controllers
- PlayStation-style controllers

---

# 3. Door State Model

Do not rely only on loose booleans such as `IsOpen` and `IsOpening` when the system grows.

Recommended motion state enum:

- `Closed`
- `Opening`
- `Open`
- `Closing`

Separate restriction/security state can include:

- `Unlocked`
- `Locked`
- `Jammed`
- `Broken`
- `Breached`
- `Destroyed`

This prevents contradictory combinations and repeated-interaction glitches.

Examples:

`Closed + Unlocked -> Opening -> Open`

`Open -> Closing -> Closed`

`Closed + Locked -> Open request rejected unless authorized unlock/breach rule succeeds`

Rapid repeated input must be resolved intentionally rather than spawning overlapping Timelines.

---

# 4. Default Transform & Movement Definition

The tutorial's `DefaultRotation` concept is approved, but Metaworld stores a canonical closed/default relative transform for each movable panel.

A movable-part definition can include:

- Part ID
- Component reference/name
- Closed/default relative transform
- Motion Type
- Rotation Axis
- Rotation Direction Sign
- Open Angle
- Translation Axis
- Open Distance
- Motion Duration
- Motion Curve
- Collision policy while moving
- Audio event hooks

Do not assume every door rotates exactly 90 degrees in exactly one second.

Those are valid prototype defaults, not universal rules.

---

# 5. Timeline / Motion Presentation

Blueprint Timelines are approved for simple local moving-panel presentation.

A Timeline can drive normalized progress `0..1` and interpolate from the stored closed transform to the configured open transform.

Rules:

- Timeline runs only while movement is active.
- No permanent Tick is required for an idle door/window.
- Reversing direction should use the current progress/state cleanly.
- Open angle/distance/duration/curve are data-driven per variant.
- Collision must remain physically meaningful while moving.

Other animation methods may later be used where they are more appropriate, but Timeline-based Blueprint motion is a valid baseline.

---

# 6. Multi-Panel Doors & Windows

The tutorial's two-window-mesh array idea is approved and generalized.

A Door/Window can own an array of movable-part definitions.

Examples:

Double window:

- Left panel: Rotation Direction Sign `+1`
- Right panel: Rotation Direction Sign `-1`

Double door:

- Left leaf: `+1`
- Right leaf: `-1`

Sliding window:

- Panel A: Translation Direction `+1`
- Panel B: stationary or opposite direction depending on variant

Do not hardcode `multiply second panel by -1` as a special case in the shared system. Direction is data on the part definition.

---

# 7. Server Authority

Door/window interaction state is authoritative.

Client:

- targets object
- displays prompt
- sends requested action
- may begin carefully designed local responsiveness/prediction if later proven safe

Server:

- resolves object identity
- checks property/access permissions
- checks lock state/key/authorization
- checks damage/jam state
- checks whether requested transition is legal
- changes authoritative target state
- replicates meaningful state change

The client cannot simply set `IsOpen = true` or unlock somebody else's door.

---

# 8. Replication Strategy

Do not replicate Timeline progress every frame as the default architecture.

Replicate compact meaningful state, such as:

- Door/Window Object ID
- target motion state
- open/closed target
- authoritative transition start time if needed
- motion duration/profile ID if not already known from definition
- security/damage state changes

Clients animate toward the authoritative state using the same motion definition.

On relevancy/late join/load, the client resolves the correct current/end state without needing the full historical Timeline.

---

# 9. Persistence

Persistent state can include:

- Object ID
- Buildable/Variant ID
- parent Opening ID
- `Open/Closed` settled state
- lock/security state
- condition/damage state
- permissions

A save/restart does not need to preserve a half-completed one-second animation unless later gameplay specifically requires that precision. Normally the authoritative settled/target state is restored and visual state is reconciled safely.

---

# 10. Locks, Keys & Permissions

Before an opening transition, the server can check:

- property owner
- household/family permission
- tenant permission
- business role
- guest access
- physical/digital key
- police/legal access where valid
- lock condition
- security system
- war/occupation rules where applicable

A door being interactable does not mean everybody is authorized to open it.

---

# 11. Obstruction & Safety

Moving objects should not blindly rotate/translate through everything.

Possible policies by variant:

- normal collision pushes/blocks movement where acceptable
- motion pauses/reverses when blocked
- door becomes temporarily obstructed
- automatic door waits for clear path
- heavy/security door follows stricter rules

Do not create an expensive world scan every frame. Use the moving object's relevant collision/sweep/query only while motion is active where required.

---

# 12. NPC Compatibility

NPCs use the same world interaction contract where practical.

An NPC with permission can:

- approach a door
- request open
- pass through
- request close where appropriate

Locked/restricted doors affect NPC navigation and behavior according to knowledge/permissions rather than being ignored by AI.

Door interaction can later integrate with Smart Objects or other navigation/interaction helpers, but the physical state remains authoritative Metaworld state.

---

# 13. Audio & Feedback

Door/window variants may define:

- open sound
- close sound
- latch sound
- lock/unlock sound
- jam/breach/broken sound
- haptic feedback where appropriate and supported

Audio/feedback is presentation layered on authoritative state, not the source of truth.

---

# 14. Controller Compatibility

Required controller-capable actions:

- target interactable
- interact/open/close
- select contextual action where more than one is available
- lock/unlock when authorized
- cancel/back from contextual UI

Interaction prompts must be able to show the active input family rather than permanent keyboard-only labels.

The feature is not complete until it is usable with keyboard/mouse, Xbox-style controller and PlayStation-style controller.

---

# 15. Performance Rules

- no idle per-frame Timeline/Tick work
- Timeline/updates exist only while movable parts are transitioning
- replicate state changes, not full transform spam every frame by default
- use shared Blueprint/data architecture across variants
- multi-panel objects animate only their configured movable parts
- obstruction queries run only when relevant
- distant/irrelevant doors/windows may use settled state without expensive continuous animation
- repeated rapid interaction must not start overlapping movement graphs

---

# 16. Python Editor Validation Upgrade

Python tooling can later audit:

- missing closed/default transforms
- invalid hinge/pivot placement
- missing movable-part definitions
- duplicate Part IDs
- impossible/open angles
- missing direction signs
- invalid movement duration/curve
- collision that blocks the opening even when open
- multi-panel parts rotating in the same direction when variant metadata expects opposing motion
- missing interaction interface/components
- missing controller/input test metadata where used

Python remains Editor tooling, not runtime interaction logic.

---

# 17. Initial Vertical-Slice Runtime Test

The first town should prove:

1. Installed door implements common Metaworld interaction interface.
2. Player targets it through normal interaction trace.
3. Door opens smoothly from stored closed transform.
4. Door closes smoothly.
5. Rapid repeated input does not create overlapping/glitched motion.
6. Locked door rejects unauthorized open request.
7. Authorized unlock/open succeeds.
8. State replicates correctly to another client.
9. Late/relevant client sees correct door state.
10. Save/load restores correct settled door state.
11. Door collision is correct when closed/open/moving.
12. Two-panel window opens with configured opposing directions.
13. Multi-panel direction comes from data, not a hardcoded second-mesh exception.
14. Window can close correctly.
15. Idle door/window has no unnecessary permanent Tick cost.
16. NPC can use an authorized interactive door path.
17. Keyboard/mouse interaction works.
18. Xbox-style controller interaction works.
19. PlayStation-style controller interaction works.
20. Repeated nearby door/window use remains within performance budget.

---

# Core Rule

> Metaworld doors and windows are not animated props. They are persistent, permission-aware, multiplayer-authoritative world objects whose panels move smoothly through shared Blueprint interaction and data-driven motion definitions only when the world state says they may move.
