# Metaworld — Modern RPG UE5 Playlist Intake — Part 1

**Status:** Canonical Playlist Intake Log

**Playlist Engine:** Unreal Engine 5.4 tutorial series

**Metaworld Target Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first

**Purpose:** Evaluate this longer modern-RPG tutorial playlist one episode at a time, preserve useful intent, upgrade outdated/tutorial-specific implementation patterns to Metaworld architecture, and avoid creating duplicate parallel systems.

## Permanent Intake Rules

1. The tutorial series is a research/input source, not a replacement architecture.
2. Metaworld remains Unreal Engine 5.8 Blueprint-first with Python Editor automation only.
3. Existing canonical systems remain in force unless the owner explicitly changes them.
4. Every episode is classified as `LOCKED`, `UPGRADE`, `FUTURE`, `RESEARCH`, `REJECT`, or a combination where appropriate.
5. Tutorial-specific UE5.4 details are upgraded to UE5.8 when implementation details materially differ.
6. Early-series "bad habits" are never copied merely because they appear first. Later tutorial corrections may improve the source series, but Metaworld canon always has priority.
7. Shared behavior belongs in the existing Master Blueprint / Actor Component / Interface / Gameplay Tag / data architecture rather than one-off giant Blueprint graphs.
8. Player-facing systems must support keyboard/mouse, Xbox-style controllers and PlayStation-style controllers through Enhanced Input and controller-navigable UI.
9. Persistent/economy/combat/inventory/world state remains server-authoritative where multiplayer correctness requires it.
10. Performance is designed from feature inception: no unnecessary permanent Tick, broad polling, world-wide scans, heavy hard-reference loading or replicated presentation spam.
11. Nanite is used wherever compatible and beneficial without breaking morphs, animation, materials or gameplay requirements.
12. No paid external service is required for baseline gameplay architecture.
13. New episodes should extend existing roadmap phases whenever possible; create a new major system only when the domain is genuinely missing.
14. At playlist completion, consolidate approved upgrades into the active roadmap/overlays while keeping the intake log as history.

---

# Episode 1 — Modern RPG Series Preview / Scope Map

**Classification:** RESEARCH — SERIES SCOPE MAP.

This episode previews planned tutorial domains but does not yet provide enough implementation detail to approve a new technical architecture for any one system.

## Topics Announced & Current Metaworld Mapping

### Character Creation

Tutorial scope:
- custom character creation.

Metaworld mapping:
- Phase 2 — Full Character Creator;
- Phase 3 — Clothing & Body Fitting;
- existing `Docs/Character_Morph_Customization_System.md` remains canonical.

Playlist use:
- look for useful UI, workflow, morph, data, equipment-fitting and quality-of-life ideas;
- do not replace Metaworld's broad continuous morph/body/face/age identity system with a narrower tutorial creator.

### Inventory / Looting / Trading

Tutorial scope:
- chests;
- corpse looting;
- trading;
- inventory management.

Metaworld mapping:
- Phase 9 — Universal Item DNA;
- Phase 10 — Universal Object Capability System;
- Phase 11 — Inventory & Containers;
- economy/trading/property/ownership systems where applicable.

Playlist use:
- evaluate item-definition architecture, containers, transfers, stack/state handling, UI and interaction flow;
- Metaworld persistent Item IDs, ownership, condition, provenance, theft/crime consequences and server authority remain higher-order requirements.

### Armor Rigging / Equipment Fitting

Tutorial scope:
- rigging armor sets to characters.

Metaworld mapping:
- Phase 3 — Clothing & Body Fitting;
- Phase 4 — Master Animation Architecture;
- morph-driven body fitting and corrective clothing/armor remain mandatory.

Playlist use:
- evaluate useful skeletal/weighting/equipment attachment workflows;
- armor must support Metaworld body morph diversity instead of assuming one fixed body shape.

### Movement & Combat Animation

Tutorial scope:
- custom movement animations;
- combat animations.

Metaworld mapping:
- Phase 1 — Master Third-Person Character;
- Phase 4 — Master Animation Architecture;
- Phase 5 — Interaction Animation Library;
- Phase 35 — Universal Combat.

Playlist use:
- extract useful Animation Blueprint, montage, locomotion/combat transition and responsiveness ideas;
- integrate with Motion Matching/Pose Search, Motion Warping, IK, animation budgeting and the shared master-character architecture rather than creating an isolated tutorial AnimBP stack.

### Character Widgets / RPG UI

Tutorial scope:
- character widgets and UI best practices.

Metaworld mapping:
- Phase 67 — User Interface;
- Phase 68 — Accessibility, Rebinding & Controller Compatibility.

Playlist use:
- evaluate reusable widget architecture, view-model/data flow, list/grid presentation and player feedback;
- no mouse-only critical UI and no widget-owned authoritative gameplay truth.

### Crafting / Item Attributes

Tutorial scope:
- crafting;
- item attributes.

Metaworld mapping:
- Phase 9 — Universal Item DNA;
- Phase 10 — Universal Object Capability System;
- Phase 11 — Inventory & Containers;
- Phase 16 — Profession / qualification integration where crafting requires learned skill, certification, tools or facilities.

Playlist use:
- evaluate recipes, ingredient handling, item-stat data, UI, crafting stations and output generation;
- crafting may not invent resources, bypass ownership/economy rules or duplicate items.

### Leveling / Stats

Tutorial scope:
- leveling;
- character statistics.

Metaworld mapping:
- RESEARCH until the detailed episodes arrive.

Metaworld already distinguishes physical resources, skills/professions, career rank, reputation, wealth, lineage abilities and public authority. A generic tutorial XP/level system will not automatically become one universal Metaworld number.

Playlist use:
- inspect how the tutorial models attributes, progression and derived stats;
- later classify which parts belong in character stats, skills, professions, combat mastery, supernatural progression or another existing system.

### Enemy AI / Combat

Tutorial scope:
- enemy AI combat.

Metaworld mapping:
- Phase 35 — Universal Combat;
- Phase 53 — NPC Intelligence;
- Phase 54 — NPC Population LOD;
- Phase 57 — World Event & Role Duty Director where combat emerges from world events.

Playlist use:
- extract perception, targeting, state/behavior, combat decision and animation ideas;
- AI must use the same world rules/capabilities as players where practical and scale through significance/LOD rather than every NPC running maximum combat logic all the time.

### Level Prototyping / Open World / Dungeons

Tutorial scope:
- level prototyping;
- environment design;
- open-world or dungeon spaces.

Metaworld mapping:
- Phase 50 — World Partition / HLOD;
- Phase 51 — PCG where useful;
- world/property/event systems for authored interiors, underground spaces and special locations.

Playlist use:
- evaluate layout, encounter-space, modular-environment, streaming and dungeon-design techniques;
- Metaworld remains a persistent Earth-based living world. Any dungeon-like content must be integrated into world fiction/locations and persistence rather than automatically becoming a disconnected lobby/instance architecture.

---

# Episode 1 Decision

No new gameplay system is created from this preview alone.

The episode is retained because it defines the playlist's research coverage and tells us which Metaworld systems future videos are likely to touch.

## Playlist Evaluation Flow

For every future episode:

`Tutorial intent`
-> `Compare against current Metaworld canon`
-> `Classify LOCKED / UPGRADE / FUTURE / RESEARCH / REJECT`
-> `Upgrade UE5.4/tutorial patterns to UE5.8 Metaworld architecture`
-> `Update existing companion when domain already exists`
-> `Create new companion only for genuinely missing domain`
-> `Record the episode here or in the next continuation part`

## Episode 1 Principle

> This playlist is a toolbox, not a template. Metaworld will take useful RPG mechanics and implementation lessons while preserving its own persistent-world identity, architecture, authority, performance and player-freedom rules.

---

# Episode 2 — Custom MetaHuman as Playable Character

**Classification:** UPGRADE — APPROVED.

**Phase Ownership:** Phase 1 Master Character + Phase 2 Character Creator + Phase 3 Clothing/Body Fitting + Phase 4 Animation.

Detailed companion:

`Docs/Playable_MetaHuman_Modular_Character_Assembly_Architecture.md`

Existing companions remain canonical:

- `Docs/Character_Morph_Customization_System.md`
- `Docs/Avatar_Communication_Character_Animation_Architecture.md`

## Approved Tutorial Intent

- a high-quality modular MetaHuman can become the playable avatar;
- Body/Face/Torso/Legs/Feet/Hair/clothing components must be correctly assembled/aligned;
- compatible modular skeletal sections can follow a leader/body pose;
- the body animation Blueprint/rig must be compatible with the playable movement system;
- unwanted starter clothing can be hidden/removed during setup.

## Metaworld Upgrades

- UE5.4 manual copy-body-parts workflow is treated as an assembly lesson, not the only UE5.8 path; use UE5.8 MetaHuman Character/Assembly assets where appropriate;
- MetaHuman assets/assembly should match the project's UE5.8 version rather than assuming older assembled assets are final shipping content;
- experimental UE5.8 MetaHuman Collection/Instance/Crowd workflows remain `RESEARCH` until production suitability is proven;
- MetaHuman presentation integrates under `BP_MW_Character_Master`; it does not become a second player-character architecture;
- `BPC_MW_AvatarCustomization`, equipment, inventory, interaction, combat, needs, networking and persistence remain shared master-character systems;
- `Set Leader Pose Component` is approved for compatible follower sections, but not assumed to be the final cheapest solution because each component still carries rendering cost and followers cannot run independent animation/physics;
- Copy Pose/post-process paths may be used where Face or another body part requires independent post-processing/physics;
- runtime Skeletal Mesh Merge is not the default player-avatar solution when it would remove morph targets required by the Metaworld creator;
- tutorial `ABP_Manny` / `ABP_Quinn` becomes the existing `ABP_MW_Master` / retargeted animation contract;
- asset-specific Control Rig/root corrections are content fixes, not universal gameplay rules;
- `Forced LOD = 0` is allowed as a diagnostic but rejected as a global hair-flicker solution; fix groom/LOD/scalability configuration and preserve significance-based character LOD;
- starter clothing visibility eventually comes from the equipment/clothing system, not permanent one-off viewport toggles;
- compact avatar/customization/equipment IDs/parameters persist and replicate; clients assemble presentation from approved data;
- the approved broad body/face/age morph range remains mandatory and is not reduced to fixed MetaHuman presets;
- Nanite is evaluated per compatible body/clothing/accessory part without breaking morph-driven identity.

### Episode 2 Principle

> MetaHuman is a high-quality character technology inside Metaworld. It serves the master-character and customization architecture instead of replacing it.

---

# Episode 3 — Physics-Enabled World Items & Interaction

**Classification:** UPGRADE — APPROVED.

**Phase Ownership:** Phase 9 Item DNA + Phase 10 Object Capabilities + Phase 11 Inventory + Phase 5 Interaction.

Detailed companion:

`Docs/Persistent_Item_Interaction_Inventory_Architecture.md`

## Approved Tutorial Intent

- world items have visible meshes and physical collision;
- item type data is separated from interaction logic;
- common world items can derive behavior from a shared item/interactable base;
- Data Tables/data definitions can drive mesh/name/item properties;
- a Blueprint Interface is appropriate for common interaction communication;
- proximity/query information can help locate interactable items.

## Metaworld Upgrades

- deprecated Quixel Bridge is not a permanent dependency; current UE5.8 content acquisition uses Fab/approved source workflows;
- auto-convex/simple collision is an approved authoring starting point, but collision is reviewed/tuned per object rather than assumed correct automatically;
- canonical world item actor can be `BP_MW_ItemWorldActor` using the existing `BPI_MW_Interactable` contract;
- ordinary item variety comes primarily from stable Item Definitions/data, not one child Blueprint per axe/apple/bottle/etc.;
- tutorial enum of every item name is rejected as scalable identity; use stable `ItemDefinitionID`, tags and data definitions;
- exact persistent copies use `ItemInstanceID` so ownership, condition, quality, theft/evidence state, creator provenance and history survive transfers;
- hardcoded `E` becomes Enhanced Input `IA_Interact` through `BPC_MW_Interaction`;
- proximity Sphere overlap may provide bounded candidates where useful, but it does not become a duplicate interaction system or unlimited Actor array;
- physics simulation is significance-aware: active loose items can simulate, while settled/distant/unloaded items use sleeping/lower-cost/persistent state rather than permanent physics;
- interaction never defines pickup as simply `Destroy Actor`; world Actor removal follows an authoritative successful transfer.

### Episode 3 Principle

> The world Actor is a physical representation of a persistent item, not the item's entire identity.

---

# Episode 4 — Inventory Grid / UI Shell

**Classification:** UPGRADE — APPROVED.

**Phase Ownership:** Phase 11 Inventory & Containers + Phase 67 UI + Phase 68 Controller/Accessibility.

Detailed companion:

`Docs/Persistent_Item_Interaction_Inventory_Architecture.md`

## Approved Tutorial Intent

- inventory can have a visual slot/grid representation;
- inventory size/capacity is data/state rather than hand-placed individual UI boxes;
- UI entries are generated dynamically from inventory/container state;
- an inventory menu can be opened/closed by player input.

## Metaworld Upgrades

- authoritative inventory lives in `BPC_MW_Inventory` / container state, not directly in the Player Character graph or Widget children;
- the same container contract supports player inventory, backpacks, chests, refrigerators, safes, vehicles, warehouses, stores, corpse/death containers and other world storage;
- UI is a view over persistent Item/Container records and never becomes the save source;
- fixed `T` key becomes Enhanced Input with keyboard/mouse, Xbox-style and PlayStation-style mappings;
- required inventory actions have controller focus/navigation/confirm/back alternatives rather than mouse-only drag-and-drop;
- normal persistent multiplayer does not pause the entire world when one player opens inventory;
- inventory widgets refresh from change events/deltas and scalable list/grid presentation rather than rebuilding every slot every frame;
- container capacity can later include slots, weight, volume, dimensions, compartments, permissions and allowed-item rules.

### Episode 4 Principle

> Inventory UI displays container truth; it does not own container truth.

---

# Episode 5 — Pickup, Stacking & Inventory Display

**Classification:** UPGRADE — APPROVED.

**Phase Ownership:** Phase 9 Item DNA + Phase 11 Inventory/Containers + multiplayer/persistence/economy integration.

Detailed companion:

`Docs/Persistent_Item_Interaction_Inventory_Architecture.md`

## Approved Tutorial Intent

- item definitions can contain an icon and maximum stack policy;
- pickup should merge into an existing compatible stack when capacity remains;
- otherwise pickup can create another inventory entry;
- stack quantity is displayed in inventory UI and count text may hide when quantity is one;
- world interaction routes into inventory transfer.

## Metaworld Upgrades

- stack compatibility is authoritative and based on definition plus any state that must remain equivalent;
- `MaxStack` is Item Definition data, not client-trusted UI data;
- items with meaningful different durability, quality, provenance, stolen/evidence state, modifications, expiry/spoilage or creator identity do not blindly merge when doing so would erase world truth;
- pickup request uses stable `ItemInstanceID` + target `ContainerID` and is validated by the server for availability, reach, access, capacity and stack rules;
- successful pickup transaction changes world/container ownership/location first and only then removes/despawns the world Actor representation;
- failed pickup leaves the world item intact;
- direct local array mutation is not authoritative multiplayer inventory;
- inventory/icon/count UI derives from replicated/authorized container data;
- private inventory state is not broadcast wholesale to unrelated clients;
- the same transfer contract later supports loot, theft, drop, storage, trade and corpse inventory.

### Episode 5 Principle

> Pickup is an atomic change of item location/possession, not `destroy Actor + append local array`.

---

# Episode 6 — In-Engine 3D Item Icon Generation

**Classification:** UPGRADE — APPROVED EDITOR TOOLING.

**Phase Ownership:** Phase 9 Item Definition presentation + Phase 67 UI + Python Editor production tooling.

Detailed companion:

`Docs/Item_Icon_Editor_Capture_Pipeline.md`

## Approved Tutorial Intent

- Unreal can generate consistent 3D-rendered item icons using a controlled Scene Capture 2D + Render Target setup;
- camera, light, background/alpha and item pose can be authored inside the project;
- the captured result can become a static UI Texture and be referenced by Item Definition data.

## Metaworld Upgrades

- ordinary runtime inventory uses cached/static icon textures rather than one live SceneCapture2D per inventory slot;
- create an editor helper such as `BP_EU_MW_ItemIconCapture` and data-driven capture profiles for different item categories;
- 256x256 is a valid prototype size, not a permanent universal resolution;
- camera framing should use mesh bounds plus optional category/item overrides so rifles, food, furniture and clothing are all readable;
- texture compression/mip settings are chosen by actual UI use rather than blindly copying one tutorial setting to every icon;
- Python Editor automation can batch-generate/audit icons for large item catalogs;
- dynamic runtime icon capture is reserved for genuinely unique customized item appearances, generated on demand, cached and tightly budgeted if later required;
- icon asset is presentation only; it never defines item identity, quantity, ownership or stack rules.

### Episode 6 Principle

> Generate expensive item presentation in the Editor when possible, cache it, and keep gameplay inventory rendering cheap.

---

# Current Modern RPG Playlist Upgrade Stack

`BP_MW_Character_Master`
-> `UE5.8 modular/MetaHuman avatar assembly when appropriate`
-> `BPC_MW_AvatarCustomization + ABP_MW_Master`

`ItemDefinitionID`
-> `ItemInstanceID`
-> `BP_MW_ItemWorldActor / BPI_MW_Interactable`
-> `Authoritative pickup/transfer`
-> `ContainerID / BPC_MW_Inventory`
-> `Grid/List UI view`
-> `Cached Item Icon`

---

# Playlist Continuation Rule

Future episodes continue in this Part 1 file until another safe continuation is needed. Detailed companions are updated rather than duplicated when later videos refine the same MetaHuman, item, inventory or icon domains.