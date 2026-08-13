# Metaworld — Online Service Integration Architecture

**Status:** Canonical Gap-Closure Architecture
**Engine:** Unreal Engine 5.8

## Purpose

Metaworld needs a provider-agnostic boundary for online login, connectivity, sessions, presence, friends and voice while keeping persistent gameplay records in Metaworld's own data architecture.

## Separation of Concerns

Online/platform services can provide:

- login identity;
- joinable sessions;
- connectivity state;
- presence/friends;
- platform privileges;
- voice-service identity.

Metaworld persistence owns:

- AccountID and CharacterIDs;
- inventory/equipment;
- property/business ownership;
- currency;
- character life/death state;
- missions/world state.

## Provider Boundary

Use Unreal's online-service abstraction where practical so provider choice remains configurable.

Potential implementations include:

- Null/local implementation for development;
- Epic Online Services where appropriate;
- platform services on supported stores/consoles;
- other supported providers later.

Core gameplay does not depend on one provider-specific identifier.

## Identity Mapping

High-level mapping:

`Online Identity -> Metaworld AccountID -> CharacterID`.

Provider identity links remain separate from mortal Character identity.

## Sessions

A session represents a joinable server context, not the persistent-world database.

Useful session metadata can include:

- server/region;
- build/protocol version;
- capacity;
- access policy;
- world/region identifier;
- joinability/status.

## Dedicated Server Flow

1. User enters through the configured online/platform service.
2. Client discovers/receives an appropriate server session.
3. Client connects to the Unreal dedicated server.
4. Metaworld resolves the durable Account/Character state through its persistence layer.
5. The world representation is reconstructed from authoritative records.

## Development Mode

Local development supports a no-paid-service route using local/null online services plus the self-hosted persistence stack.

## Voice

Voice integration remains behind the Communication architecture. Joining one world/server does not mean every player receives every voice stream; channel/relevancy policy still decides listeners.

## Friends / Presence

Platform friends/presence remain separate from in-world trust, household membership, property access, organization membership and reputation.

## Compatibility

Session/server entry must check compatible client/server build and data protocol versions before loading persistent world state.

## Acceptance Gate

Prove:

- local/null development session path;
- two clients join dedicated server;
- online identity maps consistently to AccountID;
- selected CharacterID loads from persistence;
- reconnect resolves the same durable identity;
- changing session/server does not duplicate Character state;
- voice can use provider identity while Metaworld keeps its own Channel rules.

## Core Principle

> Online services connect users to Metaworld; Metaworld's own persistent architecture defines what the world remembers.