# Metaworld — Character Morph Customization System

## Canonical Rule

Metaworld characters must support deep body and face customization. Morph targets are a first-class requirement, not an optional cosmetic extra.

Players must be able to create characters who can look meaningfully different in body type, age appearance, facial structure, and physical build while still using the same master Blueprint character family.

Core rule:

> Player identity takes priority over forcing Nanite onto the main customizable body.

If a required morph-driven body or face feature is incompatible with Nanite in Unreal Engine 5.8, that body/face mesh uses the normal Skeletal Mesh rendering path. Nanite remains the default for every other compatible asset category.

---

# 1. Target Customization Range

The Metaworld character creator should support a broad but controlled range including:

## Body Build

- Very slim
- Slim
- Average
- Athletic
- Muscular
- Heavy
- Very heavy / fat
- Broad shoulders
- Narrow shoulders
- Larger/smaller chest
- Larger/smaller waist
- Larger/smaller stomach
- Larger/smaller hips
- Larger/smaller arms
- Larger/smaller legs
- Body-fat distribution controls where practical
- Muscle-definition controls where practical

## Age Appearance

Players should be able to make characters appear:

- Young adult
- Adult
- Middle-aged
- Older
- Elderly

Age appearance should be built from multiple systems rather than one simple slider.

Possible age presentation inputs:

- Facial morphs
- Jaw/cheek changes
- Eye-area changes
- Nose/ear appearance where appropriate
- Neck/body aging morphs
- Wrinkle normal/detail maps
- Skin roughness changes
- Skin tone/detail variation
- Hair greying/whitening
- Hair thinning/balding options
- Facial-hair greying
- Posture/animation profile where appropriate

Age appearance does not automatically define gameplay age, health, skill, or weakness unless a separate gameplay system explicitly chooses to do so.

## Face

Possible morph-driven controls include:

- Head width/length
- Jaw width/shape
- Chin size/shape
- Cheek volume
- Cheekbone prominence
- Brow shape
- Eye size/spacing/shape
- Nose width/length/bridge/tip
- Mouth width/shape
- Lip fullness
- Ear size/shape where supported
- Facial fullness
- Facial asymmetry within supported bounds

## Additional Identity Options

- Skin tone
- Eye color
- Hair style
- Hair color
- Eyebrows
- Facial hair
- Makeup
- Tattoos
- Scars
- Freckles
- Skin details
- Nails/cosmetic details where supported

---

# 2. Blueprint-Driven Morph System

Morph values are controlled through Blueprints.

Recommended component:

`BPC_MW_AvatarCustomization`

Responsibilities:

- Store customization values
- Apply morph target values to the Skeletal Mesh
- Apply skin/hair/material parameters
- Apply age/detail parameters
- Drive compatible clothing morphs
- Replicate compact customization state
- Save/load customization profiles
- Validate allowed slider ranges
- Trigger corrective morphs where required

The system should use Unreal's Skeletal Mesh morph-target support and Blueprint `Set Morph Target` functionality.

Recommended data structure:

`ST_MW_AvatarMorphProfile`

Possible fields:

- BodyFat
- BodyMuscle
- ShoulderWidth
- ChestSize
- WaistSize
- BellySize
- HipSize
- ArmSize
- LegSize
- FaceAge
- FaceWidth
- JawWidth
- JawShape
- ChinSize
- CheekVolume
- EyeSize
- EyeSpacing
- NoseWidth
- NoseLength
- MouthWidth
- LipFullness
- Additional morph parameters

Do not replicate raw vertex data. Replicate/save the compact parameter values and apply them locally to the correct Skeletal Mesh.

---

# 3. One Master Character Still Applies

Morph customization does not change the character inheritance rule.

All suitable humanoid characters still derive from:

`BP_MW_Character_Master`

The master owns/attaches:

- `BPC_MW_AvatarCustomization`
- Shared skeleton/mesh contracts
- Animation interface
- Clothing/equipment sockets
- Character movement
- Other common gameplay components

Children can have different default morph profiles while using the same customization system.

Examples:

- Player creates custom body
- Civilian receives procedurally generated morph profile
- Police NPC receives another profile
- Elderly NPC receives age morph/material profile
- Heavy hostile NPC receives larger body profile

The character class does not need to change just because the body shape changes.

---

# 4. Morph Targets vs Skeleton Proportions

Morph targets are ideal for changing surface/body volume and facial shape, but not every proportion should be solved with morphs alone.

Recommended split:

## Morph Targets

Use primarily for:

- Body fat/volume
- Muscle mass/definition
- Face shape
- Facial fullness
- Wrinkles/aging geometry where needed
- Stomach/chest/hips/arms/legs volume
- Corrective deformation

## Skeleton / Rig / IK Adjustments

Use where needed for:

- Height variation
- Limb length variation
- Shoulder/hip joint placement
- Hand/foot reach
- Vehicle seating alignment
- Weapon grip alignment
- Interaction reach

Extreme height or limb-length variation should be constrained to ranges the animation/IK/clothing systems can support reliably.

---

# 5. Corrective Morphs Are Required

Combining many morphs can create bad deformation.

Examples:

- Very large belly + bent sitting pose
- Large chest + raised arms
- Heavy thighs + crouching
- Muscular shoulders + rifle aiming
- Elderly face + extreme smile

Metaworld should support corrective morph targets for problematic combinations/poses.

Correctives can be activated by:

- Body morph combinations
- Animation curves
- Pose state
- Equipment state
- Clothing state

This prevents customization freedom from destroying deformation quality.

---

# 6. Clothing Must Follow the Body

Clothing cannot assume every player has the same body.

Each customizable clothing/base garment system must support the approved body range.

Possible strategies include:

- Matching clothing morph targets driven by the same body parameters
- Parametric/resizable clothing where appropriate
- Multiple source body sizes with automatic interpolation/selection
- Cloth simulation with controlled fitting support
- Corrective clothing morphs for extreme combinations

Recommended rule:

> Every body morph that materially changes clothing fit must have an approved clothing response.

A shirt should not remain thin-body sized while the player changes to a very heavy body.

Creator texture products remain texture-only. The creator does not edit body morphs, clothing geometry, material slots, rigs, or fitting logic. Metaworld supplies the compatible clothing/base mesh and fitting system; creators only texture approved assets.

---

# 7. Animation Must Survive Customization

The animation stack must be tested against the full supported morph/body range.

Test categories include:

- Walk/run/sprint
- Crouch
- Jump/land
- Sitting
- Sleeping
- Vehicle entry/exit
- Driving
- Rifle/handgun grip
- Melee
- Carrying objects
- Builder/mechanic/medic profession animations
- Dancing/social animations
- Arrest/handcuff interactions
- Two-character interactions
- Magic casting

IK and Motion Warping should correct world contacts where appropriate.

Body morph values should not silently change collision or gameplay reach unless the relevant gameplay system explicitly accounts for it.

---

# 8. Age Is Visual + Animation, Not Just Wrinkles

A convincing older character may combine:

- Face morphs
- Neck/body morphs
- Wrinkle/detail textures
- Roughness/skin material changes
- Grey/white hair
- Thinner hair
- Different idle posture
- Optional older locomotion/personality animation profile

A player may choose to look elderly while still being a highly skilled or dangerous character.

Appearance should not automatically dictate competence.

---

# 9. Nanite Exception for Morph-Driven Main Bodies

Unreal Engine 5.8 supports Nanite broadly, including Nanite Skeletal Mesh workflows, but Nanite does not support Morph Target deformation.

Therefore:

## Main Customizable Body/Face

If the mesh requires runtime morph targets:

- Use the normal Skeletal Mesh rendering path.
- Keep morph support fully functional.
- Use LODs/animation budgeting/other optimization methods.
- Do not disable morphs just to enable Nanite.

## Other Character Assets

Evaluate Nanite separately for compatible:

- Weapons
- Rigid accessories
- Helmets
- Armor pieces
- Backpacks
- Shoes/rigid footwear parts
- Jewelry
- Equipment
- Other skeletal/static pieces that do not require unsupported morph deformation

## World Assets

Continue the existing Nanite-first rule for supported world geometry.

---

# 10. Performance Strategy

Deep morph customization must remain scalable.

Recommended optimization:

## Player / Hero Characters

- Full morph profile
- Full face/body detail
- Full animation/IK quality

## Nearby Important NPCs

- Full or near-full morph profile
- Reduced secondary detail if needed

## Crowd NPCs

- Limited morph combinations or generated preset profiles
- Lower animation update frequency
- Simplified facial system

## Distant Population

- Simplified representation
- No unnecessary high-frequency morph updates
- Population simulation where possible

Morph values normally change infrequently after character creation, so the system should avoid repeatedly setting every morph every frame when no value changed.

For supported target hardware, Unreal's GPU morph-target calculation option should be evaluated to reduce CPU morph calculation cost where beneficial.

---

# 11. Character Creator UX

Players should not need to understand technical morph names.

Present human-readable controls such as:

Body:
- Slim ↔ Heavy
- Soft ↔ Muscular
- Narrow ↔ Broad
- Small ↔ Large chest
- Small ↔ Large waist
- Small ↔ Large hips

Face:
- Narrow ↔ Wide
- Soft jaw ↔ Strong jaw
- Small ↔ Large nose
- Thin ↔ Full lips
- Young-looking ↔ Older-looking

Advanced mode can expose more detailed controls.

Presets should exist only as starting points. Players should still be able to modify them.

Possible presets:

- Slim
- Average
- Athletic
- Muscular
- Heavy
- Very Heavy
- Young Adult
- Middle-Aged
- Elderly

Presets do not replace sliders.

---

# 12. Save and Replication

The authoritative character customization record should store parameter values, not a newly duplicated mesh for every player.

Example:

`CharacterAppearanceRecord`

- Character ID
- Base body/skeleton profile ID
- Morph parameter map
- Skin/material parameter IDs
- Hair asset/color
- Facial-hair asset/color
- Eye settings
- Tattoo/scar/cosmetic IDs
- Clothing/equipment IDs
- Appearance version

On spawn:

Character record
-> `BP_MW_Character_Master`
-> `BPC_MW_AvatarCustomization`
-> Apply morph values
-> Apply materials/hair
-> Fit clothing
-> Initialize animation/IK profile

---

# 13. Python/Editor Tooling

Python and Editor Utility Blueprints can help build and validate the morph system.

Potential tools:

## Morph Audit

- Confirm required morph names exist
- Check missing morphs per body mesh
- Compare morph coverage across LODs
- Validate naming conventions
- Detect invalid duplicate names

## Clothing Compatibility Audit

- Verify clothing has matching body-fit morphs
- Test approved body presets
- Flag clipping-prone combinations
- Generate compatibility reports

## Character Preset Generator

- Build NPC population profiles from approved ranges
- Generate slim/heavy/old/young/etc. presets
- Validate parameter limits

Python remains editor/development tooling; runtime morph application remains Blueprint.

---

# 14. Initial Morph Development Order

1. Lock the canonical humanoid skeleton and base body topology.
2. Build `BPC_MW_AvatarCustomization` in Blueprint.
3. Define the authoritative morph naming standard.
4. Implement core body morphs: slim/heavy/muscle/chest/waist/belly/hips/arms/legs.
5. Implement core face-shape morphs.
6. Implement age morph/detail system.
7. Add Blueprint save/load/replication for morph parameters.
8. Test locomotion against extreme supported body shapes.
9. Add corrective morphs.
10. Build clothing fitting/matching morph pipeline.
11. Test vehicle seating and weapon/tool IK.
12. Add NPC procedural morph presets.
13. Add morph performance/scalability rules.
14. Expand customization continuously.

---

# 15. Core Principle

Metaworld should not have a world full of clones.

One player may be slim and young-looking.

Another may be heavy and elderly.

Another may be muscular and scarred.

Another may be short, broad, grey-haired, tattooed, and dressed completely differently.

They should still inherit the same master Blueprint character architecture and participate in the same animation, profession, combat, social, economy, property, crime, and life systems.

> The player chooses who their character looks like. The technology must adapt to that identity, not force every player into the same body just to simplify rendering.