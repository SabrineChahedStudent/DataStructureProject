
#include "HashTable.hpp"
#include <iostream>
using namespace std;

/**
 * Internal method to test if a positive number is prime.
 * Not an efficient algorithm.
 */
bool isPrime( int n )
{
    if( n == 2 || n == 3 )
        return true;

    if( n == 1 || n % 2 == 0 )
        return false;

    for( int i = 3; i * i <= n; i += 2 )
        if( n % i == 0 )
            return false;

    return true;
}

/**
 * Internal method to return a prime number at least as large as n.
 * Assumes n > 0.
 */
int nextPrime( int n )
{
    if( n % 2 == 0 )
        ++n;

    for( ; !isPrime( n ); n += 2 )
        ;

    return n;
}

int previousPrime( int num1 )
{
    int ctr = 0;

    for (int n = num1 - 1; n >= 1; n--)
    {
        for (int m = 2; m < n; m++)
        {
            if (n % m == 0)
                ctr++;
        }
        if (ctr == 0)
        {
            if (n == 1)
            {
               ;
                break;
            }
            return n;
            break;
        }
        ctr = 0;

        }

}

