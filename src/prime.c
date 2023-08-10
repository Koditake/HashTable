#include <math.h>

#include "prime.h"

/*
    Return whether x is prime or not
    Returns:
    1  - prime
    0  - not prime
    -1 - undefined (i.e. x < 2)
*/

int is_prime (const int x) {
    if (x < 2) {
        // no need to consider
        return -1;
    }

    if (x < 4) {
        //surely a prime
        return 1;
    }

    if (x % 2 == 0) {
        //even number
        return 0;
    }

    for (int i = 3; i <= floor(sqrt((double)x)); i += 2) {
        if (x % i == 0) {
            return 0;
        }
    }

    return 1;
}
/*
    Return the next prime after x, or x if x is prime
*/

int next_prime(int x) {
    while (is_prime(x) != 1) {
        x++;
    }

    return x;
}