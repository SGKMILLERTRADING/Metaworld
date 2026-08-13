# Metaworld — Loot Containers, Bags, Corpses, Chests & Transfer System

**Status:** Canonical / Approved Modern RPG Playlist Upgrade

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first / server-authoritative / persistent / container-unified / controller-complete

## Canonical Principle

Loot bags, corpses and chests are different world presentations of the same authoritative Container/Item transfer architecture. Their persistence, access and destruction rules differ, but taking an item always moves real ItemInstance state between real containers.

> Loot UI never manufactures or deletes the inventory truth. It selects ItemInstances/quantities from a source ContainerID and requests authoritative transfer.

Related canon:

- `Docs/Persistent_Item_Interaction_Inventory_Architecture.md`
- `Docs/Loot_Generation_Tables_Drops_Provenance_System.md`
- `Docs/Inventory_Stack_Quantity_Selection_Drop_Transfer_UI_System.md`
- `Docs/HUD_Notification_Feedback_System.md`
- `Docs/Interaction_Hold_Progress_Modal_Input_State_System.md`

---

# 1. Unified Loot Source Contract

Any lootable source exposes a real `ContainerID` plus access/interact rules.

Possible source types:

- corpse/body inventory;
- temporary loot bag;
- persistent chest;
- crate/cache;
- safe/cabinet;
- dropped bundle;
- vehicle/storage container;
- business/world container.

UI does not need separate transfer logic for each source type.

---

# 2. Loot Bag

A loot bag is an optional world presentation/container wrapper.

Possible uses:

- compactly represent multiple dropped ItemInstances after death;
- avoid spawning many loose item Actors;
- provide one interactable target;
- support visible/highlighted loot presentation.

Suggested identity:

- `LootBagActorID` / world object identity;
- `ContainerID` for contents;
- source CharacterID/EventID where relevant;
- cleanup/persistence policy.

When empty, a temporary loot bag may despawn after the authoritative container is confirmed empty and no transaction/reservation remains.

Do not destroy the bag first and hope the items transferred.

---

# 3. Corpse / Body Inventory

A dead character may expose reachable physical possessions according to death/estate/crime rules.

Rules:

- equipped/carried ItemInstances move into corpse/body/death-container state according to the death system;
- looting may be theft/crime/evidence depending on ownership/context;
- banked GrimKoin/accounts never become corpse container contents;
- estate/inheritance rights remain separate from physical reachability;
- permanent death remains unchanged.

A loot bag may be used as presentation, but it must not duplicate the actual corpse possessions.

---

# 4. Persistent Chest

A chest is a normal persistent world container with additional world presentation/interactions.

Possible state:

- Chest WorldObjectID;
- ContainerID;
- owner/property association;
- lock/security state;
- open/closed/animation state;
- loot profile seed state where initially generated;
- persistence revision;
- access/permission rules;
- destruction/damage state.

A chest does not disappear simply because it becomes empty unless its specific world-object policy says so.

---

# 5. Temporary vs Persistent Containers

Temporary loot bag:

- can despawn after empty + safe cleanup conditions.

Corpse/body:

- lifetime follows corpse/death/world cleanup policy.

Chest/safe/warehouse:

- persistent even when empty;
- contents change through real transfers/restock.

Do not use one `if empty -> Destroy Actor` rule for every loot source.

---

# 6. Loot UI

Suggested local widget:

`W_MW_LootContainer`

Possible content:

- source name/type;
- item list/grid;
- selected item details;
- stack quantity;
- `Take`;
- `Take All`;
- `Close`;
- source capacity/ownership status where useful.

The widget receives source ContainerID and presentation snapshots, not a copied authoritative inventory array.

---

# 7. Take One / Selected Item

Suggested request:

`RequestTransferItem(ItemInstanceID, SourceContainerID, TargetContainerID, Quantity)`

Server validates:

- source still contains exact item/quantity;
- requester has interaction/access rights;
- target can accept it;
- stack compatibility/capacity;
- reservations/concurrent looters;
- theft/legal rules;
- interaction context remains valid.

On commit, the source and target deltas update the UI.

Do not remove the widget child first and treat that as successful pickup.

---

# 8. Take All

`Take All` is not a blind client loop that assumes every transfer succeeds.

Possible server policy:

- evaluate transferable items;
- reserve/commit a multi-item transaction atomically where feasible;
- or process a deterministic batch with explicit per-item results;
- stop/skip according to target capacity and legality rules;
- return a result summary.

Possible outcomes:

- all transferred;
- partial because capacity;
- some items restricted/locked;
- failed because source changed.

UI clearly reports the outcome.

No item may vanish because the client's list cleared before the server committed.

---

# 9. Multiple Looters / Concurrency

Two players may access the same corpse/chest/bag.

Server owns reservations and current contents.

If both select the same final sword:

- one valid transaction commits;
- the other receives ItemNoLongerAvailable/current-state refresh.

Do not give each client an independent copy of the source array.

---

# 10. Empty State

Loot UI can show:

- `Empty`;
- no available items;
- source locked/restricted;
- contents changed.

The interaction prompt can expose `Empty` rather than opening a pointless full menu where appropriate.

Empty is presentation derived from authoritative ContainerID state.

---

# 11. Loot Highlight / Niagara

Loot bags/important drops may use Niagara or other presentation highlights.

Rules:

- effect communicates visibility/significance only;
- effect does not determine rarity/ownership;
- scalability/Effect Type/culling policy required;
- avoid one expensive always-active Niagara instance for every trivial drop;
- distant/low-value loot can use cheaper or no effect;
- stop/destroy effect when object is hidden/despawned.

The tutorial orange glow is a presentation option, not a universal rarity color.

---

# 12. Tooltip

Loot item tooltip uses the common ItemInstance presentation snapshot.

No separate `LootTooltipItemInfo` gameplay copy is needed.

The UI may build the tooltip then assign/update snapshot data, or construct with the snapshot; either is acceptable if lifecycle is event-driven and stable IDs remain the source.

Do not rely on raw per-frame bindings.

---

# 13. World Does Not Pause

Opening corpse/chest/loot UI does not globally pause Metaworld and does not use global time dilation.

World physics, enemies, players and NPCs continue according to normal rules.

The local player input layer may restrict movement/look while the loot modal is active according to UX policy.

---

# 14. Camera Collision

NPC/accessory collision should not trap the player camera unnecessarily.

Camera collision presets may ignore meshes/accessories where the camera system is intended to pass through/around them while the Character capsule/world obstruction rules remain correct.

Do not disable gameplay collision solely to fix camera collision; use appropriate collision channels/profiles.

---

# 15. Persistence

Persist:

- source ContainerID and contents;
- seeded/generated state;
- ownership/access/lock state;
- world object identity/location where applicable;
- temporary cleanup state only as required;
- transfer revisions/transactions.

Reopening a persistent chest does not regenerate its contents unless an explicit restock/world rule ran.

---

# 16. Controller Compatibility

Required actions:

- open loot source;
- navigate entries;
- inspect tooltip;
- Take selected;
- Take All;
- quantity selection where stack action requires it;
- close/back;
- predictable focus after item disappears.

No essential loot action may depend on mouse hover/click or hardcoded `E/R/F` keys.

---

# 17. Acceptance Tests

1. Loot bag, corpse and chest all expose ContainerID-based transfer.
2. Taking an item transfers exact ItemInstance/quantity once.
3. Two players cannot both take the same final item.
4. `Take All` handles capacity/restrictions without silent loss.
5. Temporary empty loot bag despawns only after authoritative empty state.
6. Empty persistent chest remains in world.
7. Corpse loot preserves theft/evidence/ownership rules.
8. Banked GrimKoin never appears in corpse loot.
9. Loot UI does not globally pause/time-dilate world.
10. Tooltip reads common item presentation state.
11. Niagara loot highlight obeys scalability/culling.
12. Chest contents persist across reopen/save/load without reroll.
13. Controller/keyboard/mouse all support Take/Take All/Close.
14. Camera collision fix does not disable unrelated gameplay collision.

## Core Rule

> Every loot source is a real container with its own lifecycle and access rules. Looting moves persistent items under server authority; bags, corpses, chests, widgets and visual effects are only different ways to present and access that shared truth.