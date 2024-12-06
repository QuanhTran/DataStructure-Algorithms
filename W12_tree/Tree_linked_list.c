#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char value;
    struct Node *left, *right;
} Node;

Node* createNode(char value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

int isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

Node* constructExpressionTree(char* postfix) {
    Node* stack[100];
    int top = -1;

    for (int i = 0; postfix[i] != '\0'; i++) {
        if ((postfix[i] >= 'a' && postfix[i] <= 'z') || (postfix[i] >= 'A' && postfix[i] <= 'Z')) {
            // Nếu là toán hạng, tạo node lá
            stack[++top] = createNode(postfix[i]);
        } else {
            // Nếu là toán tử, tạo node cha
            Node* node = createNode(postfix[i]);
            node->right = stack[top--];
            node->left = stack[top--];
            stack[++top] = node;
        }
    }
    return stack[top];
}

void inorderTraversal(Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%c ", root->value);
        inorderTraversal(root->right);
    }
}

void preorderTraversal(Node* root) {
    if (root != NULL) {
        printf("%c ", root->value);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

void postorderTraversal(Node* root) {
    if (root != NULL) {
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        printf("%c ", root->value);
    }
}

int main() {
    // Biểu thức trung tố: (a + b) * (c - d)
    // Hậu tố tương ứng: ab+cd-*
    char postfixExpression[] = "ab+cd-*";

    // Dựng cây biểu thức
    Node* root = constructExpressionTree(postfixExpression);

    printf("Duyệt theo thứ tự LNR (Trung tố):\n");
    inorderTraversal(root);
    printf("\nDuyệt theo thứ tự NLR (Tiền tố):\n");
    preorderTraversal(root);
    printf("\nDuyệt theo thứ tự LRN (Hậu tố):\n");
    postorderTraversal(root);

    return 0;
}
