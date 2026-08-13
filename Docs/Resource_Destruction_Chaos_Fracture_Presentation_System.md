# Metaworld — Resource Destruction, Chaos Fracture & Debris Presentation System

**Status:** Canonical / Approved Modern RPG Playlist Upgrade

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first / Chaos-assisted presentation / server-authoritative resource truth / performance-budgeted

## Canonical Principle

Chaos destruction can visually sell the breaking of rocks, trees and other harvestable resources, but fracture simulation does not own material yield, persistent reserve or loot truth.

> The resource system decides what was harvested. Chaos shows the world breaking apart.

Related canon:

- `Docs/Resource_Gathering_Harvesting_Tools_Depletion_Regeneration_System.md`
- `Docs/Performance_Smoothness_FrameTime_Architecture.md`
- `Docs/HUD_Notification_Feedback_System.md`

---

# 1. Geometry Collection Use

UE5.8 Geometry Collections / Chaos Fracture are approved for selected resource-destruction presentation.

Candidate use cases:

- ore rocks breaking;
- brittle stone;
- selected trees/logs where the effect fits;
- destructible salvage/material piles;
- authored world props tied to gathering.

Not every gathered resource requires full Chaos simulation.

---

# 2. Separation of Truth and Presentation

Authoritative resource extraction determines:

- ResourceNodeID;
- extraction success;
- quantity/quality yielded;
- remaining reserve;
- depletion state;
- persistent outputs.

Chaos presentation determines:

- fracture pieces;
- impulses/strain;
- crumble/fall visuals;
- dust/sparks/debris;
- local audio;
- cleanup timing.

A physics shard is not automatically an Iron Ore ItemInstance.

If recoverable chunks are intended, the resource transaction deliberately creates corresponding ItemInstances/world actors rather than treating every Geometry Collection bone as inventory.

---

# 3. Authoring

Approved authoring concepts:

- create Geometry Collection from suitable static mesh;
- fracture with an appropriate method/count;
- use clustering where useful;
- author internal materials;
- tune damage/strain thresholds;
- validate collision and initial state;
- prevent the collection from simulating destructively before the gameplay event;
- use transient Physics Fields/impulses where appropriate.

Tutorial numeric values such as 30 pieces or threshold 100/50/10 are prototypes only; each asset is profiled and tuned.

---

# 4. Trigger Flow

Recommended:

`Resource extraction reaches depletion/break phase`
-> authoritative resource state commits/reserves result
-> static/intact presentation transitions out
-> spawn/activate fracture presentation
-> apply approved Chaos trigger
-> play audio/VFX
-> cleanup fracture presentation after bounded lifetime.

Do not let a random physics collision accidentally mint resources before the resource system accepts extraction.

---

# 5. Trees

Trees may need specialized break/fall presentation rather than generic stone-style fracture.

Possible techniques by tree profile:

- authored trunk cut state + falling mesh;
- limited fracture at cut region;
- Geometry Collection for selected trees;
- simpler replacement debris for distant/background trees.

The biological resource/regrowth state remains in the Resource system.

---

# 6. Cleanup

Debris cleanup is mandatory for performance.

Possible policies:

- remove sleeping fragments after a bounded delay;
- disable collision on insignificant fragments;
- destroy/deactivate fracture actor after visual value ends;
- pool reusable presentation actors where profiling justifies it;
- reduce debris count at lower scalability tiers.

Cleanup timing is presentation and can differ from persistent resource regeneration.

A rock's debris disappearing after 20 seconds does **not** mean the ore deposit has regenerated.

---

# 7. Multiplayer

Server owns the resource/depletion result.

Fracture presentation can be replicated/triggered through a compact gameplay event/profile where needed rather than synchronizing every debris transform forever.

Distant clients may receive a cheaper broken/depleted state instead of full Chaos simulation.

---

# 8. Performance

- use Chaos only where it adds enough visual value;
- cap simultaneous fracture events;
- significance/scalability controls fragment count and lifetime;
- avoid permanent collision/simulation for settled debris;
- no resource gameplay dependency on every simulated fragment;
- profile CPU/GPU/physics cost in representative harvesting scenes.

---

# 9. Acceptance Tests

1. Resource yield remains correct if Chaos presentation is disabled.
2. Fracture cannot duplicate resource outputs.
3. Depleted resource persists after debris cleanup.
4. Fragments clean up within profile budget.
5. Multiplayer clients converge on the same resource depleted/intact truth.
6. Low scalability can use reduced/alternate destruction without changing gameplay result.
7. Trees/rocks can use different destruction profiles.

## Core Rule

> Chaos is a visual/physical destruction layer over authoritative resource state. Metaworld never lets fracture debris become the database of how much ore, wood or salvage exists.