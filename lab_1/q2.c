//Name: Subham Subhasis Sahoo
//Entry No : 2020CSB1317
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

void func(unsigned int n)
{
    unsigned int count = 0;
    while (n)
    {
        count += n & 1;
        n >>= 1;
    }
    printf("%d", count);
}

int main()
{
    int n;
    scanf("%d", &n);
    func(n);

    return 0;
}