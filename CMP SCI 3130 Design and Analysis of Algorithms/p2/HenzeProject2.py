#Adam Henze
#Computer Science 3130
#Project2
#Written in python 3.10

import time
import math

def maxDirect():
    # Set the data type limit for a 64-bit signed integer
    longint = 9223372036854775807

    # Calculate the golden ratio
    phi = (1 + math.sqrt(5)) / 2

    # Calculate the largest problem size without overflow
    n_max = int((math.log(longint * math.sqrt(5) + 0.5) / math.log(phi)))

    return n_max

def maxOverflow():
    knownF = {0: 0, 1: 1}
    # binary exponentiation for long int value
    max_value = 2 ** 63 - 1

    # begin loop to calculate overflow
    nmax_overflow = 1
    while True:
        try:
            F = knownF[nmax_overflow] + knownF[nmax_overflow - 1]
            # because python does not handle overflows similarly to C, we check to see if we pass the value of longint
            # the special property we would normally exploit is to check for when the value overflows to negative then return i - 1
            if F > max_value:
                break
            knownF[nmax_overflow + 1] = F  # Fix: Update the next Fibonacci number in the dictionary
            nmax_overflow += 1
        except KeyError:
            break

    return nmax_overflow

def fibDynamic(n):
    #use set to check for known values
    #check if in set
    if n in knownF and knownF[n] > 0:
        return knownF[n]

    # base conditions
    if n - 1 == 0:
        return 0
    elif n - 1 == 1:
        return 1

    elif n - 1 > 1:
        knownF[n] = fibDynamic(n - 1) + fibDynamic(n - 2)
        return knownF[n]

def fibIterative(n):
    p0 = 0
    p1 = 1
    swap = 0
    s = 0
    start_time = time.perf_counter()

    for i in range(n - 2):
        swap = p1
        p1 = p0 + p1
        p0 = swap

    end_time = time.perf_counter()
    elapsed_time = end_time - start_time
    print("Elapsed time: ", elapsed_time)
    return p1

def fibRecursive(n):
    if (n - 1 <= 0):
        return 0
    if (n - 1 == 1):
        return 1
    return fibRecursive(n-1) + fibRecursive(n-2);

# Main Program
if __name__ == '__main__':

# Part 1 --------------------------------------------------------------------------------------------------

    # input for N
    print("Warning: Values above 40 may result in excessive calculation times.")
    n = int(input("Please enter a value less than or equal to 40 to test for Nth Fibonacci Number\n\t#:"))

    # Recursive timing
    print("Recursive method")
    start_time = time.perf_counter()
    print(fibRecursive(n))
    end_time = time.perf_counter()
    elapsed_time = end_time - start_time
    print("Elapsed time: ", elapsed_time)

    # Dynamic timing
    knownF = {}

    print("\nDynamic Method")
    start_time = time.perf_counter()
    print(fibDynamic(n))
    end_time = time.perf_counter()
    elapsed_time = end_time - start_time
    print("Elapsed time: ", elapsed_time)

# Part 3 -------------------------------------------------------------------------------------------------------

    # iterative timing, times within function
    print("\nIterative Method")
    print(fibIterative(n))

    # iterative timing for n = 10000
    print("\nIterative Method N = 10,000")
    print(fibIterative(10000))

    nmax_direct = maxDirect()
    nmax_overflow = maxOverflow()

# Part 2 ------------------------------------------------------------------------------------------------------
    print("\nChecking for max overflow values of long int via direct calculation and overflow observation")
    print(f"Method 1 (Direct Calculation): {nmax_direct}")
    print(f"Method 2 (Overflow): {nmax_overflow}")

# We can see that the iterative and dynamic methods consistently perform better than raw recursion, with iteration being much faster

