# Metaworld — Smart News Event Selection System

**Status:** Canonical / Approved Cross-System Upgrade

**Runtime Direction:** Blueprint-first / data-driven / server-authoritative Event Ledger

## Canonical Principle

Metaworld News does **not** report every world-state change. The Event Ledger records important factual events, while a separate Smart News selection layer decides which verified events are publicly newsworthy, how far they should travel, and whether they belong in a headline, local bulletin, specialist report, emergency alert, or no public news at all.

Core rule:

> A world event becomes news because of public significance, not merely because something changed.

Examples:

- A player replaces or renovates a wall inside their own private home -> normally **No News**.
- A homeowner repairs a broken window after ordinary wear -> **No News**.
- A small shop repaints one room -> **No News**.
- A hotel closes and rebuilds an entire wing, reducing guest capacity and affecting staff/public access -> normally **Local/City News** and potentially wider coverage if the hotel is important enough.
- A major hotel wing collapses, burns, is attacked, or is evacuated -> **High-priority News / Emergency coverage** according to severity.
- A landmark tower is demolished or rebuilt -> likely **City/Regional/National News** depending on importance.

The Smart News system is deterministic/data-driven at its core and does not require a paid external AI service to decide whether an event is newsworthy.

---

# 1. Event Ledger vs News

The Event Ledger and News are separate layers.

## Event Ledger

The Event Ledger records authoritative facts and significant state transitions for systems that need history, auditability, causation, economy, crime, property, politics, construction, death, disasters and other persistent-world functions.

An Event Ledger record can exist without becoming public news.

## Smart News Selection

The Smart News layer evaluates eligible verified Event Ledger events and decides:

- whether the event is newsworthy at all;
- geographic scope;
- urgency;
- likely audience;
- headline/bulletin priority;
- whether to merge it with an existing developing story;
- whether follow-up coverage is justified;
- what verified facts may safely be published.

Therefore:

`World Event -> Event Ledger -> News Significance Evaluation -> Optional News Story`

not:

`World Event -> Automatic Headline`.

---

# 2. Newsworthiness Factors

A candidate event can be evaluated using data such as:

- `EventType`
- `JurisdictionID`
- `PropertyID / BusinessID / OrganizationID`
- `PublicVisibility`
- `PublicAccessImpact`
- `AffectedPopulationEstimate`
- `EmployeeImpact`
- `Guest/CustomerImpact`
- `EconomicImpact`
- `PublicSafetyImpact`
- `InfrastructureImpact`
- `GovernmentImportance`
- `Election/PoliticalImportance`
- `BusinessImportance`
- `Landmark/CulturalImportance`
- `CrimeSeverity`
- `Casualties / Injuries`
- `Displacement / Evacuation`
- `Traffic/TransitImpact`
- `UtilityImpact`
- `EnvironmentalImpact`
- `ScaleOfConstructionOrDestruction`
- `DurationEstimate`
- `Rarity / Novelty`
- `OngoingStoryID`
- `VerificationConfidence`
- `PublicKnowledgeState`
- `Source/ReporterAvailability` where gameplay requires it

No single field automatically determines the result except explicit emergency/public-safety overrides.

---

# 3. Suggested Coverage Tiers

## Tier 0 — Private / No News

Typical examples:

- private homeowner moves furniture;
- private wall replacement;
- ordinary interior renovation;
- routine appliance replacement;
- small repair job;
- normal construction progress with no public impact;
- ordinary private demolition inside legal property rules.

The event may still exist in property/construction history without entering News.

## Tier 1 — Neighborhood / Local Bulletin

Examples:

- temporary street obstruction from construction;
- local business closes briefly for renovation;
- small community facility changes operating hours;
- repeated utility problem affecting one block;
- neighborhood event, local crime, or small public project.

## Tier 2 — City News

Examples:

- hotel wing reconstruction affecting many guests/employees;
- major business closure/opening;
- large apartment evacuation;
- important road/bridge closure;
- major local criminal event;
- large fire;
- public building renovation or demolition;
- significant zoning/public-development decision.

## Tier 3 — Regional / National News

Examples:

- major infrastructure failure;
- famous landmark destruction/rebuild;
- regional disaster;
- major corporation failure or expansion;
- governor/president-level political event;
- large conflict or mass-casualty event;
- major economic shock.

## Tier 4 — World / Breaking News

Examples:

- war declaration or major battle;
- national leadership crisis;
- catastrophic disaster;
- event affecting multiple regions/countries;
- historic supernatural/world event if publicly verified.

## Emergency Alert Override

Some events bypass ordinary editorial thresholds because immediate public safety matters:

- active attack;
- evacuation order;
- severe weather emergency;
- major fire;
- dangerous utility failure;
- public-health/safety threat;
- imminent structural collapse affecting public space.

Emergency alerts are not entertainment headlines and use their own authority/jurisdiction rules.

---

# 4. Construction / Property News Examples

Construction actions should generate Event Ledger/news candidates only when their scale or public effect justifies it.

### Private house wall change

`Owner replaces one wall in private home`

Normally:

- property/construction record updated;
- permits/Builder work recorded where required;
- **News Tier 0**.

### Hotel changes one guest-room wall

Normally:

- ordinary maintenance/renovation;
- **News Tier 0** unless unusual circumstances exist.

### Hotel rebuilds an entire wing

Possible significance inputs:

- 80 rooms unavailable;
- 25 employees reassigned;
- public entrance/parking changed;
- construction permit issued;
- street/loading activity affected;
- renovation lasts several weeks;
- important local hotel/business.

Likely result:

- **Tier 1 or Tier 2**, depending on city/business importance and impact.

Possible verified story:

`Grand Harbor Hotel begins reconstruction of east wing; 80 rooms temporarily unavailable.`

The News system should not expose private ownership/account data that ordinary citizens would not know.

### Hotel wing collapses

Additional factors:

- injuries/deaths;
- evacuation;
- road closure;
- police/fire response;
- suspected crime or structural failure;
- utility shutdown;
- business closure.

Likely result:

- **Tier 2-4** based on severity and reach;
- emergency alert when immediate public safety requires it.

---

# 5. Smart Significance Score

Metaworld may use a weighted significance score as one implementation tool, but the weights are data-driven and jurisdiction/outlet-specific.

Conceptual inputs:

`SignificanceScore =`

- public impact
- people affected
- safety severity
- economic impact
- political/government importance
- infrastructure impact
- landmark/business importance
- rarity/novelty
- geographic reach
- duration
- verified casualty/damage severity

Possible modifiers:

- famous person/organization/property;
- ongoing crisis;
- repeated pattern;
- current public interest;
- local relevance;
- competing major stories.

The score should **not** become the only rule. Emergency overrides, legal publication restrictions, secrecy/investigation status and verification rules can override numeric ranking.

---

# 6. Geographic Relevance

Not every story should be shown equally everywhere.

A story can carry a scope such as:

- Property
- Neighborhood
- City
- County/Region
- State/Province
- Country
- World

A hotel renovation may matter greatly inside its city but not deserve national television.

A player can therefore encounter different headline mixes depending on:

- current city/region;
- home region;
- subscribed/followed topics later;
- business/profession relevance;
- national/world significance.

Official facts remain consistent even when editorial selection differs by outlet/location.

---

# 7. News Outlet Profiles

Different legitimate outlets can have different coverage priorities without changing verified facts.

Examples:

### General City News

Prioritizes:

- public safety
- government
- major businesses
- traffic/infrastructure
- crime
- community events

### Business News

Prioritizes:

- company openings/closures
- major construction
- employment changes
- market/economic events
- property development

### Sports / Entertainment

Prioritizes relevant events and public figures.

### Emergency Channel

Prioritizes immediate safety only.

The official Event Ledger remains the factual source. Outlet profile changes **selection and framing priority**, not truth.

---

# 8. Story Deduplication & Developing Stories

Metaworld should not create ten headlines for ten small updates to the same event.

Use an `OngoingStoryID` / event-cluster relationship where appropriate.

Example:

`Hotel Wing Reconstruction`

Day 1:
- permit approved
- work begins

Day 3:
- temporary entrance closes

Day 8:
- construction reaches structural stage

These can remain one developing story unless an update materially changes public significance.

A new headline may be justified when:

- casualties occur;
- reopening date changes significantly;
- criminal evidence emerges;
- public closure expands;
- government action occurs;
- project completes/reopens;
- major cost/employment impact becomes public.

This prevents news spam.

---

# 9. Cooldowns / Editorial Budget

Each outlet/region can maintain an editorial capacity/priority queue so low-importance stories do not bury major events.

Rules can include:

- maximum low-priority headlines per period;
- duplicate-topic cooldown;
- higher-priority event preemption;
- follow-up threshold;
- emergency-alert bypass;
- old low-priority candidates expiring if no longer relevant.

This is event/timestamp driven, not a permanent Tick over every world object.

---

# 10. Server Truth vs Public Knowledge

Canonical security/evidence rule remains:

`SERVER TRUTH != IN-WORLD KNOWLEDGE`.

The Event Ledger/server may know:

- who actually caused an explosion;
- who owns an anonymous account;
- exact hidden criminal participants;
- secret evidence;
- private property details.

Official News may publish only facts that the world has legitimately verified or that an authorized public institution has released.

Example:

Server truth:

`Player X secretly bombed Hotel Wing A.`

Publicly verified news at first:

`Explosion damages east wing of Grand Harbor Hotel; cause under investigation.`

Later, if police/court evidence establishes identity:

`Authorities identify suspect in Grand Harbor Hotel bombing.`

The news generator must never leak hidden server truth merely because the backend knows it.

---

# 11. Rumor / Player Journalism / Opinion

Official verified News must remain distinct from:

- rumors;
- player social posts;
- opinion shows;
- advertisements;
- entertainment;
- propaganda;
- unverified journalism.

These systems may exist, but their trust/provenance labels must be clear.

The Smart News selector described here governs official verified news unless another outlet explicitly uses a different provenance model.

---

# 12. Data Model

Suggested candidate structure:

`S_MW_NewsCandidate`

Possible fields:

- `CandidateID`
- `EventLedgerID`
- `EventType`
- `JurisdictionID`
- `GeographicScope`
- `SubjectEntityIDs[]`
- `PublicImpactScore`
- `SafetyImpactScore`
- `EconomicImpactScore`
- `GovernmentImpactScore`
- `InfrastructureImpactScore`
- `Cultural/LandmarkScore`
- `AffectedPopulationEstimate`
- `DurationEstimate`
- `RarityScore`
- `VerificationState`
- `PublicKnowledgeState`
- `EmergencyAlertEligible`
- `OngoingStoryID`
- `SuggestedCoverageTier`
- `NewsEligibilityState`
- `SuppressionReason`
- `Timestamp`

Suggested result states:

- `NotNewsworthy`
- `LocalBulletin`
- `CityNews`
- `RegionalNews`
- `NationalNews`
- `WorldNews`
- `EmergencyAlert`
- `HoldForVerification`
- `MergeIntoExistingStory`

---

# 13. Blueprint / System Architecture

Recommended flow:

`Persistent World System`
-> significant state transition
-> Event Ledger record
-> News Candidate builder
-> Smart Significance evaluator
-> verification/public-knowledge filter
-> deduplication / ongoing-story merge
-> jurisdiction/outlet priority queue
-> publish verified story/bulletin/alert if threshold passes

The selector should be centralized/data-driven rather than every Wall, Hotel, Police Actor, Business Actor or Mayor Blueprint deciding for itself whether something is news.

Buildables may emit structured event facts; they do not write headlines directly.

---

# 14. AI / Generated Writing Guardrail

If Metaworld later uses an AI model or template generator to write natural-language articles, the model receives a **restricted verified fact packet** after Smart News selection.

It may:

- turn verified facts into readable prose;
- choose approved headline styles;
- summarize a developing story.

It may not:

- invent casualties;
- identify unverified suspects;
- expose private account identity;
- invent quotes;
- fabricate causes;
- change Event Ledger facts.

A deterministic/template news writer must remain available so official News does not require a paid AI service to function.

---

# 15. Performance

Smart News is event-driven.

Rules:

- no world-wide Tick asking whether every object is newsworthy;
- only meaningful Event Ledger events enter the candidate pipeline;
- scoring happens once per candidate or meaningful update;
- story clusters/cooldowns prevent repeated processing;
- outlets query ranked published stories rather than scanning world state;
- old/archive stories persist as compact data;
- emergency events can bypass ordinary batching where necessary.

---

# 16. Initial Tests

1. Private homeowner replaces one wall -> no News.
2. Private homeowner demolishes and rebuilds one legal interior room -> no News by default.
3. Hotel replaces one guest-room wall -> no News by default.
4. Hotel closes/rebuilds an entire wing affecting many rooms/employees -> local/city News candidate.
5. Famous landmark hotel rebuilds a wing -> may rank higher than an unknown small hotel under the same physical work.
6. Hotel-wing collapse with evacuation -> city/regional news and emergency alert where appropriate.
7. Small business routine repair does not bury major city stories.
8. Repeated construction progress on one hotel wing merges into one developing story.
9. New major casualty update can create a new headline on the same ongoing story.
10. Secret perpetrator known only to server is not named publicly.
11. Police later verify/release suspect identity -> follow-up story may name suspect according to world/legal rules.
12. Local event appears primarily in the relevant city while national/world stories travel farther.
13. Emergency warning preempts low-priority business news.
14. No paid AI service is required for significance selection or factual story generation.
15. News selection creates no permanent per-object Tick cost.

---

# Core Rule

> Metaworld News should feel like a living society making editorial choices, not a debug log printed on television. Ordinary private changes stay private; events become news when their verified public impact, scale, safety, economic, political, cultural or historical significance makes them worth telling the world about.
