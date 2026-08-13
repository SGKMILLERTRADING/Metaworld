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

# Playlist Continuation Rule

Future playlist episodes may continue in this Part 4 file until another safe continuation is needed. Parts 1-4 together remain the canonical playlist intake log until final consolidation into the Master Roadmap and relevant system companions.
