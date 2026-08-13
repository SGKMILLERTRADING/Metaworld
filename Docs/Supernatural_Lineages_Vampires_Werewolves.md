# Metaworld — Supernatural Lineages: Vampires, Werewolves & Future Types

## Canonical Rule

Metaworld must support players who want to live as ordinary humans and players who want supernatural identities such as vampires or werewolves.

These identities are real gameplay lineages, not simple skins.

Core rule:

> Supernatural identity changes how a character lives in Metaworld, but it does not exempt that character from the world.

A vampire can still own property, run a business, work a profession, use vehicles, have friends, marry, pay taxes, go to court, be caught on camera, be robbed, die, inherit property, and appear on Metaworld News.

A werewolf can do the same.

Humans remain a complete and competitive life path. Supernatural lineages gain strengths and distinctive abilities, but they also carry needs, risks, weaknesses, legal/social consequences, and lifestyle differences.

---

# 1. Blueprint-First Architecture

The supernatural system remains part of the existing Blueprint-first architecture.

Recommended shared component:

`BPC_MW_Lineage`

Attached to:

`BP_MW_Character_Master`

Possible lineage tags:

- `Lineage.Human`
- `Lineage.Vampire`
- `Lineage.Werewolf`
- Future supernatural lineages only when deliberately designed

All player characters, allies, enemies, and suitable NPCs continue to inherit from the same master third-person Blueprint family.

Lineage changes data, abilities, needs, animations, morphs, senses, weaknesses, and rules through modular Blueprint systems rather than requiring a separate unrelated character architecture.

---

# 2. Character Creator Integration

Players should be able to combine lineage with the existing deep morph customization system.

A vampire can still be:

- Slim
- Heavy
- Muscular
- Elderly-looking
- Young-looking
- Tall/shorter within supported ranges
- Any supported skin tone before supernatural visual effects are applied
- Fully face-customized
- Any supported hairstyle
- Tattooed/scarred/etc.

A werewolf's normal humanoid form should retain the player's customized identity.

Transformation-specific meshes/morphs can then derive from that identity where technically practical.

Lineage should not force every vampire or every werewolf to look identical.

---

# 3. Vampire Gameplay Direction

Vampires should feel powerful and distinctive without becoming automatic best-in-game characters.

Possible strengths:

- Enhanced night vision
- Improved perception
- Faster movement or reactions in appropriate states
- Stronger close-range physical capability
- Blood-related abilities
- Supernatural healing under valid conditions
- Charm/intimidation/sensory abilities where balanced
- Long-lived visual/lore identity
- Vampire-specific skill branches

Possible needs/weaknesses:

- Blood hunger or equivalent vampire resource
- Sunlight sensitivity/severity determined by final lore/balance
- Reduced performance or danger under certain conditions
- Specialized vulnerabilities
- Social/legal risk if violent feeding is witnessed
- Need to conceal supernatural behavior in hostile communities

A vampire who feeds illegally on another character may create a crime event, camera evidence, witnesses, police investigation, reputation effects, faction consequences, and news coverage just like other serious world actions.

Blood should not simply replace every existing survival system without design. Hunger, thirst, health, stamina, mana, and vampire-specific needs should interact through configurable rules.

---

# 4. Werewolf Gameplay Direction

Werewolves should have a real transformation/gameplay identity rather than only cosmetic ears and fur.

Possible strengths:

- Transformation between humanoid and werewolf states
- Increased physical strength while transformed
- Improved tracking/scent/perception
- Strong melee capability
- Increased movement capability
- Enhanced resilience or recovery under valid conditions
- Werewolf-specific skill branches

Possible weaknesses/risks:

- Transformation control requirements
- Increased hunger/stamina costs
- Specialized vulnerabilities
- Reduced ability to use some normal tools/weapons while fully transformed
- Difficulty hiding identity if transformation is witnessed or recorded
- Social/legal consequences for uncontrolled attacks
- Environment/time/lunar influences if later adopted by lore

The exact moon/transformation rule remains a future balancing decision; it should not be hardcoded until the lore is finalized.

---

# 5. Transformation System

Transformations should be driven by Blueprint state, data, animation, morphs, materials, VFX, and mesh swaps only where necessary.

Possible Blueprint flow:

`BP_MW_Character_Master`
-> `BPC_MW_Lineage`
-> Validate transformation rules
-> Set lineage state
-> Apply attributes/abilities
-> Apply morph/material/mesh changes
-> Select animation layer/profile
-> Update collision/capabilities if required
-> Replicate authoritative state

Transformation must not create a new unrelated actor that loses inventory, identity, ownership, evidence, reputation, or networking state unless a specific technical implementation requires a controlled representation swap.

The player remains the same character identity.

---

# 6. Animation Requirements

Supernatural lineages add modular animation packs to the existing animation architecture.

Vampire examples:

- Feeding
- Bite/grab interactions
- Supernatural movement variants
- Threat/intimidation
- Ability casts
- Reactions to sunlight/weaknesses

Werewolf examples:

- Transformation
- Quadruped/low locomotion if the chosen form uses it
- Sprinting
- Claw attacks
- Bites
- Pounces
- Tracking/sniffing
- Howl/social signals
- Transformation recovery

Use Linked Animation Layers / modular animation profiles so these do not bloat `ABP_MW_Master`.

---

# 7. Morphs Remain Important

Supernatural lineages must work with Metaworld's morph-driven character identity system.

Examples:

Vampire morphs may include:

- Fangs
- Eye changes
- Facial-emaciation or feeding-state changes
- Vein/detail states
- Temporary rage/hunger facial changes

Werewolf morphs may include:

- Facial transition stages
- Jaw changes
- Hand/claw changes
- Body expansion/proportion changes where practical
- Ear/facial transformation stages

Because UE5.8 Nanite does not support Morph Target deformation, morph-dependent customizable body/face meshes remain approved non-Nanite exceptions.

Player identity and transformation quality take priority over forcing Nanite on those meshes.

---

# 8. Professions Still Matter

Being supernatural does not bypass profession rules.

A vampire does not automatically know how to manufacture guns.

A werewolf does not automatically know how to construct houses.

Examples:

- Vampire + Gunsmith = can manufacture guns if qualified
- Vampire without Gunsmith = cannot
- Werewolf + Builder = can construct approved buildings if qualified
- Werewolf without Builder = cannot

Lineage and profession are separate systems.

This allows combinations such as:

- Vampire bartender
- Vampire doctor
- Vampire police officer
- Vampire criminal
- Vampire landlord
- Werewolf mechanic
- Werewolf farmer
- Werewolf security guard
- Werewolf business owner
- Human mage
- Human gunsmith

---

# 9. Law, Cameras & Evidence

Supernatural characters obey the same evidence rules as everyone else.

A camera records what it physically sees.

If a transformed werewolf commits a crime on camera, footage can show the transformed creature.

If a vampire commits a crime while masked, the camera sees the mask and visible supernatural evidence only.

The server knows the authoritative actor identity for technical integrity, but police and news only know what legitimate evidence reveals.

Supernatural actions can create:

- Witness evidence
- Camera footage
- Injury/forensic evidence where later supported
- Reputation effects
- Police investigations
- Faction responses
- News coverage

---

# 10. Death Still Matters

Vampires and werewolves are not exempt from Metaworld permanent character death unless future lore explicitly creates a rare special mechanic.

Default rule:

- They can die permanently.
- Their character identity dies.
- Bank death/estate rules still apply.
- Physical possessions remain in the world.
- Wills/beneficiaries/inheritance still apply.
- The next character identity is not automatically the same supernatural lineage unless character-creation/progression rules allow it.

Supernatural power must not erase the stakes that make Metaworld life valuable.

---

# 11. Social Life and Community

Supernatural identity should create social possibilities, not only combat bonuses.

Possible systems later:

- Vampire houses/covens
- Werewolf packs
- Human/supernatural friendships
- Mixed families/relationships where lore allows
- Supernatural clubs/businesses
- Hidden communities
- Public supernatural communities where accepted
- Rival factions
- Religious responses
- Political debates
- Specialized doctors/healers/hunters
- Supernatural law and licensing where cities choose to regulate certain actions

Different cities may develop different reputations and laws toward supernatural residents.

---

# 12. Lineage Territories, Politics and War

Metaworld does not assume every lineage lives together peacefully.

Different communities, cities, regions, factions, packs, covens, governments, and alliances may have very different relationships.

Possible world arrangements include:

- Human-majority cities
- Vampire-controlled districts or cities
- Werewolf-controlled territories
- Mixed cities
- Neutral trade cities
- Hidden supernatural settlements
- Contested border regions
- Faction-controlled neighborhoods
- Demilitarized/neutral zones
- Refugee areas
- Occupied territory during wars

Lineage does not automatically determine political allegiance.

Examples:

- A vampire may fight against a vampire coven.
- A human may ally with a vampire faction.
- A werewolf may protect a human city.
- A mixed player organization may include humans, vampires, and werewolves.
- Two vampire houses may be at war with one another while both remain peaceful with a nearby human city.
- A human government may ally with one werewolf pack against another.

This prevents supernatural identity from becoming a simple red-team/blue-team system.

## War States

Factions, cities, governments, covens, packs, and other political organizations can enter states such as:

- Peace
- Tension
- Trade agreement
- Alliance
- Defensive pact
- Ceasefire
- Hostility
- Open war
- Occupation
- Truce

Wars can affect:

- Borders
- Travel safety
- Checkpoints
- Police/military/security presence
- Property risk
- Business access
- Trade routes
- Taxes and emergency spending
- Refugees/displaced characters
- Jobs/contracts
- News
- Prices and shortages
- Faction reputation
- Crime/enforcement
- World events

## Territory Matters

A character's experience can depend on where they are.

Example:

A vampire entering a neutral mixed city may live normally.

The same vampire entering a werewolf-controlled region during an active vampire-werewolf war may face:

- Checkpoints
- Suspicion
- Refused services
- Arrest/detention under local wartime law
- Attack from hostile factions
- Need for disguise or safe passage
- Smuggling opportunities
- Diplomatic missions
- Refugee/escape gameplay

The reverse can also happen to werewolves or humans in hostile territory.

## War Does Not Override Ordinary Metaworld Systems

Even during war:

- Property still exists.
- Businesses still need money.
- Bills can still become due.
- Banks still function where institutions remain operational.
- GrimKoin remains governed by the economy ledger.
- Cameras/evidence still work where infrastructure survives.
- News records the conflict.
- Death remains permanent.
- Wills and estates still matter.
- Professions still matter.
- Civilians may try to work, party, trade, evacuate, hide, or survive.

War becomes another condition of the living world, not a separate match/lobby.

## Dynamic Politics

Relationships should be able to change over time through world events and player/NPC actions.

Possible causes:

- Elections
- Leadership changes
- Assassinations
- Treaty violations
- Territorial disputes
- Resource shortages
- Religious conflict
- Criminal incidents
- Retaliation
- Trade agreements
- Player diplomacy
- NPC diplomacy
- Historical grievances
- Major supernatural attacks
- Shared enemies

Metaworld News and the Event Ledger should record major declarations of war, ceasefires, alliances, occupations, peace agreements, and major battles.

---

# 13. Balance Principle

Metaworld should not make one lineage objectively mandatory.

The target is:

Human
-> fewer supernatural needs/weaknesses and broad ordinary-world compatibility

Vampire
-> distinctive supernatural strengths + blood/sun/social/legal risks

Werewolf
-> transformation/physical/tracking strengths + control/vulnerability/social risks

No lineage should invalidate the others.

A successful human business owner with loyal security and strong skills can be more powerful in the world than a reckless vampire who owns nothing.

A disciplined werewolf may avoid fights because permanent death, property, bank loss, family, and business still matter.

---

# 14. Future Supernatural Types

The architecture should permit future lineages without requiring them now.

Possible future categories may include other supernatural or magical identities if they fit Metaworld lore and balance.

Every future lineage must define:

- Strengths
- Needs
- Weaknesses
- Transformation/appearance rules
- Skill branches
- Animation requirements
- Morph requirements
- Social/legal implications
- NPC behavior implications
- Death behavior
- Economy/profession compatibility
- Political/faction relationships
- Territory implications

Do not add a lineage merely as a power upgrade.

---

# 15. Core Principle

Metaworld should let players build the identity and life they actually want.

A player may want to be:

- An ordinary human bartender
- A wealthy human landlord
- A vampire nightclub owner
- A vampire police officer
- A werewolf mechanic
- A werewolf living alone in the hills
- A human mage
- A supernatural criminal
- A peaceful supernatural family member
- A vampire diplomat in a human city
- A werewolf soldier defending pack territory
- A human trader crossing a supernatural war zone

All of those lives belong in the same persistent world.

> Metaworld gives players freedom of identity, but every identity still has to live with the world — including its politics, alliances, territory, and wars.