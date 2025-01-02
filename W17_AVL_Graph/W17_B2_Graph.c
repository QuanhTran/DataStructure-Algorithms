#include <stdio.h>
#include <stdlib.h>

// Cấu trúc cho các nút trong danh sách kề
typedef struct AdjListNode {
    int dest;
    struct AdjListNode* next;
} AdjListNode;

// Cấu trúc cho danh sách kề
typedef struct AdjList {
    AdjListNode* head;
} AdjList;

// Cấu trúc cho đồ thị
typedef struct Graph {
    int V; // Số lượng đỉnh
    AdjList* array;
} Graph;

// Hàm tạo một nút danh sách kề mới
AdjListNode* newAdjListNode(int dest) {
    AdjListNode* newNode = (AdjListNode*) malloc(sizeof(AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

// Hàm tạo đồ thị với V đỉnh
Graph* createGraph(int V) {
    Graph* graph = (Graph*) malloc(sizeof(Graph));
    graph->V = V;

    // Tạo mảng danh sách kề
    graph->array = (AdjList*) malloc(V * sizeof(AdjList));

    // Khởi tạo mỗi danh sách kề là NULL
    for (int i = 0; i < V; ++i)
        graph->array[i].head = NULL;

    return graph;
}

// Hàm thêm cạnh vào đồ thị (đồ thị vô hướng)
void addEdge(Graph* graph, int src, int dest) {
    // Thêm cạnh từ src đến dest
    AdjListNode* newNode = newAdjListNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    // Thêm cạnh từ dest đến src
    newNode = newAdjListNode(src);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

// Cấu trúc cho hàng đợi (Queue) dùng trong BFS
typedef struct Queue {
    int front, rear, size;
    unsigned capacity;
    int* array;
} Queue;

// Hàm tạo hàng đợi
Queue* createQueue(unsigned capacity) {
    Queue* queue = (Queue*) malloc(sizeof(Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0; 
    queue->rear = capacity - 1; // vị trí cuối
    queue->array = (int*) malloc(queue->capacity * sizeof(int));
    return queue;
}

// Kiểm tra hàng đợi có rỗng không
int isEmptyQueue(Queue* queue) {
    return (queue->size == 0);
}

// Thêm phần tử vào hàng đợi
void enqueue(Queue* queue, int item) {
    if (queue->size == queue->capacity)
        return;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size += 1;
}

// Loại bỏ phần tử khỏi hàng đợi
int dequeue(Queue* queue) {
    if (isEmptyQueue(queue))
        return -1;
    int item = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size -= 1;
    return item;
}

// Cấu trúc cho ngăn xếp (Stack) dùng trong DFS
typedef struct Stack {
    int top;
    int capacity;
    int* array;
} Stack;

// Hàm tạo ngăn xếp
Stack* createStack(int capacity) {
    Stack* stack = (Stack*) malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*) malloc(stack->capacity * sizeof(int));
    return stack;
}

// Kiểm tra ngăn xếp có rỗng không
int isEmptyStack(Stack* stack) {
    return stack->top == -1;
}

// Thêm phần tử vào ngăn xếp
void push(Stack* stack, int item) {
    if (stack->top == stack->capacity - 1)
        return;
    stack->array[++stack->top] = item;
}

// Loại bỏ phần tử khỏi ngăn xếp
int pop(Stack* stack) {
    if (isEmptyStack(stack))
        return -1;
    return stack->array[stack->top--];
}

// Hàm BFS
void BFS(Graph* graph, int start) {
    int* visited = (int*) malloc(graph->V * sizeof(int));
    for(int i = 0; i < graph->V; i++)
        visited[i] = 0; // 0 tương đương false

    Queue* queue = createQueue(graph->V);
    enqueue(queue, start);
    visited[start] = 1; // 1 tương đương true

    printf("BFS: ");
    while (!isEmptyQueue(queue)) {
        int current = dequeue(queue);
        printf("%d ", current);

        AdjListNode* crawl = graph->array[current].head;
        while (crawl != NULL) {
            int adjVertex = crawl->dest;
            if (!visited[adjVertex]) {
                visited[adjVertex] = 1;
                enqueue(queue, adjVertex);
            }
            crawl = crawl->next;
        }
    }
    printf("\n");
    free(visited);
    free(queue->array);
    free(queue);
}

// Hàm DFS
void DFS(Graph* graph, int start) {
    int* visited = (int*) malloc(graph->V * sizeof(int));
    for(int i = 0; i < graph->V; i++)
        visited[i] = 0; // 0 tương đương false

    Stack* stack = createStack(graph->V);
    push(stack, start);

    printf("DFS: ");
    while (!isEmptyStack(stack)) {
        int current = pop(stack);

        if (!visited[current]) {
            printf("%d ", current);
            visited[current] = 1; // 1 tương đương true
        }

        AdjListNode* crawl = graph->array[current].head;
        while (crawl != NULL) {
            int adjVertex = crawl->dest;
            if (!visited[adjVertex]) {
                push(stack, adjVertex);
            }
            crawl = crawl->next;
        }
    }
    printf("\n");
    free(visited);
    free(stack->array);
    free(stack);
}

int main() {
    int V, E;
    printf("Nhập số đỉnh: ");
    scanf("%d", &V);
    printf("Nhập số cạnh: ");
    scanf("%d", &E);

    Graph* graph = createGraph(V);

    printf("Nhập các cạnh (u v):\n");
    for(int i = 0; i < E; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(graph, u, v);
    }

    int start;
    printf("Nhập đỉnh bắt đầu: ");
    scanf("%d", &start);

    BFS(graph, start);
    DFS(graph, start);

    // Giải phóng bộ nhớ
    for(int i = 0; i < V; i++) {
        AdjListNode* crawl = graph->array[i].head;
        while(crawl != NULL) {
            AdjListNode* temp = crawl;
            crawl = crawl->next;
            free(temp);
        }
    }
    free(graph->array);
    free(graph);

    return 0;
}
