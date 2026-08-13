# Metaworld — World Exit / Transition Countdown System

**Status:** Canonical / Approved UnrealDevz Multiplayer Shooter Playlist Upgrade
**Engine:** Unreal Engine 5.8
**Runtime:** Blueprint-first / multiplayer / server-authoritative / persistent-world compatible

## Canonical Principle

A world exit/transition zone is an authenticated request to move a character between approved world contexts after a cancellable countdown. It does not act as a magical save point, invulnerability zone, loot insurance system, or same-character resurrection mechanism.

> Entering an exit zone starts a transition request. The world continues to exist, the server continues to own character state, and leaving or invalidating the zone cancels the request.

Related canon:
- `Docs/Real_Time_Life_Utilities_Advertising_VIP_GrimKoin_Death_Legacy.md`
- `Docs/UI_Base_Widget_Modal_Input_Lifecycle_System.md`
- `Docs/Persistent_Item_Interaction_Inventory_Architecture.md`

## 1. Transition Zone Identity

Suggested data:
- `TransitionZoneID`;
- `TransitionProfileID`;
- source world/region;
- destination type/reference;
- required countdown duration;
- allowed character states;
- access/permission policy;
- cost/ticket/service requirement where designed;
- cancel rules;
- presentation profile.

The tutorial's 10-second countdown is useful prototype tuning, not a universal Metaworld value.

## 2. Server-Owned State Machine

Conceptual flow:

`Outside`
-> `EligibleInsideZone`
-> `CountdownActive`
-> `TransitionCommitted`
-> `Transfer/Arrival`

Cancellation paths include:
- character leaves the zone;
- access becomes invalid;
- character enters an incompatible state;
- transition service becomes unavailable;
- character dies before commitment;
- explicit cancellation where the profile permits it.

The client may display the timer, but the server owns eligibility and completion time.

## 3. No Save-Zone Semantics

Metaworld persistence is continuous. A transition zone does not decide whether inventory/property is saved.

Character, ItemInstance, Container, bank, property, injury, Condition and world state are already persistent according to their own systems.

Do not use `exit reached -> save everything` as the canonical persistence model.

## 4. Death Compatibility

If the character dies before transition commitment, the permanent-death pipeline wins.

Eligible carried physical ItemInstances follow corpse/estate/world rules. The dead CharacterID is not transferred to another map and resurrected.

A later account/new-character flow is a separate process.

## 5. Destination Types

The same transition architecture may later support:
- building/interior partition transitions where needed;
- transit terminals;
- ferries/airports/travel services;
- instanced activities where Metaworld explicitly uses them;
- admin/test transfer;
- safehouse/home entry presentation where the world architecture requires a context switch.

Transition does not automatically imply safety.

## 6. UI

Local UI may show:
- destination;
- countdown;
- cancellation reason;
- access requirement;
- transition status.

The widget is local presentation and should not be replicated as authoritative state to unrelated players.

## 7. Multiplayer

Each character has an independent transition request. One player entering a zone must not start another player's timer.

Server validates the character's current presence/eligibility at commit time. Late packets or stale UI cannot force a transition after cancellation.

## 8. Performance

Use overlap/interaction events plus bounded server timing. No permanent Tick is required just to determine whether a stationary player remains in a simple zone; use timers/events/state validation appropriate to the transition profile.

## Acceptance Tests

1. Entering an eligible zone starts one server-authorized countdown.
2. Leaving before completion cancels it.
3. Re-entering creates a fresh valid request according to policy.
4. UI countdown cannot force early completion.
5. Character death cancels transition and invokes permanent-death rules.
6. Inventory is not duplicated or specially saved by the transition widget.
7. Two players can have independent countdowns.
8. Destination/access becoming invalid cancels safely.
9. Restart/reconnect cannot duplicate a committed transfer.
10. Controller/KBM can cancel/confirm where the profile exposes those actions.

## Core Rule

Metaworld transition zones coordinate movement between approved world contexts; they never replace continuous persistence, ownership, or permanent-death rules.