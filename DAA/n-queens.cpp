
#include <bits/stdc++.h>
using namespace std;

int COL; // Column where the first queen is placed
int ROW; // Row where the first queen is placed
int N = 4; // Size of the chessboard (N x N)

// Function to print the final chessboard
void printSolution(vector<vector<int>> board) {

    // Traverse every row and column
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)

            // Print Q if a queen is present
            if (board[i][j])
                cout << "Q ";

            // Otherwise, print a dot
            else
                cout << ". ";

        printf("\n");
    }
}

// Function to check whether placing a queen at (row, col) is safe
bool isSafe(vector<vector<int>> board, int row, int col) {
    int i, j;

    // Check all columns to the left in the same row
    for (i = 0; i < col; i++)
        if (board[row][i])
            return false;

    // Check all columns to the right in the same row
    for (i = col + 1; i < N; i++)
        if (board[row][i])
            return false;

    // Check bottom-right diagonal
    for (i = row, j = col; i < N && j < N; i++, j++)
        if (board[i][j])
            return false;

    // Check top-right diagonal
    for (i = row, j = col; i >= 0 && j < N; i--, j++)
        if (board[i][j])
            return false;

    // Check top-left diagonal
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j])
            return false;

    // Check bottom-left diagonal
    for (i = row, j = col; j >= 0 && i < N; i++, j--)
        if (board[i][j])
            return false;

    // No queen is attacking this position
    return true;
}

// Recursive function to place queens column by column
bool solveNQUtil(vector<vector<int>> &board, int col) {

    // Base case: All columns have been processed
    if (col >= N)
        return true;

    // If the current column already contains the first queen,
    // skip it and move to the next column
    if (col == COL) {
        if (solveNQUtil(board, col + 1))
            return true;
        else
            return false;
    }

    else {

        // Try placing a queen in every row of the current column
        for (int i = 0; i < N; i++) {

            // Check whether the position is safe
            if (isSafe(board, i, col)) {

                // Place the queen at the current position
                board[i][col] = 1;

                // Recursively solve for the next column
                if (solveNQUtil(board, col + 1))
                    return true;

                // Backtracking: Remove the queen if no solution is found
                board[i][col] = 0;
            }
        }
    }

    // No valid position was found in this column
    return false;
}

// Function to take input and solve the N-Queens problem
bool solveNQ() {

    // Get the size of the chessboard
    cout << "Enter size of board: ";
    cin >> N;

    // Get the row of the first queen
    cout << "Enter row and col of first queen to be placed:\nrow (1-" << N
         << "): ";
    cin >> ROW;

    // Convert row from 1-based indexing to 0-based indexing
    ROW--;

    // Get the column of the first queen
    cout << "\ncol(1-" << N << "): ";
    cin >> COL;

    // Convert column from 1-based indexing to 0-based indexing
    COL--;

    cout << endl;

    // Create an N x N chessboard initialized with zeros
    vector<vector<int>> board(N, vector<int>(N, 0));

    // Place the first queen at the given position
    board[ROW][COL] = 1;

    // Start solving from column 0
    if (solveNQUtil(board, 0) == false) {

        // Display message if no solution exists
        cout << "Solution does not exist";
        return false;
    }

    // Print the solved chessboard
    printSolution(board);

    return true;
}

int main() {

    // Call the function to solve the N-Queens problem
    solveNQ();

    return 0;
}
