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

# Current Phase 20 Construction Resource Flow

`Buildable / Stage Definition`

`-> Required Material Recipe + Required Work Units`

`-> Construction Site created`

`-> Contextual Resource UI`

`-> Player/NPC/Company selects authorized source`

`-> Server validates delivery transaction`

`-> Source Inventory debited atomically`

`-> Site Delivered Material credited/persisted`

`-> Stage material readiness evaluated`

`-> Qualified labor contributes Work Units`

`-> Materials consumed according to stage policy`

`-> Stage completes`

`-> Next Stage / Final Completion`

---

# Playlist Continuation Rule

Future playlist episodes may continue in this Part 5 file until another safe continuation is needed. Parts 1-5 together remain the canonical playlist intake log until final consolidation into the Master Roadmap and relevant companion documents.
