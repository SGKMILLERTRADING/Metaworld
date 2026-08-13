# Metaworld — NPC Interaction, Trader / Merchant & Commerce System

**Status:** Canonical / Approved Modern RPG Playlist Upgrade

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first / server-authoritative / persistent / AI-native / business-integrated

## Canonical Principle

NPCs expose context-sensitive interactions through the common Interaction system. A trader/merchant is a living NPC role connected to real persistent stock, business rules and currency ledgers—not a special UI Actor containing a fake Gold balance.

> Talk/trade is an interaction with a world character. Buying and selling transfers real ItemInstances and GrimKoin/PromoKoin through authoritative commerce transactions.

Related canon:

- `Docs/Persistent_Item_Interaction_Inventory_Architecture.md`
- `Docs/Item_Valuation_Vendor_Pricing_Trade_System.md`
- `Docs/Gold_Material_Commodity_Not_Currency_Rule.md`
- `Docs/RPG_Interface_Shell_Widget_Data_Contracts_Navigation_System.md`
- `Docs/Generated_Item_Base_Stats_Affixes_Quality_System.md`

---

# 1. Base NPC Architecture

A shared NPC character foundation is approved, but Metaworld avoids a deep inheritance tree such as:

`BaseNPC -> TraderNPC -> WeaponTraderNPC -> RareWeaponTraderNPC -> ...`

Preferred architecture uses shallow character classes plus components/data/capabilities.

Conceptual NPC foundation may include:

- `BP_MW_NPC_Master`
- AI/StateTree behavior component/brain integration;
- Needs/Vitals where appropriate;
- Inventory/Container access;
- Interaction provider;
- Profession/Job role data;
- Reputation/relationship state;
- ownership/business/faction links;
- schedule/home/workplace data;
- combat/status-effect capabilities where applicable.

A trader/innkeeper/police officer/doctor can expose different actions according to role/context without requiring completely separate interaction infrastructure.

---

# 2. Common Interaction Contract

NPCs use the existing:

`BPC_MW_Interaction`
-> `BPI_MW_Interactable`
-> available interaction actions

Possible NPC actions:

- Talk
- Trade
- Ask Information
- Hire / Work interaction
- Medical Service
- Report Crime
- Quest / Task
- Bribe where world/legal rules support it
- Threaten / Rob where combat/crime systems support it
- Inspect credential / official actions
- other profession/context actions.

The Player HUD displays the currently valid action/glyph through the common interaction prompt.

Hardcoded `E` is not canonical.

---

# 3. Facing / Visibility / Reach

The tutorial's dot-product facing check is a useful candidate-quality rule.

Metaworld interaction eligibility can consider:

- distance/reach;
- view direction / dot-product cone;
- line of sight / obstruction;
- target significance/priority;
- NPC availability/state;
- player/NPC incapacitation/combat state;
- role/permission/context.

Do not run a permanent 10 Hz orientation timer on every NPC in the world.

Preferred flow:

- proximity/trace/interaction resolver identifies a bounded nearby/current candidate;
- facing/LOS checks run only while relevant or when view/target changes;
- current prompt updates event-driven/bounded as required.

NPC AI itself remains independent of whether the local player currently sees an interaction prompt.

---

# 4. NPC Role / Service Capabilities

A trader capability/service profile can define:

- BusinessID / EmployerID where applicable;
- service/vendor profile;
- goods categories bought/sold;
- legal/illegal market policy;
- accepted currency types;
- business hours/schedule;
- markup/markdown/quote rules;
- stock source container(s);
- cash/ledger payment source;
- profession/licensing requirements;
- dialogue/relationship effects;
- security/theft response;
- tax profile.

An NPC may have multiple roles and services where world design supports it.

---

# 5. Trader Inventory Is Persistent Stock

Trader stock uses the same ItemInstance/container system as player items.

Possible stock locations:

- shop shelf/container;
- counter stock;
- storeroom;
- business warehouse;
- NPC carried inventory;
- delivery shipment.

UI may present an authorized catalog view over those sources without converting them into a disconnected `ItemsToSell` array that becomes the only truth.

When an item sells, the persistent ItemInstance/quantity actually transfers from vendor/business ownership/possession to the buyer according to transaction rules.

---

# 6. Generated Items In Trader / World Stock

Generated affixes/quality are created only when a legitimate ItemInstance is created/stocked according to its generation profile.

Valid generation moments may include:

- loot generation/spawn service creating a new item;
- crafting/manufacturing output;
- vendor restock creating/receiving new generated merchandise;
- authored world placement initialization before persistent identity is committed.

Do **not** reroll generated stats on:

- every Actor BeginPlay;
- menu open;
- trader interaction;
- pickup;
- drop;
- load/reconnect;
- UI refresh.

Once `ItemInstanceID` has generated state, that state persists.

Materials/commodities/currencies only receive generated affixes if their explicit generation profile permits it. Wood, iron, gold material, ordinary currency records, etc. do not inherit weapon affixes accidentally.

---

# 7. Restocking

Trader restock is a business/world process, not a UI reset.

Possible sources:

- business purchasing from suppliers;
- player-sold items becoming stock;
- NPC/manufacturing production;
- scheduled world shipments;
- controlled generated restock profiles for game economy needs;
- warehouse transfers.

Restock creates/transfers legitimate inventory records and can respond to economy/supply chain conditions.

Opening the Trader Widget never respawns the entire stock list.

---

# 8. Trading UI

Suggested local UI:

`W_MW_TraderCommerce`

Possible views:

- Vendor Stock
- Player Sellable Inventory
- Selected Item Details
- Quantity selector
- Quote breakdown
- Player wallet/account payment availability according to payment policy
- Vendor/business funds/availability only where the design wants that information visible
- Buy / Sell / Cancel

The UI consumes snapshots/quotes and never performs client-side inventory swaps as truth.

---

# 9. Currency Rule — No Gold Money

**Gold is never the purchase/sale currency.**

Canonical payment currencies:

- GrimKoin;
- PromoKoin where the specific vendor/transaction accepts it.

Physical Gold is a material/commodity item under `Docs/Gold_Material_Commodity_Not_Currency_Rule.md`.

A merchant may sell Gold Ore/Ingot/Dust as goods, or buy them from the player, but payment is still GrimKoin/PromoKoin.

Example:

`Player sells 1 Gold Ingot`
-> vendor quote `85 GrimKoin`
-> server transfers Gold Ingot to vendor stock
-> server transfers 85 GrimKoin to player according to payment policy.

Never:

`Player Gold Balance += 85`.

---

# 10. Vendor Funds / Business Ledger

Do not give every trader a tutorial `Gold = 1000` integer.

Payment ability can come from:

- business operating ledger;
- NPC personal wallet where the NPC is genuinely trading personally;
- configured petty-cash/cash-register balance;
- other authorized business account.

A vendor may be unable/unwilling to buy if funds, storage, law or demand rules fail.

Business revenue/expenses/taxes integrate with the canonical economy/city/business systems.

---

# 11. Authoritative Quote

Buying/selling uses the existing quote architecture.

A quote can consider:

- exact ItemInstance/quantity;
- vendor/business profile;
- condition/quality/upgrades/affixes;
- supply/demand;
- legality/stolen/evidence state;
- taxes/fees;
- vendor funds/storage;
- player/business relationship where explicitly designed;
- currency accepted;
- quote expiration.

The widget displays the quote and does not independently decide final price.

---

# 12. Atomic Buy / Sell

Purchase:

`Accept Buy Quote`
-> server revalidates quote, funds, stock, capacity, legality
-> debit player's authorized GrimKoin/PromoKoin source
-> credit business/vendor ledger
-> transfer ItemInstance/quantity
-> post taxes/fees
-> persist atomically
-> notify/refresh.

Sale:

`Accept Sell Quote`
-> server revalidates ownership/possession, vendor funds/storage, legality
-> transfer ItemInstance/quantity to vendor/business
-> debit vendor/business ledger
-> credit player authorized currency source
-> post taxes/fees
-> persist atomically
-> notify/refresh.

No partial money/item state.

---

# 13. Player Movement / Menu Input

Opening the trader interface does not pause Metaworld.

The UI may deliberately restrict local movement/look while the trade screen is active for usability, but:

- this is input/UI state, not global time stop;
- Enhanced Input/controller routing is used;
- close/back uses mapped UI action, not hardcoded `E`;
- the interaction resolver/menu layer prevents immediate close/reopen without arbitrary gameplay delays where possible;
- NPC/world events can invalidate the trade (NPC walks away, combat begins, shop closes, NPC dies, etc.).

If trade context becomes invalid, the UI closes/blocks commit safely.

---

# 14. Trader As Living NPC

A trader is still a world character.

Depending on world design they may:

- have Needs;
- go home/sleep/eat;
- work scheduled shifts;
- own or work for a business;
- be injured/killed;
- fight/flee/call security;
- build relationships/reputation;
- witness/report crime;
- be robbed;
- lose physical stock through theft/destruction;
- have replacement workers/owners through business/world systems.

Trade availability therefore depends on current NPC/business state rather than assuming the menu is permanently open.

---

# 15. Controller / Accessibility

Required:

- mouse and keyboard;
- Xbox-style controller;
- PlayStation-style controller;
- navigate player/vendor inventories;
- inspect item;
- switch buy/sell side;
- choose quantity;
- request/inspect quote;
- confirm/cancel transaction;
- close interface;
- predictable focus restore.

No essential trade action requires mouse-only drag/drop or hover.

---

# 16. Performance

- no global NPC interaction timers;
- interaction checks only for bounded current candidates;
- trader stock is persistent data/container state, not always-spawned Item Actors;
- generated stats are not rerolled at BeginPlay;
- quote calculation is request/event-driven;
- large stock UI uses scalable/virtualized lists where appropriate;
- hidden trader UI stops preview/details work;
- NPC AI fidelity follows normal significance rules outside local relevance.

---

# 17. Acceptance Tests

1. Base NPC can expose Talk/Trade through common interaction architecture.
2. Facing/LOS check does not require a permanent timer on every NPC.
3. Trader stock consists of real ItemInstances/quantities.
4. Opening trader UI does not regenerate/randomize existing stock.
5. Dropping and re-picking an item preserves generated stats.
6. Restock generates/transfers stock only through legitimate restock process.
7. Materials/Gold commodity do not accidentally receive weapon affixes.
8. Trader uses GrimKoin/PromoKoin payment, never Gold currency.
9. Gold Ingot can itself be sold as an item for GrimKoin.
10. Buy/sell transaction is atomic.
11. Vendor may reject transaction for funds/storage/legal reasons.
12. Trade closes/invalidates safely if NPC becomes unavailable.
13. Trader UI supports KBM/Xbox-style/PlayStation-style controls.
14. Player inventory/trader stock remain synchronized through authoritative deltas/events.
15. NPC death/despawn does not duplicate merchant stock or money.

## Core Rule

> A Metaworld trader is a living NPC service endpoint over real business inventory and ledgers. Stock items keep persistent identity, generated properties roll only when the item is legitimately created, and every purchase/sale moves GrimKoin/PromoKoin and ItemInstances atomically—Gold remains a physical commodity, never money.