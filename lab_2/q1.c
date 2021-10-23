//Name: Subham Subhasis Sahoo
//Entry No.: 2020csb1317
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
struct Node
{
    struct Node *next;
    int data;
};
struct Node *insert(struct Node *head, int x)
{
    if (head == NULL)
    {
        head->data = x;
        printf("done");
        return head;
    }
    else
    {
        struct Node *n = (struct Node *)malloc(sizeof(struct Node));
        n->data = x;
        n->next = head;
        head = n;
        return head;
    }
}
struct Node *find(struct Node *head, int x)
{
    struct Node *ptr = head;
    struct Node *q = head;
    struct Node *m = head;
    if ((head->data) == x)
    {
        return head;
    }
    else
    {
        int count = 0;
        while (ptr->next != NULL)
        {
            if ((ptr->next->data) == x)
            {
                m = ptr->next;
                q = ptr->next->next;
                ptr->next = q;
                m->next = head;
                head = m;
                count++;
                return head;
                break;
            }
            ptr = ptr->next;
        }
        if (!count)
        {
            printf("NOT FOUND %d in list \n", x);
            return head;
        }
    }
}
void display(struct Node *head)
{
    struct Node *ptr = head;
    while (ptr->next != NULL)
    {
        printf("Element : %d \n", ptr->data);
        ptr = ptr->next;
    }
}
int main()
{
    struct Node *tail = NULL;
    tail = (struct Node *)malloc(sizeof(struct Node));
    struct Node *head;
    head = (struct Node *)malloc(sizeof(struct Node));
    tail->next = NULL;
    head = tail;
    while (1)
    {
        printf("----------------------------------------------------------------\nENTER\n1 if you want to insert a number\n2 if you want to find a number\n3 if you want to display the current linked list\n-1 if you want to quit the program\n----------------------------------------------------------------\n\n");
        int test;
        scanf("%d", &test);
        if (test == 1)
        {
            printf("Enter the number you want to insert in the unregular linked list \n");
            int x;
            scanf("%d", &x);
            head = insert(head, x);
        }
        else if (test == 2)
        {
            printf("Enter the number you want to find \n");
            int y;
            scanf("%d", &y);
            head = find(head, y);
            printf("After finding element, the linked list \n \n");
            display(head);
        }
        else if (test == 3)
        {
            printf("Displaying the current Linked List \n \n");
            display(head);
        }
        else
        {
            break;
        }
    }

    return 0;
}

//Questions
/*

Q. 1a
Ans: O(N)
Explanation: 
To insert one node, we will be consuming O(1).
We will be inserting here N nodes each of O(1) complexity, Ans: so O(N).

Q. 1b
Ans: O(N+m)
Explanation:
To access(find) the nth and n-1th elements we will take O(N) time. Then it will come to the beginning of the list. So it can accessed it constant time (O(1)). So now we will access them m-2 times. Ignoring constant, it will be O(N+m)
     
Q.1c
Ans: O(n)* ((n+k)/2)
Explanation:
If we access the nth element (k+n-i = k as i=n here) times , then it will be k(O(n)).
Likewise we will have to do a sum,
O(n)*k + O(n-1)*(k+1) + O(n-1)*(k+2)...
On solving it, we arrive at O(n)*((n+k)/2)


*/