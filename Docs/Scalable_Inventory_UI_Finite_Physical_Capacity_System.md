# Metaworld — Scalable Inventory UI & Finite Physical Capacity System

**Status:** Canonical / Approved Modern RPG Playlist Upgrade

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first / persistent / server-authoritative / controller-complete

## Canonical Principle

Metaworld inventory presentation can scale to arbitrarily large container contents, but physical characters and containers remain constrained by real gameplay capacity rules.

> Infinite scrolling UI is allowed. Infinite physical carrying is not.

Related canon:

- `Docs/Persistent_Item_Interaction_Inventory_Architecture.md`
- `Docs/Stats_Attributes_Item_Modifiers_Encumbrance_System.md`
- `Docs/Ranged_Weapons_Bow_Ammo_Quiver_Container_System.md`
- `Docs/Inventory_Stack_Quantity_Selection_Drop_Transfer_UI_System.md`

---

# 1. UI Capacity vs Physical Capacity

These are separate concepts.

## UI Presentation Capacity

The inventory screen may dynamically display as many item entries as the opened container legitimately contains.

Approved techniques include:

- ScrollBox for moderate lists;
- ListView / TileView / virtualized presentation for large inventories;
- dynamic grid rows/columns;
- pagination/filtering/search where useful;
- minimum visible empty-slot presentation for aesthetics.

The tutorial's dynamic `minimum 36 slots, then add rows` idea is acceptable presentation logic.

## Physical Capacity

Actual storage is still limited according to the Container definition/policy, for example:

- slot count;
- weight/mass capacity;
- volume;
- item dimensions;
- allowed item tags;
- compartments;
- carried-load limits;
- equipment/storage rules.

A larger ScrollBox never grants more physical storage.

---

# 2. Player Carrying Is Not Infinite

The player may have multiple authorized carried containers:

- pockets;
- backpack;
- quiver;
- belt pouch;
- weapon holster;
- other equipment storage.

Each container contributes to a combined carried-load model.

The player cannot carry unlimited items merely because UI can render unlimited entries.

Examples:

- 100 feathers may be easy to carry;
- 100 rifles are not;
- a refrigerator should not fit in a pocket;
- moving arrows from backpack to quiver does not remove their mass.

Capacity rules continue to interact with Encumbrance and movement.

---

# 3. Large External Containers

Some containers can legitimately contain very large inventories:

- warehouse;
- store stockroom;
- vehicle cargo;
- shipping container;
- property storage;
- company inventory;
- large chest/vault.

The UI should scale to these without imposing an arbitrary 36-entry ceiling.

However, their physical capacity still derives from their actual storage profile.

---

# 4. Dynamic Grid / List Rules

A UI may choose a minimum visual footprint such as 36 slots and add rows in fixed increments.

This is visual layout only.

Preferred separation:

`Container Snapshot`
-> `VisibleEntryCount / LayoutProfile`
-> UI builds/virtualizes enough presentation rows

Do not infer storage authority from Widget child count.

---

# 5. Pickup / Crafting / Trading Still Can Fail

Removing a fixed 36-slot UI cap does **not** mean transaction failure disappears.

Pickup, craft output and trade can still fail because:

- destination weight capacity exceeded;
- volume/dimension rules fail;
- allowed-tag/compartment rules fail;
- carried load reaches unsafe limits;
- container is locked/reserved;
- transaction lacks permission;
- destination physically cannot accept item.

Therefore authoritative transaction APIs keep success/failure results even if the UI is dynamically scalable.

Do not delete transaction success/failure semantics merely because the tutorial calls the inventory `infinite`.

---

# 6. Quiver Presentation

Quiver UI can also scroll/dynamically display ammunition stacks.

The quiver remains a specialized ContainerID with its own capacity.

Example:

`Leather Quiver`
- UI can render every stored arrow stack/type;
- physical maximum may still be 40 arrows or a mass/volume equivalent according to definition.

The ScrollBox does not make the quiver bottomless.

---

# 7. Trader / Commerce UI

Trader UI can display large stock catalogs/containers without fixed 36-slot assumptions.

This does not make trader storage infinite.

Vendor/business stock capacity may derive from:

- shop shelves;
- stockroom;
- warehouse;
- business inventory rules;
- transport/logistics;
- virtualized catalog backed by legitimate persistent stock records.

Player and trader sides can independently use scalable lists/grids.

---

# 8. Performance

For large inventories:

- prefer virtualized ListView/TileView when entry count is high;
- do not instantiate thousands of permanent hidden widgets if avoidable;
- update from container deltas/events;
- cache presentation snapshots;
- use soft references for heavy icons/assets;
- sorting/filtering should not rebuild every entry every frame.

---

# 9. Controller / Accessibility

Dynamic inventories must remain usable with:

- keyboard/mouse;
- Xbox-style controller;
- PlayStation-style controller.

Required:

- predictable focus across dynamically added rows;
- scroll follows focused item;
- clear container label (`Backpack`, `Quiver`, `Warehouse`, etc.);
- filtering/search alternatives for very large inventories;
- return focus after modal/options screens.

---

# 10. Acceptance Tests

1. UI displays more than 36 entries without clipping or authority changes.
2. Character cannot exceed physical carrying policy merely because the UI has more rows.
3. Pickup still fails with a clear reason when no legal capacity exists.
4. Craft output still follows destination/overflow policy.
5. Quiver ScrollBox does not bypass quiver capacity.
6. Trader stock UI can display large inventories without a fixed slot cap.
7. Widget child count never determines authoritative item capacity.
8. Large lists remain within frame-time budget using scalable presentation.
9. KBM/Xbox-style/PlayStation-style focus remains usable across dynamic content.

## Core Rule

> Metaworld inventories can be visually unbounded and dynamically scrollable, but every physical character/container still obeys its real slot, mass, volume, compartment and access rules. UI scalability never creates infinite carrying power.