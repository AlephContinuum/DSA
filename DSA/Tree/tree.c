#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024

typedef struct Record {
    char order_date[20];
    char time[20];
    float aging;
    int customer_id;
    char gender[10];
    char device_type[20];
    char login_type[20];
    char product_category[50];
    char product[50];
    float sales; 
    int quantity;
    float discount;
    float profit;
    float shipping_cost;
    char order_priority[20];
    char payment_method[20];
} Record;

typedef struct Node {
    Record data;
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(Record data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

Node* insert(Node* root, Record data) {
    if (root == NULL) return createNode(data);
    if (data.customer_id < root->data.customer_id)
        root->left = insert(root->left, data);
    else if (data.customer_id > root->data.customer_id)
        root->right = insert(root->right, data);
    return root;
}

Node* search(Node* root, int customer_id) {
    if (!root || root->data.customer_id == customer_id) return root;
    if (customer_id < root->data.customer_id)
        return search(root->left, customer_id);
    return search(root->right, customer_id);
}

Node* findMin(Node* root) {
    while (root && root->left) root = root->left;
    return root;
}

Node* delete(Node* root, int customer_id) {
    if (!root) return NULL;
    if (customer_id < root->data.customer_id)
        root->left = delete(root->left, customer_id);
    else if (customer_id > root->data.customer_id)
        root->right = delete(root->right, customer_id);
    else {
        if (!root->left) {
            Node* temp = root->right;
            free(root); return temp;
        } else if (!root->right) {
            Node* temp = root->left;
            free(root); return temp;
        }
        Node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = delete(root->right, temp->data.customer_id);
    }
    return root;
}

void modify(Node* root, int customer_id, Record new_data) {
    Node* node = search(root, customer_id);
    if (node) {
        node->data = new_data;
        printf("Record modified.\n");
    } else {
        printf("Record not found.\n");
    }
}

void printRecord(Record r) {
    printf("ID: %d | Date: %s | Product: %s | Sales: %.2f | Qty: %d | Profit: %.2f\n",
           r.customer_id, r.order_date, r.product, r.sales, r.quantity, r.profit);
}

void inOrder(Node* root) {
    if (root) {
        inOrder(root->left);
        printRecord(root->data);
        inOrder(root->right);
    }
}

void loadCSV(Node** root, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("File open error");
        return;
    }

    char line[MAX_LINE];
    fgets(line, MAX_LINE, file); // skip header

    while (fgets(line, MAX_LINE, file)) {
        Record r;
        char* token = strtok(line, ",");
        int col = 0;

        while (token) {
            switch (col) {
                case 0: strcpy(r.order_date, token); break;
                case 1: strcpy(r.time, token); break;
                case 2: r.aging = atof(token); break;
                case 3: r.customer_id = atoi(token); break;
                case 4: strcpy(r.gender, token); break;
                case 5: strcpy(r.device_type, token); break;
                case 6: strcpy(r.login_type, token); break;
                case 7: strcpy(r.product_category, token); break;
                case 8: strcpy(r.product, token); break;
                case 9: r.sales = atof(token); break;
                case 10: r.quantity = atoi(token); break;
                case 11: r.discount = atof(token); break;
                case 12: r.profit = atof(token); break;
                case 13: r.shipping_cost = atof(token); break;
                case 14: strcpy(r.order_priority, token); break;
                case 15: strcpy(r.payment_method, token); break;
            }
            token = strtok(NULL, ",");
            col++;
        }
        *root = insert(*root, r);
    }

    fclose(file);
}

Record inputRecord() {
    Record r;
    printf("Enter data as prompted:\n");
    printf("Order Date: "); scanf(" %19[^\n]", r.order_date);
    printf("Time: "); scanf(" %19[^\n]", r.time);
    printf("Aging: "); scanf("%f", &r.aging);
    printf("Customer ID: "); scanf("%d", &r.customer_id);
    printf("Gender: "); scanf(" %9s", r.gender);
    printf("Device Type: "); scanf(" %19s", r.device_type);
    printf("Login Type: "); scanf(" %19s", r.login_type);
    printf("Product Category: "); scanf(" %49[^\n]", r.product_category);
    printf("Product: "); scanf(" %49[^\n]", r.product);
    printf("Sales: "); scanf("%f", &r.sales);
    printf("Quantity: "); scanf("%d", &r.quantity);
    printf("Discount: "); scanf("%f", &r.discount);
    printf("Profit: "); scanf("%f", &r.profit);
    printf("Shipping Cost: "); scanf("%f", &r.shipping_cost);
    printf("Order Priority: "); scanf(" %19s", r.order_priority);
    printf("Payment Method: "); scanf(" %19s", r.payment_method);
    return r;
}

int main() {
    Node* root = NULL;
    loadCSV(&root, "E-commerce Dataset.csv");

    int choice, id;
    Record r;

    do {
        printf("\n--- Directory Management System ---\n");
        printf("1. Insert Record\n");
        printf("2. Search Record by Customer ID\n");
        printf("3. Delete Record by Customer ID\n");
        printf("4. Modify Record by Customer ID\n");
        printf("5. Print All Records (In-Order)\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar();  // consume newline

        switch (choice) {
            case 1:
                r = inputRecord();
                root = insert(root, r);
                printf("Record inserted.\n");
                break;
            case 2:
                printf("Enter Customer ID to search: ");
                scanf("%d", &id);
                Node* found = search(root, id);
                if (found) printRecord(found->data);
                else printf("Record not found.\n");
                break;
            case 3:
                printf("Enter Customer ID to delete: ");
                scanf("%d", &id);
                root = delete(root, id);
                printf("If record existed, it was deleted.\n");
                break;
            case 4:
                printf("Enter Customer ID to modify: ");
                scanf("%d", &id);
                getchar(); // consume newline
                r = inputRecord();
                modify(root, id, r);
                break;
            case 5:
                inOrder(root);
                break;
            case 6:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid option.\n");
        }

    } while (choice != 6);

return;
}