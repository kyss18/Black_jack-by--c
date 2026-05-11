# Data Schema

Game sessions are saved to the Spring Boot backend via `POST /save` and retrieved via `GET /history`.

---

## API Record (top-level, from `/history`)

Each record returned by the API has these fields:

| Field | Type | Description |
|-------|------|-------------|
| `id` | number | Auto-incremented record ID |
| `gameSession` | string | Unique 8-character session ID (UUID prefix) |
| `createdAt` | string | Timestamp when the session was saved (`yyyy-MM-dd HH:mm:ss`) |
| `jsonData` | object | Full game data (see below) |

---

## `jsonData`

The game data saved after each round.

| Field | Type | Description |
|-------|------|-------------|
| `balance` | object | Player's balance info for this session |
| `player` | object | Player's hands and stats |
| `dealer` | object | Dealer's hand |

---

## `balance`

| Field | Type | Description |
|-------|------|-------------|
| `starting_balance` | number | Balance before the round started |
| `after_playing` | number | Balance after the round ended |

```json
"balance": { "starting_balance": 500, "after_playing": 450 }
```

---

## `player`

| Field | Type | Description |
|-------|------|-------------|
| `balance` | number | Current balance after round |
| `hand` | array | List of hands played (multiple after splits) |
| `insurance` | number | Insurance bet amount (0 if not taken) |
| `surrender` | boolean | Whether the player surrendered |
| `totalearn` | number | Total amount won this round |
| `totalloss` | number | Total amount lost this round |

---

## `dealer`

| Field | Type | Description |
|-------|------|-------------|
| `hand` | object | Dealer's hand (see Hand Object) |

---

## Hand Object

Each entry in `player.hand` and `dealer.hand` has:

| Field | Type | Description |
|-------|------|-------------|
| `hand` | array | Cards in this hand (see Card Object) |
| `action` | array | Sequence of actions taken |
| `score` | number | Final score of the hand |
| `betting_amount` | number | Bet placed on this hand |
| `is_doubling_down` | boolean | Whether the player doubled down |
| `hand_is_bust` | boolean | Whether the hand exceeded 21 |
| `result` | string | `"win"`, `"lose"`, or `"tie"` |

```json
{
  "hand": [
    { "name_card": "A", "type_card": "Spades" },
    { "name_card": "K", "type_card": "Hearts" }
  ],
  "action": ["deal", "blackjack"],
  "score": 21,
  "betting_amount": 100,
  "is_doubling_down": false,
  "hand_is_bust": false,
  "result": "win"
}
```

---

## Card Object

| Field | Type | Description |
|-------|------|-------------|
| `name_card` | string | Card rank: `"A"`, `"2"`–`"10"`, `"J"`, `"Q"`, `"K"` |
| `type_card` | string | Suit: `"Hearts"`, `"Diamonds"`, `"Clubs"`, `"Spades"` |

```json
{ "name_card": "A", "type_card": "Spades" }
```

---

## Action Values

| Value | Meaning |
|-------|---------|
| `"deal"` | Initial two cards dealt |
| `"hit"` | Player drew a card |
| `"stand"` | Player stood |
| `"double"` | Player doubled down |
| `"split"` | Hand was split |
| `"blackjack"` | Natural blackjack on deal |
| `"bust"` | Hand exceeded 21 |
| `"surrender"` | Player surrendered |

---

## Full Example

```json
{
  "id": 1,
  "gameSession": "a3f9c21b",
  "createdAt": "2026-05-11 14:32:00",
  "jsonData": {
    "balance": {
      "starting_balance": 500,
      "after_playing": 600
    },
    "player": {
      "balance": 600,
      "insurance": 0,
      "surrender": false,
      "totalearn": 100,
      "totalloss": 0,
      "hand": [
        {
          "hand": [
            { "name_card": "A", "type_card": "Spades" },
            { "name_card": "K", "type_card": "Hearts" }
          ],
          "action": ["deal", "blackjack"],
          "score": 21,
          "betting_amount": 100,
          "is_doubling_down": false,
          "hand_is_bust": false,
          "result": "win"
        }
      ]
    },
    "dealer": {
      "hand": {
        "hand": [
          { "name_card": "9", "type_card": "Clubs" },
          { "name_card": "7", "type_card": "Diamonds" }
        ],
        "action": ["deal", "stand"],
        "score": 16,
        "betting_amount": 0,
        "is_doubling_down": false,
        "hand_is_bust": false,
        "result": ""
      }
    }
  }
}
```
