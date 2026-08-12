# Metaworld — Creator Marketplace & Texture Derivative System

## Canonical Creator Economy Rule

Metaworld provides and controls the approved base meshes, UVs, material slots, master materials, shader logic, rigging, collision, sockets, LOD/Nanite setup, physics, gameplay metadata, and performance standards.

Players/creators may create and sell **texture-only visual derivatives** for creator-enabled Metaworld assets.

Creators may not add, remove, rename, reorder, replace, or otherwise edit material slots. They may not upload or modify shader graphs, master materials, material-slot structure, mesh geometry, collision, rigging, sockets, physics, or gameplay behavior.

The creator does not duplicate or redistribute the underlying base mesh. A creator product is a texture package that references a compatible Metaworld base asset.

This provides a Second Life / IMVU-style creator economy while keeping the technical asset foundation under Metaworld control.

A mandatory **Metaworld marketplace commission** is taken automatically from every successful creator sale. The creator receives the remaining proceeds. The commission percentage must be configurable by server/economy policy rather than hardcoded into product logic, so Metaworld can tune the fee later without breaking marketplace data or creator products.

---

# 1. Base Mesh + Creator Texture Architecture

Each supported asset has a stable Metaworld Asset ID.

Example:

Base Asset:
- Asset ID: `MW_CHAIR_001`
- Type: Furniture
- Mesh: Metaworld-managed
- UV Layout Version: 1
- Material Slots: Metaworld-locked
- Material Slot Count: 3
- Gameplay capabilities: Sit, Pickup, Carry, Throw, Break, Place
- Collision/LOD/physics: Metaworld-managed

Creator Product:
- Product ID: creator-specific
- Base Asset ID: `MW_CHAIR_001`
- Creator ID
- Texture package
- UV compatibility version
- Preview images
- Price
- Currency eligibility
- License/usage rules
- Moderation status

A buyer receives a texture entitlement referencing the original base asset. The base mesh, material-slot layout, and master materials remain canonical Metaworld assets.

---

# 2. Texture-Only Creator Modifications

Creators may only provide approved texture maps for the channels already exposed by the Metaworld asset.

Depending on the asset, allowed texture inputs may include:

- Base Color / Albedo texture
- Normal map texture
- Roughness texture
- Metallic texture
- Ambient Occlusion texture where used
- Emissive texture where supported
- Opacity/mask texture where supported
- Decal texture where supported by the base asset

The exact set of allowed texture channels is defined per base asset by Metaworld.

Creators may **not** change:

- Material slot count
- Material slot names
- Material slot order
- Material assignment
- Master material
- Shader graph
- Material functions
- Material parameters outside approved texture inputs
- Mesh geometry
- UV layout
- Collision
- Gameplay capabilities
- Weapon statistics
- Storage capacity
- Physics mass
- Rig/skeleton
- Sockets
- Inventory/economy rules
- Hidden gameplay code

Creator products are visual texture products only.

---

# 3. UV and Texture Template Distribution

For each creator-enabled base mesh, Metaworld exposes a Creator Texture Template containing:

- UV template
- Locked material slot names for reference
- Which texture maps belong to each locked slot
- Texture channel requirements
- Supported resolutions
- Safe naming rules
- Preview/test scene
- Color-space rules
- Compression guidance
- UV compatibility version

Creators design against the template without receiving edit authority over the underlying material-slot structure.

If a base mesh UV layout changes, Metaworld increments the compatibility version instead of silently breaking old creator products.

---

# 4. Locked Material Architecture

Metaworld controls the complete material system.

Architecture:

Base Mesh
-> Locked Metaworld Material Slots
-> Locked Metaworld Master Materials
-> Creator Texture Inputs
-> Rendered Player-Owned Variant

Creators do not create or edit material instances themselves. Metaworld may internally create or configure material instances at runtime or during asset processing, but those instances remain controlled by the game and only receive validated creator texture inputs.

Benefits:

- Predictable performance
- Stable shader complexity
- Consistent lighting behavior
- Easier validation
- Easier LOD/Nanite compatibility
- Easier future migration
- No creator-made expensive or malicious shader graphs
- No material-slot exploits

---

# 5. Marketplace & Player Shops

Creators can operate stores inside Metaworld.

Possible storefront forms:

- Physical shop
- Mall stall
- Home shop
- Market booth
- Club merchandise area
- Online/in-world marketplace terminal
- Creator profile storefront

A product listing can contain:

- Creator name/brand
- Product name
- Compatible base asset(s)
- Preview renders
- In-world demo/rezzable preview where allowed
- Price
- Currency accepted
- Permissions/license
- Tags/categories
- Version
- Update history
- Ratings/reviews later if desired

Players can buy a creator texture from a real in-world store and apply it to an owned compatible Metaworld item.

Every successful sale is split automatically between the creator and Metaworld according to the current marketplace commission policy.

---

# 6. GrimKoin / PromoKoin Integration

Creator products participate in the existing Metaworld economy.

Recommended rule:

- Premium/high-value creator goods normally use GrimKoin.
- Low-cost promotional/common creator goods may accept PromoKoin.
- Creators choose from marketplace-approved pricing/currency policies.
- Metaworld can enforce anti-abuse pricing rules if required.
- The marketplace commission applies regardless of whether the transaction uses GrimKoin or PromoKoin, unless a specific promotional policy explicitly overrides it.

The marketplace should not create a third unrelated currency unless a later design explicitly requires one.

Every transaction generates a server-authoritative ledger record containing buyer, seller, product, gross price, currency, marketplace fee percentage, marketplace fee amount, creator net proceeds, timestamp, and entitlement result.

---

# 7. Marketplace Commission / Metaworld Revenue Share

Metaworld must earn a small percentage from creator-marketplace sales so the platform itself benefits as the creator economy grows.

Core rules:

- Every normal creator sale includes a Metaworld commission.
- The commission percentage is defined by economy configuration, not hardcoded into individual products.
- The creator sees the fee before publishing the listing.
- The buyer sees the final purchase price.
- The creator receives the net amount after the Metaworld commission.
- Metaworld receives the commission automatically as part of the same atomic transaction.
- Failed/refunded/reversed transactions must reverse both creator proceeds and the marketplace commission according to the final refund policy.
- The ledger stores both gross and net values so accounting is auditable.

Recommended initial design target:

- Use a **small single-digit percentage** as the default marketplace commission.
- Keep the exact launch value configurable until economy testing determines the right balance.
- A provisional example for testing could be **5% Metaworld / 95% creator**, but this is not yet a locked final rate.

Example with a 5% test fee:

Sale price: 100 GrimKoin
- Creator receives: 95 GrimKoin
- Metaworld receives: 5 GrimKoin

The same architecture can later support limited promotions such as temporary reduced fees, new-creator incentives, featured marketplace events, or category-specific policies, but ordinary sales should always default back to a Metaworld commission.

The purpose of the fee is to create a sustainable platform revenue stream tied directly to marketplace activity without taking so much that creators lose the incentive to build successful businesses.

---

# 8. Ownership & Entitlements

Buying a creator texture creates an entitlement, not a loose local file assumption.

Entitlement record can include:

- Buyer Player ID
- Product ID
- Creator ID
- Compatible Base Asset ID
- UV compatibility version
- Purchase timestamp
- License/permission flags
- Transferability
- Resale status if supported
- Gift status if supported
- Update entitlement
- Revocation state only for exceptional policy/security cases

When a player equips, rezzes, places, or uses an item, Metaworld resolves:

Owned Base Asset + Owned Creator Texture Entitlement -> Rendered Item Variant

This prevents duplication exploits and keeps ownership tied to the world economy.

---

# 9. Creator Permissions

Texture products can later support permission models inspired by virtual-world creator economies, but the rules should remain simple and explicit.

Possible flags:

- Personal Use
- Giftable
- Transferable
- Resellable
- Derivative texture creation allowed/not allowed
- Commercial display/use in a player business allowed

Permissions must be understandable in the UI.

A buyer receiving a texture entitlement does not receive the right to alter the underlying Metaworld mesh, UV layout, material slots, or master materials.

---

# 10. Content Safety, Copyright & Moderation

Metaworld should protect creators and the platform from abuse.

Creator texture uploads need:

- File validation
- Resolution/size limits
- Safe asset processing
- Allowed texture format validation
- Duplicate/hash checks where useful
- Moderation/reporting
- Copyright/trademark complaint process
- Prohibited-content rules
- Audit records for uploads, approvals, takedowns, purchases, and creator identity

Creators should only upload textures they have the right to use and sell.

---

# 11. Performance Budget

User-created textures must not be allowed to destroy client performance.

Each product is validated against rules such as:

- Maximum texture resolution by category
- Maximum total texture memory budget
- Allowed texture formats
- Allowed texture channels per asset
- Streaming settings
- Mip generation
- Compression settings
- Locked material-slot count inherited from the base mesh

Creator uploads cannot increase the number of material slots or introduce new shader complexity.

High-quality creator content is encouraged, but it must fit the same scalability philosophy as the rest of Metaworld.

---

# 12. Creator Workflow

Recommended first-version workflow:

1. Creator chooses an approved Metaworld base asset.
2. Creator downloads/opens the official UV/texture template.
3. Creator makes compatible texture maps in Blender, Substance Painter, Photoshop, GIMP, Krita, or another supported tool.
4. Creator previews the textures on the locked Metaworld mesh/material setup in the creator preview tool/test scene.
5. Creator uploads the texture package only.
6. Automated validation checks base-asset compatibility, UV version, texture channels, resolution, file size, metadata, and performance constraints.
7. Moderation/policy checks run where needed.
8. Creator sets shop listing, price, currency, preview, and permissions and sees the current marketplace commission before publishing.
9. Product becomes available in the creator's shop/marketplace.
10. Buyer purchases the product.
11. Transaction service atomically splits creator proceeds and the Metaworld commission.
12. Metaworld grants the buyer a texture entitlement.
13. Buyer applies the texture product to a compatible owned item.

At no point does the creator edit the mesh's material slots.

---

# 13. Creator Texture Categories

The texture marketplace can support many asset categories while preserving the same locked-mesh/locked-material rule:

- Clothing textures
- Furniture textures
- Vehicle liveries/textures
- Weapon textures/skins
- Building surface textures where supported by approved base assets
- Wall/floor texture sets
- Signs/posters using approved texture surfaces
- Tattoos
- Makeup
- Hair textures where supported
- Decals where supported
- Business branding textures
- Interior design texture packages

All categories remain texture-only unless Metaworld explicitly introduces a different creator program in the future.

---

# 14. Core Principle

Metaworld owns and controls the physical and material structure of the asset.

Creators control only the approved texture appearance.

Creators build businesses and keep the majority of each sale. Metaworld earns a small commission from each marketplace transaction so the creator economy also contributes directly to operating and growing the world.

The same chair mesh and the same locked material slots can support thousands of player-created texture products without duplicating the mesh or allowing creators to alter its technical construction.

That is the target: a player-created economy where the world remains technically controlled, optimized, secure, financially sustainable, and visually shaped by its community.
