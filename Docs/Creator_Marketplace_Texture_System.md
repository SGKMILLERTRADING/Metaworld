# Metaworld — Creator Marketplace & Texture Derivative System

## Canonical Creator Economy Rule

Metaworld provides the approved base meshes and technical asset foundations. Players/creators can create compatible textures, material variants, decals, colorways, surface treatments, and other approved visual derivatives for those meshes, publish them in player-owned shops, and sell them to other players.

The creator should not need to duplicate or redistribute the underlying base mesh in order to sell a texture product.

This allows a Second Life / IMVU-style creator economy while keeping geometry, rigging, collision, sockets, LOD/Nanite setup, physics, gameplay metadata, and performance standards under Metaworld control.

---

# 1. Base Mesh + Creator Skin Architecture

Each supported asset should have a stable Metaworld Asset ID.

Example:

Base Asset:
- Asset ID: `MW_CHAIR_001`
- Type: Furniture
- Mesh: Metaworld-managed
- UV Layout Version: 1
- Material Slot Contract: 3 slots
- Gameplay capabilities: Sit, Pickup, Carry, Throw, Break, Place
- Collision/LOD/physics: Metaworld-managed

Creator Product:
- Product ID: creator-specific
- Base Asset ID: `MW_CHAIR_001`
- Creator ID
- Texture/material package
- Compatibility version
- Preview images
- Price
- Currency eligibility
- License/usage rules
- Moderation status

A buyer receives the creator visual package plus a usage entitlement referencing the original base asset. The base mesh remains the canonical Metaworld asset.

---

# 2. Supported Creator Modifications

Initial creator content can support approved visual changes such as:

- Base Color / Albedo
- Normal maps
- Roughness
- Metallic
- Ambient Occlusion where used
- Emissive
- Opacity/masks where the base asset supports it
- Decals
- Pattern overlays
- Color parameters
- Material-instance parameters
- Approved fabric/wood/metal/plastic/leather surface presets

Later systems can optionally support more advanced creator packages, but the first marketplace should focus on safe, predictable texture/material derivatives.

The creator package must not silently change:

- Collision
- Gameplay capabilities
- Weapon statistics
- Storage capacity
- Physics mass
- Rig/skeleton
- Sockets
- Inventory value rules
- Hidden gameplay code

Visual products should remain visual unless a separate approved creator-program system explicitly allows gameplay extensions later.

---

# 3. UV and Template Distribution

For each creator-enabled base mesh, Metaworld should expose a Creator Template containing:

- UV template
- Material slot names
- Texture channel requirements
- Supported resolutions
- Safe naming rules
- Preview/test scene
- Color-space rules
- Compression guidance
- Compatibility version
- Optional Substance/Blender/PSD-style templates where legally and technically appropriate

Creators should be able to design against the template without receiving unrestricted source assets that are unnecessary for texturing.

If a base mesh UV layout changes, Metaworld increments the compatibility version instead of breaking old creator products silently.

---

# 4. Material Instance Strategy

Where practical, Metaworld should use controlled master materials and creator-driven material instances.

Base mesh
-> Metaworld Master Material
-> Creator Material Instance / Texture Set
-> Player-owned product instance

Benefits:

- Better performance consistency
- Easier validation
- Predictable shader complexity
- Easier LOD/Nanite compatibility
- Easier future migration
- Reduced risk of malicious/expensive shaders

Creator uploads should not contain arbitrary executable code or unrestricted shader graphs in the first marketplace version.

---

# 5. Marketplace & Player Shops

Creators should be able to operate stores inside Metaworld.

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

Players can buy a creator texture from a real in-world store, then apply it to an owned compatible item.

---

# 6. GrimKoin / PromoKoin Integration

Creator products participate in the existing Metaworld economy.

Recommended rule:

- Premium/high-value creator goods normally use GrimKoin.
- Low-cost promotional/common creator goods may accept PromoKoin.
- Creators can choose from marketplace-approved pricing/currency policies.
- Metaworld can enforce minimum/maximum or anti-abuse rules if needed.

The marketplace should not create a third unrelated currency unless a later design explicitly requires one.

Every transaction should generate a server-authoritative ledger record containing buyer, seller, product, price, currency, timestamp, and entitlement result.

---

# 7. Ownership & Entitlements

Buying a creator texture should create an entitlement, not a loose local file assumption.

Entitlement record can include:

- Buyer Player ID
- Product ID
- Creator ID
- Compatible Base Asset ID
- Purchase timestamp
- License/permission flags
- Transferability
- Resale status if supported
- Gift status if supported
- Update entitlement
- Revocation state only for exceptional policy/security cases

When a player equips/rezzes/places an item, Metaworld resolves:

Owned Base Asset + Owned Creator Visual Entitlement -> Rendered Item Variant

This prevents duplication exploits and keeps ownership tied to the world economy.

---

# 8. Creator Permissions

Products can later support permission models inspired by virtual-world creator economies, but simplified and made explicit.

Possible flags:

- Personal Use
- Giftable
- Transferable
- Resellable
- Modifiable parameters
- Derivative creation allowed/not allowed
- Commercial use in player business allowed

Permissions must be understandable in the UI. Avoid hidden combinations that confuse buyers or creators.

---

# 9. Content Safety, Copyright & Moderation

Metaworld should protect creators and the platform from obvious abuse.

Creator uploads need:

- File validation
- Resolution/size limits
- Malware-safe asset pipeline
- Texture/material complexity limits
- Duplicate/hash checks where useful
- Moderation/reporting
- Copyright/trademark complaint process
- Adult/age-restricted content policy if Metaworld later supports such categories
- Prohibited-content rules

Creators should only upload content they have the right to use and sell.

The system should keep audit records of uploads, approvals, takedowns, purchases, and creator identity.

---

# 10. Performance Budget

User-created visuals must not be allowed to destroy client performance.

Each product should be validated against rules such as:

- Maximum texture resolution by category
- Maximum total texture memory budget
- Allowed texture formats
- Material instance only where required
- Shader complexity limits
- Number of material slots inherited from base mesh
- Streaming settings
- Mip generation
- LOD/Nanite compatibility

High-quality creator content is encouraged, but it must fit the same scalability philosophy as the rest of Metaworld.

---

# 11. Creator Workflow

Recommended first-version workflow:

1. Creator chooses an approved Metaworld base asset.
2. Creator downloads/opens the creator UV/material template.
3. Creator makes textures/material parameters in Blender, Substance, Photoshop, GIMP, Krita, or another supported tool.
4. Creator previews the work in a Metaworld creator preview tool/test scene.
5. Creator uploads the texture/material package.
6. Automated validation checks compatibility, file limits, metadata, and performance constraints.
7. Moderation/policy checks run where needed.
8. Creator sets shop listing, price, currency, preview, and permissions.
9. Product becomes available in the creator's shop/marketplace.
10. Buyer purchases the product.
11. Metaworld grants the buyer an entitlement.
12. Buyer applies the visual package to a compatible owned item.

---

# 12. Future Expansion

Once the texture marketplace is stable, the creator economy can expand carefully into:

- Clothing textures
- Furniture skins
- Vehicle liveries
- Weapon skins
- Building materials
- Wall/floor textures
- Signs/posters
- Tattoos
- Makeup
- Hair color/material variants
- Decals
- UI-safe business branding
- Interior design packages
- Approved animations/poses later
- Approved sound/media products later
- Approved mesh submissions later only if a separate validation pipeline is created

Metaworld should not open arbitrary mesh uploads on day one. Starting with Metaworld-controlled base meshes plus player-created textures gives creators freedom while protecting compatibility, performance, gameplay fairness, and security.

---

# 13. Core Principle

Metaworld provides the physical object foundation.

Creators provide identity, fashion, branding, style, culture, and endless visual variety.

The same chair mesh can become thousands of player-created products without requiring thousands of duplicated chair meshes.

That is the target: a player-created economy where the world remains technically controlled but visually belongs to its community.
