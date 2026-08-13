# Metaworld — Construction World Persistence, Save & Load System

**Status:** Canonical / Approved Phase 20 + Persistent World Upgrade

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first

## Canonical Principle

Metaworld construction persists as authoritative world data independent of any one player, host character, currently loaded Actor, or client session.

Core rule:

> Save stable world identity and relationships, not temporary Actor references. The server persists construction truth; loading reconstructs that truth by stable IDs; replication then exposes the reconstructed state to relevant clients.

The UE4 tutorial concepts of serializing buildable IDs, transforms, completion state, saving when structures change, removing destroyed structures from persistent storage, and restoring saved buildables are approved. The tutorial implementation of storing the whole world on the host Character, rebuilding relationships through new line traces, delete-and-respawn relocation semantics, and relying on BeginPlay to synchronously respawn the entire saved world is upgraded into a persistent-world architecture.

---

# 1. Persistence Is Not Host-Character State

The tutorial stores build data on the hosting player's Character. Metaworld rejects that as the canonical world model.

Construction persists in a server/world persistence layer because:

- a Character can die permanently;
- players disconnect;
- the world can run without the original builder online;
- a dedicated server has no local player Character acting as the host owner;
- property can transfer ownership;
- NPCs/companies/cities can build structures;
- unloaded regions must still retain world state;
- server restarts must not depend on one player's pawn.

Recommended Blueprint-facing concept:

`MW World Persistence Service`

or equivalent subsystem/service accessed through stable Blueprint contracts.

For early local/free development, an Unreal SaveGame-backed adapter is acceptable. The construction gameplay model must remain storage-backend agnostic so a local file, SQLite/server database, or later production persistence service can implement the same contract without rewriting construction gameplay.

---

# 2. Unreal SaveGame as an Adapter, Not the World Model

UE SaveGame classes are useful for local prototypes, test worlds, snapshots and small/medium persistence adapters.

Metaworld should define canonical persistence records first, then serialize those records through an adapter.

Conceptual layers:

`Construction Gameplay State`
-> `Canonical Persistence Records`
-> `Persistence Repository Interface`
-> local SaveGame adapter now / database adapter later

This prevents Blueprint Actors from directly knowing whether persistence currently lives in `.sav` files, SQLite, or another server-side store.

For live/large saves, prefer asynchronous or batched writes where the adapter supports them so gameplay is not stalled by large blocking saves.

---

# 3. Canonical Saved Structure Record

Suggested structure:

`S_MW_SavedStructure`

Possible fields:

- `PersistenceSchemaVersion`
- `StructureID`
- `BuildableID`
- `FamilyID`
- `VariantID`
- `PrefabInstanceID` where applicable
- `World/Region/CellID`
- authoritative `Transform`
- `PropertyID`
- `OwnerEntityID`
- `PermissionProfileID`
- `ConstructionSiteID` where unfinished
- `ConstructionState`
- `CurrentStageID`
- `CurrentWorkUnits`
- stage/material ledger reference or compact state
- `Condition/Durability`
- `DamageState`
- `BreachState`
- `Destroyed/Collapsed/RemovedState`
- creator/final material or appearance entitlement references
- `UtilityState` / connection references where needed
- `LastModifiedTimestamp`
- `StateRevision`
- relevant Event Ledger/cause references when needed

Do not persist raw runtime Actor pointers as world identity.

---

# 4. Relationship Records Are Saved Explicitly

Episode 17 remains canonical.

Suggested relationship persistence:

`S_MW_StructureRelationship`

including:

- `RelationshipID`
- `ParentStructureID`
- `ChildStructureID`
- `RelationshipType`
- `ParentSnapPointID`
- `ChildSnapPointID`
- `OpeningID`
- `AttachmentSlotID`
- support requirement metadata
- failure policy
- relationship state
- revision/timestamp where useful

Loading does **not** normally rediscover these relationships by firing new world traces.

A saved relationship is persistent world truth unless:

- referenced IDs no longer exist;
- data/schema migration invalidated the relationship;
- corruption/inconsistency is detected;
- an explicit recovery/repair tool is being run.

Line/shape traces can be used for validation/recovery, but not as the normal source of parent-child identity on every load.

---

# 5. Material / Construction Progress Persistence

Episode 20 material state must survive save/load exactly enough to prevent duplication or loss.

Persist as appropriate:

- Requirement/ItemDefinition ID
- Required quantity
- Delivered quantity
- Consumed quantity
- AvailableOnSite quantity
- Lost/Damaged quantity
- substitution/quality state where relevant
- material ledger revision

Example before restart:

- Wood Required: 20
- Delivered: 12
- Consumed: 8
- Available On Site: 4
- Missing: 8
- Work: 25 / 40

After load, that exact authoritative construction state returns.

Save/load must never reset Delivered to zero, re-credit consumed items, or mint duplicate inventory.

---

# 6. Stable Identity Survives Relocation

Episode 13 remains canonical.

Legitimate direct relocation preserves `StructureID` wherever the object's identity logically remains the same.

Flow:

`StructureID 84721 at Transform A`
-> authorized relocation transaction
-> server validates Transform B
-> relationships/occupancy updated atomically
-> persistence record for `StructureID 84721` stores Transform B

Do not define ordinary Move as:

`Destroy old StructureID -> spawn unrelated new StructureID`

unless the action is truly dismantle/rebuild or another system explicitly creates a new identity.

Runtime loading may spawn a new Actor instance from a saved record, but the persistent world object remains the same `StructureID`.

---

# 7. Save on Meaningful State Changes

The tutorial's idea of saving when structures are placed/modified/destroyed is retained, but Metaworld avoids rewriting the entire world for every tiny event.

Mark records dirty on meaningful authoritative changes such as:

- placement accepted;
- construction site created;
- material delivery transaction committed;
- work/stage milestone committed;
- final completion;
- ownership/property change;
- door/window installation/removal when persistent;
- relocation commit;
- authorized demolition/removal;
- damage/breach/destruction terminal or meaningful threshold change;
- support/relationship change;
- utility connection/state change;
- prefab logical state change.

Dirty records can be batched/flushed according to durability requirements.

Critical economy/ownership/material transactions should use stronger immediate transactional durability than purely cosmetic state.

---

# 8. Incremental Persistence / Dirty-State Strategy

Do not serialize the whole city every time one wall changes.

Recommended model:

- persistent record has `StateRevision`;
- authoritative change marks one or more records dirty;
- transaction commits linked records together when they must remain consistent;
- persistence worker/adapter writes changed records;
- periodic checkpoints/snapshots can compact/recover state;
- Event Ledger references can preserve important causation/history separately.

Examples of linked transactions:

### Material Delivery

Source Inventory debit + Site material credit must persist atomically.

### Relocation

Structure transform + old/new snap occupancy + support relationships must persist together.

### Demolition

Structure terminal state + child relationship resolution + occupancy cleanup + salvage/material state must persist consistently.

### Destruction

Damage terminal state + support relationship changes + opening/security state + relevant debris/blockage proxies must not produce half-saved worlds.

---

# 9. Loading Uses Multiple Ordered Passes

Do not rely on arbitrary BeginPlay ordering or short Delays.

Recommended server reconstruction flow:

## Pass 1 — Load World Metadata

- schema/version
- region/cell metadata
- authoritative Buildable definitions available
- persistent records selected for the region/world

## Pass 2 — Recreate Structure Identities

For each saved structure record:

- resolve Buildable/Variant definition;
- create/reconstruct runtime Actor or lightweight representation;
- restore stable `StructureID`;
- restore authoritative transform;
- apply basic construction/damage/persistent state.

## Pass 3 — Restore Relationships

After required structures exist in the runtime registry:

- restore support edges;
- snap/opening occupancy;
- installed Door/Window links;
- attachments;
- utility dependencies;
- prefab/module relationships.

## Pass 4 — Resolve Derived State

- support/stability result;
- final collision/traversal state;
- construction-stage capabilities;
- utility availability;
- Door/Window state;
- destroyed/breached representation;
- interaction capability.

## Pass 5 — Replication / Dormancy

- expose reconstructed authoritative state to relevant clients;
- clients derive visuals through replicated state;
- settled buildables enter appropriate dormancy.

This avoids relationship failures caused by Child Actor loading before Parent Actor, or vice versa.

---

# 10. Regional / Streamed Loading

Metaworld should not require the entire world to spawn in one BeginPlay burst.

Persistence records are partitionable by:

- World/Map ID
- Region/District ID
- World Partition cell or persistence cell
- Property/complex where useful

When a region becomes server-relevant:

- load/reconstruct its needed records;
- restore cross-region references through stable IDs/registry handles;
- stream/unload runtime Actors when safe while persistence records remain authoritative.

Unloading an Actor does not delete the structure from world persistence.

---

# 11. Removed vs Destroyed vs Unloaded

These states are different.

## Unloaded

Runtime Actor is absent because of streaming/relevancy, but persistent structure still exists.

## Destroyed / Collapsed

Persistent world object exists in a terminal damaged state and may load a destroyed representation/history.

## Removed / Demolished

Structure is no longer an active world object according to demolition/removal rules. Its active record can be deleted/tombstoned/archive-moved according to persistence policy.

Do not treat `Destroy Actor` as equivalent to deleting persistence.

Runtime Actor destruction during streaming or reconstruction must never erase a legitimate persistent structure.

---

# 12. Tombstones / Removal Records

A simple tutorial may delete a saved-array entry immediately. Metaworld can require stronger history/revision handling.

For significant persistent objects, removal can produce a compact tombstone/history record containing:

- StructureID
- removed/demolished/destroyed disposition
- timestamp
- reason/cause Event ID
- former Property/Owner
- replacement StructureID where applicable
- salvage/estate/legal references where needed

This helps prevent stale replicas/backups from resurrecting removed structures and supports audit/history systems.

Not every decorative object requires indefinite tombstone retention; retention policy is data/system dependent.

---

# 13. Save Schema Versioning & Migration

Persistence must expect the game to evolve.

Every saved record or persistence bundle should carry schema/version metadata.

When definitions change between game versions:

- old Buildable IDs map through explicit migration rules;
- renamed Variant IDs are translated;
- added fields receive safe defaults;
- removed fields are ignored/migrated intentionally;
- relationship schema upgrades preserve stable IDs;
- impossible/obsolete content is flagged for repair rather than silently corrupted.

Future `MW Construction Health Check` / Python Editor tooling can validate migration tables and sample old-save fixtures.

---

# 14. Buildable Definition Versioning

A saved structure should not depend only on whatever today's Data Table happens to say.

Possible strategy:

- save stable Buildable/Variant IDs;
- record definition/schema version used when needed;
- apply current compatible definition at load;
- run explicit migration when behavior/data changed incompatibly.

Do not embed every mesh/material byte in the save. Persist stable identity/state and resolve assets from authoritative current content definitions.

---

# 15. Multiplayer / Dedicated Server Ownership

Episode 21 remains canonical.

The authoritative server loads persistence before/while exposing world state to clients.

Clients do not load their own private build-save file and push structures into the shared world.

Dedicated/listen server testing may use the same persistence contract, but canonical world truth belongs to the server-side persistence layer.

Client flow:

`Connect / become relevant`
-> server already owns/reconstructs world state
-> replicated authoritative structures/state arrive
-> client derives visuals/UI

Replication is not the persistence source.

Persistence is not the replication transport.

---

# 16. Host Migration Is a Separate Future Problem

The tutorial stores saves on a hosting Character/session. Metaworld should not confuse save/load with peer host migration.

If listen-server host migration is ever supported, it requires a separate authority-transfer design.

The persistent world record remains the source used by the new authoritative server/host; player Characters themselves are not the canonical save repository.

---

# 17. Door / Window Persistence

Installed Door/Window state can persist independently from the structural opening.

Store as relevant:

- installed Object ID
- parent wall/opening ID
- Door/Window Variant ID
- lock/security state
- stable open/closed state where required
- damage/breach state
- permissions
- condition
- custom finish

On load:

- restore wall/opening;
- restore occupancy relationship;
- restore installed object;
- restore stable interaction state.

Do not line-trace the wall and guess which Door belonged there.

---

# 18. Damage / Chaos Persistence

Episode 16 remains canonical.

Persist:

- durability/condition;
- damage state;
- breach state;
- logical damage-zone state;
- destroyed/collapsed state;
- support consequences;
- authoritative gameplay blockage/debris proxies where needed.

Do **not** save every Chaos shard transform as normal persistent construction truth.

After restart/late load, use a stable damaged/destroyed representation unless a specific gameplay-critical debris object has its own authoritative persistent record.

---

# 19. Prefab Persistence

Prefab houses keep one coherent persistent prefab identity plus logical section/object relationships.

Persist as appropriate:

- PrefabInstanceID
- root StructureID
- definition/variant
- transform
- support relationships
- opening IDs/occupancy
- installed Door/Window IDs
- utility connections
- logical damage zones
- expansion modules
- construction stage/material state
- owner/property

Merged/Nanite visual geometry does not replace logical persistent state.

---

# 20. Offline Construction

Persistent construction sites can advance while unloaded only through legitimate world rules.

Store:

- last update timestamp;
- assigned crew/contract IDs;
- available material state;
- pause/block state;
- scheduled work policy.

On server processing/load:

- calculate valid elapsed work from approved labor/schedules/resources;
- cap by stage/material availability;
- apply authoritative progression;
- persist resulting state.

A construction site does not complete simply because real time passed.

---

# 21. Failure Recovery / Corruption Handling

Persistence loading should fail loudly and recover predictably.

Possible states:

- Valid
- NeedsMigration
- MissingDefinition
- MissingParentReference
- InvalidRelationship
- InvalidMaterialLedger
- Quarantined
- Repaired

Do not silently spawn a random default mesh or invent a new parent when authoritative IDs cannot resolve.

Developer tools should produce actionable diagnostics with StructureID, BuildableID and failing relationship/data references.

---

# 22. Autosave / Checkpoint Policy

Metaworld persistence should combine event-driven durable transactions with periodic checkpointing.

Examples:

- critical material/economy/property transactions: durable commit promptly;
- ordinary construction work progress: batch small increments where safe, but never enough to enable meaningful rollback/exploit;
- large structural state change: persist promptly;
- periodic region/world checkpoint: compact state and validate revisions.

Avoid one global synchronous autosave that freezes the server/client whenever many structures exist.

---

# 23. Performance Rules

- no full-world save for every single wall interaction;
- no full-world BeginPlay respawn storm;
- no per-frame save polling;
- dirty/event-driven persistence;
- async/batched storage writes where supported;
- region/cell-based loading;
- compact stable IDs instead of repeated heavy asset data;
- relationship restoration by IDs, not whole-world traces;
- avoid loading heavy soft-referenced assets until representation requires them;
- keep persistence work off latency-sensitive gameplay paths where possible while maintaining transaction safety;
- profile save/load duration, hitching, memory, database/file size and recovery behavior.

---

# 24. Security / Exploit Rules

A client cannot:

- write a shared-world save record;
- choose its own StructureID;
- change persisted owner/property;
- resurrect a removed structure;
- load a private forged SaveGame into the server;
- restore consumed materials;
- edit work progress;
- remove damage state;
- forge support/opening relationships;
- change authoritative transform without a legal relocation transaction.

Only server-authorized world transactions mutate canonical persistence.

---

# 25. Blueprint Architecture

Recommended Blueprint-facing responsibilities:

## `BP_MW_Buildable_Master`

Exposes compact serialization/apply-state hooks for common lifecycle, but does not write files directly.

Possible hooks:

- `BuildPersistenceSnapshot`
- `ApplyPersistenceSnapshot`
- `OnPersistenceRestored`

## `BPC_MW_ConstructionProgress`

Contributes construction stage/work/material snapshot data.

## Relationship Service

Persists/restores typed relationship records.

## World Persistence Service / Subsystem

Owns:

- repository requests;
- dirty tracking;
- save transactions;
- loading passes;
- schema migration;
- region queries;
- error reporting.

Individual Wall/Window/Foundation Blueprints do not each implement their own SaveGame file logic.

---

# 26. Python / Editor QA

Python Editor automation can validate:

- duplicate Structure fixture IDs in authored tests;
- missing Buildable migration mappings;
- save schema versions;
- invalid relationship fixtures;
- invalid ItemDefinition IDs in saved test data;
- missing prefab/opening references;
- unsupported legacy fields;
- sample old-save upgrade tests;
- serialization coverage for new persistent fields;
- save/load smoke-test content.

Python remains Editor/tooling only, not runtime persistence logic.

---

# 27. Initial Persistence Vertical-Slice Tests

1. Place a Foundation; server assigns StructureID; save/restart/load restores same identity and transform.
2. Snap a Wall to Foundation; relationship IDs restore without a discovery trace.
3. Install Door in DoorOpening; Door/Object ID and OpeningID restore correctly.
4. Partially supply Wall materials; restart preserves Required/Delivered/Consumed/Available quantities exactly.
5. Partially complete Construction Work; restart preserves Work Units/stage.
6. Relocate an eligible object; restart loads same StructureID at new transform.
7. Cancel relocation; original persistent transform remains unchanged.
8. Damage Wall; restart restores correct damage state/collision.
9. Destroy Wall; restart restores destroyed/breached state without replaying old Chaos shards.
10. Destroy support; restart restores updated support graph and dependent stability result.
11. Demolish Wall; restart does not resurrect it.
12. Prefab house restores logical openings, installed objects, supports and damage sections.
13. Unloaded region retains data without runtime Actors.
14. Reload region reconstructs records and relationships in deterministic passes.
15. Two clients reconnect and see the same reconstructed authoritative world.
16. Late joiner receives current state through replication, not local SaveGame.
17. Forged client save cannot create/alter shared structures.
18. Save schema upgrade migrates a fixture from prior version without losing identity.
19. Missing/invalid Buildable definition is reported/quarantined rather than silently replaced.
20. Large test region saves/loads without unacceptable frame/server hitching.
21. Keyboard/mouse, Xbox-style and PlayStation-style gameplay remain unaffected because persistence is input-agnostic.

---

# Core Rule

> Metaworld persistence saves the world, not the temporary Actors that happen to represent it right now. Stable Structure IDs, construction/material state, ownership, transforms and typed relationships survive streaming, disconnects, character death, server restarts and future storage-backend changes. Loading reconstructs authoritative state first; replication and visuals follow from that truth.