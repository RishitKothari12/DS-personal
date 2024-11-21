#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
    int height;
};

struct Node* CreateNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    newNode->height = 1;
    return newNode;
}

int getHeight(struct Node* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

void updateHeight(struct Node* node) {
    node->height = 1 + (getHeight(node->left) > getHeight(node->right) ? getHeight(node->left) : getHeight(node->right));
}

int getBalanceFactor(struct Node* node) {
    if (node == NULL)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

struct Node* leftRotate(struct Node* node) {
    struct Node* temp = node->right;
    node->right = temp->left;
    temp->left = node;
    updateHeight(node);
    updateHeight(temp);
    return temp;
}

struct Node* rightRotate(struct Node* node) {
    struct Node* temp = node->left;
    node->left = temp->right;
    temp->right = node;
    updateHeight(node);
    updateHeight(temp);
    return temp;
}

struct Node* rebalance(struct Node* node) {
    int balanceFactor = getBalanceFactor(node);
    if (balanceFactor > 1) {
        if (getBalanceFactor(node->left) >= 0) {
            printf("Performing LL Rotation \n");
            return rightRotate(node); // LL case
        } else {
            printf("Performing LR Rotation \n");
            node->left = leftRotate(node->left); // LR case
            return rightRotate(node);
        }
    } else if (balanceFactor < -1) {
        if (getBalanceFactor(node->right) <= 0) {
            printf("Performing RR Rotation \n");
            return leftRotate(node); // RR case
        } else {
            printf("Performing RL Rotation \n");
            node->right = rightRotate(node->right); // RL case
            return leftRotate(node);
        }
    }
    return node;
}

struct Node* insertNode(struct Node* node, int data) {
    if (node == NULL)
        return CreateNode(data);
    if (data < node->data)
        node->left = insertNode(node->left, data);
    else if (data > node->data)
        node->right = insertNode(node->right, data);
    else
        return node;
    updateHeight(node);
    return rebalance(node);
}

struct Node* minValueNode(struct Node* node) {
    struct Node* current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

struct Node* deleteNode(struct Node* node, int data) {
    if (node == NULL)
        return node;
    if (data < node->data)
        node->left = deleteNode(node->left, data);
    else if (data > node->data)
        node->right = deleteNode(node->right, data);
    else {
        if (node->left == NULL) {
            struct Node* temp = node->right;
            free(node);
            return temp;
        } else if (node->right == NULL) {
            struct Node* temp = node->left;
            free(node);
            return temp;
        }
        struct Node* temp = minValueNode(node->right);
        node->data = temp->data;
        node->right = deleteNode(node->right, temp->data);
    }
    if (node == NULL)
        return node;
    updateHeight(node);
    int balanceFactor = getBalanceFactor(node);
    if (balanceFactor > 1) {
        if (getBalanceFactor(node->left) >= 0){
            printf("Performing LL Rotation \n");
            return rightRotate(node);
        }
        else {
            printf("Performing LR Rotation \n");
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
    } else if (balanceFactor < -1) {
         printf("Performing RR Rotation \n");
        if (getBalanceFactor(node->right) <= 0)
            return leftRotate(node);
        else {
             printf("Performing RL Rotation \n");
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
    }
    return node;
}

void PreOrder(struct Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        PreOrder(root->left);
        PreOrder(root->right);
    }
}

void displayTree(struct Node* node, int space) {
    const int COUNT = 5; // Distance between levels
    if (node == NULL) return;

    // Increase distance between levels
    space += COUNT;

    // Process right child first
    displayTree(node->right, space);

    // Print current node after space
    printf("\n");
    for (int i = COUNT; i < space; i++) {
        printf(" ");
    }
    printf("%d\n", node->data);

    // Process left child
    displayTree(node->left, space);

    
}


int main() {
    int num,inum,ele;
    struct Node* root = NULL;

    printf("Enter number of elements to insert: ");
    scanf("%d",&inum);

    for (int i = 0; i < inum; i++)
    {              
        printf("Enter Element %d: ",(i+1));
        scanf("%d",&ele);     
        root = insertNode(root, ele);
        printf("AVL Tree after inserting %d:\n",ele);
        displayTree(root, 0);
        printf("Preorder: ");
        PreOrder(root);
        printf("\n\n");
    }

    printf("Enter element to delete: ");
    scanf("%d",&num);
    root = deleteNode(root, num);
    printf("AVL Tree after deleting %d:\n",num);
    displayTree(root, 0);
    printf("Preorder: ");
    PreOrder(root);
    printf("\n\n");
    return 0;
}
