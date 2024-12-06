#include <stdio.h>

struct SinhVien 
{ 
    char maSV[8]; 
    char hoTen[50]; 
    int gioiTinh; 
    Ngay ngaySinh; 
    char diaChi[100]; 
    char lop[12]; 
    char khoa[7]; 
};

struct Ngay 
{ 
    int ngay, thang, nam;
 }; 
struct Node { 
    SinhVien data; 
    Node *link; 
}; 
struct List { 
    Node *first; 
    Node *last; 
};

// Tạo 1 node sinh viên mới
struct Node* makeNode(struct SinhVien sv) {
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = sv;
    newNode->link = NULL;
    return newNode;