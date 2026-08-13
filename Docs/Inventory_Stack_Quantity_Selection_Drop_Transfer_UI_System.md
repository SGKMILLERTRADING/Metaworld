# Metaworld — Inventory Stack Quantity Selection, Split, Drop & Transfer UI System

**Status:** Canonical / Approved Modern RPG Playlist Upgrade

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first / controller-complete / server-authoritative transactions

## Canonical Principle

When an action applies to part of a stack, the player selects a quantity in UI and the server performs one authoritative quantity transaction against the exact current stack/lot state.

> The slider chooses how many. It does not perform the drop, split, transfer, sale or destruction itself.

Related canon:

- `Docs/Persistent_Item_Interaction_Inventory_Architecture.md`
- `Docs/Item_Drop_Disposal_Physical_Currency_Transaction_System.md`
- `Docs/RPG_Interface_Shell_Widget_Data_Contracts_Navigation_System.md`
- `Docs/Controller_Input_Compatibility_Architecture.md`

---

# 1. Quantity Dialog

Suggested reusable widget:

`W_MW_QuantitySelector`

Possible uses:

- Drop Quantity
- Split Stack
- Transfer Quantity
- Sell Quantity
- Give Quantity
- Move to Container
- Craft Batch selection where appropriate
- Discard/Destroy Quantity where allowed

Inputs/presentation:

- ActionID
- target ItemInstanceID / StackID / lot reference
- source ContainerID
- MinQuantity
- MaxQuantity snapshot
- default quantity
- item name/icon
- action verb
- optional destination/context
- confirm/cancel.

The widget never holds the only authoritative copy of ItemInfo.

---

# 2. Integer Quantity

Item quantities are discrete units unless the item system explicitly defines a continuous measurement commodity.

For discrete stack items:

- minimum normally 1;
- maximum = current authorized selectable quantity;
- slider/stepper snaps to integers;
- numeric display always shows an integer;
- direct numeric entry may be supported where practical.

Do not allow a slider value such as `3.47 arrows`.

---

# 3. Controller / Keyboard / Mouse

Required controls:

- mouse drag/click;
- keyboard arrows or configured navigation increments;
- Xbox-style D-pad/stick/bumper controls where designed;
- PlayStation-style equivalent;
- confirm;
- cancel/back;
- optional increment/decrement buttons;
- optional hold-to-repeat quantity adjustment.

No quantity action may require a mouse-only slider.

Enhanced Input/UI navigation owns physical controls; hardcoded keyboard keys are not canonical.

---

# 4. Modal Input Layer

While the quantity selector is active:

- underlying inventory entries do not accept unintended activation;
- focus is trapped within the modal/dialog layer;
- game/world input follows the current menu policy;
- shared multiplayer world is not globally paused;
- closing/cancelling restores focus to the originating item entry when it still exists;
- click-through is blocked by the UI layer rather than scattered Boolean checks in every inventory icon.

A background blocker/overlay is an approved presentation technique.

---

# 5. Stable Target Identity

Do not identify the target only by array index.

Preferred action context:

- `ItemInstanceID` / stack-lot ID
- `SourceContainerID`
- expected revision where useful
- requested quantity
- destination/context ID

When the player confirms, re-resolve the exact current stack.

If another action changed the stack while the dialog was open, clamp/reject/rebuild according to current state instead of acting on stale quantity/index data.

---

# 6. Drop Quantity Transaction

Suggested request:

`RequestDropQuantity(ItemInstanceID, SourceContainerID, Quantity, PreferredDropContext)`

Server validates:

- exact item/stack still exists;
- requester may manipulate it;
- Quantity > 0 and <= current available quantity;
- item is not locked/reserved/traded;
- drop is legally/physically permitted;
- valid world spawn/support state exists.

Commit behavior:

- if dropping the entire stack, move the existing stack/instance to world state where appropriate;
- if dropping part, split the authoritative stack/lot into retained and dropped quantities while preserving all required metadata;
- create/resolve the legitimate world representation;
- persist/replicate once.

Do not loop `DropItem` N times for a stack quantity if one atomic stack split/drop can represent it correctly.

---

# 7. Stack Split Identity / Metadata

When a stack is split, both resulting records must retain all compatible state required by the item/lot model.

Possible retained metadata:

- ItemDefinitionID;
- quality/grade;
- creator/provenance lot;
- ownership/legal state;
- stolen/evidence flags;
- expiry/spoilage;
- condition/effect payload;
- upgrade/modification state where stackable;
- source transaction history where required.

The new split record receives its own legitimate identity/revision where the data model requires one.

No split may silently drop condition/potion/ammunition metadata.

---

# 8. Transfer / Sell / Give Quantity

The same quantity-selection contract can feed:

- `RequestTransferQuantity`
- vendor quote/sale quantity
- player-to-player trade quantity
- container move
- give/hand-off action.

The UI-selected amount is advisory until the authoritative transaction revalidates capacity, ownership, price, quote expiry and current quantity.

---

# 9. Drop Location Safety

Dropped quantity uses the existing safe world-item spawn rules:

- resolve item bounds/presentation;
- find a valid nearby drop/support point;
- avoid blocking geometry/characters;
- initialize presentation before enabling interaction;
- enable physics only when appropriate;
- let settled items sleep/reduce cost.

Dropping `x20 arrows` may create one world stack/bundle representation rather than twenty live arrow Actors when stack state permits.

---

# 10. Duplication Prevention

While the modal is open:

- target entry can be considered locally busy for presentation;
- server transaction/revision remains the real guard;
- repeated Confirm input is debounced/transaction-ID protected;
- success closes/refreshes the dialog from committed state;
- failure keeps/rebuilds the dialog with current state/reason.

No rapid clicking or input-mode transition may duplicate a stack.

---

# 11. UI Lifecycle

Recommended behavior:

- create/show selector only when needed;
- initialize from a presentation snapshot;
- refresh if target quantity changes materially;
- remove/close on confirmed success, cancel, target deletion, inventory closure or context invalidation;
- restore focus predictably;
- no per-frame inventory scan/binding.

---

# 12. Acceptance Tests

1. Slider/stepper cannot select fractional quantity for discrete items.
2. Mouse, keyboard, Xbox-style and PlayStation-style controls can adjust/confirm/cancel.
3. Underlying inventory cannot be accidentally activated while modal is open.
4. Sorting inventory while modal is open cannot redirect the action to another item.
5. Dropping part of a stack preserves all required metadata on both portions.
6. Dropping full stack does not unnecessarily duplicate the item record.
7. Confirming twice cannot duplicate the drop/transfer.
8. Quantity greater than current stack is rejected/re-resolved server-side.
9. Dropped stack spawns at a valid nearby location.
10. Arrow stack can drop as a compact bundle rather than N live Actors where compatible.
11. Closing the dialog restores focus correctly.
12. Vendor/transfer actions can reuse the same quantity selector without making the widget authoritative.

## Core Rule

> Quantity selection is reusable modal UI over stable item identity. The server revalidates the exact current stack and performs one transaction that preserves quantity, metadata and ownership without duplication.