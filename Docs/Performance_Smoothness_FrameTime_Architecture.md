# Metaworld — Performance, Smoothness & Frame-Time Architecture

## Canonical Rule

Metaworld must be designed for smooth, responsive gameplay from the beginning. Performance is a core gameplay requirement, not a final cleanup phase.

Core priority:

> Stable frame time first. Visual quality second.

Metaworld may be visually ambitious, but no feature should be allowed to create recurring hitching, severe frame-time spikes, unnecessary network load, or persistent low-FPS behavior when a lower-cost implementation can preserve the same gameplay.

The game remains Blueprint-first. Performance engineering therefore includes disciplined Blueprint architecture, Unreal Engine 5.8 scalability systems, streaming, significance/LOD systems, Nanite where compatible, animation budgeting, selective simulation, and continuous profiling.

---

# 1. Performance Targets

Primary development target:

- 60 FPS class gameplay on recommended PC hardware where practical.
- Stable frame pacing is more important than occasional high peak FPS.
- User-selectable frame caps such as 30 / 60 / 120 / Unlimited may be offered later.
- Lower-end hardware can use reduced visual/simulation presentation tiers rather than changing core gameplay rules.

Approximate frame-time reference:

- 30 FPS = 33.3 ms/frame
- 60 FPS = 16.7 ms/frame
- 120 FPS = 8.3 ms/frame

Systems should be profiled in milliseconds, not judged only by average FPS.

---

# 2. Performance Budgets Are Required

Every large system should have a budget or significance strategy.

Examples:

- Character animation budget
- NPC AI/simulation budget
- Physics budget
- Niagara/VFX budget
- Audio/voice budget
- World streaming budget
- UI budget
- Network replication budget
- Camera/evidence budget
- Media playback budget
- Shadow/lighting budget
- Texture/memory budget

A system that exceeds budget should reduce update frequency, fidelity, distance, quantity, or detail before it is allowed to stall the frame.

---

# 3. Blueprint Performance Rules

Metaworld is Blueprint-first, but Blueprints must be written with performance discipline.

Rules:

- Avoid Event Tick on every Actor/component.
- Prefer events, timers, delegates/event dispatchers, interfaces, state changes, and scheduled updates.
- If Tick is required, disable it when the Actor/system does not need it.
- Use lower tick frequency for systems that do not need per-frame updates.
- Never scan the entire world every frame to find Actors.
- Cache references and query through subsystems/managers where appropriate.
- Avoid repeated expensive casts and repeated object discovery.
- Use Blueprint Interfaces to reduce hard dependency chains.
- Avoid building huge monolithic Blueprint graphs.
- Use components only where they provide meaningful shared behavior; do not attach dozens of continuously ticking components without need.
- Use soft references/async loading for large optional assets where appropriate.
- Pool frequently created short-lived objects where practical instead of constant spawn/destroy churn.
- Keep authoritative transaction/economy/property systems event-driven rather than frame-driven.

Example:

Bad:

`Every Frame -> Check if monthly rent is due`

Good:

`Persistent timestamp/due date -> scheduled check or login/world-service update -> process only when required`

---

# 4. World Partition + HLOD

Metaworld's large Earth-based spaces should use World Partition for distance-based streaming and HLODs for distant world representation.

Principle:

> The player should never pay full simulation/rendering cost for the entire world at once.

Nearby cells:

- Full gameplay Actors
- Interactive interiors as required
- Detailed AI
- High-quality animation
- Physics/interactions

Distant/unloaded cells:

- HLOD/proxy representation where visually required
- Lightweight persistent data/state
- No unnecessary full Actor simulation

World Partition streaming sources should follow players and other deliberately important sources only.

---

# 5. Nanite-First, But Never at the Cost of Required Features

The existing Metaworld Nanite rule remains:

- Use Nanite anywhere UE5.8 supports it and the asset benefits from it.
- Do not force Nanite when it breaks required morphs, materials, animation, or gameplay.

High-priority categories include compatible:

- Buildings
- Roads
- Terrain/landscape workflows
- Rocks
- Props
- Furniture
- Creator base meshes
- Static vehicles/vehicle parts where appropriate
- Environment assets
- Geometry Collections
- Suitable foliage
- Supported skeletal assets

Customizable morph-target-dependent player bodies remain approved non-Nanite exceptions until the engine supports the required deformation path.

---

# 6. Camera System — Evidence Without Rendering Hundreds of Cameras

Metaworld can have cameras everywhere without rendering every security feed every frame.

This is mandatory for performance.

Camera system has two layers:

## Evidence Layer

Runs cheaply and authoritatively.

Stores event/evidence data such as:

- Camera ID
- Location
- Timestamp
- Visible face state
- Mask state
- Clothing descriptors
- Visible weapon/equipment
- Vehicle/plate visibility
- Entry/exit direction
- Recorded crime/event references

This layer does NOT require a SceneCapture render every frame.

## Visual Feed Layer

Expensive live rendering is activated only when needed, such as:

- Police/store owner is actively viewing a camera
- Camera feed is being displayed on a nearby monitor
- News system deliberately reconstructs/uses a verified clip
- A specific gameplay interaction requires live viewing

Inactive cameras do not continuously render high-resolution SceneCapture targets.

Camera render targets should use appropriate resolution, update frequency, distance, visibility, and feed limits.

Core rule:

> Cameras can be everywhere. Live rendered camera feeds cannot all be active everywhere at once.

---

# 7. NPC Simulation LOD

NPC intelligence must scale by relevance.

Suggested tiers:

## Tier A — Player / Critical Nearby NPC

- Full Blueprint behavior
- Full animation profile
- Detailed perception
- Full interaction capability
- High update rate

## Tier B — Nearby Ordinary NPC

- Standard behavior
- Reduced expensive queries
- Selective perception
- Animation budget controlled

## Tier C — Distant/Background NPC

- Lightweight state simulation
- No full animation if not visible
- Simplified schedule/resource changes
- Low update frequency

## Tier D — Unloaded Population Record

- Data only
- No spawned character Actor
- Simulate only important state transitions by timestamp/event

When a player approaches, the system materializes the appropriate NPC representation from persistent state.

---

# 8. Animation Budgeting

Metaworld will contain many animated players/NPCs, so animation CPU cost must be capped.

Use Unreal Engine's Animation Budget Allocator where compatible.

Priority should favor:

1. Local player
2. Nearby combat target / interaction partner
3. Important companion / quest/social target
4. Nearby NPC
5. Crowd character
6. Distant character

Less significant characters may:

- Update animation less frequently
- Interpolate between updates
- Disable expensive IK/facial layers
- Use simplified animation profiles
- Use Animation Sharing where appropriate

Motion Matching, IK, facial animation, cloth, morph curves, and complex linked layers should all be significance-aware.

---

# 9. Morph Character Performance

Deep character morphing remains required.

Performance rules:

- Morph values should change when customization/state changes, not be recomputed unnecessarily every frame.
- Use morph curves only where needed.
- Corrective morphs should be targeted, not an uncontrolled explosion of simultaneously active curves.
- Clothing/body fitting systems should cache results where practical.
- Distant characters can reduce facial/morph update fidelity when the difference is not visible.

Player identity remains more important than forcing a rendering optimization that breaks customization.

---

# 10. AI / StateTree / Smart Object Performance

Local NPC reasoning should be event-driven and significance-aware.

Rules:

- Do not run expensive perception queries on every NPC every frame.
- Use perception intervals/significance.
- Use Smart Objects for structured interactions instead of custom scanning everywhere.
- Use StateTree/local state logic for efficient behavior where appropriate.
- Distant NPCs should not run full combat/navigation/interaction stacks.
- Pathfinding requests should be staggered and prioritized.
- Large crowd movement should use crowd/population-friendly systems rather than hundreds of unique expensive planners when possible.

Optional external/local AI-model NPC reasoning must never block the game thread.

Model responses are asynchronous high-level intent only; normal game AI continues while waiting or falls back if unavailable.

---

# 11. Persistent World Systems Must Use Time Math, Not Continuous Simulation

Metaworld runs while players are offline, but the server should not simulate every inactive appliance/object every second.

Use timestamps and state transitions.

Examples:

Utilities:

- Store last billing timestamp
- Store due date/status
- On scheduled service evaluation, calculate elapsed real time
- Apply resulting state once

Crops:

- Store planted timestamp/growth parameters
- Calculate growth stage from elapsed time when relevant

Heating/cooling:

- Use property/environment state and elapsed-time calculations for unloaded properties
- Only run high-frequency thermal simulation when a loaded gameplay situation requires it

Businesses:

- Scheduled payroll/tax/accounting events
- No frame-by-frame bookkeeping

This lets the world remain persistent without wasting CPU on invisible activity.

---

# 12. Physics and Destruction

Physics is expensive and should be activated based on gameplay significance.

Rules:

- Sleeping/static objects should not remain unnecessarily active.
- Avoid thousands of independently simulating rigid bodies in inactive spaces.
- Destruction should use controlled Geometry Collection/Chaos budgets.
- Debris can simplify/despawn/merge after appropriate persistence/evidence rules are satisfied.
- Vehicle physics runs fully for relevant/active vehicles, not every parked vehicle in the world.
- Ragdolls should have distance/time/significance limits.

Persistent state can remember damage without preserving every active physical fragment forever.

---

# 13. Weather, VFX and Environmental Simulation

Weather state can be regional and persistent while visuals are local.

Server/world state:

- Region is raining
- Wind strength
- Temperature
- Storm severity

Client presentation:

- Spawn rain/fog/particles only where the player can perceive them
- Scale Niagara density by quality level
- Do not fill unseen parts of the world with expensive particles

Lightning, fires, smoke, magic effects, zombie hordes and destruction effects must have significance/distance limits.

---

# 14. Lighting and Shadows

Metaworld should use UE5.8 lighting features aggressively but with scalability.

High/Ultra may use:

- Lumen
- MegaLights where suitable
- Higher shadow quality
- Higher reflection quality
- Higher volumetric quality

Performance/Balanced may reduce:

- Lumen quality or use appropriate fallback path
- Shadow distance/resolution
- Volumetric resolution
- Reflection quality
- Local-light complexity

Gameplay must never depend on the player selecting Ultra graphics.

---

# 15. Media and Screens

Metaworld can contain TVs, radios, billboards, drive-ins, club screens, news displays and player media.

Performance rules:

- Only decode/play video feeds when relevant/visible/authorized.
- Distant or hidden screens use static/paused/low-cost representations.
- Audio uses spatial relevancy and distance attenuation.
- Vehicle/room media stops local playback when the player leaves the session.
- Avoid many simultaneous high-resolution video decoders.
- Digital billboards can reduce refresh/update rate dramatically when content is static.

---

# 16. Voice and Text Networking

Voice should use channel/relevancy rules.

Examples:

- Proximity voice: only nearby eligible players
- Vehicle voice: occupants
- Room/property voice: eligible occupants
- Team/radio channels: explicit members

Do not send every player's voice stream to every client.

Text channels should similarly send only relevant messages.

---

# 17. Multiplayer Replication

Network smoothness matters as much as rendering smoothness.

Rules:

- Server authoritative for money, inventory, combat results, ownership, property, evidence, jobs, taxes and death.
- Replicate only data clients need.
- Use relevancy/dormancy for inactive Actors.
- Reduce update rate for distant/noncritical Actors.
- Do not multicast large data payloads unnecessarily.
- Do not replicate unchanged variables continuously.
- Use compact IDs/tags/state where practical instead of large repeated structures.
- Media streams should not be relayed through ordinary gameplay replication.

A player should not receive every NPC, vehicle, camera, property and business update in the entire world.

---

# 18. Asset Streaming and Memory

Metaworld will contain a huge content library.

Rules:

- Use World Partition/Data Layers for world content.
- Use soft references for optional large assets where appropriate.
- Async load major content rather than blocking the game thread.
- Stream textures/meshes appropriately.
- Unload unused large assets.
- Avoid every child Blueprint hard-referencing massive animation/media/item libraries.
- Linked Animation Layers and data-driven references should load only relevant content where practical.

Large profession/weapon/social animation packs should not all be forced into memory for every NPC.

---

# 19. Scalability Profiles

Metaworld should ship with meaningful quality tiers, for example:

## Performance

- Lowest expensive rendering settings
- Aggressive crowd/animation LOD
- Reduced VFX density
- Reduced shadow/volumetric quality
- Lower screen percentage/upscaling settings as appropriate

## Balanced

- Recommended default for mid-range hardware
- Good visual quality with stable frame time

## High

- Higher rendering/animation/crowd quality

## Ultra

- Best presentation for capable PCs
- Never required for gameplay correctness

## Custom

- Player controls individual settings

Unreal scalability groups should drive these profiles.

---

# 20. Dynamic Resolution / Resolution Scaling

Where supported and visually acceptable, dynamic resolution or resolution scaling can be used to protect GPU frame time.

It should be configurable and tested per platform/hardware.

Resolution reduction is preferable to persistent severe frame drops during temporary GPU-heavy scenes, but image quality floors must remain acceptable.

---

# 21. Performance Testing Is Part of Every Feature

A feature is not complete when it only works.

It is complete when it:

1. Works correctly.
2. Works in multiplayer where applicable.
3. Survives persistence/save/load.
4. Has acceptable memory/network behavior.
5. Meets its frame-time budget.
6. Has appropriate scalability/LOD.
7. Has been tested in a worst-case representative scene.

Example worst-case performance scenes should eventually include:

- Busy nightclub with many players/NPCs
- Downtown traffic + pedestrians + rain at night
- Zombie attack during a crowded event
- Police response with vehicles/cameras/news
- Large creator marketplace area
- Dense apartment/business district
- Large combat event
- Player home containing many possessions

---

# 22. Profiling Tools

Use UE5.8 profiling tools continuously.

Primary tools:

- `stat unit` / `stat unitgraph`
- `stat gpu`
- Unreal Insights
- Animation Insights
- Network Insights
- Memory Insights
- GPU profiling/RenderDoc where needed
- Streaming statistics

Do not optimize based only on guesses.

Measure the actual bottleneck:

- Game thread
- Render thread
- GPU
- Network
- Memory/streaming
- Animation
- Physics

Then fix that bottleneck.

---

# 23. Performance Regression Rule

Every major feature should be compared against a known performance baseline.

If a change causes significant recurring frame-time spikes, memory growth, network spam, or streaming hitching:

- Profile it
- Identify the cause
- Reduce cost
- Add LOD/significance/streaming
- Or redesign the implementation

Do not accept "we will optimize it later" as the default answer for a known severe regression.

---

# 24. Core Principle

Metaworld can be huge without simulating/rendering everything at maximum quality at the same time.

The world remains persistent because important state is persistent, not because every object is ticking every frame.

The target architecture is:

`Full fidelity near the player`

`Reduced fidelity at distance`

`Data-only simulation when unloaded`

`Stream only what is needed`

`Budget expensive systems`

`Profile continuously`

`Scale visuals before sacrificing responsiveness`

Final rule:

> Metaworld should feel alive, not heavy. The player should notice the world — not the engine struggling to run it.`