
#include <iostream>  // Header file for input and output operations (cin, cout).
#include <vector>    // Header file to use 2D vectors for storing the chessboard.
using namespace std;

// Function to check whether placing a queen at (row, col) is safe.
bool isSafe(const vector<vector<int>>& board, int row, int col, int n) {

    // Check the same column in all previous rows.
    // We only check previous rows because queens are placed row by row.
    for (int i = 0; i < row; i++) {

        // If a queen is already present in the same column,
        // placing another queen here is not safe.
        if (board[i][col])
            return false;  // Returns false if a queen is found.
    }

    // Check the upper-left diagonal of the current position.
    // i moves upwards (row - 1) and j moves left (col - 1).
    for (int i = row - 1, j = col - 1;
         i >= 0 && j >= 0; i--, j--) {

        // Checks whether any queen exists on the upper-left diagonal.
        if (board[i][j])
            return false;  // Returns false if a queen is found.
    }

    // Check the upper-right diagonal of the current position.
    // i moves upwards and j moves right.
    for (int i = row - 1, j = col + 1;
         i >= 0 && j < n; i--, j++) {

        // Checks whether any queen exists on the upper-right diagonal.
        if (board[i][j])
            return false;  // Returns false if a queen is found.
    }

    // If no queen is found in the same column or diagonals,
    // the current position is safe.
    return true;
}

// Recursive function to solve the N-Queens problem using backtracking.
bool solve(vector<vector<int>>& board, int row, int n) {

    // Base condition: If row becomes equal to n,
    // it means all n queens have been successfully placed.
    if (row == n)
        return true;  // Solution is found.

    // Try placing a queen in every column of the current row.
    for (int col = 0; col < n; col++) {

        // Check whether the current position is safe.
        if (isSafe(board, row, col, n)) {

            // Place a queen at the current position.
            // 1 represents a queen and 0 represents an empty cell.
            board[row][col] = 1;

            // Recursively move to the next row to place another queen.
            if (solve(board, row + 1, n))
                return true;  // Returns true if a solution is found.

            // BACKTRACKING:
            // If placing the queen does not lead to a solution,
            // remove the queen from the current position.
            board[row][col] = 0;

            // The loop will now try the next column in the same row.
        }
    }

    // If no column works in the current row,
    // return false to go back to the previous row.
    return false;
}

// Main function: Program execution starts here.
int main() {

    int n;  // Stores the number of queens and chessboard size.

    cout << "Enter number of queens: ";
    cin >> n;  // Takes the number of queens from the user.

    // Check whether the entered number is valid.
    if (n <= 0) {
        cout << "Invalid size.\n";
        return 0;  // Terminates the program for invalid input.
    }

    // Creates an n x n chessboard using a 2D vector.
    // Initially, all cells contain 0 (empty positions).
    vector<vector<int>> board(n, vector<int>(n, 0));

    // Starts solving the problem from row 0.
    if (solve(board, 0, n)) {

        // If solve() returns true, a valid arrangement is found.
        cout << "Solution:\n";

        // Iterates through each row of the chessboard.
        for (const auto& row : board) {

            // Iterates through each cell in the current row.
            for (int cell : row)

                // Prints 1 if a queen is present, otherwise prints 0.
                cout << cell << " ";

            // Moves to the next line after printing one complete row.
            cout << "\n";
        }

    } else {

        // Executes when no valid arrangement of queens is possible.
        cout << "No solution exists.\n";
    }

    return 0;  // Indicates successful program termination.
}

/*
IMPORTANT CONCEPT: BACKTRACKING

1. Place a queen in a safe position in the current row.
2. Move to the next row using recursion.
3. Check whether a safe position exists in the next row.
4. If no solution is possible, remove the previously placed queen.
5. Try another column in the previous row.
6. Repeat until all queens are placed or all possibilities are exhausted.

TIME COMPLEXITY:
- Worst-case time complexity: O(N!)
- We place one queen per row and try different column arrangements.
- Safety checking also takes O(N) time per attempted placement.

SPACE COMPLEXITY:
- Chessboard: O(N^2)
- Recursion stack: O(N)
- Total auxiliary space including the board: O(N^2).
*/

/*
EXAMPLE:

Input:
n = 4

We need to place 4 queens on a 4x4 chessboard.

Rules:
- No two queens should be in the same row.
- No two queens should be in the same column.
- No two queens should be on the same diagonal.

One possible solution:

0 1 0 0
0 0 0 1
1 0 0 0
0 0 1 0

Here:
1 = Queen
0 = Empty position

Explanation:

Step 1:
Place the first queen at row 0, column 1.

Step 2:
Move to the next row and place a queen
at row 1, column 3.

Step 3:
Place the third queen at row 2, column 0.

Step 4:
Place the fourth queen at row 3, column 2.

All four queens are placed safely.

Output:
Solution:
0 1 0 0
0 0 0 1
1 0 0 0
0 0 1 0

Explanation:
- isSafe() checks the column and both diagonals.
- solve() places queens row by row.
- If a placement fails, the queen is removed.
- Trying another position is called Backtracking.
*/