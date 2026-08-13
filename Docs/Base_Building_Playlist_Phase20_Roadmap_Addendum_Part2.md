# Metaworld — Base-Building Playlist Phase 20 Roadmap Addendum — Part 2

**Status:** Canonical / Approved Phase 20 Intake Log Continuation

**Continues:** `Docs/Base_Building_Playlist_Phase20_Roadmap_Addendum.md`

**Base Master Roadmap:** `Docs/Master_Development_Roadmap.md` v2.9

**Purpose:** Continue recording approved tutorial-playlist upgrades without repeatedly replacing the very large first addendum. This continuation is equally canonical Phase 20 material and will be consolidated with Part 1 into the Master Roadmap after the playlist review is complete.

## Permanent Rules Carried Forward

All permanent rules from Part 1 remain active, including:

- Blueprint-first runtime architecture.
- `BPC_MW_BuildComponent` owns build-mode flow.
- stable Buildable/Family/Variant IDs and data-driven definitions.
- server-authoritative permanent construction state.
- controller support for keyboard/mouse, Xbox-style controllers and PlayStation-style controllers.
- property, profession, permit, resource, support, collision, persistence and performance validation.
- explicit placement footprints and logical snap/slot occupancy.
- valid terrain/structural support chains instead of arbitrary floating structures.
- tutorial-specific keys, constants, channels and delay values are examples, not permanent Metaworld architecture.

---

# Playlist Intake Status — Continued

## Episode Upgrade 12 — Construction Removal, Deconstruction & Demolition

**Classification:** UPGRADE — APPROVED

Approved:

- tutorial hold-to-remove concept retained as an intentional-action safety mechanism
- radial/circular progress UI retained for hold confirmation
- hardcoded keyboard `1` key replaced by Enhanced Input action/context architecture
- hold action must have keyboard/mouse, Xbox-style controller and PlayStation-style controller paths
- radial UI is hidden/collapsed when removal is inactive and resets on release, target loss, mode exit, rejection or completion
- construction removal is **not** a universal `Destroy Actor` command
- three removal paths are separated:
  1. cancel/dismantle unfinished construction
  2. authorized deconstruction/demolition of completed structures
  3. normal world damage/destruction through combat, accidents, fire, weather, war, crime, etc.
- tutorial `IsBuildFinished` concept is upgraded into richer construction-state + removal-policy data
- unfinished construction can be cancelled/dismantled only by authorized users/contracts/roles
- completed structures are removable through an authorized demolition/deconstruction workflow rather than being permanently undeletable
- unauthorized players cannot use construction tools to delete somebody else's finished or unfinished structure
- hostile/illegal destruction must use durability/damage/crime/evidence systems instead of construction removal
- hold duration is data-driven per removal mode/object where appropriate
- holding to confirm can start a removal job; large structures do not instantly vanish after a short hold
- structural removal can require Demolition/Construction Work Units, Builder qualification, tools, machinery, workers, permits and utility safety where applicable
- server owns final removal authorization, hold/work completion, dependency handling, salvage/refund and persistent cleanup
- client cannot fake unfinished state, ownership, hold duration, salvage amount or arbitrary actor deletion
- removing an unfinished site releases its reserved snap/placement slot only after authoritative removal transaction succeeds
- refunds/salvage are server-authoritative and cannot exceed legitimately committed materials; removal must never mint resources
- unused reserved materials may be returned according to policy
- installed/consumed materials may provide partial salvage according to material/state/damage rules
- labor/time already consumed is not automatically refunded
- removal checks structural dependencies before deleting a support-bearing piece
- walls, floors, columns, piers, foundation extensions and other supports cannot silently disappear while dependent structures remain treated as valid
- possible dependency outcomes include safe removal, blocked removal, explicit cascade-removal preview or deliberate unsafe demolition path where world rules allow it
- removing support triggers event-driven structural support revalidation
- installed doors/windows/attachments must be resolved atomically when a parent wall/opening is removed
- opening/snap/support occupancy and parent-child relationships are cleaned up as part of the removal transaction
- property/build-budget state is updated after successful removal
- demolition/deconstruction can create legitimate Builder jobs and daily role duties
- NPC Builders can perform authorized dismantling/demolition under valid contracts, tools/resources and persistent job rules
- demolition can later connect to debris cleanup, salvage, repair, inspections, insurance and public-safety duties
- no permanent removal Tick; target/progress checks only run while the relevant removal action/mode is active

Detailed companion: `Docs/Construction_Deconstruction_Demolition_Removal_System.md`

---

# Current Phase 20 Construction Stack — Continued

`Build Catalog / Selection`

`-> Ghost Placement / Rotation / Orientation`

`-> Placement Footprint / Overlap / Slot-Occupancy Validation`

`-> Terrain / Foundation Support Sampling & Required Extensions`

`-> Property / Profession / Resource Validation`

`-> Foundation / Floor / Wall Snap Architecture`

`-> Wall Families & Structural Openings`

`-> Door / Window Installation`

`-> Supported Multi-Story Construction`

`-> Persistent Construction Site / Work Stages`

`-> Completed Structure`

`-> Interactive Door / Window Runtime`

`-> Cancel / Dismantle / Authorized Demolition`

`-> Damage / Repair / Renovation / Utilities / Contracts later`

---

# Removal Principle

> Metaworld never treats removal as a universal delete key. Unfinished construction can be cancelled or dismantled under real permissions and salvage rules; completed structures use authorized deconstruction/demolition; hostile or accidental destruction uses the normal world damage/crime system. Structural dependencies, persistence, resources and multiplayer authority are always respected.

---

# Playlist Continuation Rule

Future playlist episodes can be appended to this Part 2 continuation until consolidation. Part 1 and Part 2 together are the canonical Phase 20 playlist intake log.
