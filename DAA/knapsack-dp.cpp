
#include <bits/stdc++.h>
using namespace std;

// Structure to store the weight and value of each item
struct Item {
    int weight;
    int value;
};

// Function to solve the 0/1 Knapsack problem using Dynamic Programming
int knapsack(int W, vector<Item> &items) {

    int n = items.size(); // Number of items

    // Create a DP table with (n+1) rows and (W+1) columns
    // dp[i][w] stores the maximum value using first i items
    // with knapsack capacity w
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    // Traverse through each item
    for (int i = 1; i <= n; i++) {

        // Check every possible capacity from 1 to W
        for (int w = 1; w <= W; w++) {

            // Check if the current item's weight fits in the knapsack
            if (items[i - 1].weight <= w) {

                // Option 1: Do not include the current item
                // Option 2: Include the current item
                // Add its value to the best value for the remaining capacity
                // Choose the option that gives maximum value
                dp[i][w] = max(
                    dp[i - 1][w],
                    dp[i - 1][w - items[i - 1].weight] + items[i - 1].value
                );

            } else {

                // If the item is too heavy, skip it
                // Copy the result from the previous row
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    // Return the maximum value possible with all items and capacity W
    return dp[n][W];
}

int main() {

    int W = 269; // Maximum capacity of the knapsack

    // Store items in the format {weight, value}
    vector<Item> items = {
        {95, 55},
        {4, 10},
        {60, 47},
        {32, 5},
        {23, 4},
        {72, 50},
        {80, 8},
        {62, 61},
        {65, 85},
        {46, 87}
    };

    // Call the knapsack function to calculate the maximum value
    int max_value = knapsack(W, items);

    // Display the maximum value obtained
    cout << "Maximum value: " << max_value << endl;

    return 0; // End of program
}
