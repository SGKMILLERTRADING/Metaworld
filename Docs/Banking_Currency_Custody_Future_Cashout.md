# Metaworld — Banking, GrimKoin Custody & Future Cashout Boundary

## Canonical Banking Rule

GrimKoin can exist in two distinct states:

1. **Carried GrimKoin** — available to the player for immediate in-world spending.
2. **Banked GrimKoin** — stored in a bank account and unavailable for ordinary purchases until the player withdraws it.

A player can deliberately carry little or no GrimKoin while keeping wealth in the bank.

Core rule:

> Banked GrimKoin cannot be spent from the ordinary wallet. It must be withdrawn first.

This makes banking meaningful for safety, privacy, travel, robbery risk, spending behavior, economic reputation, and death/estate planning.

---

# 1. Wallet vs Bank Account

## Player Wallet

Tracks immediately spendable currency carried by the character.

Possible fields:

- Carried GrimKoin
- Carried PromoKoin
- Currency transaction history reference
- Last withdrawal/deposit reference

The wallet is what ordinary shops, vendors, tips, bars, tickets, and direct player transactions can use unless a later payment mechanism explicitly says otherwise.

## Bank Account

Tracks deposited GrimKoin separately from the player wallet.

Possible fields:

- Account ID
- Owner Player ID
- Bank/branch ID
- Banked GrimKoin balance
- Frozen/held amount if future legal/gameplay systems require it
- Deposit history
- Withdrawal history
- Transfer history if bank transfers are added later
- Security/audit flags

The bank balance is server-authoritative and must never be stored only on the client.

---

# 2. Deposit and Withdrawal Flow

Deposit:

Carried GrimKoin
-> Player chooses amount
-> Bank transaction validates ownership/balance
-> Wallet decreases
-> Bank balance increases
-> Ledger transaction commits atomically

Withdrawal:

Banked GrimKoin
-> Player chooses amount
-> Bank transaction validates account/balance
-> Bank balance decreases
-> Wallet increases
-> Ledger transaction commits atomically

A failed transaction must not subtract from one side without crediting the other.

---

# 3. Absolute Bank Privacy From Killers and Robbers

A killer, burglar, robber, raider, hostile NPC, faction, or ordinary player never gains access to another player's bank account merely because they attacked, killed, robbed, kidnapped, defeated, or looted that character.

Canonical rule:

> Robbery is limited to property the robber can physically reach in the world. Bank-account balances are not physical loot.

A robber may potentially take, according to normal world/loot rules:

- GrimKoin physically carried by the victim
- Items physically carried by the victim
- Items inside a breached house
- Items inside a breached shop, warehouse, vehicle, container, safe, or other physical storage
- Physical cash/reserves belonging to a bank institution if an actual bank robbery system permits it

A robber may **not**:

- Read another player's private bank balance
- Withdraw another player's banked GrimKoin
- Transfer another player's banked GrimKoin
- Receive banked GrimKoin because they killed the account holder
- Rewrite the authoritative account ledger
- Use possession of the corpse, house, phone, wallet, key, or vehicle as automatic bank authorization

Even if a physical bank branch is successfully attacked, customer account balances remain authoritative server records. A bank robbery can target the bank's physical reserves, vault contents, transport, or other bank-owned physical assets without rewriting customer deposits.

---

# 4. Why Banking Matters in Gameplay

A wealthy player can keep most GrimKoin banked and carry only what is needed for the current outing.

This can reduce:

- Loss exposure during ordinary robbery
- Visible high-roller spending patterns
- Temptation to make impulsive expensive purchases

It also creates choices:

- Withdraw before a large purchase
- Travel to a bank/ATM/service point
- Decide how much cash to carry into dangerous regions
- Keep emergency reserves in the bank
- Hide true wealth from casual observers

A player's bank balance should not automatically be visible to ordinary NPCs or other players.

Economic reputation should primarily react to observable behavior such as purchases, property, vehicles, businesses, tips, public transactions, clothing, and known records.

Banking is much safer than carrying GrimKoin, but permanent character death still has a separate bank-side financial consequence.

---

# 5. Banks Are Part of the Living World

Banks can exist as real Metaworld institutions with physical branches, employees, security, vaults, ATMs, and operating schedules.

Possible roles later:

- Bank teller
- Bank manager
- Security guard
- Armored transport driver
- Accountant/auditor
- Investigator
- Estate officer

The authoritative account ledger remains protected by server rules even when a bank building is attacked.

---

# 6. Bank Access

Initial access methods can include:

- Bank teller
- ATM
- Bank terminal

Possible later features:

- Bank-to-bank transfers
- Business accounts
- Joint accounts
- Payroll accounts
- Automatic tax remittance
- Escrow
- Loans/mortgages
- Insurance
- Safe-deposit storage
- Estate/inheritance claims

These are future systems and should not be enabled until the base custody/ledger model is stable.

---

# 7. GrimKoin Gifts Are Transfers, Never Minting

A player may gift GrimKoin only if the player already legitimately owns that GrimKoin.

Valid underlying sources are:

- GrimKoin legitimately earned through jobs, wages, tips, business activity, creator sales, contracts, trading, or other approved gameplay; or
- GrimKoin purchased from the official Metaworld VIP Store.

A gift does not create currency.

Gift transaction:

Existing sender-owned GrimKoin
-> Validate available sender balance
-> Debit sender
-> Credit receiver
-> Commit one authoritative ledger transaction

There is no system-generated "gift balance" and no gift function that can create new GrimKoin.

If direct bank-to-bank gifting or transfer is added later, it follows the same rule: the sender already owns the funds and the transaction only moves existing GrimKoin.

---

# 8. Permanent Death and Banked GrimKoin

Banked GrimKoin is protected from killers, robbers, corpse looting, house raids, and physical theft from the player's property.

Permanent character death, however, triggers a **bank-side death/estate settlement**.

Canonical rule:

> On permanent character death, the bank may keep up to 50% of the deceased character's banked GrimKoin as a death/estate settlement charge before any surviving balance enters inheritance or legacy processing.

The exact percentage can be configured for balancing but cannot exceed 50% under this rule.

Example:

Banked before death: 20,000 GrimKoin

Possible settlement:
- Bank keeps: 8,000
- Surviving estate balance: 12,000

Maximum settlement:
- Bank keeps: 10,000
- Surviving estate balance: 10,000

The bank-kept amount becomes bank/institution revenue under the economic system. It is **not** paid to the killer and is **not** lootable from the corpse or property.

This gives banks a major revenue source and makes death financially painful even for wealthy players who bank carefully.

The surviving balance enters the estate/inheritance process. It does not automatically appear in the new character's wallet.

Carried GrimKoin follows separate physical loot/death rules because it is actually on the character.

---

# 9. Server-Authoritative Currency Ledger

Every currency-changing operation creates an immutable or append-only transaction record.

Recommended fields:

- Transaction ID
- Timestamp
- Player/account IDs
- Character ID where relevant
- Currency type
- Amount
- Source
- Destination
- Transaction category
- Provenance classification
- City tax amount where applicable
- Metaworld commission where applicable
- VIP Store issuance reference where applicable
- Gift sender/receiver reference where applicable
- Death/estate bank-settlement reference where applicable
- Related product/property/job/business ID
- Balance-before / balance-after references
- Fraud/security flags
- Reversal/correction reference when needed

No client should be able to directly set a wallet or bank balance.

---

# 10. Future Real-Cash GrimKoin Buyback — NOT ACTIVE NOW

Future concept:

Metaworld may eventually allow eligible players to sell/redeem earned or otherwise eligible GrimKoin back to Metaworld for real-world money.

This is **not part of the current implementation phase**.

Until that future system is deliberately activated:

- GrimKoin remains an in-game currency.
- There is no guaranteed cash value.
- There is no automatic redemption right.
- No payout API or cash withdrawal mechanism should be implemented.

The internal ledger should still preserve provenance so legitimate currency history can be reconstructed later.

---

# 11. Future Compliance Boundary

If GrimKoin later becomes redeemable for real money, Metaworld crosses into a materially different legal/compliance area.

Before enabling cash redemption, Metaworld must obtain jurisdiction-specific legal, tax, payment, AML/KYC, consumer-protection, platform/store, and payout-provider review.

Current architecture boundary:

In-Game Economy Today
-> Server-authoritative ledger
-> VIP Store may issue GrimKoin under approved purchase rules
-> No player cash redemption

Future Cashout Program
-> Separate eligibility/compliance layer
-> Identity and fraud checks
-> Approved payout rails
-> Legal/tax controls
-> Then redemption

---

# 12. Core Principle

A player's wallet is spending money.

A player's bank account is private stored wealth.

Robbers can steal physically reachable property; they cannot access another player's bank account.

Gifting only moves existing sender-owned GrimKoin.

Permanent death can cause the bank itself to keep up to half of banked GrimKoin before the remaining estate is processed.

Metaworld should build trustworthy banking and transaction records now while leaving real-money GrimKoin redemption disabled until a later dedicated, legally reviewed phase.
