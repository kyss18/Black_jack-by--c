# ♠ Blackjack Game (C++)

A feature-rich console-based Blackjack game written in C++.

## Features

- 3-deck shoe with automatic shuffle when < 25% cards remain
- **Hit**, **Stand**, **Split** (up to 4 times), **Double Down**, **Surrender**
- **Insurance** when dealer shows an Ace
- Balance tracking & deposit system
- Dealer follows standard rules (stand on 17)

## Project Structure

```
Blackjack/
├── src/                        # Source code
│   └── blackjackcomposition.cpp
├── data/                       # Player & config data (JSON)
│   ├── players.json            # Saved player data & stats
│   └── game_config.json        # Game settings
├── output/                     # Compiled executable goes here
├── docs/                       # Documentation
│   ├── README.md               # This file
│   └── RULES.md                # Blackjack rules reference
└── .gitignore
```

## How to Compile

### Using g++ (MinGW / MSYS2)
```bash
g++ -std=c++17 -o output/blackjack src/blackjackcomposition.cpp
```

### Using MSVC (Developer Command Prompt)
```bash
cl /EHsc /Fe:output\blackjack.exe src\blackjackcomposition.cpp
```

## How to Run

```bash
output/blackjack
```

## How to Play

1. Enter your starting balance when prompted.
2. From the main menu:
   - **1** — Play Blackjack
   - **5** — Deposit chips
   - **6** — Check balance
   - **9** — Exit
3. During a hand, choose from available options (Hit / Stand / Split / Surrender / Double).

## Game Rules Summary

| Rule | Value |
|------|-------|
| Decks | 3 |
| Blackjack payout | 1.5× bet |
| Dealer stands on | 17 |
| Max splits | 4 |
| Insurance | Available when dealer shows Ace |
| Surrender | Available on first two cards |

## Future Plans

- [ ] Persistent player stats saved to `data/players.json`
- [ ] Game history logging to `output/game_log.txt`
- [ ] Coin flip mini-game
- [ ] Three-Card game
- [ ] Lucky Number game
- [ ] Statistics screen
