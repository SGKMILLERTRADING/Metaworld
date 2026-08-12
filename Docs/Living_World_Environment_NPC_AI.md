# Metaworld — Living World, Environment & Intelligent NPC Architecture

## Canonical Engine Target

Metaworld targets **Unreal Engine 5.8**.

The project should use the strongest UE5.8 features that are appropriate for the player's hardware, but no single high-end rendering feature should be treated as mandatory for every machine. Metaworld must be designed around scalability profiles, device benchmarking, and graceful fallback so the same world systems still function when visual quality is reduced.

The game is a persistent Earth-based world. Time, weather, lighting, NPC routines, traffic, businesses, survival, crime, zombies, social life, property, crops, media, and world events should all react to the same shared simulation rather than existing as disconnected effects.

---

# 1. Authoritative World Clock

Metaworld needs a server-authoritative world clock shared by gameplay systems.

The world clock should track:

- Date
- Time of day
- Day/night state
- Sunrise/sunset information
- Region/time-zone data where needed
- Season/calendar state where enabled
- Scheduled world events
- Time scale

The exact real-time-to-game-time ratio should remain configurable while development is underway. The clock must be data-driven rather than hardcoded so different servers/regions/events can use different pacing if required later.

## Day/Night Gameplay Effects

Day and night are not only lighting changes.

Time of day can influence:

- Sun/moon/sky lighting
- Street lights and building lights
- Shops opening and closing
- Nightclubs and entertainment schedules
- NPC jobs and sleep routines
- Traffic density
- Public transportation schedules
- Crime opportunities
- Police/security presence
- Zombie activity
- Wildlife behavior
- Mission availability
- Player visibility/stealth
- Temperature
- Crop/growth simulation
- Electricity demand
- Social events
- Religious/cultural events
- News/broadcast schedules

A town should feel materially different at 2 PM, 10 PM, and 4 AM.

## Recommended Unreal Integration

- Metaworld World Clock Subsystem as the authoritative gameplay source
- UE Day Sequence or a Metaworld-controlled adapter for sun/moon/sky presentation
- Sky Atmosphere
- Volumetric Clouds
- Sky Light
- Directional lights
- Lumen or scalable fallback settings
- MegaLights where hardware/profile permits
- World Partition for large-world streaming

Experimental engine features must sit behind Metaworld interfaces so they can be replaced if Epic changes them.

---

# 2. Dynamic Weather & Climate

Weather must be regional and systemic, not one server-wide visual toggle.

Possible weather states include:

- Clear
- Partly cloudy
- Overcast
- Light rain
- Heavy rain
- Thunderstorm
- Fog
- High winds
- Heat wave
- Cold snap
- Snow/ice in appropriate regions
- Severe storms and special world events later

## Weather Data

Each region/biome can define:

- Climate profile
- Temperature range
- Humidity
- Rain probability
- Wind profile
- Storm probability
- Seasonal modifiers
- Snow threshold
- Fog probability
- Weather transition rules

Weather should transition through fronts/states rather than snapping randomly wherever practical.

## Weather Gameplay Effects

Weather can affect:

- Road grip and braking
- Vehicle visibility
- Headlights/wipers
- Walking/running stamina cost
- Clothing usefulness
- Body temperature/status effects later
- Fire spread/suppression
- Crop watering/growth
- Outdoor businesses/events
- NPC schedules
- Zombie/NPC perception
- Sound propagation/ambient masking where appropriate
- Electrical outages
- Flooding or blocked routes in special events
- Flights/boats if those systems are added
- Player demand for food, fuel, shelter, transport, and services

Weather should create gameplay opportunities rather than merely punish the player.

Example: a storm may close roads, increase towing/repair demand, push NPCs into shelters, reduce visibility for criminals, damage power lines, and create a news event.

---

# 3. Rendering & Performance Philosophy

Metaworld should use high-end UE5.8 presentation where the player's PC can handle it without designing the simulation around one graphics tier.

Target capability stack can include:

- Nanite-compatible environment assets where appropriate
- Lumen dynamic GI/reflections
- MegaLights for dense dynamic lighting where supported
- Virtual Shadow Maps where appropriate
- Volumetric Clouds and fog
- Niagara weather/particle effects
- PCG for scalable world dressing/generation workflows
- World Partition + HLOD for large Earth environments

## Metaworld Scalability Profiles

The project should provide quality tiers such as:

- Performance
- Balanced
- High
- Ultra
- Custom

A startup benchmark or settings assistant can recommend a profile based on the player's hardware.

Simulation correctness must not depend on Ultra graphics. A storm is still a storm on Performance mode; only its rendering complexity changes.

---

# 4. Every NPC Must Have a Brain

No important Metaworld NPC should exist only to stand still and repeat one line.

Every NPC should have a minimum systemic identity including as appropriate:

- Unique ID
- Name/identity
- Home or homelessness state
- Job/profession
- Schedule
- Needs
- Health/stamina/mana where applicable
- Skills
- Inventory
- Money/resources
- Faction/community
- Reputation
- Relationships
- Personality traits
- Goals
- Fears/preferences
- Memory/state history
- Legal status
- Ownership/permissions
- Current task
- Emergency reactions

Not every background NPC needs an expensive language model. Intelligence is layered.

---

# 5. Hybrid NPC Intelligence Tiers

## Tier 0 — Population Simulation

For distant/background citizens.

Use lightweight simulation for:

- Population counts
- Jobs
- commuting
- sleep/work cycles
- economy participation
- births/deaths only if later designed
- migration
- resource consumption
- scheduled activities

These NPCs do not require full Actors or per-frame thinking while far from players.

## Tier 1 — Local Systemic NPC

When an NPC is near a player or relevant event, it becomes a richer world agent using Unreal gameplay AI.

Possible stack:

- StateTree
- Smart Objects
- Navigation
- Perception
- Gameplay Tags
- Metaworld capability system
- Interaction system
- Event bus
- Relationship/reputation data

This tier should already be capable of living, working, eating, sleeping, fleeing, fighting, driving, shopping, using buildings, using objects, reacting to crimes, and responding to emergencies without any external AI model.

## Tier 2 — Persistent Companion / Specialist NPC

Important companions, employees, purchased/recruited NPCs, business managers, guards, mechanics, medics, drivers, builders, farmers, scavengers, mages, or similar characters receive deeper planning and memory.

They can:

- Accept player objectives
- Break objectives into tasks
- Coordinate with other NPCs
- Manage assigned inventory/storage
- Use vehicles
- Protect property
- Perform jobs
- Report progress
- Remember relationships/events
- Learn preferences within allowed progression rules
- Make bounded autonomous decisions

## Tier 3 — Optional AI-Model Enhanced NPC

Selected NPCs may optionally connect to external or local AI models for richer conversation, planning, memory summarization, negotiation, role-play, team coordination, or creative problem solving.

This is an enhancement layer, not the NPC's only brain.

If the model is unavailable, rate-limited, too expensive, offline, or disabled, the NPC falls back to its Tier 1/Tier 2 Metaworld intelligence and continues functioning.

---

# 6. AI Model Gateway — Do Not Require One API Key Per NPC

The architecture should not require a separate provider API key for every AI-enhanced NPC.

Instead:

Player / Server
    -> AI Provider Connection(s)
        -> Metaworld AI Gateway
            -> NPC Agent A
            -> NPC Agent B
            -> NPC Agent C
            -> NPC Agent D

One provider credential/account can service multiple NPC agents subject to that provider's usage limits and the player's configured budget.

A player may connect additional provider accounts/keys if they choose or if provider limits make that useful, but buying another NPC should not automatically mean buying another API key.

## Per-NPC AI Configuration

Each enhanced NPC can still have its own:

- Persona
- Role
- Memory namespace
- Tool permissions
- Context budget
- Response budget
- Daily/monthly token or cost budget
- Allowed model/provider
- Planning frequency
- Autonomy level
- Safety/permission boundaries

The gateway routes requests using the shared provider connection while accounting for each NPC separately.

## Key Security Rule

Provider credentials must be treated as secrets.

They should never be replicated through ordinary gameplay state or exposed to other players/NPCs. The AI Gateway should own credential use, while NPCs only receive approved AI responses/tool results.

Local-model support should be possible later so players can run enhanced NPC intelligence without paid external API usage if their hardware allows it.

---

# 7. AI Models Choose Intent — Metaworld Executes Actions

External/local language models must not directly manipulate Unreal actors every frame.

The model can produce high-level intents such as:

- "Guard the west entrance."
- "Find food for the team."
- "Repair the truck."
- "Take the injured player to the hospital."
- "Buy building supplies under this budget."
- "Prepare the house for the storm."
- "Coordinate the group during the zombie attack."

The Metaworld gameplay layer then validates the request and executes legal actions through capabilities, StateTrees, Smart Objects, inventory, economy, navigation, permissions, and world rules.

Example:

Player request
-> Companion planner
-> Intent: Acquire 4 food + 4 water
-> Permission/budget check
-> Search known shops/storage
-> Plan route
-> Drive/walk
-> Purchase/collect through real economy
-> Return
-> Store items
-> Report result

The model cannot simply invent food, teleport, bypass locks, spend money the player does not own, or use an ability the NPC has not learned.

---

# 8. NPC Memory & World Awareness

Important NPCs should remember meaningful facts without storing every frame of gameplay.

Memory categories can include:

- Player relationships
- Orders/promises
- Jobs completed
- Crimes witnessed
- Attacks/rescues
- Property ownership
- Business relationships
- Religious/faction relationships
- Important conversations
- Places discovered
- Team members
- Preferred equipment
- Major world events

Memories should reference the same verified world-event system used by Metaworld News where possible.

This creates consistency:

A companion who survived a famous nightclub zombie attack can remember it, the news can report it, the event ledger can archive it, and a future monument can reference it — all from the same underlying event record.

---

# 9. NPC Schedules Make Day/Night Matter

NPC intelligence and the world clock must be connected.

Example citizen schedule:

06:30 Wake
07:00 Eat
07:30 Drive to work
08:00 Work
12:00 Lunch
13:00 Work
17:00 Shop/travel
19:00 Social/family/leisure
23:00 Sleep

This is not a rigid script. Weather, danger, hunger, crime, player interaction, job loss, injury, emergencies, transport failure, relationships, parties, and zombie attacks can interrupt the schedule.

A smart NPC should have a plan, not a prison.

---

# 10. Player-Owned / Recruited NPC Teams

Players can eventually build highly capable teams around themselves.

Examples:

- Driver
- Guard
- Medic
- Mechanic
- Builder
- Farmer
- Scavenger
- Trader
- Business manager
- Security officer
- Mage
- Scout
- Cook
- Logistics worker

The player should be able to assign:

- Home/base
- Bed/room
- Vehicle access
- Storage access
- Equipment permissions
- Spending budget
- Work area
- Schedule
- Emergency behavior
- Combat rules
- Team hierarchy
- AI autonomy level

A rich player might build a highly specialized AI-assisted team, while another player can remain solo or use ordinary non-model NPCs.

AI enhancement must provide intelligence/convenience, not magical rule-breaking power.

---

# 11. Living World Dependency Chain

World Clock
    -> Day/Night
    -> Weather/Climate
    -> Lighting/Visibility
    -> NPC Schedules
    -> Traffic/Businesses
    -> Social Life
    -> Crime/Law
    -> Zombies/Threats
    -> Survival/Resources
    -> Economy
    -> Dynamic Events
    -> Event Ledger
    -> Metaworld News
    -> NPC Memory
    -> Player History

This is the goal: the same underlying world state drives many systems, making Metaworld feel alive because systems react to one another rather than because scripted events pretend the world is alive.

---

# 12. Recommended Development Placement

These features should be integrated into the master roadmap as later foundational phases:

## Environment Foundation

- World Clock
- Day/night presentation
- Regional weather
- Climate data
- Environment gameplay effects
- World Partition/scalability integration

## NPC Simulation Foundation

- NPC identity/state data
- Schedules
- Needs
- StateTree behavior
- Smart Object use
- LOD/background simulation
- Persistent relationships/memory hooks

## Advanced NPC Team & AI Gateway

- Companion commands
- Team coordination
- Permission system
- AI Gateway
- Optional local/external models
- Per-NPC AI budgets
- Memory summarization
- Fallback/offline behavior

Environment and base NPC simulation must work first. AI-model enhancement comes later so Metaworld never depends on paid APIs just to make ordinary NPCs function.
