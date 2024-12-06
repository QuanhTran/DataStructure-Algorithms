#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10 // Kích thước tối đa của stack

int count = 0; // Đếm số lượng thanh gỗ trong stack

// Định nghĩa cấu trúc thanh gỗ
struct Wood {
    char type[30];   // Loại gỗ
    float size;      // Kích thước (mét)
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
int isfull(st *s) {
    return s->top == MAX - 1;
}

// Kiểm tra stack rỗng
int isempty(st *s) {
    return s->top == -1;
}

// Thêm thanh gỗ vào stack
void push(st *s, struct Wood newWood) {
    if (isfull(s)) {
        printf("STACK FULL\n");
    } else {
        s->top++;
        s->items[s->top] = newWood;
        count++;
    }
}

// Loại bỏ thanh gỗ khỏi stack
void pop(st *s) {
    if (isempty(s)) {
        printf("\nSTACK EMPTY\n");
    } else {
        struct Wood removed = s->items[s->top];
        printf("Thanh gỗ được lấy ra: Loại: %s, Kích thước: %.2f, Tuổi: %d\n", 
               removed.type, removed.size, removed.age);
        s->top--;
        count--;
    }
}

// In các thanh gỗ trong stack
void printStack(st *s) {
    printf("\nDanh sách các thanh gỗ trong kho:\n");
    for (int i = 0; i <= s->top; i++) {
        printf("Loại: %s, Kích thước: %.2f, Tuổi: %d\n", 
               s->items[i].type, s->items[i].size, s->items[i].age);
    }
}

// Đếm số lượng thanh gỗ cùng tuổi gỗ
int countWoodByAge(st *s, int age) {
    int ageCount = 0;
    for (int i = 0; i <= s->top; i++) {
        if (s->items[i].age == age) {
            ageCount++;
        }
    }
    return ageCount;
}

int main() {
    st *s = (st *)malloc(sizeof(st));
    createEmptyStack(s);

    // Thêm các thanh gỗ vào kho
    struct Wood w1 = {"Thông", 2.5, 10};
    struct Wood w2 = {"Lim", 1.8, 15};
    struct Wood w3 = {"Sồi", 3.2, 10};
    struct Wood w4 = {"Mun", 2.0, 20};
    
    push(s, w1);
    push(s, w2);
    push(s, w3);
    push(s, w4);

    // In danh sách các thanh gỗ
    printStack(s);

    // Đếm số lượng thanh gỗ có tuổi gỗ là 10 năm
    int age = 10;
    int ageCount = countWoodByAge(s, age);
    printf("\nSố lượng thanh gỗ có tuổi gỗ %d năm: %d\n", age, ageCount);

    // Lấy một thanh gỗ ra khỏi kho
    pop(s);

    // In danh sách các thanh gỗ sau khi lấy ra
    printf("\nSau khi lấy một thanh gỗ ra:\n");
    printStack(s);

    free(s); // Giải phóng bộ nhớ
    return 0;
}
