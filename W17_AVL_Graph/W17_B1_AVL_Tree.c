#include <stdio.h>
#include <stdlib.h>

// Định nghĩa cấu trúc Node
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
    int height;
} Node;

// Hàm lấy chiều cao của node
int getHeight(Node* node) {
    if (node == NULL) return 0;
    return node->height;
}

// Hàm lấy độ cân bằng
int getBalance(Node* node) {
    if (node == NULL) return 0;
    return getHeight(node->left) - getHeight(node->right);
}

// Hàm cập nhật chiều cao
void updateHeight(Node* node) {
    if (node != NULL) {
        int leftHeight = getHeight(node->left);
        int rightHeight = getHeight(node->right);
        node->height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
    }
}

// Hàm xoay phải
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

// Hàm xoay trái
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}

// Hàm chèn một node mới
Node* insert(Node* node, int data) {
    if (node == NULL) {
        Node* newNode = (Node*) malloc(sizeof(Node));
        newNode->data = data;
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->height = 1;
        return newNode;
    }

    if (data < node->data)
        node->left = insert(node->left, data);
    else if (data > node->data)
        node->right = insert(node->right, data);
    else
        return node;

    updateHeight(node);

    int balance = getBalance(node);

    // Trường hợp Left Left
    if (balance > 1 && data < node->left->data)
        return rightRotate(node);

    // Trường hợp Right Right
    if (balance < -1 && data > node->right->data)
        return leftRotate(node);

    // Trường hợp Left Right
    if (balance > 1 && data > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Trường hợp Right Left
    if (balance < -1 && data < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Hàm duyệt cây theo thứ tự trước
void preOrder(Node* node) {
    if (node != NULL) {
        printf("%d ", node->data);
        preOrder(node->left);
        preOrder(node->right);
    }
}

// Hàm duyệt cây theo thứ tự giữa
void inOrder(Node* node) {
    if (node != NULL) {
        inOrder(node->left);
        printf("%d ", node->data);
        inOrder(node->right);
    }
}

// Hàm duyệt cây theo thứ tự sau
void postOrder(Node* node) {
    if (node != NULL) {
        postOrder(node->left);
        postOrder(node->right);
        printf("%d ", node->data);
    }
}

// Hàm chính
int main() {
    Node* root = NULL;

    int arr[] = {240, 73, 101, 21, 13, 25, 11, 37, 89, 30, 15, 51};
    int n = sizeof(arr) / sizeof(arr[0]);

    for (int i = 0; i < n; i++) {
        root = insert(root, arr[i]);
        printf("\nSau khi chèn %d:\n", arr[i]);
        printf("Duyệt trước: ");
        preOrder(root);
        printf("\nDuyệt giữa: ");
        inOrder(root);
        printf("\nDuyệt sau: ");
        postOrder(root);
        printf("\n");
    }

    return 0;
}
