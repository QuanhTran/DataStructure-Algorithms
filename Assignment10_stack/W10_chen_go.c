#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10 // Kích thước tối đa của stack

// Định nghĩa cấu trúc thanh gỗ
struct Wood {
    char type[30];   // Loại gỗ
    char size[10];   // Kích thước (chuỗi để mô tả kích thước)
    int age;         // Tuổi gỗ (năm)
};

// Định nghĩa stack
struct stack {
    struct Wood items[MAX];
    int top;
};
typedef struct stack st;

// Khởi tạo stack rỗng
void createEmptyStack(st *s) {
    s->top = -1;
}

// Kiểm tra stack đầy
int isFull(st *s) {
    return s->top == MAX - 1;
}

// Kiểm tra stack rỗng
int isEmpty(st *s) {
    return s->top == -1;
}

// Thêm thanh gỗ vào stack
void push(st *s, struct Wood newWood) {
    if (isFull(s)) {
        printf("STACK FULL\n");
    } else {
        s->top++;
        s->items[s->top] = newWood;
    }
}

// Loại bỏ thanh gỗ khỏi stack
struct Wood pop(st *s) {
    if (isEmpty(s)) {
        printf("\nSTACK EMPTY\n");
        struct Wood emptyWood = {"", "", 0};
        return emptyWood;
    } else {
        return s->items[s->top--];
    }
}

// In các thanh gỗ trong stack
void printStack(st *s) {
    printf("\nDanh sách các thanh gỗ trong kho:\n");
    for (int i = s->top; i >= 0; i--) { // In từ trên xuống
        printf("Loại: %s, Kích thước: %s, Tuổi: %d năm\n", 
               s->items[i].type, s->items[i].size, s->items[i].age);
    }
}

// Hàm thêm một thanh gỗ vào đáy stack
void pushToBottom(st *s, struct Wood newWood) {
    if (isEmpty(s)) {
        push(s, newWood);
    } else {
        struct Wood temp = pop(s);
        pushToBottom(s, newWood);
        push(s, temp);
    }
}

// Hàm chính
int main() {
    st *s = (st *)malloc(sizeof(st));
    createEmptyStack(s);

    // Thêm các thanh gỗ vào kho
    struct Wood w1 = {"Gụ", "10cm", 10};
    struct Wood w2 = {"Lim", "20cm", 20};
    struct Wood w3 = {"Sến", "30cm", 10};
    struct Wood w4 = {"Sồi", "15cm", 35};

    push(s, w1);
    push(s, w2);
    push(s, w3);
    push(s, w4);

    // In danh sách các thanh gỗ
    printStack(s);

    // Thêm một khối gỗ "Óc chó", "10cm", "5 năm" ở đáy stack
    struct Wood newWood = {"Óc chó", "10cm", 5};
    pushToBottom(s, newWood);

    // In danh sách các thanh gỗ sau khi thêm
    printf("\nSau khi thêm khối gỗ mới vào đáy:\n");
    printStack(s);

    free(s); // Giải phóng bộ nhớ
    return 0;
}
