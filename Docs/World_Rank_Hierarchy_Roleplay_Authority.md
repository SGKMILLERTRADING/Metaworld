# Metaworld — World Rank Hierarchy, Roleplay & Authority

**Status:** Canonical / Approved

## Canonical Rule

Metaworld uses an explicit rank hierarchy so players, NPCs, governments, departments, factions, businesses, and roleplay systems can understand who outranks whom without confusing wealth, profession, job title, political office, or platform ownership.

Core rule:

> The Owner/Creator is above all in-world ranks and is not an earnable player rank.

> King is the highest player-held world rank beneath the Owner.

> President is the next highest player-held civic rank beneath the Royal/Sovereign tier.

GrimKoin cannot directly buy any of these official ranks.

---

# 1. Metaworld Authority Tier

## Tier 0 — Owner / Creator

The Metaworld Owner/Creator is outside the ordinary player progression system.

This tier represents the creator/operator authority of Metaworld itself.

Rules:

- Not obtainable by election.
- Not purchasable with GrimKoin.
- Not inherited through ordinary in-world death/estate rules.
- Not a normal profession or civic office.
- Exists above every player/NPC government, kingdom, faction, department, business, and community rank.
- The Owner may still enter Metaworld as a character and participate in roleplay, but the Owner account/authority remains separate from ordinary in-world rank progression.

Canonical hierarchy starts:

`Owner / Creator`
-> `King / Sovereign Royal Tier`
-> `President`
-> lower civic/organizational ranks

---

# 2. Tier 1 — King / Sovereign Royal Tier

**King is the highest normal player-held world rank under the Owner.**

A King can represent the highest sovereign leader recognized by the Metaworld political/roleplay hierarchy.

King is not purchased.

A player reaches this tier only through the approved community/world process, including eligibility, reputation, political/community support, and the required vote/selection rules.

Possible authority, depending on the kingdom/government structure, can include:

- sovereign leadership
- national/kingdom policy
- high-level appointments
- diplomacy
- war/peace authority where constitution/rules permit
- oversight of subordinate Presidents/governors/mayors where that government hierarchy uses them
- ceremonial/state leadership
- kingdom treasury/policy authority only through legitimate government systems

The King remains subject to Metaworld's server authority, law/world rules, death, evidence, economy, reputation, and removal/succession rules.

## Queen Rule

Queen belongs to the same **Royal/Sovereign tier** when the Queen is the actual sovereign ruler.

However, a spouse using the title Queen does not automatically receive every governing permission of the King simply because of marriage.

Therefore Metaworld separates:

- **Sovereign Queen** — Tier 1 governing authority equivalent to sovereign King where the government supports it.
- **Royal Consort Queen** — royal/social title whose actual permissions come from the kingdom's constitution, appointments, and role definitions rather than automatic sovereign power.

The same distinction can be used for other royal spouses/consorts later.

---

# 3. Tier 2 — President

**President is directly below the King/Royal Sovereign tier in the global Metaworld roleplay hierarchy.**

A President is still an extremely high player rank and must be earned through the approved community election/selection process.

Possible President authority can include:

- national/republic leadership
- executive administration
- cabinet/department appointments where allowed
- national budget/policy proposals
- diplomacy
- emergency decisions
- military/security direction where constitutionally allowed
- coordination of governors, mayors, departments, and public services

President does not outrank a sovereign King in the canonical global hierarchy.

A President cannot purchase the office with GrimKoin.

---

# 4. Recommended Civic Rank Ladder

The default broad roleplay hierarchy is:

1. **Owner / Creator** — non-earnable Metaworld authority
2. **King / Sovereign Queen** — highest player-held world rank
3. **President**
4. **Governor / Regional Sovereign Delegate**
5. **Mayor / City Leader**
6. **Council / Senior Civic Leadership**
7. **Department Heads / Chiefs / Commissioners**
8. **Senior Professional Command**
9. **Professional Officers / Workers / Licensed Specialists**
10. **Citizens / Residents / Civilians**

This is the global roleplay rank order, not a claim that every government must contain every title.

Example:

A kingdom may use:

`King -> Governor -> Mayor -> Department Heads -> Citizens`

A republic may use:

`President -> Governor -> Mayor -> Department Heads -> Citizens`

A territory may have no President or King and start at Governor or Mayor.

The hierarchy defines relative placement when titles coexist; it does not force every city to spawn every office.

---

# 5. Professional Ranks Sit Inside Their Organization

Professional ranks should not be confused with world-government rank.

Example police hierarchy:

`Police Chief / Commissioner`
-> `Captain`
-> `Lieutenant`
-> `Sergeant`
-> `Senior Officer`
-> `Officer`

A Police Captain may command police officers but does not automatically outrank a Mayor, Governor, President, or King in civic authority.

Similarly:

- Chief Doctor controls appropriate hospital/medical operations, not the whole city.
- Business CEO controls their company, not public government.
- Guild leader controls their guild according to guild rules.
- Military commander controls military units according to lawful command structure.

Authority is **scoped** to the organization and role.

---

# 6. Roleplay Placement System

Every official rank/role should be data-driven with a `RankDefinition` or equivalent Blueprint/Data Asset record.

Recommended fields:

- Rank ID
- Display Name
- Global Tier
- Organization Type
- Parent Rank
- Child/Subordinate Ranks
- Jurisdiction
- Election/Promotion Requirements
- Appointment Authority
- Permissions
- Uniform/Insignia
- Salary if applicable
- Term Length if applicable
- Reputation Requirements
- Removal Rules
- Succession Rules
- Death/Vacancy Behavior
- Event Ledger/News significance

This lets Metaworld place everyone correctly without hardcoding every role directly into character Blueprints.

Possible global tags:

- `Rank.Owner`
- `Rank.Royal.King`
- `Rank.Royal.Queen.Sovereign`
- `Rank.Royal.Queen.Consort`
- `Rank.Civic.President`
- `Rank.Civic.Governor`
- `Rank.Civic.Mayor`
- `Rank.Civic.Council`
- `Rank.Police.Chief`
- `Rank.Police.Captain`
- `Rank.Police.Lieutenant`
- `Rank.Police.Sergeant`
- `Rank.Police.Officer`

---

# 7. Rank Does Not Mean Omnipotence

A higher roleplay rank does not automatically grant permission to do everything.

Example:

A King may outrank a Police Captain politically, but that does not mean the King automatically has:

- Gunsmith profession knowledge
- Builder qualification
- Doctor abilities
- access to a private player's bank account
- magical access to locked property
- immunity from cameras/evidence
- immunity from hunger
- immunity from death

Rank, profession, skills, ownership, legal authority, and capabilities remain separate systems.

This preserves Metaworld's existing rule:

> Authority tells the world your legitimate role. It does not let you bypass the physical rules of the world.

---

# 8. Elections, Promotion & Community Trust

The hierarchy controls placement, but players still earn the office/rank through the correct system.

Political offices can require:

- eligibility
- community reputation
- citizenship/residency
- candidate registration
- campaign
- votes
- certification

Professional ranks can require:

- service
- training
- performance
- lawful conduct
- department trust
- community trust
- appointment/promotion/vote where configured

GrimKoin cannot directly increase the official Rank Tier.

A player may spend GrimKoin on campaigns, advertising, staff, events, security, or legal influence activities already allowed by Metaworld, but the official rank service remains authoritative.

Corruption/bribery remains risky criminal gameplay rather than legitimate rank progression.

---

# 9. Death, Vacancy & Succession

Because character death is permanent, leadership roles must react to death.

If a King, President, Governor, Mayor, Police Captain, or other officeholder permanently dies:

- the character loses the office because that character is dead
- the office becomes vacant or enters succession/interim state
- the dead player's new character does not automatically inherit the rank
- government/organization rules select an interim or permanent replacement
- Event Ledger records major leadership death/vacancy
- Metaworld News may report it

A will can affect private property/business inheritance but does not automatically transfer an elected public office.

Royal succession, if later designed, must be explicitly defined and cannot silently override the current community legitimacy rules.

---

# 10. Core Hierarchy

Canonical world-roleplay order:

```text
OWNER / CREATOR
      ↓
KING / SOVEREIGN QUEEN
      ↓
PRESIDENT
      ↓
GOVERNOR / REGIONAL LEADER
      ↓
MAYOR / CITY LEADER
      ↓
COUNCIL / SENIOR CIVIC OFFICIALS
      ↓
DEPARTMENT HEADS / CHIEFS / COMMISSIONERS
      ↓
PROFESSIONAL COMMAND RANKS
      ↓
PROFESSIONALS / OFFICERS / WORKERS
      ↓
CITIZENS / RESIDENTS
```

Not every government requires every layer, but when these ranks coexist, this is their canonical relative placement.

Final rule:

> The Owner stands above the world hierarchy. King is the highest player-held rank. President comes next. Every other rank is placed beneath them according to its jurisdiction and organization so Metaworld roleplay remains understandable, earned, and consistent.

---

## Supersession Note

This document supersedes older Metaworld wording only where the older wording left the **relative order of King, President, and other civic ranks undefined**. Existing rules about community voting, merit, no direct GrimKoin rank purchase, corruption risk, permanent death, government responsibility, and scoped professional authority remain unchanged.