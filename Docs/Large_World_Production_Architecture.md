# Metaworld — Large World Production Architecture

**Status:** Canonical Gap-Closure Architecture
**Engine:** Unreal Engine 5.8

## Purpose

Metaworld needs a production plan that scales from one playable district to cities and regions without loading or simulating everything at full fidelity.

## Canonical UE5.8 World Stack

Use these systems together:

- Large World Coordinates;
- World Partition;
- One File Per Actor;
- Data Layers;
- HLOD;
- Level Instances;
- PCG;
- Nanite where compatible.

## Stable Geography IDs

Geography has durable data identity independent of loaded Actors:

- WorldID;
- RegionID;
- CityID;
- DistrictID;
- NeighborhoodID;
- ParcelID;
- BuildingID;
- InteriorUnitID;
- RoadSegmentID;
- PointOfInterestID.

These IDs connect ownership, businesses, utilities, missions, news, logistics and population simulation.

## Development Order

Start with one representative vertical-slice district, not the whole world.

The district should include:

- roads and sidewalks;
- homes/apartments;
- shops/businesses;
- service buildings;
- resource/crafting area;
- construction parcel;
- vehicle routes/parking;
- NPC schedules;
- representative interiors;
- persistent world events.

This becomes the performance and systems laboratory for larger regions.

## Streaming Rule

Nearby cells contain full interactive Actors where required.

Distant/unloaded cells rely on:

- HLOD/proxy visuals;
- persistent records;
- scheduled/timestamp simulation;
- regional summaries.

Unloaded world state must not require full Actor simulation.

## Data Layer Rule

Runtime Data Layers can organize variants such as:

- construction stages;
- seasonal decoration;
- event presentation;
- renovation states;
- mission presentation;
- temporary closures.

Persistent gameplay truth still lives in stable records. Data Layer load state is representation state, not the sole proof that persistent state exists.

## HLOD Rule

Create HLOD strategies by content family, such as architecture, vegetation, roadside props, landmarks and dense repeated areas. HLOD generation is part of content build/preflight.

## PCG Rule

PCG is approved for accelerating authored production, including vegetation, roadside dressing, utility/prop placement, fences, repeated structures, terrain detail and selected parcel helpers.

Generated content that becomes persistent gameplay content needs stable identity and explicit gameplay registration.

Prefer Editor-time generation for persistent authored content. Runtime PCG is selective and performance-tested.

## World Content Separation

Production should distinguish:

- roads;
- parcels;
- building shells;
- interiors;
- service points;
- utility networks;
- navigation;
- streaming/HLOD metadata.

## Interiors

Interiors do not all remain loaded. Use streamed interiors, reusable Level Instances, Data Layers where helpful, persistent interior records and significance-based materialization.

## Regional Travel

Long-distance travel may later use continuous streaming, controlled transitions or region-server handoff depending on scale/performance.

Travel must preserve CharacterID, inventory, vehicle, party and world-event state.

## Editor Automation

Python/Editor tooling should eventually validate:

- naming/folders;
- HLOD/Nanite policy;
- geography IDs;
- duplicate stable IDs;
- PCG preflight;
- navigation/build status;
- Data Layer policy;
- World Partition builder jobs;
- reports.

## Acceptance Gate

The first district must prove:

- World Partition streaming;
- HLOD transitions;
- Data Layer toggles;
- multiplayer late join;
- persistent objects across unload/reload;
- NPC significance transitions;
- vehicle traversal;
- representative interiors;
- server restart reconstruction;
- stable worst-case frame time.

## Core Principle

> Metaworld is persistent geography plus streamed representations. Only the relevant portion of the world needs full fidelity at one time.