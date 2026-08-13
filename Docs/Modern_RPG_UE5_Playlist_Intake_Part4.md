# Metaworld — Modern RPG UE5 Playlist Intake — Part 4

**Status:** Canonical Playlist Intake Log Continuation

**Continues:** `Docs/Modern_RPG_UE5_Playlist_Intake_Part3.md`

**Playlist Engine:** Unreal Engine 5.4 tutorial series

**Metaworld Target Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first

All permanent intake rules from Part 1 remain active.

---

# Episode 19 — Notify Widget / Pickup & Inventory Feedback

**Classification:** UPGRADE — APPROVED.

**Phase Ownership:** Phase 67 UI + Inventory/Equipment/Interaction feedback.

Detailed companion:

`Docs/HUD_Notification_Feedback_System.md`

## Approved Tutorial Intent

- short-lived HUD notifications can replace Print String feedback;
- notification entries can contain icon/text/category information;
- slide/fade animation is useful presentation;
- entries should remove themselves cleanly after display;
- pickup/inventory-full results should give clear player feedback.

## Metaworld Upgrades

- use one reusable local notification feed/manager rather than creating notification logic directly in Player Blueprint for every system;
- stable Category Tags/data replace a permanently closed `NotifyType` enum as the system grows;
- notification payload can include category, priority, text, icon, amount/quantity, merge key and accessibility text;
- success notifications fire only after the responsible authoritative gameplay transaction succeeds;
- inventory-full/blocked messages use the actual failure reason;
- queue/merge/cooldown rules prevent notification spam;
- animation/lifetime cleanup is UI-owned and does not rely on world time-dilation tricks;
- notifications are local presentation and never become gameplay authority.

### Episode 19 Principle

> Gameplay decides what happened; the notification feed reports the result clearly and once.

---

# Episode 20 — Notification / Rarity / Pivot Maintenance Fixes

**Classification:** LOCKED + UPGRADE MAINTENANCE.

**Phase Ownership:** UI feedback + Item asset/content QA.

Detailed companions:

- `Docs/HUD_Notification_Feedback_System.md`
- `Docs/Inventory_Equipment_UI_Preview_Tooltip_Rarity_Interaction_Prompt_Architecture.md`
- `Docs/Persistent_Item_Interaction_Inventory_Architecture.md`

## Approved Lessons

- central rarity presentation data must be correct and consistently consumed by all widgets;
- notification layer/Z-order must be intentional;
- animation-finished cleanup is preferable to fragile delay/time-dilation dependencies;
- pickup success notification should not trigger during unrelated equip/unequip flows;
- world-item pivots/origins matter for stable floor placement, icon capture and interaction presentation;
- DCC correction of bad mesh origins/spacing is valid content maintenance.

## Metaworld Upgrades

- the earlier canonical rarity profile remains authority; one wrong color is a data/QA error rather than a reason for duplicate widget switches;
- normal Metaworld menus do not globally pause/time-dilate the world, but notification cleanup remains independent of any local menu timing;
- only committed transactions emit success notifications;
- Python/Editor asset audits may later flag abnormal pivots/bounds/collision and item-preview framing issues.

### Episode 20 Principle

> Fix the source data/state and central presentation contract; do not patch the same mistake independently in every widget.

---

# Episode 21 — Drop Item & Inventory Options Menu

**Classification:** UPGRADE — APPROVED.

**Phase Ownership:** Phase 9 Item DNA + Phase 11 Inventory + Phase 67 UI.

Detailed companion:

`Docs/Item_Drop_Disposal_Physical_Currency_Transaction_System.md`

## Approved Tutorial Intent

- inventory items need contextual actions such as Drop/Destroy;
- dropping creates a world representation near the character;
- the dropped object should retain the selected item's data;
- a contextual options menu is useful inventory UX.

## Metaworld Upgrades

- `RequestDropItem(ItemInstanceID, Quantity, Context)` is a server-authoritative move from container/equipment state to world state;
- dropping preserves the same ItemInstanceID except legitimate stack splitting;
- server chooses/validates a safe world placement using support/obstruction/item bounds rather than blindly spawning at one forward-vector offset;
- world actor presentation resolves from stable ItemInstance data;
- right-click is only one UI path; controller/keyboard can open the same actions menu;
- actions are generated from current valid ItemInstance capabilities/state;
- `Destroy` is not universal permanent deletion and follows discard/destruction/salvage/protection rules.

### Episode 21 Principle

> Drop moves the persistent item from a container into the world; the context menu only requests that transaction.

---

# Episode 22 — Dropped Item Info Bug Fix

**Classification:** LOCKED / DUPLICATE BUG LESSON — NO NEW PARALLEL STATE.

**Phase Ownership:** Persistent Item architecture.

Detailed companion:

`Docs/Item_Drop_Disposal_Physical_Currency_Transaction_System.md`

## Tutorial Lesson

The tutorial fixes an overwrite bug by adding a separate `Dropped Item Info` variable.

## Metaworld Decision

Metaworld does not maintain two mutable authoritative copies of Item Info.

Canonical flow:

`World Actor`
-> `ItemInstanceID`
-> authoritative Item Definition + Instance record
-> correct world mesh/material/variant/condition

A local cached presentation snapshot may exist for rendering, but identity/state remains one persistent source of truth.

### Episode 22 Principle

> Fix stale/overwritten item presentation through stable ItemInstance identity, not duplicate mutable item-info variables.

---

# Episode 23 — Gold Currency Pickup & HUD Balance

**Classification:** PARTIAL REJECT + UPGRADE — APPROVED PATTERN, REJECT NEW GOLD CURRENCY.

**Phase Ownership:** Currency/Banking + Item/Interaction + UI Notification.

Detailed companions:

- `Docs/Item_Drop_Disposal_Physical_Currency_Transaction_System.md`
- `Docs/Banking_Currency_Custody_Future_Cashout.md`
- `Docs/HUD_Notification_Feedback_System.md`

## Rejected Tutorial Direction

- no third canonical `Gold` currency;
- no Player Blueprint `Gold` integer as currency truth;
- no client-side direct addition to a wallet balance;
- no rerolling random currency amount on every interaction;
- no per-frame UI binding as the currency ledger.

## Approved Metaworld Upgrade

Canonical currencies remain:

- GrimKoin;
- PromoKoin.

A physical currency bag/stack/pickup may represent one of those currencies.

Authoritative flow:

`Physical currency source`
-> server validates source/reach/loot rights
-> reads stored CurrencyType + Amount
-> reserves/consumes source
-> credits carried wallet through authoritative ledger
-> commits atomically
-> removes world representation
-> notification displays exact amount
-> wallet UI refreshes from state change.

Random loot amount is rolled by the authoritative loot/reward system once and stored on the world record.

Physical pickups credit carried currency, not banked GrimKoin, unless a separate banking transaction occurs.

### Episode 23 Principle

> Keep the pickup-feedback pattern, not the tutorial currency. Metaworld money remains GrimKoin/PromoKoin under the authoritative ledger.

---

# Episode 24 — Reusable Stat Component / Current & Max Values

**Classification:** UPGRADE — APPROVED.

**Phase Ownership:** Core Player Resources + Combat + Item/Equipment modifiers.

Detailed companion:

`Docs/Stats_Attributes_Item_Modifiers_Encumbrance_System.md`

## Approved Tutorial Intent

- shared numeric stat math belongs in a reusable Actor Component where appropriate;
- Current/Max semantics and clamping should be centralized;
- get/set/modify operations should be reusable across suitable Actors;
- decreasing Max should resolve invalid Current values.

## Metaworld Upgrades

- stable Stat IDs/Gameplay Tags/data replace a permanently closed enum as the catalog grows;
- stat record separates Base, Current, Max/Derived and Modifier sources rather than one mutable final value;
- increasing Max does not automatically heal/refill Current unless explicitly defined;
- reusable math does not collapse Hunger, professions, reputation, public rank, currency, item condition and other dedicated systems into one generic map;
- gameplay-relevant stat state is server-authoritative;
- event-driven recalculation replaces per-stat Tick.

### Episode 24 Principle

> Reuse stat mathematics, but keep each Metaworld system responsible for the meaning of its own state.

---

# Episode 25 — Item Stats / Equipment Modifiers / Tooltip Rows

**Classification:** UPGRADE — APPROVED.

**Phase Ownership:** Item DNA + Equipment + Combat + UI.

Detailed companion:

`Docs/Stats_Attributes_Item_Modifiers_Encumbrance_System.md`

## Approved Tutorial Intent

- items can carry numeric gameplay properties/modifiers;
- tooltips can dynamically list relevant non-zero stats;
- equipment comparisons should communicate how an item affects character/combat values.

## Metaworld Upgrades

- Item Definition supplies base modifier/stat templates while ItemInstance condition/quality/upgrades/provenance/magic may alter effective values;
- Rarity does not automatically set Damage/Armor/etc.; rarity remains separate presentation metadata;
- modifier records retain SourceID/ItemInstanceID so effects can be removed cleanly on unequip;
- equipment never permanently bakes bonuses into Base character stats;
- unloaded inventory items remain data records and do not each need a live StatsComponent;
- tooltip rows resolve authorized effective stats from ItemDefinition + ItemInstance state.

### Episode 25 Principle

> Item stats describe what the persistent item contributes; equipping applies traceable modifiers instead of rewriting the character's base values.

---

# Episode 26 — Rich Text Positive / Negative Stat Styling

**Classification:** UPGRADE — APPROVED PRESENTATION.

**Phase Ownership:** Phase 67 UI + Phase 68 Accessibility.

Detailed companion:

`Docs/Stats_Attributes_Item_Modifiers_Encumbrance_System.md`

## Approved Tutorial Intent

- stat changes/comparisons should be visually distinguishable;
- Rich Text is an acceptable presentation tool;
- `+` / `-` formatting is useful where semantically correct.

## Metaworld Upgrades

- green/red is a secondary cue, not the only meaning channel;
- include signs/arrows/icons/text so color-vision differences do not remove information;
- Stat Definition metadata decides whether higher or lower is beneficial—negative numeric change is not automatically bad (lower weight can be good);
- formatting updates when selection/stat values change rather than constructing Rich Text every frame;
- Current-vs-Max resources and item comparison deltas use explicit presentation models.

### Episode 26 Principle

> Present stat differences accessibly and according to what the stat actually means, not simply `positive number = green`.

---

# Episode 27 — Inventory Weight, Carry Capacity & Encumbrance

**Classification:** UPGRADE — APPROVED WITH MAJOR CORRECTION.

**Phase Ownership:** Inventory/Containers + Core Attributes + Movement/Needs/Combat.

Detailed companion:

`Docs/Stats_Attributes_Item_Modifiers_Encumbrance_System.md`

## Approved Tutorial Intent

- item definitions need weight/mass data;
- carried load must be compared against character capacity;
- UI should show load/capacity;
- excessive carried load should create gameplay consequences.

## Critical Metaworld Correction

**Equipping an item does not remove its mass from the character's carried load.**

A 12 kg chest plate remains 12 kg while worn.

Metaworld separates:

- Container Capacity — what fits inside a container;
- Character Carried Load — inventory + equipped gear + carried objects/containers;
- Carry Capacity — supported physical load threshold;
- Encumbrance — gameplay effects of load relative to capacity.

## Additional Upgrades

- do not use one universal `over limit -> halve Max Walk Speed` rule;
- use data-driven encumbrance thresholds/curves and effects;
- potential penalties include speed, acceleration, sprinting, stamina, jump/climb, swimming, dodge/recovery and carry animations;
- extreme loads may require dropping items, using carts/vehicles, dragging/team lifting, etc.;
- carried mass recalculates on pickup/drop/transfer/equip/unequip/stack/capacity changes rather than Tick;
- UI shows load/capacity and encumbrance state from authoritative cached totals.

### Episode 27 Principle

> Weight follows the physical item wherever the character carries it. Equipment can move between slots and containers, but it never becomes weightless because it is worn.

---

# Current Modern RPG Systems Added By Episodes 19–27

`Authoritative gameplay event`
-> `HUD Notification Feed`

`ItemInstanceID`
-> `Drop / Split / Discard transaction`
-> `World Item representation`

`Physical GrimKoin/PromoKoin pickup`
-> `Authoritative Wallet Ledger`
-> `Notification / Balance UI`

`Base Attribute`
+ `Traceable Modifier Sources`
-> `Derived Stat`
-> `Item/Equipment Tooltip Comparison`

`Inventory + Equipped + Carried Item Mass`
-> `Carried Load`
-> `Carry Capacity`
-> `Encumbrance Profile`
-> `Movement/Stamina/etc. consequences`

---

# Playlist Continuation Rule

Future episodes continue in Part 4 until another safe continuation is needed. Parts 1–4 remain the canonical intake/audit trail for this Modern RPG playlist; detailed companion documents remain the implementation authority for established domains.