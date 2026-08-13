# Metaworld — Base-Building Playlist Phase 20 Roadmap Addendum — Part 6

**Status:** Canonical / Approved Playlist Intake Log Continuation

**Continues:** `Docs/Base_Building_Playlist_Phase20_Roadmap_Addendum_Part5.md`

**Base Master Roadmap:** `Docs/Master_Development_Roadmap.md` v2.9

**Purpose:** Continue recording approved tutorial-playlist intake without repeatedly replacing increasingly large earlier addenda. Parts 1-6 are equally canonical intake material until final consolidation into the Master Roadmap and relevant companion systems.

## Permanent Rules Carried Forward

All permanent rules from Parts 1-5 remain active, including:

- Blueprint-first runtime architecture.
- stable Buildable/Family/Variant/Stage/Item/Structure/Relationship IDs.
- server-authoritative placement, construction, resources, damage, relocation, demolition, relationships, replication and persistent world state.
- client prediction never overrides authoritative world truth.
- persistent construction relationships are typed records, not rediscovered from one generic parent Actor pointer.
- durable multiplayer state replicates compactly; transient RPC/Multicast presentation is never the persistence source.
- settled construction uses relevancy/dormancy/performance budgets.
- keyboard/mouse, Xbox-style and PlayStation-style gameplay paths remain first-class.
- no paid external service is required for the baseline persistence architecture; local/free adapters are acceptable during development.

---

# Playlist Intake Status — Continued

## Episode 22 — Construction Save/Load & Persistent World Reconstruction

**Classification:** UPGRADE — APPROVED.

**Phase Ownership:** Phase 20 Construction State + Persistent World/Data Architecture + Phase 60 multiplayer reconstruction integration.

Detailed companion:

`Docs/Construction_World_Persistence_Save_Load_System.md`

Related canonical companions remain:

- `Docs/Construction_Progress_Build_To_Completion_System.md`
- `Docs/Construction_Material_Delivery_Resource_Consumption_System.md`
- `Docs/Structural_Relationship_Hierarchical_Destruction_System.md`
- `Docs/Construction_Relocation_Move_System.md`
- `Docs/Buildable_Damage_Structural_Destruction_Chaos_System.md`
- `Docs/Construction_Multiplayer_Replication_Authority_System.md`

### Approved Tutorial Intent

- buildable identity/state/transform must survive between sessions;
- save records must update when structures are placed, modified or removed;
- destroyed/removed structures must not reappear after load;
- completion/material state must restore correctly;
- multiplayer clients must see the same loaded world;
- special buildables such as Windows follow the same persistence contract as ordinary buildables.

### Metaworld Upgrades

- tutorial host-Character save ownership is rejected as canonical architecture; persistent construction belongs to a server/world persistence service independent of any one player Character;
- a Character may die, disconnect or never have created the structure, while the city/property still persists;
- Unreal SaveGame is approved as a free local/dev persistence adapter, but construction gameplay talks to canonical persistence records/repository contracts rather than directly depending on one `.sav` implementation;
- persistence backend remains swappable so later local SQLite/server database/service storage can replace or supplement SaveGame without changing construction gameplay truth;
- suggested `S_MW_SavedStructure` includes schema version, StructureID, Buildable/Family/Variant IDs, authoritative transform, property/owner, construction state/stage/work, material ledger state, condition/damage/breach/destroyed state, appearance references, utility state, timestamp and revision as applicable;
- runtime Actor pointers are never authoritative persistent identity;
- Episode 17 typed `S_MW_StructureRelationship` records persist explicitly by stable IDs;
- saved parent/support/opening/attachment relationships are restored directly from IDs rather than re-created by fresh line traces on every load;
- traces may be used only for validation/recovery when saved relationship data is invalid or being repaired;
- material persistence preserves Required, Delivered, Consumed, AvailableOnSite and Lost/Damaged quantities so save/load cannot duplicate or erase construction resources;
- Construction Work Units and Current Stage restore exactly enough to prevent progress reset/duplication exploits;
- legitimate relocation preserves the same StructureID and updates its saved transform/relationships atomically rather than defining Move as destroy-old/spawn-new identity;
- runtime reconstruction can spawn a new Actor instance while preserving the same persistent StructureID;
- placement, material delivery, stage milestones, completion, ownership change, relocation, demolition, meaningful damage/destruction, support/relationship change and relevant utility changes mark persistence records dirty;
- do not rewrite/save the entire city for every wall action;
- incremental/dirty record persistence and batched writes are preferred where safe;
- linked transactions persist together: inventory debit + site credit, relocation transform + occupancy/relationships, demolition + relationship cleanup/salvage, destruction + support/opening consequences;
- load order is multi-pass rather than BeginPlay/Delay dependent: load metadata -> reconstruct structures/IDs -> apply base state -> restore relationships -> resolve derived support/opening/utility/collision state -> expose through replication -> settle/dormancy;
- no arbitrary Blueprint Delay is used to make parent/child load ordering correct;
- world/region/cell persistence supports streamed reconstruction instead of one whole-world BeginPlay spawn storm;
- unloading a runtime Actor is not deletion from persistence;
- `Unloaded`, `Destroyed/Collapsed`, and `Removed/Demolished` are distinct states;
- `Destroy Actor` during streaming/runtime cleanup must not erase a valid persistent structure;
- significant removals can use tombstone/history records so stale backups/replicas do not resurrect deleted structures and Event Ledger/audit systems retain causation where needed;
- persistence records carry schema/version metadata and explicit migrations for changed Buildable/Variant IDs/fields/relationship formats;
- current assets are resolved from stable IDs/data definitions rather than embedding full mesh/material asset data into every save record;
- installed Door/Window identity, OpeningID, lock/security state, damage/breach state and stable interaction state restore independently from the structural wall opening;
- Chaos shard trajectories are not normal save data; destroyed state restores to a stable damaged/destroyed representation, with only explicitly gameplay-critical debris proxies persisted;
- prefab persistence retains PrefabInstanceID, root StructureID, supports, openings, installed objects, utilities, logical damage sections, expansion modules and construction state even when visual geometry is merged/Nanite optimized;
- legitimate offline NPC/company construction uses saved timestamps, contracts, resources and schedule rules; elapsed time alone never magically completes construction;
- persistence load failures use explicit diagnostics/quarantine/migration states rather than silently spawning random default content;
- event-driven durable transactions plus periodic checkpoints replace one global synchronous autosave;
- large/live saves use asynchronous/batched I/O where practical to avoid gameplay/server hitching;
- clients never load a private SaveGame and push shared structures into the authoritative world;
- authoritative server restores persistence, then replication exposes reconstructed state to relevant clients;
- replication and persistence remain separate concerns: persistence stores world truth across absence/restarts; replication delivers relevant current truth over the network;
- save/load does not require a paid cloud/backend during early development; the canonical data model is provider/backend agnostic;
- future Python/Editor health tooling can validate schema versions, migration mappings, saved fixtures, invalid relationships, Item IDs and serialization coverage.

### Persistence Principle

> Metaworld saves the world, not the temporary Actors that represent it. Stable Structure IDs, transforms, construction/material state, ownership, damage and typed relationships survive streaming, disconnects, permanent character death and server restarts. Loading reconstructs authoritative server truth first; replication and visuals follow from that state.

---

# Current Persistence / Multiplayer Construction Flow

`Authoritative World Transaction`

`-> Update Structure / Relationship / Material / Damage State`

`-> Mark persistence records dirty / commit linked transaction`

`-> Persist incrementally / checkpoint`

`-> Server restart or region load`

`-> Load schema + persistent records`

`-> Reconstruct StructureIDs / transforms / base state`

`-> Restore typed relationships / openings / supports / utilities`

`-> Resolve derived state / collision / stability`

`-> Replicate compact current truth to relevant clients`

`-> Clients derive visuals/UI`

`-> Settled objects return to dormancy`

---

# Playlist Continuation Rule

Future playlist episodes may continue in this Part 6 file until another safe continuation is needed. Parts 1-6 together remain the canonical playlist intake log until final consolidation into the Master Roadmap and relevant companion documents.
