
#include <iostream>  // For input and output (cin, cout).
#include <vector>    // For storing weights, values and DP table.
#include <algorithm> // For using max() function.
using namespace std;

// Function to calculate maximum value using 0/1 Knapsack.
int knapsack(const vector<int>& wt, const vector<int>& val, int n, int W) {

    // Creates a DP table with (n+1) rows and (W+1) columns.
    // Initially, all values are 0.
    // Rows represent items and columns represent capacities.
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    // Iterates through each item (1 to n).
    for (int i = 1; i <= n; i++) {

        // Iterates through every capacity from 0 to W.
        for (int w = 0; w <= W; w++) {

            // Initially, excludes the current item.
            // Copies the maximum value from the previous row.
            dp[i][w] = dp[i - 1][w];

            // Checks whether the current item's weight fits.
            if (wt[i - 1] <= w) {

                // Finds the maximum value between including
                // and excluding the current item.
                dp[i][w] = max(
                    dp[i][w], // Value when item is excluded.

                    // Value when item is included:
                    // Current item value + best value for remaining capacity.
                    val[i - 1] + dp[i - 1][w - wt[i - 1]]
                );
            }
        }
    }

    // Returns the maximum value for all items and full capacity.
    return dp[n][W];
}

// Main function: execution starts here.
int main() {

    int n, W; // n = number of items, W = knapsack capacity.

    cout << "Enter number of items: ";
    cin >> n; // Takes the number of items from the user.

    // Checks whether the number of items is valid.
    if (n <= 0) {
        cout << "Invalid number of items.\n";
        return 0; // Terminates the program.
    }

    // Creates two vectors to store weights and values.
    vector<int> wt(n), val(n);

    // Takes weight and value of each item.
    for (int i = 0; i < n; i++) {

        cout << "Enter weight and value: ";
        cin >> wt[i] >> val[i];

        // Checks whether weight or value is negative.
        if (wt[i] < 0 || val[i] < 0) {
            cout << "Weight and value must be non-negative.\n";
            return 0; // Terminates if input is invalid.
        }
    }

    cout << "Enter knapsack capacity: ";
    cin >> W; // Takes maximum weight capacity of the knapsack.

    // Checks whether capacity is negative.
    if (W < 0) {
        cout << "Capacity must be non-negative.\n";
        return 0; // Terminates if capacity is invalid.
    }

    // Calls knapsack function and displays the maximum value.
    cout << "Maximum value: " << knapsack(wt, val, n, W) << "\n";

    return 0; // Indicates successful program termination.
}

/*
TIME COMPLEXITY: O(n * W)
- Outer loop runs n times (number of items).
- Inner loop runs W+1 times (capacity).
- Each iteration performs constant-time operations.

SPACE COMPLEXITY: O(n * W)
- DP table contains (n+1) * (W+1) elements.
*/



/*
EXAMPLE:

Input:
Number of items = 3
Knapsack capacity = 5

Item    Weight    Value
1       2         12
2       1         10
3       3         20

Possible selections:

Item 1 + Item 2:
Weight = 2 + 1 = 3
Value = 12 + 10 = 22

Item 1 + Item 3:
Weight = 2 + 3 = 5
Value = 12 + 20 = 32

Item 2 + Item 3:
Weight = 1 + 3 = 4
Value = 10 + 20 = 30

All three items:
Weight = 2 + 1 + 3 = 6
Not allowed because capacity is 5.

Maximum value = 32

Output:
Maximum value: 32

Explanation:
- We have two choices for each item: Include or Exclude.
- The DP table stores the maximum value for each capacity.
- We use max() to select the better option.
- Item 1 and Item 3 give the maximum value of 32.
*/