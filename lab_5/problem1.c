//Name: Subham Subhasis Sahoo
//Entry No.: 2020CSB1317

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

struct node
{
    int keys;           //number of key values stored
    int *arr;           //Array to store key values
    struct node **link; //Array of pointers pointing to children
    int leaf;           //Is a leaf or not
    int t;              //Parameter t
};
struct node *B_TREE_CREATE(int keys, int t, int leaf)
{
    //Allocating memory
    struct node *temp = (struct node *)calloc(1, sizeof(struct node));
    //Allocating memory for array to store key values
    temp->arr = calloc(2 * t - 1, sizeof(int));
    //Parameter t
    temp->t = t;
    //number of key values stored
    temp->keys = keys;
    //Is a leaf or not
    temp->leaf = leaf;
    //Allocating memory for array of pointers pointing to children
    temp->link = calloc(2 * t, sizeof(struct node *));

    return temp;
}
struct node *B_TREE_SPLIT_CHILD(int i, struct node *y, struct node *s)
{
    //idea is to take y and split it and bring both nodes under s

    //creating a new node z
    struct node *z;
    z = B_TREE_CREATE((y->t) - 1, y->t, y->leaf);

    //If it is not a leaf,copying the last t children of y to z
    if (!y->leaf)
    {
        for (int j = 0; j < (z->t); j++)
            z->link[j] = y->link[j + (y->t)];
    }

    //Copying last t-1 keys values of y to z
    for (int j = 0; j < (z->t) - 1; j++)
    {
        z->arr[j] = y->arr[j + (y->t)];
    }

    y->keys = (y->t) - 1;

    //shifting the linkages one step forward, so that z can be linked to s at the appropiate place
    for (int j = (y->keys); j >= i + 1; j--)
    {
        s->link[j + 1] = s->link[j];
    }
    //z linked to s
    s->link[i + 1] = z;

    //shifting elements one step forward now so as to accomodate the median element
    for (int j = (z->keys) - 1; j >= i; j--)
        s->arr[j + 1] = s->arr[j];

    //median element accomodated
    s->arr[i] = y->arr[(y->t) - 1];

    s->keys += 1;

    return s;
}
struct node *B_TREE_INSERT_NONFULL(struct node *q, int val)
{

    if (q->leaf)
    {
        int i;
        //starting a loop backwards so as to find where value is to be placed(comparing with other elements)
        for (i = q->keys - 1; (i >= 0 && q->arr[i] > val); i--)
        {
            q->arr[i + 1] = q->arr[i]; //also shifting elements one step forward to make space for val
        }

        q->arr[i + 1] = val; //val accomodated
        q->keys = q->keys + 1;
    }
    else
    {
        //finding suitable place to accomodate val
        int i = q->keys - 1;
        while (i >= 0 && q->arr[i] > val)
        {
            i--;
        }
        //if my node gets overloaded, I have to split it
        if (q->link[i + 1]->keys == 2 * (q->t) - 1)
        {
            q = B_TREE_SPLIT_CHILD(i + 1, q->link[i + 1], q);

            if (q->arr[i + 1] < val)
            {
                i++;
            }
            //after spliting, inserting as usual at the leaves
            q->link[i + 1] = B_TREE_INSERT_NONFULL(q->link[i + 1], val);
        }
        else
        {
            //calling recursively, will terminate when it will insert at leaves
            q->link[i + 1] = B_TREE_INSERT_NONFULL(q->link[i + 1], val);
        }
    }
    return q;
}
struct node *B_TREE_INSERT(struct node *root, int val, int t)
{
    if (root == NULL)
    {
        root = B_TREE_CREATE(1, t, 1); //creating new node
        root->arr[0] = val;            //setting the value to its key values array

        return root;
    }
    else
    {
        if (root->keys != (2 * t - 1))
        {
            root = B_TREE_INSERT_NONFULL(root, val); // inserting at leaves as explained above
        }
        else //if node is full, then we have to go for split
        {
            // creating a new root, old root will split
            struct node *s;
            s = B_TREE_CREATE(0, t, 0);

            //old root connected to new root - new root now topmost
            s->link[0] = root;

            // old root split
            s = B_TREE_SPLIT_CHILD(0, root, s);

            //if my value is more than arr[0] then it will go to right linkage else it will go to left
            int i;
            if (s->arr[0] < val)
            {
                i = 1;
            }
            else
            {
                i = 0;
            }
            s->link[i] = B_TREE_INSERT_NONFULL(s->link[i], val); //inserting at leaves

            // finally making the new root as the main root
            root = s;
        }
        return root;
    }
}

void B_TREE_INORDER_TRAVERSE(struct node *root)
{ //printing elements in sorted order using similar algorithm of inorder traversal as in BST
    int i;
    for (i = 0; i < (root->keys); i++)
    {
        if (!root->leaf)
        {
            B_TREE_INORDER_TRAVERSE(root->link[i]);
        }
        printf("%d ", root->arr[i]);
    }
    if (!root->leaf)
    {
        B_TREE_INORDER_TRAVERSE(root->link[i]);
    }
}

void B_TREE_MIN(struct node *root)
{ //traversing to the left most element to get the minimum
    if (root == NULL)
    {
        printf("Tree empty\n");
        return;
    }
    int i;

    for (i = 0; i < (root->keys); i++)
    {
        if (!root->leaf)
        {
            B_TREE_MIN(root->link[0]);
        }
        else
        {
            printf("min : %d \n", root->arr[i]);
            break;
        }
    }
}
int B_TREE_SEARCH(int val, struct node *root)
{
    if (root == NULL)
    {
        return 0;
    }
    //finding to which side of the node my value is located
    int i = 0;
    while ((i < root->keys) && (val > root->arr[i]))
    {
        i++;
    }

    if (root->arr[i] == val) //if found
    {
        return 1;
    }
    else
    {
        if (root->leaf) // terminating condition ,if at the end of tree
        {
            return 0;
        }
    }

    // calling recursively on the suitable child
    return B_TREE_SEARCH(val, root->link[i]);
}

int main()
{
    struct node *root = NULL;
    int t;
    printf("Enter t\n");
    scanf("%d", &t);
    while (1)
    {
        int option;
        printf("----------------------------------------------------------------------\n");
        printf("Enter\n1 for A\n2 for B\n3 to Exit \n");
        printf("----------------------------------------------------------------------\n");
        scanf("%d", &option);
        if (option == 1)
        {
            for (int i = 100; i > 0; i--)
            {
                root = B_TREE_INSERT(root, i, t);
            }
            printf("Inserted elements from 100 to 1. Inorder traversal is as follows: \n");
            B_TREE_INORDER_TRAVERSE(root);
            printf("\n");
            int num;
            printf("Enter number to search \n");
            scanf("%d", &num);
            int searching = B_TREE_SEARCH(num, root);
            if (searching)
            {
                printf("Number found\n");
            }
            else
            {
                printf("Number not found\n");
            }
            printf("\n");
        }
        else if (option == 2)
        {
            printf("-------------------------------------\n");
            printf("Enter \n1 to insert an element\n2 to search an element\n3 to find min digit\n4 to show the inorder traversal\n5 to exit \n");
            printf("-------------------------------------\n");
            int c;
            scanf("%d", &c);
            if (c == 1)
            {
                int num;
                printf("Enter number to insert \n");
                scanf("%d", &num);
                root = B_TREE_INSERT(root, num, t);
            }
            else if (c == 2)
            {
                int num;
                printf("Enter number to search \n");
                scanf("%d", &num);
                int searching = B_TREE_SEARCH(num, root);
                if (searching)
                {
                    printf("Number found\n");
                }
                else
                {
                    printf("Number not found\n");
                }
            }
            else if (c == 3)
            {
                B_TREE_MIN(root);
                printf("\n");
            }
            else if (c == 4)
            {
                B_TREE_INORDER_TRAVERSE(root);
                printf("\n");
            }
            else if (c == 5)
            {
                break;
            }
        }
        else
        {
            break;
        }
    }

    return 0;
}