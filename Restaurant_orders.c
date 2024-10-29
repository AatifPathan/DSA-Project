#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 5  // Define the maximum size of the queue

typedef struct {
    int orderID;
    char customerName[30];
    char orderDetails[100];
} Order;

typedef struct {
    Order queue[MAX_SIZE];
    int front;
    int rear;
} CircularQueue;

// Initialize the circular queue
void initializeQueue(CircularQueue* cq) {
    cq->front = -1;
    cq->rear = -1;
}

// Check if the queue is empty
int isEmpty(CircularQueue* cq) {
    return (cq->front == -1);
}

// Check if the queue is full
int isFull(CircularQueue* cq) {
    return ((cq->rear + 1) % MAX_SIZE == cq->front);
}

// Add a new order to the queue
void enqueue(CircularQueue* cq, int orderID, char* customerName, char* orderDetails) {
    if (isFull(cq)) {
        printf("Queue is full! Cannot add more orders.\n");
        return;
    }

    if (isEmpty(cq)) {
        cq->front = cq->rear = 0;
    } else {
        cq->rear = (cq->rear + 1) % MAX_SIZE;
    }

    cq->queue[cq->rear].orderID = orderID;
    strcpy(cq->queue[cq->rear].customerName, customerName);
    strcpy(cq->queue[cq->rear].orderDetails, orderDetails);
    printf("Order added: %d, Customer: %s\n", orderID, customerName);
}

// Remove the oldest order from the queue
void dequeue(CircularQueue* cq) {
    if (isEmpty(cq)) {
        printf("Queue is empty! No orders to serve.\n");
        return;
    }

    printf("Serving order: %d, Customer: %s\n", cq->queue[cq->front].orderID, cq->queue[cq->front].customerName);

    if (cq->front == cq->rear) {  // Only one element in the queue
        cq->front = cq->rear = -1;
    } else {
        cq->front = (cq->front + 1) % MAX_SIZE;
    }
}

// Display all orders in the queue
void displayOrders(CircularQueue* cq) {
    if (isEmpty(cq)) {
        printf("No orders in the queue.\n");
        return;
    }

    printf("Orders in the queue:\n");
    int i = cq->front;
    while (1) {
        printf("Order ID: %d, Customer: %s, Details: %s\n",
               cq->queue[i].orderID, cq->queue[i].customerName, cq->queue[i].orderDetails);

        if (i == cq->rear) break;
        i = (i + 1) % MAX_SIZE;
    }
}

int main() {
    CircularQueue cq;
    initializeQueue(&cq);
    int choice, orderID;
    char customerName[30];
    char orderDetails[100];

    while (1) {
        printf("\n1. Add Order\n2. Serve Order\n3. Display Orders\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Order ID: ");
                scanf("%d", &orderID);
                printf("Enter Customer Name: ");
                scanf(" %[^\n]", customerName);  // Read string with spaces
                printf("Enter Order Details: ");
                scanf(" %[^\n]", orderDetails);   // Read string with spaces
                enqueue(&cq, orderID, customerName, orderDetails);
                break;
            case 2:
                dequeue(&cq);
                break;
            case 3:
                displayOrders(&cq);
                break;
            case 4:
                printf("Exiting the program.\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
