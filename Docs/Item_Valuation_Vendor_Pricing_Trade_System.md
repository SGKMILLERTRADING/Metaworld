# Metaworld — Item Valuation, Vendor Pricing & Trade System

**Status:** Canonical / Approved Modern RPG Playlist Upgrade

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first / server-authoritative / persistent economy

## Canonical Principle

An item may have a reference/base value for data authoring and UI, but the actual amount a buyer pays or a seller receives is determined by the authoritative economy transaction at the time of trade.

> `Reference value` is metadata. `Buy price` and `sell offer` are contextual economic results.

Related canon:

- `Docs/Persistent_Item_Interaction_Inventory_Architecture.md`
- `Docs/Banking_Currency_Custody_Future_Cashout.md`
- `Docs/HUD_Notification_Feedback_System.md`
- `Docs/Stats_Attributes_Item_Modifiers_Encumbrance_System.md`

---

# 1. No Tutorial Gold Price Currency

The tutorial's generic Gold price display is not adopted as a new currency.

Canonical currencies remain:

- GrimKoin;
- PromoKoin.

Any price display must state the actual currency type used by that transaction.

Possible examples:

- `120 GrimKoin`
- `45 PromoKoin`
- `Not for sale`
- `Vendor will not buy this item`

A future market may support different accepted payment methods, but no third default `Gold` balance is introduced.

---

# 2. Definition-Level Reference Value

An Item Definition may contain economy metadata such as:

- `ReferenceValue`
- `ReferenceCurrencyType`
- `VendorCategoryTags`
- `TradablePolicy`
- `SellablePolicy`
- `BuyablePolicy`
- `LegalMarketTags`
- `TaxCategory`
- `ScarcityCategory`
- `CreatorRoyaltyProfileID` where applicable
- `PriceProfileID`

This value is useful for:

- designer balancing;
- loot generation;
- NPC decision heuristics;
- sorting/filtering;
- approximate appraisal;
- fallback vendor calculations.

It is not a guaranteed universal shop price.

---

# 3. ItemInstance Valuation Inputs

The exact persistent item may change the effective value.

Possible factors:

- condition/durability;
- quality;
- modifications/upgrades;
- creator/crafted provenance;
- rarity/presentation classification where a market explicitly values it;
- historical significance;
- legal/stolen/evidence status;
- freshness/spoilage;
- ammunition/fuel/contents;
- cosmetic/custom appearance;
- regional scarcity;
- supply/demand;
- current event effects;
- authenticity/verification;
- business/customer reputation where explicitly allowed;
- vendor specialization.

Rarity alone does not determine price.

---

# 4. Buy Price vs Sell Offer

A vendor's price to sell an item and its offer to buy that item are separate calculations.

Example:

Reference Value = 100 GK

Possible shop result:

- Player buys from vendor for 130 GK
- Vendor offers player 65 GK

The difference may reflect:

- operating margin;
- taxes/fees;
- business costs;
- risk;
- storage demand;
- item condition;
- local supply/demand;
- legality;
- vendor type.

Do not store one static `Price` and one static `SellPrice` as permanent truth for every shop in the world.

They may exist as optional default/fallback authoring values, but the transaction service calculates the actual quote.

---

# 5. Authoritative Quote

Suggested concept:

`RequestVendorQuote(ItemInstanceID, VendorID, TransactionDirection, Quantity)`

Server resolves:

- item definition/instance;
- vendor inventory/business rules;
- currency type;
- item condition/quality;
- current market profile;
- taxes/fees;
- available vendor funds/storage;
- legal restrictions;
- quantity/stack rules;
- owner/possession rights.

Result may include:

- `QuoteID`
- `ItemInstanceID` or Definition/Quantity
- `CurrencyType`
- `UnitPrice`
- `Quantity`
- `Subtotal`
- `Tax`
- `Fees`
- `FinalPrice`
- `ExpiresAt`
- `FailureReason` if unavailable

The UI displays the quote; it does not calculate the authoritative transaction total independently.

---

# 6. Atomic Vendor Transaction

Purchase:

`Player accepts valid quote`
-> server revalidates quote/stock/funds/capacity
-> debit carried wallet or other explicitly supported payment source
-> credit business/vendor ledger
-> transfer ItemInstance/quantity to player container
-> tax/fees post to correct ledgers
-> persist atomically
-> replicate authorized result
-> notification/receipt UI updates

Sale to vendor:

`Player accepts vendor offer`
-> server verifies ownership/possession/legal state
-> verifies vendor can buy/store/pay
-> transfers item to vendor/business inventory
-> debits vendor funds
-> credits player's carried wallet or defined account
-> taxes/fees post
-> persist atomically
-> notification/receipt UI updates

No partial state should leave the player paid while retaining the item, or charged without receiving it.

---

# 7. Stolen / Illegal / Evidence Items

Not every vendor buys every item.

Possible rules:

- legitimate shop rejects known stolen property;
- regulated item requires license/permit;
- evidence in official custody cannot be casually sold;
- black-market/fence systems may later accept illicit goods under their own risk/rules;
- selling stolen property can generate evidence/crime consequences;
- ownership history persists after transfer.

A tooltip may show legal status only if the viewing character legitimately knows it.

---

# 8. Descriptions

Item Definitions may contain localized presentation fields such as:

- DisplayName
- ShortDescription
- LongDescription
- Lore/Manufacturer text where appropriate
- Usage/requirement notes

Descriptions are presentation/content data, not gameplay authority.

They may be multi-line and should use localization-ready text rather than hardcoded widget strings where practical.

Instance-specific details such as condition, creator, modifications, provenance or legal status are resolved separately and appended to the detail view only when appropriate.

---

# 9. Tooltip / Inventory Presentation

A tooltip can display:

- description;
- reference/appraised value if the design wants it;
- current vendor buy price when shopping;
- current vendor sell offer when selling;
- currency icon/type;
- taxes/fees when relevant;
- `Not for sale` / `Vendor will not buy` state;
- quote expiry/changed-price feedback when needed.

Outside an active vendor context, avoid presenting a dynamic shop price as if it were guaranteed everywhere.

Possible neutral labels:

- `Reference Value`
- `Estimated Value`
- `Appraised Value`

rather than simply `Sell Price` when no vendor quote exists.

---

# 10. Player-to-Player Trade

Direct player trade uses the same persistent ItemInstance and currency ledgers.

A trade offer may include:

- ItemInstance IDs / stack quantities;
- GrimKoin;
- PromoKoin where allowed;
- both parties' container capacity;
- ownership/legal checks.

Both sides commit atomically after final confirmation.

No UI drag/drop or client array swap is authoritative.

---

# 11. Performance

- quote calculations are event/request-driven;
- no per-frame market-price polling in ordinary inventory tooltips;
- cache short-lived quotes with expiration where useful;
- market changes invalidate/reprice only when necessary;
- unloaded shops/items remain data records;
- UI refreshes when context/quote/item state changes.

---

# 12. Acceptance Tests

1. Tutorial Gold is not introduced as a third main currency.
2. One Item Definition can have different buy/sell prices at different vendors.
3. Condition can change effective value without changing ItemDefinitionID.
4. Rarity alone does not dictate price.
5. Vendor cannot pay for an item without receiving it.
6. Player cannot be charged without receiving purchased item/quantity.
7. Taxes/fees post to the correct ledgers.
8. Stolen/illegal item rules affect vendor eligibility correctly.
9. Tooltip shows reference value outside vendor context and live quote in vendor context.
10. Description collapses cleanly when empty.
11. Controller and keyboard/mouse can inspect/accept/reject quotes.
12. Player-to-player trade commits both sides atomically.
13. Save/load preserves item ownership and business/player ledgers.
14. UI does not use per-frame bindings to calculate prices.

## Core Rule

> Metaworld items may have reference value, but real prices come from a specific buyer, seller, place and moment in the living economy. Currency and ownership move only through authoritative transactions.