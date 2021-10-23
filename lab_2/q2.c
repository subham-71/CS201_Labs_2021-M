//Name: Subham Subhasis Sahoo
//Entry No.: 2020csb1317

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
int push(int arr[], int x, int y, int *a, int *b)
{
    int condition = 0;
    if (y == 1)
    {
        if ((*a) < (*b) - 1)
        {
            (*a)++;
            arr[*a] = x;
        }
        else
        {
            condition++;
            printf("\n Can't push!! Array is full \n\n");
        }
    }
    else if (y == 2)
    {
        if ((*a) < (*b) - 1)
        {
            (*b)--;
            arr[(*b)] = x;
        }
        else
        {
            condition++;
            printf("\n Can't push!! Array is full \n\n");
        }
    }
    return condition;
}
int pop(int arr[], int n, int y, int *a, int *b)
{
    int condition = 0;
    if (y == 1)
    {

        if ((*a) >= 0)
        {
            int popp = arr[(*a)];
            arr[(*a)] = 0;
            (*a)--;

            printf("\n %d is being popped from Stack 1 \n\n", popp);
        }
        else
        {
            printf("\n Can't pop!! Stack 1 is Empty \n\n");
            condition++;
        }
    }
    else if (y == 2)
    {
        // Checking underflow condition

        if ((*b) < n)
        {
            int popped_element = arr[(*b)];
            arr[(*b)] = 0;
            (*b)++;

            printf("\n %d is being popped from Stack 2\n\n", popped_element);
        }
        else
        {
            printf("\n Can't pop!! Stack 2 is Empty!\n\n");
            condition++;
        }
    }
    return condition;
}
int main()
{
    printf("Enter size of array \n");
    int n;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        arr[i] = 0;
    }
    printf("\nArray of size %d is initialised with all elements 0. If you push an element, 0 will be replaced by that element. If you pop an element ,then that element would be removed from the array and 0 will take its position. \n \n", n);
    int top_a = -1;
    int top_b = n;
    while (1)
    {
        printf("----------------------------------------------------------------\nENTER\n1 to push\n2 to pop\n3 to show current array\n-1 to quit and show final array\n----------------------------------------------------------------\n\n");
        int z;
        scanf("%d", &z);
        if (z == 1)
        {
            printf("Enter 1 to push in stack 1 , 2 to push in stack 2\n");
            int pushq;
            scanf("%d", &pushq);
            printf("Enter number to push\n");
            int num;
            scanf("%d", &num);
            int condition = push(arr, num, pushq, &top_a, &top_b);
            if (condition)
            {
                break;
            }
            printf("\n Pushed %d in Stack %d\n\n", num, pushq);
        }
        else if (z == 2)
        {
            printf("Enter 1 to pop from Stack 1 or 2 to pop from Stack 2\n");
            int popq;
            scanf("%d", &popq);

            int condition = pop(arr, n, popq, &top_a, &top_b);
            if (condition)
            {
                break;
            }
        }
        else if (z == 3)
        {
            printf("\n");
            printf("Printing current  array \n");
            for (int i = 0; i < n; i++)
            {
                printf("%d  ", arr[i]);
            }
            printf("\n");
            printf("\n\n");
        }
        else
        {
            break;
        }
    }
    printf("\n");
    printf("Printing the final array \n");
    for (int i = 0; i < n; i++)
    {
        printf("%d  ", arr[i]);
    }
    return 0;
}

/* IMPLEMENTATION OF THREE STACKS USING ONE ARRAY

P.S:- Here by pointer I mean a variable to maintain indexes.

We can maintain three top pointers for three stacks. 
One at the beginning of the array
One at the end of the array and 
the third one at the middle of the array.

Stack-1(A):
If we want to push an element in stack 1,then we will simply push it to the next block at the beginning of the array and move the first top pointer forward.

Stack-2(B):
If we want to push an element in Stack-2,then we will wimply push it to the previous block at the end of the array and move the second top pointer backward.

Stack-3(C):
Stack 3 top pointer will be at mid
We will check the difference between the indexes of the Stack-3 Top pointer and the other stacks' top pointers.Then, we will store element in the the next block of that direction(left or right) in which the difference between the top pointers at that point point of time is maximum. 
If the memory blocks get filled up in the direction we are filling in (Top pointer of A or B- Top pointer of C ==1 ) 
then we make our top pointer point to "mid-1" if there is space available. In this way our stack 3 can grow in whichever way maximum spaces are available.


*/