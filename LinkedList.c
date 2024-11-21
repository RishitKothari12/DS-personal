#include <stdio.h>
#include <stdlib.h>

struct node {
    int coefficient;
    int exponent;
    struct node *next;
};


struct node *insertAtEnd(struct node *start, int coeff, int exp) {
    struct node *p, *NewNode;
    NewNode = (struct node*)malloc(sizeof(struct node));
    NewNode->coefficient = coeff;
    NewNode->exponent = exp;
    NewNode->next = NULL;

    if (start == NULL) {
        return NewNode;
    } else {
        p = start;
        while (p->next != NULL) {
            p = p->next;
        }
        p->next = NewNode;
        return start;
    }
}

void display(struct node *start) {
    struct node *p = start;
    if (p == NULL) {
        printf("List is Empty");
    } else {
        while (p != NULL) {
            printf("\t%d x^%d", p->coefficient, p->exponent);
            p = p->next;
            if (p != NULL) {
                printf(" + ");
            }
        }
    }
    printf("\n");
}


struct node *add_polynomials(struct node *head1, struct node *head2) {
    struct node *startresult = NULL;
    struct node *p1 = head1, *p2 = head2;

    while (p1 != NULL && p2 != NULL) {
        if (p1->exponent > p2->exponent) {
            startresult = insertAtEnd(startresult, p1->coefficient, p1->exponent);
            p1 = p1->next;
        } else if (p1->exponent < p2->exponent) {
            startresult = insertAtEnd(startresult, p2->coefficient, p2->exponent);
            p2 = p2->next;
        } else {
            startresult = insertAtEnd(startresult, p1->coefficient + p2->coefficient, p1->exponent);
            p1 = p1->next;
            p2 = p2->next;
        }
    }

    while (p1 != NULL) {
        startresult = insertAtEnd(startresult, p1->coefficient, p1->exponent);
        p1 = p1->next;
    }

    while (p2 != NULL) {
        startresult = insertAtEnd(startresult, p2->coefficient, p2->exponent);
        p2 = p2->next;
    }

    return startresult;
}

int main() {
    int count, coeff, exp;

    struct node *head1 = NULL;
    struct node *head2 = NULL;
    struct node *startresult = NULL;


    printf("Enter number of terms in expression 1: ");
    scanf("%d", &count);
    
    for (int i = 0; i < count; i++) {
        printf("Enter Coefficient and Power of Term %d: \n", i + 1);
        scanf("%d %d", &coeff, &exp);
        head1 = insertAtEnd(head1, coeff, exp);
    }
    printf("Expression 1: \n");
    display(head1);

  
    printf("Enter number of terms in expression 2: ");
    scanf("%d", &count);
    
    for (int i = 0; i < count; i++) {
        printf("Enter Coefficient and Power of Term %d: \n", i + 1);
        scanf("%d %d", &coeff, &exp);
        head2 = insertAtEnd(head2, coeff, exp);
    }
    printf("Expression 2: \n");
    display(head2);

   
    startresult = add_polynomials(head1, head2);
    printf("Resultant Polynomial: \n");
    display(startresult);
    return 0;
}