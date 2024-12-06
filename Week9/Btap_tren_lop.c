// Bài tập tại lớp tuần 10
// Thiết kế giải thuật để sắp xếp các file trong thư mục theo thức tự tăng dần về dung lượng 
 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct dateCreate {
    int ngay;
    int thang;
    int nam;
};

struct file {
    char fileName[100];
    int fileSize; // Kích thước file (KB)
    struct dateCreate ngayTaoFile; // Ngày tạo file
};

struct folder {
    struct file data;
    struct folder *link;
};
typedef struct folder folder;

int compareDate(struct dateCreate d1, struct dateCreate d2) {
    if (d1.nam != d2.nam)
        return d1.nam - d2.nam;
    if (d1.thang != d2.thang)
        return d1.thang - d2.thang;
    return d1.ngay - d2.ngay;
}

void insertFile(folder **head, struct file newFile) {
    folder *newNode = (folder *)malloc(sizeof(folder));
    newNode->data = newFile;
    newNode->link = NULL;

    if (*head == NULL || compareDate((*head)->data.ngayTaoFile, newFile.ngayTaoFile) > 0) {
        newNode->link = *head;
        *head = newNode;
    } else {
        folder *current = *head;
        while (current->link != NULL && compareDate(current->link->data.ngayTaoFile, newFile.ngayTaoFile) < 0) {
            current = current->link;
        }
        newNode->link = current->link;
        current->link = newNode;
    }
}
void createFile(folder **head) {
    struct file newFile;

    printf("Nhập tên file: ");
    scanf("%s", newFile.fileName);
    printf("Nhập kích thước file (KB): ");
    scanf("%d", &newFile.fileSize);
    printf("Nhập ngày tạo file (ngày tháng năm): ");
    scanf("%d %d %d", &newFile.ngayTaoFile.ngay, &newFile.ngayTaoFile.thang, &newFile.ngayTaoFile.nam);

    insertFile(head, newFile);
    printf("File %s đã được tạo thành công.\n", newFile.fileName);
}

void displayFiles(folder *head) {
    folder *current = head;
    printf("Danh sách các file trong thư mục:\n");
    while (current != NULL) {
        printf("Tên file: %s, Kích thước: %d KB, Ngày tạo: %02d/%02d/%04d\n",
               current->data.fileName, current->data.fileSize,
               current->data.ngayTaoFile.ngay, current->data.ngayTaoFile.thang, current->data.ngayTaoFile.nam);
        current = current->link;
    }
}

void sort(folder **head){
    for(folder *i = *head; i != NULL; i = i->link){
        folder *min = i;
    for(folder *j = i->link; j != NULL; j = j->link){
        if(j->data.fileSize < min->data.fileSize){
            min = j;
        }
    }
    int tmp = min->data.fileSize;
    min->data = i->data;
    i->data.fileSize = tmp;
    }
}

int main() {
    folder *head = NULL;
    createFile(&head);
    sort(&head);
    displayFiles(head);
}