# Metaworld — Master Development Roadmap v2

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
- performance budgets
- profiling/stress-test maps
- automated asset validation later
- automated Nanite, animation, creator-content, and performance audits later

## Phase 1 — Master Third-Person Character

- third-person locomotion
- optional first-person camera mode
- Enhanced Input
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

**Upgrade:** executors, joint ownership, trusts, family businesses, divorces/prenups if wanted, estate auctions, funeral services, cemeteries, memorials.

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

## Phase 15 — Jobs

Always maintain legitimate lower-entry GrimKoin earning paths such as cleaning, delivery, loading, farm work, sanitation, courier, construction labor, store/bar/restaurant work, driving, temporary city work, security assistance, and other gigs.

## Phase 16 — Profession System

Action tiers:

- general
- skilled/learnable
- profession-exclusive
- profession + legal license

Examples: Gunsmith, Builder, Mechanic, Electrician, Plumber, Doctor, Nurse, Lawyer, Judge, Police, Security, Farmer, Driver, Chef, Bartender, DJ, Musician, Journalist, Realtor, Banker, Investigator, Teacher, Engineer, supernatural/magic specialists.

**Upgrade:** apprenticeship, certifications, schools, mentors, mastery, professional reputation, licenses/suspension.

## Phase 17 — Taxation & City Treasury

Taxable activities can include sales, player businesses, creator products, services, rooms/rent, leases, property, vehicle sales, entertainment, permits, advertising, inheritance, and other configured transactions.

City treasury pays public workers/services such as police, firefighters, emergency response, courts, sanitation, roads, public transit, inspectors, utilities where public, and other municipal employees.

## Phase 18 — Government

- mayor/council
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

**Upgrade:** corruption investigations, recalls, protests, strikes, political factions.

## Phase 19 — Land & 3D Property

- ground footprint
- vertical air rights/build volume
- optional subsurface rights
- access/ownership/rental permissions
- construction/performance budgets

Supports houses, rooms, apartments, farms, garages, shops, warehouses, clubs, offices, towers, mixed-use buildings, elevated/sky homes within deed limits.

## Phase 20 — Construction

- build mode
- ghost preview
- snapping/grid
- placement validation
- structural/permission checks
- persistent structures
- Builder profession gates real construction where required

**Upgrade:** wiring, plumbing, HVAC, structural damage, inspections, renovation, demolition.

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

Owners pay wages, rent, tax, utilities, inventory, maintenance, security, and advertising. Appropriate workers receive tips.

## Phase 23 — Advertising

- city billboard permits/rent
- monthly fees/tax
- premium locations
- storefront/public displays

**Upgrade:** radio commercials, TV ads, sponsored events, digital billboard schedules, district campaigns.

## Phase 24 — Creator Marketplace

Locked creator rule:

- Metaworld controls base meshes, UVs, material slots/order/assignments, master materials, collision, rigging, gameplay metadata, Nanite/performance settings and technical structure.
- Creators upload approved texture maps only for locked inputs.
- Creator sale proceeds split between creator and configurable Metaworld commission.

**Upgrade:** creator brands, storefronts, collections, followers, reviews, favorites, limited releases, gifting, version management.

## Phase 25 — Music, Movies & Player Media

Authorized creator-owned/licensed media can support music sales, albums, DJs, venues, radio, cinemas, drive-ins, screenings, machinima, documentaries, advertisements, and event recordings.

## Phase 26 — Vehicle Foundation

- ownership/keys/locks
- drivers/passengers
- cargo/storage scaling
- fuel
- maintenance
- damage
- theft
- recovery

**Upgrade:** trailers, towing, insurance, impound, GPS, plates, repairs, customization, racing, taxis, buses, freight/public transport.

## Phase 27 — Voice & Text Communication

Voice channels can include proximity, vehicle, room/property, party, phone/radio, business/security.

Text can include local, DM, party, business, faction, property/room, system/news.

Players choose voice, text, or both.

## Phase 28 — Social Activities

- clubs/bars/restaurants
- parties
- concerts
- dates/weddings/funerals
- malls/parks/beaches/gyms
- sports/community gatherings
- ceremonies

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

## Phase 30 — Metaworld News

News exists through TV, radio, car radio, store/bar/hotel screens, public displays, phones/computers later, publications, emergency alerts and other appropriate channels.

Official verified news remains distinct from player journalism, opinion, rumor, entertainment and advertising.

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

## Phase 33 — Cameras & Evidence

Cameras can be common inside/outside stores, banks, bars, clubs, businesses, streets, parking, apartments and public buildings.

Camera rule:

> The camera records the visible person, not hidden account identity.

A mask means masked visual evidence. Clear face means face evidence.

Performance rule: evidence data may be recorded cheaply; do not render every security camera with continuous SceneCapture every frame. Live video is activated only where needed.

**Upgrade:** body cams, dash cams, traffic cameras, fingerprints, footprints, ballistics, forensic/DNA-style evidence if desired, chain-of-custody, evidence lockers, detectives.

## Phase 34 — Police & Courts

- patrol/dispatch
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

## Phase 36 — Destruction

- breakable doors/windows/fences/interiors
- object state transformations
- controlled Chaos/Geometry Collection use
- vehicle/property damage

Destruction must obey physics/performance budgets.

## Phase 37 — Player Needs & Survival

- Health
- Stamina
- Hunger
- Thirst
- Fatigue
- Mana
- temperature/injuries/sickness/pain later where fun

## Phase 38 — Food & Cooking

- farming/groceries
- cooking/recipes
- restaurants
- food quality
- spoilage/refrigeration
- Chef profession
- delivery

## Phase 39 — Healthcare

- hospitals/clinics
- doctors/nurses
- ambulances
- treatment/rehabilitation
- medical bills
- supernatural medicine

**Upgrade:** insurance, specialist care, emergency rooms, blood banks and other systemic healthcare.

## Phase 40 — Magic

- mana
- spells
- enchantments
- status effects
- magical equipment
- magical locations/events
- skill trees/professions

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

## Phase 45 — Diplomacy

Relationship states can include alliance, trade agreement, peace, tension, hostility, defensive pact, ceasefire, truce, occupation and war.

**Upgrade:** treaties, ambassadors, border permissions, sanctions, safe passage, negotiated peace.

## Phase 46 — War

War remains inside the living persistent world.

It can affect borders, checkpoints, travel, property, businesses, prices, shortages, jobs, taxes, security, refugees, news, deaths, inheritance and territory.

No separate disconnected war lobby is required.

## Phase 47 — Real-Time Calendar

Real elapsed time drives days/weeks/months/years and economic obligations such as bills, rent, taxes, payroll, permits, elections, contracts, estate windows and seasonal events.

## Phase 48 — Day/Night

- sunrise/sunset
- moon/stars
- shop schedules
- nightlife
- NPC sleep/work
- street lights
- crime patterns
- vampire behavior

## Phase 49 — Weather & Climate

- clear/cloud/rain/storm/fog/wind
- heat/cold
- snow/ice where appropriate
- regional climate

Weather affects driving, survival, utilities, power, crops, visibility, fires, businesses, NPC schedules and world events.

## Phase 50 — World Partition / HLOD

Large Earth regions use streaming/HLOD so players never pay full simulation/rendering cost for the entire world at once.

## Phase 51 — Procedural Content Generation

PCG can support vegetation, roadside dressing, rocks, rural variation, forests and large-scale environment dressing while important locations remain deliberately designed.

## Phase 52 — Systemic NPCs

Important NPCs can have identity, home, job, profession, schedule, needs, health/stamina/mana, skills, inventory, money, relationships, reputation, personality, goals, ownership and legal state.

## Phase 53 — NPC Intelligence

- StateTree
- Smart Objects
- significance-aware perception
- event-driven reasoning
- schedules/goals/needs
- emergency reactions
- same world capability rules as players wherever practical

## Phase 54 — NPC Population LOD

- nearby critical NPC: full simulation
- nearby ordinary NPC: reduced expensive logic
- distant NPC: lightweight state simulation
- unloaded NPC: data record + timestamp/event simulation only

Mass-based systems may be evaluated later but must not violate the Blueprint-first rule or become a required dependency until proven suitable.

## Phase 55 — Companion Teams

Recruit/employ NPC guards, mechanics, medics, drivers, builders, farmers, cooks, managers, scouts, security and other roles.

Players can assign tasks, budgets, equipment, permissions, schedules, vehicles, storage and emergency rules.

## Phase 56 — Optional AI NPC Gateway

Optional local/external AI can improve selected NPC dialogue/planning, but normal NPC gameplay must function without paid AI.

AI chooses high-level intent; Metaworld Blueprint systems validate and execute actual actions.

## Phase 57 — World Event Director

Contextual events can include zombie outbreaks, robberies, blackouts, fires, storms, faction attacks, supernatural incidents, protests, political events, supply shortages and war declarations.

## Phase 58 — Zombies & Threat Systems

Threats can reach houses, clubs, stores, hospitals, police stations, streets, farms, businesses and other places. No magical safe-zone immunity.

## Phase 59 — Authoritative Multiplayer

Server authority governs money, inventory, combat outcomes, death, ownership, property, evidence, tax, jobs, businesses, vehicles and other critical state.

## Phase 60 — Replication Scaling

Use relevancy/dormancy/update-rate reduction/compact state so clients do not receive every NPC, camera, business, property and vehicle in the world.

Evaluate UE5.8 replication options such as standard replication, Replication Graph and Iris only after Blueprint workflow and production suitability are verified.

## Phase 61 — Smoothness Program

Primary target: stable 60-FPS-class gameplay on recommended PC hardware where practical, with stable frame pacing prioritized over peak FPS.

Every major system has CPU/GPU/network/memory/significance budgets.

## Phase 62 — Nanite-First Rendering

Nanite default for compatible buildings, roads, rocks, props, furniture, creator base meshes, environment assets, suitable foliage, Geometry Collections, landscape workflows, compatible vehicle parts and compatible skeletal assets.

Morph-dependent body/face meshes remain approved exceptions when necessary.

## Phase 63 — Lumen / Lighting Scalability

Quality tiers can scale Lumen, shadows, reflections, volumetrics and related settings without changing gameplay correctness.

## Phase 64 — MegaLights

Use where appropriate for dense city/nightlife/local-light scenes, subject to profiling and quality tiers.

## Phase 65 — Animation Budgeting

Animation cost is significance-aware. Local player and important nearby characters receive priority; crowd/distant characters reduce update rate, IK, facial detail and other expensive layers.

## Phase 66 — Shader Hitch Prevention

Integrate PSO precaching and hitch analysis early enough that new materials/effects do not create recurring runtime shader stalls.

## Phase 67 — User Interface

UI for inventory, character creator, map, banks, jobs, professions, skills, businesses, property, communications, news, police tools, creator systems and other game domains.

## Phase 68 — Accessibility

- keyboard/mouse/controller
- full rebinding
- subtitles
- text alternative to voice
- per-player voice volume/mute/block
- UI scaling
- readable text
- color accessibility
- camera shake controls
- motion blur controls
- FOV controls where practical

## Phase 69 — Worst-Case Performance Test Worlds

Required stress tests include:

- downtown traffic + pedestrians + rain + night lighting
- busy nightclub + voice + dancing + screens + security
- zombie attack during crowded event
- police response + cameras + vehicles + news
- war/combat/destruction scene
- dense property with many owned items
- creator marketplace/business district

A feature is not complete because it works in an empty test map.

## Phase 70 — Wildlife & Animals

Future expansion: wildlife, pets, guard dogs, farm animals, hunting, fishing, ownership and veterinary gameplay.

## Phase 71 — Agriculture

Future expansion: crops, livestock, food supply chains, grocery businesses, restaurants and agricultural professions.

## Phase 72 — Education

Future expansion: profession schools, universities, training centers, certifications, mentorship and skill instruction.

## Phase 73 — Public Transportation

Future expansion: buses, taxis, trains, stations, transit jobs and fares.

## Phase 74 — Insurance

Future expansion: vehicle, property, business, health and cargo insurance. Insurance must not become magical instant replacement of all loss.

## Phase 75 — Tourism & Entertainment

Future expansion: hotels, resorts, attractions, beaches, arenas, festivals, concerts, tourism businesses and events.

## Phase 76 — Expanded Religion & Belief Systems

Future expansion: religions, temples/churches/orders, ceremonies, faith reputation, player leadership, supernatural belief responses and social/political effects.

## Phase 77 — Legacy / Long-Term Player Goals

Metaworld does not need a single final boss/end screen.

Long-term accomplishments can include becoming mayor, business elite, famous creator/musician, notorious criminal, legendary builder/gunsmith, landlord/property owner, faction leader, vampire coven leader, werewolf pack leader, war survivor/hero, historical figure, family founder or community leader.

The world can remember those lives through inheritance, news, museums, monuments, property history and the Event Ledger.

## Phase 78 — Future GrimKoin Buyback

**Far future only. Not active now.**

Do not enable until the economy, anti-fraud/provenance, account security, identity/compliance, payment, tax, jurisdiction and legal systems have been separately reviewed and deliberately approved.

Current development only preserves the ledger/provenance architecture needed so this remains technically possible later.

---

# 5. Approved High-Value Upgrade Map

| Foundation | Approved Upgrade |
|---|---|
| Third-person starter | Master Blueprint + modular Blueprint Components |
| Basic locomotion | Motion Matching + IK + contextual movement |
| Character creator | Full morph system + age + body diversity + clothing fitting |
| Inventory | Persistent Item DNA + container rules |
| Weapons | Universal object capabilities |
| GrimKoin/PromoKoin | Full server-authoritative ledger + provenance |
| Banking | Bank privacy + death settlement + estates/wills |
| Jobs | Profession qualifications + licensing + apprenticeship later |
| City tax | Persistent city treasury + budgets/government |
| Property | 3D parcels + utilities + real-calendar bills |
| Business | Employees + payroll + tax + tips + advertising |
| Vehicles | Cargo + ownership + theft + maintenance + damage |
| Social | Spatial voice + text + living social venues |
| Cameras | Evidence system without omniscient identity or constant SceneCapture |
| News | Event Ledger-driven news throughout world |
| NPCs | StateTree + Smart Objects + population LOD |
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
- one store
- one bar/club
- one police station
- one hospital/clinic
- one rental/apartment building
- one player property
- one buildable home/structure
- one usable vehicle
- GrimKoin + PromoKoin
- VIP purchase architecture stub without future cashout
- banking
- city tax/treasury
- bills/utilities
- inventory + Item DNA
- jobs/professions
- morph character creator
- clothing fitting baseline
- voice/text
- security cameras/evidence
- police investigation
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

`Scale visuals before sacrificing responsiveness`

Final rule:

> Metaworld should feel alive, not heavy. The player should notice the world — not the engine struggling to run it.

---

# 8. Canonical Companion Documents

The Master Roadmap is supported by detailed companion designs in `Docs/`, including:

- `Avatar_Communication_Character_Animation_Architecture.md`
- `Banking_Currency_Custody_Future_Cashout.md`
- `Blueprint_Python_Nanite_Architecture.md`
- `Character_Morph_Customization_System.md`
- `City_Taxation_Jobs_Wealth_Reputation.md`
- `Creator_Marketplace_Texture_System.md`
- `Earth_Property_Vehicles_Media_News.md`
- `Estate_Wills_Inheritance_Succession.md`
- `Free_To_Play_Economy_Media_Business_Threat_Model.md`
- `Living_World_Environment_NPC_AI.md`
- `Performance_Smoothness_FrameTime_Architecture.md`
- `Real_Time_Life_Utilities_Advertising_VIP_GrimKoin_Death_Legacy.md`
- `Security_Cameras_Evidence_Identity.md`
- `Supernatural_Lineages_Vampires_Werewolves.md`

When a companion document contains more detail than this roadmap, the roadmap establishes the approved feature direction and the companion document defines the detailed behavior, unless a later explicit canonical decision supersedes it.
