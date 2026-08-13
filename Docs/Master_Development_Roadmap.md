# Metaworld — Master Development Roadmap v2.7

**Status:** Canonical / Approved

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first

**Editor Automation:** Python

**Rendering Direction:** Nanite-first wherever compatible

**Performance Rule:** Stable frame time first; visual quality second

---

# 1. Vision

Metaworld is a persistent Earth-based life simulation, open-world action RPG, social world, economy, property, business, survival, supernatural, creator, political, law/crime, media, and living-world platform built in Unreal Engine 5.8.

The player fantasy is:

> Own almost anything, do almost anything, and become almost anything — subject to skills, professions, laws, resources, equipment, consequences, relationships, and the physical rules of the world.

Metaworld is always **game first**. Realism exists to create stories, choices, risk, opportunity, community, and fun — not repetitive chores.

---

# 2. Locked Global Rules

1. Metaworld runtime gameplay is Blueprint-first.
2. Python is approved for Unreal Editor automation, validation, asset processing, audits, reports, and production tooling — not packaged gameplay logic.
3. `BP_MW_Character_Master` is the canonical humanoid parent Blueprint.
4. Player, civilian, police, ally, enemy, worker, companion, vampire humanoid form, werewolf humanoid form, and other suitable humanoid children derive from the same master family.
5. Shared gameplay logic is modularized with Blueprint Actor Components, Blueprint Interfaces, Gameplay Tags, Data Assets/Data Tables, Animation Blueprints, and related Blueprint systems rather than one giant Event Graph.
6. Nanite is used wherever Unreal Engine 5.8 supports it and it does not break required gameplay, materials, animation, customization, or platform behavior.
7. Morph-target-dependent customizable body/face meshes are approved non-Nanite exceptions when required.
8. Player identity and gameplay requirements take priority over forcing Nanite.
9. Performance is designed from the beginning. Known severe hitching/lag cannot be deferred with “optimize later.”
10. Full fidelity exists near the player; distant systems use reduced fidelity; unloaded systems use persistent data/timestamps instead of full simulation.
11. A new account begins with exactly **1 food and 1 water** and nothing else.
12. After permanent character death, the same account does **not** receive another new-player food/water package.
13. The account survives permanent death; the character identity/name dies and the player creates a new character identity.
14. Logging out is not magical protection. The persistent world continues.
15. No magical safe zones. Safety comes from people, law, infrastructure, preparation, security, and defense.
16. GrimKoin is the main valuable currency. PromoKoin is easier/common but intentionally limited.
17. Only the official Metaworld VIP Store may sell newly issued GrimKoin for real money.
18. Player gifts only transfer GrimKoin the giver already owns. Gifts never mint currency.
19. Banked GrimKoin cannot be spent directly from the ordinary wallet; it must be withdrawn.
20. Killers/robbers never gain access to another player's bank account. They can only take physical property they can actually reach under world rules.
21. On permanent death, the bank/estate settlement may keep up to 50% of banked GrimKoin. The killer does not receive this banked money.
22. The future option for Metaworld to buy eligible GrimKoin back for real money remains disabled until a separate future legal/compliance phase.
23. Cameras record what they can physically see. A mask hides the face; cameras do not magically reveal hidden names/accounts.
24. The backend may know true actor IDs for technical authority, but in-world police/news only know what legitimate evidence reveals.
25. Supernatural identity does not exempt players from property, jobs, taxes, law, evidence, businesses, death, inheritance, or the rest of the world.
26. Lineage does not automatically determine faction loyalty. Humans, vampires, werewolves, and future lineages can ally, rival, split, govern territory, or go to war dynamically.
27. Player-sold music and video is **AI-generated-only**.
28. A player may publish/sell AI-generated music or video only when they own the output and are permitted to sell/distribute it.
29. The creator owns the original Metaworld media product; each normal sale creates a separate buyer-owned Metaworld media copy/entitlement.
30. Buying a song/video does not make it globally owned. Another player who wants independent playback on their own device must obtain their own copy/entitlement.
31. Shared playback is spatial. People physically present in the same room, house, vehicle, club, bar, theater, drive-in, or other authorized media zone may hear/watch the owner's playback without owning the file themselves.
32. Leaving the media zone ends shared access unless the player has their own legitimate entitlement or another authorized source is playing it.
33. Listening to or watching media does not grant ownership.
34. Official Metaworld News is separate from player AI-generated entertainment media and remains driven by verified Event Ledger facts.
35. Important NPCs have real survival needs. AI-enhanced NPCs do not become exempt from hunger or physical world rules.
36. Player-owned/recruited NPC companions and teams must actually obtain food through household supplies, team rations, wages/purchases, business meals, or other legitimate world systems.
37. Family/household members such as a wife, husband, spouse, partner, or other supported dependents have real needs. A household must maintain food and other necessities.
38. Food is a major recurring economic resource with meaningful cost. It should remain obtainable through work, but supporting a family, employees, guards, or a large team should materially increase living costs.
39. GrimKoin can never be the official XP/rank-up mechanism for police rank, government authority, judicial authority, military/faction command, or other public/community leadership.
40. Public leadership titles such as Mayor, Governor, President, King, Queen, council leader, or other configured civic titles require eligibility plus community/organizational support through votes or another approved collective selection process.
41. Career ranks such as police Captain are earned through service, competence, lawful conduct, reputation, leadership, training, and trust; they are not purchased.
42. Wealth can fund legitimate campaigning, advertising, events, staff, transport, security, and public projects, but the vote/rank system remains separate from wallet balance.
43. Bribery/corruption may exist as risky crime/political gameplay, but it is never a guaranteed `pay GrimKoin -> receive rank` button. Attempts can fail, create evidence, cause scandal, trigger police/court action, remove a candidate from office, or damage reputation.
44. Wealth reputation and public/community trust are separate axes. A character can be rich and hated, poor and respected, or any combination in between.
45. Construction is modular and Blueprint-component-driven. `BPC_MW_BuildComponent` owns build-mode preview/placement flow rather than placing the full construction implementation inside the master character Event Graph.
46. Construction preview is advisory; permanent placement is server-authoritative and must revalidate property rights, profession/permit requirements, resources/payment, collision/structural rules and world restrictions before a structure is created.
47. Build preview updates must be performance-budgeted. Placement traces run only while build mode is active and should use timer/event-driven updates rather than unnecessary unconditional per-frame Blueprint Tick.
48. Buildable pieces are data-driven and identified by stable Buildable IDs. Adding foundations, floors, walls, roofs, stairs, furniture, utilities or future construction pieces should primarily add data/catalog entries rather than new hardcoded selection graphs.
49. Construction supports both quick next/previous cycling and a scalable build-catalog UI. A selected buildable must not depend only on a fragile array index.
50. Build snapping is data-driven through sockets/snap points and compatibility metadata such as Gameplay Tags. Dedicated trace/collision channels may be used as low-level filters where useful, but Metaworld will not require a new global trace channel for every future build category.
51. The client never authoritatively chooses a permanent construction Actor Class, Buildable cost, resource requirement, or `CanBuild` result. Final placement resolves the submitted Buildable ID against server-authoritative data.
52. Xbox-style controllers, PlayStation-style controllers, and keyboard/mouse are first-class control paths. A reasonable player-facing feature is not considered complete if required gameplay can only be completed with keyboard/mouse.
53. Metaworld input is action-driven through Enhanced Input and contextual mapping rather than hardcoding gameplay logic to physical keyboard/controller buttons. Rebinding and controller-friendly UI navigation are required where practical.
54. Construction snapping uses a common Blueprint Interface contract such as `BPI_MW_BuildSnapProvider` so foundations, floors, walls, roofs, utilities and future buildable classes can expose snap points without class-specific cast chains.
55. Snap acquisition may use Query-Only Box Collision or equivalent lightweight volumes, but high-level compatibility comes from stable Snap Point IDs and data/tag rules. Final snapped placement is revalidated by the server using authoritative Buildable, parent Structure and Snap Point data.
56. There is **no Owner/Creator rank in the playable hierarchy**. The real-world creator plays by the same in-world survival, economy, profession, voting, law, death, reputation and rank rules as other players. King/Sovereign Queen is the highest in-world player rank; President is directly below that tier.
57. Every official role/rank has responsibilities that fit the role. Duties should be generated from actual world/community needs rather than repetitive arbitrary chores. Higher rank means greater responsibility and accountability, not free status.
58. Structural buildable families may contain variants. Standard wall, door-opening wall and window-opening wall are approved initial variants of one wall family so they share common placement/snap logic without duplicated Blueprint systems.
59. Door-opening and window-opening walls are real structural variants, not cosmetic mesh swaps. Their collision, opening dimensions, attachment slots, costs, support metadata, damage state and future door/window compatibility may differ.
60. Foundations and floors expose compatible wall-edge snap points through the common snap-provider architecture. All valid wall-family variants can use the same edge snap contract when their data allows it.
61. Preview mesh/variant switching may use movable preview components, but permanent structures are not required to remain Movable merely to support build-menu variant cycling. Final variant state is resolved authoritatively and persisted.
62. A structural door opening is not the door, and a structural window opening is not the window. Doors/windows are separate persistent buildable objects installed into compatible opening/attachment slots.
63. Each opening has stable identity, dimensions, compatibility, occupancy and obstruction metadata. A door/window installation must reference and occupy a real authoritative opening rather than relying only on raw world coordinates.
64. Door/window families are data-driven. Different styles should primarily add definitions/variants, not duplicate whole wall Blueprints.
65. Metaworld does not create a new global trace channel for every door/window/buildable type. A small set of general build/snap/obstruction queries is combined with tags, IDs and attachment-slot metadata.
66. Tutorial collision extents such as setting a Y Box Extent to `1` may be useful tuning examples but are not canonical magic values. Final placement uses opening occupancy, object bounds, obstruction checks, snap/attachment metadata and server collision validation to prevent building inside walls or other structures.
67. Door/window asset alignment is standardized through pivot/orientation/opening metadata. Arbitrary Blueprint rotation/offset fixes are data exceptions, not the normal content pipeline.

---

# 3. Core Player Resources

- Health
- Stamina
- Mana
- Hunger
- Thirst
- Fatigue/Sleep
- Later: temperature, pain, injuries, sickness, infection/status effects where fun and appropriate

Needs create meaningful decisions without turning gameplay into constant meter maintenance.

Food is both a player survival resource and a household/NPC economy pillar. Players who maintain larger families, teams, businesses, events, or security forces must plan and pay for larger food supplies.

---

# 4. Master Development Roadmap

## Phase 0 — Project Architecture & Performance Foundation

- Blueprint-first architecture
- `BP_MW_Character_Master`
- Blueprint Actor Components
- Blueprint Interfaces
- Gameplay Tags
- Data Assets/Data Tables
- persistent IDs
- save/persistence boundaries
- multiplayer authority rules
- naming/folder conventions
- Python Editor tools
- Enhanced Input architecture for keyboard/mouse + Xbox-style + PlayStation-style controllers
- performance budgets
- profiling/stress-test maps
- automated asset validation later
- automated Nanite, animation, creator-content, controller/input, and performance audits later

## Phase 1 — Master Third-Person Character

- third-person locomotion
- optional first-person camera mode
- Enhanced Input
- keyboard/mouse + gamepad movement/look/action mappings
- walking/running/sprinting/jumping/crouching/swimming
- interaction/combat/vehicle/animation hooks
- AI/player control compatibility

**Upgrade:** prone, crawling, climbing, mantling, vaulting, ladders, parkour, injury locomotion, carry/drag characters, accessibility/mobility support where later desired.

## Phase 2 — Full Character Creator

- deep morph-driven face/body customization
- very slim through very heavy/fat
- muscularity
- stomach/chest/waist/hips/shoulders/arms/legs
- controlled height range
- skin tone
- face structure
- hair/facial hair
- eyes
- tattoos/scars/freckles/makeup
- age appearance from young adult through elderly-looking
- age presentation through facial morphs, wrinkles, skin detail, hair greying/thinning, posture/animation options
- full keyboard/mouse and controller navigation/slider editing

## Phase 3 — Clothing & Body Fitting

- clothing follows body morphs
- corrective clothing morphs
- skin hiding beneath clothing
- layering
- hats/shoes/jewelry/accessories
- uniforms/armor/profession clothing

**Upgrade:** wet/dirty/damaged clothing, thermal protection, armor values, fashion/social reputation, faction/business uniforms.

## Phase 4 — Master Animation Architecture

- `ABP_MW_Master`
- Motion Matching / Pose Search
- Linked Animation Layers
- Montages
- Motion Warping
- IK Rig / IK Retargeter
- Full Body IK
- Control Rig
- Sync Groups / Markers
- Animation Notifies
- Animation Budget Allocator
- scalable animation profiles for players/NPCs

Animation families include locomotion, firearms, melee, improvised objects, carrying, vehicles, jobs, social, police, medical, construction, magic, injuries, vampire, and werewolf.

## Phase 5 — Interaction Animation Library

- sitting/lying/sleeping
- doors
- ATM/bank use
- eating/drinking
- cooking
- showers/washing
- phone/computer/TV
- shopping
- tool/work interactions
- lifting/carrying
- Smart Object-compatible interaction points

## Phase 6 — Account vs Character Identity

- permanent Metaworld Account ID
- mortal Character Identity
- character names retire on permanent death
- historical lineage between a user's prior characters remains server-side and is not ordinary public knowledge unless gameplay reveals it

## Phase 7 — Permanent Death

- character identity permanently dies
- no second starter package
- carried physical property may be looted
- physical property stays in world
- bank settlement applies
- estate opens
- businesses continue
- recovery window begins
- friends/guards may defend former property
- enemies/players/NPCs may seize exposed property under world rules
- death becomes Event Ledger/history/news when important

## Phase 8 — Wills, Families & Estates

Locked systems:

1. wills
2. beneficiaries
3. spouses/family
4. business ownership succession
5. inheritance taxes
6. court disputes
7. unclaimed estates
8. bank inheritance claims

Family/household expansion:

- spouse/partner household roles
- shared home/pantry/refrigerator resources
- household food/water budgeting
- household relationship consequences when needs are ignored
- household members may buy food themselves if they have funds/permission, but food must still come from the economy

**Upgrade:** executors, joint ownership, trusts, family businesses, divorces/prenups if wanted, estate auctions, funeral services, cemeteries, memorials, additional dependent/family structures if deliberately designed later.

Inheritance grants legal rights/claims; it does not teleport physically stolen property back to heirs.

## Phase 9 — Universal Item DNA

Persistent item identity:

- Item ID
- definition
- owner
- condition
- material
- mass
- capabilities
- history
- tracking/recovery code
- container/location
- value

## Phase 10 — Universal Object Capability System

Objects expose logical capabilities rather than narrow weapon classes.

Examples: pickup, carry, throw, swing, stab, cut, block, break, push, dig, harvest, ignite, consume, place, climb, repair, craft.

Stone, bottle, pipe, chair, hammer, firearm, tool, debris, etc. can be interpreted contextually.

## Phase 11 — Inventory & Containers

- player inventory
- pockets/backpacks
- boxes/closets/refrigerators
- vehicle storage
- warehouses/stores
- physical safes/containers
- household pantry/refrigerator inventories
- team/base ration storage
- controller-navigable inventory UI

**Upgrade:** weight + volume + dimensions + compartment rules where useful.

## Phase 12 — GrimKoin / PromoKoin Economy

- GrimKoin main purchasing power
- PromoKoin common/limited
- item/vendor eligibility rules
- sources/sinks
- player trading
- tips
- wages
- businesses
- creator sales
- economic reputation
- wealth visibility based on observable behavior rather than hidden wallet-reading
- food and household costs as recurring economic sinks
- public/community authority tracked separately from wealth

## Phase 13 — Banking

- deposits/withdrawals
- banked vs carried GrimKoin
- bank privacy from killers/robbers
- transaction ledger
- physical bank branches/ATMs/tellers/security
- death settlement up to 50%
- surviving balance enters estate

**Upgrade:** business accounts, joint accounts, payroll, transfers, escrow, loans, mortgages, safe-deposit boxes, credit, interest, repossession.

## Phase 14 — VIP GrimKoin Store

- only official Metaworld VIP Store sells newly issued GrimKoin for real money
- purchase provenance ledger
- free players remain viable through work/gameplay
- paid players receive faster purchasing power, not immunity from world rules
- player gifting transfers existing owned GrimKoin only
- purchased wealth does not purchase official career/public rank

## Phase 15 — Jobs

Always maintain legitimate lower-entry GrimKoin earning paths such as cleaning, delivery, loading, farm work, sanitation, courier, construction labor, store/bar/restaurant work, driving, temporary city work, security assistance, and other gigs.

Food costs make employment meaningful, but active players should retain realistic legal routes to earn enough to survive and work upward.

Daily/recurring job duties should be generated from real world demand and active incidents rather than artificial repetitive quotas.

Examples:

- delivery worker gets actual deliveries
- mechanic gets damaged/maintenance vehicles
- farmer gets crop/animal/supply work
- bartender serves active customers/events
- sanitation worker responds to actual city sanitation needs

## Phase 16 — Profession, Career Rank & Role Duty System

Action tiers:

- general
- skilled/learnable
- profession-exclusive
- profession + legal license

Examples: Gunsmith, Builder, Mechanic, Electrician, Plumber, Doctor, Nurse, Lawyer, Judge, Police, Security, Farmer, Driver, Chef, Bartender, DJ, Musician, Journalist, Realtor, Banker, Investigator, Teacher, Engineer, supernatural/magic specialists.

Career rank is distinct from profession qualification.

Structured career promotion can consider:

- service history
- performance
- training/certification
- lawful conduct
- complaints/discipline
- professional reputation
- leadership behavior
- community trust
- supervisor/peer/department vote or appointment where configured

**Locked:** GrimKoin cannot directly purchase rank.

**Role duty rule:** every profession/rank can define a `RoleDutyProfile` containing responsibilities, eligible duty types, jurisdiction, minimum/maximum workload, response priority, escalation rules and reputation consequences. The World Event/Job systems create duties from actual needs.

Examples:

- Police Officer: patrol, respond to calls, traffic, evidence, public assistance.
- Sergeant/Lieutenant/Captain: supervise personnel, assign resources, review incidents, manage emergencies and department problems appropriate to rank.
- Doctor/Nurse: treat real patients and emergencies.
- Builder: construction, repair, inspection and contract work.
- Journalist: investigate/report real events.
- Judge/Lawyer: handle actual cases where their role applies.

**Upgrade:** apprenticeship, certifications, schools, mentors, mastery, professional reputation, licenses/suspension, configurable organization rank trees, role duty templates and dynamic staffing needs.

## Phase 17 — Taxation & City Treasury

Taxable activities can include sales, player businesses, creator products, services, rooms/rent, leases, property, vehicle sales, entertainment, permits, advertising, inheritance, and other configured transactions.

City treasury pays public workers/services such as police, firefighters, emergency response, courts, sanitation, roads, public transit, inspectors, utilities where public, and other municipal employees.

Food supply/emergency reserves may later become a legitimate city budget responsibility during storms, war, famine/shortage, displacement, or disaster.

Public payroll should connect to actual staffed roles and responsibilities rather than decorative titles.

## Phase 18 — Government, Elections, Community Leadership & Leadership Duties

Government features:

- mayor/council
- governors/regions where used
- President where a nation/government supports that title
- King/Queen where a kingdom-style government supports those titles
- city budgets
- tax rates
- public contracts
- elections
- laws
- emergency declarations
- zoning
- licenses
- public spending
- policing priorities

**Playable hierarchy rule:** there is no Owner/Creator in-world rank. King/Sovereign Queen is the highest player-held rank; President is directly beneath the Royal/Sovereign tier, followed by lower civic structures according to jurisdiction.

**Canonical leadership rule:** legitimate top leadership requires eligibility plus community/organizational support. Titles cannot be purchased from a store with GrimKoin.

Possible election flow:

Eligibility
-> candidate registration
-> campaign period
-> debates/events/advertising
-> voting
-> authoritative count/certification
-> office granted
-> term begins

Possible voter groups depend on office and can include eligible player citizens, eligible NPC citizens, organization members, profession members, or another approved electorate.

NPC votes should consider information they can reasonably know: service history, city safety, jobs, taxes, infrastructure, scandals, news, faction/lineage relations, candidate platform, personal relationships, war/security concerns, and economic conditions.

King/Queen are currently community-recognized/elected leadership titles, not automatic hereditary ranks. Hereditary succession is not assumed unless explicitly approved later.

GrimKoin can legitimately fund:

- campaign advertising
- billboards
- media appearances
- events
- staff
- transportation
- venues
- security
- public projects/donations where allowed

But it does not directly change official vote totals or promotion rank.

**Leadership duties:** high office receives world-state-driven responsibility rather than generic daily grind tasks.

Examples:

- Mayor: local budgets, city services, zoning, public complaints, local emergencies, contracts and staffing problems.
- Governor: regional infrastructure, inter-city issues, emergency coordination and regional policy.
- President: national budgets/policy, appointments, diplomacy, national emergencies and major security/economic issues.
- King/Sovereign Queen: highest sovereign responsibilities, major diplomacy, kingdom-wide crises, war/peace decisions where law permits, high appointments and national/kingdom stability.

Ignoring duties can affect services, city/state performance, public trust, elections, recalls, faction stability and news reputation.

**Corruption gameplay:** bribery, illegal vote buying, pressure, or secret influence can be attempted where enabled, but can fail and can create financial/camera/witness evidence, police investigations, court cases, disqualification, removal, scandal, jail/fines, and news coverage.

**Upgrade:** corruption investigations, recalls, impeachment/removal procedures, protests, strikes, political factions, polls, endorsements, campaign finance rules, coalition governments, referendums.

## Phase 19 — Land & 3D Property

- ground footprint
- vertical air rights/build volume
- optional subsurface rights
- access/ownership/rental permissions
- construction/performance budgets

Supports houses, rooms, apartments, farms, garages, shops, warehouses, clubs, offices, towers, mixed-use buildings, elevated/sky homes within deed limits.

## Phase 20 — Modular Blueprint Construction & Base-Building

**Core implementation:**

- `BPC_MW_BuildComponent` attached to `BP_MW_Character_Master`
- Enhanced Input build-mode actions instead of a permanently hardcoded keyboard key
- keyboard/mouse + Xbox-style + PlayStation-style controller mappings
- `BuildModeOn`, `CanBuild`, `SelectedBuildableID`, `SelectedFamilyID`, `SelectedVariantID`, selected definition, category/index, placement transform and placement-reason state
- active camera/view reference for placement traces
- data-driven build range rather than one fixed trace distance for every object
- ghost/preview representation
- green valid / red blocked feedback, with optional warning state later
- centralized selection refresh / `ChangeMesh`-style function updates ghost, family/variant, collision preview, opening metadata and rules when selection changes
- timer/event-driven `BuildCycle` while build mode is active
- no placement trace/update cost while build mode is off
- grid snapping
- interface-driven socket/snap-point placement
- free placement for eligible objects
- surface-aligned placement where appropriate
- configurable rotation steps and fine adjustment
- placement validation
- structural/support checks where needed
- persistent structures

**Data-driven buildable catalog:**

- canonical Struct/Data Table and/or Primary Data Asset definitions
- stable Buildable ID
- Family ID / Variant ID where applicable
- category/subcategory/search tags
- mesh/ghost representation
- soft references to heavy assets where practical
- permanent Actor Class/placement handler
- trace/query settings where needed
- variant-specific collision/footprint/opening metadata
- grid/socket/surface placement rules
- provided and accepted snap types
- range/rotation/slope/support rules
- profession/skill/permit requirements
- material/resource/GrimKoin costs
- durability/repair/demolition/utility/persistence/performance metadata
- catalog icon/description/unlock state

For the prototype, a small Data Table can be loaded/cached into an array. At scale, Metaworld should cache lightweight definitions or the active category/family rather than forcing thousands of heavy buildable assets into memory simultaneously.

**Selection and controls:**

- next/previous quick cycling, including mouse wheel as an optional keyboard/mouse default
- controller next/previous/category/variant navigation through Enhanced Input
- safe wrap from Last -> First and First -> Last
- selected identity uses stable Buildable/Family/Variant IDs rather than only array position
- scalable Build Catalog UI with categories, families, variants, search, filters, favorites, recently used, costs and unavailable reason
- build catalog must be fully navigable with controller focus/D-pad/stick/confirm/back paths
- selection change refreshes ghost mesh, placement rules, collision-preview data, opening state, snap compatibility, trace/query filters, costs and requirements

**Snap architecture:**

- foundations/floors/walls/roofs/stairs/doors/windows/utilities implement or participate in `BPI_MW_BuildSnapProvider`
- snap points can use Scene Components/sockets for exact transform plus Query-Only Box Collision or equivalent lightweight acquisition volumes
- snap point Box Extent defines usable acquisition area; keep component scale at 1 where practical
- snap points carry stable Snap Point IDs and compatibility metadata such as `Build.Snap.Foundation`, `Build.Snap.Wall`, `Build.Snap.Roof`, `Build.Snap.Door`, `Build.Snap.Utility.Power`
- Buildable Definitions declare snap types they accept and provide
- Build Component queries the hit/relevant structure through the interface, filters compatible/available points and scores/selects the best candidate
- no class-specific Foundation -> Floor -> Wall cast chain
- no scanning all snap points in the world every update
- dedicated collision/query profiles remain allowed for efficient low-level filtering
- Metaworld does not create a separate global trace channel for every future buildable category

**Wall family / wall snapping upgrade:**

- canonical initial family `Build.Family.Wall`
- initial variants: `Wall.Standard`, `Wall.DoorOpening`, `Wall.WindowOpening`
- foundations and floors expose wall-edge snap points such as North/East/South/West using `Build.Snap.Wall`
- compatible wall variants snap through the same edge contract rather than separate duplicated placement graphs
- Standard/DoorOpening/WindowOpening may differ in mesh, collision, opening size, bounds, cost, durability, support, damage and attachment metadata
- DoorOpening can expose `Build.Attach.Door`; WindowOpening can expose `Build.Attach.Window`
- gameplay blocking collision must preserve actual doorway/window openings; snap query boxes remain separate Query-Only acquisition volumes
- preview can dynamically change wall variants; the server resolves and persists the final variant definition
- converting a placed solid wall into an opening later is an authorized renovation transaction, not an untracked cosmetic mesh swap

**Doors, windows & opening attachment upgrade:**

- `Wall.DoorOpening` provides a real persistent door opening/attachment slot; it is not itself the installed door
- `Wall.WindowOpening` provides a real persistent window opening/attachment slot; it is not itself the installed window
- initial installable families include `Build.Family.Door` and `Build.Family.Window`
- each opening has stable Opening/Attachment Slot ID, transform, dimensions, facing, compatibility tags, occupancy state, installed Object/Structure ID and obstruction bounds
- door/window definitions declare accepted opening types/sizes and their own dimensions, collision, cost, durability and behavior
- player targets a compatible opening; preview snaps to that exact opening transform
- an occupied opening rejects another normal installation unless a future multi-part definition explicitly allows it
- solid walls reject Door/Window installation because they expose no compatible opening slot
- final server request references Buildable ID + Parent Structure ID + Opening/Attachment Slot ID; raw coordinates alone are not authoritative
- server checks opening existence, occupancy, size/type compatibility, property permissions, Builder requirements, cost/resources, obstruction/collision and world rules before installation
- door/window receives its own persistent ID and state while retaining a parent-opening relationship
- save/load restores wall, opening, installed object, state and relationship
- door/window pivots/orientation/closed-state transforms are standardized in the asset pipeline; per-asset offsets are explicit data exceptions
- use a small number of Build Placement/Snap/Obstruction query profiles rather than one new global trace channel for each door/window type
- collision/acquisition extents are tuned per kit; no single tutorial number such as Y Extent `1` is treated as universal correctness
- doors can later integrate open/close, locks, keys, household/business permissions, alarms, breach/damage and security systems
- windows can later integrate openable variants, breakable glass, reinforcement, alarms, weather exposure and repair
- full door/window selection, installation and interaction paths must remain controller-compatible

Detailed canonical design: `Docs/Doors_Windows_Openings_Construction_System.md`.

**Placement validation integrates with the whole Metaworld:**

- property/deed/build-volume rights
- owner/tenant/family/business/faction/public-contract permissions
- Builder profession qualification where required
- permits/licenses where required
- material/resource availability
- GrimKoin/fees where applicable
- snap compatibility and occupancy
- opening/attachment-slot compatibility and occupancy where applicable
- variant compatibility
- variant-specific collision/overlap
- obstruction bounds
- terrain/slope
- foundation/support
- height/air-right/subsurface restrictions
- zoning/utility restrictions where configured
- parcel performance/build budget

**Multiplayer authority / `SpawnBuild`:**

- client owns responsive ghost preview
- structural placement confirm sends `SelectedBuildableID/VariantID + candidate transform + optional ParentStructureID + SnapPointID`
- opening installation sends selected Door/Window Buildable ID + Parent Structure ID + Opening/Attachment Slot ID + candidate transform
- server resolves the authoritative Buildable/Variant Definition independently
- server resolves the authoritative parent Structure, Snap Point or Opening/Attachment Slot when used
- server re-validates the final requested transform and all rules
- client `CanBuild`, Actor Class, mesh, cost, resource requirements, snap/opening compatibility and occupancy are never authoritative
- resources/payment are consumed only after authoritative validation succeeds
- successful placement receives persistent Structure/Object ID, Family/Variant state, owner/property links, support/snap/opening relationships and world state

**Performance:** preview uses one temporary low-cost ghost; updates use timers/events rather than unnecessary unconditional Tick; targeted traces/overlaps replace broad world scans; snap/opening queries target the hit/relevant structure; heavy buildable assets can use soft references/category loading; wall/door/window variants share common logic; moving door logic runs only while needed; permanent structures participate in World Partition/HLOD/relevancy systems.

**Approved upgrades:** foundations/support graphs, walls/floors/roofs/stairs, standard/door-opening/window-opening walls, separate placeable doors/windows attached to persistent opening slots, multiple opening sizes/styles, door locks/keys/access permissions, security/reinforced doors/windows, breakable windows, build catalog favorites/recently used, snap/opening occupancy/reservation, snap-point scoring, snap-tag debugger, house-plan presets, copy/rotate/mirror tools, staged construction, construction contracts, Builder companies, inspections, wiring, plumbing, HVAC, structural damage, renovation, repair, demolition/salvage, utility hookups, city/public construction contracts and property construction history.

Detailed canonical construction design: `Docs/Modular_Blueprint_Base_Building_System.md`.

## Phase 21 — Utilities & Bills

Real-time billing:

- electricity
- water
- heating
- fuel/gas where appropriate
- communications/internet later
- sanitation
- security
- rent
- taxes
- maintenance

Nonpayment can lead to actual service shutoff and gameplay consequences.

**Upgrade:** generators, solar/batteries, wells, water tanks, fireplaces, backup heaters, insulation, emergency systems, smart-home controls.

## Phase 22 — Business Ownership

Businesses include bars, clubs, stores, restaurants, garages, hotels, security companies, transport, apartment businesses, theaters/drive-ins, farms, construction companies, media companies and more.

Owners pay wages, rent, tax, utilities, inventory, maintenance, security, advertising, and food/staff-meal costs where contracts or business models include them. Appropriate workers receive tips.

Business owners/managers receive operational duties based on actual stock, staff, bills, customers, repairs, security, contracts and supply problems rather than decorative management menus.

## Phase 23 — Advertising

- city billboard permits/rent
- monthly fees/tax
- premium locations
- storefront/public displays

**Upgrade:** radio commercials, TV ads, sponsored events, digital billboard schedules, district campaigns, political/campaign advertising under configured election rules.

## Phase 24 — Creator Marketplace

Locked creator rule:

- Metaworld controls base meshes, UVs, material slots/order/assignments, master materials, collision, rigging, gameplay metadata, Nanite/performance settings and technical structure.
- Creators upload approved texture maps only for locked inputs.
- Creator sale proceeds split between creator and configurable Metaworld commission.

**Upgrade:** creator brands, storefronts, collections, followers, reviews, favorites, limited releases, gifting, version management.

## Phase 25 — AI Music, AI Video & Player Media Ownership

Player-sold music/video is **AI-generated-only**.

Requirements:

- seller owns the AI-generated output
- seller is permitted to sell/distribute it
- rights/ownership declaration stored with the Media Asset ID
- normal sale creates a buyer-owned Metaworld copy/entitlement
- creator retains the original sellable product unless a future explicit exclusive-sale type says otherwise
- another player who wants independent playback must buy/obtain their own entitlement
- hearing/watching somebody else's playback does not grant ownership

Spatial playback rule:

- owner plays song in car -> occupants can hear it
- owner plays song in house/club -> people in the active media zone can hear it
- owner plays video on TV/screen -> people in the viewing zone can watch it
- attendees/listeners/viewers do not receive the file merely by being present
- leaving the zone ends shared access unless they own their own copy or another authorized source is playing it

Supported systems can include AI-generated songs, albums, music videos, films, documentaries, advertisements and other approved AI-created media.

**Upgrade:** creator media storefronts, playlists, albums/series, venue screening permissions, buy-as-gift, entitlement transfer rules, radio-station/business broadcast licensing, charts/discovery, creator brands, favorites, reviews, and media libraries.

Detailed canonical design: `Docs/AI_Media_Ownership_Playback_Licensing.md`.

## Phase 26 — Vehicle Foundation

- ownership/keys/locks
- drivers/passengers
- cargo/storage scaling
- fuel
- maintenance
- damage
- theft
- recovery
- keyboard/mouse + gamepad driving controls

**Upgrade:** trailers, towing, insurance, impound, GPS, plates, repairs, customization, racing, taxis, buses, freight/public transport.

## Phase 27 — Voice & Text Communication

Voice channels can include proximity, vehicle, room/property, party, phone/radio, business/security.

Text can include local, DM, party, business, faction, property/room, system/news.

Players choose voice, text, or both.

Communication UI must remain controller-navigable where it is part of required gameplay.

## Phase 28 — Social Activities

- clubs/bars/restaurants
- parties
- concerts
- dates/weddings/funerals
- family meals/gatherings
- malls/parks/beaches/gyms
- sports/community gatherings
- ceremonies
- political rallies/debates/community meetings

Leisure remains inside the living world and can be interrupted by danger/events.

## Phase 29 — Event Ledger

Persistent verified world-event records:

- Event ID
- timestamp
- location
- participants
- verified facts
- consequences
- related property/business/faction
- public/private state
- importance

Election results, public appointments, recalls, major scandals, public-office deaths, major food shortages and similar civic events can feed the ledger.

Role-duty completion/failure can feed relevant organization/public records when significant.

## Phase 30 — Metaworld News

News exists through TV, radio, car radio, store/bar/hotel screens, public displays, phones/computers later, publications, emergency alerts and other appropriate channels.

Official verified news remains distinct from player journalism, player AI-generated entertainment media, opinion, rumor and advertising.

News can report elections, campaigns, debates, scandals, recalls, shortages, strikes, food emergencies, leadership changes and professional/public achievements when newsworthy.

## Phase 31 — Living History

- monuments
- memorials
- graveyards
- museums
- plaques
- archives
- newspapers
- property histories
- major player biographies
- wars/elections/disasters/discoveries recorded
- former Presidents/Kings/Queens/Mayors/community leaders recorded where historically important

## Phase 32 — Crime System

- theft
- robbery
- assault
- murder
- trespassing
- property damage
- vehicle theft
- fraud
- illegal business actions
- supernatural crimes
- bribery/corruption/election crimes where enabled

## Phase 33 — Cameras & Evidence

Cameras can be common inside/outside stores, banks, bars, clubs, businesses, streets, parking, apartments and public buildings.

Camera rule:

> The camera records the visible person, not hidden account identity.

A mask means masked visual evidence. Clear face means face evidence.

Performance rule: evidence data may be recorded cheaply; do not render every security camera with continuous SceneCapture every frame. Live video is activated only where needed.

**Upgrade:** body cams, dash cams, traffic cameras, fingerprints, footprints, ballistics, forensic/DNA-style evidence if desired, chain-of-custody, evidence lockers, detectives.

## Phase 34 — Police, Ranks, Duties & Courts

- patrol/dispatch
- world-state-driven daily/shift duties
- warrants
- evidence review
- arrests
- questioning
- jail
- lawyers/judges
- court cases
- appeals
- fines
- bail
- community service

Police career rank is earned, not bought.

Possible configurable progression:

Officer -> Senior Officer -> Sergeant -> Lieutenant -> Captain -> higher command where supported.

Promotion can consider service, successful work/cases, evidence quality, lawful conduct, community trust, training/certification, leadership, complaints, discipline, corruption history, and department/community evaluation or vote where configured.

A bad officer who mistreats the city cannot simply spend GrimKoin to become Captain.

Higher police rank changes duties: supervisors must manage personnel, priorities, resources, cases, emergencies and accountability rather than merely receiving a stronger badge.

Player police have in-world legal authority only — not platform moderation powers.

## Phase 35 — Universal Combat

- unarmed combat
- fists/feet/shove/grab/tackle/grapple
- stones/bottles/pipes/bats/chairs/tools
- knives/firearms
- magic/supernatural attacks
- block/dodge/recoil
- armor
- hit locations
- injuries/bleeding/status
- durability/condition
- complete keyboard/mouse + controller combat mappings

## Phase 36 — Destruction

- breakable doors/windows/fences/interiors
- object state transformations
- controlled Chaos/Geometry Collection use
- vehicle/property damage

Destruction must obey physics/performance budgets.

Door/window destruction later uses the separate persistent object state rather than requiring the entire wall to be replaced.

## Phase 37 — Player Needs & Survival

- Health
- Stamina
- Hunger
- Thirst
- Fatigue
- Mana
- temperature/injuries/sickness/pain later where fun

NPC and household needs use the same general world philosophy but scale through lower-cost simulation at distance.

## Phase 38 — Food, Cooking & Household Supply Economy

Food is a first-class recurring economic resource.

Core systems:

- farming/groceries
- cooking/recipes
- restaurants
- food quality
- spoilage/refrigeration
- Chef profession
- delivery
- household pantry/refrigerator
- family meal supply
- companion/team ration supply
- business staff meals where applicable
- emergency food reserves later

Food should not be unrealistically cheap. Pricing can reflect production, transport, wages, rent, utilities/refrigeration, city tax, scarcity, quality, spoilage risk, weather, war/disruption, local demand, and region.

A solo player has lower food costs than a player supporting a spouse/family, guards, AI companions, employees whose contract includes meals, or a large event/team.

Food must remain obtainable through work and normal economic play; the goal is meaningful budgeting, not unavoidable starvation for active players.

**Upgrade:** food preferences/diets, food supply contracts, wholesale markets, restaurant reputation, emergency rationing, famine/shortage events, city food reserves, household auto-shopping permissions.

Detailed canonical design: `Docs/Food_Family_NPC_Needs_Community_Ranks_Governance.md`.

## Phase 39 — Healthcare

- hospitals/clinics
- doctors/nurses
- ambulances
- treatment/rehabilitation
- medical bills
- supernatural medicine
- real patient/emergency duties for healthcare roles

**Upgrade:** insurance, specialist care, emergency rooms, blood banks and other systemic healthcare.

## Phase 40 — Magic

- mana
- spells
- enchantments
- status effects
- magical equipment
- magical locations/events
- skill trees/professions
- controller-compatible spell/ability selection and activation

## Phase 41 — Supernatural Lineages

Initial canonical lineages:

- Human
- Vampire
- Werewolf

Lineage changes needs, abilities, morphs, senses, weaknesses, animation and social/political rules without escaping ordinary Metaworld systems.

## Phase 42 — Vampire Systems

Potential systems:

- blood hunger/resource
- feeding
- night/perception abilities
- sunlight/other weaknesses
- vampire houses/covens
- vampire skill branches
- politics/businesses/medicine/social systems

## Phase 43 — Werewolf Systems

Potential systems:

- transformation
- scent/tracking
- packs/territory
- howl/social signals
- physical strengths
- transformation-control mastery
- weaknesses
- werewolf political systems

## Phase 44 — Factions

Lineage is not faction.

Humans, vampires, werewolves and future lineages may create mixed or separate factions, governments, covens, packs, gangs, companies, communities and alliances.

Faction leaders can use internal member/community election or other approved collective selection rules. GrimKoin does not automatically buy command rank.

Faction ranks also carry role-appropriate responsibilities where the organization supports them.

## Phase 45 — Diplomacy

Relationship states can include alliance, trade agreement, peace, tension, hostility, defensive pact, ceasefire, truce, occupation and war.

**Upgrade:** treaties, ambassadors, border permissions, sanctions, safe passage, negotiated peace.

## Phase 46 — War

War remains inside the living persistent world.

It can affect borders, checkpoints, travel, property, businesses, prices, food supply, shortages, jobs, taxes, security, refugees, news, deaths, inheritance and territory.

No separate disconnected war lobby is required.

Leadership/military role duties respond to actual war state, logistics and threats.

## Phase 47 — Real-Time Calendar

Real elapsed time drives days/weeks/months/years and economic obligations such as bills, rent, taxes, payroll, permits, elections, campaign periods, leadership terms, contracts, estate windows and seasonal events.

Role schedules, shifts and recurring responsibilities can use the same calendar without requiring every duty to be a daily repetitive quest.

## Phase 48 — Day/Night

- sunrise/sunset
- moon/stars
- shop schedules
- nightlife
- NPC sleep/work
- NPC meals
- street lights
- crime patterns
- vampire behavior

## Phase 49 — Weather & Climate

- clear/cloud/rain/storm/fog/wind
- heat/cold
- snow/ice where appropriate
- regional climate

Weather affects driving, survival, utilities, power, crops, food supply/prices, visibility, fires, businesses, NPC schedules, role duties and world events.

Open/broken windows and doors can later affect weather exposure/interior comfort when those systems are implemented.

## Phase 50 — World Partition / HLOD

Large Earth regions use streaming/HLOD so players never pay full simulation/rendering cost for the entire world at once.

## Phase 51 — Procedural Content Generation

PCG can support vegetation, roadside dressing, rocks, rural variation, forests and large-scale environment dressing while important locations remain deliberately designed.

## Phase 52 — Systemic NPCs & Household Needs

Important NPCs can have identity, home, job, profession, schedule, needs, health/stamina/mana, hunger/thirst/fatigue where appropriate, skills, inventory, money, relationships, reputation, personality, goals, ownership and legal state.

NPC hunger is real.

Nearby NPC:
- can seek food
- shop/eat/cook through world systems
- consume actual inventory/resources

Distant NPC:
- lightweight food/need simulation

Unloaded NPC:
- timestamp/resource/income/household-state calculations rather than continuous Actor Tick

NPC spouses/family/households can share food reserves and budgets where relevant.

NPC workers/leaders can receive the same role-duty categories as players, resolved through cheaper scheduled simulation when unloaded.

## Phase 53 — NPC Intelligence

- StateTree
- Smart Objects
- significance-aware perception
- event-driven reasoning
- schedules/goals/needs
- food-seeking and meal behavior
- role-duty selection/execution
- emergency reactions
- same world capability rules as players wherever practical

NPCs should understand usable doors/openings through normal navigation/interaction systems rather than construction-only snap collision.

## Phase 54 — NPC Population LOD

- nearby critical NPC: full simulation
- nearby ordinary NPC: reduced expensive logic
- distant NPC: lightweight state simulation
- unloaded NPC: data record + timestamp/event simulation only

Food, household consumption, employment, role duties and voting behavior must use aggregated/scheduled simulation when NPCs are unloaded rather than per-frame logic.

Mass-based systems may be evaluated later but must not violate the Blueprint-first rule or become a required dependency until proven suitable.

## Phase 55 — Companion Teams & Provisioning

Recruit/employ NPC guards, mechanics, medics, drivers, builders, farmers, cooks, managers, scouts, security and other roles.

Players can assign tasks, budgets, equipment, permissions, schedules, vehicles, storage, emergency rules, and food/ration access.

Companions do not receive free food because they are owned/recruited.

Provisioning options can include:

- shared home pantry
- base/team food storage
- direct rations
- employer-provided meals
- wages with permission for NPC to buy their own food
- cook/logistics NPC maintaining supplies

Companion tasks should fit their assigned role and actual team needs.

## Phase 56 — Optional AI NPC Gateway

Optional local/external AI can improve selected NPC dialogue/planning, but normal NPC gameplay must function without paid AI.

AI chooses high-level intent; Metaworld Blueprint systems validate and execute actual actions.

AI-enhanced NPCs remain hungry, need resources, obey professions, spend real budget, perform role responsibilities, and cannot invent food or bypass economy/world rules.

## Phase 57 — World Event & Role Duty Director

Contextual events can include zombie outbreaks, robberies, blackouts, fires, storms, faction attacks, supernatural incidents, protests, political events, elections, recalls, corruption scandals, food shortages, supply disruptions and war declarations.

The same world state can generate duties for relevant roles instead of generic daily quests.

Examples:

- robbery -> police response/investigation + journalist coverage + hospital treatment if injured
- storm -> utility repair + police traffic control + mayor emergency decisions + supply deliveries
- food shortage -> farmer/driver/grocer contracts + leadership response + news coverage
- damaged/breached property -> Builder/security/police/insurance duties where relevant
- war -> military/security duties + medical response + diplomacy + logistics + refugee aid

## Phase 58 — Zombies & Threat Systems

Threats can reach houses, clubs, stores, hospitals, police stations, streets, farms, businesses and other places. No magical safe-zone immunity.

Threats can disrupt food production, transport and household supply and generate emergency duties for many professions.

Doors/windows can later be breached/damaged according to their real durability/security state rather than acting as magic barriers.

## Phase 59 — Authoritative Multiplayer

Server authority governs money, inventory, combat outcomes, death, ownership, property, construction placement, evidence, tax, jobs, businesses, vehicles, votes, leadership rank, career rank, role-duty completion/rewards, household state, and other critical state.

Construction placement requests use stable Buildable/Variant IDs; the server resolves authoritative Actor Class, mesh/variant, cost, resource, snapping, opening/attachment and permission data rather than trusting client values.

## Phase 60 — Replication Scaling

Use relevancy/dormancy/update-rate reduction/compact state so clients do not receive every NPC, camera, business, property, election state, construction preview and vehicle in the world.

Construction ghosts remain local/transient unless a deliberate cooperative-build feature requires sharing preview state; permanent structures replicate/stream through normal world relevancy.

Door/window state replication should transmit meaningful state changes rather than require continuous full-rate updates while idle.

Role-duty UI receives only duties relevant to the player/organization/jurisdiction rather than global task spam.

Evaluate UE5.8 replication options such as standard replication, Replication Graph and Iris only after Blueprint workflow and production suitability are verified.

## Phase 61 — Smoothness Program

Primary target: stable 60-FPS-class gameplay on recommended PC hardware where practical, with stable frame pacing prioritized over peak FPS.

Every major system has CPU/GPU/network/memory/significance budgets.

Food, family, NPC hunger, elections, role-duty checks and rank checks must be event/timestamp-driven rather than per-frame world scans.

Construction placement updates run only during build mode, use targeted traces/overlaps, and stop immediately when build mode exits. Large build catalogs use lightweight indexes/soft references/category caching rather than loading every heavy construction asset at once.

Construction snap/opening detection asks only the hit/relevant structure for filtered compatible points/slots; it never scans the whole world every placement update. Related wall/door/window variants share common logic/data rather than multiplying placement Blueprints.

Idle doors/windows do not run unnecessary permanent Tick logic; movement/interaction updates occur only when required.

Controller support must use Enhanced Input actions/context mappings rather than expensive polling hacks.

## Phase 62 — Nanite-First Rendering

Nanite default for compatible buildings, roads, rocks, props, furniture, creator base meshes, environment assets, suitable foliage, Geometry Collections, landscape workflows, compatible vehicle parts and compatible skeletal assets.

Morph-dependent body/face meshes remain approved exceptions when necessary.

Permanent construction meshes use Nanite wherever compatible and beneficial; preview ghosts may use a simpler rendering representation when that is cheaper or technically cleaner.

## Phase 63 — Lumen / Lighting Scalability

Quality tiers can scale Lumen, shadows, reflections, volumetrics and related settings without changing gameplay correctness.

## Phase 64 — MegaLights

Use where appropriate for dense city/nightlife/local-light scenes, subject to profiling and quality tiers.

## Phase 65 — Animation Budgeting

Animation cost is significance-aware. Local player and important nearby characters receive priority; crowd/distant characters reduce update rate, IK, facial detail and other expensive layers.

Meal/cooking/social/role-duty animations only run at full fidelity when characters are relevant/visible.

## Phase 66 — Shader Hitch Prevention

Integrate PSO precaching and hitch analysis early enough that new materials/effects do not create recurring runtime shader stalls.

Construction ghost/preview materials and the full library of buildable materials must be included in hitch/performance testing.

## Phase 67 — User Interface

UI for inventory, character creator, map, banks, jobs, professions, skills, businesses, property, construction/build catalogs, household/pantry needs, team provisioning, communications, news, police tools, elections/candidates/voting, career rank, role duties/responsibilities, creator systems, AI-media libraries and other game domains.

Construction UI can include categories, families/variants, Door/Window categories, opening compatibility, search/filter, favorites/recently used, thumbnails, material/resource costs, profession/permit requirements, snap compatibility, rotate/snap controls, placement failure reason and cancel/confirm controls.

All major required menus must have controller focus/navigation paths; mouse-only critical controls are not acceptable.

## Phase 68 — Accessibility, Rebinding & Controller Compatibility

- keyboard/mouse
- Xbox-style controllers
- PlayStation-style controllers
- full/reasonable rebinding
- Enhanced Input action/context architecture
- controller focus navigation
- device-appropriate prompts where practical
- stick sensitivity/dead-zone settings
- invert axes where appropriate
- hold/toggle options where useful
- subtitles
- text alternative to voice
- per-player voice volume/mute/block
- UI scaling
- readable text
- color accessibility
- camera shake controls
- motion blur controls
- FOV controls where practical
- rebindable construction controls rather than a mandatory `B` key
- next/previous construction and family/variant cycling are rebindable and also accessible through catalog UI
- Door/Window installation and interaction has controller-equivalent select/target/confirm/cancel/open/close/lock actions where applicable

**Acceptance gate:** every major player-facing feature is tested with keyboard/mouse, an Xbox-style gamepad and a PlayStation-style gamepad. A feature is not complete if required gameplay cannot be completed through a supported controller path.

Detailed canonical design: `Docs/Controller_Input_Compatibility_Architecture.md`.

## Phase 69 — Worst-Case Performance & Input Test Worlds

Required stress tests include:

- downtown traffic + pedestrians + rain + night lighting
- busy nightclub + voice + dancing + AI music/video screens + security
- zombie attack during crowded event
- police response + cameras + vehicles + news
- city election/rally with many player/NPC voters
- role-duty director generating simultaneous legitimate duties across multiple professions
- large household/companion base with food consumption and schedules
- restaurant/grocery supply scene with many NPC consumers
- active construction site with catalog cycling, wall variant cycling, door/window opening installation, ghost preview, interface snap detection, foundation/floor wall-edge snap boxes, repeated modular pieces and many nearby finished structures
- large construction catalog selection stress test without loading every heavy asset
- full construction flow tested with keyboard/mouse, Xbox-style controller and PlayStation-style controller
- controller navigation through character creator, inventory, build catalog, bank and job/role-duty UI
- wall collision/navigation test with Standard, DoorOpening and WindowOpening variants
- install/remove/replace door and window tests with opening occupancy/obstruction validation
- repeated door open/close interaction without idle Tick cost explosion
- war/combat/destruction scene
- dense property with many owned items
- creator marketplace/business district

A feature is not complete because it works in an empty test map or only with one input device.

## Phase 70 — Wildlife & Animals

Future expansion: wildlife, pets, guard dogs, farm animals, hunting, fishing, ownership and veterinary gameplay.

Animals may later create additional feeding/feed-supply costs where appropriate.

## Phase 71 — Agriculture

Future expansion: crops, livestock, food supply chains, grocery businesses, restaurants and agricultural professions.

Agriculture is a strategic food-economy pillar because household, NPC, business and city demand consumes actual food supply.

Agriculture roles receive actual production/harvest/supply duties based on season, land, weather, demand and shortages.

## Phase 72 — Education

Future expansion: profession schools, universities, training centers, certifications, mentorship and skill instruction.

Education can contribute to eligibility for advanced professional rank and public office where rules require qualifications.

Builder training/certification can unlock larger or regulated construction categories.

## Phase 73 — Public Transportation

Future expansion: buses, taxis, trains, stations, transit jobs and fares.

Transit employees receive real route/transport duties based on schedules and demand.

## Phase 74 — Insurance

Future expansion: vehicle, property, business, health and cargo insurance. Insurance must not become magical instant replacement of all loss.

Construction/property insurance may later recognize inspected structures, code compliance, security, utilities and damage history.

Damaged/breached doors and windows can later participate in legitimate property insurance/repair claims if that system is implemented.

## Phase 75 — Tourism & Entertainment

Future expansion: hotels, resorts, attractions, beaches, arenas, festivals, concerts, tourism businesses and events.

Large events create food/service demand and campaign/civic-event opportunities.

## Phase 76 — Expanded Religion & Belief Systems

Future expansion: religions, temples/churches/orders, ceremonies, faith reputation, player leadership, supernatural belief responses and social/political effects.

Religious/community leadership can use its own trust/election/selection rules and cannot automatically be purchased with GrimKoin unless that specific institution's legitimate world rules explicitly allow a monetary office — which does not override public-government rank rules.

Leadership roles can receive institution-appropriate responsibilities generated from actual followers/events/community needs.

## Phase 77 — Legacy / Long-Term Player Goals

Metaworld does not need a single final boss/end screen.

Long-term accomplishments can include becoming Mayor, Governor, President, King, Queen, Police Captain/Chief where configured, business elite, famous AI-media creator/musician/filmmaker, notorious criminal, legendary builder/gunsmith, landlord/property owner, faction leader, vampire coven leader, werewolf pack leader, war survivor/hero, historical figure, family founder or community leader.

Leadership is meaningful because players/NPC communities must trust and select you and because high office carries real responsibilities. GrimKoin cannot simply purchase these achievements.

Builders can leave persistent architectural history through famous homes, businesses, public works, monuments and districts recorded in property/history systems.

The world can remember those lives through inheritance, news, museums, monuments, property history, election history and the Event Ledger.

## Phase 78 — Future GrimKoin Buyback

**Far future only. Not active now.**

Do not enable until the economy, anti-fraud/provenance, account security, identity/compliance, payment, tax, jurisdiction and legal systems have been separately reviewed and deliberately approved.

Current development only preserves the ledger/provenance architecture needed so this remains technically possible later.

---

# 5. Approved High-Value Upgrade Map

| Foundation | Approved Upgrade |
|---|---|
| Third-person starter | Master Blueprint + modular Blueprint Components |
| Input | Enhanced Input + keyboard/mouse + Xbox-style + PlayStation-style controller support across every major player-facing feature |
| Basic locomotion | Motion Matching + IK + contextual movement |
| Character creator | Full morph system + age + body diversity + clothing fitting + controller navigation |
| Inventory | Persistent Item DNA + container/household storage rules + controller UI |
| Weapons | Universal object capabilities |
| GrimKoin/PromoKoin | Full server-authoritative ledger + provenance |
| Banking | Bank privacy + death settlement + estates/wills |
| Jobs | Profession qualifications + licensing + apprenticeship later |
| Role duties | Dynamic world-state-driven responsibilities fitting each job/rank rather than repetitive arbitrary daily chores |
| Career ranks | Merit/service/trust-based promotion; no GrimKoin rank purchase |
| Playable hierarchy | No Owner rank; King/Sovereign Queen highest player rank, President next, lower ranks scoped by jurisdiction/organization |
| Government | Community elections/selection for Mayor/President/King/Queen and other civic leadership + real leadership responsibilities |
| Political economy | Campaign spending allowed; vote buying/bribery only as risky corruption gameplay |
| City tax | Persistent city treasury + budgets/government |
| Food | Real household/NPC consumption + meaningful pricing + supply-chain economy |
| Family | Spouse/household needs + pantry/budget responsibility |
| AI/NPC companions | Hunger + provisioning/rations/wages; AI does not remove physical needs |
| Property | 3D parcels + utilities + real-calendar bills |
| Construction | Modular `BPC_MW_BuildComponent` + Data Table/Data Asset catalog + stable Buildable/Family/Variant IDs + quick cycling/catalog UI + `BPI_MW_BuildSnapProvider` + query-only snap volumes + Standard/DoorOpening/WindowOpening wall family + separate persistent Door/Window families installed into authoritative opening slots + pivot/orientation standards + obstruction/occupancy validation + controller controls + timer ghost preview + property/profession/resource validation + server-authoritative persistent placement |
| Business | Employees + payroll + food where applicable + tax + tips + advertising + operational duties |
| Vehicles | Cargo + ownership + theft + maintenance + damage + controller driving |
| Social | Spatial voice + text + living social venues |
| Player media | AI-generated-only + creator ownership + per-buyer entitlements + spatial shared playback |
| Cameras | Evidence system without omniscient identity or constant SceneCapture |
| News | Event Ledger-driven news throughout world |
| NPCs | StateTree + Smart Objects + population LOD + scheduled needs/voting/role duties |
| Supernatural | Lineages + morphs + politics + territory + war |
| Rendering | Nanite-first + HLOD + scalable Lumen/MegaLights |
| Smoothness | Performance budgets + PSO precaching + continuous profiling |
| Open world | World Partition + HLOD + PCG where useful |
| Production tooling | Python Editor validators, audits and batch tools |

All upgrades in this table are approved and part of the canonical roadmap.

---

# 6. First Full Vertical Slice

Before building the entire world, prove Metaworld's DNA in one small but fully connected town.

Recommended vertical slice contains:

- one small town
- one bank
- one store/grocery
- one bar/club
- one restaurant/food source
- one police station
- one hospital/clinic
- one rental/apartment building
- one player property
- one buildable home/structure
- modular `BPC_MW_BuildComponent` build-mode prototype
- Data Table/Data Asset catalog with at least Foundation, Floor and Wall definitions
- stable Buildable/Family/Variant IDs
- next/previous cycling through Foundation -> Floor -> Wall with wrap-around
- Wall family cycling through Standard -> DoorOpening -> WindowOpening
- selection/variant change refreshes ghost mesh, collision/opening preview and placement rules
- camera-based placement trace with data-driven range
- timer-driven green/red ghost preview
- `BPI_MW_BuildSnapProvider` implemented by Foundation/Floor/Wall pieces where appropriate
- Query-Only Box Collision or equivalent snap acquisition volumes with stable Snap Point IDs
- foundation/floor North/East/South/West wall-edge snap points
- snap metadata proving all compatible wall variants use the same `Build.Snap.Wall` edge contract
- interface-driven snap detection on the hit/relevant structure
- invalid/occupied snap combination rejection
- Standard wall blocks correctly
- DoorOpening wall leaves a usable doorway opening and exposes a stable Door attachment/opening slot
- WindowOpening wall leaves a usable window opening and exposes a stable Window attachment/opening slot
- separate Door Buildable snaps only into a compatible unoccupied Door opening
- separate Window Buildable snaps only into a compatible unoccupied Window opening
- Door/Window size/type mismatch is rejected
- a solid wall cannot accept Door/Window installation
- a second normal Door/Window cannot occupy the same opening
- obstruction validation prevents a Door/Window from being installed inside wall geometry/another object
- installed Door receives its own persistent ID and can open/close correctly
- installed Window receives its own persistent ID
- save/load restores wall + Opening ID + installed Door/Window + relationship/state
- unauthorized player cannot replace/remove installed Door/Window
- snap query volumes do not block player movement
- grid rotation/snap
- property-boundary permission rejection
- Builder qualification check for structural piece/installation where required
- material/GrimKoin cost validation per wall/Door/Window variant
- server resolves Buildable/Variant ID + Parent Structure ID + Snap/Openings IDs rather than trusting client Actor Class/mesh/cost/snap state
- server-authoritative final placement and persistent Structure/Object ID state
- complete construction flow tested with keyboard/mouse
- complete construction flow tested with Xbox-style controller
- complete construction flow tested with PlayStation-style controller
- one usable vehicle with keyboard/mouse and controller driving
- GrimKoin + PromoKoin
- VIP purchase architecture stub without future cashout
- banking
- city tax/treasury
- bills/utilities
- inventory + Item DNA
- jobs/professions
- at least three role-duty examples generated from actual town state
- police rank prototype based on service/reputation rather than money
- one police shift with world-state-driven duties
- one local election prototype with player/NPC voters
- campaign spending separated from actual votes
- one Mayor leadership-duty example based on a real town problem
- morph character creator fully navigable with controller
- clothing fitting baseline
- voice/text
- one AI-generated song marketplace purchase + owned-copy playback test
- one AI-generated video marketplace purchase + TV/shared-room playback test
- verification that shared listeners/viewers do not receive ownership
- security cameras/evidence
- police investigation
- household/family food inventory prototype
- recruited NPC/companion hunger + provisioning prototype
- grocery/restaurant food purchase and consumption loop
- day/night
- weather
- 20–50 meaningful NPCs with population LOD
- one vampire gameplay example
- one werewolf gameplay example
- one zombie/dynamic world-event scenario
- permanent death
- estate/recovery system
- Event Ledger
- news reporting what actually happened
- controller navigation test through major vertical-slice menus
- performance stress testing

If this town works smoothly and the systems truly interoperate, Metaworld has proven the architecture needed to scale outward.

---

# 7. Permanent Development Principle

Metaworld can be enormous without rendering and simulating everything at maximum fidelity at once.

The permanent architecture is:

`Full fidelity near the player`

`Reduced fidelity at distance`

`Persistent data-only simulation when unloaded`

`Stream only what is needed`

`Budget expensive systems`

`Profile continuously`

`Support controller and keyboard/mouse from feature inception`

`Scale visuals before sacrificing responsiveness`

Final rule:

> Metaworld should feel alive, not heavy. The player should notice the world — not the engine struggling to run it.

---

# 8. Roadmap Feature Intake Rule

The Master Roadmap is a living canonical plan.

When new Metaworld feature ideas are approved, they should be handled in one of four ways:

- **LOCKED** — approved and added directly to the roadmap/global rules.
- **UPGRADE** — approved improvement to an existing phase.
- **FUTURE** — approved concept intentionally scheduled later.
- **RESEARCH** — promising idea that must be tested before becoming a dependency.

New discoveries from Unreal Engine videos, YouTube research, Epic documentation, games, tools, plugins, design references, or future brainstorming should be checked against the existing architecture before being inserted.

Rules for intake:

1. Do not delete an already approved Metaworld rule merely because a new feature exists.
2. Integrate the new feature with existing systems rather than creating duplicate isolated systems.
3. Identify which roadmap phase owns the feature.
4. Add a new phase only when the feature is truly a separate major system.
5. Record performance implications.
6. Preserve Blueprint-first runtime architecture unless the owner explicitly changes that rule.
7. Preserve the smoothness/performance target.
8. Preserve player ownership/economy/security rules.
9. Preserve Xbox-style and PlayStation-style controller compatibility for player-facing features alongside keyboard/mouse.
10. Preserve role-appropriate responsibility/duty integration when a new feature affects jobs, professions, departments or leadership.
11. Prefer shared family/variant/data architecture over duplicated Blueprint logic when related content differs mainly by configuration or structural variant.
12. Keep structural openings separate from installed functional objects when that separation improves replacement, damage, security, ownership or persistence.
13. Do not turn tutorial-specific collision values or one-off trace channels into universal architecture unless profiling/testing proves they belong there.
14. Mark experimental Unreal features as research/evaluation until proven suitable.
15. Keep the roadmap current so it can always answer: what is approved, what comes later, and what still needs research.

---

# 9. Canonical Companion Documents

The Master Roadmap is supported by detailed companion designs in `Docs/`, including:

- `AI_Media_Ownership_Playback_Licensing.md`
- `Avatar_Communication_Character_Animation_Architecture.md`
- `Banking_Currency_Custody_Future_Cashout.md`
- `Blueprint_Python_Nanite_Architecture.md`
- `Character_Morph_Customization_System.md`
- `City_Taxation_Jobs_Wealth_Reputation.md`
- `Controller_Input_Compatibility_Architecture.md`
- `Creator_Marketplace_Texture_System.md`
- `Doors_Windows_Openings_Construction_System.md`
- `Earth_Property_Vehicles_Media_News.md`
- `Estate_Wills_Inheritance_Succession.md`
- `Food_Family_NPC_Needs_Community_Ranks_Governance.md`
- `Free_To_Play_Economy_Media_Business_Threat_Model.md`
- `Living_World_Environment_NPC_AI.md`
- `Modular_Blueprint_Base_Building_System.md`
- `Performance_Smoothness_FrameTime_Architecture.md`
- `Real_Time_Life_Utilities_Advertising_VIP_GrimKoin_Death_Legacy.md`
- `Security_Cameras_Evidence_Identity.md`
- `Supernatural_Lineages_Vampires_Werewolves.md`
- `World_Rank_Hierarchy_Roleplay_Authority.md`

When a companion document contains more detail than this roadmap, the roadmap establishes the approved feature direction and the companion document defines the detailed behavior, unless a later explicit canonical decision supersedes it.

For player music/video ownership and playback, `AI_Media_Ownership_Playback_Licensing.md` supersedes older broader wording that allowed generic non-AI player media sales.

For food, family/household needs, NPC provisioning, community voting, professional rank and elected leadership, `Food_Family_NPC_Needs_Community_Ranks_Governance.md` is the detailed canonical companion design.

For controller/input compatibility, `Controller_Input_Compatibility_Architecture.md` is the detailed canonical companion design. Every future player-facing feature must preserve keyboard/mouse plus Xbox-style and PlayStation-style controller operation where a reasonable control path exists.

For construction/base-building, `Modular_Blueprint_Base_Building_System.md` is the detailed canonical companion design and supersedes generic older construction wording when additional detail is required, including wall-family variants, wall-edge snapping, variant-specific collision/openings and future door/window attachment slots.

For installed doors/windows/opening attachment behavior, `Doors_Windows_Openings_Construction_System.md` is the detailed canonical companion design. Door/window objects remain separate persistent buildables attached to structural openings.

For global playable roleplay rank placement, `World_Rank_Hierarchy_Roleplay_Authority.md` is the detailed canonical companion design. There is no Owner/Creator gameplay rank; King/Sovereign Queen is the highest player-held rank and President is directly below it.