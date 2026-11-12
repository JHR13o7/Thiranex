#include <iostream>

using namespace std;

//Global variables representing the game's state
char board[3][3];
char currentPlayer;

// Resets the board with numbers 1-9 for a new game
void initializeBoard() {
    char start = '1';

    //Nested loops to populate the 2D array
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = start++;
        }
    }
    currentPlayer = 'X'; //Player 'X' always takes the first turn
}

//Dynamically displays the current state of the 3x3 grid
void displayBoard(){
    cout << "\n     Tic Tac Toe     \n";
    cout << " Player 1 (X) - Player 2 (O) \n\n";

    // Drawing the grid and injecting the 2D array values
    cout << "     |     |     \n";
    cout << "  " << board[0][0] << "  |  " << board[0][1] << "  |  " << board[0][2] << "  \n";
    cout << "_____|_____|_____\n";
    cout << "     |     |     \n";
    cout << "  " << board[1][0] << "  |  " << board[1][1] << "  |  " << board[1][2] << "  \n";
    cout << "_____|_____|_____\n";
    cout << "     |     |     \n";
    cout << "  " << board[2][0] << "  |  " << board[2][1] << "  |  " << board[2][2] << "  \n";
    cout << "     |     |     \n\n";
}

//Handles user input, validates it, and updates the array
void playerMove() {
    int choice;
    bool validMove = false;

    // Loop until the player provides a legal move
    while (!validMove) {
        cout << "Player " << currentPlayer << ", enter a number (1-9): ";

        // Validation: Prevent crashes if the user types a letter instead of a number
        if (!(cin >> choice)) {
            cin.clear(); // Clear the error flag on cin
            cin.ignore(10000, '\n'); // Ignore the garbage input in the buffer
            cout << "Invalid input! Please enter a number.\n";
            continue; // Restart the loop
        }

        // Map the 1-9 choice to 2D array indices (row and column)
        int row = (choice - 1) / 3;
        int col = (choice - 1) % 3;

        // Validation: Check if choice is 1-9 AND the spot isn't already taken
        if (choice >= 1 && choice <=9 && board[row][col] != 'X' && board[row][col] != 'O') {
            board[row][col] = currentPlayer; //Place the piece
            validMove = true; // Break the loop
        } else {
            cout << "Invalid move! Spot already taken or out of bounds. Try again.\n";
        }
    }
}

// Evaluate the array for a winner
bool checkWin() {
    // Check all rows and cloumns using a single loop
    for (int i = 0; i< 3; i++) {
        if ((board[i][0] == board[i][1] && board[i][1] == board[i][2]) ||
            (board[0][i] == board[1][i] && board[1][i] == board[2][i])) {
                return true; //Match found
            }
    }
    // Check both diagonals
    if ((board[0][0] == board[1][1] && board[1][1] == board[2][2]) ||
        (board[0][2] == board[1][1] && board[1][1] == board[2][0])) {
            return true; // Match found
        }
        return false; //No winner yet
}

// Evaluate if the board is completely full (draw)
bool checkDraw() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != 'X' && board[i][j] != '0') {
                return false; //Found an empty spot (still a number, game continues)
            }
        }
    }
    return true; //Board is full
}

// Swaps the active player
void switchPlayer() {
    // This is a ternary operator. It acts like a compact is-else statement.
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}

int main() {
    char playAgain;

    // The outer loop handles game replays
    do {
        initializeBoard(); // Reset the board for a fresh gae
        bool gameOver = false;

        // The inner loop handles the active match
        while (!gameOver) {
            displayBoard();
            playerMove(); //Ask for input and place the piece

            // Check game state immediately after a piece is placed
            if (checkWin()) {
                displayBoard(); // Show the final winning board
                cout << "Congratulations! Player " << currentPlayer << " wins!\n";
                gameOver = true;
            } else if (checkDraw()) {
                displayBoard();
                cout << "No moves left. It's a draw!\n";
                gameOver = true;
            } else {
                switchPlayer(); //No winner yet, pass the turn
            }
        }

        // Replay functionality
        cout << "\nDo you want to play again? (y/n): ";
        cin >> playAgain;
    } while (playAgain == 'y' || playAgain == 'Y');

    cout << "Thanks for playing! Goodbye.\n";
    return 0;
}