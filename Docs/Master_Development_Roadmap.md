# Metaworld — Master Development Roadmap

## Vision

Metaworld is a hybrid Unreal Engine 5 title combining social/avatar customization, open-world driving/action, base-building/community management, deep RPG progression/quests, responsive combat, survival pressure, social life, ownership, careers, and a reactive world.

To prevent system entanglement as the project grows, development starts from a clean foundation and proceeds incrementally through modular, component-based, data-driven subsystems.

A core Metaworld design rule is that the world should feel usable rather than decorative. Many physical objects can become tools, improvised weapons, crafting resources, trade goods, construction materials, quest objects, or social props depending on context.

Metaworld does **not** require a primitive or Stone Age progression start. Players enter a developed open world with normal technology and equipment around them, while still being able to improvise with fists, stones, bottles, pipes, bats, furniture, tools, debris, and other physical objects when circumstances demand it.

Metaworld is a life-sim and open-world sandbox, but it must **always remember that it is a game first**. Hunger, thirst, sleep, work, money, social life, and property should create decisions, stories, risk, and opportunity without becoming repetitive chores that overpower the fun.

## Core Player Fantasy

A player should be able to **own almost anything, do almost anything, and become almost anything** within the rules of the world.

Examples include becoming or combining roles such as:

- Fighter
- Survivor
- Farmer
- Builder
- Driver
- Mechanic
- Trader
- Shop owner
- Business owner
- Property owner
- Landlord
- Medic
- Hunter
- Scavenger
- Crafter
- Entertainer
- Club owner
- Security worker
- Criminal
- Law-enforcement-aligned character
- Explorer
- Mercenary
- Community leader
- Social celebrity
- Collector
- Vehicle owner
- Home owner
- Mage / supernatural specialist

These are not rigid character classes. A player's identity should emerge from skills, possessions, reputation, relationships, jobs, businesses, choices, and behavior.

## New-Player Starting Rule

Every new player begins with only the bare minimum needed to survive the first moments of the game:

- 1 food item
- 1 water item

That is it.

The player must find their own path from there through exploration, work, trading, scavenging, cooperation, crime, quests, combat, crafting, business, social connections, or other gameplay systems.

The starting condition should create urgency and possibility without forcing every player through the same tutorial career or progression route.

## Game-First Simulation Principle

Metaworld can simulate many parts of life, but realism must serve gameplay.

Rules:

1. Hunger, thirst, and fatigue create meaningful decisions but should not drain so quickly that players spend all their time maintaining meters.
2. Social activities such as parties, clubs, bars, concerts, gatherings, dates, games, and community events must have real gameplay value rather than being decorative menus.
3. Leisure does not freeze the world. A zombie attack, crime, mission event, fire, blackout, faction conflict, weather event, or other dynamic event can interrupt a party.
4. The world should produce unexpected stories by allowing independent systems to collide.
5. No location should be treated as completely disconnected from the simulation merely because it is a social or leisure location.
6. Difficulty, pacing, and fairness matter more than perfect realism.
7. Player freedom should be broad, but consequences, ownership, law, reputation, cost, risk, and world reaction make choices meaningful.

## Core Player Resources

Metaworld characters should have several distinct resources rather than one generic energy meter.

### Health

- Represents physical life/condition.
- Reduced by injuries, combat, hazards, disease/status effects, and other damage sources.
- Can interact with body-part damage, armor, healing, medicine, and survival systems later.

### Stamina

- Represents short-term physical exertion.
- Used by sprinting, climbing, heavy melee attacks, dodging, blocking, grappling, carrying heavy objects, and other demanding physical actions.
- Regenerates relatively quickly when the player rests or slows down.
- Hunger, thirst, fatigue, injuries, encumbrance, skills, equipment, and status effects can influence maximum stamina or regeneration.

### Mana

- Represents supernatural/magical energy.
- Used by spells, magical abilities, enchanted actions, supernatural skills, and other mana-based systems.
- Regenerates separately from stamina.
- Skills, equipment, consumables, status effects, locations, and world systems can influence mana capacity, regeneration, and cost.
- Mana should not force every player into magic. A player can ignore magic entirely if that is the life/build they want.

### Hunger

- Long-term survival need.
- Food restores hunger and can provide temporary benefits or penalties depending on quality/type.
- Severe hunger can gradually reduce performance, stamina recovery, health recovery, or other systems rather than instantly killing the player.

### Thirst

- Long-term survival need with stronger urgency than hunger.
- Water and other drinks restore thirst.
- Dehydration can affect stamina, health, focus, and recovery.

### Fatigue / Sleep

- Represents the need for rest over longer gameplay periods.
- Sleeping restores fatigue and can improve recovery.
- Beds, homes, hotels, camps, vehicles, shelters, and other locations can provide different rest quality later.
- Fatigue should matter without forcing the player to sleep constantly.

## Core Architecture Principles

1. Keep gameplay domains isolated behind components, subsystems, interfaces, gameplay tags, and data assets.
2. Avoid placing unrelated systems directly inside the player character.
3. Prefer data-driven content over hardcoded item, economy, quest, weapon, skill, spell, or building definitions.
4. Design save/persistence boundaries early so world state and player state remain separable.
5. Keep first-person, third-person, social, combat, vehicle, construction, survival, and magic modes interoperable but decoupled.
6. Build each phase so it can be tested independently before the next major subsystem is introduced.
7. Do not define every usable object as a dedicated weapon class. Define physical properties and capabilities, then let combat, crafting, building, AI, economy, and interaction systems interpret those capabilities.
8. Context determines use. The same hammer can repair, build, break, be traded, or be used in combat without becoming a different fake copy of the item.
9. NPCs and players should use the same object capability rules wherever practical.
10. Economy, ownership, law, reputation, AI, combat, survival, social systems, and world simulation should communicate through clean events/interfaces rather than direct hard dependencies.
11. Player progression should not require rigid classes. Skill trees unlock specialization while preserving hybrid builds and experimentation.
12. Dynamic events should be able to affect social, residential, commercial, wilderness, and mission spaces where appropriate.
13. Time of day and weather must be gameplay state, not presentation-only effects.
14. Ordinary NPC intelligence must function without paid external AI services; model-powered NPC intelligence is an optional enhancement layer.
15. AI models may choose goals, conversation, and plans, but only Metaworld's validated gameplay systems may execute world actions.

---

# Master Development Roadmap

## Phase 1 — Core Modular Pawn & Camera System

Goals:

- Seamless switching between third-person and first-person modes.
- UE5 Enhanced Input mapping setup.
- Baseline locomotion and camera behavior.
- Clean foundation for later social, RPG, driving, combat, survival, magic, and interaction systems.

Current starter implementation:

- `AMyGameCharacter`
- Third-person spring-arm camera
- First-person camera mode using the same camera rig
- Enhanced Input bindings for movement, looking, jumping, and camera toggling

## Phase 2 — Modular Data-Driven Inventory & Economy Subsystem

Goals:

- Item definitions using Unreal data assets / data-driven structures.
- Player inventory containers.
- Player-to-player trading.
- Vendor buying and selling.
- Multi-currency wallet balances.
- Clean separation between item definition, item instance, ownership, condition, and monetary value.
- Support later systems such as clothing, furniture, weapons, tools, vehicles, crafting materials, property, creator goods, and resources through the same ownership foundation.

### Canonical Currency Model

#### GrimKoin

- GrimKoin is the **main currency of Metaworld**.
- It should have meaningful purchasing power.
- It is intentionally harder to earn than PromoKoin.
- Important equipment, meaningful upgrades, larger purchases, valuable resources, property-related costs, vehicles, stronger weapons, substantial ammo purchases, and other high-value goods can require GrimKoin.
- Having enough GrimKoin should matter; the economy should not make major purchases trivial.

#### PromoKoin

- PromoKoin is the **common/easier-to-obtain secondary currency**.
- It should be useful, but have deliberately limited purchasing power.
- It can cover small everyday purchases and low-impact consumables.
- A player may be able to buy a small amount of ordinary ammunition with PromoKoin, but PromoKoin should not provide easy access to decisive combat power, strong weapons, major armor, high-end upgrades, or other fight-changing advantages.
- PromoKoin should remain valuable enough that players do not ignore it, while never replacing GrimKoin as the core economy currency.

### Economy Design Rule

Currency value must be enforced by vendor/item pricing rules and eligibility, not only by making one number larger than another. Some items may accept both currencies at different rates; some may be GrimKoin-only; some everyday goods may be PromoKoin-first.

Recommended modules/components:

- Inventory Component
- Wallet / Economy Component
- Item Definition data assets
- Item Instance records
- Ownership / condition records
- Trade transaction layer
- Vendor interface
- Currency Definition data assets
- Purchase eligibility / pricing policy layer

## Phase 3 — Base-Building & Grid Construction System

Goals:

- Placement line tracing.
- Ghost / preview objects.
- Grid snapping.
- Rotation controls.
- Placement validation.
- Persistent construction state.

Recommended modules/components:

- Build Mode Component
- Placement Validator
- Grid / Snap Utility
- Buildable Definition data assets
- Construction persistence records

## Phase 4 — Universal Combat, Equipment & Object Capability Framework

Metaworld should not treat combat as a narrow list of predefined weapon classes. A weapon is often simply an object being used as a weapon.

Examples include fists, stones, bottles, pipes, bats, chairs, tools, debris, knives, firearms, throwables, and crafted/improvised equipment.

Goals:

- First-person and third-person combat handling.
- Unarmed combat.
- Held-object melee combat.
- Throwing physical objects.
- Firearms and ammunition.
- Ballistics / traces / projectiles.
- Recoil.
- Animation montages.
- Health and damage processing.
- Stamina costs for appropriate physical combat actions.
- Object condition and durability.
- Breakable objects and state transitions.
- Contextual interactions such as swing, throw, block, cut, stab, break, repair, build, harvest, and place.
- AI ability to recognize and use suitable nearby objects when appropriate.

Recommended modules/components:

- Object Capability Component / interface
- Interaction Component
- Combat Component
- Equipment Component
- Health Component
- Damage interfaces
- Physical/Object Definition data assets
- Capability gameplay tags
- Object condition / durability system
- Weapon-specific logic only where genuinely required, such as firearms

## Phase 5 — Player Needs, Survival & Resource Loops

Goals:

- Hunger.
- Thirst.
- Fatigue / sleep.
- Health recovery relationships.
- Stamina capacity and regeneration relationships.
- Food and drink quality/effects.
- Crop growth timers.
- Harvesting.
- Community resources.
- Survival / production loops.
- Persistent timed world state.

Recommended modules/components:

- Player Needs Component
- Attribute / Vitals Component
- Resource Component / subsystem
- Growth Component
- Harvestable interface
- Community resource subsystem
- Persistent timer/state records
- Food / Drink Definition data assets

## Phase 6 — Skill Trees, Attributes & RPG Progression

Metaworld should use open specialization rather than hard character classes.

Goals:

- Modular skill trees.
- Skill points and/or progression through use, quests, training, achievements, or combinations of these systems.
- Branching skills with prerequisites.
- Cross-tree hybrid builds.
- Passive bonuses and active abilities.
- Physical, mental, social, professional, and supernatural skill families.
- Profession and lifestyle progression without locking the player permanently into one career.

Recommended modules/components:

- Skill Tree Subsystem
- Player Progression Component
- Skill Definition data assets
- Skill Node data assets
- Prerequisite / unlock evaluator
- Attribute modifier system
- Mana / ability-cost integration

## Phase 7 — Social Life, Venues & Dynamic World Events

Social gameplay is a core part of Metaworld, but social spaces remain part of the living game world.

Goals:

- Parties, clubs, bars, concerts, player gatherings, homes/private events.
- Social interactions and entertainment activities.
- Relationships and reputation hooks.
- Venue ownership/business hooks.
- Dynamic events that can interrupt ordinary life.

Possible dynamic interruptions include zombie attacks, crime, faction attacks, fires, blackouts, weather emergencies, police/security incidents, world bosses, supernatural events, supply shortages, and community emergencies.

Recommended modules/components:

- Social Interaction Component
- Venue / Activity subsystem
- Dynamic Event subsystem
- World Event dispatcher
- Reputation / relationship hooks
- NPC population/event hooks
- Property/business integration

## Phase 8 — Mana, Magic & Supernatural Ability Framework

Mana exists as a first-class player resource but magic remains optional for players.

Goals:

- Mana pool and regeneration.
- Mana costs.
- Data-driven spells and abilities.
- Skill-tree integration.
- Status effects.
- Cooldowns where needed.
- Equipment and item modifiers.
- First-person and third-person ability use.
- AI-compatible supernatural abilities.
- World locations/items/events that can affect mana or magic.

Recommended modules/components:

- Mana Attribute
- Ability Component / framework
- Spell / Ability Definition data assets
- Effect / status system
- Cost and cooldown evaluators
- Skill-tree integration

## Phase 9 — Living Earth Environment: Day/Night, Weather & Climate

Metaworld uses a shared world clock and regional environment simulation so the Earth setting changes continuously and affects gameplay.

Goals:

- Server-authoritative date/time/world clock.
- Full day/night cycle.
- Sunrise, sunset, moon, stars, atmosphere, cloud and lighting transitions.
- Regional weather and climate profiles.
- Rain, storms, wind, fog, temperature, snow/ice where appropriate.
- Weather transitions rather than simple random visual toggles.
- Time/weather integration with NPC schedules, shops, nightlife, traffic, zombies, visibility, stealth, driving, crops, fires, power, survival, and dynamic events.
- UE5.8 scalability so high-end visual systems improve presentation without changing simulation rules.

Recommended modules/components:

- World Clock Subsystem
- Environment/Weather Subsystem
- Region/Climate definitions
- Time/weather event dispatcher
- Day Sequence adapter/presentation layer
- Sky Atmosphere / Volumetric Cloud integration
- Lumen/MegaLights scalability integration
- World Partition / HLOD environment integration

Detailed design: `Docs/Living_World_Environment_NPC_AI.md`

## Phase 10 — Systemic NPC Life & World Population

Every important NPC should have systemic identity and behavior rather than existing only as a static quest dispenser.

Goals:

- NPC identity, home, job, schedule, needs, skills, inventory, money, relationships, reputation, personality and goals.
- Sleep/work/leisure schedules affected by world conditions.
- Smart Object use for beds, chairs, shops, workstations, vehicles, doors, venues and other interactions.
- StateTree-based local behavior.
- Background/population simulation for distant NPCs.
- LOD transition between lightweight simulation and full local agents.
- Emergency reactions to zombies, crime, fire, storms and player actions.
- NPC use of the same object capability, economy, property, law and world-event systems as players wherever practical.

Recommended modules/components:

- NPC Identity/State record
- NPC Needs/Goals component
- NPC Schedule subsystem
- StateTree behavior layer
- Smart Object integration
- NPC memory/relationship hooks
- Population LOD/simulation layer
- Event Bus integration

Detailed design: `Docs/Living_World_Environment_NPC_AI.md`

## Phase 11 — Advanced Companion Teams & Optional AI Model Gateway

Players can recruit/purchase/employ capable NPCs and build specialized teams. External or local AI models may enhance selected NPCs, but ordinary NPCs must remain functional without paid APIs.

Goals:

- Player companion/team commands.
- Specialized NPC roles such as guard, medic, mechanic, driver, builder, farmer, scavenger, trader, manager, cook, scout or mage.
- Base/home, vehicle, storage, equipment, budget, schedule, emergency and combat permissions.
- Team coordination and task delegation.
- Persistent memory and progress reporting.
- Optional local/external model integration for richer dialogue, planning and reasoning.
- Shared AI provider gateway: multiple NPC agents can use one configured provider connection subject to provider limits and player budgets.
- Per-NPC persona, memory, model choice, autonomy, context/token/cost budget and permissions.
- Secure credential isolation.
- Offline/rate-limit fallback to normal Metaworld NPC intelligence.
- AI model selects high-level intent; validated Metaworld gameplay systems execute actual actions.

Recommended modules/components:

- Companion/Team Subsystem
- NPC Command/Task system
- AI Gateway
- AI Agent profile
- Per-NPC memory namespace
- Permission/capability validator
- Cost/usage budget tracker
- Local-model adapter
- External-provider adapters
- Fallback behavior layer

Detailed design: `Docs/Living_World_Environment_NPC_AI.md`

---

# Development Order After Phase 1

The preferred order is:

1. Inventory + GrimKoin/PromoKoin economy foundation
2. Construction / base-building
3. Universal object capabilities + combat + equipment
4. Player vitals, stamina, hunger, thirst, fatigue + survival resources
5. Skill trees + RPG progression
6. Social venues + dynamic world events
7. Mana + magic/supernatural abilities
8. World clock + day/night + regional weather/climate
9. Systemic NPC schedules + population simulation
10. Advanced companion teams + optional AI-model enhancement

This order creates shared data, ownership, currency, physical-object, attribute, progression, environment, event, and NPC foundations before expensive model-powered intelligence is introduced.

# Current Status

- Repository initialized.
- UE5 C++ module foundation established.
- Phase 1 starter character code added as the first gameplay baseline.
- GrimKoin and PromoKoin economy roles defined.
- Universal object-as-potential-weapon philosophy adopted for later combat architecture.
- New-player start defined as one food item plus one water item.
- Hunger, thirst, fatigue/sleep, stamina, health, and mana defined as distinct player resources.
- Open skill-tree / no-rigid-class progression philosophy defined.
- Social venues and dynamic world interruptions established as core design principles.
- Broad player freedom established: own, do, and become almost anything within systemic world rules.
- Earth-based property, vehicle storage, spatial media, and factual living-news design documented.
- UE5.8 established as the target engine version.
- Day/night, regional weather/climate, and environment-to-gameplay integration added to the roadmap.
- Systemic NPC life, schedules and layered population simulation added to the roadmap.
- Optional AI-model-enhanced companion teams added with a shared gateway/fallback architecture rather than requiring one API key per NPC.
