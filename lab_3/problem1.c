//Subham Subhasis Sahoo
//2020CSB1317

//Description of the functions at the end of the code from line no. 226
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
struct Node
{
    int data;
    struct Node *next;
};

struct Node *add_node(struct Node *head, int x)
{
    if (head == NULL)
    {
        struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
        temp->data = x;
        temp->next = NULL;
        return temp;
    }
    else
    {
        struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
        struct Node *ptr = head;
        temp->data = x;
        while (ptr->next)
        {
            ptr = ptr->next;
        }
        ptr->next = temp;
        temp->next = NULL;
        return head;
    }
}

struct Node *add_node_cycle(struct Node *head, int y)
{
    if (y == 0)
    {
        struct Node *ptr = head;
        while (ptr->next != NULL)
        {
            ptr = ptr->next;
        }
        ptr->next = head;
        return head;
    }
    else
    {
        struct Node *ptr = head;
        struct Node *p = head;
        for (int i = 0; i < y; i++)
        {
            ptr = ptr->next;
        }
        while (p->next != NULL)
        {
            p = p->next;
        }
        p->next = ptr;
        return head;
    }
}

void display(struct Node *head)
{
    int i = 0;
    while ((head != NULL) && (i <= 20))
    {
        printf("Element : %d \n", head->data);
        head = head->next;
        i++;
    }
}

void DetectCycle(struct Node *head)
{
    struct Node *ptr = head;

    struct Node *first = ptr;
    struct Node *second = ptr;
    int flag = 0;
    while (1)
    {
        if (!(first && second && second->next))
        {
            break;
        }
        first = first->next;
        second = second->next->next;
        if (first == second)
        {
            flag = 1;
            break;
        }
    }
    if (flag)
    {
        printf("The linked list contains CYCLE !! \n");
    }
    else
    {
        printf("The linked list contains no cycle !! \n");
    }
}
void DetectFindStart(struct Node *head)
{
    struct Node *ptr = head;

    struct Node *first = ptr;
    struct Node *second = ptr;
    struct Node *common;
    int flag = 0;
    int count = 0;
    while (1)
    {
        if (!(first && second && second->next))
        {
            break;
        }
        first = first->next;
        second = second->next->next;
        if (first == second)
        {
            common = first;
            flag = 1;
            break;
        }
    }
    if (!flag)
    {
        printf("The linked list contains no cycle !!");
        return;
    }

    struct Node *loop = common;

    while (1)
    {

        loop = loop->next;
        count++;
        if (loop == common)
        {
            printf("Length of cycle : %d \n", count);
            break;
        }
    }

    int head_dis = 0;
    struct Node *head_dis_a = ptr;
    struct Node *head_dis_b = common;

    while (1)
    {
        if (head_dis_a == head_dis_b)
        {
            printf("Distance from head is :  %d \n", head_dis);
            break;
        }

        head_dis_a = head_dis_a->next;
        head_dis_b = head_dis_b->next;
        head_dis++;
    }
}

int main()
{

    struct Node *head = NULL;
    printf("------------------------------------------------------------------- \n");
    printf("Enter\nY to enter a linked list with cycle \nN to enter a linked list with no cycle\nE to exit \n");
    printf("------------------------------------------------------------------- \n");
    char c;
    scanf("%c", &c);
    if (c == 'N' || c == 'n')
    {
        printf("Enter the size (number of edges) of linked list without cycle: ");
        int edges;
        scanf("%d", &edges);
        if (edges == 0)
        {
            printf("No Linked List created as the size is 0. \n");
        }
        for (int i = 0; i <= edges; i++)
        {
            head = add_node(head, (i + 1));
        }
        // display(head);
        DetectCycle(head);
    }
    else if (c == 'Y' || c == 'y')
    {
        printf("Enter the length of cycle in the linked list: ");
        int cycle;
        scanf("%d", &cycle);

        printf("Enter the distance (number of edges) of the start node of the cycle from the head of the linked list: ");
        int edges;
        scanf("%d", &edges);

        if (cycle < 2)
        {
            printf("Length of cycle can't be less than 2. \n");
            printf("Distance from head is not defined. \n");
        }
        else
        {
            for (int i = 0; i < edges + cycle; i++)
            {
                head = add_node(head, (i + 1));
            }

            head = add_node_cycle(head, edges);
            // display(head);
            DetectFindStart(head);
        }
    }

    return 0;
}

/*
WORKING OF THE DetectCycle FUNCTION

I am maintaining two pointers here,both initially pointing to the head of the linked list. 
Then I am moving forward one pointer by one step and the other pointer by two steps.

If there is a cycle.
then none of these would become null. Once the pointers enter into the cycle, they continue to rotate around it only.
At some point of time (after few or several iterations in the cycle),  these two pointers will be pointing
at the same node in the cycle. 
So checking this condition, we can detect a cycle.

If there is not a cycle, 
then these pointers will go outside our linked list at some point of time and thus the we can detect that there is no cycle.

WORKING OF THE DetectFindStart FUNCTION

We have to find the length of the cycle and the distance of the starting node of cycle from head node.

LENGTH OF THE CYCLE

As mentioned above, If there is a cycle, the two pointers will be eventually pointing to the same node inside
the cycle(can be any node in the cycle).After detecting this common node, we can point it through another pointer.
Then we move forward this pointer(pointer pointing to the common node) by one step untill it reaches the common node again.
(As it will be moving inside the cycle, it has to reach the common node at some point of time.)

The number of steps taken by this pointer to reach  the common pointer again is the Length of the cycle.

DISTANCE OF STARTING NODE FROM THE HEAD NODE

I observed that the starting node of the cycle is equidistant from the head node and the common node. So, we again point to the
head of the list with one pointer and point to the common node(as mentioned above) of the list with another pointer.

Then we start moving the head pointer(pointer to head) forward and the common node pointer(pointer to common node) 
forward by one step untill they point to the same node. This node is the node that is the starting point of the cycle.

Then we calculate the steps taken by the head pointer to reach this same node, and this will give us our 
distance of the starting node of the cycle from the head of the linked list.

*/
