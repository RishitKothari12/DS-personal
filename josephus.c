#include <stdio.h>

// Function to find the position of the last person standing
int josephus(int n, int k) {
    // Base case: If there's only one person left
    if (n == 1) {
        return 0; // Position is 0 (zero-based index)
    } else {
        // Recursive case: Adjust the position using modulo operation
        return (josephus(n - 1, k) + k) % n;
    }
}

int main() {
    int n, k;
    
    // Input: Number of people (n) and step size (k)
    printf("Enter the number of people (n): ");
    scanf("%d", &n);
    printf("Enter the step size (k): ");
    scanf("%d", &k);
    
    // Solve the Josephus problem (convert to 1-based index)
    int survivor = josephus(n, k) + 1;

    // Output: The position of the last person standing
    printf("The position of the survivor is: %d\n", survivor);

    return 0;
}
