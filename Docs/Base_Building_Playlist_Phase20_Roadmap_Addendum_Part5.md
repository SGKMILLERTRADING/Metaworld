# Metaworld — Base-Building Playlist Phase 20 Roadmap Addendum — Part 5

**Status:** Canonical / Approved Playlist Intake Log Continuation

**Continues:** `Docs/Base_Building_Playlist_Phase20_Roadmap_Addendum_Part4.md`

**Base Master Roadmap:** `Docs/Master_Development_Roadmap.md` v2.9

**Purpose:** Continue recording approved tutorial-playlist intake without repeatedly replacing the increasingly large earlier addenda. Parts 1-5 are equally canonical intake material until final consolidation into the Master Roadmap and relevant companion systems.

## Permanent Rules Carried Forward

All permanent rules from Parts 1-4 remain active, including:

- Blueprint-first runtime architecture.
- `BP_MW_Buildable_Master` owns common lifecycle only; components/interfaces/data own reusable capabilities.
- `BPC_MW_BuildComponent` and shared interaction systems remain the player-facing construction architecture.
- stable Buildable/Family/Variant/Stage/Item IDs and server-authoritative persistent state.
- keyboard/mouse, Xbox-style and PlayStation-style controller support.
- construction stages use real materials, work units, professions/tools and persistent state.
- client-responsive UI/preview never overrides server-authoritative inventory, resource, construction, placement, damage or completion truth.
- no permanent Tick/polling on idle construction sites when event/context-driven updates can solve the problem.
- large-project logistics, NPC labor and offline simulation use persistent jobs/timestamps/data rather than full always-active Actor simulation.
- stable frame time remains a mandatory design constraint.
- durable multiplayer construction truth is replicated as compact authoritative state; client RPCs submit intent and transient cosmetic Multicast is never the only source of persistent truth.
- ordinary settled buildables do not continuously replicate movement; relevancy, dormancy and appropriate update frequency are required scaling tools.

---

# Playlist Intake Status — Continued

## Episode 20 — Construction Resource Requirements, Delivery & Consumption

**Classification:** UPGRADE — APPROVED.

**Phase Ownership:** Phase 20 Construction Progress / Inventory / Economy integration.

Detailed companion:

`Docs/Construction_Material_Delivery_Resource_Consumption_System.md`

Existing parent companion remains canonical:

`Docs/Construction_Progress_Build_To_Completion_System.md`

### Approved Tutorial Intent

- each buildable/stage can define required materials;
- construction UI can dynamically show required resources;
- a player can contribute materials from legitimate inventory sources;
- construction cannot finish when required resources are missing;
- inventory is reduced when valid materials are committed to construction;
- common logic should be shared rather than copied independently into Wall/Window/Foundation/etc. child Blueprints.

### Metaworld Upgrades

- tutorial `S_Buildable -> Items[S_Slots]` becomes a stable data-driven Construction Stage recipe using ItemDefinition IDs and requirement records rather than raw inventory-slot structures as recipe truth;
- recommended material requirement state separates Required, Delivered, Consumed, AvailableOnSite, Lost/Damaged and Missing quantities;
- material delivery and Construction Work Units remain separate requirements: delivering resources does not magically complete labor, and labor cannot invent missing resources;
- partial deliveries are supported so players/NPCs/companies do not need to carry an entire project's resources at once;
- legitimate material sources can include player inventory, backpack/container, authorized vehicle cargo, property storage, construction pallet/site storage, company warehouse, supplier delivery and NPC/company inventory according to permission rules;
- no arbitrary nearby inventory is silently drained;
- server owns the authoritative stage recipe and acceptable ItemDefinition IDs/quantities;
- recommended delivery request uses Site ID + Requirement/Item ID + requested quantity + authorized Source Inventory ID;
- server validates site/stage, permissions, source ownership/access, authoritative source quantity, item compatibility/quality/substitution rules, remaining requirement and transaction state;
- delivery is atomic: debit source inventory -> credit site delivered-material state -> persist both sides -> replicate result; a failed transaction changes neither side;
- concurrent multiplayer deliveries use locking/version/transaction protection so two clients cannot double-spend one stack or over-credit the same remaining requirement;
- client cannot fake inventory amount, deliver negative quantities, use another player's private inventory, change the recipe, or mark materials complete directly;
- consumption policy is data-driven and can occur on delivery, work progress, stage milestone or stage completion according to the material/stage design;
- delivered material and consumed/installed material remain distinct for cancellation, theft, damage, salvage and refund logic;
- cancellation/refund cannot mint resources; returned + salvaged amounts cannot exceed legitimate authoritative stock/installed material under applicable damage/salvage policy;
- construction sites may hold a compact logical material ledger instead of spawning one Actor per board/brick/nail;
- high-value/visible logistics can still use pallets, crates, trucks and physical delivery gameplay without requiring all bulk inventory to remain physical Actors forever;
- exposed unconsumed site stock may participate in future theft/security/crime rules when world rules allow; consumed structural material is not equivalent to loose inventory;
- installed persistent components such as Doors, Windows, generators or security equipment can preserve their own Object IDs/state rather than being flattened into anonymous bulk quantity when installed;
- NPC suppliers/construction companies use the same authoritative material requirement and delivery transaction model as players;
- large projects use stage-scoped recipes (foundation/frame/exterior/utilities/finish) instead of demanding every future resource on the first interaction;
- construction resource UI shows current-stage item name/icon, required/delivered/missing quantities, available source quantity, readiness and blocked reasons;
- controller users can inspect requirements, select authorized material source, deliver partial/all quantities and understand missing-resource feedback without mouse-only UI;
- tutorial's independent `0.1s` non-stop line trace for the resource widget is rejected as universal architecture;
- resource UI updates when interaction target changes, construction management UI opens/closes, site stage/material state changes, relevant source inventory changes or permissions/block reasons change;
- `BPC_MW_Interaction` remains the shared targeting path; resource widgets do not run their own forever-polling trace just to discover the same target;
- Build Master/child Blueprints do not directly mutate arbitrary Player/Backpack raw arrays; construction uses an inventory transaction contract/service;
- resource logic remains common construction-site/component behavior rather than duplicated in special Window/Wall/Foundation graphs;
- save/load/reconnect preserves required/delivered/consumed material state and cannot reset or duplicate deliveries;
- no permanent material-check Tick on idle construction sites;
- large material quantities replicate as compact state/deltas rather than full inventory dumps every frame;
- future `MW Construction Health Check` can audit missing/invalid recipes, invalid Item IDs/quantities, legacy direct raw-inventory mutation, impossible stage requirements and resource widgets that reintroduce permanent polling.

### Example State

`Structural Wall — Frame Stage`

- Wood Required: 20
- Wood Delivered: 12
- Wood Consumed: 8
- Wood Available On Site: 4
- Wood Missing: 8
- Construction Work: 25 / 40 Units

This state means the wall is partly supplied and partly worked. Neither the resource nor labor requirement is treated as automatically complete.

### Resource Transaction Principle

> Construction materials are real economy state. Authorized inventories lose exactly what an authoritative construction site receives, material delivery and labor remain separate, partial deliveries/logistics are supported, and no client can complete construction by faking inventory or resource progress.

---

## Episode 21 — Multiplayer Construction Replication & Authority

**Classification:** UPGRADE — APPROVED.

**Phase Ownership:** Phase 20 Construction Gameplay State + Phase 60 Multiplayer Replication.

Detailed companion:

`Docs/Construction_Multiplayer_Replication_Authority_System.md`

### Approved Tutorial Intent

- permanent build Actors are created by the server;
- clients submit placement/action requests to the server rather than authoritatively spawning world structures themselves;
- persistent construction state must be synchronized between players;
- materials/progress/damage/destruction must remain consistent for all relevant clients;
- special buildables such as Doors/Windows follow the same multiplayer authority rules as ordinary Buildables.

### Metaworld Upgrades

- client placement ghost remains local by default and is not continuously replicated during camera/stick/mouse preview movement;
- client submits placement intent/candidate transform, Buildable ID and relevant selection data through an owned Player/Character/Build Component server RPC path;
- server independently resolves the authoritative Buildable/Variant Definition and revalidates transform, orientation, property, zoning, footprint, obstruction, snap occupancy, support, profession, resources, permissions and other world rules;
- client preview fields such as `CanBuild`, local footprint size, local recipe/cost, local resource amount or claimed support are never trusted as authoritative;
- server assigns permanent Structure/Site/Object IDs and creates the authoritative Construction Site/Buildable;
- durable construction state uses replicated/RepNotify-style variables/structs so late joiners and newly relevant clients can reconstruct the current world state;
- persistent replicated state can include stable Structure ID, Buildable/Variant ID, settled transform, construction stage, compact progress, material readiness, damage state, breach/destroyed state, stable Door/Window state and relevant relationship/stability revisions;
- tutorial blanket `Replicate Movement` on every BuildMaster is rejected as a universal rule;
- settled Foundation/Wall/Floor/Roof/Column/Prefab structural pieces normally keep a stable authoritative transform and do not continuously replicate movement while idle;
- relocation continues to use a local temporary ghost + server validation + one committed new settled transform/relationship transaction rather than streaming movement during ordinary Move mode;
- Doors/Windows replicate accepted state/transition intent such as Closed/Opening/Open/Closing/Locked/Breached and clients animate from shared data instead of replicating panel transforms every frame;
- tutorial `MultiSetMesh`, `MultiFinishBuild`, `MultiDestroyBuild` patterns are rejected as the only persistent truth;
- mesh/material/collision/completion/destruction presentation derives from authoritative replicated state so late joiners do not require historical Multicast replay;
- Multicast remains allowed for genuinely transient one-shot presentation such as sounds, dust, sparks, impact VFX, destruction seed/impulse cues or similar effects when useful;
- resource delivery remains an atomic server transaction: validate source/site -> debit authoritative source -> credit authoritative site -> persist -> replicate compact result;
- clients do not multicast inventory subtraction or directly replicate arbitrary local inventory arrays into Construction Sites;
- Construction Work requests are server-validated for authorization, stage readiness, resources, profession/skill/tool, range, cadence and anti-spam before Work Units increase;
- replicate resulting compact progress/stage state rather than every hammer swing/frame value;
- damage/destruction remains server-authoritative; clients receive compact state/events and may play Chaos locally where relevant;
- individual Chaos shards are not persistent authoritative replicated objects by default;
- if specific debris must block/interact with gameplay, create/promote a small authoritative debris/blockage Actor with an explicit replication policy;
- structural relationship graph remains authoritative server/persistent data and is not dumped wholesale to every client;
- clients receive only relationship/stability/opening/attachment data required for relevant gameplay/UI;
- ordinary buildables are not `Always Relevant` by default;
- per-connection relevancy/streaming/distance/ownership/active-interaction rules limit which structures need network updates;
- settled persistent structures use dormancy aggressively: wake for meaningful state changes -> replicate -> return to dormant state;
- meaningful wake events can include stage/material changes, damage, relocation commit, demolition, utility changes, relationship/stability changes and other client-visible persistent transitions;
- Net Update Frequency should reflect object behavior; static buildings do not use character-like network update rates;
- avoid replicating fields that clients can derive from other replicated state;
- Actor Components replicate only when they own connection-relevant authoritative state/RPCs; helper/UI/editor/local-preview components are not replicated by default;
- client-to-server RPCs route through an Actor/Component legitimately owned by that client rather than assuming the client can call server RPCs on arbitrary world walls it does not own;
- replication is distinct from persistence: replication answers what a currently relevant connection needs now, while persistence preserves what remains true when no player is nearby/connected;
- late join/relevancy re-entry reconstructs current Buildable, transform, construction state, finishes, Door/Window state, damage/destruction and relevant utility/stability state without replaying historical placement sounds, hammer actions, material-delivery events or Chaos shard trajectories;
- UE5.8 generic replicated Actor/property/RPC/relevancy/dormancy architecture is the Blueprint-first baseline;
- Replication Graph/Iris may be evaluated later in Phase 60 under measured large-world profiling without changing construction gameplay truth or becoming an early unverified hard dependency;
- multiplayer construction remains replication-system-agnostic enough to optimize later;
- modified clients cannot spawn permanent Buildables, forge legal placement/support, alter authoritative cost, complete construction, deliver nonexistent resources, increase Work Units, set Health/Destroyed state, relocate/demolish unauthorized structures or forge structural relationships;
- large multiplayer tests must profile server replication CPU, bandwidth, actor counts, dormancy effectiveness, relevancy, packet loss/latency and late-join reconstruction.

### Multiplayer Construction Principle

> Metaworld multiplayer construction sends intent upward and authoritative state outward. The client predicts the experience; the server decides the world. Persistent facts replicate through compact state that late joiners can reconstruct, while RPCs and multicasts are reserved for requests and transient presentation. Settled structures sleep instead of consuming movement, CPU and bandwidth forever.

---

# Current Phase 20 Construction Resource / Multiplayer Flow

`Buildable / Stage Definition`

`-> Local Client Ghost / Catalog / Resource UI`

`-> Client submits Placement / Delivery / Work intent`

`-> Server independently validates authoritative world state`

`-> Server creates/updates persistent Construction Site`

`-> Source Inventory debited atomically when delivering materials`

`-> Site Material / Work / Stage state updated and persisted`

`-> Compact authoritative state replicated to relevant clients`

`-> Clients derive current visuals/UI through state / RepNotify`

`-> Settled structures become dormant`

`-> Meaningful change wakes structure -> replicate -> settle/dormant again`

`-> Late joiners reconstruct current state without historical RPC replay`

---

# Playlist Continuation Rule

Future playlist episodes may continue in this Part 5 file until another safe continuation is needed. Parts 1-5 together remain the canonical playlist intake log until final consolidation into the Master Roadmap and relevant companion documents.
