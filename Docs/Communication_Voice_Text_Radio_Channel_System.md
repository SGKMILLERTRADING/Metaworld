# Metaworld — Communication, Voice, Text & Radio Channel System

**Status:** Canonical Gap-Closure Architecture

## Purpose

Metaworld needs scalable player/NPC communication that respects proximity, rooms, vehicles, organizations, radio systems, privacy, moderation and network relevance.

## Communication Modes

The shared communication architecture can support:

- proximity voice;
- proximity/local text;
- direct messages;
- household/property channels;
- vehicle occupant channels;
- organization/team channels;
- radio channels;
- phone-style calls/messages later;
- service/emergency channels;
- public announcements/news where appropriate.

## Channel Identity

Use stable channel/session records where persistence is needed:

- CommunicationChannelID;
- ChannelType;
- owner/organization/property reference;
- membership/access policy;
- moderation policy;
- lifetime/persistence policy.

Temporary proximity voice does not require durable message history.

## Voice Direction

UE's Voice Chat Interface is the preferred abstraction layer to evaluate because it can operate across supported providers/platforms.

Voice provider choice remains replaceable behind Metaworld channel policy.

## Relevancy Rule

Do not send every player's communication to every client.

Examples:

- proximity voice -> nearby eligible listeners;
- vehicle voice -> occupants;
- room/property voice -> eligible occupants;
- organization/radio -> authorized channel members;
- direct call -> participants.

## Spatial Voice

Proximity voice uses spatial attenuation and world relevance where supported.

Walls/rooms/property acoustics may later influence presentation, but authorization/relevance is decided separately from audio effects.

## Text

Text messages are authoritative communication events where persistence/moderation requires it.

Possible metadata:

- sender CharacterID/Account moderation reference;
- ChannelID;
- timestamp;
- content;
- delivery/read status where relevant;
- moderation/report references.

## Radio / Device Integration

A radio/phone may be a persistent ItemInstance or installed vehicle/property device.

Having a device does not automatically grant access to every channel. Channel credentials/organization permission still apply.

## NPC Communication

NPC dialogue, radio calls and service messages use the same high-level channel concepts when appropriate, but AI-generated text/voice is presentation. World-state actions still go through authoritative gameplay systems.

## Blocking / Muting

Account-level communication controls can include:

- mute voice;
- mute text;
- block user;
- report communication;
- parental/platform privilege restrictions later.

Blocking communication does not erase the other Character from the world or change gameplay authority.

## Performance

- proximity queries are spatial/relevance-based;
- voice streams are limited to eligible listeners;
- text history is paged/limited;
- inactive channels do not run per-frame work;
- media/video streams are not ordinary gameplay replication payloads.

## Acceptance Gate

Prove:

- two clients use proximity text/voice policy;
- distance/relevance removes listener correctly;
- vehicle/room channel isolates participants;
- organization channel checks membership;
- mute/block affects presentation only;
- reconnect restores persistent channel membership where configured;
- network traffic remains bounded with many nearby channels.

## Core Principle

> Communication is routed by who should hear/see it, not broadcast to the entire Metaworld.