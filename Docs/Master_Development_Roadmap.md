# Metaworld — Master Development Roadmap

## Vision

Metaworld is a hybrid Unreal Engine 5 title combining social/avatar customization, open-world driving/action, base-building/community management, deep RPG progression/quests, and responsive combat.

To prevent system entanglement as the project grows, development starts from a clean foundation and proceeds incrementally through modular, component-based, data-driven subsystems.

## Core Architecture Principles

1. Keep gameplay domains isolated behind components, subsystems, interfaces, and data assets.
2. Avoid placing unrelated systems directly inside the player character.
3. Prefer data-driven content over hardcoded item, economy, quest, weapon, or building definitions.
4. Design save/persistence boundaries early so world state and player state remain separable.
5. Keep first-person, third-person, social, combat, vehicle, and construction modes interoperable but decoupled.
6. Build each phase so it can be tested independently before the next major subsystem is introduced.

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
- Clean separation between item definition, item instance, ownership, and monetary value.

Recommended modules/components:

- Inventory Component
- Wallet / Economy Component
- Item Definition data assets
- Trade transaction layer
- Vendor interface

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

## Phase 4 — Combat & Weapon Component

Goals:

- First-person and third-person weapon handling.
- Ballistics / traces / projectiles.
- Recoil.
- Animation montages.
- Ammo management.
- Health and damage processing.

Recommended modules/components:

- Combat Component
- Weapon Component / weapon actors
- Health Component
- Damage interfaces
- Weapon Definition data assets

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

1. Inventory + economy foundation
2. Construction / base-building
3. Combat + weapons
4. Survival / growth / community resources

This order provides shared data, ownership, and resource abstractions before systems that depend on them become complex.

# Current Status

- Repository initialized.
- UE5 C++ module foundation being established.
- Phase 1 starter character code added as the first gameplay baseline.
