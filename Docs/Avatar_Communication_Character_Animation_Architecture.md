# Metaworld — Avatar Customization, Communication & UE5.8 Character Animation Architecture

## Canonical Character Rule

Metaworld uses a single master third-person character foundation as the canonical parent for player characters, allies, enemies, civilians, companions, guards, workers, and other humanoid character types where practical.

The master character is the shared shell, not a monolithic dump of every gameplay implementation.

Core rule:

> Every humanoid child character inherits the same master character contract, while reusable systems live in components, interfaces, data assets, and modular animation layers attached to that master.

This preserves one authoritative parent while keeping the project maintainable.

---

# 1. Master Character Hierarchy

Recommended hierarchy:

`BP_MW_Character_Master`

Children can include:

- `BP_MW_PlayerCharacter`
- `BP_MW_Civilian`
- `BP_MW_Ally`
- `BP_MW_Enemy`
- `BP_MW_Companion`
- `BP_MW_Guard`
- `BP_MW_Police`
- `BP_MW_Worker`
- `BP_MW_Mage`
- Other role/faction variants

The master defines shared contracts such as:

- Character movement
- Camera hooks
- Mesh/avatar references
- Interaction entry points
- Animation interface
- Health/vitals component
- Inventory component
- Equipment component
- Needs component
- Skill/progression component
- Reputation/relationship hooks
- Voice/text communication hooks
- Object capability hooks
- Combat entry points
- Vehicle entry/exit hooks
- AI possession/controller hooks
- Networking/replication hooks

Children primarily configure data, role behavior, faction, default equipment, AI/controller, permissions, and specialized components.

---

# 2. Do Not Put Every Feature Directly in One Blueprint Graph

The master Blueprint remains the single parent, but major systems should be modular.

Recommended pattern:

Master Character
-> Components
-> Interfaces
-> Data Assets
-> Animation Blueprint
-> Linked Animation Layers
-> Child Blueprint configuration

Example:

`BP_MW_Character_Master`
- `VitalsComponent`
- `NeedsComponent`
- `InventoryComponent`
- `EquipmentComponent`
- `InteractionComponent`
- `CombatComponent`
- `VoiceTextComponent`
- `AvatarCustomizationComponent`
- `MotionWarpingComponent`
- `SkillComponent`
- `ReputationComponent`

This means a fix to inventory or combat is inherited by every child without making the parent Event Graph unmanageable.

---

# 3. Fully Customizable Characters

Players should be able to create distinct identities rather than selecting a few fixed presets.

Target customization categories include:

## Body / Identity

- Skin tone
- Body shape within supported technical bounds
- Height ranges where animation/clothing support allows
- Face shape
- Facial feature proportions
- Age appearance where supported
- Eye color
- Eye appearance
- Hair style
- Hair color
- Eyebrows
- Facial hair
- Makeup
- Tattoos
- Scars
- Freckles/skin details
- Nails and cosmetic details where supported

## Clothing / Presentation

- Shirts/tops
- Pants/skirts
- Dresses
- Jackets
- Shoes
- Hats
- Accessories
- Jewelry
- Work uniforms
- Profession clothing
- Armor/protective gear
- Creator texture variants on approved Metaworld meshes

The customization system should store parameters/data IDs rather than saving a unique duplicated character mesh for every player whenever possible.

---

# 4. Shared Skeleton and Compatibility Strategy

For Metaworld's animation volume, character customization must preserve animation compatibility.

Recommended policy:

- One canonical humanoid skeleton family where practical.
- Controlled body-proportion ranges.
- IK Rig/Retargeter profiles for supported body variants.
- Runtime or offline retargeting only where needed.
- Standard hand/foot/weapon/socket contracts.
- Clothing built against supported body/skeleton contracts.
- Facial system separated from locomotion where practical.

Extreme body shapes that break animations, reach distances, vehicle seating, weapon grips, or clothing should be constrained or use dedicated compatibility profiles.

---

# 5. Communication — Voice or Text by Player Choice

Players can communicate by microphone, text, or both.

Neither mode should be treated as second-class.

## Voice

Possible channel types:

- Proximity/local voice
- Vehicle voice
- Room/property voice
- Party/team voice
- Phone/radio voice later
- Business/security channels later

Essential controls:

- Push-to-talk option
- Voice activation option where appropriate
- Input/output device selection
- Individual mute
- Block
- Master voice volume
- Per-player volume
- Report tools
- Parental/account privilege checks where required

## Text

Possible channels:

- Local/proximity text
- Direct message
- Party/team
- Business/faction
- Property/room
- System/news channels

Text should support players who cannot or do not want to use a microphone.

Voice/text permissions and moderation must remain separate from in-world police/law systems.

---

# 6. Animation Architecture Overview

Metaworld needs a large animation library because characters can:

- Walk/run/sprint
- Crouch/prone
- Jump/fall/land
- Climb/mantle/vault
- Swim
- Fight unarmed
- Use improvised weapons
- Use firearms
- Use tools
- Build
- Repair
- Cook
- Farm
- Dig
- Harvest
- Drive
- Enter/exit vehicles
- Sit in many seat types
- Sleep
- Eat/drink
- Dance
- Party
- Talk/gesture
- Perform jobs
- Carry/drag people
- Carry objects of different sizes
- Use phones/radios
- Cast magic
- React to injury/weather/fear
- Perform social/emote animations
- Use Smart Objects and contextual interactions

No single animation technique should handle all of this.

Metaworld should use a layered animation stack.

---

# 7. Locomotion Foundation — Motion Matching / Pose Search

Recommended primary locomotion direction for the high-fidelity player and important nearby NPCs:

- Motion Matching
- Pose Search databases
- Trajectory/query-driven locomotion
- Motion-matched starts/stops/turns where coverage supports it

Motion Matching should handle core movement responsiveness rather than manually building hundreds of state transitions.

Animation databases should be organized by locomotion context such as:

- Unarmed relaxed
- Alert
- Injured
- Carrying light object
- Carrying heavy object
- Rifle/long gun
- Handgun
- Melee
- Crouched
- Special professions where needed

Do not create one gigantic database containing every possible animation in the game.

---

# 8. Linked Animation Layers — Modular Animation by Gameplay Domain

Use a primary Animation Blueprint plus Animation Layer Interfaces / Linked Anim Layers to separate complex gameplay animation domains.

Suggested layer families:

- Locomotion layer
- Unarmed combat layer
- Firearm layer
- Melee/tool layer
- Carry layer
- Interaction layer
- Vehicle layer
- Social/emote layer
- Profession/work layer
- Magic layer
- Injury/status layer
- Facial/upper-body communication hooks where appropriate

Example:

`ABP_MW_Master`
-> `ALI_MW_Locomotion`
-> `ALI_MW_Combat`
-> `ALI_MW_Interaction`
-> `ALI_MW_Vehicle`
-> `ALI_MW_Social`
-> `ALI_MW_Profession`
-> `ALI_MW_Magic`

This keeps animation extensible as Metaworld adds years of content.

---

# 9. Montages for Discrete Gameplay Actions

Animation Montages should drive discrete actions that need controlled playback, sections, notifies, slots, and multiplayer-aware root motion.

Good montage use cases:

- Reload
- Melee attacks
- Weapon equip/unequip
- Eating/drinking
- Using tools
- Healing
- Repair animation
- Crafting actions
- Arrest/handcuff actions
- Door interactions
- Enter/exit contextual actions
- Emotes
- Magic casts
- Job actions

Use montage slots so upper-body actions can play while lower-body locomotion continues where appropriate.

Child Montages can provide weapon/tool/profession variants while preserving the same gameplay timing contract.

---

# 10. Motion Warping for Contextual Interactions

Motion Warping should be used for actions where the animation must align with a world target.

Examples:

- Mantling a wall
- Vaulting
- Sitting in a chair
- Entering a vehicle
- Exiting a vehicle
- Opening certain doors
- Taking cover
- Performing an arrest
- Using a workstation
- Lifting/carrying contextual objects
- Finishing a melee interaction
- Climbing into a bed

The gameplay system provides the valid target; the animation warps root motion to align the character with it.

Do not use Motion Warping as a substitute for normal locomotion.

---

# 11. IK Rig and IK Retargeter

Use IK Rig / IK Retargeter to support:

- Different player body proportions
- Different compatible humanoid meshes
- Reusing common animation libraries
- Hand/foot contact preservation
- Runtime retargeting where justified
- Offline animation retargeting for production assets

Prefer offline retargeting for heavily reused production animation when it gives better performance/control; use runtime retargeting selectively when dynamic character variation requires it.

---

# 12. Full Body IK and Procedural Contact

Full Body IK / procedural IK should solve contact problems that canned animation alone cannot.

Examples:

- Feet aligning to uneven ground
- Hands reaching steering wheels
- Hands aligning to doors
- Weapon grips
- Carrying differently sized objects
- Reaching shelves/workstations
- Sitting alignment
- Injury poses
- Contextual leaning
- Two-character interactions where small positional differences exist

IK should refine authored animation, not replace high-quality animation data.

---

# 13. Control Rig

Use Control Rig for:

- Creating/adjusting rigs in Unreal
- Animation fixes
- Procedural rig logic
- Sequencer cinematics
- In-engine animation authoring
- Retarget cleanup
- Hand/foot correction
- Interaction prototyping

Control Rig is especially useful when Metaworld needs many small interaction fixes without round-tripping every change through an external DCC.

---

# 14. Chooser / Dynamic Asset Selection

Dynamic asset selection can choose animations based on context such as:

- Equipped weapon/tool
- Injury state
- Carry type
- Character body/profile
- Profession
- Surface/environment
- Hit location
- Stance
- Social state

Because current UE5.8 dynamic asset selection/Chooser documentation marks this workflow Experimental, Metaworld should wrap it behind its own animation-selection interface/data layer so the project can replace the implementation if Epic changes it.

---

# 15. Sync Groups, Markers and Notifies

Use Sync Groups / Sync Markers for cyclic animation timing such as walk/run blending and other synchronized loops.

Use Animation Notifies for frame/phase-aligned gameplay and audiovisual events such as:

- Footsteps
- Hand contact
- Melee hit windows
- Weapon magazine events
- Tool impact
- Sound/VFX
- Interaction release/grab moments

Gameplay authority must still validate important actions; a client-side notify alone should never create authoritative damage, money, inventory, or ownership changes.

---

# 16. Social Animation Library

Metaworld needs more social animation than a normal action game.

Categories include:

- Idle personality variants
- Conversation gestures
- Pointing
- Greeting
- Handshake
- Hug
- Sitting
- Leaning
- Drinking
- Eating
- Smoking only if later permitted by game-content policy/design
- Dancing
- Cheering
- Arguing
- Fear
- Crying
- Laughing
- Phone use
- Watching TV/movie
- Bartending
- Serving food
- Shopping
- Cashier interactions
- Police/security communication
- Religious/ceremonial actions
- Performance/music actions

These should be data-driven and selected contextually rather than hardwired into individual character Blueprints.

---

# 17. Profession Animation Packs

Each profession can add a modular animation set without changing the master character contract.

Examples:

## Builder
- Hammering
- Measuring
- Carrying materials
- Power-tool use
- Ladder/workstation interactions

## Mechanic
- Hood/engine interactions
- Wheel change
- Tool use
- Under-vehicle work

## Medic
- Examination
- Bandaging
- CPR/medical procedures where appropriate
- Patient carry/drag

## Bartender
- Pouring
- Mixing
- Serving
- Cleaning

## Gunsmith
- Bench work
- Inspection
- Assembly/disassembly animations
- Testing interactions

## Farmer
- Planting
- Watering
- Harvesting
- Tool use

Profession gameplay determines permission/capability; animation only presents the authorized action.

---

# 18. Combat Animation Packs

Combat should be modular by capability/equipment rather than one fixed class.

Libraries can include:

- Unarmed
- Knife
- Bat/pipe/blunt
- Improvised object
- Handgun
- Rifle
- Shotgun
- Heavy weapon where later supported
- Shield/blocking object
- Magic

Each can have:

- Locomotion overlay/profile
- Equip/unequip
- Aim/ready
- Attack
- Reload/use
- Hit reactions
- Block/dodge
- Finish/recovery

Object capabilities determine which animation profile is eligible.

---

# 19. Vehicle Animation System

Vehicles require dedicated contextual animation support:

- Approach door
- Open door
- Enter seat
- Close door
- Driver pose
- Passenger poses
- Steering
- Gear/control interactions
- Look/gesture while seated
- Exit
- Emergency exit
- Motorcycle mounting
- Truck/van height differences

Seat definitions should expose transforms/IK targets to the shared character animation system.

---

# 20. Two-Character and Multi-Character Interactions

Metaworld needs synchronized interactions such as:

- Handshake
- Hug
- Arrest/handcuff
- Medical treatment
- Carry injured person
- Drag person
- Grappling
- Some combat interactions
- Dance pair interactions
- Ceremonies

These require authority, synchronization, target alignment, cancellation rules, and interruption handling.

They should be built as interaction assets/contracts rather than bespoke Blueprint scripts for every pair.

---

# 21. Facial Animation and Voice

Voice communication and NPC dialogue should eventually connect to facial animation where technically practical.

Architecture should allow:

Voice / dialogue data
-> Facial animation/lip-sync layer
-> Head/eye look-at layer
-> Gesture/social layer
-> Body locomotion layer

The facial system should not block basic voice chat if high-fidelity lip sync is unavailable on lower hardware tiers.

---

# 22. Animation Scalability for a Large Living World

Metaworld can have many NPCs, so animation quality must scale by significance/distance.

Suggested tiers:

## Hero / Player
- Full locomotion system
- Full IK
- High-frequency animation
- Facial detail

## Nearby Important NPC
- Full or near-full locomotion
- Selective IK
- Reduced facial cost where needed

## Crowd NPC
- Simpler animation layer
- Reduced update frequency
- Shared animation where appropriate

## Distant Population
- No full skeletal evaluation unless visible/relevant
- Population simulation only

Use Animation Budget Allocator for bounded animation CPU cost and Animation Sharing where large groups can share evaluated poses.

---

# 23. Animation Data Organization

Recommended content structure:

`Content/Characters/Animation/`

- `Core/`
- `Locomotion/`
- `Combat/Unarmed/`
- `Combat/Firearms/`
- `Combat/Melee/`
- `Interactions/`
- `Vehicles/`
- `Social/`
- `Professions/Builder/`
- `Professions/Mechanic/`
- `Professions/Medic/`
- `Professions/Bartender/`
- `Professions/Gunsmith/`
- `Magic/`
- `Injury/`
- `NPC/`
- `Montages/`
- `MotionMatching/`
- `IK/`
- `ControlRig/`

Naming conventions and gameplay tags should identify action, stance, equipment, body profile, and variant.

---

# 24. Recommended Animation Development Order

1. Lock canonical skeleton/socket conventions.
2. Build `BP_MW_Character_Master` shell and components.
3. Build primary `ABP_MW_Master`.
4. Establish Motion Matching locomotion baseline.
5. Establish IK Rig/Retargeter and supported body profiles.
6. Add foot IK / procedural contact.
7. Add Linked Anim Layer architecture.
8. Add montage slot conventions.
9. Add interaction + Motion Warping framework.
10. Add unarmed combat pack.
11. Add firearm/tool/melee animation profiles.
12. Add vehicle seat/entry/exit system.
13. Add social animation library.
14. Add profession animation packs.
15. Add two-character interaction framework.
16. Add facial/voice integration.
17. Add Animation Budget Allocator and crowd optimization.
18. Expand databases continuously as Metaworld adds content.

---

# 25. Epic Game Animation Sample as a Reference Baseline

Use Epic's Game Animation Sample as a reference project for modern high-fidelity Motion Matching locomotion, traversal, animation databases, and extensible character animation workflows.

Do not blindly transplant the entire sample into Metaworld.

Audit and extract patterns that fit the master-character/component/layer architecture.

---

# 26. Core Principle

Metaworld has one authoritative humanoid character family.

Every player, ally, enemy, worker, civilian, police officer, companion, or other compatible humanoid can inherit the same master character foundation.

But inheritance is not the same as monolithic implementation.

The master owns the contract.
Components own gameplay systems.
Linked animation layers own animation domains.
Data assets own configuration.
Child Blueprints define role and variation.

This gives Metaworld one source of truth without creating one impossible-to-maintain Blueprint.
