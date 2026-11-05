#include <iostream>
#include <vector>
using namespace std;

bool isSafe(const vector<vector<int>>& board, int row, int col, int n) {
    // Check the same column in previous rows.
    for (int i = 0; i < row; i++) {
        if (board[i][col])
            return false;
    }

    // Check upper-left diagonal.
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j])
            return false;
    }

    // Check upper-right diagonal.
    for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++) {
        if (board[i][j])
            return false;
    }

    return true;
}

bool solve(vector<vector<int>>& board, int row, int n) {
    if (row == n)
        return true;

    for (int col = 0; col < n; col++) {
        if (isSafe(board, row, col, n)) {
            board[row][col] = 1;

            if (solve(board, row + 1, n))
                return true;

            // Backtrack.
            board[row][col] = 0;
        }
    }

    return false;
}

int main() {
    int n;
    cout << "Enter number of queens: ";
    cin >> n;

    if (n <= 0) {
        cout << "Invalid size.\n";
        return 0;
    }

    vector<vector<int>> board(n, vector<int>(n, 0));

    if (solve(board, 0, n)) {
        cout << "Solution:\n";
        for (const auto& row : board) {
            for (int cell : row)
                cout << cell << " ";
            cout << "\n";
        }
    } else {
        cout << "No solution exists.\n";
    }

    return 0;
}

/*
Note: This follows the supplied PDF code: it starts with an empty board
and places queens row by row. The PDF's problem statement mentions a
pre-placed first queen, but its provided code does not accept a fixed
queen position.
*/
