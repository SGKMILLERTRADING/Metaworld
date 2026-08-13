# Metaworld — Food, Family & NPC Needs, Community Ranks and Elected Leadership

**Status:** Canonical / Approved

## Canonical Principle

Metaworld is a living society. Players are not the only characters with needs, and money is not the same thing as social rank or public authority.

Core rules:

> Player-owned/recruited AI NPCs have real survival needs and must be provisioned.

> A household/family must be fed. A spouse or dependent NPC is not a decorative object that ignores hunger.

> Food is a major recurring economic need and should have meaningful cost/value.

> GrimKoin can buy goods, services, advertising, property, security, campaigns, and influence attempts — but it cannot directly buy official rank.

> Major leadership and public rank comes from service, reputation, eligibility, trust, and community/organizational votes or approved civic processes.

---

# 1. Food Is a First-Class Economy

Food is not a trivial cosmetic consumable.

Food supports:

- Players
- Player families/households
- Spouses
- Dependents where supported
- Player-owned/recruited NPC companions
- Employees/teams where the owner provides meals or rations
- NPC households
- Restaurants
- Grocery stores
- Farms
- Hospitals
- Hotels
- Clubs/events
- Military/faction operations where later supported
- Emergency shelters

Food should have meaningful price and scarcity without becoming so punitive that ordinary play collapses into constant grinding.

The world should always preserve legitimate ways to earn GrimKoin and obtain food, but players who support larger households or teams take on larger recurring costs.

---

# 2. Household Food Responsibility

If a player creates or joins a family/household, household members have real needs.

Possible household members include:

- Wife/husband/spouse
- Partner where supported
- Children/dependents only if that feature is later deliberately designed
- Elderly/dependent relatives where supported
- Household NPCs
- Live-in employees where contract rules include meals

Household systems can track:

- Food inventory
- Water/drink inventory
- Meal availability
- Household consumption rate
- Refrigerator/pantry storage
- Food spoilage
- Household budget
- Preferred foods/dietary traits later
- Emergency reserves

A player cannot maintain a large family indefinitely with no food supply.

If food runs low, household members can react through:

- Hunger
- Complaints/requests
- Buying food themselves if they have money/permission
- Asking the player for food or money
- Reduced morale/relationship quality
- Leaving to find food where appropriate
- Health/performance consequences if deprivation becomes severe

Relationships should create responsibility as well as social value.

---

# 3. Player-Owned / Recruited NPC Hunger

AI-enhanced NPCs and ordinary recruited NPCs use the same fundamental needs framework.

Being connected to an AI model does not remove physical needs.

A player who recruits a guard, mechanic, medic, driver, manager, builder, cook, farmer, companion, or other NPC must account for that NPC's living needs according to the relationship/contract.

Possible provisioning models:

- Player supplies food directly
- Home/base pantry is shared with team NPCs
- Employer provides meals/rations
- NPC receives wages and can buy food independently if contract allows
- Business provides staff meals
- Team logistics worker maintains supplies

The canonical rule is that the NPC must actually obtain food through the world economy. The game does not silently spawn free food because the NPC belongs to a player.

---

# 4. NPC Need Simulation and Performance

NPC needs must be performance-aware.

Nearby important NPC:
- full hunger state
- can seek food
- can use kitchen/shop/restaurant Smart Objects
- can eat visible inventory items

Distant NPC:
- lightweight hunger/resource simulation

Unloaded NPC:
- store last-fed timestamp, reserves, income and household state
- calculate elapsed need changes when relevant

Do not Tick hunger every frame for every NPC in Metaworld.

---

# 5. Food Supply Chain

Food should connect multiple professions and businesses.

Possible chain:

Farm
-> harvest
-> processor/distributor
-> wholesaler/transport
-> grocery/restaurant
-> player/NPC household

Possible roles:

- Farmer
- Rancher/livestock worker later
- Fisher/hunter later
- Food processor
- Truck driver
- Warehouse worker
- Grocer
- Chef
- Cook
- Server
- Delivery driver
- Restaurant owner
- Hotel operator
- Emergency supplier

Weather, war, road closures, business failure, fuel costs, power outages, crop failure, crime, and political policy can affect food prices and availability.

This makes food a real economic pillar rather than a single survival bar.

---

# 6. Food Price Principle

Food is important and should not be unrealistically cheap.

Price should reflect factors such as:

- Production cost
- Transport cost
- Business wages
- Rent
- Utilities/refrigeration
- City tax
- Scarcity
- Region
- Weather
- War/disruption
- Quality
- Spoilage risk
- Demand

Food should remain obtainable through work and low-entry jobs. The goal is meaningful budgeting, not unavoidable starvation for active players.

A player supporting only themselves has lower food costs than a player supporting:

- spouse/family
- multiple companions
- guards
- business employees whose contracts include meals
- large events

Wealth can therefore support larger social structures, but money does not replace the need to organize supply.

---

# 7. Public Leadership Is Community-Based

Metaworld supports high public leadership titles and government types, potentially including:

- Mayor
- Governor
- President
- King
- Queen
- Council member
- Regional leader
- Faction leader
- Other locally defined titles

The exact title can vary by government/city/territory, but top legitimate public leadership is not purchased as a shop rank.

A character must first meet eligibility rules, then gain support through the relevant community process.

Possible eligibility factors:

- Citizenship/residency
- Minimum reputation
- Clean-enough legal status where required
- Service history
- Prior leadership experience where required
- Faction/community standing
- Time in city/region
- Required profession/civic qualifications where appropriate

Then the community votes or uses another approved collective selection process.

Even kingdom-style titles such as King or Queen are community-recognized/elected positions in the current Metaworld design rather than automatic real-money/GrimKoin purchases.

Hereditary succession is not automatic unless a future explicit rule is approved.

---

# 8. GrimKoin Cannot Directly Buy Rank

Canonical rule:

> There is no legitimate `Pay GrimKoin -> Become Captain/President/King/Queen` progression path.

GrimKoin cannot directly raise:

- Police rank
- Government rank
- Military/faction command rank where merit/community rules apply
- Judicial authority
- Public office
- Community leadership reputation

Money can support a campaign or organization through legitimate systems such as:

- advertising
- campaign events
- staff
- transportation
- venues
- security
- public projects
- donations where rules permit

But the underlying vote, reputation, eligibility and service systems still decide whether the character earns the position.

---

# 9. Career Rank Is Earned

Police is the clearest example.

Possible rank progression:

Officer
-> Senior Officer
-> Sergeant
-> Lieutenant
-> Captain
-> Higher command where city structure supports it

The exact rank names remain configurable.

Promotion can consider:

- Time/service
- Successful calls/cases
- Evidence quality
- Lawful conduct
- Community trust
- Department reputation
- Leadership behavior
- Training/certification
- Complaints/discipline
- Corruption history
- Fellow officer/supervisor assessment
- Community or department vote where configured

A player who is a terrible police officer, abuses the city, ignores citizens, fabricates cases, or has very poor trust should not simply grind money and purchase Captain.

A great officer who protects the city and earns trust has a real path upward.

The same merit/trust pattern can apply to other structured careers.

---

# 10. Community Voting

Voting should be a real persistent civic system.

Possible election flow:

Eligibility window
-> candidates register
-> campaign period
-> debates/events/advertising
-> voters evaluate reputation/history/platform
-> voting window
-> authoritative vote count
-> result certified
-> office/rank granted
-> term begins

Voting records should protect ballot secrecy where appropriate while keeping the authoritative count auditable/server-controlled.

Possible voters:

- Eligible player citizens
- Eligible NPC citizens according to simulation rules
- Organization members for internal ranks
- Profession members for professional leadership roles where appropriate

The exact electorate depends on the office.

---

# 11. NPC Votes Matter

NPC citizens should not be mindless guaranteed votes.

NPC voting behavior can consider what they reasonably know about candidates:

- public service history
- city safety
- taxes
- jobs
- infrastructure
- scandals
- news
- corruption evidence
- faction/lineage relations
- promises/platform
- personal relationships
- personality
- economic conditions
- war/security concerns

They must not read hidden backend facts that were never publicly revealed.

An NPC can vote differently from another NPC even when both live in the same city.

---

# 12. Campaigns and Public Reputation

Campaigning can create real gameplay:

- rallies
- debates
- speeches
- interviews
- TV/radio advertisements
- billboards
- community events
- door-to-door campaigning later
- endorsements
- public projects
- fundraising where allowed

Metaworld News can report:

- candidate registration
- debates
- scandals
- endorsements
- polls if implemented
- election results
- contested results
- recalls

The Event Ledger records authoritative election outcomes.

---

# 13. Corruption / Buying Influence

GrimKoin cannot legitimately buy rank, but corrupt behavior can exist as risky gameplay if enabled.

A rich player may attempt to:

- bribe a voter
- bribe an official
- secretly fund influence operations
- buy favorable advertising
- pay intermediaries
- pressure businesses/employees
- exchange favors

This is not a guaranteed `buy votes` mechanic.

Possible consequences:

- Voter refuses
- Voter accepts but votes differently
- Witnesses/cameras capture evidence
- Financial ledger raises suspicious flags
- Police investigation
- Court case
- Disqualification
- Removal from office
- Reputation collapse
- News scandal
- Fines/jail
- Faction retaliation

A player may try to buy out everyone, but that becomes an emergent corruption strategy with enormous risk/cost — not the official progression system.

---

# 14. Leadership Has Responsibility

Winning office is not simply a permanent title.

Leaders may be responsible for:

- Budgets
- Taxes
- Public payroll
- Infrastructure
- Security
- City services
- Laws/policy
- Emergency decisions
- War/peace decisions where authority permits
- Public contracts
- Utility policy
- Food/emergency reserves later

Bad leadership affects the actual city.

A leader can lose support because of:

- poor services
- high crime
- corruption
- excessive taxes
- unemployment
- shortages
- war failures
- broken infrastructure
- scandals

Possible removal systems later:

- election loss
- recall
- impeachment/court process where government type supports it
- internal faction vote
- death/permanent death

---

# 15. Rank and Wealth Are Separate Reputation Axes

Metaworld tracks wealth and public trust separately.

A character can be:

- Rich but hated
- Poor but respected
- Rich and respected
- Powerful business owner with no political office
- Police captain with modest personal wealth
- Popular president with limited wealth
- Wealthy candidate who loses the election

This preserves the core rule that GrimKoin has real power in the economy without becoming an XP potion for social authority.

---

# 16. Blueprint Architecture

Possible Blueprint systems:

- `BPC_MW_Needs`
- `BPC_MW_Household`
- `BPC_MW_Employment`
- `BPC_MW_Reputation`
- `BPC_MW_CivicEligibility`
- `BPC_MW_ProfessionalRank`
- `BPC_MW_Candidate`
- `BPI_MW_FoodConsumer`
- `BPI_MW_Voter`
- `BPI_MW_RankAuthority`
- `BPSS_MW_Elections`
- `BPSS_MW_Government`
- `BPSS_MW_FoodEconomy`

Data definitions can include:

- Food Definition
- Household Contract/Role
- Employment Contract
- Rank Definition
- Promotion Requirement
- Office Definition
- Election Definition
- Voter Eligibility Rule
- Government Type

All critical votes, ranks, economy transfers and public-office state must be server-authoritative.

---

# 17. Performance Rule

Do not simulate every household meal or election decision every frame.

Use:

- scheduled hunger checks
- timestamps
- household inventory deltas
- aggregate distant NPC consumption
- event-driven promotion evaluations
- scheduled elections
- cached reputation values
- data-only unloaded NPC state

Full meal/restaurant animations and detailed decision-making only activate when relevant to nearby gameplay.

---

# 18. Core Principle

Metaworld gives wealth real economic power, but it does not let wealth replace community.

A player who wants a family must support that family.

A player who recruits NPCs must account for their needs.

A city needs food, workers and supply chains.

A police officer earns respect and rank through service.

A leader earns office through community support.

A rich player may try to influence the system, even corruptly, but GrimKoin is never the official rank-up button.

> Food keeps people alive. Service builds reputation. Community grants legitimate authority.