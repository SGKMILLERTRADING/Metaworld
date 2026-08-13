# Metaworld — Interaction Hold, Progress, Modal Input & State System

**Status:** Canonical / Approved Modern RPG Playlist Upgrade

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first / Enhanced Input / controller-complete / server-authoritative interaction state

## Canonical Principle

Tap, hold, release and cancel interactions are explicit interaction states driven by Enhanced Input and authoritative gameplay validation. UI progress visualizes the active interaction; it does not decide that the interaction succeeded.

> Input expresses intent. The interaction system owns state. The progress bar only shows that state.

Related canon:

- `Docs/Controller_Input_Compatibility_Architecture.md`
- `Docs/Persistent_Item_Interaction_Inventory_Architecture.md`
- `Docs/Loot_Containers_Bags_Corpses_Chests_Transfer_System.md`
- `Docs/RPG_Interface_Shell_Widget_Data_Contracts_Navigation_System.md`
- `Docs/Construction_Progress_Build_To_Completion_System.md`

---

# 1. Enhanced Input Action States

Use Enhanced Input action state rather than raw hardcoded key events.

Suggested common interaction action:

`IA_MW_Interact`

Useful trigger events include:

- Started;
- Triggered;
- Ongoing where the action's trigger semantics require it;
- Completed;
- Canceled.

For a hold interaction, the mapping/action trigger can represent the hold requirement, while gameplay state still validates target/range/permissions.

Do not hardcode `E pressed`, `E released`, `R take all`, etc. as canonical controls.

---

# 2. Interaction Modes

An available interaction may define:

- Tap;
- Hold;
- Toggle;
- Continuous/Work;
- Timed Authoritative Action;
- Modal Open.

Examples:

Tap:
- open unlocked door;
- pick up small item.

Hold:
- search/loot locked chest;
- revive/medical action;
- force open object;
- dismantle;
- longer contextual action.

The interaction definition owns required duration and cancellation rules.

---

# 3. Hold Interaction State

Suggested conceptual state:

`S_MW_ActiveInteraction`

Possible fields:

- InteractionInstanceID;
- ActionID;
- TargetID;
- Initiator CharacterID;
- StartedAt;
- RequiredDuration / WorkRequirement;
- authoritative state;
- progress/revision;
- cancellation reason;
- reservation/lock state where required.

Client input begins a request; server or owning authoritative gameplay layer accepts/rejects the interaction.

---

# 4. Progress UI

The interaction prompt/HUD may show:

- radial progress;
- linear progress;
- hold glyph;
- remaining duration;
- cancel/release hint;
- unavailable reason.

The percentage is presentation derived from the active interaction state/time.

If local progress reaches 100% but the authoritative action was canceled/invalidated, no loot/open/revive/etc. commits.

---

# 5. Release / Cancel

A hold action may cancel when:

- input is released before threshold;
- target changes;
- player moves beyond allowed range;
- LOS breaks where required;
- player becomes incapacitated;
- combat/action restriction occurs;
- target is destroyed/locked/taken by another player;
- modal/menu state invalidates the interaction;
- server rejects current conditions.

Cancellation resets/hides presentation according to policy and releases reservations safely.

Do not let a local timer continue to completion after the interaction context is gone.

---

# 6. Preventing Double Activation

The tutorial issue where opening a widget while the Interact key is still held causes accidental immediate actions is solved through explicit interaction/input state.

Rules:

- when a modal opens, the originating gameplay interaction is consumed/completed/canceled deliberately;
- the modal input layer does not reinterpret the same held physical input as a second action;
- Started/Completed/Canceled semantics are respected;
- actions may require a fresh press after modal/context transition where appropriate;
- repeated commit requests use InteractionInstanceID / transaction protection.

Do not rely on arbitrary delays to stop immediate reopen/double-loot.

---

# 7. Modal Input Layer

While inventory, trader, loot or quantity UI is active:

- focus is owned by the active UI layer;
- underlying world actions cannot fire through the modal;
- Enhanced Input mapping contexts/UI routing are changed intentionally;
- local movement/look may be enabled or restricted according to the specific screen;
- shared world never globally pauses merely because a menu opens;
- closing restores the correct gameplay mapping/focus exactly once.

`Game and UI`, `UI Only` or equivalent behavior is chosen per screen and validated with controllers; do not scatter ad-hoc Set Input Mode calls through every child widget.

---

# 8. No Manual Garbage Collection As Widget Cleanup

Closing a widget should:

- remove/deactivate the widget;
- unbind delegates/events;
- release local references/resources;
- stop preview/capture/animations/timers;
- allow Unreal's normal object lifecycle/garbage collection to reclaim unreachable objects.

Do **not** make `Force Garbage Collection` / manual GC every menu close part of normal gameplay flow.

Forced collection can create frame hitches and is reserved for controlled/debug/special lifecycle circumstances only after profiling.

Correct ownership/reference cleanup is the primary solution.

---

# 9. Chest Hold Interaction

A chest may define:

- instant Open if unlocked;
- Hold Search/Open for a configured duration;
- lockpick/force-open action through separate capability;
- Empty state;
- owner/access/lock restrictions.

Suggested flow:

`Resolve Chest Interaction`
-> player Starts IA_MW_Interact
-> RequestBeginInteraction(ActionID, ChestID)
-> validate range/access/state
-> active hold begins
-> HUD radial progress derives from accepted state
-> Completed threshold reached
-> server revalidates
-> open/loot context becomes available
-> UI opens.

Releasing/moving away cancels before commit.

---

# 10. Crafting / Other Progress Reuse

The same interaction-state principles may be reused for:

- hold-to-craft confirmation;
- gathering;
- repair;
- construction work;
- medical treatment;
- searches;
- lockpicking;
- sabotage;
- long interactions.

But each owning gameplay system remains authoritative for its result and persistence.

---

# 11. Empty / Disabled Interaction Presentation

The current target can report:

- Empty;
- Locked;
- In Use;
- Too Far;
- No Permission;
- Missing Tool;
- Already Open;
- No Valid Action.

The prompt can hide the hold meter when no executable hold action exists.

---

# 12. Performance

- no permanent hold timer on every interactable;
- only active interaction schedules progress/timing work;
- UI animations run only while visible;
- candidate targeting is bounded to relevant nearby/view targets;
- no repeated global widget/Actor scans;
- modal transitions do not force garbage collection;
- authoritative timestamps can replace high-frequency timer polling where appropriate.

---

# 13. Controller Compatibility

Hold/tap behavior must work with:

- keyboard/mouse;
- Xbox-style controller;
- PlayStation-style controller;
- rebinding.

Prompt shows current mapped glyph/action and clearly distinguishes Tap vs Hold.

Back/Cancel behavior is device-independent.

---

# 14. Acceptance Tests

1. Hold chest interaction begins only after valid target/action request.
2. Releasing early cancels and never opens/loots chest.
3. Moving out of range cancels correctly.
4. Local progress reaching 100% cannot bypass server validation.
5. Opening loot UI does not treat the same held Interact press as Take/Take All.
6. Closing UI does not immediately reopen due to stale held input.
7. No arbitrary delay is required for normal close/reopen safety.
8. No forced garbage collection occurs on ordinary widget close.
9. Modal prevents click/key/controller input from activating background inventory/world actions.
10. Enhanced Input Started/Completed/Canceled semantics work with KBM/Xbox-style/PlayStation-style mappings.
11. Empty chest shows an appropriate disabled/empty presentation.
12. Interaction timers/progress do no work when no interaction is active.

## Core Rule

> Metaworld treats interaction as explicit state, not a loose collection of key presses and widget timers. Enhanced Input starts/cancels intent, the authoritative system validates and commits the action, and UI progress simply reflects what is actually happening.