# Metaworld — Modern RPG UE5 Playlist Intake — Part 10

**Status:** Canonical Playlist Intake Log Continuation

**Continues:** `Docs/Modern_RPG_UE5_Playlist_Intake_Part9.md`

**Playlist Engine:** Unreal Engine 5.4 tutorial series

**Metaworld Target Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first

All permanent intake rules from Part 1 remain active.

**Counting Note:** The first Trading Widget tutorial supplied in this batch is the same scope already recorded as Episode 71 and is treated as a duplicate/repeat. It does not receive a second episode number. This Part contains 14 new episodes, Episodes 72–85.

---

# Episode 72 — Buy From Trader / Sell To Trader Logic

**Classification:** UPGRADE — APPROVED WITH ATOMIC COMMERCE CORRECTION.

**Phase Ownership:** Economy/Trade + NPC Services + Inventory/Containers + UI.

Detailed companion:

`Docs/Commerce_Buy_Sell_Quantity_Quote_UI_System.md`

## Approved Intent

- reusable trade inventory entries for player/vendor sides;
- explicit Buy and Sell actions;
- refresh both sides after committed trade;
- weight/capacity matter;
- merchant stock limits matter.

## Metaworld Upgrades

- no copied Player/Trader inventory functions become separate authorities;
- stock/player sides reference real ContainerIDs and ItemInstances;
- Buy/Sell use authoritative quote + one atomic transaction;
- no tutorial Gold currency; GrimKoin/PromoKoin only;
- vendor capacity is data/business-storage driven, not universal 36 slots;
- carried load/capacity is revalidated by server;
- UI refreshes from committed deltas/events.

### Principle

> Buy/Sell UI selects a direction; the server moves real item and currency state atomically.

---

# Episode 73 — Trade Failure Notifications / Trader Tooltips / Price Labels

**Classification:** LOCKED + UPGRADE UI/FEEDBACK MAINTENANCE.

Detailed companions:

- `Docs/Commerce_Buy_Sell_Quantity_Quote_UI_System.md`
- `Docs/HUD_Notification_Feedback_System.md`

## Metaworld Upgrades

- failure reasons become generic commerce result codes such as PlayerInsufficientFunds, VendorInsufficientFunds, VendorStorageFull, QuoteExpired, ItemUnavailable;
- localized messages say `Not enough GrimKoin` / appropriate PromoKoin context, never tutorial `Not enough Gold`;
- trader tooltip uses stable ItemInstance + commerce context rather than another fragile source enum/reference copy;
- entry price label is approved but displays the actual quote currency and is invalidated/refreshed when quote changes;
- right-click being disabled temporarily is not a final input architecture—context actions/modal quantity support return through the common UI system.

### Principle

> Commerce feedback explains authoritative failure/results, and visible prices are current quotes—not static Gold labels.

---

# Episode 74 — Multi-Quantity Buy / Sell Slider

**Classification:** UPGRADE — APPROVED WITH QUANTITY-TRANSACTION REUSE.

Detailed companions:

- `Docs/Commerce_Buy_Sell_Quantity_Quote_UI_System.md`
- `Docs/Inventory_Stack_Quantity_Selection_Drop_Transfer_UI_System.md`

## Metaworld Upgrades

- reuse `W_MW_QuantitySelector` for Buy/Sell rather than a trade-specific slider authority;
- quantity selector receives exact ItemInstance/stack ID + ContainerID + commerce context;
- integer quantity only for discrete items;
- quote recalculates/refreshes for selected quantity;
- confirm sends one authoritative quantity transaction, not N one-item trades;
- mouse/right-click is optional shortcut; controller/keyboard access is mandatory;
- modal blocks click-through/background activation.

### Principle

> Multi-buy/sell is one quoted quantity transaction against exact current stock, not a loop of client-side trades.

---

# Episode 75 — Inventory Input / Trader Close / Quantity Total Improvements

**Classification:** LOCKED + UPGRADE INPUT/UI MAINTENANCE.

Detailed companions:

- `Docs/Commerce_Buy_Sell_Quantity_Quote_UI_System.md`
- `Docs/Interaction_Hold_Progress_Modal_Input_State_System.md`

## Metaworld Upgrades

- modal/interface layer prevents background item/game actions while commerce/inventory is active;
- remove arbitrary close delays; explicit menu/input state prevents immediate reopen;
- quantity UI may preview total quote and transferred mass;
- server revalidates final quote, quantity, funds, capacity and carried load;
- input mode changes are centralized by interface layer rather than scattered child-widget casts.

### Principle

> Correct modal state replaces delay hacks; live totals help the player but never authorize the transaction.

---

# Episode 76 — MetaHuman NPC Performance Optimization

**Classification:** UPGRADE — APPROVED WITH PROFILE-BASED FIDELITY CORRECTION.

Detailed companion:

`Docs/NPC_MetaHuman_Fidelity_Customization_Hair_Performance_System.md`

## Approved Intent

- reduce NPC texture/hair/simulation cost;
- hair is a major performance budget;
- MetaHuman modular assembly needs deliberate setup;
- background NPCs should cost less than hero/player characters.

## Metaworld Upgrades

- reject universal `MaxTextureSize=256` and `MinLOD=4` for every NPC;
- use NPCFidelityProfileID, LODSync, platform/significance/device-profile policy;
- strands/cards/mesh hair selected by quality/performance need;
- hair physics/interpolation can be disabled/reduced by profile;
- full-fidelity MetaHumans are not kept active for irrelevant/unloaded NPCs;
- tutorial FPS/quality claims must be measured in Metaworld.

### Principle

> NPC fidelity scales with significance; no background crowd member receives unlimited MetaHuman rendering cost.

---

# Episode 77 — NPC Appearance Variables / Leather Armor / Helmet

**Classification:** UPGRADE — APPROVED CONTENT/AVATAR PRESENTATION.

Detailed companions:

- `Docs/NPC_MetaHuman_Fidelity_Customization_Hair_Performance_System.md`
- `Docs/Equipment_Armor_Weapon_Attachment_Avatar_Fitting_Architecture.md`

## Metaworld Upgrades

- NPC appearance comes from structured appearance/equipment data rather than many unrelated authoritative mesh variables;
- Construction Script is useful for editor preview but runtime appearance rebuilds only on initialization/state change;
- fixed rigged armor pipeline remains approved where appropriate;
- one-piece armor is allowed as presentation/performance optimization but cannot erase separate underlying equipment ItemInstances if gameplay needs them;
- helmet/headwear uses attachment and hair/body coverage profiles;
- same fitting/QA principles as player armor.

### Principle

> NPC visual configuration is data-driven presentation over identity/equipment state, not a manually wired mesh collection that becomes gameplay truth.

---

# Episode 78 — MetaHuman Groom Hair / Static Mesh Hair

**Classification:** UPGRADE — APPROVED MULTI-FIDELITY HAIR SYSTEM.

Detailed companion:

`Docs/NPC_MetaHuman_Fidelity_Customization_Hair_Performance_System.md`

## Metaworld Upgrades

- stable HairStyleID can reference groom + binding + card/mesh fallback + color/material profile;
- Data Table/Data Asset authoring is approved;
- material instances handle hair-color variations without duplicated materials;
- apply material/appearance changes on state change, not Tick;
- groom strands reserved for contexts that justify their cost;
- cards/static/skeletal mesh hair approved for lower-cost profiles;
- Two-Sided is used only when asset geometry/material actually requires visible backfaces, not as universal transparency fix.

### Principle

> One NPC identity can have multiple hair representations across fidelity levels while keeping the same hairstyle/color intent.

---

# Episode 79 — Reusable Loot Generation Component / Weighted Loot Tables

**Classification:** UPGRADE — APPROVED / NEW LOOT-GENERATION DOMAIN.

Detailed companion:

`Docs/Loot_Generation_Tables_Drops_Provenance_System.md`

## Metaworld Upgrades

- reusable `BPC_MW_LootSource`/service is approved;
- stable LootProfileID owns contextual tables rather than one DropChance on every ItemDefinition;
- supports weighted choice, guaranteed/optional groups, independent rolls and no-loot outcome;
- authoritative generation rolls once and creates legitimate ItemInstances/stack lots;
- generated affixes use existing generation profiles and persist;
- Gold-as-money generation rejected; physical Gold commodity or legitimate carried GrimKoin/PromoKoin only under their own rules.

### Principle

> Loot tables author what a source may create; the result becomes normal persistent world property exactly once.

---

# Episode 80 — Enemy Death Loot Bag / Generated Drops

**Classification:** UPGRADE — APPROVED WITH CORPSE/IDENTITY CORRECTION.

Detailed companions:

- `Docs/Loot_Generation_Tables_Drops_Provenance_System.md`
- `Docs/Loot_Containers_Bags_Corpses_Chests_Transfer_System.md`

## Metaworld Upgrades

- loot bag may compactly present multiple physical drops through one ContainerID;
- actual carried/equipped NPC items move into death/corpse state rather than being duplicated by a loot table;
- additional authored drops may be generated only where explicit profile says so;
- enemy `Gold` money roll rejected;
- physical Gold commodity may be loot, or legitimate carried GrimKoin/PromoKoin may be reachable under currency/death rules;
- banked currency never drops;
- temporary bag despawns only after authoritative contents are empty/safely cleaned.

### Principle

> Death moves real possessions and may create explicit bonus loot, but it never duplicates equipment or turns bank balances into a magic bag of Gold money.

---

# Episode 81 — Loot Container UI

**Classification:** UPGRADE — APPROVED CONTAINER UI.

Detailed companion:

`Docs/Loot_Containers_Bags_Corpses_Chests_Transfer_System.md`

## Metaworld Upgrades

- `W_MW_LootContainer` receives source ContainerID and item presentation snapshots;
- source list is not a copied authoritative array;
- item entry shows icon/name/type/rarity/quantity according to common presentation system;
- Take, Take All and Close become device-independent UI actions;
- opening loot does not globally pause the world;
- scalable list/scroll presentation is approved.

### Principle

> The loot window is a view of a real source container, not the place where dropped items actually live.

---

# Episode 82 — Take / Take All Functional Loot Transfers

**Classification:** UPGRADE — APPROVED WITH TRANSACTION/CONCURRENCY CORRECTION.

Detailed companion:

`Docs/Loot_Containers_Bags_Corpses_Chests_Transfer_System.md`

## Metaworld Upgrades

- Take transfers exact ItemInstance/quantity server-authoritatively;
- Take All is a server-evaluated batch/multi-item result, not blind UI child removal;
- capacity/legal/access rules may yield partial results;
- two players cannot both loot the same final item;
- temporary empty bag may despawn after authoritative empty state;
- persistent chest does not disappear when empty;
- hardcoded E/R/F shortcuts become mapped input actions/controller navigation;
- notification occurs only after successful transfer.

### Principle

> Looting is container-to-container transfer under concurrency; clearing a widget never means the items were taken.

---

# Episode 83 — Loot Niagara Highlight / Tooltip Cleanup / No Time Dilation / Camera Collision

**Classification:** LOCKED + UPGRADE PRESENTATION/PERFORMANCE MAINTENANCE.

Detailed companions:

- `Docs/Loot_Containers_Bags_Corpses_Chests_Transfer_System.md`
- `Docs/Avatar_Preview_Lifecycle_Performance_System.md`

## Metaworld Upgrades

- Niagara highlight is approved for significant loot but must use Effect Type/scalability/culling/performance budget;
- orange glow does not equal universal rarity meaning;
- tooltip remains common ItemInstance presentation, with event-driven initialization/update;
- global inventory time dilation remains rejected;
- world physics continues while menus are open;
- camera can ignore NPC mesh/accessory collision through correct collision channels while gameplay collision remains intact.

### Principle

> Loot presentation can be visible and polished without turning every drop into a permanent particle cost or pausing the living world.

---

# Episode 84 — Persistent Chest / Hold-to-Interact Radial Progress

**Classification:** UPGRADE — APPROVED CHEST + HOLD-INTERACTION FOUNDATION.

Detailed companions:

- `Docs/Loot_Containers_Bags_Corpses_Chests_Transfer_System.md`
- `Docs/Interaction_Hold_Progress_Modal_Input_State_System.md`

## Metaworld Upgrades

- chest is a persistent world object + ContainerID with lock/owner/access/generation state;
- chest persists when empty unless its own object policy says otherwise;
- hold interaction uses IA_MW_Interact state + InteractionInstanceID/timestamp rather than a local timer alone;
- radial progress is presentation; server revalidates before opening/loot access;
- releasing input, moving away, losing LOS/permission or target invalidation cancels correctly;
- small/medium chest meshes are presentation variants/profile data;
- seeded chest contents do not reroll on reopen.

### Principle

> A chest is persistent storage with a validated interaction; the radial meter shows progress but cannot grant loot by itself.

---

# Episode 85 — Widget Held-Input Fix / Enhanced Input Migration / Crafting & Data Cleanup

**Classification:** LOCKED + UPGRADE MAINTENANCE.

Detailed companion:

`Docs/Interaction_Hold_Progress_Modal_Input_State_System.md`

## Approved Intent

- prevent held interaction input from leaking into newly opened widgets;
- migrate old raw keys to Enhanced Input;
- distinguish press/release behavior;
- improve crafting-progress cleanup and Empty-state UI;
- organize project data/assets cleanly.

## Metaworld Upgrades

- use Enhanced Input Started/Completed/Canceled/hold trigger semantics and explicit modal interaction state;
- opening a modal consumes/ends originating world interaction so the same held input cannot immediately loot/activate again;
- no arbitrary close delays;
- **manual/forced garbage collection on ordinary widget close is rejected**—release references/timers/captures and let Unreal manage GC; forced GC only for controlled profiled cases;
- `Format Gold as currency` is rejected for physical Gold; currency formatting applies to GrimKoin/PromoKoin;
- stat/progression display rounding is presentation metadata and never changes authoritative values;
- negative stat formatting should avoid duplicate minus signs through centralized formatting;
- organize Structs/Data Tables/Components/Enums by clear project folders/naming standards; stable IDs prevent folder moves from changing gameplay identity.

### Principle

> Explicit Enhanced Input/modal state solves held-input bugs; cleanup releases ownership correctly instead of forcing garbage collection, and UI formatting never changes Metaworld's Gold/currency canon.

---

# Current Modern RPG Additions From Episodes 72–85

`Living Trader / Business`
-> `Persistent Stock Container`
-> `Buy/Sell Direction`
-> `Quantity Selector`
-> `Authoritative Quote`
-> `GrimKoin/PromoKoin Atomic Transaction`

`NPC CharacterID`
-> `Appearance Record`
-> `NPC Fidelity Profile`
-> `LODSync / Texture / Hair Technology`
-> `Significance-Scaled Presentation`

`LootProfileID`
-> `Authoritative Roll Once`
-> `Persistent ItemInstances`
-> `Corpse / LootBag / Chest ContainerID`
-> `Take / Take All Transactions`
-> `Optional Niagara Highlight`

`IA_MW_Interact`
-> `Started / Hold / Completed / Canceled`
-> `Authoritative Interaction State`
-> `Radial Progress Presentation`
-> `Modal Input Layer`

`Gold`
-> `Physical Commodity / Craft Material`
-> **NOT MONEY**

---

# Playlist Continuation Rule

Future episodes continue in Part 10 until another safe continuation is needed. Parts 1–10 remain the canonical intake/audit trail for this Modern RPG playlist; detailed companion documents remain implementation authority for established domains.