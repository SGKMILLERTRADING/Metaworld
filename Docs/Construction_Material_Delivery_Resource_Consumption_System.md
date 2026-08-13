# Metaworld — Construction Material Delivery & Resource Consumption System

**Status:** Canonical / Approved Phase 20 Upgrade

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first

## Canonical Principle

Metaworld construction consumes real authoritative resources. A construction site can show exactly what materials are required, what has already been delivered, what remains available on-site, what has been consumed by completed work, and what is still missing before the next stage can advance.

Core rule:

> Materials are delivered and consumed through server-authoritative inventory transactions; labor and materials are separate construction requirements, and neither can counterfeit the other.

The UE4 tutorial concepts of storing item requirements per buildable, showing those requirements in UI, checking player inventory/backpack, consuming required items and preventing completion until materials exist are approved. Metaworld upgrades them into a persistent staged-delivery system compatible with players, NPCs, warehouses, suppliers, vehicles, construction companies, multiplayer authority and the existing Construction Progress / Build-To-Completion architecture.

---

# 1. Integration with Construction Progress

This is not a second construction system.

It extends:

`Docs/Construction_Progress_Build_To_Completion_System.md`

Canonical flow:

`Placement Approved`
-> persistent Construction Site created
-> stage recipe resolved
-> materials delivered/reserved
-> server accepts valid delivery transaction
-> stage becomes ready for eligible work
-> qualified labor contributes Construction Work Units
-> materials are consumed according to stage policy
-> stage completes
-> next stage recipe becomes active
-> final completion only after all required stage conditions pass

A buildable cannot become complete merely because a client says the required items were present.

---

# 2. Data-Driven Material Requirements

Do not store a loose array of arbitrary inventory slots as the only recipe truth.

Recommended recipe entry:

`S_MW_ConstructionMaterialRequirement`

Possible fields:

- `RequirementID`
- `StageID`
- `ItemDefinitionID`
- `RequiredQuantity`
- `DeliveredQuantity`
- `ConsumedQuantity`
- `MinimumQuality` where relevant
- `AllowedSubstitutionTags[]` where deliberately supported
- `ConsumptionPolicy`
- `Refund/SalvagePolicy`
- `IsOptional`
- `RequirementGroupID` for alternatives where supported

The authoritative Buildable / Construction Stage definition owns required quantities and compatibility. Client UI never defines the recipe.

---

# 3. Delivered vs Consumed vs Missing

Metaworld distinguishes material states.

Example:

`Structural Wall — Frame Stage`

- Required Wood: 20
- Delivered Wood: 12
- Consumed Wood: 8
- Available On-Site Wood: 4
- Missing Wood: 8
- Required Work Units: 40
- Completed Work Units: 25

Conceptual formulas:

`AvailableOnSite = Delivered - Consumed`

`Missing = max(Required - Delivered, 0)`

A project can therefore receive materials before labor begins without pretending those materials have already become part of the structure.

---

# 4. Labor and Materials Are Separate

Canonical rule:

- delivering materials does not automatically add Construction Work Units;
- performing labor without required stage materials does not magically create materials;
- a stage may require both material readiness and qualified work before completion;
- some simple installation stages can deliberately consume a component and complete quickly if their definition says so.

Example:

`20 Wood delivered`
+ `0 / 40 Work Units`
= materials ready, wall not built.

`40 / 40 Work Units attempted`
+ `12 / 20 Wood delivered`
= stage blocked at its configured material/work relationship rather than granting a free wall.

---

# 5. Partial Delivery

Players do not need to carry an entire skyscraper's materials in one inventory transaction.

Construction sites can accept partial deliveries when their recipe allows it.

Example:

Required:

- 100 Lumber
- 40 Steel
- 20 Concrete Bags

Deliveries:

- Player A delivers 30 Lumber
- NPC supplier delivers 50 Lumber
- Truck shipment delivers remaining 20 Lumber + 20 Steel
- Later shipment delivers remaining Steel/Concrete

The site persists cumulative authoritative delivery state.

This supports real logistics, warehouses, delivery jobs, suppliers and construction companies.

---

# 6. Approved Inventory Sources

A material delivery action can use one or more authorized source inventories according to world rules.

Possible sources:

- player carried inventory;
- equipped backpack/container inventory;
- authorized vehicle cargo;
- nearby construction delivery pallet/container;
- property storage;
- construction company warehouse;
- supplier shipment;
- NPC worker/company inventory;
- contract-reserved inventory.

Do not silently drain arbitrary nearby containers.

The UI must show which source is being used or allow the player to select an authorized source when multiple are available.

Source priority is data/UI policy, not a hidden hardcoded assumption.

---

# 7. Server-Authoritative Delivery Transaction

Recommended request:

`RequestDeliverConstructionMaterials(SiteID, RequirementID/ItemID, RequestedQuantity, SourceInventoryID)`

Server validates:

- Construction Site exists;
- site/stage recipe requires or accepts the Item ID;
- source inventory exists;
- actor has permission to access source inventory;
- actor has permission to contribute to the site;
- source contains sufficient authoritative quantity;
- item quality/substitution rules pass;
- requested quantity does not exceed allowed remaining requirement unless over-delivery is explicitly allowed;
- item is not reserved/locked by another transaction;
- range/access/logistics rules pass where relevant;
- stage/site has not been cancelled, completed, relocated or invalidated.

Atomic commit:

1. lock/validate source + site transaction;
2. debit source inventory;
3. credit site delivered-material state;
4. update any reservation/contract ledger;
5. persist both sides;
6. replicate compact result;
7. release transaction lock.

If the transaction fails, neither inventory nor site delivery state changes.

---

# 8. Consumption Policy

Delivered does not always mean immediately consumed.

Possible stage policies:

## Consume On Delivery

Suitable only when the material is immediately committed/installed and cannot reasonably be recovered as site stock.

## Consume On Work Progress

Materials are consumed proportionally or at defined work milestones.

Example:

- framing work consumes lumber as Work Units advance.

## Consume On Stage Milestone

A batch is consumed when a defined substage/milestone completes.

## Consume On Stage Completion

Useful for simple components when delivered inventory must remain refundable until the stage actually commits.

The policy is authoritative and chosen per stage/requirement.

---

# 9. Cancellation, Refund & Salvage Safety

The existing demolition/cancellation rules remain canonical.

Material accounting must distinguish:

- undelivered requirements;
- delivered but unconsumed site stock;
- consumed/installed materials;
- damaged/lost/stolen materials;
- salvageable materials.

Cancellation cannot duplicate resources.

Core invariant:

> Returned + salvaged material can never exceed legitimate remaining/unconsumed/installed material according to the authoritative recipe and damage state.

Unconsumed delivered stock may often be returned to an authorized destination.

Consumed materials use salvage/demolition rules rather than receiving a magical full refund.

---

# 10. Construction Site Material Storage

A construction site can have a logical site-material ledger without spawning one Actor for every board, brick or nail.

Persistent site state can include:

- `RequirementID`
- `ItemDefinitionID`
- `DeliveredQuantity`
- `ConsumedQuantity`
- `ReservedQuantity`
- `Lost/DamagedQuantity`
- `Source/Delivery references` where audit/history is useful.

High-value or gameplay-relevant deliveries may have physical pallets/crates/vehicles, while bulk quantities can remain compact persistent data after valid delivery.

This prevents material simulation from becoming an Actor-count problem.

---

# 11. Theft / Site Security

Where world rules allow exposed construction resources to be stolen, theft operates through authoritative inventory/site-material transactions.

Possible rules:

- only unconsumed physical/site-stock material is theft-eligible;
- consumed structural material is not equivalent to loose inventory;
- theft may require access to a physical crate/pallet/storage point;
- stolen amounts decrement site stock authoritatively;
- missing materials can pause work;
- theft can create crime/evidence/security events.

The client cannot manufacture loose resources by interacting with a construction visual.

---

# 12. Resource HUD / Construction UI

The tutorial's dynamic resource list is approved.

Construction UI can show per requirement:

- item icon/name;
- required quantity;
- delivered quantity;
- consumed quantity where useful;
- remaining/missing quantity;
- player/source currently available quantity;
- valid substitution/quality warning;
- stage readiness;
- blocked reason.

Example:

`Frame — Materials`

- Wood: `12 / 20 delivered` — `8 missing`
- Nails: `30 / 30 delivered`
- Steel Brackets: `4 / 6 delivered` — `2 missing`

`Work: 25 / 40`

`Status: Missing 8 Wood, 2 Steel Brackets`

Controller navigation must work without mouse dependence.

---

# 13. No Permanent 0.1-Second Interaction Trace

The tutorial's repeating `0.1s` line trace is rejected as a universal permanent architecture.

Metaworld already has a shared interaction system.

Preferred UI refresh triggers:

- interaction target changes;
- Build/Construction management mode opens/closes;
- relevant site stage changes;
- material delivery/consumption changes;
- relevant source inventory changes;
- permission/blocked state changes.

`BPC_MW_Interaction` can perform targeted acquisition while interaction targeting is relevant, but the construction resource widget does not need its own independent forever-running trace timer.

No world-wide Tick or per-site polling is required.

---

# 14. Interaction Flow

Recommended player flow:

`Player targets Construction Site`
-> shared interaction system identifies `Construction.Site`
-> UI receives Site ID + public/authorized construction summary
-> resource list generated from authoritative Stage Definition + replicated site state
-> player chooses `Deliver Materials` / `Build` / other valid action
-> server validates action
-> site state updates
-> UI refreshes from new authoritative state

A Window, Wall, Foundation or Prefab does not need a unique copy of the inventory-consumption graph if the common construction-site/component architecture can resolve its recipe.

---

# 15. Inventory Integration

Construction does not duplicate the inventory system.

It consumes inventory through an inventory transaction contract/service.

Required inventory capabilities include conceptually:

- query quantity by stable ItemDefinitionID/tags;
- validate ownership/access;
- reserve quantity during transaction when required;
- remove exact quantity atomically;
- report transaction success/failure;
- persist source inventory;
- prevent double-spend/race conditions.

Build Master/Construction Site should not directly manipulate arbitrary raw arrays in unrelated Player/Backpack Blueprints.

---

# 16. Multiplayer / Concurrent Builders

Multiple players/NPCs can contribute to the same authorized site.

Example:

- Player A delivers 5 Wood;
- Player B simultaneously attempts to deliver 10 Wood;
- only the server decides final accepted quantities based on the latest remaining requirement;
- transaction locks/version checks prevent both clients from over-crediting the site.

The client cannot:

- fake inventory quantity;
- submit a negative quantity;
- use another player's private inventory;
- claim materials were delivered without server debit;
- reuse the same stack in two simultaneous deliveries;
- substitute an invalid Item ID;
- change the site's required recipe;
- mark material requirements complete directly.

---

# 17. NPC / Supplier / Company Integration

NPC Builders and companies use the same authoritative material requirement model.

This supports jobs/contracts such as:

- purchase 100 Lumber;
- collect materials from warehouse;
- load delivery vehicle;
- deliver to Construction Site;
- verify delivery;
- continue stage labor when materials are ready.

Distant/offline logistics can use persistent scheduled transactions only when a legitimate supplier/company/vehicle/resource source exists.

Materials do not appear at the site merely because an NPC was assigned.

---

# 18. Large Projects / Stage Recipes

Large projects use stage-scoped recipes rather than requiring every future material on day one.

Example apartment:

## Foundation Stage

- Concrete
- Rebar
- Forms

## Structural Frame

- Steel
- Fasteners
- Concrete

## Exterior

- Wall materials
- Glass
- Doors

## Utilities

- Cable
- Pipe
- panels/fixtures

## Finish

- flooring
- paint/finish materials
- installed components

This makes logistics and economic milestones understandable and keeps site state manageable.

---

# 19. Installed Components vs Bulk Materials

Some requirements represent ordinary quantity resources:

- lumber;
- concrete;
- fasteners.

Others can represent persistent installed objects:

- door;
- window;
- generator;
- breaker panel;
- HVAC equipment;
- security device.

Installed objects should preserve their own stable Object IDs/condition/security/customization state when the construction stage consumes/installs the specific item where world rules require it.

Do not reduce every persistent object to an anonymous quantity count.

---

# 20. Persistence

Persist appropriate construction-resource state:

- Construction Site ID;
- Stage ID;
- Requirement IDs;
- required quantity;
- delivered quantity;
- consumed quantity;
- lost/damaged quantity;
- reservation/transaction state where needed;
- material-delivery history where economically/audit relevant;
- installed Object IDs for persistent components;
- contract/supplier milestone references where relevant.

Save/load/reconnect must not duplicate or reset delivered materials.

---

# 21. Performance

- no permanent resource-check Tick on construction sites;
- no independent `0.1s` HUD trace loop per player solely for build resources;
- UI refresh is event/context driven;
- inventory queries happen on relevant interaction/transaction events;
- large material quantities are compact data, not one Actor per unit;
- replicate deltas/compact quantities, not full inventory/site data every frame;
- use soft references for item presentation assets where appropriate;
- distant sites do not poll player inventories;
- scheduled NPC logistics use timestamps/jobs rather than persistent full simulation.

---

# 22. Controller Support

All construction material management must support:

- keyboard/mouse;
- Xbox-style controllers;
- PlayStation-style controllers.

Controller users must be able to:

- inspect required resources;
- change/select authorized source inventory where exposed;
- deliver all/partial quantities;
- understand missing items;
- cancel/return;
- switch between material and labor/site views.

No mandatory mouse-hover-only information.

---

# 23. Python Editor / Health-Check Integration

Editor tooling can audit:

- stages with missing recipes;
- zero/negative required quantities;
- invalid ItemDefinition IDs;
- invalid substitution groups;
- recipes referencing deleted items;
- installed-object requirements incorrectly treated as bulk consumables;
- impossible stage material/work combinations;
- UI icon/display references;
- refund/salvage policy gaps;
- direct legacy raw-inventory mutation inside buildable children;
- resource widgets with independent permanent polling logic.

Integrate these checks into the future `MW Construction Health Check` where practical.

---

# 24. Initial Tests

1. Construction Site displays correct current-stage recipe.
2. UI shows required/delivered/missing quantities.
3. Player with no required material cannot fake delivery.
4. Player with partial quantity can make a valid partial delivery.
5. Server removes exactly the accepted quantity from source inventory.
6. Site receives exactly the same accepted quantity.
7. Failed transaction changes neither side.
8. Concurrent deliveries cannot over-credit the remaining requirement.
9. Player cannot use another player's unauthorized inventory.
10. Backpack/vehicle/property storage can be used only when authorized by source policy.
11. Delivering all materials alone does not complete labor-requiring stage.
12. Labor cannot pass configured material readiness limits.
13. Work-stage material consumption follows the configured consumption policy.
14. Cancel/refund cannot mint resources.
15. Save/load preserves delivered and consumed quantities.
16. Installed Door/Window component preserves required persistent identity where configured.
17. NPC/company supplier can make the same authoritative delivery transaction.
18. Resource UI updates when target/site/inventory changes without its own permanent 0.1-second polling loop.
19. Keyboard/mouse can inspect/deliver resources.
20. Xbox-style controller can inspect/deliver resources.
21. PlayStation-style controller can inspect/deliver resources.
22. Many idle construction sites create no continuous material-check Tick cost.

---

# Core Rule

> Metaworld construction resources are real economy state. The site knows what its current stage requires; authorized players, NPCs, suppliers and companies deliver legitimate inventory through atomic server transactions; delivered stock and consumed material remain distinct; labor advances separately; UI is contextual and event-driven; no client can finish a structure by faking inventory or resource progress.