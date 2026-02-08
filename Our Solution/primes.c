#include "primes.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>

// Optimized prime check
int is_prime(int n)
{
    if(n <= 1) return 0;
    if(n <= 3) return 1;
    if(n%2 == 0 ||n%3 == 0) return 0;
    for(int i=5; i*i<=n;i+= 6)
    {
        if (n%i == 0||n%(i+2) == 0)return 0;
    }
    return 1;
}

// Writes primes to a file descriptor
void solve_range(int start, int end, int fd)
{
    char buffer[32];
    for (int i = start; i <= end; i++)
    {
        if (is_prime(i))
        {
            int len = sprintf(buffer, "%d\n", i);
            write(fd, buffer, len);
        }
    }
}