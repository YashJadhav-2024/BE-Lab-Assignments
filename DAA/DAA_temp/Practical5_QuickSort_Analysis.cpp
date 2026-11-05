
#include <iostream>   // For input and output operations (cin, cout).
#include <vector>     // For storing array elements dynamically.
#include <cstdlib>    // For rand() and srand() random number functions.
#include <ctime>      // For time() to generate a changing random seed.
#include <algorithm>  // For using swap() function.
using namespace std;


// PART 1: PARTITION FUNCTION
// Places the pivot element at its correct sorted position.
int partitionArray(vector<int>& a, int low, int high, long long& comp) {

    int pivot = a[high];  // Selects the last element as the pivot.

    int i = low - 1;      // Tracks the position of elements smaller than or equal to pivot.

    // Traverses the array from low to high-1.
    for (int j = low; j < high; j++) {

        comp++;  // Increments comparison counter for each pivot comparison.

        // Checks whether the current element is smaller than or equal to pivot.
        if (a[j] <= pivot) {

            i++;  // Moves the boundary of smaller elements forward.

            swap(a[i], a[j]); // Places the smaller element before the pivot.
        }
    }

    // Places the pivot after all smaller elements.
    // Now the pivot is at its correct sorted position.
    swap(a[i + 1], a[high]);

    return i + 1; // Returns the final index of the pivot.
}


// PART 2: RANDOMIZED PARTITION FUNCTION
// Selects a random pivot instead of always selecting the last element.
int randomizedPartition(vector<int>& a, int low, int high, long long& comp) {

    // Generates a random index between low and high (inclusive).
    int pivotIndex = low + rand() % (high - low + 1);

    // Moves the randomly selected pivot to the last position.
    // This allows us to reuse the normal partition function.
    swap(a[pivotIndex], a[high]);

    // Calls the normal partition function to arrange elements around the pivot.
    return partitionArray(a, low, high, comp);
}


// PART 3: DETERMINISTIC QUICK SORT
// Sorts the array using the last element as the pivot.
void quickSort(vector<int>& a, int low, int high, long long& comp) {

    // Base condition: Executes only when at least two elements exist.
    if (low < high) {

        // Partitions the array and gets the pivot's correct position.
        int p = partitionArray(a, low, high, comp);

        // Recursively sorts the left subarray (elements before pivot).
        quickSort(a, low, p - 1, comp);

        // Recursively sorts the right subarray (elements after pivot).
        quickSort(a, p + 1, high, comp);
    }
}


// PART 4: RANDOMIZED QUICK SORT
// Sorts the array using a randomly selected pivot.
void randomizedQuickSort(vector<int>& a, int low, int high, long long& comp) {

    // Checks whether the subarray contains at least two elements.
    if (low < high) {

        // Randomly selects a pivot and partitions the array.
        int p = randomizedPartition(a, low, high, comp);

        // Recursively sorts the left subarray.
        randomizedQuickSort(a, low, p - 1, comp);

        // Recursively sorts the right subarray.
        randomizedQuickSort(a, p + 1, high, comp);
    }
}


// PART 5: DISPLAY FUNCTION
// Prints all elements of the array.
void display(const vector<int>& a) {

    // Visits each element in the array.
    for (int x : a)
        cout << x << " "; // Prints the current element followed by a space.

    cout << "\n"; // Moves to the next line after printing the array.
}


// PART 6: MAIN FUNCTION
// Program execution starts here.
int main() {

    // Initializes the random number generator using the current time.
    // This helps generate different random pivot positions on different runs.
    srand(static_cast<unsigned int>(time(nullptr)));

    int n; // Stores the number of elements.

    cout << "Enter number of elements: ";
    cin >> n; // Takes the array size from the user.

    // Checks whether the entered size is valid.
    if (n <= 0) {

        cout << "Invalid size.\n"; // Displays an error message.

        return 0; // Terminates the program.
    }

    // Creates vector a to store original input.
    // Creates vector b to store a copy for randomized Quick Sort.
    vector<int> a(n), b;

    cout << "Enter elements: ";

    // Takes n elements from the user.
    for (int i = 0; i < n; i++)
        cin >> a[i];

    b = a; // Copies the original array into b.
           // Both sorting algorithms now work on identical input.

    // Initializes two comparison counters to zero.
    long long comp1 = 0, comp2 = 0;

    // Calls deterministic Quick Sort on array a.
    // low = 0 (first index), high = n-1 (last index).
    quickSort(a, 0, n - 1, comp1);

    // Calls Randomized Quick Sort on array b.
    randomizedQuickSort(b, 0, n - 1, comp2);

    // Displays the deterministic Quick Sort result.
    cout << "Deterministic Quick Sort: ";
    display(a);

    // Displays the number of comparisons made by deterministic Quick Sort.
    cout << "Comparisons: " << comp1 << "\n";

    // Displays the randomized Quick Sort result.
    cout << "Randomized Quick Sort: ";
    display(b);

    // Displays the number of comparisons made by randomized Quick Sort.
    cout << "Comparisons: " << comp2 << "\n";

    return 0; // Indicates successful program termination.
}


/*
TIME COMPLEXITY:

1. Average Case: O(n log n)
   - The array is divided into approximately equal subarrays.
   - There are approximately log n levels of recursion.
   - Each level performs O(n) partitioning work.

2. Worst Case: O(n^2)
   - Occurs when the pivot repeatedly becomes the smallest
     or largest element.
   - One partition contains n-1 elements and the other is empty.

SPACE COMPLEXITY:

1. Average: O(log n)
   - Recursion stack for approximately balanced partitions.

2. Worst Case: O(n)
   - Recursion stack when partitions are highly unbalanced.

RANDOMIZED QUICK SORT:

- Selects a random pivot instead of always choosing the last element.
- Reduces the likelihood of repeatedly getting unbalanced partitions.
- Expected time complexity: O(n log n).
- Worst-case time complexity is still O(n^2).
*/

/*
EXAMPLE:

Input:
Number of elements = 5
Array = 5 2 8 1 3

A. DETERMINISTIC QUICK SORT

Step 1:
Select the last element as pivot.
Pivot = 3

Array:
5 2 8 1 3

Step 2:
Compare each element with pivot 3.
Elements smaller than or equal to 3 go left.
Elements greater than 3 go right.

After partitioning:
2 1 3 5 8
    ^
  Pivot

Step 3:
Recursively sort left and right subarrays.

Final sorted array:
1 2 3 5 8


B. RANDOMIZED QUICK SORT

Step 1:
Select a random element as pivot.
For example, pivot = 5.

Step 2:
Move the selected pivot to the last position.

Step 3:
Partition the array around the pivot.

Step 4:
Recursively sort the left and right subarrays.

Final sorted array:
1 2 3 5 8


Output:
Deterministic Quick Sort: 1 2 3 5 8
Randomized Quick Sort: 1 2 3 5 8

Explanation:
- Deterministic Quick Sort always selects the last element as pivot.
- Randomized Quick Sort selects a random pivot.
- Both use partitioning and recursion.
- Randomized Quick Sort reduces the likelihood of
  repeatedly getting unbalanced partitions.
*/