// Implement minmax algorithm for game playing
#include <iostream>
#include <vector>
#include <climits>
using namespace std;

const char PLAYER_X = 'X';
const char PLAYER_O = 'O';
const char EMPTY = '.';

void printBoard(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++)
            cout << board[i][j] << " ";
        cout << endl;
    }
    cout << endl;
}

// Evaluate the board and return a score
int evaluateBoard(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        // Rows
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != EMPTY)
            return (board[i][0] == PLAYER_X) ? 10 : -10;
        // Columns
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != EMPTY)
            return (board[0][i] == PLAYER_X) ? 10 : -10;
    }

    // Diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != EMPTY)
        return (board[0][0] == PLAYER_X) ? 10 : -10;

    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != EMPTY)
        return (board[0][2] == PLAYER_X) ? 10 : -10;

    return 0; // Draw or ongoing
}

bool isGameOver(char board[3][3]) {
    if (evaluateBoard(board) != 0)
        return true;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == EMPTY)
                return false;

    return true;
}

// Minimax function
int minimax(char board[3][3], int depth, bool isMaximizing) {
    int score = evaluateBoard(board);

    // Base cases
    if (score == 10 || score == -10)
        return score;

    if (isGameOver(board))
        return 0;

    if (isMaximizing) { // Maximize for X
        int best = INT_MIN;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = PLAYER_X;
                    best = max(best, minimax(board, depth + 1, false));
                    board[i][j] = EMPTY;
                }
            }
        }
        return best;
    } else { // Minimize for O
        int best = INT_MAX;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = PLAYER_O;
                    best = min(best, minimax(board, depth + 1, true));
                    board[i][j] = EMPTY;
                }
            }
        }
        return best;
    }
}

// Find best move for computer
pair<int, int> findBestMove(char board[3][3]) {
    int bestVal = INT_MIN;
    pair<int, int> bestMove = {-1, -1};

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == EMPTY) {
                board[i][j] = PLAYER_X;
                int moveVal = minimax(board, 0, false); // Minimize for O
                board[i][j] = EMPTY;

                if (moveVal > bestVal) {
                    bestMove = {i, j};
                    bestVal = moveVal;
                }
            }
        }
    }
    return bestMove;
}

// Main game loop
void playGame() {
    char board[3][3];
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = EMPTY;

    cout << "Tic-Tac-Toe: Player X (you) vs. Player O (computer)\n";
    printBoard(board);

    while (true) {
        // Human move
        int row, col;
        cout << "Enter your move row (0, 1, or 2): ";
        cin >> row;
        cout << "Enter your move column (0, 1, or 2): ";
        cin >> col;

        if (row < 0 || row > 2 || col < 0 || col > 2) {
            cout << "Invalid input! Try again.\n";
            continue;
        }

        if (board[row][col] != EMPTY) {
            cout << "Invalid move! Try again.\n";
            continue;
        }

        board[row][col] = PLAYER_X;

        if (isGameOver(board)) {
            printBoard(board);
            int result = evaluateBoard(board);
            if (result == 10)
                cout << "You win!\n";
            else
                cout << "It's a draw!\n";
            break;
        }

        // Computer move
        cout << "Computer's turn...\n";
        pair<int, int> bestMove = findBestMove(board);
        board[bestMove.first][bestMove.second] = PLAYER_O;
        printBoard(board);

        if (isGameOver(board)) {
            int result = evaluateBoard(board);
            if (result == -10)
                cout << "Computer wins!\n";
            else
                cout << "It's a draw!\n";
            break;
        }
    }
}

int main() {
    playGame();
    return 0;
}