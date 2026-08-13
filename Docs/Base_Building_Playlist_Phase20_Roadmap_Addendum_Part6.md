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
- private residential property is locked to unauthorized outsiders by default; household/property access is server-authoritative persistent permission state rather than a client-side Door Boolean.

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

## Episode 23 — Raise/Lower Foundation Elevation + Household Property Access

**Classification:** UPGRADE — APPROVED.

**Phase Ownership:** Phase 20 foundation terrain/support placement + Property/Household/Security access integration.

Updated foundation companion:

`Docs/Foundation_Terrain_Support_Extension_System.md`

New household/property access companion:

`Docs/Household_Property_Access_Lock_Permissions_System.md`

Related Door/Window interaction companion remains:

`Docs/Interactive_Doors_Windows_Runtime_System.md`

### Approved Foundation Tutorial Intent

- foundation placement can be raised or lowered relative to its initial terrain-derived candidate height;
- vertical adjustment is available only to buildables whose definitions permit it;
- lowering can allow controlled foundation embed into uneven terrain;
- elevation offset resets when starting a fresh build flow so one preview's adjustment does not leak into another.

### Metaworld Foundation Upgrades

- tutorial raw `AddLocation` vector becomes `RequestedFoundationElevationOffset` owned by `BPC_MW_BuildComponent` during preview;
- Foundation Buildable Definitions can expose `AllowElevationAdjustment`, `ElevationStep`, `MinElevationOffset`, `MaxElevationOffset`, `MaxTerrainEmbedDepth` and related support metadata;
- physical keys `8` and `2` are not canonical; use Enhanced Input actions such as `IA_MW_BuildRaise` / `IA_MW_BuildLower` with keyboard/mouse, Xbox-style and PlayStation-style mappings;
- capability is data-driven rather than one hardcoded `IsFoundation ? AddLocation : Zero` branch; other buildable families gain vertical adjustment only when their own definitions explicitly allow it;
- every raise/lower step dirties the candidate transform and re-runs terrain/support/overlap/property validation;
- raising may increase support-gap depth and therefore increase required pier/footing/extension segment count, resources and Construction Work Units;
- elevation that exceeds legal support depth, build height, property/air rights, zoning or support rules remains blocked;
- lowering into terrain is controlled intentional contact, not a universal collision bypass;
- tutorial box-extent shrinking/dividing is not adopted as a global fix; Metaworld uses authored terrain-contact/embed allowance and separate above-ground/below-ground placement volumes where needed;
- `MaxTerrainEmbedDepth` limits how far a foundation can intentionally enter terrain;
- lowered foundations still cannot penetrate protected utilities, public infrastructure, neighboring property, invalid underground structures or unrelated buildable obstruction footprints;
- the visible mesh remains separate from the authoritative placement/obstruction footprint;
- offset resets on Build Mode start, buildable selection change, placement completion/cancel or selection of a buildable that does not support elevation adjustment;
- final server placement independently clamps/rejects elevation and recalculates support samples/extensions/cost; a modified client cannot fake ground height or remove required supports;
- persistence stores the committed foundation transform and explicit support graph; save/load does not infer a new elevation from current player settings;
- no permanent elevation/terrain polling exists after placement.

### Household / Home Access Rule — User Canon

The user-established residential access rule is canonical:

> A private house is locked to outsiders by default. The owner, their husband/wife/spouse, their children/dependents where they are legitimate household members, and anyone else the owner explicitly gives access to can enter according to their permissions. Everyone else remains locked out unless a separate legitimate lease, legal or emergency authority grants access.

Approved access architecture:

- owner access is always recognized from authoritative property/title state;
- spouse/partner household access can be granted automatically for the shared residence without automatically transferring property ownership;
- legitimate household children/dependents can enter the home by default while high-risk powers such as sale, demolition, lock administration or secure-vault access remain separately permissioned;
- owner/authorized manager can explicitly grant or revoke access to friends, guests, tenants, employees, Builders, repair workers, security staff and other people/NPCs;
- grants may be permanent, temporary, scheduled, room/zone limited, contract-linked or one-time where supported;
- tenancy/lease rights are separate legal access rights and cannot always be revoked by simply clicking the ordinary lock UI while the lease remains legally active;
- legal/emergency override can exist for properly authorized police/court/fire/medical/emergency conditions; this is not an unrestricted admin bypass;
- physical/digital keys and credentials can exercise access, but possession of a stolen key does not make entry legally authorized;
- private properties can use room/access zones so `EnterHouse` does not automatically mean `OpenVault`, `ManageSecurity`, `Demolish`, `SellProperty` or `GrantAccess`;
- exterior residential access defaults to deny for unknown/unauthorized players and NPCs;
- a breached/destroyed door may allow physical passage but does not convert the intruder into an authorized resident; trespass/crime/evidence rules can still apply;
- Door Actors query the authoritative property/access policy rather than owning the entire household permission list themselves;
- access lists and grants persist across server restart and expose only necessary results to other clients; unrelated players do not receive the owner's full private access list;
- NPC residents/tenants/employees use the same permission model and locked doors affect their navigation/behavior;
- access management UI must work with keyboard/mouse, Xbox-style and PlayStation-style controllers;
- no per-door Tick checks household membership; permission checks are event-driven and can use safe revision-based caches.

### Tutorial Future-Roadmap Notes

The tutorial mentions future allowed/forbidden build zones, furniture, collision outlines and a Fortnite-style snapping grid. These are recorded as playlist signals, not automatic replacements of existing canon:

- **Allowed/forbidden building zones:** already substantially covered by Metaworld property/build volumes, zoning, protected/public areas and exclusion validation; future videos may add useful UI/authoring ideas.
- **Furniture:** compatible with the existing placeable/free-standing object direction; future playlist videos can contribute placement, interaction and relocation details.
- **Collision outlines:** useful as a future preview/readability enhancement if it can show blocked volumes/support reasons without expensive continuous rendering/query cost.
- **Fortnite-style grid snapping:** Metaworld already has data-driven GridSize/RotationStep plus typed structural snap points; future grid ideas can improve usability but will not replace support/opening/relationship-aware snapping with one universal grid.

### Foundation Elevation Principle

> Raising or lowering a foundation changes the requested placement elevation, not the rules. Every adjusted position still owes valid support, legal terrain embed, collision clearance, property rights, resources and server approval.

### Household Access Principle

> Metaworld homes are private by default. Household membership and explicit authorization grant access; ownership, residency, guest access and administrative powers remain distinct permissions, and outsiders stay locked out unless a legitimate world rule says otherwise.

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

# Current Foundation Elevation Flow

`Select Foundation Definition`

`-> Base terrain/snap candidate`

`-> Player raises/lowers RequestedFoundationElevationOffset`

`-> Candidate transform becomes dirty`

`-> Recalculate support samples / terrain embed / overlap / property rules`

`-> Recalculate extension count / resource + work cost`

`-> Client displays valid/blocked prediction`

`-> Server independently validates final transform/support/cost`

`-> Persistent Foundation + support graph created`

---

# Playlist Continuation Rule

Future playlist episodes may continue in this Part 6 file until another safe continuation is needed. Parts 1-6 together remain the canonical playlist intake log until final consolidation into the Master Roadmap and relevant companion documents.