
#include <iostream>              // Header file used for input and output operations.
using namespace std;             // Allows us to use cin and cout without writing std::.

// Recursive function to calculate the nth Fibonacci number.
int fibonacciRecursive(int n) {

    if (n <= 1)                  // Base condition: checks whether n is 0 or 1.
        return n;                // Returns n directly (0 or 1) and stops recursion.

    // Calls the same function for the previous two Fibonacci positions.
    // Adds both returned values to calculate the current Fibonacci number.
    return fibonacciRecursive(n - 1) + fibonacciRecursive(n - 2);
}

// Iterative function to calculate the nth Fibonacci number using a loop.
int fibonacciIterative(int n) {

    if (n <= 1)                  // Checks the base cases 0 and 1.
        return n;                // Directly returns n if it is 0 or 1.

    int a = 0, b = 1;             // Initializes the first two Fibonacci numbers.

    // Loop starts from 2 because 0 and 1 are already initialized.
    // Continues until the nth Fibonacci number is calculated.
    for (int i = 2; i <= n; i++) {

        int c = a + b;            // Calculates the next Fibonacci number.

        a = b;                    // Updates a with the previous value of b.

        b = c;                    // Updates b with the newly calculated number.
    }

    return b;                     // Returns the nth Fibonacci number.
}

// Main function: execution of the program starts here.
int main() {

    int n;                        // Declares an integer variable to store user input.

    cout << "Enter n: ";          // Asks the user to enter the number of terms.
    cin >> n;                     // Reads the input entered by the user.

    // Checks whether the entered number is negative.
    if (n < 0) {

        cout << "Please enter a non-negative number.\n";
        // Displays an error message if the input is negative.

        return 0;                 // Terminates the program.
    }

    cout << "Recursive Fibonacci: "; // Displays the recursive series heading.

    // Loop runs from 0 to n to print n+1 Fibonacci numbers.
    for (int i = 0; i <= n; i++)

        // Calls the recursive function for each value of i
        // and prints the returned Fibonacci number.
        cout << fibonacciRecursive(i) << " ";

    cout << "\nIterative Fibonacci: ";
    // Moves to a new line and displays the iterative series heading.

    // Loop runs from 0 to n to print the iterative Fibonacci series.
    for (int i = 0; i <= n; i++)

        // Calls the iterative function for each value of i
        // and prints the returned Fibonacci number.
        cout << fibonacciIterative(i) << " ";

    cout << "\n";                 // Prints a new line after the output.

    return 0;                     // Indicates successful program termination.
}

/*
TIME COMPLEXITY:

1. Recursive Fibonacci: O(2^n)
   - Each function call generates two more recursive calls.
   - Many Fibonacci values are calculated repeatedly.
   - Therefore, execution time grows exponentially.

2. Iterative Fibonacci: O(n)
   - The for loop runs approximately n times.
   - Each iteration performs a constant number of operations.

AUXILIARY SPACE COMPLEXITY:

1. Recursive Fibonacci: O(n)
   - Recursive calls are stored in the call stack.
   - Maximum recursion depth is proportional to n.

2. Iterative Fibonacci: O(1)
   - Uses only three variables: a, b and c.
   - No additional array or recursive stack is required.
*/
/*
EXAMPLE:

Input:
n = 5

Fibonacci calculation:
F(0) = 0
F(1) = 1
F(2) = 0 + 1 = 1
F(3) = 1 + 1 = 2
F(4) = 1 + 2 = 3
F(5) = 2 + 3 = 5

Output:
Recursive Fibonacci: 0 1 1 2 3 5
Iterative Fibonacci: 0 1 1 2 3 5

Explanation:
- Recursive approach calls the same function repeatedly.
- Iterative approach uses a loop and three variables.
- Both produce the same Fibonacci series.
*/