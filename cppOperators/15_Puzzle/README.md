# 15 Puzzle

C++ implementation of the 15 Puzzle game [(see more)](https://en.wikipedia.org/wiki/15_Puzzle).

## Basic overview

Start with a 4x4 grid with 15 tiles numbered 1-15 and one empty tile.

```
X   15  1   4
2   5   9   12
7   8   11  14
10  13  6   3
```

Each turn, select a tile to move to the empty spot `X`.
Can only slide in tiles adjacent to the empty tile.

Goal is to rearrange tiles until they are in numerical order with the missing tile in the bottom right corner.

```
1   2   3   4
5   6   7   8
9   10  11  12
13  14  15  X
```

## Implementation: top-level

### Display

Board:
- Generate initial game state (numbered tiles 1-15, empty tile)
- Display updated game state post-command
- Evaluate a completed game

### User

Each turn, user enters a single letter command to perform an action.
5 valid commands:
- w: slide tile up
- a: slide tile left
- s: slide tile down
- d: slide tile right
- q: quit game

Must be able to:
- Receive user inputs
- Handle invalid inputs
- Allow user to quit early

## Implementation: class/namespace/main

### Class Tile

Display an individual tile

### Class Board

private:
- state/tile holder: 4x4 grid of Tile
- namespace to hold valid command chars?
- bool quitGame: false

public:
- randomise game state on initialisation?
- display game state:
- get user input:
- update game state: get user input -> change state / quit (-> quitGame = true)
- evaluate game state: continueGame() false if (state == win state || continueGame == true)

### Namespace UserCommands

Namespace in Board denoting valid commands
Handle invalid inputs

### main()

- Initialise board
- Display board
-   do (
        get user input -> update game state
        display new state
        )
    while (continueGame())
- Display response according to Board.quitGame


### Helper Class Point

Index game board tiles by {x, y}
Class helps pass or return a pair of indices

### Helper Class Direction

Translate user-input `char` commands -> Direction object 
More intuitive to understand
