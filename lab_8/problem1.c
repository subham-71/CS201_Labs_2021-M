// Name: Subham Subhasis Sahoo
// Entry No. : 2020CSB1317

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

// defining node structure to be used in linked lists
typedef struct node
{
    int num;
    struct node *next;
} node;

// list of linked lists
typedef struct node_arr
{
    struct node *head;
} node_arr;

// initializing all head pointers in the list to null
void init_graph(node_arr *graph, int m)
{
    for (int i = 0; i < m; i++)
    {
        graph[i].head = NULL;
    }
}

// creating a node from given number
node *create_node(int num)
{
    node *temp;
    temp = (struct node *)malloc(sizeof(struct node));
    temp->num = num;
    temp->next = NULL;
    return temp;
}

void insert(node_arr *graph, int index, int val, int m)
{
    node *temp = create_node(val);

    // chaining vertexes that are connected to a particular vertex
    if (graph[index].head == NULL)
    {
        graph[index].head = temp;
    }

    else
    {
        struct node *p = graph[index].head;
        while (p->next != NULL)
        {
            p = p->next;
        }
        p->next = temp;
        temp->next = NULL;
    }
}
void display(node_arr *graph, int m)
{
    // looping through vertexes
    for (int i = 0; i < m; i++)
    {
        struct node *temp = graph[i].head;
        if (temp == NULL)
        {
            printf("\tindex %d:\t---\n", i);
        }
        else
        {
            printf("\tindex %d:\t", i);
            struct node *temp = graph[i].head;
            // looping through vertexes that were connected to the the main vertex
            while (temp != NULL)
            {
                printf("-> %d ", temp->num);
                temp = temp->next;
            }
            printf("\n");
        }
    }
}
// queue implemented using linked list for BFS algorithm
struct node *f = NULL;
struct node *r = NULL;

// enqueue operation
void enqueue(int val)
{
    struct node *n = (struct node *)malloc(sizeof(struct node));
    if (n == NULL)
    {
        printf("Queue is Full");
    }
    else
    {
        n->num = val;
        n->next = NULL;
        if (f == NULL)
        {
            f = r = n;
        }
        else
        {
            r->next = n;
            r = n;
        }
    }
}

// is empty condition
int isEmpty()
{
    if (f == NULL)
    {
        return 1;
    }
    else
        return 0;
}

// dequeue operation
int dequeue()
{
    int val = -1;
    struct node *ptr = f;
    // checking if queue is empty or not
    if (isEmpty())
    {
        printf("Queue is Empty\n");
    }
    else
    {
        f = f->next;
        val = ptr->num;
        free(ptr);
    }
    return val;
}

// bfs algo
void bfs(node_arr *graph, int index, int m)
{
    // array to store color
    //  0 for white
    //  1 for grey
    //  2 for black
    int color[m];

    // array to store predcessor
    int p[m];

    // array to store distance
    int d[m];

    for (int i = 0; i < m; i++)
    {
        // initializing color of all nodes to white
        color[i] = 0;
        p[i] = -1;

        // initializing all distances to -1
        d[i] = -1;
    }

    // starting from source vertex
    struct node *temp = graph[index].head;
    // marking its own distance as 0
    d[index] = 0;
    // coloring it gray
    color[index] = 1;

    while (temp != NULL)
    {
        enqueue(temp->num);
        // visited node marked gray
        color[temp->num] = 1;
        // assigning distance of the node from source that got visited
        d[temp->num] = d[index] + 1;

        temp = temp->next;
    }

    while (!isEmpty())
    {
        int dequeued = dequeue();
        struct node *x = graph[dequeued].head;
        while (x != NULL)
        {
            if (color[x->num] == 0)
            {
                // visited node marked gray
                color[x->num] = 1;
                // assigning distance of the node from source that got visited
                d[x->num] = d[dequeued] + 1;
                // assigning predecessor of the node that got visited
                p[x->num] = dequeued;
                enqueue(x->num);
            }
            x = x->next;
        }
        // node with all adjacent nodes visited marked black
        color[dequeued] = 2;
    }

    // priniting all the distances
    for (int i = 0; i < m; i++)
    {
        if (d[i] == -1)
        {
            printf("Vertex %d is not reachable from source %d \n", i, index);
        }
        else
        {
            printf("Distance of vertex %d from source vertex %d is %d \n", i, index, d[i]);
        }
    }
}
int main()
{
    int m;
    printf("Enter number of vertices : ");
    scanf("%d", &m);

    node_arr *arr = (node_arr *)malloc(m * (sizeof(node_arr)));
    init_graph(arr, m);

    int c;
    printf("----------------------------------------------------\nEnter\n 1 for directed\n 0 for undirected \n----------------------------------------------------\n");
    scanf("%d", &c);
    if (c == 1)
    {
        printf("Enter one by one your edges for your directed graph and enter -1 -1 to quit giving inputs \n");
        while (1)
        {
            int x, y;
            scanf("%d", &x);
            scanf("%d", &y);
            if (x == -1 && y == -1)
            {
                printf("Your directed graph is as follows : \n");
                display(arr, m);
                break;
            }
            insert(arr, x, y, m);
        }
    }
    if (c == 0)
    {
        printf("Enter one by one your edges for your undirected graph and enter -1 -1 to quit giving inputs \n");
        while (1)
        {
            int x, y;
            scanf("%d", &x);
            scanf("%d", &y);
            if (x == -1 && y == -1)
            {
                printf("Your undirected graph is as follows : \n");
                display(arr, m);
                break;
            }
            insert(arr, x, y, m);
            insert(arr, y, x, m);
        }
    }
    printf("Enter source vertex s from where you want to run BFS algorithm on the graph you entered for the above problem : ");
    int source;
    scanf("%d", &source);
    bfs(arr, source, m);

    return 0;
}