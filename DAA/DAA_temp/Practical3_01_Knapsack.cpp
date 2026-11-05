#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int knapsack(const vector<int>& wt, const vector<int>& val, int n, int W) {
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            dp[i][w] = dp[i - 1][w];

            if (wt[i - 1] <= w) {
                dp[i][w] = max(
                    dp[i][w],
                    val[i - 1] + dp[i - 1][w - wt[i - 1]]
                );
            }
        }
    }

    return dp[n][W];
}

int main() {
    int n, W;

    cout << "Enter number of items: ";
    cin >> n;

    if (n <= 0) {
        cout << "Invalid number of items.\n";
        return 0;
    }

    vector<int> wt(n), val(n);

    for (int i = 0; i < n; i++) {
        cout << "Enter weight and value: ";
        cin >> wt[i] >> val[i];

        if (wt[i] < 0 || val[i] < 0) {
            cout << "Weight and value must be non-negative.\n";
            return 0;
        }
    }

    cout << "Enter knapsack capacity: ";
    cin >> W;

    if (W < 0) {
        cout << "Capacity must be non-negative.\n";
        return 0;
    }

    cout << "Maximum value: " << knapsack(wt, val, n, W) << "\n";
    return 0;
}

/*
Time complexity: O(n * W)
Space complexity: O(n * W)
*/
