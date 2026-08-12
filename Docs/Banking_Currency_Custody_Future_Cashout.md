# Metaworld — Banking, GrimKoin Custody & Future Cashout Boundary

## Canonical Banking Rule

GrimKoin can exist in two distinct states:

1. **Carried GrimKoin** — available to the player for immediate in-world spending.
2. **Banked GrimKoin** — stored in a bank account and unavailable for ordinary purchases until the player withdraws it.

A player can therefore deliberately carry little or no GrimKoin while keeping wealth in the bank.

Core rule:

> Banked GrimKoin cannot be spent from the ordinary wallet. It must be withdrawn first.

This makes banking meaningful for safety, privacy, travel, robbery risk, spending behavior, and economic reputation.

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

A failed transaction must not be able to subtract from one side without crediting the other.

---

# 3. Why Banking Matters in Gameplay

Banking changes risk and social visibility.

A wealthy player can keep most GrimKoin banked and carry only what is needed for the current outing.

This can reduce:

- Loss exposure during robbery/death systems
- Visible high-roller spending patterns
- Temptation to make impulsive expensive purchases

It can also create gameplay choices:

- Withdraw before a large purchase
- Travel to a bank/ATM/service point
- Decide how much cash to carry into dangerous regions
- Keep emergency reserves in the bank
- Hide true wealth from casual observers

A player's bank balance should not automatically be visible to ordinary NPCs or other players.

Economic reputation should primarily react to observable behavior such as purchases, property, vehicles, businesses, tips, public transactions, clothing, and known records.

---

# 4. Banks Are Part of the Living World

Banks can exist as real Metaworld institutions with physical branches, employees, security, vaults, ATMs, and operating schedules.

Possible roles later:

- Bank teller
- Bank manager
- Security guard
- Armored transport driver
- Accountant/auditor
- Investigator

The exact relationship between physical bank robbery and account balances must be designed carefully. Physical theft can target cash reserves, vault inventory, transport, or other bank-owned assets without automatically allowing attackers to rewrite server account balances.

The authoritative account ledger should remain protected by server rules even when a bank building is attacked.

---

# 5. Bank Access

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

These are future systems and should not be enabled until the base custody/ledger model is stable.

---

# 6. Server-Authoritative Currency Ledger

Every currency-changing operation should create an immutable or append-only transaction record.

Recommended fields:

- Transaction ID
- Timestamp
- Player/account IDs
- Currency type
- Amount
- Source
- Destination
- Transaction category
- City tax amount where applicable
- Metaworld commission where applicable
- Related product/property/job/business ID
- Balance-before / balance-after references
- Fraud/security flags
- Reversal/correction reference when needed

No client should be able to directly set a wallet or bank balance.

---

# 7. Future Real-Cash GrimKoin Buyback — NOT ACTIVE NOW

Future concept:

Metaworld may eventually allow eligible players to sell/redeem earned GrimKoin back to Metaworld for real-world money.

This is **not part of the current implementation phase**.

Until that future system is deliberately activated:

- GrimKoin remains an in-game currency.
- There is no guaranteed cash value.
- There is no automatic redemption right.
- No payout API or cash withdrawal mechanism should be implemented.

However, the internal ledger should be designed now so legitimate provenance can be reconstructed later if cash redemption is introduced.

Future payout preparation hooks can include:

- Account identity status
- Transaction provenance
- Anti-duplication/fraud history
- Earned-vs-purchased classification if needed
- Suspicious transaction flags
- Payout eligibility state
- Payout limits
- Tax/reporting metadata hooks
- Jurisdiction/account region

---

# 8. Future Compliance Boundary

If GrimKoin later becomes redeemable for real money, Metaworld crosses from a closed game economy into a materially different legal/compliance area.

Before enabling cash redemption, Metaworld must obtain jurisdiction-specific legal, tax, payment, AML/KYC, consumer-protection, platform/store, and payout-provider review.

The technical architecture should therefore keep a hard boundary:

In-Game Economy Today
-> Server-authoritative ledger
-> No cash redemption

Future Cashout Program
-> Separate eligibility/compliance layer
-> Identity and fraud checks
-> Approved payout rails
-> Legal/tax controls
-> Then redemption

Do not retrofit these controls after cashout launches.

---

# 9. Core Principle

A player's wallet is spending money.

A player's bank account is stored wealth.

Banked GrimKoin is not ordinary spendable wallet currency until the player withdraws it.

Metaworld should build trustworthy banking and transaction records now while leaving real-money GrimKoin redemption disabled until a later dedicated, legally reviewed phase.
