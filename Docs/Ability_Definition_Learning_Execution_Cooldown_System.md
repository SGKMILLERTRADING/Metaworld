# Metaworld — Ability Definition, Learning, Execution & Cooldown System

**Status:** Canonical / Approved Modern RPG Playlist Upgrade
**Engine:** Unreal Engine 5.8
**Runtime:** Blueprint-first / server-authoritative / data-driven / event-driven

## Canonical Principle
Abilities are stable gameplay definitions coordinated by an authoritative Ability component. They may spend existing character resources, require equipment profiles, start Combat or Character Actions, apply Conditions, or trigger other approved gameplay systems. They do not duplicate those systems.

## 1. Identity
Use stable `AbilityDefinitionID` values such as `Ability.Defense.StoneForm`, `Ability.Combat.Whirlwind`, and `Ability.Infusion.Fire`. Data Tables/Data Assets are approved authoring sources, but enum display names are not persistent identity.

## 2. Ability Definition Data
An ability may define: ID, name/description, icon, tags, execution profile, montage, cooldown, resource costs, required/blocked state tags, equipment/handling requirements, target rules, effect references, interruption policy, learning requirements, AI-use policy, and presentation assets.

## 3. Runtime Owner
Recommended `BPC_MW_Abilities` responsibilities:
- learned/unlocked ability state;
- activation validation;
- cooldown/cost/requirement checks;
- authoritative `AbilityExecutionID` creation;
- coordination with Combat, Movement, Status Effects, Equipment and Items;
- persistence/replication;
- UI events.

It does not own Health, Mana, Inventory, Equipment or final damage formulas.

## 4. Learning
Learning is persistent character knowledge. A character can know an ability without assigning it to a quickslot. Possible sources include trainers, progression, manuals, quests, world events, lineage/supernatural unlocks and development grants. Duplicate learning follows explicit policy.

## 5. Activation Flow
`RequestActivateAbility(AbilityDefinitionID, TargetContext)`
-> learned/available?
-> cooldown clear?
-> state/equipment/target valid?
-> sufficient canonical resources?
-> reserve/spend costs according to profile
-> create `AbilityExecutionID`
-> start approved Character/Combat action
-> execute authored phases
-> route effects to their owning systems
-> start cooldown according to profile
-> persist/replicate result.

Clients cannot report `AbilitySucceeded=true` as trusted truth.

## 6. Costs
Costs use existing resources such as Mana, Stamina, Health where deliberately designed, reagents/items, or other future canonical resources. Cost timing can occur at start, commitment, channel cadence, or according to explicit cancellation/refund policy.

## 7. Requirements
Requirements use stable capabilities/tags/profiles instead of tutorial-only enums. Examples include a required handling profile, an allowed equipment capability, empty hands, a profession tool, or a valid environment/state.

## 8. Action Integration
`Action.Ability.Executing` may describe state, but the authoritative execution is the `AbilityExecutionID` plus associated Character/Combat action. Compatibility rules decide whether the ability can coexist with movement, aiming, swimming, climbing, resting, dodge windows, Stun and other states. The Character Action/Movement Resolver owns movement consequences.

## 9. Cooldowns
Do not spawn one temporary Actor/Actor Component per cooldown as the default architecture. Use compact records:
- AbilityDefinitionID or CooldownGroupID;
- StartedAt;
- EndsAt;
- source execution/revision.

Cooldown policies may be per-ability, shared group, charge/recharge, category/global where deliberately designed, or none. Save/load reconstructs remaining time from timestamps.

## 10. Stone Form Example
Stone Form validates activation, starts an execution, applies a canonical `Condition.Buff.StoneForm`, and lets Status Effects/source-aware modifiers supply temporary defense. Tutorial values such as +100 Armor for 30 seconds are tuning only; Base Armor is not permanently edited.

## 11. Whirlwind Example
Whirlwind validates compatible combat state, starts one execution, uses authored active hit windows, resolves candidate targets through the shared Combat system, and produces canonical DamagePackets. A local animation notify cannot create authoritative damage.

## 12. Interruption
Interruptions such as Stun, Knockdown, death, invalid target/state, or explicit cancellation reconcile only the relevant active execution. Reserved costs/cooldown behavior follow the definition. Unrelated Conditions and gameplay state are preserved.

## 13. Multiplayer / Persistence
Persist learned abilities/loadout and any cooldown timestamps that must survive reconnect. Server owns grants, activation legality, costs, cooldowns, execution phase and gameplay consequences. Clients may predict presentation only.

## 14. Performance
Ability definitions are data; cooldowns are timestamp records; only active executions schedule work; no permanent Tick per ability; UI derives visible cooldowns locally; expensive audiovisual references should be soft where practical.

## Acceptance Tests
1. Unlearned ability cannot activate.
2. Learned ability can exist without quickslot assignment.
3. Active cooldown blocks activation.
4. Save/reconnect preserves remaining cooldown.
5. Canonical resource costs are enforced.
6. Invalid equipment/state rejects activation.
7. Stone Form applies/removes through Status Effects.
8. Whirlwind uses shared Combat damage resolution.
9. Stun interrupts only the relevant execution.
10. Client cannot forge cooldown completion or resource availability.
11. No per-cooldown Actor Component is required.
12. Quickslot/controller activation reaches the same request path.

## Core Rule
Metaworld abilities are authoritative data-driven action definitions layered over existing gameplay systems. The Ability component owns learning, activation, cooldown and execution coordination; every underlying system retains ownership of its own gameplay truth.