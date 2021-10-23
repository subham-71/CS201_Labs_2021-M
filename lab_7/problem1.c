//Name: Subham Subhasis Sahoo
//Entry No. : 2020CSB1317

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

//nodes for doubly linked list
typedef struct node
{
    int num;
    struct node *next;
    struct node *prev;
} node;

//hash table structure with head pointers of doubly linked list for all the slots
typedef struct node_arr
{
    struct node *head;
} node_arr;

//initialising hash table with all head pointers to null
void init_hash_table(node_arr *hash_table, int m)
{
    for (int i = 0; i < m; i++)
    {
        hash_table[i].head = NULL;
    }
}
//creating node from a number
node *create_node(int num)
{
    node *temp;
    temp = (struct node *)malloc(sizeof(struct node));
    temp->num = num;
    temp->prev = NULL;
    temp->next = NULL;
    return temp;
}
//given hash fucntion
int hash(int num, int m)
{
    int hash_value;
    if (num > 0)
    {
        hash_value = num % m;
    }
    else
    {
        if (num % m != 0)
        {
            hash_value = num % m + m;
        }
        else
        {
            hash_value = num % m;
        }
    }

    return hash_value;
}
//insertion in hash table
void insert_hash_table(node_arr *hash_table, int val, int m)
{
    node *temp = create_node(val);
    int index = hash(val, m);

    //if head pointer null (slot empty), store the created node in head
    if (hash_table[index].head == NULL)
    {
        hash_table[index].head = temp;
    }

    //in case of collison , value stored in the doubly linked list nodes
    else
    {
        temp->next = hash_table[index].head;
        hash_table[index].head->prev = temp;
        hash_table[index].head = temp;
    }
}

void delete_hash_table(node_arr *hash_table, int val, int m)
{
    //finding slot of the value
    int index = hash(val, m);
    struct node *temp = hash_table[index].head;

    //finding value in doubly linked list
    while (temp != NULL)
    {
        if (temp->num == val)
        {
            //checking if node at head
            if (temp == hash_table[index].head)
            {
                if (temp->next != NULL)
                {
                    temp->next->prev = NULL;
                }
                else
                {
                    hash_table[index].head = NULL;
                }
                hash_table[index].head = temp->next;
            }

            //checking if node is at the end
            else if (temp->next == NULL)
            {
                temp->prev->next = NULL;
            }

            else
            {
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
            }
            // freeing the memory.
            free(temp);
            return;
        }
        temp = temp->next;
    }
}

void search_hash_table(node_arr *hash_table, int val, int m)
{
    //finding hash value of given number
    int index = hash(val, m);
    int flag = 0;

    //searching in the doubly linked list of that slot
    node *temp = hash_table[index].head;
    while (temp != NULL)
    {
        if (temp->num == val)
        {
            flag = 1;
            printf("Number %d present in index %d \n", val, index);
            break;
        }
        temp = temp->next;
    }
    if (!flag)
    {
        printf("Number %d  not present \n", val);
    }
}
void print_hash_table(node_arr *hash_table, int m)
{
    //looping through the hash table structure which initially contained head pointers only
    for (int i = 0; i < m; i++)
    {
        struct node *temp = hash_table[i].head;
        if (temp == NULL)
        {
            printf("\tindex %d:\t---\n", i);
        }
        else
        {
            printf("\tindex %d:\t", i);
            struct node *temp = hash_table[i].head;
            //looping through the doubly linked list of a particular slot
            while (temp != NULL)
            {
                printf("%d ", temp->num);
                temp = temp->next;
            }
            printf("\n");
        }
    }
}

int main()
{
    int m;
    printf("Enter m \n");
    scanf("%d", &m);

    node_arr *arr = (node_arr *)malloc(m * (sizeof(node_arr)));
    init_hash_table(arr, m);

    int choice;
    while (1)
    {
        printf("----------------------------------------------------------------\nENTER\n1. Insert\n2. Delete\n3. Search\n4. Display\n5 to quit \n----------------------------------------------------------------\n\n");
        scanf("%d", &choice);
        if (choice == 1)
        {
            int val;
            printf("Enter value to Insert : ");
            scanf("%d", &val);
            insert_hash_table(arr, val, m);
        }
        else if (choice == 2)
        {
            int val;
            printf("Enter value to Delete : ");
            scanf("%d", &val);
            delete_hash_table(arr, val, m);
        }
        else if (choice == 3)
        {
            int val;
            printf("Enter value to Search : ");
            scanf("%d", &val);
            search_hash_table(arr, val, m);
        }
        else if (choice == 4)
        {
            print_hash_table(arr, m);
        }
        else if (choice == 5)
        {
            break;
        }
    }

    return 0;
}