#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
typedef struct Node {
char data;
struct Node *left, *right;
} Node;
Node* newNode(char data) {
Node* node = (Node*)malloc(sizeof(Node));
node->data = data;
node->left = node->right = NULL;
return node;
}
int isOperator(char ch) {
return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
}
Node* constructTree(const char* postfix) {
Node* stack[100];
int top = -1;
for (int i = 0; postfix[i] != '\0'; i++) {
char ch = postfix[i];
if (!isOperator(ch)) {
stack[++top] = newNode(ch);
} else {
Node* right = stack[top--];
Node* left = stack[top--];
Node* opNode = newNode(ch);
opNode->left = left;
opNode->right = right;
stack[++top] = opNode;
}
}
return stack[top];
}
void inorder(Node* root) {
if (root) {
inorder(root->left);
printf("%c ", root->data);
inorder(root->right);
}
}
void preorder(Node* root) {
if (root) {
printf("%c ", root->data);
preorder(root->left);
preorder(root->right);
}
}
void postorder(Node* root) {
if (root) {
postorder(root->left);
postorder(root->right);
printf("%c ", root->data);
}
}
int main() {
const char postfix[] = "AB+C*";
Node* root = constructTree(postfix);
printf("Inorder traversal: ");
inorder(root);
printf("\n");
printf("Preorder traversal: ");
preorder(root);
printf("\n");
printf("Postorder traversal: ");
postorder(root);
printf("\n");
return 0;
}