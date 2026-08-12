# Metaworld — Master Development Roadmap

## Vision

Metaworld is a hybrid Unreal Engine 5 title combining social/avatar customization, open-world driving/action, base-building/community management, deep RPG progression/quests, and responsive combat.

To prevent system entanglement as the project grows, development starts from a clean foundation and proceeds incrementally through modular, component-based, data-driven subsystems.

A core Metaworld design rule is that the world should feel usable rather than decorative. Many physical objects can become tools, improvised weapons, crafting resources, trade goods, construction materials, quest objects, or social props depending on context.

Metaworld does **not** require a primitive or Stone Age progression start. Players can enter a modern/fantasy open world with normal equipment and technology, while still being able to improvise with fists, stones, bottles, pipes, bats, furniture, tools, debris, and other physical objects when circumstances demand it.

## Core Architecture Principles

1. Keep gameplay domains isolated behind components, subsystems, interfaces, gameplay tags, and data assets.
2. Avoid placing unrelated systems directly inside the player character.
3. Prefer data-driven content over hardcoded item, economy, quest, weapon, or building definitions.
4. Design save/persistence boundaries early so world state and player state remain separable.
5. Keep first-person, third-person, social, combat, vehicle, and construction modes interoperable but decoupled.
6. Build each phase so it can be tested independently before the next major subsystem is introduced.
7. Do not define every usable object as a dedicated weapon class. Define physical properties and capabilities, then let combat, crafting, building, AI, economy, and interaction systems interpret those capabilities.
8. Context determines use. The same hammer can repair, build, break, be traded, or be used in combat without becoming a different fake copy of the item.
9. NPCs and players should use the same object capability rules wherever practical.
10. Economy, ownership, law, reputation, AI, combat, and world simulation should communicate through clean events/interfaces rather than direct hard dependencies.

---

# Master Development Roadmap

## Phase 1 — Core Modular Pawn & Camera System

Goals:

- Seamless switching between third-person and first-person modes.
- UE5 Enhanced Input mapping setup.
- Baseline locomotion and camera behavior.
- Clean foundation for later social, RPG, driving, combat, and interaction systems.

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

## Phase 5 — Resource Management & Survival/Growth Loops

Goals:

- Crop growth timers.
- Harvesting.
- Community resources.
- Survival / production loops.
- Persistent timed world state.

Recommended modules/components:

- Resource Component / subsystem
- Growth Component
- Harvestable interface
- Community resource subsystem
- Persistent timer/state records

---

# Development Order After Phase 1

The preferred order is:

1. Inventory + GrimKoin/PromoKoin economy foundation
2. Construction / base-building
3. Universal object capabilities + combat + equipment
4. Survival / growth / community resources

This order provides shared data, ownership, currency, physical-object, and resource abstractions before systems that depend on them become complex.

# Current Status

- Repository initialized.
- UE5 C++ module foundation established.
- Phase 1 starter character code added as the first gameplay baseline.
- GrimKoin and PromoKoin economy roles defined.
- Universal object-as-potential-weapon philosophy adopted for later combat architecture.
