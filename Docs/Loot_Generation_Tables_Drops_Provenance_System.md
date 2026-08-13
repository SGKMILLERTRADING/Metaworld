# Metaworld — Loot Generation, Tables, Drops & Provenance System

**Status:** Canonical / Approved Modern RPG Playlist Upgrade

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first / server-authoritative / persistent / data-driven / deterministic-capable

## Canonical Principle

Loot generation creates legitimate persistent item results from an authoritative loot source and table/profile. The result is generated once, recorded with provenance, and then behaves like any other ItemInstance in Metaworld.

> Loot tables decide what is created. They do not bypass ItemInstance identity, economy, ownership, evidence, condition, rarity, affix or container rules.

Related canon:

- `Docs/Persistent_Item_Interaction_Inventory_Architecture.md`
- `Docs/Generated_Item_Base_Stats_Affixes_Quality_System.md`
- `Docs/Gold_Material_Commodity_Not_Currency_Rule.md`
- `Docs/HUD_Notification_Feedback_System.md`

---

# 1. Loot Generator / Component

A reusable loot component/service is approved.

Suggested conceptual component:

`BPC_MW_LootSource`

It may be used by:

- defeated enemies/NPCs;
- wildlife/creatures;
- chests/containers;
- world caches;
- quest/event rewards where appropriate;
- destructible world objects;
- resource nodes where loot semantics fit.

The component references loot profile/table data rather than containing hardcoded item Switch logic.

---

# 2. Stable Loot Profile Identity

Recommended:

`LootProfileID`

Examples:

- `Loot.NPC.Bandit.Basic`
- `Loot.Container.Chest.Civilian.Small`
- `Loot.Creature.Wolf`
- `Loot.Business.Warehouse.Tools`

The profile can reference one or more groups/entries.

A Data Table/Data Asset is an approved Blueprint-first authoring source.

---

# 3. Loot Entry

Suggested conceptual entry fields:

- ItemDefinitionID or LootSubProfileID;
- weight/drop chance;
- minimum/maximum quantity;
- guaranteed vs optional;
- quality/generation profile;
- rarity/affix profile where applicable;
- condition range;
- level/region/context requirements where deliberately used;
- uniqueness/cooldown constraints;
- ownership/provenance policy;
- stack/lot creation policy;
- world/event tags.

Do not add one `DropChance` field to every ItemDefinition and assume the same chance applies to every enemy/chest/context in the world.

---

# 4. Weighted Selection

Weighted random selection is approved.

A loot group may calculate total positive weight, select an authoritative random value and resolve one or more entries according to the configured policy.

Possible group modes:

- ChooseOne;
- ChooseN;
- IndependentRolls;
- Guaranteed + Optional;
- WeightedWithoutReplacement;
- NestedSubTable.

The exact algorithm is profile data, not a UI concern.

---

# 5. No-Loot Outcome

A source may legitimately produce no item result.

Represent this through explicit profile policy such as:

- NoLootWeight;
- EmptyResult entry;
- minimum drop count = 0.

Do not fake no-loot by generating and immediately deleting items.

---

# 6. Generated Item State

If the selected loot item supports generated quality/affixes, generation happens **once when the persistent ItemInstance is created**.

Possible inputs:

- LootProfileID;
- source/source tier;
- region/event difficulty;
- source NPC/creature state;
- item generation profile;
- authoritative random seed/stream;
- authored world modifiers.

Do not reroll on BeginPlay, pickup, drop, opening loot UI or load/reconnect.

Materials/commodities such as wood, iron, leather and physical Gold receive only the generated state their explicit definition/profile allows.

---

# 7. Gold Rule

Tutorial-generated Gold as currency is rejected.

Loot may create **physical Gold material ItemInstances** such as Gold Nugget/Ore/Ingot only when the loot profile deliberately includes that commodity.

Loot may also award GrimKoin/PromoKoin only through the canonical currency/ledger/physical-wallet policy where the source legitimately holds currency.

Never create a generic `Gold += RandomAmount` money result.

If an NPC physically carried GrimKoin, the death/loot system may expose the legitimate carried amount according to world rules; banked balances are never loot-generated or transferred by looting.

---

# 8. Provenance

Generated loot records where useful:

- source LootProfileID;
- source CharacterID/ContainerID/EventID;
- generation timestamp;
- creator/manufacturer if definition requires it;
- generated quality/affixes;
- original legal owner/current possessor;
- stolen/evidence flags if the transfer becomes unlawful;
- generation transaction ID/revision.

This supports auditing and prevents reroll/duplication bugs.

---

# 9. Enemy Death / Corpse Relationship

Defeating an NPC does not automatically create arbitrary unrelated loot.

Possible policies:

- physical items the NPC actually carried/equipped move to corpse/body/container state;
- additional authored/generated loot may be created only when the game design explicitly defines it;
- quest/event drops can be generated separately with provenance;
- banked currency/accounts are not lootable;
- estate/property rights remain separate from reachable physical possessions.

Avoid duplicating the NPC's equipped sword by both moving the real ItemInstance to corpse inventory and generating a second identical sword from a loot table unless deliberately intended.

---

# 10. Loot Generation Timing

Possible generation moments:

- when a source is legitimately spawned/initialized and receives persistent identity;
- on authoritative death event;
- when a chest is first seeded;
- on scheduled restock/reset where world design explicitly permits it;
- event reward commit.

Once seeded, reopening/streaming the source does not regenerate it.

Persistent chests keep their current contents until changed/restocked by real world process.

---

# 11. Container Destination

Loot generation should normally place results into a real ContainerID or validated world-output state.

Examples:

- CorpseContainerID;
- LootBagContainerID;
- ChestContainerID;
- WorldDropBundleID;
- Workstation/Reward ContainerID.

The generator does not need to spawn one Actor per item immediately.

---

# 12. Performance

- loot profiles are data, not ticking Actors;
- generation occurs only at legitimate events;
- stored loot is compact container/item data;
- large nested profiles are resolved on demand, not every frame;
- world item Actors appear only when physical representation is required;
- deterministic seeds may aid replay/audit/debug;
- Python/editor validation can check impossible/zero/negative weights, missing ItemDefinitionIDs, circular nested tables and invalid generated-stat profiles.

---

# 13. Acceptance Tests

1. Loot source uses stable LootProfileID.
2. Same persistent source cannot regenerate loot merely by reopening UI/streaming.
3. Weighted selection respects configured profile.
4. No-loot outcome creates no phantom item.
5. Generated item affixes roll exactly once.
6. NPC equipped item is not duplicated by death loot unless profile explicitly creates another.
7. Physical Gold may drop as commodity; Gold never becomes tutorial currency.
8. Banked GrimKoin never appears in corpse loot.
9. Generated loot enters a legitimate ContainerID/world state.
10. Two clients cannot independently seed the same source differently.
11. Save/load preserves seeded container contents.
12. Loot provenance can identify source/generation transaction where required.

## Core Rule

> Loot is authoritative item creation and transfer, not a visual reward trick. The source rolls once, creates legitimate persistent results with provenance, stores them in real containers/world state, and never rerolls merely because an Actor or widget was recreated.