
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

using namespace std;

// Function to partition the array using the first element as pivot
int deterministicPartition(vector<int> &arr, int low, int high) {

    int pivot = arr[low]; // Select the first element as pivot
    int left = low + 1;   // Pointer starts from the second element
    int right = high;     // Pointer starts from the last element

    while (true) {

        // Move left pointer until an element greater than pivot is found
        while (left <= right && arr[left] <= pivot) {
            left++;
        }

        // Move right pointer until an element smaller than pivot is found
        while (left <= right && arr[right] >= pivot) {
            right--;
        }

        // If pointers cross, partitioning is complete
        if (left > right) {
            break;
        }

        // Swap elements that are on the wrong sides of the pivot
        swap(arr[left], arr[right]);
    }

    // Place pivot in its correct sorted position
    swap(arr[low], arr[right]);

    // Return the final position of the pivot
    return right;
}

// Recursive function to perform Deterministic Quick Sort
void deterministicQuickSort(vector<int> &arr, int low, int high,
                            int &comparisons, int &swaps) {

    // Continue sorting if the subarray has more than one element
    if (low < high) {

        // Partition the array and get the pivot position
        int pivotIndex = deterministicPartition(arr, low, high);

        // Add the estimated number of comparisons in this partition
        comparisons += (high - low);

        // Count the two swaps performed during partitioning
        swaps += 2;

        // Recursively sort the left subarray
        deterministicQuickSort(arr, low, pivotIndex - 1, comparisons, swaps);

        // Recursively sort the right subarray
        deterministicQuickSort(arr, pivotIndex + 1, high, comparisons, swaps);
    }
}

// Function to partition the array using a randomly selected pivot
int randomizedPartition(vector<int> &arr, int low, int high) {

    // Select a random index between low and high
    int pivotIndex = low + rand() % (high - low + 1);

    // Move the randomly selected pivot to the first position
    swap(arr[low], arr[pivotIndex]);

    int pivot = arr[low]; // Store the pivot value
    int left = low + 1;   // Pointer starts from the second element
    int right = high;     // Pointer starts from the last element

    while (true) {

        // Move left pointer until an element greater than pivot is found
        while (left <= right && arr[left] <= pivot) {
            left++;
        }

        // Move right pointer until an element smaller than pivot is found
        while (left <= right && arr[right] >= pivot) {
            right--;
        }

        // Stop when the pointers cross each other
        if (left > right) {
            break;
        }

        // Swap elements that are on the wrong sides of the pivot
        swap(arr[left], arr[right]);
    }

    // Place pivot in its correct sorted position
    swap(arr[low], arr[right]);

    // Return the final position of the pivot
    return right;
}

// Recursive function to perform Randomized Quick Sort
void randomizedQuickSort(vector<int> &arr, int low, int high,
                         int &comparisons, int &swaps) {

    // Continue sorting if the subarray has more than one element
    if (low < high) {

        // Partition the array using a random pivot
        int pivotIndex = randomizedPartition(arr, low, high);

        // Add the estimated number of comparisons in this partition
        comparisons += (high - low);

        // Count the two swaps performed during partitioning
        swaps += 2;

        // Recursively sort the left subarray
        randomizedQuickSort(arr, low, pivotIndex - 1, comparisons, swaps);

        // Recursively sort the right subarray
        randomizedQuickSort(arr, pivotIndex + 1, high, comparisons, swaps);
    }
}

// Function to display all elements of the array
void printArray(const vector<int> &arr) {

    // Traverse and print each element
    for (int num : arr) {
        cout << num << " ";
    }

    cout << endl;
}

int main() {

    // Initialize random number generator using current time
    srand(time(0));

    int n;

    // Get the number of elements from the user
    cout << "Enter the number of elements: ";
    cin >> n;

    // Create an array of size n
    vector<int> arr1(n);

    // Accept array elements from the user
    cout << "Enter elements: \n";
    for (int i = 0; i < n; i++) {
        cin >> arr1[i];
    }

    // Create a copy of the original array for randomized Quick Sort
    vector<int> arr2 = arr1;

    int ch;

    // Display menu repeatedly until the user chooses Exit
    while (1) {

        // Initialize comparison and swap counters to zero
        int comparisonsDet = 0, swapsDet = 0;
        int comparisonsRand = 0, swapsRand = 0;

        cout << "1.Deterministic Quick Sort\n2.Randomized Quick Sort\n3.Exit\n";
        cout << "Enter your choice: ";
        cin >> ch;

        switch (ch) {

        case 1:

            // Display the original array
            cout << "Original array for deterministic quick sort:\n";
            printArray(arr1);

            // Perform Deterministic Quick Sort
            deterministicQuickSort(arr1, 0, arr1.size() - 1,
                                   comparisonsDet, swapsDet);

            // Display the sorted array
            cout << "Sorted array (Deterministic):\n";
            printArray(arr1);

            // Display the number of comparisons
            cout << "Deterministic Quick Sort Comparisons: "
                 << comparisonsDet << endl;

            // Display the number of swaps
            cout << "Deterministic Quick Sort Swaps: "
                 << swapsDet << endl;

            break;

        case 2:

            // Display the original array
            cout << "\nOriginal array for randomized quick sort:\n";
            printArray(arr2);

            // Perform Randomized Quick Sort
            randomizedQuickSort(arr2, 0, arr2.size() - 1,
                               comparisonsRand, swapsRand);

            // Display the sorted array
            cout << "Sorted array (Randomized):\n";
            printArray(arr2);

            // Display the number of comparisons
            cout << "Randomized Quick Sort Comparisons: "
                 << comparisonsRand << endl;

            // Display the number of swaps
            cout << "Randomized Quick Sort Swaps: "
                 << swapsRand << endl;

            break;

        case 3:

            // Exit the program
            exit(0);
            break;
        }
    }

    return 0;
}
