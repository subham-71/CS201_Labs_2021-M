//Name: Subham Subhasis Sahoo
//Entry No. : 2020CSB1317
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define ll long long

void heap_push(int heap[], int n, int *size, int data)
{
    if (*size >= n)
    {
        printf("overflow \n");
        return;
    }

    heap[*size] = data;
    int current = *size;
    while ((current > 0) && (heap[(current - 1) / 2] > heap[current])) //checking and swapping to build min heap
    {
        int temp = heap[(current - 1) / 2];
        heap[(current - 1) / 2] = heap[current];
        heap[current] = temp;

        current = (current - 1) / 2;
    }
    *size += 1;
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
            if (heap[2 * current + 1] < heap[2 * current + 2])
            {
                child = 2 * current + 1;
            }
            else
            {
                child = 2 * current + 2;
            }
        }
        if (heap[current] > heap[child]) //checking and swapping to build a min heap
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

    int heap[k];
    int size = 0;
    printf("Enter %d elements each separated by a space \n", n);
    int arr[n];

    for (int i = 0; i < k; i++)
    {
        scanf("%d", &arr[i]);
        heap_push(heap, n, &size, arr[i]);
        // show_heap(heap, size);
    }
    for (int i = k; i < n; i++)
    {
        ll root = heap_pop(heap, &size);
        ll y = root;
        scanf("%d", &arr[i]);
        ll x = arr[i];
        if (y > x)
        {
            heap_push(heap, n, &size, y);
        }
        else
        {
            heap_push(heap, n, &size, x);
        }
    }

    ll k_max = heap_pop(heap, &size);
    printf("%d th largest element is %d", k, k_max);

    return 0;
}