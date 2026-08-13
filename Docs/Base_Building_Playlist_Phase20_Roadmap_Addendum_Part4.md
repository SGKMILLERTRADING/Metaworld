# Metaworld — Base-Building Playlist Phase 20 Roadmap Addendum — Part 4

**Status:** Canonical / Approved Playlist Intake Log Continuation

**Continues:** `Docs/Base_Building_Playlist_Phase20_Roadmap_Addendum_Part3.md`

**Base Master Roadmap:** `Docs/Master_Development_Roadmap.md` v2.9

**Purpose:** Continue recording approved tutorial-playlist intake without repeatedly replacing the increasingly large earlier addenda. Parts 1-4 are equally canonical intake material until final consolidation into the Master Roadmap.

## Permanent Rules Carried Forward

All permanent rules from Parts 1-3 remain active, including:

- Blueprint-first runtime architecture.
- `BP_MW_Buildable_Master` owns only common persistent buildable lifecycle; capabilities remain interface/component/data driven.
- stable Buildable/Family/Variant IDs and server-authoritative persistent world state.
- typed persistent structural relationships replace one generic child Actor array.
- parent failure resolves according to relationship type, alternate support and failure policy rather than synthetic massive damage.
- Chaos/Geometry Collection fracture hierarchy remains separate from Metaworld's cross-buildable relationship graph.
- Event Ledger facts and public News are separate layers; server truth must not automatically leak into public in-world knowledge.
- stable frame time takes priority over spectacle or excessive simulation.
- Metaworld is **not** being migrated to another Unreal project; migration-focused playlist episodes are mined for dependency, QA, recovery and architecture lessons only.

---

# Playlist Intake Status — Continued

## Episode 18 — Parent-Child Destruction Confirmation + Smart News Significance

**Classification:**

- **Hierarchical destruction portion:** LOCKED / DUPLICATE of Episode 17 — no new destruction architecture required.
- **Smart News selection:** UPGRADE — APPROVED.

### Destruction Tutorial Intake

The tutorial repeats the same useful goal already approved in Episode 17: destroying a supporting/parent structure must not leave impossible floating or orphaned attached buildables.

Retained intent:

- register relationships when objects are placed/installed;
- know which structures/attachments depend on which other structures;
- resolve dependents when a parent is destroyed;
- prevent floating doors/windows/walls and other orphaned objects.

No new system is created for:

- `BuildChildren[]` as the authoritative model;
- `Add Build Child` as the only relationship contract;
- `ForEach Child -> Deal Massive Damage`;
- arbitrary Blueprint `Delay` as ordering/correctness;
- `Avoid Adding as Child` as a universal foundation exception.

Episode 17 remains canonical:

- `S_MW_StructureRelationship` / typed relationship records;
- stable Parent/Child Structure IDs;
- `Structure.Support`, installed attachment, surface attachment, snap occupancy, utility, containment and module/group relationship types;
- alternate-support reevaluation;
- failure policies such as ReevaluateSupport, DestroyWithParent, Detach, Drop, Salvage, DisconnectUtility, PreserveIfAlternateSupport and BlockRemoval;
- deterministic server relationship-resolution queue/transaction;
- persistent relationships independent of Actor streaming;
- no universal child-damage cascade.

Detailed destruction companion remains:

`Docs/Structural_Relationship_Hierarchical_Destruction_System.md`

---

# Smart News Significance Upgrade

The user-established rule is canonical:

> Not every world change becomes News. A player changing a wall in their own private home normally does not make the news, while a hotel rebuilding an entire wing can be news because of its public, business, employment, access, safety and community impact.

Detailed companion:

`Docs/Smart_News_Event_Selection_System.md`

Approved:

- official Metaworld News continues to use verified Event Ledger facts as its factual source
- Event Ledger recording does **not** mean automatic headline publication
- a separate Smart News significance layer evaluates whether an event deserves no news, local bulletin, city news, regional/national/world coverage, emergency alert, hold-for-verification or merge-into-existing-story treatment
- newsworthiness is based on public significance rather than mere world-state change
- private homeowner wall changes, ordinary interior renovations, furniture movement, routine repairs and normal small maintenance are normally `Tier 0 / No News`
- a hotel changing one ordinary guest-room wall is normally still `No News`
- a hotel rebuilding an entire wing can qualify for local/city news when it materially affects room capacity, guests, employees, public access, permits, local traffic/business activity or operating duration
- a famous/landmark hotel may receive wider coverage than a small unknown hotel for the same physical work because cultural/business significance differs
- a hotel-wing collapse, fire, attack or evacuation can escalate to high-priority news/emergency coverage according to verified safety impact, casualties, displacement and geographic reach
- construction/destruction systems emit structured Event Ledger facts; individual Wall/Hotel/Business Blueprints do not directly write their own headlines
- suggested significance inputs include public access impact, affected population, employee/customer impact, economic impact, public safety, infrastructure, government/political importance, business importance, cultural/landmark importance, crime severity, casualties, displacement, traffic/transit impact, utilities, event scale, duration, rarity/novelty, geographic scope and verification state
- numeric significance scoring is allowed as one tool but is not the only authority; emergency overrides, verification, secrecy/investigation status and publication restrictions can override scores
- geographic relevance controls distribution: neighborhood, city, region, country or world
- different legitimate outlets may have different topic priorities while sharing the same verified facts
- emergency alerts remain separate from entertainment/editorial headline priority
- duplicate/progress events can merge under an `OngoingStoryID` so one hotel renovation does not generate a new headline for every construction stage
- follow-up headlines require meaningful new significance such as casualty changes, reopening delays, criminal findings, government action, expanded closure or final reopening
- editorial priority queues/cooldowns prevent low-importance stories from burying major events
- low-priority candidates can expire without publication
- `SERVER TRUTH != IN-WORLD KNOWLEDGE` remains mandatory for News
- the backend knowing a hidden perpetrator does not authorize News to name that person before police/court/public verification
- official News can initially say `cause under investigation` and later publish a verified suspect update when legitimate in-world evidence/public release supports it
- official verified News remains distinguishable from rumor, player journalism, opinion, advertisements, entertainment and propaganda
- a data structure such as `S_MW_NewsCandidate` can carry EventLedgerID, event type, jurisdiction, geographic scope, subject entities, significance sub-scores, affected population, verification/public-knowledge state, emergency eligibility, OngoingStoryID, suggested tier and suppression reason
- Smart News selection is event-driven, not a Tick over every object in the world
- no paid external AI service is required for significance selection or factual publication; deterministic/templates remain the baseline
- if AI-written articles are later used, the writer receives only a restricted verified fact packet and may not invent casualties, suspects, causes, quotes or private account identity
- news archives remain persistent world history while publication selection prevents the live feed from becoming a debug log

---

# Smart News Example Matrix

| Event | Default Result |
|---|---|
| Player changes one wall inside own private house | No News |
| Player legally renovates one private bedroom | No News |
| Small shop repairs one damaged wall | No News |
| Hotel changes one guest-room wall | No News |
| Hotel closes/rebuilds an entire wing | Local/City News candidate |
| Landmark hotel closes major wing for long reconstruction | City/Regional candidate |
| Hotel wing collapses with evacuation | Breaking City/Regional News + possible Emergency Alert |
| Hotel attack with casualties | High-priority News; scope based on severity/reach |
| Major bridge/road/public building reconstruction | City/Regional/National depending impact |
| Private structure change with no public effect | Suppressed from News |

---

# Smart News Principle

> Metaworld News is a living society's editorial layer, not a dump of every server event. Private ordinary changes stay private; verified events rise into news when their public impact, scale, safety, economy, politics, culture, crime or historical importance makes them worth reporting.

---

## Episode 19 — Project Migration Tutorial / Construction Dependency Health Check

**Classification:** RESEARCH / TOOLING UPGRADE — APPROVED.

**Explicit scope:** Metaworld is **not being migrated** to another project. This episode is included because it is part of the playlist and exposes useful hidden-dependency failure modes.

Detailed companion:

`Docs/Construction_System_Dependency_Health_Check_Standard.md`

Approved lessons:

- construction dependencies must be explicit, versioned, documented and auditable rather than remembered as manual editor setup
- plugin/engine-feature requirements belong in a dependency manifest and health-check workflow
- tutorial APEX Destruction dependency is not adopted for new Metaworld content; Episode 16's Chaos/Geometry Collection direction remains canonical
- project-level collision/query settings must be reproducible and validated; Metaworld does not return to one global trace channel per Foundation/Wall/Door/Window/Floor family
- canonical small general Build Placement/Obstruction and Snap/Acquisition query families remain in force, with semantic compatibility determined through IDs/tags/data
- simple collision, placement footprints, opening/snap query volumes, stage collision and destroyed/breached collision are audited explicitly
- `Refresh All Nodes` is retained as a useful Blueprint recovery/debug step after dependency/signature changes but is not treated as architecture or proof of correctness
- recovery sequence includes dependency repair -> Refresh Nodes -> compile -> inspect warnings -> verify parent/interface contracts -> run construction smoke test
- tutorial character-graph copying is rejected as permanent architecture; `BP_MW_Character_Master` hosts reusable `BPC_MW_BuildComponent` / interaction components and Enhanced Input contexts instead
- input conflicts with inventory/combat are handled through contextual Enhanced Input ownership/priority rather than copied physical-key graphs
- construction health checks verify keyboard/mouse, Xbox-style and PlayStation-style mappings for all required build actions
- HUD/widgets should consume stable construction state through explicit UI contracts/view models/events/interfaces rather than directly binding to fragile internal Character variables
- asset/material/reference audits cover ghost materials, valid/blocked preview, construction-stage presentation, final material restoration, destruction presentation and broken/overly-heavy references
- inheritance/interface audits verify expected `BP_MW_Buildable_Master` parentage, required parent calls, component/interface contracts, absence of duplicate legacy graphs and absence of accidental idle Tick
- stable Buildable/Family/Variant/Prefab/Open/Snap/Relationship IDs are validated; mesh identity alone is never authoritative gameplay identity
- persistence compatibility must be checked after architecture/data changes; a Blueprint compiling does not prove old construction state/saves still restore correctly
- approved Editor-side tooling concept: `MW Construction Health Check`, implemented over time with Python and/or Editor Utility Blueprints
- health-check categories can include plugins/features, Blueprint architecture, data IDs, collision/query profiles, footprints, support samples, openings/snaps, input/controller coverage, UI dependencies, Nanite status, damage/Chaos references, persistence schema and performance warnings
- tooling can flag already-rejected legacy patterns such as APEX for new content, one trace channel per family, Visibility as universal obstruction truth, BuildChildren-only relationships, synthetic child-kill cascades, all structures permanently Movable, hardcoded Q/E/1/right-click input, giant Character graphs, giant Build Master graphs, idle Tick and client-authoritative world state
- maintain a repeatable construction smoke-test map/suite covering build mode, selection, rotation, overlap, terrain support, snapping, upper floors, Door installation/runtime interaction, save/load, relocation, demolition, damage, hierarchical support reevaluation, prefab placement and controller paths
- portability is treated as architecture quality even though the project is not moving: clear boundaries make debugging, engine upgrades, creator requirements and future refactors safer

### Construction Dependency Principle

> Metaworld stays in its project. The lesson from migration tooling is dependency discipline: every construction feature should declare what it needs, validate those requirements automatically where practical, and fail with clear diagnostics instead of hidden editor-state assumptions.

---

# Playlist Continuation Rule

Future playlist episodes may continue in this Part 4 file until another safe continuation is needed. Parts 1-4 together remain the canonical playlist intake log until final consolidation into the Master Roadmap and relevant system companions.
