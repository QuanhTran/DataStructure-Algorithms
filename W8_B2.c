#include <stdio.h>
#include <stdlib.h>

struct node{
    int heSo;
    int bac;
    struct node *next;
};

typedef struct node node;

node *taoDathuc(int heSo, int bac){
    node *newNode = (node*)malloc(sizeof(node));
    newNode->heSo = heSo;
    newNode->bac = bac;
    newNode->next = 0;
    return newNode;
}

// Them da thuc vao DSLK
void themDathuc(node **daThuc, int heSo, int bac){
    node *newNode = taoDathuc(heSo, bac);
    newNode->next = (*daThuc);
    (*daThuc) = newNode;
}

void inDathuc(node *daThuc){
    int laHangtudautien = 1;
    while (daThuc != NULL)
{
    if(!laHangtudautien && daThuc->heSo > 0){
        printf("+");
    }
    printf("%dx^%d", daThuc->heSo, daThuc->bac);
    laHangtudautien = 0;
    daThuc = daThuc->next;
}
   printf("\n"); 
}

int main(){
    node* f = NULL; // Khởi tạo đa thức f
    node* g = NULL; // Khởi tạo đa thức g
    // Khởi tạo f(x) = x^10 + 1
    themDathuc(&f, 1, 10); // Thêm hạng tử x^10
    themDathuc(&f, 1, 0); // Thêm hạng tử 1 (x^0)
    // Khởi tạo g(x) = 10x^15 - 2x^7 + 3x^2 - 7
    themDathuc(&g, 10, 15); // Thêm hạng tử 10x^15
    themDathuc(&g, -2, 7); // Thêm hạng tử -2x^7
    themDathuc(&g, 3, 2); // Thêm hạng tử 3x^2
    themDathuc(&g, -7, 0); // Thêm hạng tử -7 (x^0)
    // In các đa thức
    printf("f(x) = ");
    inDathuc(f); // In đa thức f
    printf("g(x) = ");
    inDathuc(g); // In đa thức g
    return 0; // Kết thúc chương trình
}