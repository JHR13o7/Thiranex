### 4. Tic Tac Toe Mini Game (`Tic-Tac-Toe/README.md`)

```markdown
# Tic Tac Toe (Console Mini Game)

An interactive two-player console game built in C++ demonstrating core programming fundamentals including 2D arrays, nested loops, input validation, and conditional game-state evaluation[cite: 3].

## Key Features
* **Dynamic 2D Grid Rendering:** Uses a `3x3` character array (`char board[3][3]`) to track moves and redraw the board cleanly after every turn[cite: 3].
* **Coordinate Mapping & Validation:** Maps 1–9 slot selections to 2D row/column indices while preventing invalid characters, out-of-bounds numbers, or overwriting occupied cells[cite: 3].
* **Automated Win & Draw Detection:** Evaluates rows, columns, diagonals, and board saturation after each move to declare a winner or a draw[cite: 3].
* **Replay Loop:** Allows players to start a fresh match immediately after a game concludes without restarting the program[cite: 3].

## How to Compile and Run
1. Open a terminal in the project directory.
2. Compile the source code:
   ```bash
   g++ TicTacToe.cpp -o TicTacToe.exe