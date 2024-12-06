#include <iostream>
using namespace std;

void merge(int a[], int n1, int b[], int n2, int result[]) {
    int i = 0, j = 0, k = 0;

    while (i < n1 && j < n2) {
        if (a[i] <= b[j]) {
            result[k++] = a[i++];
        } else {
            result[k++] = b[j++];
        }
    }
    while (i < n1) {
        result[k++] = a[i++];
    }

    while (j < n2) {
        result[k++] = b[j++];
    }
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    int a[] = {15, 30, 201, 303}; 
    int b[] = {5, 7, 10, 27, 98, 121, 204, 308}; 
    int n1 = sizeof(a) / sizeof(a[0]); 
    int n2 = sizeof(b) / sizeof(b[0]); 
    int result[n1 + n2];
    merge(a, n1, b, n2, result);
    cout << "Mang da tron la: \n";
    printArray(result, n1 + n2);

    return 0;
}