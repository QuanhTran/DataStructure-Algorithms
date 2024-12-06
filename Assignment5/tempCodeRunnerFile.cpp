#include <iostream>
#include <vector>
#include <cmath>

// Hàm kiểm tra số nguyên tố
bool isPrime(int n) {
    if (n < 2) return false;
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) return false;
    }
    return true;
}

// Hàm kiểm tra số nguyên tố Blum: p % 4 == 3
bool isBlumPrime(int p) {
    return isPrime(p) && (p % 4 == 3);
}

// Tạo ra một mảng các số Blum
std::vector<int> generateBlumNumbers(int limit) {
    std::vector<int> blumNumbers;
    for (int p = 2; p < limit; p++) {
        if (isBlumPrime(p)) {
            for (int q = p + 1; q < limit; q++) {
                if (isBlumPrime(q)) {
                    int blum = p * q;
                    if (blum < limit) {
                        blumNumbers.push_back(blum);
                    }
                }
            }
        }
    }
    return blumNumbers;
}

// Hàm kiểm tra xem một số có phải là số Blum không
bool isBlumNumber(int n, const std::vector<int>& blumNumbers) {
    for (int blum : blumNumbers) {
        if (blum == n) return true;
    }
    return false;
}

// Tìm các cặp số Blum có tổng cũng là số Blum
void findBlumPairs(const std::vector<int>& blumNumbers, int limit) {
    std::cout << "Cac cap so Blum co tong la so Blum nho hon " << limit << ":" << std::endl;
    for (int i = 0; i < blumNumbers.size(); i++) {
        for (int j = i + 1; j < blumNumbers.size(); j++) {
            int sum = blumNumbers[i] + blumNumbers[j];
            if (sum < limit && isBlumNumber(sum, blumNumbers)) {
                std::cout << blumNumbers[i] << " + " << blumNumbers[j] << " = " << sum << std::endl;
            }
        }
    }
}

int main() {
    int N = 1000;  // Giới hạn giá trị tìm kiếm số Blum
    std::vector<int> blumNumbers = generateBlumNumbers(N);

    std::cout << "Cac so Blum nho hon " << N << ": ";
    for (int num : blumNumbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    findBlumPairs(blumNumbers, N);

    return 0;
}
