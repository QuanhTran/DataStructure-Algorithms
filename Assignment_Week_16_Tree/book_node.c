#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Định nghĩa cấu trúc Node cho cây mục lục
struct Node {
    char title[100];       // Tên mục (Chapter, Section, ...)
    int pages;             // Số trang
    struct Node* firstChild; // Node con đầu tiên 
    struct Node* nextSibling; // Node anh em tiếp theo
};

// Hàm tạo một node mới
struct Node* createNode(const char* title, int pages) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    strcpy(newNode->title, title);
    newNode->pages = pages;
    newNode->firstChild = NULL;
    newNode->nextSibling = NULL;
    return newNode;
}

// Hàm thêm một node con vào một node cha
void addChild(struct Node* parent, struct Node* child) {
    if (parent->firstChild == NULL) {
        parent->firstChild = child;
    } else {
        struct Node* temp = parent->firstChild;
        while (temp->nextSibling != NULL) {
            temp = temp->nextSibling;
        }
        temp->nextSibling = child;
    }
}

// Đếm số chương của cuốn sách
int countChapters(struct Node* root) {
    int count = 0;
    struct Node* temp = root->firstChild;
    while (temp != NULL) {
        count++;
        temp = temp->nextSibling;
    }
    return count;
}

// Tìm chương dài nhất
struct Node* findLongestChapter(struct Node* root) {
    struct Node* temp = root->firstChild;
    struct Node* longestChapter = NULL;
    int maxPages = 0;

    while (temp != NULL) {
        if (temp->pages > maxPages) {
            maxPages = temp->pages;
            longestChapter = temp;
        }
        temp = temp->nextSibling;
    }
    return longestChapter;
}

// Xóa một mục và cập nhật lại cây
struct Node* deleteNode(struct Node* root, const char* title) {
    if (root == NULL) {
        return NULL;
    }

    // Nếu node hiện tại là node cần xóa
    if (strcmp(root->title, title) == 0) {
        // Xóa toàn bộ cây con
        struct Node* temp = root->firstChild;
        while (temp != NULL) {
            struct Node* next = temp->nextSibling;
            deleteNode(temp, temp->title);
            temp = next;
        }
        free(root);
        return NULL;
    }

    // Xử lý cho con đầu tiên
    if (root->firstChild != NULL) {
        root->firstChild = deleteNode(root->firstChild, title);
    }

    // Xử lý cho anh em tiếp theo
    if (root->nextSibling != NULL) {
        root->nextSibling = deleteNode(root->nextSibling, title);
    }

    return root;
}

// In cây mục lục
void printTree(struct Node* root, int level) {
    if (root == NULL) {
        return;
    }

    // In thụt lề theo cấp độ
    for (int i = 0; i < level; i++) {
        printf("  ");
    }
    printf("%s (Pages: %d)\n", root->title, root->pages);

    // Gọi đệ quy cho con đầu tiên và anh em tiếp theo
    printTree(root->firstChild, level + 1);
    printTree(root->nextSibling, level);
}

// Hàm chính
int main() {
    // Tạo root của cây (đại diện cho sách)
    struct Node* book = createNode("Book", 0);

    // Tạo các chương và thêm vào sách
    struct Node* chapter1 = createNode("Chapter 1", 20);
    struct Node* chapter2 = createNode("Chapter 2", 30);
    struct Node* chapter3 = createNode("Chapter 3", 15);
    addChild(book, chapter1);
    addChild(book, chapter2);
    addChild(book, chapter3);

    // Tạo các mục con cho Chapter 1
    struct Node* section1_1 = createNode("Section 1.1", 10);
    struct Node* section1_2 = createNode("Section 1.2", 10);
    addChild(chapter1, section1_1);
    addChild(chapter1, section1_2);

    // Tạo các mục con cho Chapter 2
    struct Node* section2_1 = createNode("Section 2.1", 15);
    struct Node* section2_2 = createNode("Section 2.2", 15);
    addChild(chapter2, section2_1);
    addChild(chapter2, section2_2);

    // In cây mục lục
    printf("Book Table of Contents:\n");
    printTree(book, 0);

    // Đếm số chương
    int numChapters = countChapters(book);
    printf("\nNumber of chapters: %d\n", numChapters);

    // Tìm chương dài nhất
    struct Node* longestChapter = findLongestChapter(book);
    if (longestChapter != NULL) {
        printf("Longest chapter: %s (Pages: %d)\n", longestChapter->title, longestChapter->pages);
    }

    // Xóa một mục khỏi sách
    const char* titleToDelete = "Chapter 2";
    book = deleteNode(book, titleToDelete);
    printf("\nAfter deleting '%s':\n", titleToDelete);
    printTree(book, 0);

    return 0;
}
