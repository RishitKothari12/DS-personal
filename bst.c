/*Implementation of basic operations of BST
In first Turn:
1- Creation of BST- insertion 
output : all test cases covering (like skewed tree , full tree, and a normal BST)
2- Search
output : all test cases covering found and not found
4- Find Min and Max
Turn2:
5- Predecessor/ Successor
output : all test cases covering like corner cases of finding predecessor of MIN and finding successor of MAX*/

#include<stdio.h>
#include<stdlib.h>

struct node
{
    int data;
    struct node* left;
    struct node* right;
};

struct node* createnode(struct node* root, int data)
{
    struct node* newnode = (struct node*)malloc(sizeof(struct node));
    newnode->data = data;
    newnode->left = NULL;
    newnode->right = NULL;
    return newnode;
}

struct node* insert(struct node* root, int data)
{
    if (root == NULL)
    {
        root = createnode(root, data);
        return root;
    }
    else if (data < root->data)
    {
        root->left = insert(root->left, data);
    }
    else if (data > root->data)
    {
        root->right = insert(root->right, data);
    }
}

struct node* search(struct node* root, int data)
{
    if(root == NULL)
    {
        printf("%d not found\n", data);
        return 0;
    }
    else if(data < root->data)
    {
        return search(root->left, data);
    }
    else if(data > root->data)
    {
        return search(root->right, data);
    }
    else if(data == root->data)
    {
        printf("%d found\n", data);
    }
    else
    {
        printf("%d not found\n", data);
    }
}

struct node* min(struct node* root)
{
    struct node* current = root;
    while(current->left != NULL)
    {
        current = current->left;
    }
    printf("Minimum element is %d\n", current->data);
}

struct node* max(struct node* root)
{
    struct node* current = root;
    while(current->right != NULL)
    {
        current = current->right;
    }
    printf("Maximum element is %d\n", current->data);
}

struct node* predecessor(struct node* root, int data) {
    struct node* current = search(root, data); // Find the node with the given data
    if (current == NULL) {
        printf("Node with data %d not found\n", data);
        return NULL;
    }

    // Case 1: Node has a left subtree
    if (current->left != NULL) {
        struct node* temp = current->left;
        while (temp->right != NULL) {
            temp = temp->right;
        }
        printf("Predecessor of %d is %d\n", data, temp->data);
        return temp;
    }

    // Case 2: No left subtree, go up to find the predecessor
    struct node* predecessor = NULL;
    struct node* ancestor = root;
    while (ancestor != current) {
        if (current->data < ancestor->data) {
            ancestor = ancestor->left;
        } else {
            predecessor = ancestor; // This could be the predecessor
            ancestor = ancestor->right;
        }
    }

    if (predecessor != NULL) {
        printf("Predecessor of %d is %d\n", data, predecessor->data);
    } else {
        printf("No predecessor for %d\n", data);
    }
    return predecessor;
}

void preorder(struct node* root)
{
    if(root != NULL)
    {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

int main()
{
    struct node* root = NULL;
    root = createnode(root, 54);
    insert(root, 32);
    insert(root, 67);
    insert(root, 25);
    insert(root, 98);

    printf("Preorder Traversal: ");
    preorder(root);

    printf("\nEnter data to search: ");
    int src;
    scanf("%d", &src);
    search(root, src);
    min(root);
    max(root);
    predecessor(root, 54);
}