# Metaworld — Persistent Item, Interaction & Inventory Architecture

**Status:** Canonical / Approved Modern RPG Playlist Upgrade

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first / server-authoritative / persistent

## Canonical Principle

World items, inventory entries, containers, loot, trade and pickup all represent the same persistent item system viewed in different locations/states.

> An item does not stop existing when it enters inventory. Metaworld tracks what kind of item it is, which exact copy it is, who owns/possesses it, its condition and where it currently resides.

This extends Master Roadmap Phase 9 (Universal Item DNA), Phase 10 (Object Capabilities) and Phase 11 (Inventory & Containers).

---

# 1. Definition vs Instance

Metaworld separates two identities.

## `ItemDefinitionID`
Defines the item type/catalog entry.

Possible definition data:

- name/localization key
- description
- category/tags
- world mesh / skeletal representation
- inventory icon
- max stack policy
- mass/volume/dimensions
- material/class
- capabilities
- equipment slot compatibility
- durability rules
- value/vendor rules
- crafting tags/ingredients later
- soft asset references
- physics/collision profile
- rarity/presentation metadata where useful

## `ItemInstanceID`
Identifies one exact persistent copy or stack record where instance identity is required.

Possible instance state:

- `ItemInstanceID`
- `ItemDefinitionID`
- quantity
- owner/legal owner
- current possessor/container
- condition/durability
- quality/variant
- creator/provenance
- custom name/appearance where permitted
- stolen/evidence/history flags
- timestamp/history references
- persistence revision

Do not use an enum of every item name as the scalable identity system. Enums may be useful for small closed categories, but catalog items use stable data IDs.

---

# 2. World Item Actor

Recommended common world representation:

`BP_MW_ItemWorldActor`

Responsibilities:

- reference authoritative `ItemInstanceID` / definition;
- present the appropriate mesh/material;
- expose interaction options through `BPI_MW_Interactable`;
- participate in pickup/drop/loot/inspect/use rules;
- use appropriate simple collision;
- simulate physics only while relevant/required;
- sleep/disable expensive simulation when settled or insignificant;
- preserve world ownership/evidence state.

Do not create one unique child Blueprint for every ordinary item when data alone can describe it. Child Blueprints/components are reserved for genuinely unique behavior.

---

# 3. Asset / Collision Authoring

The tutorial's simple/auto-convex collision workflow is approved as an authoring starting point.

Metaworld rules:

- prefer authored simple collision appropriate to the object;
- auto-convex is a starting tool, not guaranteed final collision quality;
- avoid expensive complex/per-poly physics collision by default;
- pickup/interact query shape may be simpler than physical collision;
- physics mass/material behavior should reflect definition data where practical;
- Nanite may be used for compatible static item meshes while collision/gameplay stays explicit.

Current content acquisition should use the UE5.8/Fab workflow rather than treating deprecated Quixel Bridge as a permanent dependency.

---

# 4. Interaction / Targeting

Items use the existing common interaction architecture.

Recommended flow:

`Enhanced Input IA_Interact`
-> `BPC_MW_Interaction`
-> relevant view/proximity target resolution
-> `BPI_MW_Interactable`
-> display valid options
-> submit authoritative request

Possible actions:

- Pick Up
- Inspect
- Use
- Equip
- Open Container
- Loot
- Move/Carry
- Drop
- Trade later

The tutorial's hardcoded `E` input is not canonical.

A proximity Sphere Overlap may be used as an optimization/candidate source where useful, but do not maintain duplicate interaction truth or unlimited candidate arrays. The common interaction component resolves the final target/action.

---

# 5. Pickup Is a Transaction

Tutorial behavior that destroys the Actor is upgraded.

Canonical pickup:

`RequestPickup(ItemInstanceID, TargetInventoryID)`

Server validates:

- item exists and is available;
- requester can reach/interact with it;
- ownership/theft/world rules;
- target inventory/container permission;
- target capacity/weight/volume/slot rules;
- stack compatibility;
- item is not reserved/locked by another transaction.

If valid:

1. reserve/lock the item transaction;
2. remove it from world location state;
3. merge into a compatible stack or create an inventory entry;
4. persist owner/possessor/container/location change;
5. remove/despawn the world Actor representation;
6. replicate compact inventory/world updates.

If any required step fails, the item remains in the world.

`Destroy Actor` is presentation cleanup after successful transfer, not the definition of pickup.

---

# 6. Inventory Component / Container Contract

Recommended player component:

`BPC_MW_Inventory`

But the same container contract should support:

- player pockets
- backpacks
- boxes/chests
- refrigerators
- cabinets
- safes
- vehicle cargo
- warehouses
- stores
- construction-site storage
- corpse/death inventories where world rules permit

Suggested stable container identity:

`ContainerID`

Possible container rules:

- slot count
- weight capacity
- volume capacity
- allowed/forbidden item tags
- compartment rules
- access permissions
- lock/security state
- owner/property association

Inventory logic does not live primarily in the Player Character Event Graph.

---

# 7. Stacking

Stacking is allowed only when the authoritative definition/state says two item records are compatible.

Basic rules can include:

- same `ItemDefinitionID`;
- definition allows stacking;
- quantity does not exceed `MaxStack`;
- state that must remain unique is compatible.

Do not blindly merge items if it would erase meaningful persistent differences such as:

- durability/condition;
- quality;
- ownership/provenance;
- stolen/evidence status;
- ammunition subtype;
- custom modifications;
- expiry/spoilage state;
- creator identity.

For stackable commodities, Metaworld may use compact quantity records while preserving any required lot/provenance data.

---

# 8. Inventory UI

The tutorial's grid/list visual idea is approved, but UI is a view of inventory state, not the authoritative inventory itself.

Recommended UI:

- grid and/or list presentation;
- icon;
- stack quantity;
- item name;
- condition/quality where useful;
- weight/space feedback;
- equipped/locked/stolen/status indicators where legitimate knowledge permits;
- controller focus/navigation;
- sort/filter/search where inventory scale justifies it;
- tooltips/detail panel;
- contextual actions.

Do not store the real inventory only as Widget children.

Do not rebuild every icon every frame. Refresh from inventory change events/deltas and use scalable list/grid presentation for large containers.

The tutorial's fixed `T` key and mouse-only cursor/input-mode workflow becomes Enhanced Input + controller-friendly UI routing.

Pausing the entire game to open inventory is not appropriate for normal persistent multiplayer gameplay. UI can open while world time continues unless a specific single-player/debug context deliberately allows pause.

---

# 9. Loot / Corpse / Theft Integration

The same inventory transfer contract supports looting.

A corpse/body/container does not grant universal ownership merely because it is interactable.

Transfers may create:

- theft/crime state;
- witness/camera evidence;
- inheritance/estate claims;
- faction/property conflict;
- stolen-item provenance;
- police recovery state.

Permanent-death rules remain intact: reachable physical property may be taken according to world rules, while banked currency/accounts remain protected by the banking/estate architecture.

---

# 10. Trading

Future trading uses atomic item/currency transfer rather than client-side array swaps.

A trade transaction can validate both offers, permissions, item states, GrimKoin/PromoKoin values where included, capacity, and ownership before committing both sides together.

No partial trade completion should leave one side paid while the other side keeps the item.

---

# 11. Persistence / Replication

Persist world truth by stable IDs.

Inventory save state stores compact item/container records, not Widget state or transient Actor pointers.

Replication sends only inventory information relevant to the owning/authorized connection.

Do not replicate a player's full private inventory to unrelated nearby clients.

World pickup/drop uses server authority; clients receive resulting state.

---

# 12. Performance

- no permanent physics simulation for every loose item in the world;
- settled/distant items sleep or use lower-cost representation;
- no global item scans;
- proximity candidate lists are bounded and event-driven;
- UI refreshes on changes, not Tick;
- heavy assets use soft references where practical;
- containers can stream/paginate/virtualize large inventories;
- unloaded containers exist as persistent data without active Actors.

---

# 13. Controller Compatibility

Required with keyboard/mouse, Xbox-style and PlayStation-style controllers:

- target item;
- interact/pick up;
- open/close inventory;
- navigate grid/list;
- inspect item;
- move/split stack where supported;
- equip/use/drop;
- move between containers;
- confirm/cancel trade/transfer.

No core inventory action may require mouse-only drag-and-drop as its only path.

---

# Core Rule

> Metaworld inventory is persistent world ownership/location data with a UI on top. Pickup moves an authoritative item from the world into a container; it never becomes real merely because a client destroyed an Actor or appended a local array.