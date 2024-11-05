#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 3  
#define MAX_ORDER_DETAILS 100

typedef struct {
    int orderID;
    char customerName[30];
    char orderDetails[MAX_ORDER_DETAILS];
} Order;

typedef struct {
    Order queue[MAX_SIZE];
    int front;
    int rear;
} CircularQueue;

void initializeQueue(CircularQueue* cq) {
    cq->front = -1;
    cq->rear = -1;
}

int isEmpty(CircularQueue* cq) {
    return (cq->front == -1);
}

int isFull(CircularQueue* cq) {
    return ((cq->rear + 1) % MAX_SIZE == cq->front);
}

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
    printf("Order added: %d, Customer: %s, Items: %s\n", orderID, customerName, orderDetails);
}

void dequeue(CircularQueue* cq) {
    if (isEmpty(cq)) {
        printf("Queue is empty! No orders to serve.\n");
        return;
    }
    printf("Serving order: %d, Customer: %s, Items: %s\n", cq->queue[cq->front].orderID, cq->queue[cq->front].customerName, cq->queue[cq->front].orderDetails);
    if (cq->front == cq->rear) {  
        cq->front = cq->rear = -1;
    } else {
        cq->front = (cq->front + 1) % MAX_SIZE;
    }
}

void displayOrders(CircularQueue* cq) {
    if (isEmpty(cq)) {
        printf("No orders in the queue.\n");
        return;
    }
    printf("Orders in the queue:\n");
    int i = cq->front;
    while (1) {
        printf("Order ID: %d, Customer: %s, Items: %s\n", cq->queue[i].orderID, cq->queue[i].customerName, cq->queue[i].orderDetails);
        if (i == cq->rear) break;
        i = (i + 1) % MAX_SIZE;
    }
}

int main() {
    CircularQueue cq;
    initializeQueue(&cq);
    int choice, orderID;
    char customerName[30];
    char orderDetails[MAX_ORDER_DETAILS];
    const char* menuItems[] = {"Cake", "Coffee", "Tea", "Soft Drink"};
    int menuSize = 4;

    while (1) {
        printf("\n1. Add Order\n2. Serve Order\n3. Display Orders\n4. Exit\nEnter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }
        getchar();

        switch (choice) {
            case 1:
                if (isFull(&cq)) {
                    printf("Queue is full! Cannot add more orders.\n");
                    break;
                }
                printf("Enter Order ID: ");
                if (scanf("%d", &orderID) != 1) {
                    printf("Invalid input for Order ID.\n");
                    while (getchar() != '\n');
                    continue;
                }
                getchar();
                printf("Enter Customer Name: ");
                fgets(customerName, sizeof(customerName), stdin);
                customerName[strcspn(customerName, "\n")] = '\0';
                orderDetails[0] = '\0';
                printf("Available Menu Items:\n");
                for (int i = 0; i < menuSize; i++) {
                    printf("%d. %s\n", i + 1, menuItems[i]);
                }
                printf("Select multiple items by entering their numbers separated by spaces, then press Enter.\n");
                char itemInput[100];
                getchar();
                fgets(itemInput, sizeof(itemInput), stdin);
                itemInput[strcspn(itemInput, "\n")] = '\0';
                char *token = strtok(itemInput, " ");
                while (token != NULL) {
                    int item = atoi(token);
                    if (item >= 1 && item <= menuSize) {
                        if (strlen(orderDetails) > 0) {
                            strcat(orderDetails, ", ");
                        }
                        strcat(orderDetails, menuItems[item - 1]);
                    } else {
                        printf("Invalid choice %d ignored.\n", item);
                    }
                    token = strtok(NULL, " ");
                }
                if (strlen(orderDetails) == 0) {
                    strcpy(orderDetails, "No items selected");
                }
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
