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

struct fileNode {
    struct file data;
    struct fileNode *link;
};

typedef struct fileNode fileNode;

// Hàm so sánh ngày tạo để sắp xếp các file theo thứ tự ngày tạo
int compareDate(struct dateCreate d1, struct dateCreate d2) {
    if (d1.nam != d2.nam)
        return d1.nam - d2.nam;
    if (d1.thang != d2.thang)
        return d1.thang - d2.thang;
    return d1.ngay - d2.ngay;
}

// Hàm chèn file vào danh sách liên kết theo thứ tự ngày tạo
void insertFile(fileNode **head, struct file newFile) {
    fileNode *newNode = (fileNode *)malloc(sizeof(fileNode));
    newNode->data = newFile;
    newNode->link = NULL;

    if (*head == NULL || compareDate((*head)->data.ngayTaoFile, newFile.ngayTaoFile) > 0) {
        newNode->link = *head;
        *head = newNode;
    } else {
        fileNode *current = *head;
        while (current->link != NULL && compareDate(current->link->data.ngayTaoFile, newFile.ngayTaoFile) < 0) {
            current = current->link;
        }
        newNode->link = current->link;
        current->link = newNode;
    }
}

// Hàm tạo file mới
void createFile(fileNode **head) {
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

// Hàm thêm file từ thư mục khác
void addFileFromOtherDirectory(fileNode **head) {
    struct file newFile;

    printf("Nhập tên file cần sao chép từ thư mục khác: ");
    scanf("%s", newFile.fileName);
    printf("Nhập kích thước file (KB): ");
    scanf("%d", &newFile.fileSize);
    printf("Nhập ngày tạo file (ngày tháng năm): ");
    scanf("%d %d %d", &newFile.ngayTaoFile.ngay, &newFile.ngayTaoFile.thang, &newFile.ngayTaoFile.nam);

    insertFile(head, newFile);
    printf("File %s đã được thêm từ thư mục khác.\n", newFile.fileName);
}

// Hàm tính tổng kích thước các file trong danh sách
int calculateTotalSize(fileNode *head) {
    int totalSize = 0;
    fileNode *current = head;

    while (current != NULL) {
        totalSize += current->data.fileSize;
        current = current->link;
    }
    return totalSize;
}

// Hàm hiển thị danh sách các file
void displayFiles(fileNode *head) {
    fileNode *current = head;
    printf("Danh sách các file trong thư mục:\n");
    while (current != NULL) {
        printf("Tên file: %s, Kích thước: %d KB, Ngày tạo: %02d/%02d/%04d\n",
               current->data.fileName, current->data.fileSize,
               current->data.ngayTaoFile.ngay, current->data.ngayTaoFile.thang, current->data.ngayTaoFile.nam);
        current = current->link;
    }
}

// Hàm tìm và xóa file có kích thước nhỏ nhất
void removeSmallestFile(fileNode **head) {
    if (*head == NULL) {
        return;
    }

    fileNode *prev = NULL, *current = *head;
    fileNode *minPrev = NULL, *minNode = *head;

    // Tìm file có kích thước nhỏ nhất
    while (current != NULL) {
        if (current->data.fileSize < minNode->data.fileSize) {
            minPrev = prev;
            minNode = current;
        }
        prev = current;
        current = current->link;
    }

    // Xóa minNode khỏi danh sách
    if (minPrev == NULL) {
        *head = minNode->link; // Xóa phần tử đầu
    } else {
        minPrev->link = minNode->link;
    }
    printf("Đã xóa file có kích thước nhỏ nhất: %s, kích thước: %d KB\n", minNode->data.fileName, minNode->data.fileSize);
    free(minNode);
}

#define USB_CAPACITY 32768000 // Dung lượng USB 32GB tính bằng KB

void backupToUSB(fileNode **head) {
    int totalSize = calculateTotalSize(*head);

    printf("Tổng kích thước các file trong thư mục: %d KB\n", totalSize);

    // Nếu tổng kích thước vượt quá dung lượng USB, thực hiện loại bỏ
    while (totalSize > USB_CAPACITY) {
        printf("Tổng kích thước %d KB vượt quá dung lượng USB %d KB. Loại bỏ file nhỏ nhất...\n", totalSize, USB_CAPACITY);
        removeSmallestFile(head);
        totalSize = calculateTotalSize(*head);
    }

    printf("Sao lưu thành công. Dung lượng sử dụng trên USB: %d KB\n", totalSize);
    displayFiles(*head);
}

// Hàm main
int main() {
    fileNode *head = NULL;
    int choice;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Tạo file mới\n");
        printf("2. Thêm file từ thư mục khác\n");
        printf("3. Hiển thị danh sách file\n");
        printf("4. Tính tổng kích thước các file\n");
        printf("5. Sao lưu vào USB\n");
        printf("6. Thoát\n");
        printf("Nhập lựa chọn của bạn: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createFile(&head);
                break;
            case 2:
                addFileFromOtherDirectory(&head);
                break;
            case 3:
                displayFiles(head);
                break;
            case 4: {
                int totalSize = calculateTotalSize(head);
                printf("Tổng kích thước các file trong thư mục: %d KB\n", totalSize);
                break;
            }
            case 5:
                backupToUSB(&head);
                break;
            case 6:
                printf("Thoát chương trình.\n");
                exit(0);
            default:
                printf("Lựa chọn không hợp lệ. Vui lòng chọn lại.\n");
        }
    }
    return 0;
}
