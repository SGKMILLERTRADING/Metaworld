# Metaworld — World Logistics Delivery System

**Status:** Canonical / Approved UnrealDevz Multiplayer Shooter Playlist Upgrade
**Engine:** Unreal Engine 5.8
**Runtime:** Blueprint-first / server-authoritative / persistent-world integrated

## Canonical Principle

A world delivery event brings one persistent container from a configured source/process into an approved world location. The delivery has a stable event identity, one manifest, one resulting ContainerID and one completion history.

## 1. Event State

Suggested fields:
- WorldEventID;
- DeliveryProfileID;
- ContainerID;
- source/service reference where applicable;
- destination region;
- scheduled/triggered timestamp;
- phase/status;
- manifest revision;
- access policy.

## 2. Delivery Presentation

A DeliveryProfile may select an aircraft, vehicle, parachute, drone, courier or other presentation appropriate to the world event.

Presentation timing, route, speed and altitude are tuning values. The visual actor does not own the delivered inventory.

## 3. Container / Manifest

The delivered package uses the normal persistent Container + ItemInstance architecture.

Contents are established once through an approved source/profile and do not reroll because the package is reopened, streamed or the server restarts.

## 4. Triggering

Production delivery events are server/world-system authorized. Development tools may trigger test events, but ordinary clients do not create authoritative deliveries.

## 5. Placement

The server validates a legal final location and uses safe world-item/container spawn rules so the package does not initialize inside invalid geometry.

## 6. Access

Access, ownership and transfer permissions remain governed by normal container/world rules. Arrival of the package does not automatically grant ownership to a nearby character.

## 7. Persistence

Persist event identity, final container location, manifest/current contents and completed/claimed/empty state as appropriate. Restart must not create a second package for an already-completed event.

## 8. Event Ledger

Significant deliveries can create Event Ledger records. Public visibility/news follows the existing world-knowledge and Smart News rules rather than automatically broadcasting every delivery.

## 9. Performance

Delivery presentation exists only while an event is active. After completion, the resulting package is handled as a normal persistent container. Distant presentation can use significance/LOD and compact replicated phase state.

## Acceptance Tests

1. One WorldEventID produces one ContainerID.
2. Restart does not duplicate the delivered package.
3. Manifest/current contents do not reroll on reopen.
4. Client cannot create production delivery state without authorization.
5. Final package placement is valid.
6. Normal container permissions and transfer rules remain active.
7. Presentation cleanup does not delete the persistent container.
8. Multiple events remain independently identifiable.

## Core Rule

Metaworld logistics deliveries are persistent world events with one event identity, one manifest and one resulting container. Delivery actors communicate the process; normal world inventory, access and persistence systems own the result.