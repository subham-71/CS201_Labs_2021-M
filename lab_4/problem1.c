//Name: Subham Subhasis Sahoo
//Entry No. : 2020CSB1317
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define ll long long

void max_heapify(int a[], int i, int size)
{
    int temp, largest, left, right, k;
    left = (2 * i + 1);    //index of left child
    right = ((2 * i) + 2); //index of right child
    if (left >= size)
        return;
    else
    {
        //finding max of children nodes
        if (left < (size) && a[left] > a[i])
            largest = left;
        else
            largest = i;
        if (right < (size) && a[right] > a[largest])
            largest = right;
        //swapping
        if (largest != i)
        {
            temp = a[i];
            a[i] = a[largest];
            a[largest] = temp;
            max_heapify(a, largest, size);
        }
    }
}

int *heap_build(int arr[], int n)
{
    int size = n;
    for (int j = n / 2; j >= 0; j--)
    {
        max_heapify(arr, j, size);
    }
    return arr;
}
int heap_pop(int heap[], int *size)
{
    if (*size <= 0)
    {
        printf("underflow \n");
        return -1;
    }
    int current = 0;
    int popped = heap[0];
    heap[0] = heap[*size - 1];
    *size -= 1;

    while ((2 * current + 1) < *size)
    {
        int child;
        if ((2 * current + 2) == *size) //if only one leaf node
        {
            child = 2 * current + 1;
        }
        else //finding max of the children nodes
        {
            if (heap[2 * current + 1] > heap[2 * current + 2])
            {
                child = 2 * current + 1;
            }
            else
            {
                child = 2 * current + 2;
            }
        }
        if (heap[current] < heap[child]) //checking and swapping to build a max heap
        {
            int temp = heap[current];
            heap[current] = heap[child];
            heap[child] = temp;

            current = child;
        }
        else
        {
            break;
        }
    }
    return popped;
}

void show_heap(int heap[], int n)
{
    for (int i = 0; i < n; ++i)
    {
        printf("%d ", heap[i]);
    }
    printf("\n");
}

int main()
{
    // freopen("input.txt", "r", stdin);

    int n, k;
    printf("Enter n \n");
    scanf("%d", &n);
    printf("Enter k \n");
    scanf("%d", &k);

    int heap[n];
    int *arr; //to receive the heapified array from the function

    printf("Enter %d elements each separated by a space \n", n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &heap[i]);
    }

    arr = heap_build(heap, n);
    // show_heap(arr, n);
    int size = n;
    int k_max;
    for (int i = 0; i < k; i++)
    {
        k_max = heap_pop(heap, &size);
    }
    printf("%d th largest element is %d \n", k, k_max);

    return 0;
}