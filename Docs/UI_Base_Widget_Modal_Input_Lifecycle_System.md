# Metaworld — Base Widget, Modal Input & UI Lifecycle System

**Status:** Canonical / Approved Modern RPG Playlist Upgrade

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first / Enhanced Input / controller-complete / event-driven

## Canonical Principle

Shared UI behavior belongs in reusable widget bases/controllers and a coherent UI stack, not duplicated across every Inventory, Trader, Loot, Dialogue, Quickslot and Options widget.

> Opening or closing a widget changes local UI/input state. It does not pause Metaworld, force garbage collection, or make the widget the owner of gameplay truth.

Related canon:

- `Docs/RPG_Interface_Shell_Widget_Data_Contracts_Navigation_System.md`
- `Docs/Interaction_Hold_Progress_Modal_Input_State_System.md`
- `Docs/Controller_Input_Compatibility_Architecture.md`
- `Docs/Quickslot_Hotbar_Item_Action_Assignment_System.md`
- `Docs/NPC_Dialogue_Service_Conversation_UI_System.md`

---

# 1. Base Widget Is Approved

A reusable Blueprint base widget is approved for common presentation/lifecycle behavior.

Possible conceptual base:

`W_MW_BaseWidget`

Possible specialized descendants/interfaces:

- `W_MW_BaseModal`
- `W_MW_BasePanel`
- `W_MW_BaseContextMenu`
- `W_MW_BaseServiceScreen`

Shared functionality can include:

- open/activate lifecycle hooks;
- close/back request;
- default focus target;
- focus restoration metadata;
- modal/background dim behavior;
- input-layer request/release;
- safe timer/delegate cleanup;
- transition animation hooks;
- accessibility announcement hooks.

Do not put Item, Crafting, Trade or Combat gameplay logic into the base widget.

---

# 2. UI Stack / Manager Owns Global UI State

Stateful UI orchestration should be owned by a local player UI manager/controller rather than a static function library.

Conceptual flow:

`Local Player UI Manager`
-> Push Screen/Modal
-> apply mapping/input policy
-> set focus
-> suspend lower layer if required
-> Pop Screen/Modal
-> restore previous focus/input policy.

Pure formatting/helper functions may live in function libraries. Stateful ownership such as "which modal is active" should not be hidden in global static helpers.

---

# 3. Input Modes Are Policies, Not Per-Widget Hacks

Metaworld may use Game Only, UI Only, or Game + UI style routing according to the active UI layer, but the policy is centralized.

Examples:

- normal gameplay: gameplay context active;
- inventory/service modal: UI context active, local movement/look restricted where intended;
- lightweight nonblocking HUD: gameplay remains active;
- quantity selector: modal UI captures Confirm/Cancel/navigation;
- dialogue/service screen: UI focus, world still advances.

Do not scatter `Set Input Mode` calls across dozens of unrelated widgets with contradictory behavior.

---

# 4. Enhanced Input Replaces Legacy Held-Key Gates

The tutorial's `CanPressKey` Boolean is a useful diagnosis of held-key leakage, but Metaworld uses Enhanced Input trigger state/context ownership.

Relevant trigger lifecycle:

- Started
- Ongoing
- Triggered
- Completed
- Canceled

A world Interact action that opens a modal is consumed/completed by the originating interaction context. The newly active UI context requires a fresh logical UI action where appropriate.

Do not let the same held physical press both open a chest and immediately activate `Take`, or open Inventory and immediately close it.

---

# 5. Modal Layer

A modal blocks unintended interaction with lower UI layers.

Examples:

- quantity selection;
- confirmation dialog;
- quickslot assignment;
- destructive action confirmation;
- some service transactions.

Modal behavior:

- visible dim/background optional;
- lower-layer pointer/focus input blocked;
- only modal navigation/actions active;
- Escape/Back/Cancel routes to modal first;
- focus returns to originating control if still valid.

The dim/black-screen widget is presentation, not an input authority by itself.

---

# 6. Close / Back Contract

Widgets request close through shared lifecycle behavior.

Suggested concepts:

- `RequestClose`
- `CanClose`
- `OnBeforeClose`
- `OnClosed`

The UI manager decides stack behavior.

Examples:

Trade opened from NPC Dialogue:
`Back`
-> close Trade
-> restore Dialogue focus.

Inventory opened from gameplay:
`Back`
-> close Inventory
-> restore gameplay input.

A hardcoded `E`, `I`, or arbitrary key inside every widget is not canonical.

---

# 7. Focus Ownership

Every interactive screen/modal defines:

- default focus target;
- fallback focus target;
- focus restoration target/source;
- behavior when the referenced item/button disappears.

Controller users must never be stranded with invisible/no focus.

Hover effects and focus effects should have equivalent readability.

---

# 8. Widget References & Cleanup

On close/deactivation:

- unbind delegates/listeners;
- clear transient references;
- stop local timers;
- stop animations/captures that should not continue;
- release preview-only objects/resources;
- remove/deactivate from UI stack according to pooling policy.

Validated references are useful for optional objects, but architectural ownership should make invalid references nonfatal.

Do not keep discarded widgets alive only because old dispatchers/static references still point at them.

---

# 9. No Forced Garbage Collection As Normal UI Flow

Metaworld does not call forced GC every time Inventory, Loot, Trader or another widget closes.

Normal lifecycle:

`Close UI`
-> unbind/clear/stop work
-> remove/deactivate
-> references become unreachable or pooled intentionally
-> Unreal manages garbage collection normally.

Forced collection may be a profiling/debug/tool operation, not the routine solution to UI bugs.

---

# 10. Reusable Presentation Helpers

Global/pure helper functions are appropriate for deterministic presentation such as:

- rarity style lookup;
- formatting mass/value/percent;
- localized stat display;
- input glyph lookup through proper input presentation service;
- common tooltip formatting.

These helpers should not require a persistent Player Blueprint reference when the calculation does not logically depend on the player.

---

# 11. Blueprint Organization Standard

The tutorial's organization practices are approved:

- clear categories for variables/functions;
- comments around non-obvious logic;
- concise function/macro extraction;
- consistent graph regions/colors where useful;
- validated optional references;
- descriptive names.

But "Collapse to Nodes" is not a substitute for modular system design.

Prefer:

- function when logic has a clear local responsibility;
- component/service when logic is a reusable gameplay domain;
- interface when behavior crosses unrelated classes;
- data asset/table when behavior is configuration;
- macro only for small graph-flow reuse where semantics fit.

Do not hide giant monolithic logic inside one collapsed graph and call it modular.

---

# 12. Quickslot/UI Stale-State Rule

Quickslot overlay/empty/active presentation derives from current assignment + availability state.

If an item is re-equipped or becomes available again, the quickslot presentation refreshes from the current assignment resolver and clears stale unavailable overlays automatically.

The fix is event-driven state recomputation, not manually sprinkling `SetVisibility(Hidden)` into every call site forever.

---

# 13. Performance

- no polling just to discover whether a modal is open;
- no forced GC per close;
- no hidden widgets running Tick unnecessarily;
- input mapping/context changes occur on lifecycle transitions;
- event-driven focus/presentation refresh;
- heavy screens may lazy-load/pool after profiling;
- stale delegate bindings are removed.

---

# 14. Acceptance Tests

1. Inventory opens/closes without held-key double-trigger.
2. Loot/Chest opening cannot immediately trigger Take from the same press.
3. Quantity modal blocks lower inventory activation.
4. Closing modal restores correct source focus.
5. Trade opened from Dialogue can return to Dialogue cleanly.
6. No routine forced GC is required to prevent duplicate widgets/input.
7. Destroyed/deactivated widgets leave no stale dispatcher listeners.
8. Quickslot unavailable overlay clears when assignment becomes available again.
9. Common close/back behavior works with KBM/Xbox-style/PlayStation-style input.
10. Widget base class contains lifecycle/UI concerns only, not item/economy gameplay authority.
11. Pure global presentation helpers do not require unnecessary Player references.
12. Hidden UI layers perform no unnecessary per-frame work.

## Core Rule

> Metaworld UI has one coherent lifecycle and input stack. Base widgets share presentation/focus/close behavior, Enhanced Input handles fresh presses and modal routing, and closing a screen cleans references and work instead of relying on delays, legacy key gates or forced garbage collection.