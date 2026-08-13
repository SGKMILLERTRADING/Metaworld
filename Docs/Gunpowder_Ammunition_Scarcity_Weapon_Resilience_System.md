# Metaworld — Gunpowder, Ammunition Scarcity & Weapon Resilience System

**Status:** Canonical / Locked Cross-System Rule

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first / server-authoritative / persistent economy / living-world scarcity

## Canonical Principle

Gunpowder/propellant ammunition is **not an infinite game resource** in Metaworld. Firearms, cartridges and the industrial supply chains that sustain them exist as persistent world resources that can become scarce, critically scarce or effectively unavailable over the life of the world.

> Guns are powerful while ammunition exists. Ammunition is not guaranteed forever. If the supply chain dies, firearms can become old tools with no practical fuel, while swords, bows, crossbows, spears, axes and other maintainable weapon systems become strategically important again.

Metaworld is not designed around a permanently convenient combat meta. Technology, scarcity and player/world behavior can change what is practical.

Related canon:

- `Docs/Persistent_Item_Interaction_Inventory_Architecture.md`
- `Docs/Ranged_Weapons_Bow_Ammo_Quiver_Container_System.md`
- `Docs/Crafting_Recipes_Materials_Production_System.md`
- `Docs/Item_Valuation_Vendor_Pricing_Trade_System.md`
- `Docs/Smart_News_Event_Selection_System.md`
- `Docs/Performance_Smoothness_FrameTime_Architecture.md`

---

# 1. Firearms Are Persistent Tools, Ammunition Is Consumable World Stock

A gun remains a persistent ItemInstance with its own:

- definition;
- condition/durability;
- owner/provenance;
- upgrades/modifications;
- legal/evidence state;
- value/history.

Ammunition is separate persistent consumable stock.

Every legitimate fired round reduces actual available ammunition/propellant supply somewhere in the world economy.

The UI or weapon animation cannot create rounds from nothing.

---

# 2. No Infinite Ammunition Loot Faucet

Loot tables, enemy respawns, vendor restocks and container reopening must not secretly regenerate an endless modern-ammunition supply.

Possible legitimate ammunition sources:

- existing stockpiles/caches;
- business/vendor inventory;
- police/military/government reserves;
- player/NPC stored ammunition;
- manufacturing output while the industrial chain still functions;
- recovered/redistributed lawful or illicit stock;
- world-event shipments/imports if the world still has a source;
- rare authored discoveries/caches that exist once in persistent world state.

Once a persistent cache is depleted, reopening/reloading the area does not refill it unless a real restock event occurred.

---

# 3. Scarcity States

The world/economy may track broad scarcity for ammunition/propellant families.

Example states:

- Available
- Tight Supply
- Scarce
- Critical
- Strategic Reserve Only
- Effectively Exhausted / No Accessible Supply

These states are descriptive/data-driven, not mandatory fixed thresholds.

Different regions/calibers/ammunition families can reach different scarcity levels at different times.

---

# 4. Practical Exhaustion Is Allowed Canon

Metaworld explicitly allows a world state where ordinary gunpowder/propellant ammunition can no longer be found through normal gameplay because:

- old stock has been fired/consumed;
- stockpiles were destroyed/stolen/exhausted;
- factories shut down;
- required industrial inputs/logistics disappeared;
- governments/organizations retain only inaccessible strategic reserves;
- transport/trade routes collapse;
- production knowledge/equipment exists but cannot currently be supplied.

At that point firearms still physically exist.

They simply may have no ammunition to use.

That is an intended world consequence, not a balance bug.

---

# 5. Recovery Is Not Guaranteed

A future society/player organization may attempt to restore ammunition production, but Metaworld does not guarantee success.

Restoration can require abstract world systems such as:

- suitable industrial facilities;
- skilled professions/engineering;
- functioning power/utilities;
- secure supply chains;
- required material/chemical inputs represented safely as game data;
- machinery/tools;
- transport;
- workforce;
- legal/security control.

Metaworld documentation should model these at system/gameplay level and does not require real-world explosive manufacturing instructions.

If the world cannot rebuild the chain, scarcity can remain effectively permanent.

---

# 6. Ammunition Is Not Created By Money

Having GrimKoin does not guarantee ammunition exists to purchase.

In a shortage:

- vendors may have zero stock;
- prices can rise sharply;
- organizations may ration supply;
- legal sales may stop;
- black markets may appear;
- theft/robbery/conflict over stock can increase;
- counterfeit/unsafe goods may become a world/economy risk if later designed.

Currency expresses purchasing power; it does not conjure physical supply.

---

# 7. Firearm Value Changes With World State

A firearm can move through economic roles over time.

Example:

`Plentiful ammunition era`
-> firearm = powerful practical weapon

`Critical shortage`
-> firearm = valuable but expensive to operate

`No ammunition`
-> firearm = stored emergency/historical/collectible/obsolete practical tool

A rare gun with zero available ammunition may be worth less as a combat tool while remaining historically, legally or collector-significant.

The contextual valuation system decides actual market behavior.

---

# 8. Pre-Firearm / Low-Industrial Weapons Remain First-Class

Swords, bows, crossbows, spears, axes, clubs and other older weapon families are never designed as throwaway tutorial weapons that become useless once the player finds a gun.

They remain relevant because they may be:

- maintainable with more locally available materials;
- reusable without consuming cartridges every attack;
- quieter;
- repairable by different professions;
- practical when ammunition is unavailable;
- tactically useful in close quarters or specialized circumstances;
- culturally/factionally important;
- usable by characters without firearm access/licensing;
- compatible with recoverable ammunition such as arrows/bolts where applicable.

They still require skill, stamina, maintenance, materials and risk. They are not an `easy mode` replacement.

---

# 9. Bows / Crossbows / Recoverable Ammunition

Bows/crossbows use the existing ranged architecture.

Arrows/bolts remain physical ammunition and can also become scarce, but unlike a fired cartridge they may be recoverable/recraftable according to material, impact and breakage rules.

Possible result:

- arrow survives and is recoverable;
- arrow breaks and materials are lost/salvageable;
- special arrow payload is consumed;
- lost arrow remains in persistent world state until cleanup policy resolves it.

This gives ranged weapons different long-term logistics rather than making them infinite.

---

# 10. Melee Weapon Logistics

Melee weapons consume condition/durability, stamina and repair resources rather than cartridge stock per strike.

A sword can become damaged, broken, stolen or impossible to repair if metalworking resources disappear.

Therefore `gunpowder exhausted` does not mean `all other weapons are free forever`.

Every weapon family has its own logistical pressure.

---

# 11. NPC / Faction Adaptation

NPCs, businesses, police, military groups, gangs and factions should adapt loadouts/behavior to real available supply.

Examples:

- police conserve ammunition;
- factions switch to bows/melee;
- elite units retain small strategic firearm reserves;
- traders stop listing unavailable ammunition;
- raids target stockpiles/factories;
- guards use different weapons depending on local resources;
- training/profession demand shifts toward archery, smithing, repair and low-tech production.

Do not spawn a firearm loadout with infinite ammo merely because an NPC archetype says `Gun User`.

---

# 12. Crafting / Industry

Ammunition production is an industrial crafting/manufacturing process using abstract recipe/resource definitions.

It obeys:

- RecipeDefinitionID;
- required facilities/tools;
- profession/skill;
- source materials;
- utilities;
- batch quantity;
- business ownership/access;
- server-authoritative reservation/consumption/output.

No UI craft loop creates infinite ammo from missing inputs.

Sensitive real-world explosive formulation details are not required for gameplay architecture.

---

# 13. Stockpiles / Strategic Reserves

Organizations may intentionally reserve ammunition.

Possible storage:

- armory;
- police station;
- military depot;
- secure warehouse;
- private collection;
- hidden cache;
- vehicle shipment.

These are persistent containers with access/security/crime rules.

If a reserve is stolen/destroyed, that change matters to the real world supply.

---

# 14. Crime / Politics / War

Scarcity can create:

- ammunition theft;
- smuggling;
- rationing;
- black-market trading;
- hoarding;
- political conflict over factories/resources;
- raids on depots;
- war over supply chains;
- law changes;
- corruption;
- counterfeit trade;
- strategic disarmament.

These consequences can feed the Event Ledger, Smart News, reputation and legal systems.

---

# 15. Smart News / World Events

Meaningful events may include:

- ammunition factory shutdown;
- major stockpile theft;
- government rationing;
- last regional supplier closing;
- discovery of a major cache;
- restored production line;
- catastrophic destruction of supply infrastructure;
- faction seizure of strategic reserves.

Routine individual bullet usage is not a news event.

---

# 16. Server Authority / Persistence

Server owns:

- ammunition quantities;
- container stock;
- shot consumption;
- manufacturing output;
- stockpile transfers;
- scarcity/world-supply records;
- vendor availability;
- loot/cache depletion.

Clients cannot generate ammunition by reload, reconnect, Actor respawn, loot-menu reopen or local craft UI.

Save/load/server restart preserves depletion.

---

# 17. Performance

Do not simulate every round in every warehouse as an Actor.

Stored ammunition is compact persistent stack/lot data.

World supply/scarcity aggregates update from meaningful transactions/events.

Only locally relevant projectiles/loose ammunition require active Actors.

---

# 18. Player Experience Principle

Metaworld is intentionally not a world where the strongest technology remains permanently convenient.

Players must respond to:

- shortages;
- changing prices;
- lost infrastructure;
- altered faction behavior;
- weapon availability;
- repair/material pressure;
- world events.

There is no guarantee that the best strategy today remains the best strategy months/weeks later in world time.

This keeps players adapting rather than permanently solving combat with one item class.

---

# 19. Acceptance Tests

1. Firing a gun consumes real authoritative ammunition.
2. Reopening/reloading an emptied cache does not respawn ammunition.
3. Vendor cannot sell ammo that does not exist in legitimate stock/supply policy.
4. GrimKoin cannot create unavailable ammunition.
5. World can reach practical zero accessible gunpowder/propellant ammunition.
6. Existing firearms remain persistent items when ammo disappears.
7. NPC/faction loadouts adapt to actual supply.
8. Bows/swords/melee remain viable first-class weapon families throughout the game.
9. Arrows/bolts obey recover/break/craft rules rather than infinite ammo.
10. Ammunition manufacturing requires real abstract recipe/facility/resource inputs.
11. Save/load preserves stockpile depletion and scarcity.
12. Loot system cannot become an infinite ammo faucet.
13. Major supply events can feed Smart News/Event Ledger.
14. Scarcity changes market value without rewriting ItemDefinition identity.

## Core Rule

> Metaworld does not promise ammunition forever. Every round fired participates in a living finite supply chain. When that chain fails, guns can become relic-like tools and older weapon systems become essential again—forcing players, NPCs and societies to adapt to the world instead of expecting the world to stay easy.