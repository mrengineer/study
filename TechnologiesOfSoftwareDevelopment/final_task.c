#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//Выбрал 17е задание с очередью.

#define MAX_QUEUE 10  // Размер очереди

// структура клиента
typedef struct {
    int id;          // номер клиента
    int serviceTime; // время обслуживания
} Client;

// структура очереди
typedef struct {
    Client data[MAX_QUEUE];
    int front;   // начало очереди
    int rear;    // конец очереди
    int count;   // кол-во клиентов
} Queue;

// инициализация очереди
void initQueue(Queue *q) {
    q->front = 0;
    q->rear = -1;
    q->count = 0;
}

// проверка на пустоту
int isEmpty(Queue *q) {
    return q->count == 0;
}

// проверка на заполненность
int isFull(Queue *q) {
    return q->count == MAX_QUEUE;
}

// добавить клиента в очередь (FIFO)
void add_to_queue(Queue *q, Client c) {
    if (isFull(q)) {
        printf("Queue is FULL, client %d not added\n", c.id);
        return;
    }

    q->rear = (q->rear + 1) % MAX_QUEUE;
    q->data[q->rear] = c;
    q->count++;

    printf("Client %d added, service time %d\n", c.id, c.serviceTime);
}

// обслужить клиента
void remove_from_queue(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty, no clients\n");
        return;
    }

    Client c = q->data[q->front];
    q->front = (q->front + 1) % MAX_QUEUE;
    q->count--;

    printf("Client %d served\n", c.id);
}

// имитация работы очереди
void simulateQueue() {
    Queue q;
    Client c;
    int nextId = 1;
    int step;

    initQueue(&q);
    srand(time(NULL));

    for (step = 0; step < 15; step++) {
        printf("\nStep %d\n", step + 1);

        // случайно добавляем клиента
        if (rand() % 2) {
            c.id = nextId++;
            c.serviceTime = rand() % 5 + 1;
            add_to_queue(&q, c);
        }

        // случайно обслуживаем клиента
        if (rand() % 2) {
            remove_from_queue(&q);
        }

        printf("Clients in queue: %d\n", q.count);
    }
}

int main() {
    printf("Queue simulation (FIFO)\n");
    simulateQueue();
    return 0;
}
