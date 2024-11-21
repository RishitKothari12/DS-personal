#include <stdio.h>
#include <stdlib.h>

struct node_tree {
    char data;
    struct node_tree *left, *right;
};

struct stack {
    struct node_tree **arr;
    int size;
    int top;
};

struct stack *st;

struct node_tree *peek();
void push(struct node_tree *x);
int isEmpty();
struct node_tree *pop();
void postorder(struct node_tree* root);
int is_digit(char ch);
struct node_tree *create_node(char data);
struct node_tree *create();
int count_nodes(struct node_tree* root);
int count_leaves(struct node_tree* root, int count);
struct node_tree *expression_tree(char *exp);

int is_digit(char ch) {
    return (ch >= '0' && ch <= '9');
}

struct node_tree *create_node(char data) {
    struct node_tree *new_node = (struct node_tree *)malloc(sizeof(struct node_tree));
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

struct node_tree *create() {
    int x;
    struct node_tree *new_node;
    new_node = (struct node_tree *)malloc(sizeof(struct node_tree));
    printf("Enter data (-1 for no node):\n");
    scanf("%d", &x);
    if (x == -1) {
        return NULL;
    }
    new_node->data = x;
    printf("Enter left child of %d\n", x);
    new_node->left = create();
    printf("Enter right child of %d\n", x);
    new_node->right = create();
    return new_node;
}

int count_nodes(struct node_tree* root) {
    if(root == NULL) {
        return 0;
    }
    return count_nodes(root->left) + count_nodes(root->right) + 1;
}

int count_leaves(struct node_tree* root, int count) {
    if(root) {
        if(root->left == NULL && root->right == NULL) {
            count++;
        } else {
            if(root->left) {
                count = count_leaves(root->left, count);
            }
            if(root->right) {
                count = count_leaves(root->right, count);
            }
        }
    }
    return count;
}

int countHeight(struct node_tree* node, struct node_tree* target){
    if(node == NULL){
        return -1; // return -1 for NULL node
    } else if(node == target){
        return 0; // return 0 for the target node
    } else {
        int left_height = countHeight(node->left, target);
        int right_height = countHeight(node->right, target);
        
        if(left_height > right_height){
            return left_height + 1;
        } else {
            return right_height + 1;
        }
    }
}

struct node_tree *expression_tree(char *exp) {
    int i = 0;
    while (exp[i] != '\0') {
        if (is_digit(exp[i])) {
            struct node_tree *operand = create_node(exp[i]);
            push(operand);
        } else {
            struct node_tree *operator = create_node(exp[i]);
            operator->right = pop();
            operator->left = pop();
            push(operator);
        }
        i++;
        printf("Intermediate step (Postorder): ");
        postorder(peek());
        printf("\n");
    }
    return pop();
}

void preorder(struct node_tree* root)
{
    if(root != NULL){
        printf("%d", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(struct node_tree* root) {
    if (root == NULL) {
        return;
    }
    postorder(root->left);
    postorder(root->right);
    printf("%c ", root->data);
}

void push(struct node_tree *x) {
    if (st->top == st->size - 1) {
        printf("Stack overflow\n");
        return;
    } else {
        st->top++;
        st->arr[st->top] = x;
    }
}

int isEmpty() {
    return st->top == -1;
}

struct node_tree *pop() {
    if (isEmpty()) {
        printf("Stack underflow\n");
        return NULL;
    } else {
        return st->arr[st->top--];
    }
}

struct node_tree *peek() {
    if (isEmpty()) {
        printf("Stack underflow\n");
        return NULL;
    } else {
        return st->arr[st->top];
    }
}



int main() {
    st = (struct stack *)malloc(sizeof(struct stack));
    st->size = 100;
    st->top = -1;
    st->arr = (struct node_tree **)malloc(st->size * sizeof(struct node_tree *));
    
    struct node_tree *tree;
    tree = create();
    
    printf("Preorder traversal of initial tree:\n");
    preorder(tree);
    printf("\n");
    
    printf("Number of nodes: %d\n", count_nodes(tree));
    printf("Number of leaf nodes: %d\n", count_leaves(tree, 0));
    
     struct node_tree* target = tree->left->right; // target node is 1
    printf("Height of Node %d is: ", target->data);
    int height = countHeight(tree, target);
    printf("%d",height);
    printf("\n");

    char exp[100];
    printf("\nEnter postfix expression: ");
    scanf("%s", exp);
    struct node_tree *root = expression_tree(exp);
    
    printf("Postorder traversal of final expression tree:\n");
    postorder(root);
    printf("\n");
    
    free(st->arr);
    free(st);
    
    return 0;
}