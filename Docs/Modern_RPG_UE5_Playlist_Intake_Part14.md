# Metaworld — Modern RPG UE5 Playlist Intake — Part 14

**Status:** Canonical Playlist Intake Log Continuation

**Continues:** `Docs/Modern_RPG_UE5_Playlist_Intake_Part13.md`

**Playlist Engine:** Unreal Engine 5.4 tutorial series

**Metaworld Target Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first

All permanent intake rules from Part 1 remain active.

This Part contains **Episodes 112–122**.

The submitted Swimming Mechanics/Animations summary appeared twice in the source message and is counted once.

---

# Episode 112 — Ladder Climb Down / Exit / Camera / Regrab Fixes

**Classification:** LOCKED + UPGRADE — LADDER FINALIZATION.

**Phase Ownership:** Traversal + Movement + Animation + Interaction + Water handoff.

Detailed companions:

- `Docs/Ladder_Climbing_Traversal_System.md`
- `Docs/Ladder_Climb_Down_Camera_Regrab_Finalization_System.md`

## Approved Tutorial Intent

- climb ladder from top/downward;
- refine entry/exit overlap behavior;
- stop residual movement on mount;
- orient camera/character toward ladder;
- prevent immediate accidental re-climb after dropping;
- clean Blueprint graph organization.

## Metaworld Upgrades

- top entry uses authored ladder-local target/approach data, not one universal world-Z threshold;
- sprint/ground momentum is consumed/reconciled before entry alignment;
- exit overlap is a candidate signal and fires only from the correct traversal state;
- camera facing comes from ladder-local orientation with accessibility-friendly transition;
- dropping restores Falling and requires fresh valid re-entry intent rather than immediately re-triggering from the same overlap;
- ladder transitions reconcile Water/Swimming/Breath state through environment state rather than stale booleans;
- collapsing nodes improves readability but does not move traversal ownership back into a monolithic Player Blueprint.

### Episode 112 Principle

> A finished ladder is bidirectional, state-safe and environment-aware; mounting, dropping and exiting cannot be controlled accidentally by stale overlap or momentum state.

---

# Episode 113 — Base Resource Gathering / Iron Ore

**Classification:** UPGRADE — NEW RESOURCE GATHERING / HARVESTING DOMAIN.

**Phase Ownership:** Item DNA + Crafting Materials + Professions + Interaction + World Economy.

Detailed companion:

`Docs/Resource_Gathering_Harvesting_Tools_Depletion_Regeneration_System.md`

## Approved Tutorial Intent

- reusable resource-node foundation for mining/logging/gathering;
- hold/progress interaction;
- character faces resource during work;
- Fab asset authoring/collision/material setup;
- resource profile chooses output item;
- quantity feedback/notification.

## Metaworld Upgrades

- stable `ResourceNodeID` + persistent remaining reserve;
- Mine/Cut/Gather become interaction/capability tags rather than a permanently closed resource enum;
- progress UI mirrors authoritative gathering work;
- server validates access/tool/profession/resource reserve before reward;
- random yield is rolled once by the server and reduces the real reserve;
- output is persistent ItemInstance/quantity integrated with inventory/economy/crafting;
- property/permit/theft/environment rules can govern harvesting;
- quickslot initial bugfix remains maintenance under existing Quickslot architecture.

### Episode 113 Principle

> Gathering converts real persistent world reserves into real items through authorized work; the resource mesh and radial bar never mint rewards themselves.

---

# Episode 114 — Pickaxe / Mining Animation / Montage Notify

**Classification:** UPGRADE — APPROVED TOOL + ANIMATION PIPELINE.

**Phase Ownership:** Resource Gathering + Equipment/Tools + Animation + Audio/VFX.

Detailed companions:

- `Docs/Resource_Gathering_Harvesting_Tools_Depletion_Regeneration_System.md`
- `Docs/Animation_Authoring_Control_Rig_Root_Motion_Workflow.md`

## Approved Tutorial Intent

- real pickaxe content/item representation;
- socket/attachment setup;
- Control Rig/Sequencer-authored mining animation;
- dynamic tool presentation during the action;
- Montage Notify for impact-timed sound/VFX;
- resource-specific animation behavior.

## Metaworld Upgrades

- pickaxe is a real ItemInstance/tool capability when required, not a free spawned gameplay tool;
- animation profile is selected from resource/tool capability data rather than giant Switch graphs as content grows;
- tool durability/quality/skill can affect work;
- Montage Notify aligns impact presentation/work phase but server remains authoritative for extraction;
- spawned visual tool actor represents the authoritative/equipped/borrowed tool state and is cleaned up without changing ownership.

### Episode 114 Principle

> The mining animation can make the strike feel precise, but only the validated resource/tool transaction decides whether that strike extracts material.

---

# Episode 115 — Resource Respawn / Mine-Cut-Gather Prompts / Montage Sections

**Classification:** PARTIAL REJECT + UPGRADE — REGENERATION MUST MATCH RESOURCE NATURE.

**Phase Ownership:** Resource Gathering + Ecology/Economy + Interaction + Animation.

Detailed companion:

`Docs/Resource_Gathering_Harvesting_Tools_Depletion_Regeneration_System.md`

## Approved Tutorial Intent

- depleted resource presentation can hide/disable collision;
- regeneration can be timestamp/timer driven when legitimate;
- Mine/Cut/Gather prompt vocabulary;
- impact particles at tool location;
- Montage Sections for repeatable work loops.

## Rejected Tutorial Interpretation

No universal resource respawn timer.

## Metaworld Upgrades

- plants/berries may regrow;
- trees can regrow over meaningful world/ecological time;
- ore/mineral deposits are finite/depletable unless an explicit world/geological rule legitimately creates new reserves;
- unloaded regeneration is resolved from persistent timestamps/state rather than keeping every node/component timer alive;
- debris disappearance is independent from resource regeneration;
- animation loop count does not equal material quantity unless the authoritative work profile commits extraction at those phases.

### Episode 115 Principle

> Renewable resources recover because their world rules support recovery; finite resources can run out. Respawn is never permission to create infinite matter.

---

# Episode 116 — Destructible Resources / Geometry Collections

**Classification:** UPGRADE — APPROVED CHAOS PRESENTATION LAYER.

**Phase Ownership:** Resource Gathering + Chaos/Destruction + Performance.

Detailed companion:

`Docs/Resource_Destruction_Chaos_Fracture_Presentation_System.md`

## Approved Tutorial Intent

- Geometry Collection / Fracture workflow;
- tuned fracture counts/noise/clustering/damage thresholds;
- fractured rock/tree presentation;
- debris sleep/removal;
- timed actor cleanup;
- resource-specific destruction audio.

## Metaworld Upgrades

- Chaos does not own resource reserve/yield;
- physics shards are not automatically inventory items;
- resource transaction commits extraction/depletion first, then triggers fracture presentation;
- tutorial values such as 30 pieces or fixed damage thresholds are per-asset prototype numbers only;
- low scalability/distant clients may use cheaper destruction representation;
- cleanup lifetime is visual and does not imply resource respawn;
- cap/budget simultaneous Chaos events.

### Episode 116 Principle

> Chaos shows the resource breaking; the persistent Resource system decides what existed, what was harvested and whether anything remains.

---

# Episode 117 — Ledge Climbing / Hang / Climb Up / Drop

**Classification:** UPGRADE — NEW LEDGE / MANTLE TRAVERSAL DOMAIN.

**Phase Ownership:** Traversal + Animation + Movement + Stamina/Encumbrance.

Detailed companion:

`Docs/Ledge_Mantle_Climb_Traversal_System.md`

## Approved Tutorial Intent

- authored ledge collision/positioning targets;
- facing/range eligibility;
- hang state;
- root-motion climb-up montage;
- drop/let-go action;
- suppress unrelated interactions during ledge traversal.

## Metaworld Upgrades

- stable traversal profile/targets rather than ledge-specific Player offsets;
- `MOVE_Flying` may support a prototype hang state but never becomes semantic free-flight capability;
- explicit Approach/Grab/Hang/ClimbUp/Drop/Interrupted state;
- server revalidates grab and top landing clearance;
- Motion Warping/root motion align authored action to valid target;
- Stamina/Encumbrance/injury can affect hang/climb;
- dynamic trace-detected ledges can later use the same contract; authored overlap ledges are not the only future form.

### Episode 117 Principle

> A ledge is a validated traversal target; root motion presents the mantle while gameplay owns the grab, hang, landing and fall states.

---

# Episode 118 — Ledge Decals / Visual Climb Markers

**Classification:** UPGRADE — APPROVED OPTIONAL PRESENTATION / ACCESSIBILITY.

**Phase Ownership:** Traversal + Environment Art + Accessibility + Performance.

Detailed companion:

`Docs/Ledge_Mantle_Climb_Traversal_System.md`

## Approved Tutorial Intent

- Fab/prebuilt decal materials;
- custom transparent decal authoring;
- reusable Decal Component on authored ledges;
- configurable color/opacity;
- prevent unwanted decal projection onto character.

## Metaworld Upgrades

- decal is optional presentation and never traversal truth;
- profiles can support environmental wear, paint/chalk, mission markers or accessibility highlighting;
- players can potentially use a reduced/no-marker presentation where design permits;
- decals are performance-budgeted/cullable;
- ledge remains climbable according to traversal data even if marker is hidden.

### Episode 118 Principle

> Visual markers tell the player where a climb may be; the traversal profile decides whether the climb is actually legal.

---

# Episode 119 — Swimming Foundation / Water Body / Depth Detection

**Classification:** UPGRADE — NEW SWIMMING / WATER MOVEMENT DOMAIN.

**Phase Ownership:** Movement + Water Environment + Animation + Controller.

Detailed companion:

`Docs/Swimming_Water_Breath_Drowning_Survival_System.md`

## Approved Tutorial Intent

- UE Water Body environment;
- Start/Stop Swimming transitions;
- depth-sensitive swim eligibility;
- buoyancy/water movement setup;
- prevent shallow-water false swimming;
- disable Foot IK while swimming.

## Metaworld Upgrades

- one environment/water-contact state owns WaterBody context, surface/depth samples and semantic swim state;
- entering a water overlap does not automatically mean full Swimming;
- body-relative pelvis/chest/head/airway samples support different avatar proportions;
- water queries are bounded to relevant characters/water contexts, not global scans;
- Character Movement Swimming is implementation, while Metaworld tracks explicit Wading/Surface/Underwater/Exit states;
- Foot IK/ground systems restore from state rather than loose DoOnce logic.

### Episode 119 Principle

> Water overlap starts environment evaluation; actual depth and body state decide whether the character wades, swims or remains on land.

---

# Episode 120 — Swimming Animation / Directional Movement / Surface Control

**Classification:** UPGRADE — APPROVED SWIM MOVEMENT + ANIMATION EXTENSION.

**Phase Ownership:** Swimming + Animation + Movement + Performance.

Detailed companion:

`Docs/Swimming_Water_Breath_Drowning_Survival_System.md`

## Approved Tutorial Intent

- retarget swimming/treading animations;
- swimming Blend Space;
- underwater directional movement;
- ascend/descend control;
- surface detection to prevent flying out of water;
- body-depth based transition.

## Metaworld Upgrades

- surface and underwater swim are explicit states/profiles;
- surface vertical movement is constrained by queried water surface rather than camera pitch alone;
- head socket is acceptable prototype sample, but production uses avatar-compatible airway/head profile;
- animation belongs in `ABP_MW_Master`/linked swim layer;
- richer directional blend/layers may replace a 1D prototype as fidelity grows;
- current/waves/equipment drag can later feed the same movement profile.

### Episode 120 Principle

> Swimming follows water-relative movement and validated surface depth; looking upward must never turn Swimming into Flying.

---

# Episode 121 — Breath / Drowning / Fast Swimming

**Classification:** UPGRADE — NEW WATER SURVIVAL RESOURCE.

**Phase Ownership:** Vitals/Stats + Swimming + Status Effects + HUD + Exertion.

Detailed companion:

`Docs/Swimming_Water_Breath_Drowning_Survival_System.md`

## Approved Tutorial Intent

- Breath Current/Max resource;
- drain while submerged;
- drowning after Breath reaches zero;
- contextual Breath HUD bar;
- surface recovery;
- fast swimming.

## Metaworld Upgrades

- Breath drains only when airway/head state is authoritatively submerged;
- bounded clamp `0 <= Breath <= EffectiveMaxBreath`;
- zero Breath activates Drowning consequence/status that applies authoritative Health damage;
- Breath recovery begins only when the character can actually breathe;
- Health does not automatically heal when Breath recovers;
- Breath HUD is event-driven and contextual/accessibility-configurable;
- Fast Swim is an exertion state using Stamina + Encumbrance rather than a free speed change.

### Episode 121 Principle

> Water depth controls Breath; Breath controls drowning risk; the HUD only reports that survival state.

---

# Episode 122 — Drowning / Ghost Swimming Transition Fixes

**Classification:** LOCKED + UPGRADE — ENVIRONMENT STATE RECONCILIATION.

**Phase Ownership:** Swimming + Ladder Traversal + Movement + Breath/Vitals.

Detailed companions:

- `Docs/Swimming_Water_Breath_Drowning_Survival_System.md`
- `Docs/Ladder_Climb_Down_Camera_Regrab_Finalization_System.md`

## Approved Tutorial Intent

- climbing from water must stop invalid Breath drain after the airway clears the surface;
- leaving water must disable swim/water movement state;
- overlap-order edge cases need explicit cleanup/reconciliation.

## Metaworld Upgrade

Do not fix these bugs by scattering more manual `WaterVolume = false` / `StopHoldingBreath` calls into every traversal Blueprint.

Use a single environment/water-contact resolver:

`Actual current water/body/airway contact`
-> derive Wading/Swimming/Underwater state
-> derive Breath drain/recovery eligibility
-> traversal transitions request/reconcile the environment state
-> stale overlap booleans are overwritten by current truth.

This reconciliation runs after ladder/ledge exits, teleports, respawns and unusual collision-transition events.

### Episode 122 Principle

> The cure for ghost swimming and dry-land drowning is one authoritative environment state, not another special-case Boolean reset.

---

# Part 14 Consolidated Additions

New companions introduced in this Part:

- `Docs/Ladder_Climb_Down_Camera_Regrab_Finalization_System.md`
- `Docs/Resource_Gathering_Harvesting_Tools_Depletion_Regeneration_System.md`
- `Docs/Resource_Destruction_Chaos_Fracture_Presentation_System.md`
- `Docs/Ledge_Mantle_Climb_Traversal_System.md`
- `Docs/Swimming_Water_Breath_Drowning_Survival_System.md`

Core integration chain:

`Persistent ResourceNode`
-> `Authorized Gathering Work`
-> `Real Tool / Profession`
-> `Persistent Material Output`
-> `Reserve Depletion`
-> `Optional Chaos Presentation`
-> `Legitimate Regeneration or Permanent Depletion`

and

`Water Contact`
-> `Wade / Surface Swim / Underwater Swim`
-> `Airway Submersion`
-> `Breath`
-> `Drowning Consequence`
-> `Ladder/Ledge/Water Exit`
-> `Environment State Reconciliation`.

## Part 14 Core Rule

> Metaworld traversal and resource systems must stay connected to persistent world truth. Ore cannot respawn because debris vanished, and a character cannot keep swimming/drowning because one overlap Boolean failed to clear.