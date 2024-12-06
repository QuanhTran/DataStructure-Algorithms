/* Trong siêu thị người ta xếp hàng để thực hiện thanh toán. Mỗi giỏ hàng với các hàng hoá được
coi như một node trong một cấu trúc hàng đợi.Khai báo cấu trúc hàng đợi. Các thông tin chứa ở mỗi 
node sinh viên tự đưa vào để đảm bảo các nội dung sau được thực hiện 
Loại bỏ từng người ra khỏi hàng đợi sau khi người đó đã thực hiện thanh toán xong 
Tính tổng số tiền mà thu ngân thu được tại quầy trong một phiên làm việc  
Xác định số lượng một sản phẩm A đã được bán tại quầy thu ngân  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Định nghĩa cấu trúc sản phẩm
struct Product {
    char name[50];  
    int quantity;   
    float price;    
};

// Định nghĩa cấu trúc giỏ hàng
struct Cart {
    struct Product products[100]; // Danh sách sản phẩm trong giỏ
    int productCount;             // Số lượng sản phẩm trong giỏ
    struct Cart* next;            
};

// Định nghĩa cấu trúc hàng đợi
struct Queue {
    struct Cart* front;  
    struct Cart* rear;   
};
typedef struct Queue Queue;

// Khởi tạo hàng đợi rỗng
void initQueue(Queue* q) {
    q->front = q->rear = NULL;
}

// Kiểm tra hàng đợi rỗng
int isEmpty(Queue* q) {
    return q->front == NULL;
}

// Thêm giỏ hàng vào hàng đợi
void enqueue(Queue* q, struct Cart* newCart) {
    if (q->rear == NULL) {
        q->front = q->rear = newCart;
    } else {
        q->rear->next = newCart;
        q->rear = newCart;
    }
    q->rear->next = NULL;
}

// Loại bỏ giỏ hàng khỏi hàng đợi
struct Cart* dequeue(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
        return NULL;
    }
    struct Cart* temp = q->front;
    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    return temp;
}