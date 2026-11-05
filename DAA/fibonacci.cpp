
#include <iostream>              // Header file for input and output.
using namespace std;

// Recursive function to calculate the nth Fibonacci number.
int fibonacci(int n) {

  if (n <= 1)                    // Base condition: checks if n is 0 or 1.
    return n;                    // Returns 0 or 1 and stops recursion.

  // Calls the same function for the previous two numbers
  // and adds their results to calculate the current number.
  return fibonacci(n - 1) + fibonacci(n - 2);
}


// Function to print Fibonacci series using recursion.
void recursive(int n) {

  // Loop runs from 0 to n-1 to print n Fibonacci numbers.
  for (int i = 0; i < n; ++i)

    // Calls fibonacci() for each position and prints the result.
    cout << fibonacci(i) << " ";
}


// Function to print Fibonacci series using iteration.
void iterative(int n) {

  int a1 = 0;                    // Stores the first Fibonacci number.
  int a2 = 1;                    // Stores the second Fibonacci number.

  // Prints the first two Fibonacci numbers.
  cout << a1 << " " << a2 << " ";

  // Starts from 2 because 0 and 1 are already printed.
  // Continues until n Fibonacci numbers are generated.
  for (int i = 2; i < n; i++) {

    int a3 = a2 + a1;            // Calculates the next Fibonacci number.

    a1 = a2;                     // Updates a1 with the previous a2 value.
    a2 = a3;                     // Updates a2 with the newly calculated value.

    cout << a2 << " ";           // Prints the newly calculated number.
  }

  cout << endl;                  // Moves the cursor to the next line.
}


// Main function: execution starts here.
int main() {

  recursive(10);                 // Prints 10 Fibonacci numbers using recursion.

  cout << endl;                  // Moves to the next line.

  iterative(10);                 // Prints 10 Fibonacci numbers using iteration.

  return 0;                      // Indicates successful program termination.
}

/*
TIME COMPLEXITY:

1. Recursive Fibonacci:
   O(2^n) - Repeatedly calculates the same Fibonacci values.

2. Iterative Fibonacci:
   O(n) - Uses a loop that runs n-2 times.

SPACE COMPLEXITY:

1. Recursive Fibonacci:
   O(n) - Uses the function call stack.

2. Iterative Fibonacci:
   O(1) - Uses only three variables (a1, a2, a3).
*/
