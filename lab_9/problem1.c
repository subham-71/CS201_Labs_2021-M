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
// queue implemented using linked list for DFS algorithm
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
// DFS Algorithm
int time = 0;
void dfs_visit(node_arr *graph, int i, int color[], int d[], int f[], int p[])
{
    color[i] = 1;
    time = time + 1;
    d[i] = time;
    struct node *x = graph[i].head;
    while (x != NULL)
    {
        // if node not visited
        if (color[x->num] == 0)
        {
            p[x->num] = i;
            dfs_visit(graph, x->num, color, d, f, p);
        }
        x = x->next;
    }
    // node with all adjacent nodes visited marked black
    color[i] = 2;
    time = time + 1;
    f[i] = time;
}
int d_t[10000]; // temporary array to store discovery time while traversal so that it can be used globally
int f_t[10000]; // temporary array to store finished time while traversal so that it can be used globally

void dfs(node_arr *graph, int m)
{
    // array to store color
    //  0 for white
    //  1 for grey
    //  2 for black
    int color[m];

    // array to store predcessor
    int p[m];

    // array to store discovery time
    int d[m];

    // array to store finishing time
    int f[m];

    for (int i = 0; i < m; i++)
    {
        // initializing color of all nodes to white
        color[i] = 0;
        p[i] = -1;
    }

    for (int i = 0; i < m; i++)
    {
        if (color[i] == 0)
        {
            dfs_visit(graph, i, color, d, f, p);
        }
    }
    for (int i = 0; i < m; i++)
    {
        printf("index %d :   discovery time: %d  finished time: %d  \n", i, d[i], f[i]);
        d_t[i] = d[i]; // storing discovery time values in global array so as to use later
        f_t[i] = f[i]; // storing finished time values in global array so as to use later
    }
}

// functions to classify edges as tree,back,forward and cross
void edge_visit(node_arr *graph, int i, int color[], int d[], int f[], int p[])
{
    color[i] = 1;
    time = time + 1;
    d[i] = time;
    struct node *x = graph[i].head;
    while (x != NULL)
    {
        if (color[x->num] == 0)
        // Tree edge
        {
            printf("%d --> %d : Tree edge \n", i, x->num);
            edge_visit(graph, x->num, color, d, f, p);
        }
        else
        {
            // condition to check for back edge
            if (d_t[i] > d_t[x->num] && f_t[i] < f_t[x->num])
            {
                printf("%d --> %d : Back edge \n", i, x->num);
            }
            // condition to check for forward edge
            else if (d_t[i] < d_t[x->num] && f_t[i] > f_t[x->num])
            {
                printf("%d --> %d : Forward edge \n", i, x->num);
            }
            else
            {
                printf("%d --> %d : Cross edge \n", i, x->num);
            }
        }
        x = x->next;
    }
    // node with all adjacent nodes visited marked black
    color[i] = 2;
    time = time + 1;
    f[i] = time;
}
void edge(node_arr *graph, int m)
{
    // array to store color
    //  0 for white
    //  1 for grey
    //  2 for black
    int color[m];

    // array to store predcessor
    int p[m];

    // array to store discovery time
    int d[m];

    // array to store finishing time
    int f[m];

    for (int i = 0; i < m; i++)
    {
        // initializing color of all nodes to white
        color[i] = 0;
        p[i] = -1;
    }

    for (int i = 0; i < m; i++)
    {
        if (color[i] == 0)
        {
            edge_visit(graph, i, color, d, f, p);
        }
    }
}
int visited[1000][1000]; // used to print edges of undirected graphs
void edge_visit_u(node_arr *graph, int i, int color[], int d[], int f[], int p[])
{
    color[i] = 1;
    time = time + 1;
    d[i] = time;
    struct node *x = graph[i].head;
    while (x != NULL)
    {
        if (visited[i][x->num] == 0 && visited[x->num][i] == 0)
        {

            if (color[x->num] == 0)
            // Tree edge
            {
                visited[i][x->num] = 1;
                visited[x->num][i] = 1;

                printf("%d --> %d : Tree edge \n", i, x->num);
                edge_visit_u(graph, x->num, color, d, f, p);
            }
            else
            {
                visited[i][x->num] = 1;
                visited[x->num][i] = 1;
                // condition to check for back edge
                if (d_t[i] > d_t[x->num] && f_t[i] < f_t[x->num])
                {
                    printf("%d --> %d : Back edge \n", i, x->num);
                }
                // condition to check for forward edge
                else if (d_t[i] < d_t[x->num] && f_t[i] > f_t[x->num])
                {
                    printf("%d --> %d : Forward edge \n", i, x->num);
                }
                else
                {
                    printf("%d --> %d : Cross edge \n", i, x->num);
                }
            }
        }
        x = x->next;
    }
    // node with all adjacent nodes visited marked black
    color[i] = 2;
    time = time + 1;
    f[i] = time;
}
void edge_u(node_arr *graph, int m)
{
    // array to store color
    //  0 for white
    //  1 for grey
    //  2 for black
    int color[m];

    // array to store predcessor
    int p[m];

    // array to store discovery time
    int d[m];

    // array to store finishing time
    int f[m];

    for (int i = 0; i < m; i++)
    {
        // initializing color of all nodes to white
        color[i] = 0;
        p[i] = -1;
    }

    for (int i = 0; i < m; i++)
    {
        if (color[i] == 0)
        {
            edge_visit_u(graph, i, color, d, f, p);
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

    int output[m];
    int input[m];
    for (int i = 0; i < m; i++)
    {
        input[i] = 0;
        output[i] = 0;
    }
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
            output[x]++;
            input[y]++;
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
            output[x]++;
            output[y]++;
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

    dfs(arr, m);
    printf("\n \n The classification of edges are as following : \n\n");

    if (c == 0)
    {
        edge_u(arr, m);
    }
    else
    {
        edge(arr, m);
    }

    return 0;
}