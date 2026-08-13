# Metaworld — Resource Gathering, Harvesting, Tools, Depletion & Regeneration System

**Status:** Canonical / Approved Modern RPG Playlist Upgrade

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first / server-authoritative / persistent / economy-integrated / event-driven

## Canonical Principle

Metaworld gathering converts legitimate world-resource state into persistent ItemInstances through tools, work, skills and authoritative transactions. Resource recovery follows the nature of the resource; it is not a universal respawn timer.

> Mining, logging and gathering are part of the living material economy. A visual resource Actor is presentation of persistent resource state, not an infinite item generator.

Related canon:

- `Docs/Persistent_Item_Interaction_Inventory_Architecture.md`
- `Docs/Crafting_Recipes_Materials_Production_System.md`
- `Docs/Crafting_Profession_Skill_Progression_System.md`
- `Docs/Interaction_Hold_Progress_Modal_Input_State_System.md`
- `Docs/Animation_Authoring_Control_Rig_Root_Motion_Workflow.md`
- `Docs/Performance_Smoothness_FrameTime_Architecture.md`

---

# 1. Resource Node Identity

Suggested stable identity:

`ResourceNodeID`

Possible node definition/state:

- ResourceNodeID
- ResourceProfileID
- resource category/tags
- world location / owning region/property
- remaining reserve / harvestable quantity
- quality/grade distribution
- regeneration policy
- required tool/capability
- required skill/profession
- work/time requirement
- legal/ownership restrictions
- depletion state
- last harvest timestamp
- next eligible regeneration time where applicable
- visual state/profile
- revision.

Do not make the visible rock/tree mesh the only source of truth.

---

# 2. Resource Categories

Examples:

- `Resource.Mining.IronOre`
- `Resource.Mining.CopperOre`
- `Resource.Logging.Tree.Hardwood`
- `Resource.Gather.Plant.Herb`
- `Resource.Gather.Berry`
- `Resource.Salvage.Metal`

Interaction verbs derive from capability/profile data:

- Mine
- Cut
- Chop
- Gather
- Harvest
- Dig
- Salvage.

Use stable tags/data rather than a closed enum for every future resource type.

---

# 3. Tools Are Real ItemInstances

Pickaxes, axes, saws, sickles and other gathering tools use the normal ItemDefinition/ItemInstance + Equipment architecture.

A gathering tool may contribute:

- ToolCapability tags;
- efficiency;
- quality;
- durability/condition;
- handling/work speed;
- profession requirements;
- upgrade/affix state where permitted.

The tutorial's dynamically spawned pickaxe presentation is acceptable only as a visual representation of the currently authorized tool/action. Do not create a free temporary pickaxe if the character does not actually possess or have access to one when the action requires it.

---

# 4. Interaction Flow

Suggested flow:

`Target Resource Node`
-> common `BPC_MW_Interaction`
-> request Mine/Cut/Gather
-> server validates node, tool, skill, access and character state
-> create authoritative gathering interaction/job
-> align character to target if needed
-> play work animation / hold progress
-> commit resource extraction at approved work point/completion
-> create/transfer output ItemInstances
-> reduce persistent node reserve
-> update node visual state
-> notify/progression events.

The radial progress bar is local presentation of the work state. It never creates the reward by itself.

---

# 5. Output Quantity / Quality

Randomized yield is approved only when rolled authoritatively inside the resource profile's legal range.

Yield may depend on:

- remaining reserve;
- node grade/quality;
- tool capability/quality;
- profession/skill;
- character condition;
- deliberate randomness;
- extraction method;
- world/event modifiers.

The server creates the exact persistent outputs once.

Example:

`Iron Deposit #R128`
-> successful mining work
-> server resolves `3 x Iron Ore, Grade B`
-> creates/transfers output
-> reserve decreases by 3.

Opening UI or replaying an animation never rerolls the same committed extraction.

---

# 6. Renewable vs Finite Resources

There is no universal `RespawnAfterSeconds` rule.

## Renewable biological resources

Plants, berries and similar resources may regenerate through ecology/growth rules.

## Trees

Logging can remove a mature tree/resource state. Regrowth may require meaningful world time, seed/sapling/ecology state and environmental conditions.

## Ore / mineral deposits

Ore deposits are finite/depletable by default unless an explicit geological/world rule creates legitimate new accessible reserves.

A mined-out iron node must not silently refill every few minutes merely because the tutorial uses a timer.

## Salvage / manufactured resources

Salvage exists only while the physical source exists or new manufactured/wrecked material enters the world.

---

# 7. Regeneration State

When regeneration is legitimate, use persistent timestamps/state rather than leaving every depleted Actor running a timer forever.

Possible states:

- Available
- InUse/Reserved
- PartiallyDepleted
- Depleted
- Recovering/Growing
- ReadyToRegenerate
- Regenerated
- Destroyed/PermanentlyExhausted.

An unloaded resource node can recover from timestamps/data without an active world Actor.

---

# 8. Ownership / Crime / Environment

Resource gathering can respect:

- land/property ownership;
- mining/logging rights;
- public-resource rules;
- business/faction claims;
- permits/licenses;
- protected areas;
- theft/trespass;
- environmental regulations where implemented;
- war/occupation/resource-control rules.

A visible tree or ore vein is not automatically free for everyone to harvest.

Unauthorized extraction can create evidence/crime/business consequences.

---

# 9. Animation / Audio / VFX

Approved techniques:

- Control Rig/Sequencer-authored mining/logging animations;
- montages and Montage Sections for repeated work cycles;
- animation notifies for synchronized impact sound/VFX;
- Motion Warping/IK for tool-to-target alignment where useful;
- contextual tool presentation;
- resource-specific audio/VFX.

Animation notifies can signal a presentation/work phase, but the server validates any gameplay extraction committed at that phase.

---

# 10. Profession Progression

Successful meaningful work may grant relevant progression such as:

- Mining;
- Logging;
- Foraging/Gathering;
- Salvaging;
- associated profession specializations.

Reward comes from the resource/work profile and authoritative result, not simply the number of montage loops.

Anti-spam rules can reduce or deny progression for meaningless repeated actions.

---

# 11. Multiplayer / Concurrency

Two players cannot extract the same final unit of a depleted resource.

Server reserves/serializes extraction against the persistent ResourceNodeID/reserve.

If only two ore units remain and two players each request three, the authoritative system resolves legitimate outcomes without duplication.

---

# 12. Performance

- resource Actors do not Tick just because they exist;
- hold/work updates exist only while interacting;
- depleted/unloaded nodes persist as compact data;
- regeneration uses timestamps/event scheduling;
- no global scan of all nodes every frame;
- animation/VFX fidelity scales by significance;
- visual fractured debris is separate from persistent resource reserve.

---

# 13. Controller Compatibility

Mine/Cut/Gather must support:

- KBM;
- Xbox-style controller;
- PlayStation-style controller;
- current-device prompt glyph;
- hold/toggle accessibility policy where appropriate;
- cancellation/interruption.

---

# 14. Acceptance Tests

1. Mining requires a valid resource node and required tool/capability.
2. Successful extraction creates output exactly once and reduces node reserve exactly once.
3. Two players cannot duplicate the final reserve.
4. Random yield is server-generated and persists after commit.
5. Dropping/reopening UI does not reroll yield.
6. Pickaxe presentation cannot grant a non-owned tool capability.
7. Biological resource can regenerate according to its profile.
8. Finite ore deposit does not refill through a universal short timer.
9. Save/restart preserves remaining reserve and recovery timestamp.
10. Unauthorized harvesting can be denied or recorded according to property/legal rules.
11. Montage Notify aligns sound/VFX without becoming sole gameplay authority.
12. KBM/Xbox-style/PlayStation-style gathering works.
13. Distant/depleted resource nodes incur no permanent Tick cost.

## Core Rule

> Metaworld resources belong to the persistent world economy. Gathering is authoritative work against a real reserve using real tools; renewable resources recover through ecology/time, finite resources can actually run out, and no visual respawn trick is allowed to create infinite matter.