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
