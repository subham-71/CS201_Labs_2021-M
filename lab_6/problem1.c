// Name:Subham Subhasis Sahoo
// Entry No.: 2020CSB1317

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

struct node
{
    int key;
    struct node *left;
    struct node *right;
};
//calculating height of nodes
int height(struct node *r)
{
    if (r == NULL)
    {
        return -1;
    }
    else
    {
        int l_height = height(r->left);
        int r_height = height(r->right);

        if (l_height > r_height)
        {
            return (l_height + 1);
        }
        else
        {
            return (r_height + 1);
        }
    }
}
//left rotate adjustment
struct node *left_rotate(struct node *x)
{
    struct node *y = x->right;
    struct node *temp = y->left;

    y->left = x;
    x->right = temp;

    return y;
}
//right rotate adjustment
struct node *right_rotate(struct node *y)
{
    struct node *x = y->left;
    struct node *temp = x->right;

    x->right = y;
    y->left = temp;

    return x;
}
//calculating balance factor of nodes
int balance(struct node *r)
{
    if (r == NULL)
    {
        return -1;
    }
    else
    {
        return (height(r->left) - height(r->right));
    }
}

//to create a node with data contained in it
struct node *get_node(int data)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->key = data;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

//to insert a node in tree
struct node *insert(struct node *r, int x)
{
    //inserting in tree
    if (r == NULL)
    {
        r = get_node(x);
        return r;
    }
    if (x < r->key)
    {
        r->left = insert(r->left, x);
    }
    else if (x > r->key)
    {
        r->right = insert(r->right, x);
    }

    //checking balance factor and adjusting accordingly
    int balance_f = balance(r);
    if (balance_f > 1 && x < r->left->key)
    {
        return right_rotate(r);
    }
    else if (balance_f > 1 && x > r->left->key)
    {
        r->left = left_rotate(r->left);
        return right_rotate(r);
    }
    else if (balance_f < -1 && x > r->right->key)
    {
        return left_rotate(r);
    }
    else if (balance_f < -1 && x < r->right->key)
    {
        r->right = right_rotate(r->right);
        return left_rotate(r);
    }
    else
    {
        return r;
    }
}
//inorder traversal
void print_in(struct node *r)
{
    if (r == NULL)
    {
        return;
    }
    print_in(r->left);
    printf("%d ", r->key);
    print_in(r->right);
}
//pre-order traversal
void print_pre(struct node *r)
{
    if (r == NULL)
    {
        return;
    }

    printf("%d ", r->key);
    print_pre(r->left);
    print_pre(r->right);
}
//search function
struct node *find(struct node *r, int val)
{
    if (r == NULL || r->key == val)
    {
        return r;
    }

    else if (val < r->key)
    {
        return find(r->left, val);
    }

    else
    {
        return find(r->right, val);
    }
}
int main()
{
    struct node *root = NULL;
    for (int i = 0; i < 25; i++)
    {
        root = insert(root, i);
    }

    while (1)
    {
        printf("Enter i to inset s to search p to print and q to quit \n");
        char c;
        scanf("%s", &c);
        if (c == 'i')
        {
            printf("Enter value you want to insert \n");
            int val;
            scanf("%d", &val);
            root = insert(root, val);
        }
        if (c == 's')
        {
            printf("Enter value you want to search \n");
            int val;
            scanf("%d", &val);
            struct node *finding = NULL;
            finding = find(root, val);
            if (finding == NULL)
            {
                printf("Not found \n");
            }
            else
            {
                printf("Found \n");
                int balance_f = balance(finding);
                printf("Balance Factor is %d \n", balance_f);
                int height_node = height(finding);
                printf("Height is %d \n", height_node);
            }
        }
        if (c == 'p')
        {
            printf("In order traversal : \n");
            print_in(root);
            printf("\n");
            printf("Pre order traversal : \n");
            print_pre(root);
            printf("\n");
        }
        if (c == 'q')
        {
            break;
        }
    }

    return 0;
}