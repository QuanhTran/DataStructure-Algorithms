#include <iostream>

using namespace std;

// Khai báo cấu trúc Ngay, SinhVien, Node và List 
struct Ngay {
    int ngay;
    int thang;
    int nam;
};

struct sinhVien {
    char maSV[8];       // Mã sinh viên (8 ký tự)
    char hoTen[50];     // Họ tên sinh viên (50 ký tự)
    int gioiTinh;       // Giới tính (0: Nam, 1: Nữ)
    Ngay ngaySinh;      // Ngày sinh
    char diaChi[100];   // Địa chỉ sinh viên
    char lop[12];       // Lớp sinh viên
    char khoa[7];       // Khoa sinh viên
};

struct Node {
    sinhVien data;      // Dữ liệu sinh viên
    Node* link;         // Con trỏ đến nút tiếp theo
};

struct List {
    Node* first;        // Con trỏ đến nút đầu tiên của danh sách
    Node* last;         // Con trỏ đến nút cuối cùng của danh sách
};

// Hàm khởi tạo danh sách sinh viên rỗng
void startList(List &list) {
    list.first = nullptr;
    list.last = nullptr;
}

// Hàm so sánh mã sinh viên (thủ công từng ký tự)
int soSanhMaSV(const char maSV1[], const char maSV2[]) {
    for (int i = 0; i < 7; i++) {
        if (maSV1[i] < maSV2[i]) return -1;
        if (maSV1[i] > maSV2[i]) return 1;
    }
    return 0; // Hai mã sinh viên bằng nhau
}

// Hàm thêm sinh viên vào danh sách đã sắp xếp theo mã sinh viên
void insertSorted(List &list, sinhVien sv) {
    Node* newNode = new Node;
    newNode->data = sv;
    newNode->link = nullptr;

    if (list.first == nullptr || soSanhMaSV(sv.maSV, list.first->data.maSV) < 0) {
        // Thêm vào đầu danh sách nếu rỗng hoặc mã SV nhỏ nhất
        newNode->link = list.first;
        list.first = newNode;
        if (list.last == nullptr) list.last = newNode; // Trường hợp danh sách rỗng
    } else {
        // Tìm vị trí phù hợp để chèn vào danh sách
        Node* current = list.first;
        while (current->link != nullptr && soSanhMaSV(current->link->data.maSV, sv.maSV) < 0) {
            current = current->link;
        }
        newNode->link = current->link;
        current->link = newNode;
        if (newNode->link == nullptr) list.last = newNode; // Cập nhật last nếu là nút cuối
    }
}

// Hàm in danh sách sinh viên
void printList(const List &list) {
    Node* current = list.first;
    while (current != nullptr) {
        cout << "Ma SV: " << current->data.maSV 
             << " - Ho ten: " << current->data.hoTen << endl;
        current = current->link;
    }
}

int main() {
    List list;
    startList(list);

    // Ví dụ thêm sinh viên
    sinhVien sv1 = {"224456", "Le Duc Anh", 0, {15, 5, 2004}, "Ha Noi", "ET-E9", "IoT"};
    sinhVien sv2 = {"224429", "Tran Quang Anh", 0, {3, 11, 2004}, "Nghe An", "ET-E9", "IoT"};
    sinhVien sv3 = {"224433", "Truong Quoc Anh", 0, {19, 9, 2004}, "Da Nang", "ET-E9", "IoT"};
    sinhVien sv4 = {"224402", "Pham Thu Ha", 1, {24, 12, 2004}, "Thanh Hoa", "ET-E9", "IoT"};

    insertSorted(list, sv1);
    insertSorted(list, sv2);
    insertSorted(list, sv3);
    insertSorted(list, sv4);

    // In danh sách sinh viên
    cout << "Danh sach sinh vien: " << endl;
    printList(list);
    return 0;
}
