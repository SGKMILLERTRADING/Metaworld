# Metaworld — Master Roadmap v4.1 — Gap-Closure Overlay

**Status:** Canonical Roadmap Overlay
**Preserves:** `Docs/Metaworld_Master_Roadmap_v4_0_Consolidated_Starting_Roadmap.md` and all earlier canonical documents except where this overlay upgrades a listed gap from `Needs Architecture` to `Architecture Acquired`.

## Purpose

v4.0 identified several major areas Metaworld still needed before the roadmap could become a serious implementation plan. This overlay closes those design gaps with focused canonical architecture documents.

`Architecture Acquired` still does **not** mean the system is implemented, multiplayer-tested, persisted or performance-proven.

---

# 1. Critical Infrastructure Gap — CLOSED AT ARCHITECTURE LEVEL

## Persistent Backend / Dedicated Server

**New authority:** `Docs/Persistent_Backend_Dedicated_Server_Data_Architecture.md`

Now established:

- dedicated authoritative Unreal server;
- separate durable persistence service/database;
- Account/Character/Item/Container/Property/Vehicle/etc. persistent records;
- idempotent TransactionID model;
- revision/concurrency rules;
- restart/reconnect reconstruction;
- local/self-hosted development baseline;
- replication vs persistence separation;
- future region/server handoff direction.

## Online Service Boundary

**New authority:** `Docs/Online_Service_Integration_Architecture.md`

Now established:

- provider-agnostic online-service layer;
- online identity -> AccountID -> CharacterID mapping;
- sessions are connection context, not world storage;
- local/null development route;
- voice/friends/presence remain separate from in-world permissions/relationships.

---

# 2. Large World / Map Production Gap — CLOSED AT ARCHITECTURE LEVEL

**New authority:** `Docs/Large_World_Production_Architecture.md`

Now established:

- UE5.8 Large World Coordinates;
- World Partition;
- One File Per Actor;
- Data Layers;
- HLOD;
- Level Instances;
- PCG;
- Nanite integration;
- stable Region/City/District/Parcel/Building/Road IDs;
- vertical-slice district first;
- unloaded state uses persistent records/timestamps;
- Editor/Python validation direction.

---

# 3. Vehicles / Transportation Gap — CLOSED AT ARCHITECTURE LEVEL

**New authority:** `Docs/Vehicle_Transportation_Ownership_Persistence_System.md`

Now established:

- VehicleDefinitionID vs exact VehicleID;
- persistent ownership/access;
- seat reservation;
- vehicle ContainerIDs;
- fuel/energy;
- condition/maintenance;
- parking/dormancy;
- significance-aware traffic;
- Chaos Vehicles / Modular Vehicles evaluation;
- networked-physics testing;
- commercial/public transport extension path.

---

# 4. Health / Recovery Gap — CLOSED AT ARCHITECTURE LEVEL

**New authority:** `Docs/Character_Recovery_Care_Architecture.md`

Now established:

- persistent recovery-state records;
- body-zone integration;
- Vitals remains Health authority;
- Movement Resolver integration;
- real care supplies/services;
- profession/facility integration;
- timestamp recovery while unloaded;
- NPC significance-aware care state;
- single death pipeline remains authoritative.

---

# 5. Agriculture / Food Production Gap — CLOSED AT ARCHITECTURE LEVEL

**New authority:** `Docs/Agriculture_Food_Production_Supply_System.md`

Now established:

- persistent farms/plots/crop cycles;
- timestamp growth;
- real harvest batches;
- storage/processing/transport supply chain;
- spoilage/preservation by timestamp;
- profession/job integration;
- NPC/household consumption;
- real scarcity instead of infinite vendor restock.

---

# 6. Organizations / Factions Gap — CLOSED AT ARCHITECTURE LEVEL

**New authority:** `Docs/Organization_Faction_Membership_Authority_System.md`

Now established:

- OrganizationID / MembershipID / RoleID;
- shared framework for businesses, civic groups, factions, gangs, clubs, guilds and other organizations;
- role/permission checks;
- organization treasury/property/storage;
- relationship/diplomacy records;
- multiple leadership/governance models;
- persistence independent of loaded member Actors.

---

# 7. Deeper NPC Life / Population Gap — CLOSED AT ARCHITECTURE LEVEL

**New authority:** `Docs/NPC_Schedule_Relationship_Goal_Population_System.md`

Now established:

- persistent NPC life record;
- schedule blocks;
- household/home/employment links;
- long-term goals;
- multidimensional relationships;
- employment/payroll integration;
- StateTree/Smart Object local behavior direction;
- four significance tiers;
- timestamp/data simulation while unloaded;
- materialization from persistent state.

---

# 8. Communications Gap — CLOSED AT ARCHITECTURE LEVEL

**New authority:** `Docs/Communication_Voice_Text_Radio_Channel_System.md`

Now established:

- proximity voice/text;
- direct/property/vehicle/organization/radio/service channels;
- ChannelID/access policy;
- relevance-based routing;
- UE Voice Chat Interface evaluation;
- spatial voice presentation;
- text persistence where needed;
- mute/block/report boundaries;
- bounded network behavior.

---

# 9. Operations / Moderation Gap — CLOSED AT ARCHITECTURE LEVEL

**New authority:** `Docs/Operations_Moderation_Admin_Architecture.md`

Now established:

- platform administration separate from playable ranks;
- audit records;
- moderation/report workflows;
- technical recovery/support;
- backup/restore requirements;
- creator-content operational state;
- privacy boundaries.

---

# 10. Accessibility / Localization Gap — CLOSED AT ARCHITECTURE LEVEL

**New authority:** `Docs/Accessibility_Localization_Input_Presentation_System.md`

Now established:

- remapping/toggle/hold alternatives;
- sensitivity/dead-zone settings;
- UI scaling/readability;
- non-color-only critical meaning;
- subtitles/captions;
- localization-ready Text/String Table direction;
- layout resilience;
- localized dates/numbers/currency presentation;
- controller/accessibility acceptance gate.

---

# 11. Business Operations Gap — CLOSED AT ARCHITECTURE LEVEL

**New authority:** `Docs/Business_Operations_Accounting_Supply_Chain_System.md`

Now established:

- persistent BusinessID and ledger;
- real stock ContainerIDs;
- supplier/delivery records;
- employees/shifts/payroll;
- operating hours;
- service businesses;
- expenses/taxes/accounting categories;
- failure/closure/ownership transfer;
- NPC/player/organization ownership through the same core model.

---

# 12. What Is Still Missing Now

The major design gaps above are no longer blank areas. The remaining work is now primarily **implementation proof, integration depth and content**.

## Technical Spikes Required

### Spike A — Dedicated Server + Persistence

Build the minimum local stack:

- dedicated UE5.8 server;
- 2 local clients;
- local persistence service/database;
- AccountID/CharacterID;
- one ItemInstance transaction;
- reconnect;
- server restart;
- duplicate/idempotency test.

### Spike B — Replication Technology

Benchmark representative Metaworld Actor/component load using:

- generic replication baseline;
- UE5.8 Iris candidate path.

Do not select by marketing claims alone. Measure server CPU, bandwidth, relevancy/filter behavior and late join.

### Spike C — World District

Create a small World Partition district proving:

- Data Layers;
- HLOD;
- persistent objects across streaming;
- NPC materialization;
- one property/interior;
- one business;
- one construction parcel;
- one vehicle route.

### Spike D — Vehicle

Build one ordinary persistent car proving:

- VehicleID;
- driver/passenger seats;
- network movement under latency;
- storage;
- energy/fuel;
- parking/dormancy;
- restart reconstruction.

### Spike E — NPC Life

Build one NPC proving:

- home;
- schedule;
- work;
- Smart Object use;
- wage/food transaction;
- relationship change;
- unload/timestamp simulation;
- later materialization.

### Spike F — Business + Agriculture Supply Chain

Build one small chain:

`Farm/Producer -> Storage -> Delivery -> Shop -> Household/Player`.

Prove stock scarcity and restart persistence.

### Spike G — Communication

Prove local proximity channel plus one organization/vehicle channel with relevance-based delivery.

### Spike H — Recovery/Care

Prove one persistent recovery state, one legitimate care action/service, Movement Resolver integration and restart persistence.

---

# 13. Tutorial / Research Selection Rule Going Forward

Future playlists should be chosen to provide implementation detail for systems above rather than repeating mature basic inventory/crafting/combat tutorials.

High-value research targets now include:

1. UE5.8 dedicated-server production workflows;
2. persistence/database integration patterns;
3. Iris/network scaling and profiling;
4. World Partition/Data Layers/HLOD/PCG large-world production;
5. Chaos/Modular Vehicle multiplayer workflows;
6. StateTree/Smart Objects and scalable NPC schedules;
7. business/economy/supply-chain implementation;
8. agriculture/farming production;
9. health/recovery/service systems;
10. voice/online-service integration;
11. accessibility/localization pipelines;
12. large-scale profiling and operations.

---

# 14. Updated Roadmap Principle

Metaworld no longer needs another round of broad feature brainstorming before implementation can start.

The architecture now covers the major world pillars.

The development focus becomes:

`PROVE FOUNDATION -> BUILD VERTICAL SLICE -> STRESS TEST -> EXPAND CONTENT -> ADD REGIONS/SYSTEM DEPTH`

## Core Rule

> v4.0 identified the missing pillars. v4.1 gives those pillars architecture. The next milestone is not more ideas — it is proving the architecture in a small persistent multiplayer Metaworld slice.