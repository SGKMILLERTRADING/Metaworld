# Metaworld — Breakable World Object, Destruction & Loot System

**Status:** Canonical / Approved Modern RPG Playlist Upgrade

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first / server-authoritative world state / Chaos-capable / loot-integrated / persistent

## Canonical Principle

A breakable crate, barrel, prop or other world object is a persistent world object with durability/destruction policy and optional legitimate contents. Chaos Geometry Collection, particles, sound and debris present the destruction; Loot/Container systems determine what real ItemInstances or currency records become available.

> Breaking the object changes authoritative world state. Fracture pieces are presentation. Loot is seeded/created through the real loot system and never appears because a particle effect happened.

Related canon:

- `Docs/Loot_Generation_Tables_Drops_Provenance_System.md`
- `Docs/Loot_Containers_Bags_Corpses_Chests_Transfer_System.md`
- `Docs/Resource_Destruction_Chaos_Fracture_Presentation_System.md`
- `Docs/Combat_Hit_Detection_Damage_Resistance_Feedback_System.md`
- `Docs/Gold_Material_Commodity_Not_Currency_Rule.md`

---

# 1. Breakable Object Identity

Suggested capability/profile:

`Object.Capability.Breakable`

A breakable world object can define:

- WorldObjectID;
- BreakableProfileID;
- durability/health model;
- allowed damage channels/tools;
- armor/material response;
- destruction threshold/policy;
- LootProfileID / contained ContainerID where applicable;
- ownership/property/legal state;
- repair/rebuild policy;
- persistent destroyed/intact state;
- Chaos/VFX/audio presentation profile.

---

# 2. Damage Integration

Combat/tool contact submits a normal validated damage event against the world object.

Example:

`Sword hit crate`
-> hit/contact validated
-> Breakable object accepts physical damage profile?
-> reduce durability / commit break result
-> if destroyed, transition once.

Do not make a PointDamage event by itself a trusted destruction command from a client.

Some objects can reject inappropriate attacks:

- cardboard/wood may break from melee;
- reinforced metal crate may require tools/explosives;
- puzzle object may be indestructible until world rule changes.

---

# 3. Destruction Is Idempotent

Suggested state:

- Intact;
- Damaged;
- Destroying;
- Destroyed;
- Repaired/Rebuilt where supported.

A destruction transition occurs once.

Repeated hits after `Destroyed` cannot:

- reseed loot;
- replay ownership transfer;
- award currency repeatedly;
- generate duplicate destruction events.

---

# 4. Chaos / Geometry Collection Presentation

Geometry Collection + Chaos fracture is approved for suitable breakables.

Rules:

- fracture count/cluster layout is art/performance data, not item quantity;
- Master Field/Chaos impulses present the committed break event;
- fragment collision uses an appropriate debris profile so tiny pieces do not trap players;
- debris can sleep/remove on a bounded schedule;
- destroyed persistent state remains even after debris is cleaned up.

The visual destruction actor/Geometry Collection may be spawned or activated only when required.

---

# 5. Loot / Contents

Two valid content models are supported.

## A. Seeded Container Contents

The crate has a real ContainerID seeded once.

`Crate Container`
-> contains ItemInstances
-> break opens/spills/transfers those existing contents into a reachable loot/world-output container.

## B. Destruction-Time Loot Profile

An authored disposable object may roll a LootProfile once on the authoritative destruction event.

The result is immediately persisted with provenance and cannot reroll on reload/rebreak.

Use profile/data policy deliberately; do not combine both models in a way that duplicates the same item.

---

# 6. Gold / Currency Rule

Tutorial `random Gold drop` as money is rejected.

A breakable may legitimately contain/drop:

- physical Gold Ore/Nugget/Ingot/etc. as ItemInstances if its LootProfile includes them;
- physical/carried GrimKoin or PromoKoin according to the canonical currency/container policy;
- ordinary items/materials.

Never:

`Break crate -> PlayerGold += RandomAmount`.

Breaking a crate does not reach into a bank ledger or mint currency from nothing unless a deliberate reward/world-system rule explicitly created that currency source.

---

# 7. Spill / World Output

Destroying a container does not require spawning one Actor per item.

Possible output:

- LootBagContainerID;
- spill bundle/container;
- a bounded number of grouped world stacks;
- preserved individual world actors only where needed.

ItemInstance identity, quantity, provenance and ownership survive the spill.

---

# 8. Ownership / Crime / Evidence

Destroying someone else's crate may be:

- property damage;
- burglary/theft attempt;
- vandalism;
- lawful owner action;
- authorized job action.

Loot becoming physically accessible does not automatically change legal ownership.

World law/evidence systems can receive:

- Destroyed WorldObjectID;
- attacker identity;
- weapon/tool ItemInstanceID;
- timestamp/location;
- resulting theft/transfer events.

---

# 9. Persistence / Reset

Persistent world breakables save meaningful state:

- durability/damage if required;
- intact/destroyed;
- contents/loot seed state;
- repair/rebuild timestamps/state.

A world designer may explicitly define renewable/resettable arcade props, but ordinary persistence does not silently respawn a destroyed crate and regenerate loot merely because a timer or streaming event fired.

---

# 10. Feedback

Approved presentation:

- wood/metal/stone impact audio;
- splinters/dust/sparks;
- Niagara burst;
- fracture impulse;
- camera/haptic feedback when locally relevant.

Feedback follows the committed damage/destruction result.

---

# 11. Performance

- intact breakables do not Tick for destruction checks;
- Chaos activates only when required;
- fragment collision/lifetime is bounded;
- loot remains compact data until physical presentation is necessary;
- distant destruction presentation can scale down while world state remains correct;
- use pooled/shared effects where practical.

---

# Acceptance Tests

1. Valid hit damages/breaks object only through authoritative damage state.
2. Destroy transition happens once.
3. Repeated hits cannot duplicate loot.
4. Fracture piece count does not change loot quantity.
5. Player can pass through/around cleaned debris according to collision profile.
6. Seeded contents preserve exact ItemInstance identity after break/spill.
7. Physical Gold remains commodity; no Gold wallet currency is awarded.
8. GK/PK only appear from legitimate currency source/state.
9. Breaking another owner's object can preserve crime/property evidence.
10. Save/load keeps a persistent crate destroyed without rerolling contents.
11. Debris cleanup does not restore the crate or regenerate loot.
12. Chaos/VFX can be reduced without changing world/loot truth.

## Core Rule

> Metaworld breakables combine authoritative world-object damage with optional persistent contents and scalable Chaos presentation. The object breaks once, loot exists once, and visual debris never decides item creation, currency or persistence.