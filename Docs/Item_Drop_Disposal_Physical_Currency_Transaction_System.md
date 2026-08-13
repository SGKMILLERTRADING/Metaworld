# Metaworld — Item Drop, Disposal & Physical Currency Transaction System

**Status:** Canonical / Approved Modern RPG Playlist Upgrade

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first / server-authoritative / persistent

## Canonical Principle

Dropping, discarding, destroying and converting a physical currency pickup are authoritative state transitions on persistent world records.

> A drop moves an existing ItemInstance from a container to the world. It does not create a duplicate replacement item and then delete the original as an unrelated operation.

Related canon:

- `Docs/Persistent_Item_Interaction_Inventory_Architecture.md`
- `Docs/Banking_Currency_Custody_Future_Cashout.md`
- `Docs/HUD_Notification_Feedback_System.md`

---

# 1. Drop Item Transaction

Recommended request:

`RequestDropItem(ItemInstanceID, Quantity, RequestedDropContext)`

Server validates:

- requester possesses/controls the item;
- item is not locked/reserved by another transaction;
- item is allowed to leave the current container/equipment state;
- requested stack quantity is valid;
- equipment conflicts are resolved first if the item is equipped;
- the world location is legal/valid for spawning or placing the item;
- ownership/property/world rules that apply to dropping/discarding are satisfied.

If valid:

1. reserve the item/quantity transaction;
2. split the stack only if necessary and legal;
3. remove the ItemInstance/quantity from the source container;
4. set world-location state on the same ItemInstance or newly split persistent stack record;
5. spawn/enable the approved `BP_MW_ItemWorldActor` presentation;
6. apply world mesh/collision/physics profile;
7. persist the move;
8. replicate the resulting world/container delta;
9. emit local notification feedback.

If the transaction fails, the item remains in the original container/equipment state.

## Drop Placement

Do not blindly spawn every dropped item at a fixed forward-vector offset.

The server may use:

- character position/facing as a starting request;
- short ground/support trace;
- item bounds;
- obstruction checks;
- property/zone rules;
- safe fallback point near the character.

This prevents items appearing inside walls, below terrain, inside another character, or in invalid inaccessible locations.

---

# 2. Dropped Item Data

The tutorial's separate `dropped item info` variable fixes an overwrite bug, but Metaworld solves the underlying problem with stable persistent identity.

`BP_MW_ItemWorldActor`
-> `ItemInstanceID`
-> authoritative Item Definition + Instance state

The world presentation resolves its mesh/material/condition/variant from that stable record.

Do not keep two mutable copies of the same authoritative item-info struct and hope they remain synchronized.

---

# 3. Context / Options Menu

A contextual item options menu is approved.

Possible actions:

- Equip / Unequip
- Use
- Inspect
- Drop
- Split Stack
- Move To Container
- Give / Trade
- Favorite / Lock
- Discard / Destroy when permitted

Mouse right-click may open it, but it must also be reachable by keyboard and controller focus/action input.

Do not make screen-positioned right-click UI the only path.

The menu is a presentation of currently valid actions for the focused ItemInstance; it does not own the item transaction logic.

---

# 4. Destroy / Discard Is Not Universal Delete

A `Destroy` button is not allowed to erase every persistent item record unconditionally.

Item Definitions / world rules may classify whether an item can be:

- dropped;
- discarded as trash;
- dismantled/salvaged;
- consumed;
- physically destroyed;
- transferred to a waste/recycling system;
- protected from casual deletion.

Protected examples can include:

- evidence items under custody rules;
- leased/borrowed items;
- certain property documents/keys/credentials;
- bound mission/world objects where deletion would break state;
- items reserved in active trade/transaction;
- equipped items until properly unequipped;
- items with legal/ownership restrictions where disposal has consequences.

When an item truly ceases to exist, the server records the terminal reason/history before removing active inventory/world representation.

Destroying an item may create:

- salvage/waste outputs when defined;
- property/economic loss;
- evidence/history consequences;
- crime consequences if it was not legally yours;
- notification feedback.

It must never be a client-only `Remove Array Element` shortcut.

---

# 5. Physical Currency Pickup — No New Gold Currency

The tutorial's `Gold` integer is **not** adopted as a third Metaworld main currency.

Canonical currencies remain:

- GrimKoin — primary valuable currency;
- PromoKoin — easier/common limited currency.

The tutorial pattern is retained only as a lesson for physical currency pickup/loot and UI feedback.

Possible world currency presentation:

`CurrencyPickupRecord`
- CurrencyType = GrimKoin or PromoKoin
- Amount
- WorldLocation / container source
- provenance/source reference
- transaction/reservation ID

On pickup:

1. client requests interaction;
2. server validates the physical currency source still exists and is reachable/lootable;
3. server reads the authoritative amount and currency type;
4. source is reserved/consumed;
5. carried wallet/physical-currency balance is credited through the authoritative ledger;
6. transaction commits atomically;
7. world presentation is removed;
8. local notification displays the credited amount.

Do not trust a client-supplied amount.

## Random Currency Amounts

Randomized loot amounts are allowed only when generated by an authoritative loot/reward system from approved ranges/tables.

The world record stores the rolled amount once.

Do not reroll currency every time a client inspects/interacts with the same pickup.

## Carried vs Banked Currency

Physical pickups credit **carried** GrimKoin/PromoKoin unless another explicit system says otherwise.

They do not silently deposit into the player's private bank account.

Banked GrimKoin still requires the banking/deposit rules in the canonical banking architecture.

---

# 6. Currency Presentation Is Not Currency Truth

A coin bag/coin stack/wallet mesh can visually represent a currency pickup, but the mesh does not define the amount.

One bag mesh may represent 5 GrimKoin or 500 GrimKoin if the authoritative record says so.

Likewise, rarity styling does not change currency value.

The UI should display:

- currency type;
- exact credited amount;
- carried balance where authorized/useful;
- transaction feedback.

Balance widgets refresh from ledger/wallet state changes rather than per-frame Player Blueprint bindings.

---

# 7. Multiplayer / Anti-Duplication Rules

Two clients attempting to pick up/drop/move the same ItemInstance or currency source are serialized by the server.

Required safeguards:

- transaction reservation/lock;
- one authoritative source state;
- idempotent request handling where appropriate;
- one committed terminal result;
- no source removal without destination/world credit;
- no destination credit without source debit/removal;
- no client-authored wallet balance.

---

# 8. Acceptance Tests

1. Dropping an item preserves the same ItemInstanceID.
2. Split-stack drop creates only the legitimate split record/quantity.
3. Drop cannot duplicate an equipped/inventory item.
4. Dropped item resolves correct mesh/variant/condition from persistent data.
5. Invalid drop location falls back or rejects safely.
6. Controller/keyboard can open the same item options as mouse right-click.
7. Protected items reject unauthorized destroy/discard.
8. Legitimate destroy/discard records the terminal state without duplication.
9. GrimKoin physical pickup credits carried GrimKoin only after server validation.
10. PromoKoin physical pickup behaves according to the same transaction contract.
11. No third `Gold` currency is created.
12. Randomized currency amount is rolled/stored authoritatively once.
13. Two simultaneous pickup attempts produce one winner/one source removal.
14. Notifications fire only after committed results.
15. Save/load restores dropped persistent items and wallet ledger state correctly.

## Core Rule

> Persistent items and currency move through authoritative transactions. UI buttons, world Actors and pickup meshes are representations and requests—not ownership, identity, or balance truth.