# Metaworld — Vehicle, Transportation, Ownership & Persistence System

**Status:** Canonical Gap-Closure Architecture
**Engine:** Unreal Engine 5.8

## Purpose

Vehicles are persistent property and transportation systems, not temporary movement Actors. Metaworld needs one vehicle architecture that supports ownership, access, passengers, storage, condition, maintenance, energy/fuel, traffic, evidence and multiplayer movement.

## Stable Identity

Separate vehicle definition from exact persistent copy:

- VehicleDefinitionID = model/type/catalog definition;
- VehicleID / VehicleInstanceID = exact persistent vehicle;
- OwnerID / OrganizationID;
- RegistrationID where applicable;
- AccessPolicyID;
- VehicleContainerID;
- Condition/maintenance state;
- location/garage state.

A specific vehicle keeps the same identity whether parked, driven, stored, damaged or unloaded.

## UE5.8 Physics Direction

Initial implementation should evaluate Chaos Vehicles for normal vehicles and Chaos Modular Vehicles for gameplay that genuinely needs runtime component changes or breakable modular vehicle construction.

Networked Physics is part of the evaluation because vehicles must feel responsive without giving the controlling client final authority over persistent vehicle state.

## Authority

The server owns:

- who is allowed to enter/control;
- authoritative VehicleID state;
- persistent location/garage state;
- storage contents;
- condition and maintenance;
- fuel/energy;
- ownership/registration;
- collisions with persistent consequences;
- final travel/transition state.

Clients may predict/smooth local vehicle movement according to the chosen UE networking path.

## Access / Keys

Vehicles integrate with the existing Credential/Lock architecture.

Possible access methods:

- physical key ItemInstance;
- electronic credential;
- owner/household/organization permission;
- rental/service permission;
- temporary authorized driver.

Physical access and legal ownership are separate facts.

## Seats

Each vehicle exposes stable seat definitions:

- SeatID;
- role/driver/passenger;
- entry/exit transforms;
- allowed character profiles;
- door/side metadata;
- occupancy.

Seat reservation prevents two characters from occupying the same seat.

## Vehicle Storage

Trunks, glove boxes, cargo beds and other storage use ordinary ContainerID architecture.

Vehicle storage is finite and physical. Items do not disappear when the vehicle unloads from the world.

## Fuel / Energy

Fuel, charge or other energy is data-driven by vehicle profile.

Possible types include:

- liquid fuel;
- battery charge;
- hybrid systems;
- future/special systems.

Energy is persistent state and consumption is driven by meaningful operation rather than arbitrary per-frame bookkeeping where avoidable.

## Condition / Maintenance

Vehicles can track systems such as:

- overall condition;
- tires/wheels;
- engine/powertrain;
- body/panels;
- lights/electrical;
- windows/doors;
- battery/fuel system;
- service intervals.

Not every part needs full simulation unless it creates useful gameplay.

Repair uses tools, parts, professions, facilities and legitimate transactions.

## Parking / Garages

A parked vehicle may become dormant/data-driven rather than remaining a fully active physics Actor.

Persist:

- VehicleID;
- transform/parking slot;
- condition;
- storage;
- access state;
- fuel/energy;
- relevant evidence/history.

Materialize full physics only when relevant.

## Traffic / NPC Vehicles

Traffic uses significance tiers:

- nearby interactive traffic = full vehicle representation;
- nearby background traffic = simplified logic;
- distant traffic = schedule/flow simulation;
- unloaded traffic = regional records rather than spawned vehicles.

Do not run full Chaos physics for every parked or distant vehicle in a city.

## Accidents / World Integration

Vehicle events can integrate with:

- Health/Injury;
- property condition;
- ownership/insurance later;
- evidence/cameras;
- law/traffic rules;
- maintenance businesses;
- missions/jobs;
- News when significant.

## Public / Commercial Transport

The same architecture should later support:

- taxis/rides;
- buses;
- delivery vehicles;
- service vehicles;
- rental vehicles;
- organization fleets;
- public transport schedules.

## Minimum Vehicle Vertical Slice

Build one ordinary car first and prove:

- VehicleID persistence;
- server-authorized driver entry;
- passenger seat;
- controller/KBM driving;
- network movement under latency;
- trunk ContainerID;
- fuel/energy consumption;
- condition change;
- parking/dormancy;
- unload/reload;
- server restart reconstruction;
- ownership/credential check.

## Core Principle

> A vehicle is persistent movable property with physics presentation, not disposable transport spawned around the current player.