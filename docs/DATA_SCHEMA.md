# Game Session Data Schema

Each completed game session is saved as a JSON object. This document explains every field.

---

## Top-Level Fields

| Field | Type | Description |
|-------|------|-------------|
| `date` | string | Date the session was played (`YYYY-MM-DD`) |
| `balance` | object | Player's balance before and after the session |
| `summary` | object | Quick totals for bets, earnings, and losses |
| `insurance` | object | Insurance side bet details |
| `dealer` | object | Dealer's cards and final score |
| `player` | object | All player hands and their outcomes |

---

## `balance`

Tracks how much money the player had before and after the round.

| Field | Type | Description |
|-------|------|-------------|
| `before` | number | Balance at the start of the session |
| `after` | number | Balance at the end of the session |

```json
"balance": { "before": 100, "after": 92 }
```

---

## `summary`

Aggregated totals for the session. Useful for quickly checking profit/loss without scanning every hand.

| Field | Type | Description |
|-------|------|-------------|
| `total_bet` | number | Sum of all bets placed across all hands |
| `total_earn` | number | Total amount won |
| `total_loss` | number | Total amount lost |

```json
"summary": { "total_bet": 100, "total_earn": 50, "total_loss": 58 }
```

> **Net result** = `total_earn` - `total_loss`

---

## `insurance`

Insurance is a side bet available when the dealer's first card is an Ace. It pays 2:1 if the dealer has blackjack.

| Field | Type | Description |
|-------|------|-------------|
| `taken` | boolean | Whether the player bought insurance |
| `bet` | number | Amount bet on insurance (max: half of main bet) |
| `result` | string | `"win"`, `"lose"`, or `"none"` if not taken |

```json
"insurance": { "taken": true, "bet": 50, "result": "win" }
```

---

## `dealer`

The dealer's hand at the end of the round.

| Field | Type | Description |
|-------|------|-------------|
| `cards` | array | List of cards in the dealer's hand (see [Card Object](#card-object)) |
| `score` | number | Dealer's final score |

```json
"dealer": {
  "cards": [
    { "rank": "K", "suit": "Hearts", "value": 10 },
    { "rank": "9", "suit": "Spades", "value": 9 }
  ],
  "score": 19
}
```

---

## `player`

Contains all hands the player played this session (multiple hands occur after a split).

| Field | Type | Description |
|-------|------|-------------|
| `total_hands` | number | How many hands were played (1 normally, more after splits) |
| `hands` | array | List of hand objects (see [Hand Object](#hand-object)) |

---

## Hand Object

Each entry in `player.hands` represents one hand.

| Field | Type | Description |
|-------|------|-------------|
| `hand_index` | number | Hand number, starting at 1 |
| `cards` | array | Cards in this hand (see [Card Object](#card-object)) |
| `score` | number | Final score of this hand |
| `bet` | number | Amount bet on this hand |
| `actions` | array | Sequence of moves taken (see [Actions](#actions)) |
| `double_down` | boolean | Whether the player doubled down on this hand |
| `bust` | boolean | Whether this hand went over 21 |
| `result` | string | `"win"`, `"lose"`, or `"tie"` |

```json
{
  "hand_index": 1,
  "cards": [
    { "rank": "A", "suit": "Clubs", "value": 11 },
    { "rank": "10", "suit": "Diamonds", "value": 10 }
  ],
  "score": 21,
  "bet": 50,
  "actions": ["deal", "blackjack"],
  "double_down": false,
  "bust": false,
  "result": "win"
}
```

---

## Card Object

Used in both `dealer.cards` and `player.hands[].cards`.

| Field | Type | Description |
|-------|------|-------------|
| `rank` | string | `"A"`, `"2"`–`"10"`, `"J"`, `"Q"`, or `"K"` |
| `suit` | string | `"Hearts"`, `"Diamonds"`, `"Clubs"`, or `"Spades"` |
| `value` | number | Numeric value used for scoring (Ace = 11, face cards = 10) |

```json
{ "rank": "A", "suit": "Clubs", "value": 11 }
```

---

## Actions

The `actions` array records every move made on a hand, in order.

| Value | When it appears |
|-------|----------------|
| `"deal"` | Always first — the two initial cards were dealt |
| `"hit"` | Player drew an extra card |
| `"stand"` | Player chose to stop drawing |
| `"double"` | Player doubled the bet and drew one final card |
| `"split"` | Hand was split from another hand |
| `"blackjack"` | Hand is a natural blackjack (Ace + 10-value on deal) |
| `"bust"` | Hand exceeded 21 |

---

## Examples

### Example 1 — Player Blackjack (Player wins with Ace + King on deal)

The player is dealt a natural blackjack (Ace + King). The dealer does not have blackjack, so the player wins 1.5× their bet. No insurance was taken.

```json
{
  "date": "2026-04-16",

  "balance": { "before": 100, "after": 150 },

  "summary": { "total_bet": 100, "total_earn": 150, "total_loss": 0 },

  "insurance": { "taken": false, "bet": 0, "result": "none" },

  "dealer": {
    "cards": [
      { "rank": "9", "suit": "Hearts", "value": 9 },
      { "rank": "7", "suit": "Clubs", "value": 7 }
    ],
    "score": 16
  },

  "player": {
    "total_hands": 1,
    "hands": [
      {
        "hand_index": 1,
        "cards": [
          { "rank": "A", "suit": "Spades", "value": 11 },
          { "rank": "K", "suit": "Hearts", "value": 10 }
        ],
        "score": 21,
        "bet": 100,
        "actions": ["deal", "blackjack"],
        "double_down": false,
        "bust": false,
        "result": "win"
      }
    ]
  }
}
```

> **What happened:** Player bet $100, got blackjack, and won $150 (1.5×). Balance goes from $100 → $150 after adding the winnings.

---

### Example 2 — Player Surrenders (Player gives up half the bet)

The player is dealt a bad hand (16 against dealer's Ace) and chooses to surrender. The dealer's turn is skipped — surrender ends the round immediately.

```json
{
  "date": "2026-04-16",

  "balance": { "before": 200, "after": 150 },

  "summary": { "total_bet": 100, "total_earn": 0, "total_loss": 50 },

  "insurance": { "taken": false, "bet": 0, "result": "none" },

  "dealer": {
    "cards": [
      { "rank": "A", "suit": "Diamonds", "value": 11 }
    ],
    "score": 11
  },

  "player": {
    "total_hands": 1,
    "hands": [
      {
        "hand_index": 1,
        "cards": [
          { "rank": "9", "suit": "Clubs", "value": 9 },
          { "rank": "7", "suit": "Hearts", "value": 7 }
        ],
        "score": 16,
        "bet": 100,
        "actions": ["deal", "surrender"],
        "double_down": false,
        "bust": false,
        "result": "lose"
      }
    ]
  }
}
```

> **What happened:** Player bet $100 but surrendered. They lost only $50 (half the bet). Balance goes from $200 → $150. The dealer's `cards` array only has one card because the dealer's hidden card is never revealed when the player surrenders.

---

### Example 3 — Dealer Blackjack with Insurance (Player breaks even)

The dealer shows an Ace. The player buys insurance for $25 (half of their $50 bet). The dealer reveals blackjack, so the player loses their main bet but wins the insurance 2:1, breaking even.

```json
{
  "date": "2026-04-16",

  "balance": { "before": 300, "after": 300 },

  "summary": { "total_bet": 50, "total_earn": 50, "total_loss": 50 },

  "insurance": { "taken": true, "bet": 25, "result": "win" },

  "dealer": {
    "cards": [
      { "rank": "A", "suit": "Hearts", "value": 11 },
      { "rank": "K", "suit": "Spades", "value": 10 }
    ],
    "score": 21
  },

  "player": {
    "total_hands": 1,
    "hands": [
      {
        "hand_index": 1,
        "cards": [
          { "rank": "8", "suit": "Clubs", "value": 8 },
          { "rank": "J", "suit": "Diamonds", "value": 10 }
        ],
        "score": 18,
        "bet": 50,
        "actions": ["deal", "stand"],
        "double_down": false,
        "bust": false,
        "result": "lose"
      }
    ]
  }
}
```

> **What happened:** Player lost their $50 main bet to dealer blackjack, but won $50 from insurance (bet $25, paid 2:1 = +$50). Net change is $0 — balance stays at $300.

---

## Full Example

```json
{
  "date": "2026-04-16",

  "balance": { "before": 100, "after": 100 },

  "summary": { "total_bet": 100, "total_earn": 50, "total_loss": 50 },

  "insurance": { "taken": false, "bet": 0, "result": "none" },

  "dealer": {
    "cards": [
      { "rank": "K", "suit": "Hearts", "value": 10 },
      { "rank": "9", "suit": "Spades", "value": 9 }
    ],
    "score": 19
  },

  "player": {
    "total_hands": 2,
    "hands": [
      {
        "hand_index": 1,
        "cards": [
          { "rank": "A", "suit": "Clubs", "value": 11 },
          { "rank": "10", "suit": "Diamonds", "value": 10 }
        ],
        "score": 21,
        "bet": 50,
        "actions": ["split", "stand"],
        "double_down": false,
        "bust": false,
        "result": "win"
      },
      {
        "hand_index": 2,
        "cards": [
          { "rank": "7", "suit": "Hearts", "value": 7 },
          { "rank": "5", "suit": "Clubs", "value": 5 },
          { "rank": "J", "suit": "Spades", "value": 10 }
        ],
        "score": 22,
        "bet": 50,
        "actions": ["split", "hit", "bust"],
        "double_down": false,
        "bust": true,
        "result": "lose"
      }
    ]
  }
}
```
