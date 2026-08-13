# Metaworld — Commerce Buy / Sell / Quantity / Quote UI System

**Status:** Canonical / Approved Modern RPG Playlist Upgrade

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first / server-authoritative / event-driven / controller-complete

## Canonical Principle

Trading UI presents two sides of an authoritative commerce transaction: the player's eligible inventory and the vendor/business stock. The UI may request quotes and quantities, but it never performs the authoritative item/currency transfer itself.

> Commerce UI selects what to trade and how much. The economy service decides the quote, and the server commits the exchange.

Related canon:

- `Docs/NPC_Interaction_Trader_Merchant_Commerce_System.md`
- `Docs/Item_Valuation_Vendor_Pricing_Trade_System.md`
- `Docs/Gold_Material_Commodity_Not_Currency_Rule.md`
- `Docs/Inventory_Stack_Quantity_Selection_Drop_Transfer_UI_System.md`
- `Docs/RPG_Interface_Shell_Widget_Data_Contracts_Navigation_System.md`

---

# 1. Trader Screen

Suggested local interface:

`W_MW_TraderCommerce`

Possible sections:

- vendor stock;
- player sellable inventory;
- selected-item details;
- quantity selector;
- live quote / price breakdown;
- accepted currency indicator;
- player available payment source where appropriate;
- vendor/business purchasing capacity where intentionally exposed;
- Buy / Sell / Confirm / Cancel.

The two grids/lists are views over real ContainerIDs and ItemInstances.

Do not maintain copied `TraderInventory` and `PlayerInventory` arrays as the only gameplay truth inside the widget.

---

# 2. Buy / Sell Direction

Use stable transaction direction/state rather than duplicating separate widget types where one reusable entry can work.

Possible conceptual context:

- `CommerceDirection.BuyFromVendor`
- `CommerceDirection.SellToVendor`

An entry presentation snapshot can include:

- ItemInstanceID / stack-lot ID;
- source ContainerID;
- display name/icon;
- quantity available;
- condition/quality/rarity presentation;
- current quote state;
- allowed action(s).

A simple `IsBuyIcon` Boolean is acceptable for a prototype, but stable transaction context is preferred as the system grows.

---

# 3. Currency Rule

Normal commerce uses:

- GrimKoin;
- PromoKoin only where the vendor/business accepts it.

Never use tutorial Gold as the player's or merchant's money balance.

Physical Gold remains a persistent commodity/material ItemInstance and may itself be bought or sold for GrimKoin/PromoKoin.

Examples:

- `Buy Steel Sword — 130 GrimKoin`
- `Sell Gold Ingot — Vendor offers 85 GrimKoin`
- `PromoKoin not accepted`

Do not label physical Gold quantity as currency.

---

# 4. Authoritative Quote

The UI requests/receives a quote from the existing economy architecture.

Suggested request:

`RequestVendorQuote(ItemInstanceID, VendorID, Direction, Quantity)`

Possible returned fields:

- QuoteID;
- exact item/quantity;
- CurrencyType;
- UnitPrice;
- Subtotal;
- Tax;
- Fees;
- FinalPrice;
- quote expiry/revision;
- failure reason.

Quote inputs may include:

- item condition/quality/upgrades/affixes;
- vendor specialization;
- current supply/demand;
- legality/stolen/evidence state;
- taxes/fees;
- vendor funds/storage;
- relationship/reputation only where explicitly allowed;
- accepted currency.

The widget displays the quote; it does not independently calculate authoritative totals from a static Data Table price.

---

# 5. Buy Transaction

High-level flow:

`Player chooses item + quantity`
-> request/receive valid quote
-> confirm
-> server revalidates quote/stock/funds/capacity/legality
-> debit authorized GrimKoin/PromoKoin source
-> credit business/vendor ledger
-> transfer exact ItemInstance/quantity to player ContainerID
-> post taxes/fees
-> persist atomically
-> emit inventory/economy/UI deltas.

If any required validation fails, no partial purchase commits.

---

# 6. Sell Transaction

High-level flow:

`Player chooses owned item + quantity`
-> vendor quote
-> confirm
-> server validates ownership/possession/vendor policy/storage/funds/legality
-> transfer exact ItemInstance/quantity to vendor/business stock
-> debit vendor/business authorized payment source
-> credit player's authorized GrimKoin/PromoKoin source
-> post taxes/fees
-> persist atomically
-> emit deltas.

The player cannot be paid while keeping the same sold item, and the vendor cannot take the item without paying a committed accepted quote.

---

# 7. Vendor Inventory Capacity

Do not hardcode a universal `36 slots` limit for every merchant.

Each vendor/business stock source can define:

- slot capacity;
- mass/volume capacity;
- accepted item categories;
- shelf/storage/warehouse capacity;
- legal restrictions;
- current reserved stock;
- restock policy.

A small NPC personal trader may have very limited capacity; a warehouse-backed business may have much more.

---

# 8. Quantity Trading

Multiple-item buy/sell uses the canonical `W_MW_QuantitySelector`.

The selected quantity is advisory until server revalidation.

The quote should update when quantity changes where pricing/tax/discount rules require it.

For stackable items:

- quantity is integer;
- maximum comes from current authorized available amount;
- current state is re-resolved on confirm;
- one transaction moves the selected amount;
- stack split preserves all required metadata.

Do not loop one-item buy/sell N times when one quantity transaction is correct.

---

# 9. Failure Feedback

Failure reasons are data/state, not separate hardcoded Gold-specific notifications.

Possible result reasons:

- PlayerInsufficientFunds;
- VendorInsufficientFunds;
- VendorStorageFull;
- PlayerStorageFull;
- ItemNoLongerAvailable;
- ItemNotAccepted;
- IllegalOrRestricted;
- QuoteExpired;
- QuantityChanged;
- TradeContextInvalid;
- CurrencyNotAccepted.

The notification/HUD system converts these into localized player-facing messages.

Examples:

- `Not enough GrimKoin`
- `Vendor cannot afford this purchase`
- `Vendor has no storage for this item`

Never `Not enough Gold` unless the player literally lacks Gold material required for a crafting recipe rather than a commerce payment.

---

# 10. Price Labels On Entries

It is approved to show a current buy/sell amount directly on item entries so players do not need to open every tooltip.

Rules:

- label clearly identifies currency;
- price comes from current quote/quote snapshot;
- stale quote state is refreshed/invalidated when needed;
- price region can show `Not Buying`, `Unavailable`, etc.;
- tooltip/detail panel can expose full tax/fee breakdown.

Do not display a generic gold-coin glyph that confuses physical Gold with GrimKoin.

---

# 11. Tooltips / Detail Data

Trader tooltips use stable ItemInstanceID + commerce context and authorized presentation snapshots.

Do not add a permanently growing tooltip enum (`Inventory`, `Equipment`, `Trader`, `Chest`, etc.) when a generic source/context contract can resolve the correct item snapshot.

The same tooltip presentation system can display:

- item details;
- current vendor quote;
- comparison against equipped gear;
- quantity;
- legal/known state where appropriate.

---

# 12. UI Focus / Input

Opening commerce UI may restrict the local player's movement/look for usability, but does not pause Metaworld.

Use a proper modal/UI input layer:

- Enhanced Input / UI action routing;
- controller/keyboard/mouse navigation;
- predictable initial focus;
- Back/Cancel closes interface;
- no hardcoded `E` close requirement;
- no arbitrary delay to prevent immediate reopen;
- underlying gameplay interaction cannot keep firing while trade UI is active;
- switching input device remains supported.

Immediate reopen is prevented through interaction/menu state and input consumption, not timer-delay hacks.

---

# 13. Live Totals

Quantity UI may display local preview values such as:

- quantity;
- estimated/quoted total price;
- total mass transferred;
- resulting carried load preview.

These are presentation calculations from current snapshots/quotes.

Server revalidates final:

- transaction total;
- current quote;
- capacity;
- carried-load result;
- funds;
- quantity.

A client-side total never authorizes the trade.

---

# 14. Event-Driven Refresh

Refresh the affected UI when:

- vendor stock changes;
- player inventory changes;
- quote changes/expires;
- player/vendor funds relevant to the visible context change;
- selected ItemInstance changes;
- trade commits/fails;
- NPC/business availability changes.

Do not rebuild both inventory grids every frame.

---

# 15. Commerce Context Invalidates Safely

Trade may become unavailable if:

- NPC walks away;
- NPC is incapacitated/killed;
- combat begins;
- shop closes;
- ownership/employment/service state changes;
- business loses authorization;
- player loses interaction range;
- session/connection state changes.

An outstanding quote may be canceled/invalidated and no transaction can commit after the required context is gone.

---

# 16. Acceptance Tests

1. Player buys exact ItemInstance/quantity using GrimKoin/PromoKoin only.
2. Physical Gold item may be sold as merchandise but never becomes currency balance.
3. Vendor stock and player inventory remain real Container/Item state.
4. Different vendors can return different quotes for the same item.
5. Quantity buy/sell reuses canonical quantity selector.
6. Double-confirm cannot duplicate item or payment.
7. Player insufficient funds yields localized failure without state change.
8. Vendor insufficient funds/storage yields correct failure without state change.
9. Quote expiration forces revalidation.
10. UI price labels identify the actual currency.
11. Trade UI supports KBM/Xbox-style/PlayStation-style navigation.
12. Closing trade does not require an arbitrary delay before interaction works again.
13. Background gameplay interaction cannot trigger through the active modal.
14. NPC becoming unavailable prevents further trade commit.
15. UI refreshes from deltas/events without per-frame polling.

## Core Rule

> Commerce UI never owns stock, money or final prices. It selects an exact trade, asks the authoritative economy for a quote, and submits one atomic transfer of ItemInstances and GrimKoin/PromoKoin.