# Metaworld — Earth, Property, Vehicles, Media & Living News

## Canonical World Identity

Metaworld takes place on Earth in a persistent modern world. It is not a separate fantasy realm with modern props added on top. Roads, towns, wilderness, hills, homes, apartments, businesses, clubs, vehicles, utilities, law, survival threats, social life, magic/supernatural systems, and player-created history all exist inside the same world simulation.

Players should be free to choose radically different lifestyles while still inhabiting the same shared world.

Examples:

- Build a remote house in the hills and only travel into town for goods, work, trade, medical care, entertainment, or social contact.
- Live in a dense town that never sleeps.
- Rent a cheap room when new.
- Buy a townhouse for personal use.
- Build houses and rent them to other players.
- Own apartments, stores, clubs, garages, farms, warehouses, offices, workshops, or entertainment venues.
- Own land and use its vertical space for towers, rooftop structures, elevated homes, sky houses, stacked rentals, bridges, platforms, or other construction where allowed by the parcel rules.

The world should support both solitude and dense social life without declaring either one the correct way to play.

---

# 1. Three-Dimensional Property Rights

Metaworld property is not treated only as a flat ground tile. A property deed defines a three-dimensional parcel/build volume.

A parcel can include:

- Ground footprint
- Buildable vertical range / air rights
- Optional subsurface rights
- Entry/access permissions
- Ownership
- Rental/lease rights
- Construction limits driven by technical performance budget rather than arbitrary decorative restrictions

The design goal is to let players use the space they paid for while keeping the shared world technically stable.

## Property Types

Possible property forms include:

- Rural land
- Hill/mountain property
- Town lots
- Townhouses
- Apartments
- Rental rooms
- Farms
- Garages
- Workshops
- Shops
- Warehouses
- Clubs/bars
- Offices
- Player-built apartment buildings
- Elevated/sky homes
- Mixed-use properties

## Ownership and Rental

Properties should support:

- Buy
- Sell
- Rent
- Lease
- Sublet where the owner permits it
- Guest permissions
- Family/group permissions
- Business permissions
- Storage permissions
- Build permissions
- Lock/access rules
- Tenant rights and lease duration

Town-owned or NPC-managed rooms can provide an early housing market, while player landlords can later compete by building or purchasing better housing.

A new player does not automatically receive a house. Housing is something the player finds, rents, earns, builds, shares, or buys.

## Vertical Space Rule

Players can build above their land, including elevated and sky structures, but the deed defines a finite 3D build envelope so the engine can stream, replicate, save, and render the parcel safely.

This preserves the Second-Life-style freedom of using vertical space without treating every parcel as literally infinite.

Recommended systems:

- Property/Parcel Subsystem
- 3D Parcel Volume definition
- Property Deed data asset/record
- Ownership and Permission Component
- Lease/Rental subsystem
- Property taxation/fees only if later required by economy design
- Build Budget / Streaming Budget policy
- Persistent construction records

---

# 2. Vehicles as Mobile Property and Storage

Vehicles are not only transportation. They are mobile assets with real inventory/storage utility.

The larger and more suitable the vehicle, the more it can carry.

Examples:

- Motorcycle: extremely limited storage
- Small car: glovebox + small trunk
- Sedan: moderate trunk storage
- SUV: larger cargo storage
- Pickup: bed + cabin compartments
- Van: large cargo area
- Box truck: very large cargo capacity
- Trailer: additional towable storage
- Specialized vehicles: purpose-built storage or equipment

Storage should not be based only on a single arbitrary slot number. The architecture should be capable of considering:

- Cargo volume
- Weight/mass
- Item dimensions where relevant
- Compartments
- Seat occupancy versus cargo use
- Vehicle upgrades
- Installed racks/boxes/containers
- Damage state

The game can simplify these calculations for usability, but the data model should allow physical differences between vehicles to matter.

Vehicles can later support:

- Personal ownership
- Shared/group ownership
- Keys/access permissions
- Locking
- Theft
- Insurance/recovery systems if desired
- Fuel/energy
- Maintenance
- Damage
- Repair
- Modifications
- Mobile storage
- Sleeping/rest in suitable vehicles
- Radios/media sessions

Recommended systems:

- Vehicle Definition data assets
- Vehicle Ownership Component
- Vehicle Cargo Component
- Cargo Capacity evaluator
- Vehicle Access/Key system
- Vehicle persistence records

---

# 3. Room- and Vehicle-Scoped Personal Media

Players should be able to play music and video in-world, but playback is scoped to the physical social context.

Core rule:

> Media belongs to a place/session, not to the whole server.

Examples:

- A player starts music in their car: occupants of that car can hear it.
- A player plays music inside their house: players inside the relevant room/media zone can hear it.
- A club owner runs music in the club: attendees in that venue hear it.
- A television plays a video: players close enough and inside the relevant viewing space can see/hear it.
- Walking out of the room/car/venue removes the player from that media session unless the content is also being broadcast through another legitimate in-world system.

## Media Session Architecture

A Media Session should contain:

- Session owner/host
- Source type
- Source identifier
- Playback state
- Playback timestamp
- Volume policy
- Spatial/room/vehicle scope
- Permission rules
- Participant list resolved from physical presence

The server should primarily synchronize playback state and authorization. Where technically appropriate, clients retrieve/play approved media themselves rather than the Metaworld gameplay server acting as a giant media relay.

## Player Controls

Players must have:

- Local mute
- Local volume
- Media opt-out
- Block/mute controls for abusive sources/users
- Content-safety controls where required

## Content Rule

The feature should support media the player is permitted to use or services/sources that Metaworld is allowed to integrate. The architecture should not assume that arbitrary copyrighted files can simply be rebroadcast to other players without restrictions.

Recommended systems:

- Media Session Subsystem
- Spatial Media Zone Component
- Vehicle Media Component
- TV/Screen Media Component
- Playback synchronization service
- Permission/source policy
- Local mute/volume controls

---

# 4. Metaworld Living News Network

Metaworld should have actual in-world news generated from events that really happened in Metaworld.

The project already intends to keep persistent records of world events. Those records can become the factual foundation of a news system.

A player can return home, turn on a television, radio, phone, computer, newspaper, or other media device and learn what has been happening in the world.

Possible stories:

- Zombie outbreak in a district
- Major player rescue
- Large fire
- Blackout
- Famous crime
- Arrest
- Court verdict
- Prison escape
- New mayor/election result
- Guild/faction conflict
- Business opening or collapse
- Major property sale
- Historic construction project
- Player achievement
- Discovery
- Major battle
- Community event
- Religious/cultural event
- Rare item discovery
- Major market/economic change
- Death or memorial of a historically important character if the game supports it

## Verified Event Ledger

World systems publish structured events into a persistent event ledger.

Example:

World Event
- Event ID
- Timestamp
- Location
- Participants
- Event Type
- Verified server facts
- Consequences
- Related property/business/faction
- Public/private classification
- Historical importance score

The official Metaworld news service should report only facts supported by the server/event ledger. If rumors, speculation, or player journalism are supported later, they should be clearly distinguished from verified official reporting.

## News Pipeline

World systems -> Event Bus -> Persistent Event Ledger -> Newsworthiness/Verification -> Story generation/editorial layer -> TV/Radio/Newspaper/App -> Player watches/reads/listens

Because the world already records events, the news is not fake background flavor. It is a readable/watchable version of the world's own history.

## Historical Continuity

Major news events can also feed:

- Monuments
- Memorials
- Museums
- Town records
- Player biographies
- Faction histories
- Property history
- Server/world timeline

This turns everyday emergent gameplay into persistent culture and history.

Recommended systems:

- World Event Bus
- Persistent Event Ledger
- Event Verification/Visibility rules
- Newsworthiness evaluator
- News Story records
- Broadcast schedule/content service
- TV/Radio/Newspaper/Phone presentation clients
- Historical archive

---

# 5. Example Emergent Life

A player starts with one food item and one water item.

They rent a cheap town room because they cannot afford property.

They work jobs, trade, scavenge, learn skills, and eventually earn GrimKoin.

They buy a used car. The trunk becomes their first meaningful mobile storage.

Later they buy land in the hills and build a remote home with a workshop and storage.

They mainly live outside town, driving in when they need supplies, social contact, repairs, work, trade, or entertainment.

Another player chooses the opposite life: they buy a townhouse, open a club, build apartments above it, and rent rooms to other players.

At the club, the owner starts a room-scoped music session. Only people physically in the club hear it.

During the party, a zombie outbreak reaches the district. The same venue that was a social space becomes a survival space. Players barricade doors, improvise weapons from furniture, use medical and combat skills, and evacuate through vehicles whose cargo space is used to carry supplies and injured survivors.

The server records the outbreak, casualties, rescues, property damage, arrests, heroic actions, and other verified facts.

Later, survivors go home and watch a Metaworld news broadcast reporting the event they actually lived through.

That is the target experience: social life, property, transport, survival, combat, economy, media, and history are not separate games. They are systems inside one persistent world.
