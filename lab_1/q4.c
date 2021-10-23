//Name: Subham Subhasis Sahoo
//Entry No : 2020CSB1317
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

struct Node
{
    int coefficient;
    int exponent;
    struct Node *next;
};

void display(struct Node *head)
{
    struct Node *temp = head->next;
    while (temp->next)
    {
        printf("%dx^%d+", temp->coefficient, temp->exponent);
        temp = temp->next;
    }
    printf("%dx^%d", temp->coefficient, temp->exponent);
    printf("\n");
}
struct Node *polymulti(struct Node *head_a, struct Node *head_b)
{
    struct Node *ha = head_a;
    struct Node *hb = head_b;

    struct Node *multi_head;
    multi_head = (struct Node *)malloc(sizeof(struct Node));
    while (ha != NULL)
    {
        while (hb != NULL)
        {
            int p = ha->coefficient * hb->coefficient;
            int q = ha->exponent + hb->exponent;
            multi_head->coefficient = p;
            multi_head->exponent = q;
            multi_head = multi_head->next;

            hb = hb->next;
        }
        ha = ha->next;
    }
    return multi_head;
}

int main()
{
    //input1
    int a;
    printf("No. of non-zero terms in first polynomial\n");
    scanf("%d", &a);

    struct Node *head_a = NULL;
    head_a = (struct Node *)malloc(sizeof(struct Node));

    head_a->coefficient = 0;
    head_a->exponent = 0;
    struct Node *temp_a = head_a;
    int n = a;
    printf("Enter terms in descending order of powers \n");
    while (a--)
    {
        struct Node *new_node = NULL;
        new_node = (struct Node *)malloc(sizeof(struct Node));
        printf("Enter term %d's coefficient : ", n - a);
        scanf("%d", &new_node->coefficient);
        printf("Enter term %d's exponent : ", n - a);
        scanf("%d", &new_node->exponent);
        new_node->next = NULL;
        temp_a->next = new_node;
        temp_a = temp_a->next;
    }

    // input2
    int b;
    printf("No. of non-zero terms in second polynomial\n");
    scanf("%d", &b);

    struct Node *head_b = NULL;
    head_b = (struct Node *)malloc(sizeof(struct Node));
    head_b->coefficient = 0;
    head_b->exponent = 0;

    struct Node *temp_b = head_b;
    printf("Enter terms in descending order of powers \n");
    int m = b;
    while (b--)
    {
        struct Node *new_node = NULL;
        new_node = (struct Node *)malloc(sizeof(struct Node));
        printf("Enter  term %d's coefficient : ", m - b);
        scanf("%d", &new_node->coefficient);
        printf("Enter term %d's exponent : ", m - b);
        scanf("%d", &new_node->exponent);
        new_node->next = NULL;
        temp_b->next = new_node;
        temp_b = temp_b->next;
    }

    printf("\nFirst polynomial  \n");
    display(head_a);

    printf("\nSecond Polynomial \n");
    display(head_b);

    //Multiplication of polynomials
    struct Node *multi_head = polymulti(head_a, head_b);

    printf("Ploynomial Multiplication \n");
    display(multi_head);

    return 0;
}