# Metaworld — Real-Time Life, Utilities, Advertising, VIP GrimKoin, Death & Legacy Recovery

## Canonical Principle

Metaworld runs as a persistent Earth-based world on real calendar time. The world does not pause when a player logs out, and the passage of time creates real obligations, opportunities, risks, and history.

A real-world month is a Metaworld month for billing, rent, taxes, subscriptions, permits, wages, and other monthly obligations unless a specific system explicitly defines a different schedule.

Core rule:

> Life in Metaworld can become comfortable, wealthy, social, and powerful — but maintaining that life requires work, money, planning, relationships, and protection.

---

# 1. Real-Time Calendar

Metaworld should maintain an authoritative persistent calendar tied to real-world elapsed time.

The calendar can drive:

- Days
- Weeks
- Months
- Years
- Rent due dates
- Utility bills
- City taxes
- Billboard permits
- Business fees
- Employee payroll
- Property obligations
- Seasonal events
- Elections
- News archives
- Weather/climate seasons where appropriate
- Subscription/service renewals
- Loan/mortgage payments later
- Insurance premiums later

The visual day/night cycle may use presentation tuning where necessary, but economic due dates and monthly obligations should follow the real calendar unless deliberately configured otherwise.

The authoritative clock must continue while players are offline.

---

# 2. Monthly Bills and Utilities

Owning or renting property can create recurring bills.

Possible services include:

- Electricity
- Water
- Heating
- Gas/fuel where appropriate
- Waste/sanitation fees where privately billed
- Internet/communications later
- Building maintenance contracts
- Property security contracts
- Rent
- City property/land tax where applicable

Bills should have:

- Account/property ID
- Service provider
- Billing period
- Amount due
- Due date
- Grace period if the service defines one
- Payment status
- Shutoff eligibility
- Reconnection requirements
- Transaction history

---

# 3. Utility Shutoff Has Gameplay Consequences

Unpaid services are not merely warning text.

If electricity is disconnected:

- Lights stop working
- Refrigeration may stop
- Some security systems fail
- Powered doors/equipment may fail
- Entertainment systems stop
- Heating/cooling may fail
- Business operations may be disrupted

If water is disconnected:

- Sinks/showers/plumbing systems may stop
- Cooking/cleaning operations may be affected
- Some businesses may be unable to operate normally

If heating fails during dangerous cold:

- Indoor temperature can fall over time
- Player/NPC comfort and health can be affected
- Pipes/equipment can be at risk if later simulated
- Residents may need fireplaces, generators, alternate heat, shelter, or relocation

If cooling fails during extreme heat, the opposite problem may occur.

Weather, utilities, property quality, generators, insulation, fuel reserves, and emergency systems should interact.

---

# 4. Backup Systems Create Value

Prepared owners can protect themselves from service loss or disasters with systems such as:

- Generators
- Solar/battery systems later
- Water tanks
- Wells where property permits
- Stored fuel
- Fireplaces
- Backup heaters
- Insulation upgrades
- Emergency food/water
- Backup communication systems

This creates work for electricians, mechanics, builders, utility workers, suppliers, and security businesses.

---

# 5. News Is Everywhere

Metaworld News should exist throughout ordinary life, not only when a player deliberately opens a menu.

Official verified news can appear through:

- Television
- Radio
- Car radio
- Public screens
- Store televisions
- Club/bar screens
- Hotel/lobby televisions
- Phones/computers later
- Newspapers/publications later
- Transit/public displays
- Emergency alert systems

The same verified Event Ledger remains the factual source for official Metaworld News.

Player journalism, advertising, entertainment, rumor, and opinion must remain distinguishable from official verified news.

---

# 6. City Billboard and Advertising Economy

Businesses can purchase the right to display advertisements on city-controlled billboard locations and other approved advertising surfaces.

Possible advertising locations:

- Roadside billboards
- Building-mounted signs where permitted
- Transit stops
- Public display boards
- Mall/public market advertising spaces
- Digital city screens
- Event signage

The business pays the city for the advertising right.

Possible charges include:

- Initial placement/permit fee
- Monthly billboard rent
- Monthly advertising tax/permit fee
- Premium location surcharge
- Digital-screen scheduling fee where applicable

These payments go to the city treasury, not to Metaworld's platform commission unless a separate platform transaction fee also applies.

A billboard contract should track:

- Billboard/location ID
- Business/owner ID
- Approved advertisement asset
- Start date
- End/renewal date
- Monthly charge
- Tax/permit rate
- Payment state
- Content moderation/approval state

If the owner stops paying, the city can remove or deactivate the advertisement after the applicable billing/grace rules.

Advertising becomes another meaningful city revenue stream that helps fund public workers and services.

---

# 7. Metaworld VIP Store — Exclusive Real-Money GrimKoin Seller

Metaworld is free to play, but players may optionally purchase GrimKoin directly from the official Metaworld VIP Store.

Canonical issuance rule:

> Only the Metaworld VIP Store may sell newly issued GrimKoin for real-world money.

Players cannot create/mint GrimKoin.

Players can obtain GrimKoin through:

- Jobs
- Wages
- Tips
- Business profits
- Creator sales
- Trading
- Contracts
- City/public work
- Legitimate player-to-player gifts of already-existing GrimKoin
- Other legitimate in-world earnings
- Optional purchase from the official VIP Store

## Strict Gifting Rule

A GrimKoin gift must come from GrimKoin the gifting player already owns.

Valid gift sources are:

- GrimKoin the player legitimately earned through gameplay/economic activity; or
- GrimKoin the player previously purchased from the official Metaworld VIP Store.

A gift is only an ownership transfer. It never creates new GrimKoin.

The gifting player must have the transferred amount available in an eligible owned balance at the time the transfer commits. The system must debit the giver and credit the receiver atomically.

There is no separate system-generated "gift GrimKoin," no infinite gifting allowance, and no other method for a player to mint currency by calling a gift function.

If future bank-to-bank gifting/transfers are allowed, the same rule applies: the funds must already exist in the sender's own account and must move through the authoritative ledger.

---

# 8. Free-to-Play vs Paid Acceleration

A free player should be able to survive, work, earn GrimKoin, learn professions, build relationships, own property eventually, create businesses, and rise in the world through gameplay.

However, free players cannot simply refuse all economic participation forever without consequences.

They still need:

- Food
- Water
- Shelter when conditions require it
- Bills if they own/rent services
- Equipment/resources
- Protection

A player who purchases GrimKoin from the VIP Store can start faster or maintain an expensive lifestyle more easily because they have additional spending power.

The VIP Store should not grant unique supernatural rule-breaking capabilities that free players can never obtain through gameplay unless Metaworld deliberately creates a separate cosmetic/status product category later.

The economy must still be tuned so a player who never spends real money has a viable path through work, skill, business, trade, and cooperation.

---

# 9. GrimKoin Issuance Ledger

Every VIP-store GrimKoin purchase should be recorded separately from earned GrimKoin.

Recommended ledger provenance fields:

- Transaction ID
- Account ID
- Character ID at time of purchase
- GrimKoin amount
- Real-money purchase reference
- Issuance source: VIP Store
- Timestamp
- Wallet/bank destination
- Fraud/refund status

Every player-to-player gift should also record:

- Giver account/character ID
- Receiver account/character ID
- Amount
- Source balance
- Provenance linkage to already-existing GrimKoin
- Timestamp
- Before/after balances

This allows Metaworld to distinguish currency that was issued through the VIP Store from currency earned through gameplay while still proving that gifts only move existing currency.

This distinction may become important for future economy analytics, fraud detection, refunds, balancing, and any future GrimKoin buyback program.

---

# 10. Future GrimKoin Buyback Remains Disabled for Now

Metaworld may later buy eligible GrimKoin back from players for real-world money.

This is a future concept only.

The current system should prepare provenance and accounting data but should not expose real-money cashout until a separate future phase deliberately enables it.

The future system will need its own eligibility, fraud, identity, legal, tax, payment, and payout controls.

The VIP Store and future buyback must remain separate transaction types so Metaworld can control issuance, redemption, rates, limits, and eligibility independently.

---

# 11. True Character Death

Death in Metaworld is a real character event.

When a character dies permanently:

- That character is dead.
- The dead character's display/character name is retired as that person's identity.
- The player returns through the same underlying Metaworld account but as a new character identity.
- The player must choose/create a new character name.
- The new character does not receive the original new-player food/water starter package because the account has already passed the new-player state.

Important distinction:

The permanent account ID survives for technical identity, moderation, purchases, security, and historical continuity.

The character identity does not survive.

Recommended identity structure:

Metaworld Account ID — permanent
-> Character Identity A — can die permanently
-> Character Identity B — new life after death
-> Character Identity C — later life if B dies

The world history can remember that these are separate characters without exposing private account linkage to ordinary players unless a gameplay system deliberately reveals lineage/legacy.

---

# 12. Death Does Not Reset the Account to New-Player Status

A returning player after permanent character death does not become a first-time account again.

They do not receive:

- Free new-player food
- Free new-player water
- Another first-time tutorial reward package
- Automatic replacement property
- Automatic replacement vehicles
- Automatic replacement inventory

They must survive their new life using whatever resources, allies, knowledge, legacy claims, work opportunities, or recovery options remain available.

---

# 13. Death Must Be Expensive Enough to Change Player Behavior

Permanent death is intentionally costly.

Metaworld should create a real reason for players to value ordinary life, friendships, entertainment, business, family/community activity, parties, professions, and peaceful prosperity instead of treating constant fighting as the only meaningful activity.

A player considering a pointless fight may be risking:

- Their current character identity
- Carried GrimKoin
- A major portion of banked GrimKoin
- Property security
- Vehicles
- Equipment
- Businesses
- Relationships
- Reputation
- Recovery time
- Valuable possessions

Core design goal:

> Fighting can be exciting, but dying should hurt enough that a successful life is worth protecting.

---

# 14. Physical Property and Possessions Can Be Lost After Death

The dead character's physical world does not disappear.

Their:

- House
- Land
- Vehicles
- Weapons
- Clothing
- Furniture
- Storage
- Business inventory
- Tools
- Creator goods
- Other physical possessions

remain in the persistent world according to their normal ownership/location state.

Friends, guards, employees, tenants, enemies, thieves, raiders, hostile NPCs, factions, police, landlords, and other systems continue interacting with that property.

The new character does not automatically teleport every old item into a new inventory.

If the dead character's friends, guards, or allies also die or abandon the property, no artificial protection appears. Hostile players or NPCs can take advantage of the loss of defenders under normal world rules.

---

# 15. Tracking Codes / Asset Recovery Codes

Important owned assets can expose a private tracking/recovery code while the original character owns them.

The player must deliberately copy/save that code if they want the ability to locate the asset after losing normal ownership visibility through death or other events.

Possible tracked assets:

- Vehicles
- High-value weapons
- Containers
- Property records
- Valuable equipment
- Important creator goods
- Other uniquely identified assets

The tracking code is effectively proof that the previous owner knew the unique asset identifier before losing ordinary access.

The code must not itself grant ownership or teleport the asset.

It only assists in locating/identifying the item during the allowed recovery period.

If the player never saved the code, the new character may have no direct tracking method and may need friends, witnesses, police, investigators, rumors, records, or ordinary searching to find the property.

---

# 16. Limited Legacy Recovery Window

After permanent character death, the account's new character receives a limited recovery/legacy period for eligible former assets.

During that period:

- Saved tracking codes can still resolve eligible assets.
- Loyal friends can help locate/protect property.
- Police/investigators may help where law permits.
- The new character can attempt to reclaim property through legal, social, economic, or combat means.
- Current possessors can resist where world rules allow.

The recovery period must be configurable.

When it expires:

- Special legacy tracking/recovery privileges end.
- Unrecovered physical property is no longer treated as specially recoverable by the former account.
- A player or NPC who has successfully taken/claimed/possessed the property under world rules may keep it.
- Unclaimed or abandoned estate assets can pass into city/NPC/system-controlled abandoned-property, auction, salvage, repossession, cleanup, or other Metaworld sink processes depending on asset type and jurisdiction.
- The former account no longer receives a special right to recover those assets merely because a previous character once owned them.

If the original player's friends also die, fail, or cannot recover the property before the timer expires, the same rule applies: the old estate is lost to whoever successfully controls it or to the applicable Metaworld/NPC/city system.

The exact duration should be balanced later rather than hardcoded now.

---

# 17. Recovery Is Not Automatic Ownership Restoration

Knowing where your former property is does not mean the world gives it back.

Example:

Character A dies.
-> Raiders steal A's truck.
-> Player returns as Character B.
-> B has the saved tracking code.
-> B locates the truck.
-> Raiders still physically possess it.
-> B must negotiate, buy it back, involve police, steal it back, defeat the raiders, or use another legitimate world solution.

Loyal friends therefore become extremely valuable.

A friend may:

- Guard the dead character's house
- Hide their vehicle
- Store valuables
- Tell the new character what happened
- Help track thieves
- Help reclaim property
- Protect the recovery mission

But friends are not immortal insurance. If they die too, abandon the estate, lose the fight, or fail to act before the recovery window ends, the estate can be permanently lost.

This makes relationships have real stakes.

---

# 18. Banked GrimKoin and Death — Up to 50% Can Be Lost

Banking protects GrimKoin from ordinary carried-cash loss, but it does not make death financially harmless.

Canonical death rule:

> On permanent character death, the bank/estate system may take up to 50% of the deceased character's banked GrimKoin before any surviving legacy balance can be recovered.

The exact percentage may be configured by the final death/estate balance rules, but it must never exceed 50% under this rule.

Example:

Bank balance before death: 20,000 GrimKoin

Possible death settlement:
- Estate/bank loss: 8,000 GrimKoin
- Surviving legacy balance: 12,000 GrimKoin

Maximum case:
- Estate/bank loss: 10,000 GrimKoin
- Surviving legacy balance: 10,000 GrimKoin

The lost share becomes an intentional economy sink or bank/estate settlement according to the configured economic rules. It is not automatically awarded to the killer.

The surviving balance enters the legacy/estate process rather than automatically appearing in the new character's wallet.

Physical carried GrimKoin can be governed by separate loot/death rules.

This creates a major reason to avoid meaningless death: even a wealthy player who banks carefully can lose a painful portion of accumulated wealth.

---

# 19. Death Becomes World History

A permanent character death can generate Event Ledger records.

Depending on importance, it can affect:

- Friends/relationships
- Businesses
- Employees
- Land ownership
- Factions
- Police investigations
- Court/estate processes later
- News
- Memorials
- Graveyards
- Monuments
- Player biographies
- Historical records

A famous mayor, business owner, criminal, musician, builder, warrior, or community leader dying should matter to the world.

The new character is a new person, not a magical resurrection of the old identity.

---

# 20. Example — Life, Bills, Death and Recovery

A player owns a house in a cold region.

They pay monthly:

- Property tax
- Electricity
- Water
- Heating
- Security contract

They run a store downtown and pay the city for two billboards.

They earn GrimKoin through their business and occasionally buy additional GrimKoin from the official VIP Store.

They bank most of their GrimKoin and carry only spending money.

One month they fail to pay the heating bill.

Heat is disconnected.

A cold weather event arrives.

The house becomes dangerously cold because the player never installed backup heating.

Later the character dies during another world event.

That identity is permanently dead.

The bank/estate system applies the configured death settlement and removes a portion of the dead character's banked GrimKoin, potentially as much as half.

The player returns through the same account as a newly named character and receives no first-time food/water package.

Their old truck has been stolen.

Their house is being defended by two loyal friends.

Because they saved the truck's tracking code, they can still locate it during the legacy recovery window.

They discover a hostile group now has the truck.

The new character and loyal friends must decide whether to negotiate, involve police, pay for recovery, or fight to get it back.

If both friends die during the recovery attempt and the new character still cannot reclaim the estate before the recovery timer expires, the former estate loses its special legacy protection. The hostile possessors or applicable NPC/city/Metaworld systems keep or dispose of the assets under world rules.

The world remembers the original character's death and everything that happened afterward.

---

# 21. Core Principle

Metaworld should not feel like a lobby where nothing matters after logout or death.

Time passes.

Bills become due.

Utilities can be cut.

Businesses advertise and pay the city.

News follows the world everywhere.

Players can work for GrimKoin or optionally buy newly issued GrimKoin only from Metaworld's VIP Store.

Players can gift only GrimKoin they already legitimately own; gifting never creates currency.

Death ends the character's identity.

Death can also destroy up to half of that character's banked GrimKoin through the bank/estate settlement system.

The account continues, but the next character starts a new life without first-time starter resources.

Property and possessions remain in the world and may be stolen, occupied, defended, reclaimed, or permanently lost.

Tracking codes and loyal relationships can help recover a former life — but only for a limited time.

If the new character and their allies fail, other players, NPCs, the city, or Metaworld's abandoned-property systems can ultimately keep or absorb what remains.

The target feeling is simple:

> A great life in Metaworld is possible, but the player has to build it, maintain it, protect it, survive long enough to keep it, and understand that death can erase a painful part of everything they built.
