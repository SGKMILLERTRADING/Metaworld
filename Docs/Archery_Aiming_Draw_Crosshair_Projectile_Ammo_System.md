# Metaworld — Archery Aiming, Draw, Crosshair, Projectile & Ammo System

**Status:** Canonical / Approved Modern RPG Playlist Upgrade
**Engine:** Unreal Engine 5.8
**Runtime:** Blueprint-first / server-authoritative / ItemInstance-aware / controller-complete / event-driven

## Canonical Principle
Archery is one ranged-combat handling profile built on the existing Bow, Quiver, Equipment, Combat, Status, Movement and Item systems. Aim/draw/crosshair are presentation and intent; the authoritative shot consumes real ammunition and resolves one projectile/result through the shared ranged pipeline.

## 1. Archery State
Suggested action states:
- Bow Ready;
- Aiming;
- Drawing;
- Fully Drawn;
- Releasing/Firing;
- Recovering;
- No Ammo / invalid state.

These are derived from a valid Combat/Ability action and equipped Bow ItemInstance, not a collection of loose widget booleans.

## 2. Bow Locomotion / Aim
Bow handling profile may supply:
- bow-specific locomotion/strafe presentation;
- aim-offset profile;
- draw/release montages;
- movement limitations while aiming;
- camera profile;
- draw-time profile;
- compatible ammo tags.

Movement speed remains owned by the Character Movement Resolver. Tutorial speed caps are tuning only.

## 3. Aim Camera
Aiming may locally adjust:
- camera distance/FOV;
- shoulder/socket offset;
- reticle visibility;
- rotation response.

Camera transitions are local presentation and cannot make an invalid target/hit authoritative.

Canceling aim restores the correct camera profile through state transition rather than an unrelated hardcoded reset.

## 4. Draw Progress
Recommended record/context:
- DrawStartedAt;
- RequiredDrawDuration from current Bow/Attack profile;
- current draw fraction;
- FullyDrawn state;
- selected ammo preference.

AttackSpeed or archery stats may modify draw duration within legal profile bounds.

Crosshair/HUD can derive draw percentage from timestamps/state. A client reaching 100% visually does not authorize a shot early.

## 5. Crosshair
Crosshair may present:
- draw/charge contraction;
- fully-drawn readiness cue;
- selected ammo type/count;
- unavailable/no-ammo state;
- aim spread/accuracy profile where later designed.

Do not run a permanent 0.01-second timer when the bow is not being aimed. Visible draw presentation may update locally while active and stops immediately on cancel/fire/state exit.

## 6. Fire Request
`RequestReleaseBow(TargetContext)`
-> valid Bow ItemInstance equipped?
-> valid aim/draw state?
-> resolve current accessible compatible ammunition
-> server validates character/action state
-> reserve/consume one ammunition unit according to shot policy
-> construct shot/projectile state
-> launch/resolve projectile
-> persist ammo delta
-> emit presentation/result state.

Client animation or crosshair cannot create infinite ammunition.

## 7. Aiming Geometry
A common third-person solution is accepted:
- camera/view trace resolves desired aim point;
- projectile origin remains the actual bow/arrow origin;
- launch direction is derived from origin toward the valid aim point;
- near-obstacle handling prevents extreme convergence angles;
- server checks plausible direction/obstruction.

Tutorial distances/offsets are tuning only.

The crosshair does not let the projectile pass through an obstacle close to the bow simply because the camera can see past it.

## 8. Projectile
A fired arrow can use a lightweight projectile Actor with Projectile Movement / gravity/trajectory profile.

The projectile retains compact provenance such as:
- shot/CombatAction ID;
- Bow ItemInstanceID;
- ammo definition/stack provenance;
- source character;
- damage/effect profile;
- authoritative spawn/launch state.

Not every in-flight arrow needs full persistent ItemInstance Actor state.

## 9. Collision / Fast Projectiles
Use an appropriate projectile collision strategy, including swept movement and/or CCD where profiling/physics mode requires it. A stretched collision box alone is not the canonical anti-tunneling solution.

Collision channels are broad filters; target legality and result still use the canonical Combat resolver.

## 10. Impact / Sticking
On valid impact:
- resolve semantic body zone/world surface;
- commit the combat/world result;
- stop/deactivate flight presentation;
- optionally attach a visual arrow to the hit component/bone/surface;
- decide whether arrow breaks, despawns, or becomes recoverable according to ammo definition.

Stuck visual arrow is presentation unless/until a legitimate recoverable ItemInstance/world item is created.

## 11. Weak-Point / Body-Zone Result
Semantic body-zone mapping can influence result profile where designed. Tutorial raw skeleton-bone checks are authoring/prototype shortcuts; canonical mapping uses the anatomy/body-zone profile so different character skeletons remain compatible.

Weak-point/head results remain distinct from random Critical state and use explicit result ordering.

## 12. Trail / Blood / Hit Audio
Projectile trail, impact VFX, blood, and hit audio are driven by the committed result/presentation profile. They deactivate/cleanup on impact or lifetime end and do not authorize the result.

## 13. Arrow Lifetime / Recoverability
Tutorial fixed `Destroy after 10 seconds` is presentation/performance tuning only.

Definition/profile can choose:
- break on impact;
- temporary visual only;
- recoverable arrow world item;
- persistent special projectile where needed.

Cleanup of a visual projectile cannot refund ammunition automatically.

## 14. Quiver / Ammo Count
The existing quiver remains a specialized real ContainerID. HUD count is an aggregate of accessible compatible ammunition, not a duplicate map that becomes inventory authority.

Maintain cached ammo aggregates from Container deltas where useful.

Selected/current arrow is an ammo preference such as `Ammo.Arrow.Poison`, not one arbitrary stack reference unless a specific exact stack is intentionally selected.

## 15. Auto-Fallback Ammo
If selected ammo reaches zero, policy may:
- choose next compatible ammo type according to player/profile ordering;
- leave selection empty and require manual choice;
- use a configured fallback.

The server/container resolver validates actual availability.

## 16. No Ammo
With no compatible ammunition:
- ordinary arrow shot cannot commit;
- HUD shows zero/unavailable state;
- aim policy may either allow dry aiming or reject entering aim according to design;
- no hidden free arrow is spawned.

## 17. Action Continuity / Input Buffer
After a shot, the action coordinator decides whether to:
- return to Aim/Draw if input remains held and ammo exists;
- exit aim;
- execute a buffered Dodge/other legal action;
- respect Stun/interrupt/state restrictions.

Releasing aim during the firing commitment cannot arbitrarily rotate/cancel the shot unless the action profile permits it.

## 18. Controller Compatibility
Aiming, draw/release, ammo selection and quickslot preference must support KBM, Xbox-style and PlayStation-style mappings through Enhanced Input rather than hardcoded mouse buttons.

## 19. Performance
- crosshair updates only while visible/active;
- no full inventory scan every frame for arrow count;
- projectile Actors exist only while needed;
- trail/VFX deactivate on impact/relevance;
- stuck visuals/lifetime are capped/significance-aware;
- distant projectile presentation can scale without changing authoritative result.

## Acceptance Tests
1. Bow aim uses handling/movement profile without overwriting movement authority.
2. Crosshair draw percent follows current draw state/timestamp.
3. Client cannot fire before authoritative/legal draw state.
4. Shot consumes one real compatible ammo unit.
5. No ammo means no normal shot.
6. Camera aim cannot make arrow pass through a near obstacle illegally.
7. Fast projectile uses robust swept/collision policy.
8. Body-zone result uses semantic anatomy mapping.
9. Stuck visual cannot duplicate recoverable ammo.
10. Quiver count derives from real container quantities.
11. Selected ammo auto-fallback follows configured policy.
12. Cancel/fire/buffer transitions cleanly reconcile camera/crosshair/action state.
13. KBM/Xbox-style/PlayStation-style controls use the same gameplay requests.

## Core Rule
Metaworld archery combines local responsive aiming presentation with authoritative ranged transactions. The bow remains an exact ItemInstance, the quiver remains a real container, every committed shot consumes real ammo, and projectile/contact results use the same Combat, Status and persistence rules as the rest of the world.