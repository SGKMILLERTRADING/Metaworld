# Metaworld — NPC Combat AI, Engagement & Death System

**Status:** Canonical / Approved Modern RPG Playlist Upgrade

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first / StateTree-oriented / shared Combat Component / persistent NPC state / server-authoritative

## Canonical Principle

NPC combat AI decides *what action to attempt* while the same Combat, Equipment, Vitals, Movement and Status systems used by players decide whether that action is legal and what result occurs.

> NPCs do not get a second simplified combat game. Their AI chooses attack, block, dodge, reposition, retreat, use item or disengage; shared gameplay systems execute those choices.

Related canon:

- `Docs/Combat_Action_Gameplay_Tag_State_System.md`
- `Docs/Combat_Hit_Detection_Damage_Resistance_Feedback_System.md`
- `Docs/NPC_Interaction_Trader_Merchant_Commerce_System.md`
- `Docs/Equipment_Armor_Weapon_Attachment_Avatar_Fitting_Architecture.md`
- `Docs/Status_Effects_Conditions_Buffs_Debuffs_System.md`

---

# 1. AI Decision Layer

Recommended high-level decision architecture:

- StateTree / AI controller / bounded perception;
- combat engagement context;
- target evaluation;
- movement/navigation requests;
- action selection;
- retreat/surrender/de-escalation where appropriate.

The AI layer submits requests to shared gameplay systems rather than directly editing Health or spawning fake weapons.

---

# 2. Perception

Tutorial Pawn Sensing intent is accepted as a prototype, but Metaworld should use a scalable perception/awareness strategy appropriate to current UE5.8 architecture and population scale.

Awareness can consider:

- sight;
- hearing/noise;
- damage source;
- faction/hostility;
- crime/witness information;
- known attacker/target memory;
- line of sight;
- environment/cover;
- significance/distance.

Do not run expensive always-on sensing logic at full fidelity for every distant NPC.

---

# 3. Engagement State

Suggested semantic states/tags can include:

- `AI.Combat.Alert`
- `AI.Combat.Engaged`
- `AI.Combat.Searching`
- `AI.Combat.Retreating`
- `AI.Combat.Surrendered`
- `AI.Combat.Dead`

These are AI/world states, distinct from action tags such as `Action.Combat.Attacking`.

---

# 4. Target Selection

Target selection can consider:

- hostility/faction rules;
- recent attacker;
- threat level;
- distance/reachability;
- visibility;
- mission/job duty;
- self-preservation;
- protection of allies/property;
- law/security role;
- current weapon/ammunition/resources.

A simple tutorial Player tag is not the final hostility model.

---

# 5. Navigation / Positioning

NPC AI requests movement through normal navigation/movement architecture.

Combat positioning can include:

- approach;
- maintain weapon range;
- circle/strafe;
- seek cover later;
- flank later;
- retreat;
- avoid hazards;
- avoid stacking several NPC capsules in one exact point.

The Combat Component does not own pathfinding.

---

# 6. Shared Combat Actions

When AI chooses an attack:

`AI decision`
-> `RequestCombatAction(AttackDefinitionID/context)`
-> `BPC_MW_Combat` validates weapon/action/resource/state
-> committed action drives animation/hit windows/damage.

The same applies to:

- Block;
- Dodge;
- Parry where AI profile supports it;
- Weapon switch;
- Bow/firearm use;
- consumable use;
- magic later.

---

# 7. NPC Equipment

An enemy holding an Iron Sword should use a legitimate equipped ItemInstance / loadout source.

Do not make `BeginPlay -> spawn free Iron Sword` the permanent economy/identity rule for persistent NPCs.

Valid sources can include:

- persistent owned equipment;
- generated NPC loadout at legitimate NPC creation/spawn initialization;
- faction/job-issued gear;
- authored encounter equipment;
- temporary non-lootable training/test props only when explicitly designed.

Death/loot then respects whether the weapon actually belongs to/exists on the NPC.

---

# 8. Damage / Conditions

NPCs use the same damage packet, armor/resistance and Status Effect architecture.

A sword may produce physical damage and a poison-coated weapon may apply a Poison condition according to weapon/ammo/effect data.

AI does not directly call `SetPlayerHealth`.

---

# 9. Death

Death transition is authoritative and idempotent.

Suggested flow:

`Health/death condition reached`
-> server commits death state exactly once
-> stop accepting incompatible combat actions
-> AI engagement ends
-> navigation/perception updates/disables as appropriate
-> death animation/ragdoll presentation
-> collision switches to valid corpse profile
-> equipment/corpse inventory/loot transitions through item/container systems
-> world/legal/news/evidence/death systems receive event where applicable.

A `State.Dead` tag helps broad checks, but a persistent death record/state remains authoritative.

---

# 10. Corpse Collision

Dead-body collision should prevent pathological blocking while preserving intended corpse interaction.

Possible profile:

- no normal AI navigation blocking after settling;
- camera ignores where appropriate;
- player movement does not become permanently trapped;
- corpse still supports looting/dragging/evidence interactions where designed.

Do not simply disable every collision forever if later corpse gameplay needs it.

---

# 11. Death Once

A dead NPC cannot:

- die twice;
- keep taking ordinary combat damage if death policy says no;
- continue attacking;
- respawn equipment/loot by replaying death logic.

Repeated damage events after death are ignored or routed to corpse-damage rules if such a feature exists later.

---

# 12. Persistence / Population

Persistent NPC death follows Metaworld world rules.

NPC state can include:

- alive/dead;
- injuries/conditions;
- equipment/inventory;
- target/engagement reset policy;
- corpse/estate/loot disposition;
- family/job/business consequences.

Do not respawn a dead persistent civilian just because their Actor streamed out/in.

---

# 13. Performance

- perception/decision fidelity scales by significance;
- distant NPCs do not run full combat logic when irrelevant;
- no permanent attack timer when not engaged;
- StateTree/events drive decisions;
- combat traces exist only during active attacks;
- ragdolls/physics scale/settle according to performance policy;
- corpse presentation can downgrade while persistent state remains data.

---

# 14. Acceptance Tests

1. NPC chooses an attack but damage occurs only through shared Combat system.
2. NPC cannot attack without a valid weapon/action state when required.
3. NPC target selection does not mistake all NPCs for the player.
4. Dead NPC stops AI combat exactly once.
5. Repeated lethal hits cannot duplicate loot/death effects.
6. Corpse collision does not trap the player while remaining usable where intended.
7. NPC equipment preserves ItemInstance provenance into death/loot.
8. NPC poison/fire/etc. effects use shared status/damage rules.
9. Distant irrelevant NPCs do not run full perception/combat loops.
10. Persistent death does not reverse merely from streaming/reload.

## Core Rule

> Metaworld AI chooses combat behavior; shared authoritative gameplay systems execute it. NPCs sense, decide and navigate through an AI layer, but weapons, actions, stamina, damage, conditions, death and loot remain the same persistent systems used across the world.