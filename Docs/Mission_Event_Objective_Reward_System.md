# Metaworld — Mission Event, Objective & Reward System

**Status:** Canonical / Approved UnrealDevz Multiplayer Shooter Playlist Upgrade
**Engine:** Unreal Engine 5.8
**Runtime:** Blueprint-first / server-authoritative / persistent-world integrated / data-driven

## Canonical Principle

A mission is a structured world activity built from stable definition data, one persistent MissionInstance state, explicit objectives and authoritative completion/reward rules. Trigger volumes and widgets may start or present a mission, but they do not own its progress.

> World systems produce objective progress. Mission UI reports it. Rewards commit once after validated completion.

## 1. Definition vs Instance

`MissionDefinitionID` can define title, availability, start triggers, objective graph, participant policy, timing, reward profile and world consequences.

`MissionInstanceID` records one occurrence with start time, participants, objective state, linked world references, completion/failure/cancel state, reward state and revision/history.

## 2. Start / Reveal Triggers

Possible triggers include:
- entering an area;
- NPC/service interaction;
- accepting a contract;
- item/evidence discovery;
- scheduled/world event;
- profession/business action;
- admin/test tooling.

An overlap volume is only a trigger source.

## 3. Objective Contracts

Objectives use stable IDs and event-driven progress.

Possible categories:
- reach/visit;
- interact/use;
- collect/deliver legitimate ItemInstances;
- protect/escort/repair/build;
- investigate/discover/report;
- complete profession/service work;
- activate/deactivate world mechanisms;
- maintain a condition for a duration;
- other data-driven objective contracts.

Do not reduce every mission to one hardcoded counter.

## 4. Linked World State

If a mission creates or references temporary world actors/objects, the MissionInstance records their stable references and listens to their authoritative state changes.

Persistent NPCs/world objects are not duplicated simply because a mission started.

## 5. Difficulty / Presentation

Difficulty is a data/profile concept that can influence authorized content variables, restrictions, duration or reward policy. HUD color/text merely presents difficulty.

## 6. Rewards

RewardProfile may grant/transfer legitimate outputs such as:
- GrimKoin/PromoKoin under economy rules;
- ItemInstances or one persistent reward container;
- reputation/faction changes;
- profession/skill progression;
- ability/recipe knowledge;
- property/service access;
- world-state consequences.

Rewards are server-authoritative and idempotent. A committed reward cannot be granted again by reopening UI or reconnecting.

## 7. Container Rewards

Any reward container uses the normal `ContainerID` + ItemInstance architecture. Its contents are established once and do not reroll on reopen/restart.

## 8. Multiplayer Scope

Mission scope explicitly defines progress/reward ownership:
- individual;
- party/group;
- organization/faction;
- public/world event.

Server records participant eligibility where shared rewards require it.

## 9. Persistence / Reconnect

MissionInstance state persists according to its lifetime policy. Reconnect restores authoritative progress rather than restarting it unless the definition explicitly specifies a reset.

## 10. UI / Notifications

UI may show title, objectives, progress, known requirements, authorized reward information and completion state. Widgets never mutate authoritative progress directly.

## 11. Event Ledger

Significant public mission outcomes may create Event Ledger records and become eligible for Smart News. Private/local activities do not automatically become public news.

## 12. Performance

- objective updates are event-driven;
- no global objective Tick/scans;
- temporary mission presentation exists only while relevant;
- UI updates on MissionInstance revision changes;
- world content follows normal significance/streaming rules.

## Acceptance Tests

1. Valid trigger creates/opens the intended MissionInstance once.
2. Re-entering a trigger does not duplicate an already-live instance unintentionally.
3. Objective progress comes from authoritative world events.
4. Reconnect restores progress correctly.
5. Reward commits exactly once.
6. Reward container cannot reroll/duplicate contents.
7. Multiplayer scope controls who receives progress/rewards.
8. UI cannot grant completion or rewards.
9. Cleanup of temporary presentation does not erase MissionInstance history.
10. New objective categories can be added through data/contracts.

## Core Rule

Metaworld missions are persistent event-driven workflow instances: triggers begin them, world systems advance them, and the server commits one legitimate completion/reward result.