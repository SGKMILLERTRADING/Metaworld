# Metaworld

Metaworld is a modular Unreal Engine 5 game project combining:

- Social/avatar customization inspired by virtual social worlds
- Open-world driving and action
- Base-building and community management
- Deep RPG progression and quest systems
- Responsive first/third-person combat

The project is intentionally built as a component-based, data-driven architecture so major gameplay systems remain isolated, reusable, and extensible.

## Current Development Phase

**Phase 1 — Core Modular Pawn & Camera System**

Initial implementation includes:

- UE5 C++ character base
- Enhanced Input support
- Third-person movement
- First-person / third-person camera switching
- Modular project structure ready for future subsystems

## Master Roadmap

See [`Docs/Master_Development_Roadmap.md`](Docs/Master_Development_Roadmap.md).

## Source Layout

```text
Metaworld/
├── Docs/
├── Source/
│   └── Metaworld/
│       ├── Private/
│       ├── Public/
│       └── Metaworld.Build.cs
└── Metaworld.uproject
```

## Architectural Rule

Gameplay systems should be implemented as modular components/subsystems rather than hardwired into the player character wherever practical. The player character should coordinate capabilities, not become a monolithic container for inventory, economy, weapons, construction, survival, quests, vehicles, social systems, and persistence.
