#include <iostream>
using namespace std;

int fibonacciRecursive(int n) {
    if (n <= 1)
        return n;
    return fibonacciRecursive(n - 1) + fibonacciRecursive(n - 2);
}

int fibonacciIterative(int n) {
    if (n <= 1)
        return n;

    int a = 0, b = 1;
    for (int i = 2; i <= n; i++) {
        int c = a + b;
        a = b;
        b = c;
    }
    return b;
}

int main() {
    int n;
    cout << "Enter n: ";
    cin >> n;

    if (n < 0) {
        cout << "Please enter a non-negative number.\n";
        return 0;
    }

    cout << "Recursive Fibonacci: ";
    for (int i = 0; i <= n; i++)
        cout << fibonacciRecursive(i) << " ";

    cout << "\nIterative Fibonacci: ";
    for (int i = 0; i <= n; i++)
        cout << fibonacciIterative(i) << " ";

    cout << "\n";
    return 0;
}

/*
Time complexity:
- Recursive Fibonacci: O(2^n) (more precisely exponential)
- Iterative Fibonacci: O(n)

Auxiliary space complexity:
- Recursive: O(n) maximum call-stack depth for one call
- Iterative: O(1)
*/
