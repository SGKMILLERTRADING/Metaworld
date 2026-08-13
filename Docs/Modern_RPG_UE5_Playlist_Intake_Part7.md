# Metaworld — Modern RPG UE5 Playlist Intake — Part 7

**Status:** Canonical Playlist Intake Log Continuation

**Continues:** `Docs/Modern_RPG_UE5_Playlist_Intake_Part6.md`

**Playlist Engine:** Unreal Engine 5.4 tutorial series

**Metaworld Target Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first

All permanent intake rules from Part 1 remain active.

---

# Episode 46 — Random Stat Display Fix + Exact XP Threshold Level-Up Fix

**Classification:** LOCKED / BUGFIX — NO PARALLEL SYSTEM.

**Phase Ownership:** Generated Item UI + Profession/Skill Progression.

Detailed companions:

- `Docs/Generated_Item_Base_Stats_Affixes_Quality_System.md`
- `Docs/Crafting_Profession_Skill_Progression_System.md`
- `Docs/Crafting_UI_Recipe_Selection_Details_Progress_System.md`

## Approved Tutorial Intent

- crafting preview should communicate the number/range of possible random/generated stats;
- progression must trigger when XP reaches the threshold exactly, not only when it exceeds it.

## Metaworld Decision

Random-stat presentation remains driven by the canonical generated-item profile.

Do not add a separate widget `Switch on Rarity` as gameplay truth.

The UI may show examples such as:

- `Possible Affixes: 1`
- `Possible Affixes: 1–2`
- `Affix Budget: Rare Profile`

according to the resolved generation profile.

The profile may use rarity as one input, but rarity is not hardcoded everywhere as `Uncommon=1, Rare=2, Epic=3, Legendary=4` unless a particular profile explicitly chooses that rule.

### Exact Threshold Rule

Profession/skill progression evaluates threshold completion as:

`CurrentProgress >= RequiredProgress`

not only `CurrentProgress > RequiredProgress`.

Example:

`10 / 10` must cross the threshold.

Excess progress continues into the next threshold as already established.

### Episode 46 Principle

> UI reads generated-item rules from the generation profile, and progression treats reaching the requirement exactly as success.

---

# Episode 47 — Item Upgrade Tab / Eligible Item Selection / Preview

**Classification:** UPGRADE — APPROVED / NEW ITEM-UPGRADE DOMAIN.

**Phase Ownership:** Item DNA + Equipment + Stats + Crafting/Professions + Phase 67/68 UI.

Detailed companion:

`Docs/Item_Upgrade_Reinforcement_Enhancement_System.md`

## Approved Tutorial Intent

- add an Upgrade section to the player interface;
- filter inventory/equipment items to those eligible for upgrading;
- select one exact item;
- show current item stats and expected upgraded result before confirmation;
- reuse established item tooltip/stat presentation where practical.

## Metaworld Upgrades

- interface shell can register stable `UI.Tab.Upgrade` rather than relying on a magic widget index;
- selected target is exact `ItemInstanceID`, not ItemDefinition alone or inventory index;
- upgrade eligibility is resolved from Item Definition + exact ItemInstance state + UpgradeProfile;
- weapons/armor are common upgrade candidates but not the only possible families forever;
- preview uses current effective stats + proposed UpgradeProfile result;
- preview is presentation only; server recalculates on request;
- item moving/dropping/equipping while selected invalidates or refreshes selection safely;
- controller/keyboard users receive the same selection and stat comparison as mouse users.

### Episode 47 Principle

> Upgrade UI selects an exact persistent item and previews an allowed modification; it does not define the upgrade or own the item.

---

# Episode 48 — Upgrade Stat Calculation / +1 Presentation

**Classification:** UPGRADE — APPROVED WITH DATA-DRIVEN STAT CORRECTION.

**Phase Ownership:** Item Upgrade + Stats/Modifiers + UI.

Detailed companion:

`Docs/Item_Upgrade_Reinforcement_Enhancement_System.md`

## Approved Tutorial Intent

- upgrading can change relevant item stats;
- UI should preview the upgraded result;
- upgrade level/tier should be visible to the player;
- logic should be centralized rather than scattered through individual widgets.

## Metaworld Upgrades

- reject one universal `Stat × 1.1` / 10% rule for all items;
- `UpgradeProfileID` defines per-level/per-family stat operations, caps and curves;
- operations may be Add, Multiply, authored Curve/Table or specific capability changes;
- `+1`, `+2`, etc. are presentation derived from persistent UpgradeLevel, not permanently appended to the base localized DisplayName;
- upgrade state is an ItemInstance layer separate from mandatory base stats, generated affixes and condition;
- preview must not double-count base/generated/upgrade modifiers.

### Episode 48 Principle

> Upgrade strength is authored by the item's UpgradeProfile; `+1` describes the item's persistent upgrade state rather than becoming a new item name or universal 10% formula.

---

# Episode 49 — Upgrade Costs, Materials & Commit

**Classification:** UPGRADE — APPROVED WITH CURRENCY / IDENTITY CORRECTIONS.

**Phase Ownership:** Item Upgrade + Inventory + Economy + Profession/Skill.

Detailed companions:

- `Docs/Item_Upgrade_Reinforcement_Enhancement_System.md`
- `Docs/Banking_Currency_Custody_Future_Cashout.md`
- `Docs/Item_Valuation_Vendor_Pricing_Trade_System.md`

## Approved Tutorial Intent

- upgrades can require materials/resources;
- upgrade requirements can scale with level/tier;
- a rare catalyst such as Diamond Dust can be used;
- profession/skill requirements can gate advanced upgrades;
- UI displays costs before confirmation;
- successful upgrade consumes required resources.

## Critical Metaworld Identity Rule

Normal upgrade does **not** remove the original item and create an unrelated replacement.

`ItemInstanceID #84721 +2`
-> successful upgrade
-> `ItemInstanceID #84721 +3`

The same item's owner, provenance, history, generated affixes and evidence/legal state remain attached.

A genuinely transformative recipe may explicitly consume the old item and create a new definition/instance, but that is a separate transformation policy with provenance linkage.

## Currency / Material Correction

- no tutorial Gold balance is introduced;
- upgrade service costs use GrimKoin/PromoKoin only where that service/process actually charges currency;
- player-owned workstation upgrades may require only materials/work depending on design;
- Diamond Dust or similar catalyst is an ordinary persistent material ItemInstance/stack, not a hidden upgrade currency;
- material/currency inputs are reserved/consumed atomically with the upgrade transaction.

### Episode 49 Principle

> Reinforcement modifies the exact item the player owns. Costs are real materials/services/currencies, and the transaction must either commit correctly or leave the item/resources unchanged.

---

# Episode 50 — Upgrade Caps, Stacking & Profession Reward

**Classification:** UPGRADE — APPROVED WITH PERSISTENCE CORRECTIONS.

**Phase Ownership:** Item Upgrade + Inventory Stacking + Profession Progression + UI.

Detailed companions:

- `Docs/Item_Upgrade_Reinforcement_Enhancement_System.md`
- `Docs/Crafting_Profession_Skill_Progression_System.md`

## Approved Tutorial Intent

- show current upgrade level in UI;
- stop/hide upgrade controls at maximum level;
- stack compatibility must account for upgrade state;
- successful upgrades may award relevant crafting/profession experience;
- refresh UI when upgrade state/progression changes.

## Metaworld Upgrades

- maximum UpgradeLevel is data-driven by UpgradeProfile/item path and enforced by server as well as UI;
- when maxed, UI shows Max/Completed state and removes unavailable action/cost presentation;
- ordinary unique equipment generally remains separate ItemInstances;
- where a stackable item can be upgraded, stack compatibility includes UpgradeLevel/path plus every other meaningful instance/lot property;
- items with different upgrade state never merge if that would erase information;
- successful upgrade may award the relevant profession/skill only after authoritative commit;
- no generic Crafting Level owns all upgrades;
- cost scaling comes from UpgradeProfile/service/economy data rather than a hardcoded Gold formula.

### Episode 50 Principle

> Upgrade caps and stacking are properties of persistent item state, while progression rewards the actual profession responsible for the work.

---

# Episode 51 — Upgrade Tooltip / Selection / Progression Synchronization Fixes

**Classification:** LOCKED + UPGRADE MAINTENANCE.

**Phase Ownership:** Item Upgrade UI + Interface Data Contracts + Progression UI.

Detailed companions:

- `Docs/Item_Upgrade_Reinforcement_Enhancement_System.md`
- `Docs/RPG_Interface_Shell_Widget_Data_Contracts_Navigation_System.md`

## Approved Tutorial Intent

- tooltip must show current upgrade level;
- dropping/destroying/moving a selected upgrade item must clear stale UI;
- switching away/back should rebuild current state;
- progression UI should display the latest XP after an upgrade reward.

## Metaworld Upgrades

- all UI derives UpgradeLevel from the same ItemInstance presentation snapshot;
- no separate tooltip binding owns a second upgrade value;
- if selected ItemInstance disappears/moves/becomes ineligible, `SelectedItemInstanceID` is re-resolved then refreshed/cleared safely;
- leaving/re-entering Upgrade tab rebuilds or refreshes from current ItemInstance truth;
- event ordering is explicit: committed upgrade/progression -> state-change events -> presentation refresh;
- event-driven UI replaces raw per-frame property bindings;
- inventory/equipment/upgrade/tooltip/preview remain synchronized from stable IDs/revisions.

### Episode 51 Principle

> Fix stale upgrade UI by re-resolving the exact ItemInstance and reacting to committed state events, not by maintaining duplicate widget copies of upgrade data.

---

# Episode 52 — Player HUD: Health, Mana & Stamina

**Classification:** UPGRADE — APPROVED / NEW HUD VITALS DOMAIN.

**Phase Ownership:** Core Player Resources + Phase 67 UI + Phase 68 Accessibility + Performance.

Detailed companion:

`Docs/Player_HUD_Vitals_Resources_System.md`

## Approved Tutorial Intent

- always-available/contextual HUD can display Health, Mana and Stamina;
- Current/Max resources map naturally to progress bars;
- custom Fill/Background images, padding and borders can improve readability/polish;
- HUD initializes for the local player and reflects resource changes.

## Metaworld Upgrades

- `W_MW_PlayerHUD` is local presentation; Stats/Vitals own authoritative Current/Max values;
- percentage calculation safely handles Max <= 0 and clamps only visual percent;
- event-driven `OnResourceChanged` style updates replace per-frame Player Blueprint bindings;
- Health/Stamina/Mana modules can have data-driven visibility rules;
- Stamina may be contextual (sprinting/exertion/below full) with accessibility option to keep visible;
- Mana may hide for characters who do not have/use Mana, allowing future lineage/resource modules without meaningless empty bars;
- resource meaning is not conveyed by color alone;
- custom textures/materials/styles are approved but remain reusable and performance-budgeted;
- visual smoothing/damage-trail animation is presentation only;
- HUD binds/unbinds cleanly on possession/new character/reconnect and never duplicates;
- no HUD logic changes permanent-death or resource authority.

### Episode 52 Principle

> The HUD is a responsive instrument panel for authoritative character resources; it shows Health, Stamina and Mana clearly without becoming the system that owns them.

---

# Current Modern RPG Additions From Episodes 46–52

`Generated Item Profile`
-> `Possible Affix Count/Range Presentation`

`Profession Progress`
-> threshold test `>=`
-> safe carry-over

`Exact ItemInstanceID`
-> `UpgradeProfileID`
-> `Upgrade Preview`
-> `Material / Service / Profession Requirements`
-> `Authoritative Upgrade Transaction`
-> `Same ItemInstanceID, higher UpgradeLevel`
-> `Persistent Upgrade History`
-> `Equipment / Tooltip / Economy / Profession Progress`

`Authoritative Health / Stamina / Mana`
-> `Resource Change Events`
-> `W_MW_PlayerHUD`
-> `Accessible / performant resource bars`

---

# Playlist Continuation Rule

Future episodes continue in Part 7 until another safe continuation is needed. Parts 1–7 remain the canonical intake/audit trail for this Modern RPG playlist; detailed companion documents remain implementation authority for established domains.