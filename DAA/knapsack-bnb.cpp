
#include <algorithm> // For sorting items using sort().
#include <iostream>  // For input and output operations.
#include <queue>     // For queue used in Branch and Bound.
#include <vector>    // For storing items dynamically.

using namespace std;


// Structure to store details of each item.
struct Item {
  int weight;       // Weight of the item.
  int value;        // Profit or value of the item.
  double ratio;     // Value per unit weight (value / weight).
};


// Structure representing a node in the state-space tree.
struct Node {
  int level;        // Index of the last item considered.
  int profit;       // Total profit obtained so far.
  int weight;       // Total weight selected so far.
  double bound;     // Maximum possible profit (upper bound).
};


// Function to sort items in decreasing order of value/weight ratio.
bool compareItems(Item a, Item b) {
  return a.ratio > b.ratio;
}


// Function to calculate the upper bound for a node.
double bound(Node u, int n, int W, vector<Item> &items) {

  // If current weight has reached capacity, no additional profit is possible.
  if (u.weight >= W)
    return 0;

  double profit_bound = u.profit; // Starts with current profit.

  int j = u.level + 1;             // Starts checking the next item.
  int totweight = u.weight;        // Stores current total weight.

  // Adds complete items while they fit within the remaining capacity.
  while ((j < n) && (totweight + items[j].weight <= W)) {

    totweight += items[j].weight;  // Adds the item's weight.
    profit_bound += items[j].value; // Adds the item's full value.
    j++;                           // Moves to the next item.
  }

  // If some capacity remains, considers a fraction of the next item.
  // This gives an optimistic upper bound on possible profit.
  if (j < n)
    profit_bound += (W - totweight) * items[j].ratio;

  return profit_bound; // Returns the calculated upper bound.
}


// Function to solve 0/1 Knapsack using Branch and Bound.
int knapsack(int W, vector<Item> &items) {

  int n = items.size(); // Gets the total number of items.

  // Sorts items by decreasing value/weight ratio.
  sort(items.begin(), items.end(), compareItems);

  // Creates a queue to store nodes of the state-space tree.
  queue<Node> Q;

  Node u, v; // u = current node, v = child node.

  // Creates the root node.
  // Level -1 means no items have been considered.
  // Initial profit and weight are 0.
  u = {-1, 0, 0, 0};

  Q.push(u); // Inserts the root node into the queue.

  int maxProfit = 0; // Stores the maximum profit found so far.

  // Continues until the queue becomes empty.
  while (!Q.empty()) {

    u = Q.front(); // Gets the first node from the queue.
    Q.pop();       // Removes that node from the queue.

    // If this is the root node, set the next level to 0.
    if (u.level == -1)
      v.level = 0;

    // If all items have been considered, skip this node.
    if (u.level == n - 1)
      continue;

    // Moves to the next item.
    v.level = u.level + 1;

    // BRANCH 1: INCLUDE THE CURRENT ITEM.

    // Adds the current item's weight to the total weight.
    v.weight = u.weight + items[v.level].weight;

    // Adds the current item's value to the total profit.
    v.profit = u.profit + items[v.level].value;

    // Checks whether the item fits and improves maximum profit.
    if (v.weight <= W && v.profit > maxProfit)
      maxProfit = v.profit;

    // Calculates the upper bound for the include branch.
    v.bound = bound(v, n, W, items);

    // Adds this node to the queue only if it can improve maxProfit.
    // Otherwise, the branch is pruned.
    if (v.bound > maxProfit)
      Q.push(v);


    // BRANCH 2: EXCLUDE THE CURRENT ITEM.

    // Keeps the previous total weight without adding the item.
    v.weight = u.weight;

    // Keeps the previous profit without adding the item.
    v.profit = u.profit;

    // Calculates the upper bound for the exclude branch.
    v.bound = bound(v, n, W, items);

    // Explores this branch only if it can potentially improve maxProfit.
    if (v.bound > maxProfit)
      Q.push(v);
  }

  // Returns the highest profit found.
  return maxProfit;
}


// Main function: program execution starts here.
int main() {

  int W = 50; // Maximum capacity of the knapsack is 50.

  // Stores items in the format {weight, value, ratio}.
  vector<Item> items = {
      {10, 60, 6},
      {20, 100, 5},
      {30, 120, 4}
  };

  // Calculates the value/weight ratio for every item.
  for (auto &item : items) {

    // Converts value to double to get an accurate decimal ratio.
    item.ratio = static_cast<double>(item.value) / item.weight;
  }

  // Calls the Knapsack function and stores the maximum profit.
  int max_value = knapsack(W, items);

  // Displays the maximum profit.
  cout << "Maximum value: " << max_value << endl;

  return 0; // Indicates successful program termination.
}
