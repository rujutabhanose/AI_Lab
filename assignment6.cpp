// Implement basic search strategies – 8-Queens Problem
#include <iostream>
#include <vector>
using namespace std;

// Function to check if placing a queen at (row, col) is safe
bool isSafe(vector<vector<char>> &board, int row, int col) {
    int n = board.size();

    // Check vertically upward
    for (int i = row - 1; i >= 0; i--) {
        if (board[i][col] == 'Q')
            return false;
    }

    // Check upper left diagonal
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j] == 'Q')
            return false;
    }

    // Check upper right diagonal
    for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++) {
        if (board[i][j] == 'Q')
            return false;
    }

    return true;
}

// Recursive function to solve the N-Queens problem
bool solveNQueens(vector<vector<char>> &board, int row) {
    int n = board.size();

    // Base case: All queens are placed
    if (row == n) {
        // Print the solution
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++)
                cout << board[i][j] << " ";
            cout << endl;
        }
        cout << endl;
        return true;
    }

    // Try placing a queen in all columns of the current row
    for (int col = 0; col < n; col++) {
        if (isSafe(board, row, col)) {
            board[row][col] = 'Q'; // Place the queen

            if (solveNQueens(board, row + 1))
                return true; // Stop after the first valid solution

            board[row][col] = '.'; // Backtrack
        }
    }

    return false;
}

int main() {
    int n = 8;
    vector<vector<char>> board(n, vector<char>(n, '.'));

    if (!solveNQueens(board, 0))
        cout << "No solution found." << endl;

    return 0;
}