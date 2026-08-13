# Metaworld — Item Upgrade, Reinforcement & Enhancement System

**Status:** Canonical / Approved Modern RPG Playlist Upgrade

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first / server-authoritative / persistent / transaction-driven

## Canonical Principle

Upgrading changes the state/capabilities of an exact persistent item through an authoritative transformation process. Ordinary reinforcement does not destroy the old item and create a fake replacement copy.

> If a sword is reinforced from +2 to +3, it is still the same sword, with the same ItemInstanceID, ownership, provenance and history.

Related canon:

- `Docs/Persistent_Item_Interaction_Inventory_Architecture.md`
- `Docs/Generated_Item_Base_Stats_Affixes_Quality_System.md`
- `Docs/Stats_Attributes_Item_Modifiers_Encumbrance_System.md`
- `Docs/Crafting_Profession_Skill_Progression_System.md`
- `Docs/Item_Valuation_Vendor_Pricing_Trade_System.md`
- `Docs/Banking_Currency_Custody_Future_Cashout.md`

---

# 1. Upgrade Identity

Recommended exact-item state:

- `ItemInstanceID`
- `ItemDefinitionID`
- `UpgradeProfileID`
- `UpgradeLevel` / EnhancementTier where the profile uses levels
- upgrade/modification records
- upgrade history/revision
- condition/durability
- generated affixes/quality
- creator/provenance/owner/possessor

Normal upgrade flow:

`ItemInstanceID #84721 + UpgradeLevel 2`
-> approved upgrade transaction
-> same `ItemInstanceID #84721 + UpgradeLevel 3`

Do not remove the original inventory entry and create a new unrelated ItemInstance merely to display `+3`.

## True Transformation Exception

A recipe may explicitly define a destructive transformation into a fundamentally different definition.

Example:

`Damaged Iron Sword`
-> forge conversion recipe
-> `Reforged Steel Sword`

If the design considers this a newly created physical object, the original may be consumed and a new ItemInstance created. The new record should preserve transformation/provenance links to the source where relevant.

---

# 2. Upgrade Eligibility

Upgradeable status is data-driven.

Possible Item Definition / Upgrade Profile rules:

- allowed item families/categories;
- minimum/maximum upgrade level;
- allowed upgrade paths;
- required profession/skill;
- required workstation/tool;
- required condition/durability threshold;
- prohibited item states;
- legal/license restrictions;
- mutually exclusive enhancement branches;
- whether generated affixes may be retained, improved, rerolled or never touched.

The Upgrade UI filters eligible ItemInstances by these rules instead of assuming every Weapon/Armor is upgradeable forever.

---

# 3. Upgrade Profile

Suggested stable identity:

`UpgradeProfileID`

A profile may define per-level/tier data such as:

- target stat/capability changes;
- Add / Multiply / authored curve operation;
- maximum level/tier;
- material requirements;
- currency/service cost policy;
- required profession/skill;
- workstation/tool requirements;
- success/failure behavior where the game deliberately supports chance;
- durability/condition effects;
- visual/audio presentation;
- progression reward;
- upgrade branch/path metadata.

Do not hardcode one universal `BaseStat × 1.1` modifier across all items.

Different item families can use different curves and caps.

Examples:

- sword reinforcement may raise durability and physical damage modestly;
- armor reinforcement may raise protection while adding some mass;
- tool calibration may improve precision/efficiency rather than damage;
- magical enhancement may add a new capability/affix through a separate profile.

---

# 4. Upgrade Level Is Not the Item Name

The UI may display:

- `Iron Sword +1`
- `Iron Sword +4`
- `Reinforced III`
- another localized tier label

but `+1` is presentation derived from persistent upgrade state.

Do not permanently mutate the base localized item DisplayName string by appending text every upgrade.

This keeps:

- localization clean;
- sorting/filtering stable;
- ItemDefinition identity unchanged;
- tooltips/world labels/equipment UI synchronized from one UpgradeLevel source.

---

# 5. Preview / Stat Comparison

Before confirming an upgrade, UI may show:

- current ItemInstance stats;
- expected post-upgrade stats;
- changed values/deltas;
- upgrade level/current cap;
- required materials;
- currency/service cost;
- profession/skill requirement;
- workstation/tool requirement;
- condition/durability impact;
- unavailable/failure reason.

The preview is calculated from authoritative definitions/current ItemInstance state but is presentation only.

Server recalculates/revalidates on submission.

The same comparison-direction metadata from the Stats system applies: higher is not automatically better for every value (for example lower weight can be beneficial).

---

# 6. Materials

Upgrade materials are normal persistent ItemDefinitions/ItemInstances.

Examples:

- metal ingots/plates;
- leather/components;
- rare catalysts;
- gems/dust/crystals;
- replacement parts;
- supernatural reagents.

A tutorial `Diamond Dust` resource is acceptable as an example material if Metaworld designs such a resource, but it is not a hidden currency.

Material requirements use the same inventory/container/reservation architecture as crafting.

They may come only from approved accessible sources according to upgrade context.

---

# 7. Currency / Service Cost

No generic tutorial `Gold` currency is introduced.

Canonical currencies remain:

- GrimKoin;
- PromoKoin where the specific service allows it.

An upgrade does not automatically require currency merely because materials are required.

Possible cases:

- player performs own upgrade at owned workstation -> materials/work only;
- NPC/business provides upgrade service -> service quote/fee in GrimKoin/PromoKoin;
- city/regulatory fee -> explicit fee/tax where applicable;
- supernatural altar/process -> may require non-currency resources instead.

Business/service pricing follows the contextual economy/ledger architecture rather than one universal static Gold formula.

---

# 8. Upgrade Request / Atomic Transaction

Suggested request:

`RequestUpgradeItem(ItemInstanceID, UpgradePathID, UpgradeContextID, SelectedSourceContainerIDs)`

Server validates:

- exact item exists and requester may modify it;
- item is currently upgradeable;
- requested next level/path is legal;
- current UpgradeLevel/revision matches expected state;
- required profession/skill is satisfied;
- correct station/tools/context are available;
- required materials exist in approved sources;
- required currency/service payment is available where applicable;
- item is not reserved/traded/locked by another transaction;
- generated/modification compatibility rules pass.

Commit flow:

1. reserve ItemInstance and required inputs/payment;
2. recalculate post-upgrade state;
3. consume materials/payment according to policy;
4. mutate same ItemInstance upgrade state;
5. update effective modifiers/stats;
6. record upgrade provenance/history/revision;
7. persist atomically;
8. refresh equipment-derived stats if item is equipped;
9. replicate authorized state;
10. emit progression/notification/UI update after success.

If required commit fails, the item and costs remain unchanged unless a deliberately designed risk/failure mechanic explicitly says otherwise.

---

# 9. Equipped Item Upgrade

Default recommended UX is to require the item to be in an eligible controllable inventory/workstation context, but an implementation may allow an equipped item if server rules explicitly support it.

If an equipped item upgrades successfully:

- same ItemInstanceID remains equipped;
- remove/rebuild that source's effective modifier snapshot safely;
- do not apply old + new bonuses simultaneously;
- refresh Character Stats/Equipment UI from `OnItemInstanceChanged` / `OnStatsChanged` style events.

---

# 10. Base Stats / Generated Affixes / Upgrade Modifiers

Metaworld keeps these layers distinct:

`ItemDefinition base functionality`
+
`ItemInstance generated affixes/quality`
+
`Upgrade/enhancement records`
+
`Condition/durability effects`
=
`Effective Item Stats`

Upgrade policy explicitly states what it can change.

Examples:

- reinforcement modifies base-derived damage/protection/durability;
- socket/gem upgrade adds an authored enhancement modifier;
- specialized reroll process may replace one generated affix only if that feature is intentionally designed;
- ordinary `+1` does **not** reroll all existing affixes.

Avoid double-counting the same stat across base/generated/upgrade layers.

---

# 11. Upgrade Caps / Branches

Maximum level is data-driven by UpgradeProfile, item family, rarity/quality where deliberately relevant, and world rules.

When maxed:

- upgrade action becomes unavailable;
- UI clearly shows Max/Completed state;
- cost widgets/actions collapse or disable appropriately;
- no hidden extra upgrade request succeeds server-side.

Possible future branching:

`Sword +3`
-> Reinforced path
or
-> Lightweight path
or
-> Enchanted path

Branches may be mutually exclusive or allow specific combinations according to profile data.

---

# 12. Stacking

Unique upgradeable equipment generally should not stack when its exact ItemInstance state differs.

For stackable items, stack compatibility must consider all state that cannot be lost, including where applicable:

- ItemDefinitionID;
- UpgradeLevel/path;
- generated affixes;
- condition/quality;
- ownership/provenance;
- evidence/stolen state;
- modifications.

Two visually identical items do not stack if merging would erase meaningful persistent differences.

---

# 13. Profession / Skill Progression

A successful upgrade may award practice/XP to the relevant profession/skill if the Upgrade Profile defines it.

Examples:

- Smithing reinforcement -> Smithing/Metalwork progress;
- Gunsmith modification -> Gunsmith/PrecisionAssembly;
- Armor tailoring -> Tailoring/Leatherwork.

No one generic Crafting Level owns all upgrade progression.

Progression reward is server-owned and occurs after the qualifying committed work/result.

---

# 14. Economy / Value

Upgrade state can affect contextual valuation because it changes the exact ItemInstance.

A vendor may value:

- higher UpgradeLevel;
- useful enhancement path;
- condition;
- generated affixes;
- provenance/creator;
- demand/scarcity;
- legal status.

Actual vendor quote remains contextual; `+5` does not guarantee a fixed world price.

---

# 15. UI Synchronization

Upgrade screen, inventory entry, equipment slot, tooltip, character preview and stats panel consume the same ItemInstance upgrade state/presentation snapshot.

Required behavior:

- item removed/moved while selected -> selection invalidates safely;
- successful upgrade -> selected snapshot refreshes;
- max level -> costs/action hide/disable;
- leaving/re-entering tab resolves current ItemInstance state instead of showing stale cached values;
- no raw per-frame bindings required;
- no `+1` hardcoded in multiple widgets separately.

Controller/keyboard/mouse users receive the same upgrade preview, costs and confirmation path.

---

# 16. Persistence / Concurrency

Persist UpgradeLevel/path/modification records and revision on exact ItemInstance.

Server serializes concurrent modification attempts so two upgrade requests cannot both spend the same inputs or independently advance +2 to +3 twice.

Save/load, drop, trade, death/estate transfer and container movement preserve upgrade state.

---

# 17. Performance

- upgrade calculations happen on selection/request/item-state change, not Tick;
- preview is cached until relevant state changes;
- material/currency availability refreshes from deltas/events;
- unloaded upgraded items remain data records;
- UI refreshes only affected entries;
- heavy upgrade visuals/assets use soft references where appropriate.

---

# 18. Acceptance Tests

1. Upgrading +2 -> +3 preserves the same ItemInstanceID.
2. Upgrade cannot create a duplicate old/new owned item.
3. Max UpgradeLevel is enforced both UI-side and server-side.
4. Upgrade preview matches committed result for deterministic profile changes.
5. Currency uses GrimKoin/PromoKoin policy; no Gold balance appears.
6. Diamond Dust/other catalyst is a normal persistent material item.
7. Failed transaction cannot consume materials/payment while leaving item unchanged unless explicit failure-risk design says so.
8. Equipped upgraded item does not double-apply old and new modifiers.
9. Upgrade state survives save/load/drop/trade.
10. Upgrade history/provenance remains attached to the same item.
11. Two concurrent requests cannot both advance the same item from one level/revision.
12. Different UpgradeProfiles can use different stat curves/costs without rewriting core logic.
13. UpgradeLevel participates in stack compatibility where stacking is permitted.
14. Tooltip/inventory/equipment/preview all show the same current upgrade state.
15. Successful upgrade can award the correct profession/skill once.
16. True transformation recipes create a new ItemInstance only when explicitly defined and preserve source provenance linkage where required.

## Core Rule

> Reinforcement modifies the history and capability of the exact item the player owns. Costs, caps and stat changes are data-driven and authoritative; the UI previews the transaction, but never replaces the item with a disconnected copy.