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
            while (temp != NULL)
            {
                printf("%d ", temp->num);
                temp = temp->next;
            }
            printf("\n");
        }
    }
}
struct node *f = NULL;
struct node *r = NULL;
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
int isEmpty()
{
    if (f == NULL)
    {
        return 1;
    }
    else
        return 0;
}
int dequeue()
{
    int val = -1;
    struct node *ptr = f;
    if (f == NULL)
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

void bfs(node_arr *graph, int index, int m)
{
    int color[m];
    int p[m];
    int d[m];
    for (int i = 0; i < m; i++)
    {
        color[i] = 0;
        p[i] = -1;
        d[i] = -1;
    }

    struct node *temp = graph[index].head;
    d[index] = 0;
    color[index] = 1;
    while (temp != NULL)
    {
        enqueue(temp->num);
        color[temp->num] = 1;
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
                color[x->num] = 1;
                d[x->num] = d[dequeued] + 1;
                p[x->num] = dequeued;
                enqueue(x->num);
            }
            x = x->next;
        }
        color[dequeued] = 2;
    }

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
    printf("Enter 1 for directed 0 for undirected \n");
    scanf("%d", &c);
    if (c == 1)
    {
        printf("Enter one by one your edges for your directed graph \n");
        while (1)
        {
            int x, y;
            scanf("%d", &x);
            if (x == -1)
            {
                printf("Your directed graph is as follows : \n");
                display(arr, m);
                break;
            }
            scanf("%d", &y);
            insert(arr, x, y, m);
        }
    }
    if (c == 0)
    {
        printf("Enter one by one your edges for your undirected graph \n");
        while (1)
        {
            int x, y;
            scanf("%d", &x);
            if (x == -1)
            {
                printf("Your undirected graph is as follows : \n");
                display(arr, m);
                break;
            }
            scanf("%d", &y);
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