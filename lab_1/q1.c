//Name: Subham Subhasis Sahoo
//Entry No : 2020CSB1317
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    int n;
    printf("Enter how many numbers: \n");
    scanf("%d", &n);
    float arr[n];
    float avg, stddeviation;
    float sum = 0, sqr = 0;

    printf("Input %d numbers: \n", n);
    for (int i = 0; i < n; i++)
    {
        scanf("%f", &arr[i]);
        sum += arr[i];
    }
    avg = sum / (float)n;
    float y;
    for (int i = 0; i < n; i++)
    {
        y = arr[i] - avg;
        sqr += y * y;
    }
    float x;
    x = sqr / (float)n;
    stddeviation = sqrt(x);
    printf("Average of numbers : %f\n", avg);
    printf("Standard deviation : %f\n", stddeviation);

    return 0;
}