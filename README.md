# Blackjack (C++)

Console-based Blackjack game written in C++. Supports full casino rules and optionally saves game history to a Spring Boot backend.

## Features

- 3-deck shoe, reshuffles when < 25% cards remain
- Hit, Stand, Split (up to 4 times), Double Down, Surrender, Insurance
- Balance tracking & deposit system
- Dealer stands on 17, Blackjack pays 1.5x
- Game history saved via REST API (optional)

## Requirements

- **g++** with C++14 support — install via [MSYS2](https://www.msys2.org/) (UCRT64)
- **libcurl** — required for API communication

Install both with MSYS2:
```bash
pacman -S mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-curl
```

## Compile & Run

```bash
g++ main.cpp src/*.cpp -Iinclude -L. -lcurl -o blackjack.exe
```

```bash
./blackjack.exe
```

## How to Play

Enter your starting balance when prompted, then use the menu:

| Option | Action |
|--------|--------|
| 1 | Play Blackjack |
| 2 | View game history (requires API) |
| 5 | Deposit chips |
| 6 | Check balance |
| 9 | Exit |

During a hand:

| Action | Description |
|--------|-------------|
| Hit | Draw another card |
| Stand | Keep current hand |
| Split | Split two equal-value cards (max 4 times) |
| Double Down | Double bet, receive one more card |
| Surrender | Forfeit hand, lose only 50% of bet |
| Insurance | Side bet when dealer shows Ace; pays 2:1 if dealer has Blackjack |

## API Backend (Optional)

The game can save session data to a Spring Boot REST API at `http://localhost:8080`.

- `POST /save` — saves game session after each round
- `GET /history` — retrieves all saved sessions

If the backend is not running, the game prints `Failed to save` and continues normally.

See [black_jack_API/](black_jack_API/) for the Spring Boot project.

## Project Structure

```
Blackjack/
├── main.cpp
├── include/            # Header files
│   ├── card.h
│   ├── Deck.h
│   ├── Hand.h
│   ├── Player.h
│   ├── Dealer.h
│   ├── service.h
│   ├── input.h
│   ├── saving.h
│   ├── APIclient.h
│   ├── Gamerecord.h
│   └── json.hpp
├── src/                # Source files
│   ├── Deck.cpp
│   ├── Hand.cpp
│   ├── Player.cpp
│   ├── Dealer.cpp
│   ├── service.cpp
│   ├── input.cpp
│   ├── saving.cpp
│   ├── APIclient.cpp
│   └── Gamerecord.cpp
├── data/               # Config files
├── docs/               # Documentation
│   ├── RULES.md
│   └── DATA_SCHEMA.md
├── black_jack_API/     # Spring Boot backend
└── compile_flags.txt
```

See [docs/RULES.md](docs/RULES.md) for full game rules and [docs/DATA_SCHEMA.md](docs/DATA_SCHEMA.md) for the saved data format.
