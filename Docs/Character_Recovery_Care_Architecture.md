# Metaworld — Character Recovery & Care Architecture

**Status:** Canonical Gap-Closure Architecture

## Purpose

Metaworld needs persistent character recovery state that can connect Vitals, body zones, movement, consumable items, professional services, facilities and permanent death without creating a second Health authority.

## Persistent Recovery State

Longer-lived character health/recovery problems use stable records such as:

- RecoveryStateInstanceID;
- RecoveryStateDefinitionID;
- BodyZoneID where relevant;
- severity;
- source/provenance;
- start timestamp;
- current stage;
- active modifiers;
- care/recovery progress.

## Initial Families

Start with a limited useful set of persistent states representing things such as wounds, burns, mobility injuries, sickness, infection, toxic exposure and recovery fatigue.

Each state exists because it changes meaningful gameplay; avoid adding simulation detail that creates chores without decisions.

## Shared-System Integration

- Vitals remains the Health authority.
- Status Effects handles bounded conditions where appropriate.
- Movement consequences feed the shared Movement Resolver.
- Items/Inventory provides real supplies.
- Profession/Skills governs specialist services.
- Rest/Sleep participates in recovery where defined.

## Care Actions

Care uses authoritative actions and legitimate resources/services.

Examples can include basic first aid, stabilization, medicine use, professional care, rest and facility-based services.

A care action changes only the state it is defined to address.

## Care Items

Care supplies are persistent ItemInstances/stacks with explicit use rules. They are consumed or changed only through authoritative item-use transactions.

## Professional Services

Health-care professions use existing Profession architecture with data-driven training, tools, facility and service requirements.

## Recovery While Unloaded

Time-based recovery uses timestamps/state transitions when a Character is unloaded or offline. It must not require continuous Actor simulation.

## Facilities

Care facilities can connect to rooms/beds, staff schedules, supply inventory, service transactions, utilities and Business/Organization ownership.

## NPC Use

NPCs use the same high-level recovery framework at significance-appropriate fidelity. Important nearby NPCs may use detailed states; distant NPCs may use summarized state/timestamp progression.

## Death Integration

All serious consequences still flow through the canonical Vitals/death pipeline. Recovery architecture does not create an alternate death system.

## Acceptance Gate

Prove one persistent recovery state can:

- be created from an authoritative gameplay event;
- affect the correct shared system;
- receive a valid care action using a real resource/service;
- change Movement Resolver output if appropriate;
- persist across reconnect/restart;
- advance by timestamp while unloaded;
- integrate with an NPC/facility service.

## Core Principle

> Recovery is durable character state resolved through existing Metaworld systems, not a set of disconnected temporary variables.