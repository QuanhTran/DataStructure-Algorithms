#include <iostream>
#include <string.h>

using namespace std;

enum Color {
    Red,
    White,
    Blue
};

int main(){
    enum Color Do = Red;
    enum Color Trang = White;
    enum Color Xanh = Blue;
    std::string a[9]= {"Xanh", "Do", "Xanh", "Do", "Do", "Trang", "Do", "Xanh", "Trang"};
    for(int i=0; i<9; i++){
        int min = i;
        for( int j=i+1; j<9; j++){
            if(a[j] < a[min]){
                min = j;
            }
        }
        std::string temp=a[i];
            a[i] = a[min];
            a[min] = temp;
    }
    for(int i=0; i<9; i++){
    cout << a[i] << " ";
}
    cout << endl;
    return 0;
}