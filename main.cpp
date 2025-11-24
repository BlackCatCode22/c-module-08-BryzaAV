#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Global variables for the board and scores
char board[8][8];
int scoreRed = 0;
int scoreBlack = 0;

// Function to initialize the board with pieces
void initBoard() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if ((i + j) % 2 != 0) {
                if (i < 3) board[i][j] = 'b';      // Black pieces
                else if (i > 4) board[i][j] = 'r'; // Red pieces
                else board[i][j] = ' ';            // Empty black squares
            } else {
                board[i][j] = ' ';                 // Empty white squares
            }
        }
    }
}

// Function to display the board and current score
void displayBoard() {
    cout << "   0  1  2  3  4  5  6  7" << endl;
    for (int i = 0; i < 8; i++) {
        cout << i << " ";
        for (int j = 0; j < 8; j++) {
            cout << "[" << board[i][j] << "]";
        }
        cout << endl;
    }
    cout << "--------------------------------" << endl;
    cout << "Scoreboard -> Red: " << scoreRed << " | Black: " << scoreBlack << endl;
    cout << "--------------------------------" << endl;
}

// Function to execute a move
// Returns true if move was successful, false otherwise
bool makeMove(int r1, int c1, int r2, int c2, char player) {
    // 1. Check bounds
    if (r1 < 0 || r1 > 7 || c1 < 0 || c1 > 7 || r2 < 0 || r2 > 7 || c2 < 0 || c2 > 7) {
        cout << "Error: Move out of bounds." << endl;
        return false;
    }

    // 2. Check if picking correct piece
    char piece = board[r1][c1];
    char opponent = (player == 'r') ? 'b' : 'r';
    char playerKing = (player == 'r') ? 'R' : 'B';
    char opponentKing = (player == 'r') ? 'B' : 'R';

    if (piece != player && piece != playerKing) {
        cout << "Error: That's not your piece!" << endl;
        return false;
    }

    // 3. Check if destination is empty
    if (board[r2][c2] != ' ') {
        cout << "Error: Destination is not empty." << endl;
        return false;
    }

    // 4. Calculate distances
    int rowDiff = r2 - r1;
    int colDiff = abs(c2 - c1);

    // 5. Regular Move logic (1 step diagonal)
    if (abs(rowDiff) == 1 && colDiff == 1) {
        // Regular pieces can only move forward
        if (piece == 'r' && rowDiff > 0) { cout << "Error: Red must move UP (row decreases)." << endl; return false; }
        if (piece == 'b' && rowDiff < 0) { cout << "Error: Black must move DOWN (row increases)." << endl; return false; }

        // Execute move
        board[r2][c2] = piece;
        board[r1][c1] = ' ';
    }
    // 6. Capture Move logic (2 steps diagonal)
    else if (abs(rowDiff) == 2 && colDiff == 2) {
        // Determine position of the jumped piece
        int jumpR = (r1 + r2) / 2;
        int jumpC = (c1 + c2) / 2;
        char jumpedPiece = board[jumpR][jumpC];

        if (jumpedPiece != opponent && jumpedPiece != opponentKing) {
            cout << "Error: You are not jumping over an opponent!" << endl;
            return false;
        }

        // Regular pieces direction check
        if (piece == 'r' && rowDiff > 0) { cout << "Error: Red must move UP." << endl; return false; }
        if (piece == 'b' && rowDiff < 0) { cout << "Error: Black must move DOWN." << endl; return false; }

        // Execute move and remove captured piece
        board[r2][c2] = piece;
        board[r1][c1] = ' ';
        board[jumpR][jumpC] = ' '; // Remove opponent
        cout << "Captured!" << endl;
    } else {
        cout << "Error: Invalid move pattern." << endl;
        return false;
    }

    // 7. King Promotion
    if (player == 'r' && r2 == 0) board[r2][c2] = 'R';
    if (player == 'b' && r2 == 7) board[r2][c2] = 'B';

    return true;
}

// Function to check if a player has any pieces left
bool hasWon(char player) {
    char opponent = (player == 'r') ? 'b' : 'r';
    char opponentKing = (player == 'r') ? 'B' : 'R';

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board[i][j] == opponent || board[i][j] == opponentKing) {
                return false; // Opponent still has pieces
            }
        }
    }
    return true; // No opponent pieces found
}

int main() {
    char playAgain = 'y';

    while (playAgain == 'y' || playAgain == 'Y') {
        initBoard();
        char turn = 'r'; // Red starts first
        bool gameOver = false;

        cout << "Welcome to C++ Checkers!" << endl;
        cout << "r = Red Piece (Moves UP), b = Black Piece (Moves DOWN)" << endl;
        cout << "R/B = Kings (Move Any Direction)" << endl;

        while (!gameOver) {
            displayBoard();
            cout << "Current Turn: " << (turn == 'r' ? "Red" : "Black") << endl;

            int r1, c1, r2, c2;
            cout << "Enter move (From Row Col To Row Col): "; // Example: 5 0 4 1
            cin >> r1 >> c1 >> r2 >> c2;

            if (makeMove(r1, c1, r2, c2, turn)) {
                if (hasWon(turn)) {
                    displayBoard();
                    cout << "*** " << (turn == 'r' ? "Red" : "Black") << " WINS! ***" << endl;
                    if (turn == 'r') scoreRed++;
                    else scoreBlack++;
                    gameOver = true;
                }
                // Switch turn
                turn = (turn == 'r') ? 'b' : 'r';
            } else {
                cout << "Try again." << endl;
            }
        }

        cout << "Game Over! Current Score - Red: " << scoreRed << " | Black: " << scoreBlack << endl;
        cout << "Play again? (y/n): ";
        cin >> playAgain;
    }

    cout << "Thanks for playing!" << endl;
    return 0;
}