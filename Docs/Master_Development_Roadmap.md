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

Examples include:

- Fists and kicks
- Stones
- Bottles
- Pipes
- Bats
- Chairs and furniture
- Tools
- Debris
- Knives and melee weapons
- Firearms
- Throwables
- Crafted/improvised equipment

The player does not begin in a Stone Age progression tier; improvised combat is a persistent world capability available alongside conventional equipment.

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

### Universal Object Capability Principle

Objects should expose capabilities and physical/data properties instead of being duplicated into isolated gameplay categories.

Example capability tags may include:

- `Capability.Pickup`
- `Capability.Carry`
- `Capability.Throw`
- `Capability.Swing`
- `Capability.Block`
- `Capability.Stab`
- `Capability.Cut`
- `Capability.Break`
- `Capability.Repair`
- `Capability.Dig`
- `Capability.Harvest`
- `Capability.Place`
- `Capability.Consume`
- `Capability.Craft`

Relevant object properties can include mass, material, hardness, dimensions, shape, grip/handling, durability, condition, ownership, value, and world persistence.

Damage should ultimately be able to consider object properties, attack/use type, velocity, character ability, hit location, armor, and object condition rather than relying exclusively on one hardcoded `Damage` number.

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
- Physical skills that can affect stamina use, carrying, melee, shooting, movement, crafting, survival, and work.
- Mental/social skills that can affect trading, persuasion, business, leadership, reputation, crafting, learning, and other systems.
- Magic/supernatural trees that use Mana.
- Profession and lifestyle progression without locking the player permanently into one career.

Possible skill families include:

- Strength / Athletics
- Endurance / Survival
- Melee
- Firearms
- Defense
- Stealth
- Driving
- Mechanics
- Building / Construction
- Crafting
- Farming
- Cooking
- Medicine
- Trading / Commerce
- Business / Management
- Social / Charisma
- Leadership
- Scavenging
- Magic / Mana disciplines
- Specialized professions added later

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

- Parties.
- Clubs.
- Bars.
- Concerts.
- Player gatherings.
- Homes and private events.
- Social interactions.
- Entertainment activities.
- Relationships and reputation hooks.
- Venue ownership/business hooks.
- Dynamic events that can interrupt ordinary life.

Example emergent scenario:

> Players are partying in a club when a zombie attack begins outside, breaches the venue, and turns a social night into an emergency survival event.

The party system does not need special zombie code. The venue, AI, threat, combat, law/security, NPC, and event systems should be able to interact through shared world events and interfaces.

Possible dynamic interruptions include:

- Zombie attacks
- Crime
- Faction attacks
- Fires
- Blackouts
- Weather emergencies
- Police/security incidents
- NPC disputes
- World bosses or supernatural events
- Mission/event chains
- Supply shortages
- Community emergencies

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

This order creates shared data, ownership, currency, physical-object, attribute, progression, and event foundations before systems depending on them become complex.

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
