# Metaworld — Construction Multiplayer Replication & Authority System

**Status:** Canonical / Approved Phase 20 + Phase 60 Upgrade

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first

## Canonical Principle

Metaworld construction is client-responsive but server-authoritative. Clients may preview, request and present construction actions, while the server owns every permanent structure, resource transaction, construction stage, damage state, relationship change and legal world-state transition.

Core rule:

> Replicate durable construction state; RPC-request actions; multicast only genuinely transient presentation when needed. Settled structures do not continuously replicate movement or replay visual state that clients can derive from authoritative data.

The UE4 tutorial concepts of server-side spawning, replicated build state and synchronized multiplayer construction are approved. Metaworld upgrades the tutorial away from universal Replicate Movement, blanket Replicated variables and Multicast-for-every-visual-change patterns into a scalable persistent-world replication architecture.

---

# 1. Phase Ownership

This system crosses two roadmap areas without duplicating systems.

## Phase 20 — Construction Gameplay State

Phase 20 owns:

- Buildable / Variant identity
- placement validation
- construction stages
- material delivery / consumption
- work units
- support / snap / opening relationships
- relocation / demolition state
- damage / destroyed state integration
- persistence

## Phase 60 — Multiplayer Replication

Phase 60 owns:

- client/server authority boundaries
- replicated actor/state strategy
- RPC request patterns
- RepNotify/client state application
- relevancy
- dormancy
- network update budgets
- late-join reconstruction
- replication stress testing

Construction defines **what** state exists. Phase 60 defines **how much of that state crosses the network, when, and to whom**.

---

# 2. Authority Model

## Client May

- enter Build Mode locally;
- move/rotate a local ghost;
- show valid/blocked prediction;
- browse catalog/resources;
- request placement;
- request resource delivery;
- request construction work;
- request interaction with doors/windows;
- request relocation/demolition;
- show predicted/contextual UI;
- play approved cosmetic presentation after authoritative state is known.

## Server Owns

- permanent Actor creation;
- Structure/Object ID assignment;
- authoritative Buildable/Variant definition;
- final transform;
- property/zoning/profession/tool/resource/support validation;
- construction Site ID and stage;
- material ledger;
- work units;
- ownership/permissions;
- support/snap/opening relationships;
- relocation/demolition transactions;
- durability/damage/destruction state;
- collision/traversal consequence;
- persistence;
- news/Event Ledger facts generated from construction consequences.

The client never creates authoritative permanent construction by itself.

---

# 3. Placement Request Flow

Recommended Blueprint-first flow:

`Local Build Ghost`
-> player confirms
-> client sends `RequestPlaceBuildable(...)` through an owned replicated Player/Character/Build Component RPC path
-> server resolves authoritative Buildable Definition
-> server clamps/validates requested transform/orientation
-> server checks property / zoning / footprint / obstruction / snap / support / resources / profession / permissions
-> if rejected: send/replicate rejection reason to requesting client
-> if approved: server creates persistent Construction Site / finished object according to definition
-> server assigns stable Structure/Site IDs and relationships
-> replicated actor/state becomes visible to relevant clients

The server never trusts client preview fields such as:

- `CanBuild = true`;
- client footprint size;
- client resource totals;
- client SnapPoint occupancy;
- client support claim;
- client Buildable recipe/cost;
- client finished state.

The client submits intent and candidate data; the server reconstructs truth from authoritative definitions/world state.

---

# 4. Do Not Replicate the Build Ghost by Default

The ordinary placement ghost is local presentation.

Do not network every:

- camera trace;
- mouse movement;
- stick movement;
- fine-rotation step;
- green/red material update;
- temporary snap candidate.

This avoids turning construction preview into continuous bandwidth traffic.

If a future co-op feature intentionally lets teammates see another player's active blueprint/ghost, use a separate low-frequency, relevance-limited preview channel/state rather than making the normal placement ghost authoritative.

---

# 5. Durable State vs Transient Events

## Durable / Replicated State

Use replicated/RepNotify-style state for facts that late joiners or newly relevant clients must know, for example:

- Structure/Object ID;
- Buildable/Variant ID;
- authoritative settled transform;
- owner/property references where visible/needed;
- construction state/stage;
- compact progress/work state;
- material requirement/delivery summary when relevant;
- damage state;
- breached/destroyed state;
- door/window stable state;
- significant opening/support/relationship revision/state;
- prefab logical state;
- utility connection state when relevant;
- relocation/demolition stable result.

## Transient / Cosmetic RPC Events

RPC/Multicast may be useful for one-shot presentation such as:

- nearby placement sound;
- impact sound;
- dust burst;
- a short construction animation cue;
- demolition warning effect;
- destruction impulse/seed presentation;
- temporary local feedback that does not need to exist for late joiners.

Transient events never replace persistent state.

---

# 6. RepNotify / State-Driven Presentation

Persistent world visuals should derive from authoritative replicated state.

Example:

`ConstructionState = UnderConstruction`

Client presentation can resolve:

- construction-stage mesh;
- temporary material;
- stage collision;
- available interaction prompts.

Later:

`ConstructionState = Completed`

RepNotify/state application updates:

- finished mesh/material/creator finish;
- finished gameplay collision;
- available openings/snaps;
- normal interactions;
- construction HUD state.

Do not require a historical `MultiFinishBuild` RPC for correctness.

Late joiners reconstruct directly from the replicated/persisted Completed state.

---

# 7. Replicate Movement Is Not Universal

The tutorial enables `Replicate Movement` on BuildMaster actors. Metaworld rejects this as a universal construction default.

## Settled Structural Pieces

Examples:

- foundation;
- wall;
- floor;
- roof;
- column;
- finished prefab shell.

These normally do **not** need continuous movement replication after authoritative placement.

They have a stable transform. Their initial/committed authoritative location is part of actor/state creation/replication, then they remain settled.

## Relocation

Relocation uses the existing transaction model:

- original structure remains authoritative;
- client moves a temporary ghost;
- server validates destination;
- server commits one new settled transform/relationship state.

Do not turn ordinary relocation into continuous networked physics movement.

## Doors / Windows

Replicate state/transition intent such as:

- Closed;
- Opening;
- Open;
- Closing;
- Locked/Breached/etc.

Clients animate the accepted transition locally from shared data/curves rather than streaming component transform every frame.

## True Physics Objects

Only objects that genuinely simulate authoritative networked physics should use an appropriate physics-replication strategy. Construction rubble/shards remain subject to the Episode 16 destruction-performance rules.

---

# 8. Resource Delivery Replication

Episode 20 remains authoritative.

Flow:

`Client requests Deliver Material`
-> server validates Site ID / stage / source inventory / permissions / quantity / item compatibility
-> server locks/serializes transaction
-> authoritative source inventory debited
-> construction site material ledger credited
-> both persisted
-> compact changed state replicated to relevant clients
-> contextual UI refreshes

Clients do not multicast inventory subtraction.

Clients do not directly replicate raw local inventory arrays into the construction site.

Replicate only the material/progress state each connection actually needs.

---

# 9. Construction Work Replication

Construction work is server-authoritative.

Client requests an action such as:

`RequestPerformConstructionWork(SiteID, ActionContext)`

Server validates:

- site exists;
- stage is ready;
- required resources are available;
- worker is authorized;
- profession/skill/tool requirements;
- range/state;
- cadence/anti-spam;
- stamina/condition where applicable.

Then server increments authoritative work/progress.

Replicate compact resulting progress/state, not every local animation-frame value.

Nearby worker animation can be replicated/presented through the character animation/action system. Distant construction progress can remain data-only.

---

# 10. Damage / Destruction Replication

Episode 16 remains canonical:

- server owns durability and terminal destruction state;
- server updates authoritative collision/traversal/support/relationship consequences;
- relevant clients receive compact damage/destruction state/event;
- nearby clients may play Chaos/Geometry Collection presentation;
- individual rubble shards are not authoritative persistent network objects by default;
- late joiners load the stable destroyed/breached representation.

Do not depend on `Multicast Destroy Build` as the only truth.

Do not keep every destructible component continuously network-physics replicated merely because a destruction effect may happen once.

If a specific large debris object matters to gameplay, promote/create a small authoritative debris/blockage Actor with its own explicit replication policy.

---

# 11. Structural Relationship Replication

The authoritative relationship graph remains server-side/persistent truth.

Not every client needs the complete global graph.

Replicate or expose only relationship information needed for relevant gameplay/UI, for example:

- current opening occupancy;
- local snap occupancy;
- stability result;
- support warning;
- direct attachment relationship needed for interaction;
- demolition/relocation dependency preview for authorized player.

Large internal graph structures should not be dumped wholesale to every connection every frame.

Relationship changes are event-driven and can carry revision/state identifiers where useful.

---

# 12. Relevancy

A persistent city may contain enormous numbers of buildable Actors.

A client should receive only Actors/state relevant to that connection.

Use Unreal relevancy principles and project-specific distance/ownership/world-partition logic so a player in one district does not continuously receive updates for every construction object in every other district.

Possible relevance factors:

- physical distance;
- same streamed/world region;
- ownership/private UI needs;
- active construction interaction;
- active damage/destruction event;
- property-management view;
- emergency/public event relevance.

Do not mark ordinary buildables `Always Relevant` by default.

---

# 13. Dormancy

Dormancy is a primary construction scalability tool.

Typical settled structure lifecycle:

`Placed / changed`
-> actor awake for replication
-> authoritative state reaches relevant clients
-> no further meaningful change
-> actor enters appropriate dormancy

Wake/flush dormancy when meaningful state changes, such as:

- construction stage advances;
- material state changes when remote clients need it;
- damage state changes;
- door/window stable state changes if actor policy requires;
- ownership/permission-visible state changes;
- relocation commits;
- demolition occurs;
- utility state changes;
- relationship/stability state changes.

Then return to dormant state when settled.

Do not leave thousands of unchanged buildings awake in the replication gather/update path.

---

# 14. Net Update Frequency / Bandwidth

Not all construction actors require the same update rate.

Examples:

- settled wall: extremely low/none while dormant;
- active construction site: low-to-moderate event-driven state updates;
- door transition: replicate state transition, local animation;
- actively damaged object: temporary higher relevance/update need;
- physics-critical gameplay debris: explicit dedicated policy.

Do not use character-like update frequencies for static buildings.

Avoid replicating properties that clients can derive from other replicated state.

---

# 15. Actor Component Replication

Actor Components do not need to replicate merely because they exist.

For reusable construction components:

- replicate only components that own connection-relevant authoritative state/RPCs;
- prefer the owning buildable actor to replicate compact canonical state where that avoids unnecessary component network overhead;
- do not mark every support/inventory/interaction/helper component replicated by default;
- UI-only/editor-only/local-preview components do not replicate.

`BPC_MW_BuildComponent` on the player may use an owned RPC path for construction requests, but the permanent world buildable remains server-owned world state.

---

# 16. Multiplayer RPC Ownership

Client-to-server RPCs must originate through an Actor/Component the client legitimately owns, such as its Player Controller / possessed Character / owned Build Component path.

Do not rely on a client calling a Server RPC directly on an arbitrary world wall it does not own as the universal interaction architecture.

Recommended request routing:

`Local Input`
-> owned player interaction/build component
-> Server Request RPC
-> server validates target Structure/Site ID
-> server applies authoritative world action

This is compatible with interaction, resource delivery, construction work, move, demolition and damage request flows.

---

# 17. Multicast Rules

Multicast is **not banned**, but it is restricted to appropriate transient presentation.

Approved examples may include:

- one-shot nearby construction effect;
- dust/spark/impact presentation;
- destruction impulse/seed cue;
- temporary alarm/effect.

Rejected as persistent truth:

- `MultiSetMesh` as the only record of selected/final mesh;
- `MultiFinishBuild` as the only record that construction finished;
- `MultiDestroyBuild` as the only record that a structure is destroyed;
- repeated multicast progress values;
- repeated multicast movement for settled structures.

If a client joins late or an Actor becomes relevant later, replicated/persisted state must be sufficient to reconstruct the correct world without replaying old multicasts.

---

# 18. Late Join / Relevancy Re-Entry

A newly connected player or newly relevant client must be able to reconstruct:

- correct Buildable/Variant;
- settled transform;
- construction stage/progress as needed;
- finished material/creator finish;
- door/window stable state;
- damage/breach/destroyed state;
- relevant opening/attachment state;
- utility/stability state needed for presentation/interaction.

They do not need historical RPC replay for:

- placement sound;
- individual hammer actions;
- past dust effects;
- old Chaos shard trajectories;
- every material delivery event.

Persistent state is the recovery source.

---

# 19. Persistence vs Replication

Replication is not the save system.

Replication answers:

`What should this currently relevant client know now?`

Persistence answers:

`What does the world remain true even when nobody is connected/nearby?`

The server persists significant construction state independently of whether an Actor is currently relevant to any client.

On stream/load/server restart, authoritative persistent records recreate the correct replicated world state.

---

# 20. Networked Physics / Chaos Guardrail

Unreal Engine 5.8 supports networked physics, but that does not make networked physics the default architecture for construction.

Use networked physics only where physical simulation is actually gameplay-critical.

Construction default remains:

- static/settled authoritative structures;
- state-driven door/window transitions;
- server damage/stability decisions;
- local/budgeted Chaos presentation;
- small authoritative debris proxies only when required.

This protects server CPU, bandwidth and frame pacing.

---

# 21. Generic Replication Baseline / Scaling Research

Metaworld's Blueprint-first baseline should work with Unreal's standard replicated Actors, properties/RepNotify, RPCs, relevancy and dormancy.

Unreal Engine 5.8 also exposes larger-scale replication systems such as Replication Graph and Iris. These should be evaluated deliberately during Phase 60 performance testing rather than becoming an unverified hard dependency during early Blueprint construction work.

Reasons:

- the project must remain functional before advanced replication optimization;
- large-world actor counts need measured profiling;
- plugin/system maturity and Blueprint integration must be verified against the exact UE5.8 project configuration;
- replacing replication infrastructure later must not change construction gameplay truth.

The construction data model must therefore remain replication-system-agnostic enough to optimize later.

---

# 22. Security / Exploit Rules

A modified client cannot:

- spawn permanent build actors;
- choose its own authoritative Buildable cost;
- forge legal transform/support;
- set construction complete;
- subtract another player's inventory;
- deliver nonexistent resources;
- increase Work Units;
- set Health/Destroyed state;
- relocate/demolish another player's structure;
- forge opening/snap relationships;
- force multicast persistent state;
- keep a local illegal object after server rejection.

Server validation always uses stable IDs and authoritative data.

---

# 23. Performance Rules

- no continuous movement replication for settled structures;
- no Always Relevant on ordinary construction actors;
- use dormancy aggressively for unchanged persistent buildables;
- use relevancy/streaming to limit connection scope;
- keep Net Update Frequency appropriate to object behavior;
- replicate only state clients need;
- derive presentation from compact state where possible;
- do not multicast state changes that RepNotify can reconstruct;
- no full global relationship/material/inventory graph replication;
- no per-frame network updates for construction progress;
- no default authoritative replication of every Chaos shard;
- wake actors only for meaningful state changes;
- profile server replication CPU, bandwidth, packet loss and late-join behavior with large structure counts.

---

# 24. Blueprint-Oriented State Layout

Possible compact shared replicated state can be organized into small structs/variables rather than dozens of unrelated booleans.

Conceptual examples:

`S_MW_BuildableNetState`

- stable Structure ID
- Buildable/Variant ID
- Construction State / Stage ID
- damage state
- stable interaction/opening state
- state revision/version

`S_MW_ConstructionProgressNetState`

- Stage ID
- Current Work Units or normalized progress where needed
- material-readiness summary
- blocked state/reason code where appropriate

Keep large private/internal server data out of public replication when clients do not need it.

---

# 25. Initial Multiplayer Vertical Slice

At minimum test with server + two clients:

1. Client A enters Build Mode; Client B does not receive A's ordinary ghost updates.
2. Client A requests legal Foundation placement.
3. Server independently validates and spawns the persistent site.
4. Client B sees the replicated site.
5. Client A attempts forged/illegal placement -> server rejects; Client B sees nothing.
6. Client A delivers materials; server atomically updates source/site; Client B sees relevant construction-state change.
7. Simultaneous resource delivery by A/B cannot duplicate or over-credit materials.
8. A/B contribute valid Work Units; stage state remains consistent.
9. Stage completes once; clients derive finished presentation from authoritative state.
10. Late-joining Client C sees the already-completed structure without receiving historical FinishBuild RPCs.
11. Settled Foundation/Wall become dormant and stop unnecessary update work.
12. Door interaction replicates accepted state and both clients animate it consistently without per-frame door-transform replication.
13. Client attempts unauthorized Move/Demolish -> server rejects.
14. Authorized relocation commits one legal new settled transform and relationships.
15. Damage is server-authoritative; destroyed state reaches all relevant clients.
16. Chaos fracture can differ cosmetically without disagreement about wall collision/breach/support truth.
17. Late-joining Client C sees settled destroyed state without historical shard trajectories.
18. Destroyed support triggers identical authoritative stability result for all clients.
19. Actor becoming irrelevant then relevant again reconstructs correct state.
20. Large test set of idle structures demonstrates dormancy/relevancy preventing continuous network load.
21. Packet loss/latency test does not allow duplicate material transactions, duplicate stage completion or duplicate demolition.
22. Keyboard/mouse, Xbox-style and PlayStation-style requests all reach the same authoritative server actions.

---

# Core Rule

> Metaworld multiplayer construction sends intent upward and authoritative state outward. The client predicts the experience; the server decides the world. Persistent facts replicate through compact state that late joiners can reconstruct, while RPCs and multicasts are reserved for requests and transient presentation. Settled structures sleep instead of consuming movement, CPU and bandwidth forever.