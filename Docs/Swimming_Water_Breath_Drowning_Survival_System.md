# Metaworld — Swimming, Water Contact, Breath & Drowning Survival System

**Status:** Canonical / Approved Modern RPG Playlist Upgrade

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first / server-authoritative movement and resources / Water-system-integrated / controller-complete / event-driven

## Canonical Principle

Swimming is a real movement/environment state driven by authoritative water contact, character depth and traversal context. Breath is a bounded survival resource that drains only while the character's airway is actually submerged and drowning is a consequence state when Breath is depleted.

> Water contact, swim movement, underwater state, Breath and drowning must derive from one coherent environment state. No stale Boolean may leave the player ghost-swimming or drowning on dry land.

Related canon:

- `Docs/Movement_Sprint_Stamina_Regeneration_Exertion_System.md`
- `Docs/Player_HUD_Vitals_Resources_System.md`
- `Docs/Stats_Attributes_Item_Modifiers_Encumbrance_System.md`
- `Docs/Ladder_Climbing_Traversal_System.md`
- `Docs/Ledge_Mantle_Climb_Traversal_System.md`
- `Docs/Status_Effects_Conditions_Buffs_Debuffs_System.md`
- `Docs/Avatar_Communication_Character_Animation_Architecture.md`

---

# 1. Water Contact State

Use one authoritative/local-predicted environment contact model rather than unrelated booleans scattered across Water Body, Player and HUD Blueprints.

Conceptual state can include:

- ActiveWaterBodyID / water context;
- water surface elevation at character sample point;
- foot/pelvis/chest/head or airway depth samples as required;
- in-water volume/contact;
- wading depth;
- swim-eligible depth;
- airway submerged;
- underwater state;
- surface-swimming state;
- transition state;
- water flow/current data where relevant;
- revision/timestamp.

The Character Movement/Traversal systems consume this state.

---

# 2. Movement States

Suggested semantic states:

- OnLand
- Wading
- EnteringWater
- Swimming.Surface
- Swimming.Underwater
- ExitingWater
- Falling/Jumping over water as appropriate.

Character Movement's Swimming mode can be used where appropriate, but the semantic Metaworld state remains explicit and can distinguish surface versus underwater behavior.

---

# 3. Swim Entry

Entering a Water Body/volume alone is not sufficient to force full swimming.

Eligibility can consider:

- actual water depth at the character;
- pelvis/chest depth;
- bottom/ground contact;
- character height/body profile;
- current traversal state;
- collision/clearance;
- character capability/status.

This avoids swimming because the capsule barely touches shallow water.

Body-relative sample points are preferred over one hardcoded world offset so different character proportions remain supported.

---

# 4. Surface / Underwater Detection

Water Bodies can provide water-surface/depth/flow information for gameplay queries.

Metaworld can sample the current relevant water context while the local/authoritative character is actually near/in water.

Do not globally query every Water Body or every NPC every frame.

Useful state changes:

- head/airway crosses below surface -> start holding Breath;
- airway rises above surface -> stop drain / start recovery policy;
- character reaches surface while underwater -> clamp/transition to surface-swim behavior;
- character fully leaves water -> exit swimming and clear water contact.

A head socket can be a prototype sampling point, but the authoritative model should use a stable airway/head profile compatible with character customization.

---

# 5. Swimming Movement

While swimming:

- movement input is resolved in water-relative/character camera directions according to profile;
- surface swim constrains inappropriate upward motion beyond the water surface;
- underwater swim supports controlled vertical movement;
- acceleration/deceleration/buoyancy/speed come from the movement profile;
- normal Foot IK is disabled or bypassed while not grounded;
- encumbrance/equipment/injury/status can modify swim ability.

The player cannot fly above the surface simply because control-rotation forward vectors contain an upward component.

---

# 6. Fast Swimming / Exertion

Fast swimming is the aquatic counterpart of Sprint, not a separate infinite speed boost.

`IA_MW_Sprint / contextual swim exertion`
-> validate Swimming state
-> validate Stamina / encumbrance / condition
-> enter FastSwim exertion
-> increase swim speed according to profile
-> drain Stamina
-> stop/revert when input ends or eligibility fails.

Releasing Fast Swim recomputes normal effective swimming speed rather than restoring a hardcoded constant.

---

# 7. Breath Resource

Breath is a bounded resource owned by the authoritative Stats/Vitals survival state.

Possible resource definition:

- ResourceStatID = Breath;
- CurrentBreath;
- EffectiveMaxBreath;
- drain rate/cadence;
- recovery rate/cadence;
- recovery delay if desired;
- blocker/state tags;
- modifiers from skills, conditions, equipment or supernatural capabilities.

Breath begins draining only when the airway/head state is legitimately submerged according to the environment resolver.

`0 <= Breath <= EffectiveMaxBreath`.

---

# 8. Drowning

When Breath reaches zero while airway remains submerged:

- enter/activate `Condition.Debuff.Drowning` or equivalent survival consequence state;
- apply authoritative Health damage at a bounded cadence/profile;
- continue until airway returns to breathable air, death occurs, or another valid intervention changes state.

Drowning damage is not calculated by the HUD.

Rising above water stops new drowning pulses according to policy and allows Breath recovery; Health does not necessarily auto-heal merely because Breath returns.

---

# 9. Breath Recovery

Breath recovery begins only when the character can actually breathe.

Examples:

- airway above water surface;
- not in a suffocating/smoke/toxic environment if those systems later reuse Breath/oxygen mechanics;
- no status effect explicitly blocking recovery.

The tutorial's rule "regenerate at surface, not underwater" is locked.

Recovery uses explicit resource policy/timers/timestamps rather than a permanent generic Tick.

---

# 10. HUD

Add a contextual Breath module to `W_MW_PlayerHUD`.

Possible behavior:

- hidden while Breath is full and the player is safely breathing;
- appears when airway submerges / Breath begins draining;
- remains visible through critical/empty/drowning state;
- recovers/fades after returning to safety;
- accessibility option can keep it always visible.

The HUD reads authoritative Breath changes through events and does not own the drain/recovery logic.

---

# 11. Animation

Swimming animation integrates into `ABP_MW_Master` / appropriate linked layer.

Possible states:

- tread/idle surface;
- surface forward swim;
- underwater idle;
- underwater directional swim;
- fast swim;
- enter/exit water;
- injured/exhausted variants later.

A 1D Blend Space is an acceptable starting point for speed blending, but full directional/vertical swimming may require richer blend spaces/layers as quality increases.

Foot IK/ground-contact systems must not fight swimming poses.

---

# 12. Water Entry / Exit With Traversal

Swimming must hand off cleanly to ladders, ledges, boats, shore exits and other traversal.

Example ladder exit:

`Swimming`
-> request Ladder entry
-> traversal owns mount/alignment
-> environment resolver continues checking real airway/water contact during transition
-> character rises out of water
-> airway above surface
-> Breath drain stops / recovery becomes eligible
-> ladder exit restores Walking when on platform.

Do not rely on one WaterVolume overlap Boolean that can remain stuck after traversal teleports/warps the capsule.

---

# 13. Ghost Swimming Prevention

On leaving all valid water contact:

- environment resolver clears ActiveWaterBodyID/contact;
- semantic swim state exits;
- Character Movement returns to the correct non-water mode;
- buoyancy/water-specific movement modifiers are removed;
- Foot IK/ground locomotion can resume when grounded;
- Breath state is recalculated from actual airway exposure.

The system must reconcile state after teleports, ladder exits, respawns and unusual overlap-order events.

---

# 14. Currents / Weather / Equipment Future Integration

The architecture can later incorporate:

- river/current flow;
- waves;
- storms;
- temperature/hypothermia;
- clothing/armor drag;
- flotation devices;
- diving gear;
- underwater tools/weapons;
- supernatural breathing/swimming abilities;
- boats/vehicle transitions.

Heavy armor can make swimming harder or impossible according to data; no universal rule is assumed until balanced.

---

# 15. Multiplayer / Authority

Server owns gameplay-relevant swim state, Breath and drowning consequences.

Clients can predict/smooth movement and water animation through normal Character Movement/networking patterns, but cannot claim infinite Breath, ignore drowning or fly above water.

Only nearby/relevant water movement presentation needs full update fidelity.

---

# 16. Performance

- water/depth sampling is bounded to characters currently near/in relevant water contexts;
- no world-wide water scans;
- resource drain/recovery uses bounded active timers/timestamps/events;
- HUD updates on Breath/resource state changes;
- swimming animation/IK runs only while relevant;
- distant NPC water traversal can use lower simulation fidelity where appropriate.

---

# 17. Controller Compatibility

Required:

- enter/exit water naturally;
- swim forward/back/strafe;
- ascend/descend underwater;
- fast swim where allowed;
- camera control;
- traversal handoff;
- KBM/Xbox-style/PlayStation-style support;
- rebindable logical actions.

---

# 18. Acceptance Tests

1. Shallow water does not force swimming prematurely.
2. Deep water transitions to Swimming correctly.
3. Surface swim cannot fly above water from camera pitch.
4. Underwater movement supports controlled ascent/descent.
5. Foot IK disables/bypasses while swimming and restores on ground.
6. Breath drains only while airway is submerged.
7. Breath never exceeds Max and never drops below legal range.
8. Breath reaching zero underwater causes authoritative drowning damage.
9. Surfacing stops drowning and allows Breath recovery according to policy.
10. Fast swimming drains Stamina and respects Encumbrance.
11. Climbing a ladder out of water stops stale swim/drowning state once airway/contact is clear.
12. Leaving water cannot leave ghost Swimming/WaterVolume state.
13. Save/reconnect does not restore impossible stale underwater state without current environment validation.
14. HUD Breath bar is event-driven/contextual.
15. KBM/Xbox-style/PlayStation-style swimming works.

## Core Rule

> Metaworld water survival uses one coherent environment state. Water contact decides swimming; airway submersion decides Breath drain; zero Breath causes drowning; traversal and exits must reconcile that state immediately so the character can never keep swimming or drowning after leaving the water.