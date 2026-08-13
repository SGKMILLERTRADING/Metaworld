# Metaworld — AI Media Ownership, Sales & Spatial Playback

**Status:** Canonical / Approved

## Canonical Rule

Player-sold music and video in Metaworld is restricted to **AI-generated media that the selling player owns and is permitted to sell**.

This system is not intended for players to upload and sell ordinary third-party songs, movies, TV programs, YouTube videos, commercial music, copyrighted films, or other media they do not own.

Core rules:

> Player marketplace music/video must be AI-generated and owned by the player who publishes it.

> Buying media gives that buyer their own Metaworld-owned copy/entitlement for playback.

> Shared listening/viewing in the same physical location does not transfer ownership.

---

# 1. AI-Generated-Only Marketplace Rule

Sellable player media categories include AI-generated:

- Songs
- Instrumentals
- Albums/collections
- Music videos
- Short films
- Movies
- Series/episodes if later supported
- Advertisements/commercials
- Documentaries
- Entertainment videos
- Other approved AI-generated audio/video categories

The player publishing the media must own the output and have the right to sell/distribute it under the terms of the AI tool/service used to create it.

The uploader must make a rights/ownership declaration before publication.

Metaworld can retain:

- Media Asset ID
- Creator Account/Character ID
- AI-generated classification
- Ownership declaration
- Creation/source metadata where required
- Upload timestamp
- Moderation status
- Sale price
- Currency
- Copy/entitlement count
- Transaction history
- Takedown/dispute status

---

# 2. Creator Owns the Original

The player creator owns the original sellable Metaworld media product they publish, subject to Metaworld platform rules and the rights they actually hold.

A normal sale does not automatically transfer the creator's original publishing rights to one buyer.

Instead, each normal sale creates a separate buyer-owned Metaworld media copy/entitlement.

Example:

Creator owns `Song_A`.

Player B buys `Song_A`.

- Creator still owns/publishes the original product.
- Player B now owns one personal Metaworld copy/entitlement.

Player C later wants their own copy.

- Player C must buy `Song_A` separately.

Player B's purchase does not make the file globally owned by everyone.

---

# 3. Buyer-Owned Media Copy / Entitlement

A buyer-owned media entitlement should track at minimum:

- Entitlement ID
- Media Asset ID
- Buyer Account/Character ID
- Creator ID
- Purchase Transaction ID
- Purchase timestamp
- Currency/price
- Playback permissions
- Resale/transfer rule if later supported
- Revocation/takedown state only for legitimate platform/legal reasons

The buyer can use their owned copy on compatible Metaworld media devices they have permission to control.

Examples:

Music can play through:

- Radio
- Car radio/media player
- Home stereo
- Club/bar sound system where owner/operator permits
- Jukebox where supported
- Other approved audio devices

Video can play through:

- Television
- Home theater screen
- Club/bar screen
- Cinema/drive-in screen where venue rights permit
- Other approved video devices

---

# 4. Same-Location Shared Playback

Ownership and physical playback are separate.

If a player owns a song and plays it in their house:

- The owner is using their copy.
- Other players physically inside the active media zone can hear it.
- Those listeners do not gain a copy.
- Leaving the media zone ends that shared listening unless another legitimate source is playing it.

If a player owns a video and plays it on their TV:

- People in the same room/viewing zone can watch it.
- Those viewers do not own the video merely because they watched it.
- If they want to play it later on their own TV, they must buy their own copy.

Core rule:

> One owned copy can entertain many people who are physically present at the same playback location, but presence is not ownership.

---

# 5. Vehicle, Room, Property & Venue Scope

Media playback should use Metaworld's spatial Media Session system.

Possible scopes:

- Vehicle occupants
- One room
- House/property media zone
- Bar/club zone
- Cinema/drive-in screening zone
- Business/event zone

A Media Session can track:

- Session ID
- Host/controller
- Owned Media Entitlement ID
- Media Asset ID
- Playback state
- Playback timestamp
- Volume
- Spatial zone
- Eligible listeners/viewers
- Device ID

The server validates that the host/device has permission to use the relevant media entitlement before playback begins.

---

# 6. No Ownership Through Hearing or Watching

The following do **not** grant ownership:

- Hearing a song in somebody else's car
- Hearing music at a club
- Watching a movie at a friend's house
- Watching a video at a bar
- Attending a cinema/drive-in screening
- Being present at a party
- Seeing/hearing media through an authorized shared session

To obtain a personal copy, the player must purchase or otherwise legitimately receive an entitlement through an approved Metaworld ownership-transfer system.

---

# 7. Venue Playback and Tickets

A venue can use media owned/licensed by its operator according to Metaworld rules.

Example:

Venue owner owns an AI-generated movie copy with venue playback permission.

They schedule a screening.

Players can buy admission/tickets.

Attendees are allowed to watch during the event because they are physically present in the authorized venue zone.

The ticket does not give each attendee permanent ownership of the movie.

If an attendee wants their own permanent copy afterward, they must purchase that media product separately if it is for sale.

The same principle can apply to clubs, concerts, DJ events, bars, radio programming, and other venue playback systems.

---

# 8. Radio and Broadcast Distinction

Personal/location playback is different from citywide or world broadcast.

Normal owned-copy playback can be scoped to a room, property, vehicle, venue, or other defined local session.

If Metaworld later allows true radio-station broadcasting or large-area media broadcasting, that should use a separate broadcast permission/business system rather than treating one personal copy as unlimited global broadcast rights.

---

# 9. Gifting and Transfers

If media gifting is enabled later, gifting must transfer an existing legitimate entitlement or purchase a new entitlement for the recipient according to the configured marketplace rule.

The gift system must not duplicate unlimited free copies.

Possible models later:

- Buy as gift -> recipient receives new entitlement
- Transfer owned copy -> sender loses that copy and recipient gains it

The exact model can be configured later, but ownership records must remain authoritative.

---

# 10. News Is Separate

Official Metaworld News is not governed by player entertainment-media ownership in the same way.

Official news comes from Metaworld's verified Event Ledger/news system.

Player AI-generated music/video is creator marketplace content.

Keep separate classifications for:

- Official Metaworld News
- Player AI-generated music
- Player AI-generated video/film
- Player journalism if later supported
- Advertising
- Public-service/emergency broadcasts

---

# 11. Performance Rule

Owning a media file/entitlement does not mean every device continuously decodes it.

Playback only runs when relevant.

Use:

- spatial relevancy
- visibility
- authorized participants
- paused/static representation when not viewed
- limited simultaneous video decoders
- local client playback where appropriate
- server synchronization of entitlement and playback state rather than relaying full media through ordinary gameplay replication

This protects Metaworld's smoothness target.

---

# 12. Canonical Example

Player A creates an AI-generated song and owns the output.

Player A publishes it in the Metaworld marketplace for 100 GrimKoin.

Player B buys it.

Player B now owns a personal Metaworld copy/entitlement.

Player B drives three friends in a car and plays the song.

All four occupants hear the song because they are inside the same vehicle Media Session.

The three friends do not own the song.

Later Player C goes home and wants to play it on their own radio.

Player C must buy their own copy.

The same rule applies to video:

Player B owns a movie -> plays it on the home TV -> everyone in the room can watch -> only Player B owns that copy -> others must buy their own copy if they want independent playback later.

---

# 13. Supersession Rule

This document supersedes any older Metaworld wording that broadly allowed player-sold music/video merely because a player had generic distribution rights.

The approved rule is now narrower:

> Sellable player music and video is AI-generated-only, must be owned by the seller, and uses per-buyer Metaworld ownership entitlements with shared spatial playback but no automatic ownership transfer to listeners/viewers.
