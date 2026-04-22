# Blackjack (C++)

A feature-rich console-based Blackjack game written in C++ with balance tracking, split, double down, surrender, and insurance.

## Features

- 3-deck shoe with automatic reshuffle when < 25% cards remain
- **Hit**, **Stand**, **Split** (up to 4 times), **Double Down**, **Surrender**, **Insurance**
- Balance tracking & deposit system
- Dealer follows standard casino rules (stand on 17)
- Blackjack pays 1.5×

## Requirements

- **g++** with C++14 support (MinGW recommended on Windows)
- MinGW install path: `C:/mingw` (used by `compile_flags.txt`)

> If you don't have MinGW, download it from [winlibs.com](https://winlibs.com/) or install via MSYS2.

## How to Compile

Open a terminal (Git Bash, MSYS2, or any shell with `g++` on your PATH) in the project root and run:

```bash
g++ -std=c++14 -Iinclude -o output/blackjack.exe main.cpp src/Dealer.cpp src/Deck.cpp src/Hand.cpp src/Player.cpp src/game.cpp src/input.cpp
```

Or use a one-liner that picks up all source files automatically:

```bash
g++ -std=c++14 -Iinclude -o output/blackjack.exe main.cpp src/*.cpp
```

## How to Run

After compiling, run the executable:

```bash
./output/blackjack.exe
```

Or on Windows Command Prompt:

```cmd
output\blackjack.exe
```

A pre-built executable is also available at `output/blackjack.exe`.

## How to Play

1. At the main menu, select an option:
   | Key | Action |
   |-----|--------|
   | 1 | Play Blackjack |
   | 5 | Deposit chips |
   | 6 | Check balance |
   | 9 | Exit |

2. Place your bet when prompted.

3. During a hand, choose from the available actions:
   | Action | Description |
   |--------|-------------|
   | Hit | Draw another card |
   | Stand | Keep your current hand |
   | Split | Split two equal-value cards (max 4 splits) |
   | Double Down | Double your bet, receive one more card |
   | Surrender | Forfeit the hand, lose only 50% of your bet |
   | Insurance | Side bet when dealer shows an Ace; pays 2:1 if dealer has blackjack |

## Project Structure

```
Blackjack/
├── main.cpp            # Entry point
├── include/            # Header files
│   ├── card.h
│   ├── Deck.h
│   ├── Hand.h
│   ├── Player.h
│   ├── Dealer.h
│   ├── game.h
│   └── input.h
├── src/                # Implementation files
│   ├── Deck.cpp
│   ├── Hand.cpp
│   ├── Player.cpp
│   ├── Dealer.cpp
│   ├── game.cpp
│   └── input.cpp
├── output/             # Compiled executable
│   └── blackjack.exe
├── data/               # Player & config data
├── docs/               # Documentation
│   ├── RULES.md        # Full blackjack rules reference
│   └── DATA_SCHEMA.md  # Data file schema
└── compile_flags.txt   # Compiler flags for IDE tooling
```

## Game Rules Summary

| Rule | Value |
|------|-------|
| Decks in shoe | 3 |
| Blackjack payout | 1.5× bet |
| Dealer stands on | 17 |
| Max splits | 4 |
| Insurance | Available when dealer shows Ace |
| Surrender | Available on first two cards |

See [docs/RULES.md](docs/RULES.md) for the full rules reference.
