# Metaworld — Persistent Backend & Dedicated Server Data Architecture

**Status:** Canonical Gap-Closure Architecture
**Engine:** Unreal Engine 5.8
**Runtime:** Blueprint-first gameplay / authoritative multiplayer world

## Purpose

Metaworld needs durable state that survives Actor unloading, travel, client disconnects and dedicated-server restarts. Local SaveGame and transient GameInstance state are not the authoritative world database.

## Canonical Topology

`Client -> Unreal Dedicated Server -> Persistence Service -> Durable Database`

The dedicated server owns live gameplay decisions for its active world. The persistence layer stores durable world records.

## Local Development Baseline

Early development should work on one development machine using self-hosted components:

- UE dedicated-server process;
- two or more local test clients;
- local persistence/API service;
- PostgreSQL or another proven transactional database.

Paid hosting can be added later without redesigning gameplay identity.

## Persistent Record Families

Durable records must support at least:

- AccountID;
- CharacterID and life/death state;
- ItemInstanceID and ContainerID;
- Equipment state;
- currency ledger;
- Property/Structure ownership;
- Business/Organization state;
- NPC persistent state;
- Mission/Event state;
- legal/custody state;
- Estate/Inheritance state;
- Vehicle state;
- world resources/objects that require persistence.

## Transaction Contract

Important persistent changes use explicit transactions containing:

- TransactionID / idempotency key;
- requesting identity;
- stable target IDs;
- expected revision where needed;
- authoritative validation;
- atomic commit;
- resulting revision;
- timestamp.

Retrying the same accepted transaction must not duplicate items, currency, rewards or ownership changes.

## Revision Rule

Important aggregates use revision numbers or an equivalent concurrency rule.

Example:

`Container Revision 55 -> transfer -> commit -> Revision 56`.

A stale request reloads/retries rather than overwriting newer state.

## Persistence Strategy

Use a combination of:

- authoritative identity/ownership/economy records;
- snapshots for reconstructing larger aggregates;
- durable event/audit records for important irreversible changes;
- timestamps for unloaded simulation;
- schema migrations as data evolves.

World persistence must not require every object to write every frame.

## High-Value Commit Rule

Durable commit is required before final success is reported for changes where loss/duplication would be unacceptable, including:

- currency transfer;
- persistent item transfer;
- property/business ownership changes;
- permanent-death/estate transitions;
- mission reward commitment;
- high-value crafting/production output.

Lower-priority analytics/presentation history may be deferred or batched.

## Restart / Recovery

Required test:

1. Perform persistent transaction.
2. Stop server.
3. Restart server.
4. Reconnect clients.
5. Confirm exactly one durable result.

## Session Boundary

Platform login/session technology and Metaworld gameplay persistence are separate concerns.

An online identity service may prove which user connected. Metaworld maps that authenticated identity to its own AccountID, CharacterIDs and persistent records.

## Region / Scale Direction

Stable IDs must remain valid if Metaworld later uses multiple world-server processes.

Future handoff direction:

`Region A -> durable handoff state -> Region B -> reconstruct Character state`.

Do not make persistent identity depend on one loaded Actor pointer.

## Replication vs Persistence

Replication answers: `What should connected clients know now?`

Persistence answers: `What remains true after disconnect, unload or restart?`

UE5.8 Iris and the generic replication system should be benchmarked with representative Metaworld loads before one path is locked globally.

## Minimum Acceptance Gate

Before larger persistent features are trusted, prove:

- two clients connect to dedicated server;
- AccountID -> CharacterID resolution;
- ItemInstance pickup/transfer persists;
- reconnect restores state;
- server restart restores state;
- duplicate request produces one result;
- stale revision cannot overwrite newer state;
- permanent death remains dead after restart;
- local client saves cannot redefine authoritative inventory/currency.

## Core Principle

> The dedicated server owns live authority; durable services preserve world truth beyond the life of any one server process.