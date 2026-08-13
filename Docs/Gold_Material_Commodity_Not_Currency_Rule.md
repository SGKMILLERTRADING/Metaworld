# Metaworld — Gold Material / Commodity — Not Currency Rule

**Status:** Canonical / Locked

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first / persistent / server-authoritative economy and item state

## Canonical Principle

Gold exists in Metaworld as a **physical material, commodity and crafting resource**. It is **not money** and is never used as the default unit for buying or selling goods/services.

> Gold can be mined, carried, stored, stolen, refined, traded and crafted. Payments are made in Metaworld's canonical currencies, not in a tutorial Gold balance.

Canonical currencies remain:

- GrimKoin;
- PromoKoin where the specific transaction permits it.

---

# 1. Gold Is an Item / Material

Gold uses the normal Item Definition / Item Instance architecture.

Possible definitions include:

- `Item.Material.Metal.Gold.Ore`
- `Item.Material.Metal.Gold.Nugget`
- `Item.Material.Metal.Gold.Ingot`
- `Item.Material.Metal.Gold.Dust`
- `Item.Material.Metal.Gold.Leaf`
- `Item.Material.Metal.Gold.Wire`
- `Item.Material.Metal.Gold.Component`

Possible stable tags:

- `Item.Category.Material`
- `Material.Metal.Gold`
- `Commodity.PreciousMetal.Gold`
- `Craft.Resource.Metal.Gold`

Gold records may carry normal persistent state such as:

- quantity;
- mass/volume;
- purity/grade;
- condition where meaningful;
- creator/refiner/provenance;
- legal owner/current possessor;
- stolen/evidence history;
- current ContainerID/world location;
- reference/appraised value;
- stack/lot identity.

There is no character variable such as `Gold = 500` representing currency.

---

# 2. Gold Can Be Used In Crafting

Recipes may consume gold where the authored design makes sense.

Examples may include:

- weapon fittings/components;
- decorative or ceremonial weapon parts;
- jewelry;
- electronics/components;
- plating/inlays;
- magical/supernatural recipes;
- high-value tools/components;
- business/manufacturing goods;
- art/collectibles.

The recipe specifies the required gold form, quantity and quality/purity rules.

Crafting consumes/reserves the actual Gold ItemInstance/stack/lot through the normal authoritative crafting transaction.

Gold is therefore a **resource input**, not a crafting currency.

---

# 3. Buying / Selling Gold

Gold itself may be bought or sold as a commodity.

Example:

`Gold Ingot ItemInstance / stack`
-> vendor quote
-> player sells ingot
-> player receives GrimKoin (or PromoKoin only where explicitly accepted)

The ingot is the good being traded; GrimKoin/PromoKoin are the payment.

Do not display:

`Gold: 250`

as the player's money balance.

Possible UI instead:

- `Gold Ingot x3`
- `Mass: 3 kg`
- `Purity: 99.5%`
- `Vendor Offer: 240 GrimKoin`

Actual price remains contextual under `Docs/Item_Valuation_Vendor_Pricing_Trade_System.md`.

---

# 4. Physical Gold Can Be Stolen / Lost / Recovered

Because gold is a physical commodity, it follows normal world-item rules.

Gold can potentially be:

- carried;
- stored in a safe/warehouse;
- transported by vehicle;
- stolen;
- seized as evidence;
- inherited;
- recovered by police;
- destroyed/lost only according to actual world/item rules;
- sold through legitimate or illicit markets depending on provenance/world law.

Banked GrimKoin is not transformed into physical gold merely because both have value.

---

# 5. Gold Coins Are Still Items Unless Explicitly Defined Otherwise

Metaworld may visually contain gold coins, medallions or minted pieces as:

- collectibles;
- commodities;
- jewelry;
- ceremonial items;
- historical artifacts;
- crafting inputs.

Their appearance does not automatically make them legal tender.

If a future world system introduces a separate physical-token payment instrument, it must be explicitly designed and must not silently replace GrimKoin/PromoKoin canon.

---

# 6. Trading UI Rule

Trader/vendor UI must never use a generic gold-coin icon to imply the transaction currency unless the icon is clearly branded as the actual GrimKoin/PromoKoin payment symbol.

Recommended display:

- `Buy: 125 GrimKoin`
- `Sell Offer: 62 GrimKoin`
- `PromoKoin Accepted: Yes/No`

Gold material inventory is shown in the normal item lists like wood, iron, leather, ammunition and other commodities.

---

# 7. Crafting / Upgrade / Service Costs

A recipe or upgrade may require:

- Gold material;
- other physical materials;
- work/time;
- tools/workstation;
- profession/skill;
- and separately a service fee in GrimKoin/PromoKoin when a business/NPC is charging for labor/service.

Example:

`Gold-inlaid Sword Upgrade`

Requires:
- 1 Gold Ingot (material)
- 2 Steel Components (material)
- Smithing skill
- Forge
- optional Blacksmith Service Fee: 80 GrimKoin

The Gold Ingot and the GrimKoin fee are different resource types with different ownership/transaction rules.

---

# 8. Persistence / Economy

Gold material persists through the same ItemInstance/container/world systems as other commodities.

Its market price may respond to:

- purity/quality;
- weight/quantity;
- local supply/demand;
- crime/stolen/evidence state;
- regional scarcity;
- vendor specialization;
- economic events;
- creator/refiner provenance where relevant.

Gold's market value does not turn it into the accounting currency.

---

# 9. Acceptance Tests

1. Character has no generic Gold money balance.
2. Vendor purchase/sale uses GrimKoin/PromoKoin, never tutorial Gold currency.
3. Gold Ore/Ingot/etc. can exist as persistent items.
4. Gold material can be used by recipes/upgrades that explicitly require it.
5. Selling a Gold Ingot transfers the ingot and credits the agreed GrimKoin/PromoKoin payment atomically.
6. Gold material contributes to carried mass/container capacity.
7. Gold can retain owner/provenance/stolen/evidence state.
8. Gold stored in a warehouse is not available to remote crafting unless the crafting-source rules permit that warehouse.
9. Gold-coin-shaped world items are not automatically legal tender.
10. UI clearly distinguishes Gold material quantity from actual currency balances.

## Core Rule

> Gold is valuable because it is a real material and commodity in the world. Metaworld does not use gold as money: goods and services are bought and sold with GrimKoin/PromoKoin, while physical gold remains an item that can be crafted, owned, transported and traded.