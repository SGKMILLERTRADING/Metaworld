# Metaworld — NPC Schedule, Relationship, Goal & Population System

**Status:** Canonical Gap-Closure Architecture

## Purpose

Metaworld's NPC foundation already supports shared humanoid systems, needs, significance and basic services/combat. This document adds the missing long-term life layer: schedules, relationships, goals, employment and population simulation.

## Persistent NPC Record

Important NPCs use stable records containing, as appropriate:

- NPCCharacterID;
- household/family links;
- home/property relationship;
- employment/organization membership;
- profession/skills;
- needs/resources;
- schedule profile;
- relationship records;
- goals/current commitments;
- reputation/legal state;
- inventory/equipment;
- current region/location summary.

## Schedule System

Schedules are data-driven time blocks, not giant per-NPC Tick graphs.

Examples:

- sleep/home;
- commute/travel;
- work shift;
- meals;
- shopping/services;
- social/free time;
- family responsibilities;
- special appointments/events.

Schedules can be interrupted by real world events, urgent needs, employment changes, travel problems or other higher-priority states.

## Local AI

Nearby materialized NPCs can use Blueprint-friendly StateTree/Behavior logic and Smart Objects for reserved interactions.

Smart Objects describe available interaction opportunities; the NPC's own logic decides whether and how to use them.

## Long-Term Goals

NPC goals are higher-level persistent intents such as:

- earn money;
- maintain household supplies;
- improve profession;
- find/keep housing;
- care for family;
- maintain business/job;
- social relationship goals;
- respond to organization/world obligations.

Goals produce practical tasks through existing systems rather than bypassing them.

## Relationships

Relationship records may track dimensions such as:

- familiarity;
- trust;
- affection;
- respect;
- fear;
- resentment;
- family/household role;
- professional relationship.

Do not collapse all social state into one universal reputation number.

## Employment

NPC employment connects to:

- Business/OrganizationID;
- Job/RoleID;
- work location;
- schedule;
- wage/payroll;
- required profession/skills;
- attendance/performance where useful.

An unemployed NPC can seek suitable work through data-level matching rather than scanning every business every frame.

## Significance Tiers

### Tier A — Nearby Important
Full character, animation, local reasoning, interactions.

### Tier B — Nearby Ordinary
Standard character with reduced expensive layers.

### Tier C — Distant
Lightweight scheduled/state simulation.

### Tier D — Unloaded
Persistent record + timestamp/event transitions only.

NPC identity/state survives movement between tiers.

## Materialization

When an unloaded NPC becomes relevant:

1. load persistent NPC record;
2. calculate elapsed schedule/need changes;
3. determine expected current activity/location;
4. spawn appropriate character representation;
5. resume local StateTree/interaction behavior.

## Population Simulation

Large populations are simulated in aggregate where individual fidelity provides no visible value.

Regional systems can summarize:

- employment demand;
- household food demand;
- travel flows;
- service demand;
- births/deaths later if approved;
- migration/movement;
- major event participation.

Important named NPCs retain richer individual persistence.

## External/AI Model Use

Any future local/external language-model reasoning is optional high-level intent generation only. It is asynchronous and cannot directly mutate authoritative inventory, money, property or legal state.

## Acceptance Gate

Prove one NPC can:

- wake/home state;
- travel to scheduled workplace;
- reserve/use a Smart Object;
- receive wage/obtain food through real systems;
- remember a relationship change;
- unload into data-only simulation;
- advance schedule by timestamp;
- materialize later in the expected state;
- survive server restart.

## Core Principle

> NPCs live through persistent records and meaningful systems. Full Actor simulation is a temporary representation used only when the world needs to see it.