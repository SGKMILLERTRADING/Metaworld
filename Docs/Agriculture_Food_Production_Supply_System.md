# Metaworld — Agriculture, Food Production & Supply System

**Status:** Canonical Gap-Closure Architecture

## Purpose

Food is already a major survival and household economic resource. Metaworld now needs a production-side architecture so food comes from persistent farms, workers, animals/crops, processing, storage, transport and businesses rather than infinite vendor restocks.

## Stable Identity

Use stable records such as:

- FarmID / ProductionSiteID;
- FieldID / PlotID;
- CropCycleID;
- LivestockGroupID where applicable;
- HarvestBatchID;
- StorageContainerID;
- ProductionJobID.

## Crop Lifecycle

A crop profile can define:

- seed/input requirements;
- climate/season compatibility;
- water requirements;
- growth duration;
- expected yield range;
- disease/weather sensitivity where useful;
- harvest window;
- processing needs.

Unloaded crops use timestamps and environmental summaries rather than continuous Actor simulation.

## Food Supply Chain

`Inputs -> Production -> Harvest -> Storage -> Processing -> Transport -> Business/Household -> Consumption`

Each stage uses real persistent items/containers where meaningful.

## Scarcity

Food production can fail or shrink because of supply, weather, labor, transport, utilities or world events. Vendors cannot conjure unlimited food merely because players need it.

## Professions / Jobs

Agriculture connects to professions and employment such as:

- farmer;
- ranch/livestock worker;
- driver/delivery worker;
- food processor;
- cook/baker;
- warehouse worker;
- shop/business staff.

## Storage / Spoilage

Food items may use shelf-life/spoilage profiles where useful. Refrigerated or protected storage can modify preservation through timestamp-based calculations.

Do not run per-frame spoilage logic for every food item.

## NPC / Household Integration

NPC households, businesses, institutions and player families consume real food supply at significance-appropriate fidelity.

## World Integration

Agriculture connects to:

- land/property;
- water/utilities;
- weather/calendar;
- vehicles/logistics;
- businesses;
- jobs/wages;
- taxes;
- markets;
- News/world events when shortages or major surpluses matter.

## Initial Vertical Slice

Prove one small farm-to-shop chain:

1. persistent field/plot;
2. planted crop cycle;
3. timestamp growth;
4. harvest creates real item batch;
5. storage container;
6. transport/delivery;
7. shop stock receives items;
8. household/player buys and consumes them;
9. restart preserves all stages.

## Core Principle

> Food exists because the world produces, stores and moves it. A persistent economy should be able to experience abundance, shortage and recovery.