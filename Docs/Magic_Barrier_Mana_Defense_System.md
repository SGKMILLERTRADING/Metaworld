# Metaworld — Magic Barrier & Mana Defense System

**Status:** Canonical / Approved Modern RPG Playlist Upgrade
**Engine:** Unreal Engine 5.8
**Runtime:** Blueprint-first / server-authoritative / ability-driven / event-driven

## Canonical Principle

A magic barrier is an Ability-driven defensive state that can absorb eligible incoming gameplay results by spending canonical Mana. The barrier does not replace the Combat, Vitals, Status or Movement systems; it contributes a defensive layer to the shared result pipeline.

> Mana powers the barrier. The authoritative defense resolver decides what is absorbed. Niagara, materials, cracks, lights, sound and HUD flashes only present that state.

Related canon:
- `Docs/Ability_Definition_Learning_Execution_Cooldown_System.md`
- `Docs/Combat_Defense_Block_Dodge_Guard_Stamina_Input_Buffer_System.md`
- `Docs/Combat_Hit_Detection_Damage_Resistance_Feedback_System.md`
- `Docs/Character_Action_Movement_State_Resolver_System.md`
- `Docs/Magic_Staff_Spell_Projectile_Combat_System.md`

## 1. Barrier Ability State

Suggested stable definition:
`Ability.Magic.Defense.Barrier`

An active execution may own:
- AbilityExecutionID;
- source CharacterID;
- required Staff/Focus capability where designed;
- StartedAt;
- eligible result channels;
- coverage/angle policy;
- absorption profile;
- Mana conversion profile;
- movement/action restrictions;
- presentation profile;
- break/end reason.

Gameplay Tags such as `State.Magic.BarrierActive` may describe the state but are not the authority by themselves.

## 2. Activation

`RequestActivateAbility(BarrierDefinitionID)`
-> learned/available?
-> valid equipment/state?
-> enough activation resource?
-> begin AbilityExecutionID
-> apply action/movement restrictions through the normal resolver
-> enable authoritative barrier defense layer
-> emit presentation state.

The client cannot make itself protected merely by spawning the shield VFX.

## 3. Mana Absorption

Incoming eligible result:
-> normal contact/result is validated
-> barrier profile checks eligibility/coverage
-> calculate absorbable amount
-> calculate required Mana from the profile
-> spend available Mana authoritatively
-> absorb all or part of the eligible amount
-> unresolved remainder continues through normal defense/resistance/Vitals processing.

If Mana is insufficient, the barrier may partially absorb the result or fail according to definition. Do not silently create negative Mana or free absorption.

Tutorial numeric thresholds are tuning only.

## 4. Barrier vs Guard

Magic Barrier and physical Guard/Block are distinct defensive resources/layers.

- Stamina pays exertion where relevant;
- Guard represents physical defensive stability for ordinary block equipment;
- Mana can fuel magical barrier absorption.

Definitions decide ordering/compatibility. Do not merge them into one anonymous defense value.

## 5. Eligible Result Types

BarrierDefinition may define which result channels can be absorbed, reduced, redirected or ignored.

Examples can include physical, fire, cold, electric, supernatural or projectile-related results according to game design.

A visual color does not define the gameplay channel. The committed result profile does.

## 6. Movement / Collision

Do not use arbitrary capsule-radius changes as the canonical solution for barrier spacing.

Barrier action may request movement restrictions such as:
- slower walk;
- no Sprint;
- strafe profile;
- rotation restriction;
- stationary cast.

The Character Movement Resolver computes actual movement outputs from all active state, including Encumbrance, Stun, terrain/water and other actions.

The barrier VFX has no authority to alter character collision unless a specific tested gameplay profile explicitly requires a bounded collision change.

## 7. Break / End

Barrier can end because of:
- input release;
- Mana exhaustion;
- Stun/Knockdown/death;
- invalid equipment/state;
- Ability cancellation;
- configured maximum duration;
- explicit break condition.

The end transition happens once for the active AbilityExecutionID and removes only the exact barrier-owned state/restrictions.

## 8. Crack / Break Presentation

Approved presentation:
- translucent/Fresnel sphere;
- crack particles/material;
- impact ripples;
- break burst;
- staff light;
- hit/break audio;
- local HUD flash;
- controller haptics;
- color treatment based on the incoming committed result channel.

Crack count/intensity can reflect presentation state such as remaining Mana or absorbed impact severity, but it does not own barrier strength.

Cleaning up a crack Niagara component must never remove unrelated gameplay state.

## 9. Dynamic Channel Feedback

The shield may present different colors/sounds for Fire, Cold, Electric or other result channels.

This is feedback only. The barrier does not convert a result type merely because its material changed color.

## 10. Multiplayer / Performance

- server owns activation, Mana spending, absorption and end state;
- clients predict/present locally where safe;
- no permanent Tick while barrier is inactive;
- lifetime/active state uses the Ability execution record;
- VFX significance can reduce distant shield effects without changing protection;
- lights and Niagara should be bounded/profiled.

## Acceptance Tests

1. Barrier cannot activate without legal Ability/equipment/resource state.
2. VFX alone cannot grant protection.
3. Eligible incoming result spends the correct canonical Mana amount.
4. Insufficient Mana follows partial/fail policy without negative resource exploits.
5. Unabsorbed remainder continues through normal result/Vitals processing.
6. Movement restrictions compose with Encumbrance/Stun/etc. through the Movement Resolver.
7. Barrier break/end removes only barrier-owned state.
8. Crack/break VFX can be culled without changing authoritative protection.
9. Dynamic colors reflect result presentation without changing result type.
10. One barrier execution cannot break/end multiple times and duplicate side effects.

## Core Rule

Metaworld magic barriers are Mana-powered defensive Ability executions layered into the shared authoritative result pipeline. Gameplay determines absorption and resource cost; audiovisual shield effects only communicate that state.