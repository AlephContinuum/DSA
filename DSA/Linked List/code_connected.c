#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 100

typedef struct Record {
    char order_date[MAX_LEN];
    char time[MAX_LEN];
    int aging;
    int customer_id;
    char gender[MAX_LEN];
    char device_type[MAX_LEN];
    char customer_login_type[MAX_LEN];
    char product_category[MAX_LEN];
    char product[MAX_LEN];
    float sales;
    int quantity;
    float discount;
    float profit;
    float shipping_cost;
    char order_priority[MAX_LEN];
    char payment_method[MAX_LEN];
    struct Record* next;
} Record;

// Function to create a new record
Record* createRecord(const char* order_date, const char* time, int aging, int customer_id, const char* gender,
                     const char* device_type, const char* customer_login_type, const char* product_category,
                     const char* product, float sales, int quantity, float discount, float profit,
                     float shipping_cost, const char* order_priority, const char* payment_method) {
    Record* newRecord = (Record*)malloc(sizeof(Record));
    if (!newRecord) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    strncpy(newRecord->order_date, order_date, MAX_LEN - 1);
    strncpy(newRecord->time, time, MAX_LEN - 1);
    newRecord->aging = aging;
    newRecord->customer_id = customer_id;
    strncpy(newRecord->gender, gender, MAX_LEN - 1);
    strncpy(newRecord->device_type, device_type, MAX_LEN - 1);
    strncpy(newRecord->customer_login_type, customer_login_type, MAX_LEN - 1);
    strncpy(newRecord->product_category, product_category, MAX_LEN - 1);
    strncpy(newRecord->product, product, MAX_LEN - 1);
    newRecord->sales = sales;
    newRecord->quantity = quantity;
    newRecord->discount = discount;
    newRecord->profit = profit;
    newRecord->shipping_cost = shipping_cost;
    strncpy(newRecord->order_priority, order_priority, MAX_LEN - 1);
    strncpy(newRecord->payment_method, payment_method, MAX_LEN - 1);
    newRecord->next = NULL;
    return newRecord;
}

// Function to insert a record into the linked list
void insertRecord(Record** head, const char* order_date, const char* time, int aging, int customer_id,
                  const char* gender, const char* device_type, const char* customer_login_type,
                  const char* product_category, const char* product, float sales, int quantity,
                  float discount, float profit, float shipping_cost, const char* order_priority,
                  const char* payment_method) {
    Record* newRecord = createRecord(order_date, time, aging, customer_id, gender, device_type,
                                      customer_login_type, product_category, product, sales, quantity,
                                      discount, profit, shipping_cost, order_priority, payment_method);
    newRecord->next = *head;
    *head = newRecord;
}

// Function to search for a record by customer ID
Record* searchRecord(Record* head, int customer_id) {
    while (head) {
        if (head->customer_id == customer_id) return head;
        head = head->next;
    }
    return NULL;
}

// Function to delete a record by customer ID
void deleteRecord(Record** head, int customer_id) {
    Record* current = *head;
    Record* previous = NULL;

    while (current != NULL && current->customer_id != customer_id) {
        previous = current;
        current = current->next;
    }

    if (!current) {
        printf("Record with Customer ID %d not found.\n", customer_id);
        return;
    }

    if (previous == NULL) {
        *head = current->next;
    } else {
        previous->next = current->next;
    }

    free(current);
    printf("Record deleted successfully.\n");
}

// Function to modify a record by customer ID
void modifyRecord(Record* head, int customer_id) {
    Record* rec = searchRecord(head, customer_id);
    if (!rec) {
        printf("Record with Customer ID %d not found.\n", customer_id);
        return;
    }
    printf("Enter new Order Date: ");
    scanf("%s", rec->order_date);
    printf("Enter new Time: ");
    scanf("%s", rec->time);
    printf("Enter new Aging: ");
    scanf("%d", &rec->aging);
    printf("Enter new Gender: ");
    scanf("%s", rec->gender);
    printf("Enter new Device Type: ");
    scanf("%s", rec->device_type);
    printf("Enter new Customer Login Type: ");
    scanf("%s", rec->customer_login_type);
    printf("Enter new Product Category: ");
    scanf("%s", rec->product_category);
    printf("Enter new Product: ");
    scanf("%s", rec->product);
    printf("Enter new Sales: ");
    scanf("%f", &rec->sales);
    printf("Enter new Quantity: ");
    scanf("%d", &rec->quantity);
    printf("Enter new Discount: ");
    scanf("%f", &rec->discount);
    printf("Enter new Profit: ");
    scanf("%f", &rec->profit);
    printf("Enter new Shipping Cost: ");
    scanf("%f", &rec->shipping_cost);
    printf("Enter new Order Priority: ");
    scanf("%s", rec->order_priority);
    printf("Enter new Payment Method: ");
    scanf("%s", rec->payment_method);
    printf("Record modified successfully.\n");
}

// Function to display a single record
void displayRecord(Record* rec) {
    printf("Order_Date: %s\n", rec->order_date);
    printf("Time: %s\n", rec->time);
    printf("Aging: %d\n", rec->aging);
    printf("Customer_Id: %d\n", rec->customer_id);
    printf("Gender: %s\n", rec->gender);
    printf("Device_Type: %s\n", rec->device_type);
    printf("Customer_Login_type: %s\n", rec->customer_login_type);
    printf("Product_Category: %s\n", rec->product_category);
    printf("Product: %s\n", rec->product);
    printf("Sales: %.2f\n", rec->sales);
    printf("Quantity: %d\n", rec->quantity);
    printf("Discount: %.2f\n", rec->discount);
    printf("Profit: %.2f\n", rec->profit);
    printf("Shipping_Cost: %.2f\n", rec->shipping_cost);
    printf("Order_Priority: %s\n", rec->order_priority);
    printf("Payment_method: %s\n", rec->payment_method);
}

// Function to display all records
void displayRecords(Record* head) {
    while (head) {
        printf("-------------------------------------------------\n");
        displayRecord(head);
        head = head->next;
    }
}

// Function to free all records
void freeRecords(Record* head) {
    Record* tmp;
    while (head) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

// Function to load records from a CSV file
void loadFromCSV(Record** head, const char* filename) {
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        printf("CSV file not found. Starting with an empty directory.\n");
        return;
    }
    char line[1024];
    fgets(line, sizeof(line), fp); // Skip header line
    while (fgets(line, sizeof(line), fp)) {
        char order_date[MAX_LEN], time[MAX_LEN], gender[MAX_LEN], device_type[MAX_LEN], customer_login_type[MAX_LEN];
        char product_category[MAX_LEN], product[MAX_LEN], order_priority[MAX_LEN], payment_method[MAX_LEN];
        int aging, customer_id, quantity;
        float sales, discount, profit, shipping_cost;

        char* token = strtok(line, ",");
        if (!token) continue;
        strcpy(order_date, token);

        token = strtok(NULL, ",");
        strcpy(time, token ? token : "");

        token = strtok(NULL, ",");
        aging = token ? atoi(token) : 0;

        token = strtok(NULL, ",");
        customer_id = token ? atoi(token) : 0;

        token = strtok(NULL, ",");
        strcpy(gender, token ? token : "");

        token = strtok(NULL, ",");
        strcpy(device_type, token ? token : "");

        token = strtok(NULL, ",");
        strcpy(customer_login_type, token ? token : "");

        token = strtok(NULL, ",");
        strcpy(product_category, token ? token : "");

        token = strtok(NULL, ",");
        strcpy(product, token ? token : "");

        token = strtok(NULL, ",");
        sales = token ? atof(token) : 0.0;

        token = strtok(NULL, ",");
        quantity = token ? atoi(token) : 0;

        token = strtok(NULL, ",");
        discount = token ? atof(token) : 0.0;

        token = strtok(NULL, ",");
        profit = token ? atof(token) : 0.0;

        token = strtok(NULL, ",");
        shipping_cost = token ? atof(token) : 0.0;

        token = strtok(NULL, ",");
        strcpy(order_priority, token ? token : "");

        token = strtok(NULL, ",");
        if (token) {
            char* p = strchr(token, '\n');
            if (p) *p = 0;
            strcpy(payment_method, token);
        } else {
            payment_method[0] = '\0';
        }

        insertRecord(head, order_date, time, aging, customer_id, gender, device_type, customer_login_type,
                     product_category, product, sales, quantity, discount, profit, shipping_cost,
                     order_priority, payment_method);
    }
    fclose(fp);
    printf("Data loaded from CSV.\n");
}

// Function to save records to a CSV file
void saveToCSV(Record* head, const char* filename) {
    FILE* fp = fopen(filename, "w");
    if (!fp) {
        printf("Unable to open file for writing.\n");
        return;
    }
    fprintf(fp, "Order_Date,Time,Aging,Customer_Id,Gender,Device_Type,Customer_Login_type,Product_Category,Product,Sales,Quantity,Discount,Profit,Shipping_Cost,Order_Priority,Payment_method\n");
    while (head) {
        fprintf(fp, "%s,%s,%d,%d,%s,%s,%s,%s,%s,%.2f,%d,%.2f,%.2f,%.2f,%s,%s\n",
                head->order_date, head->time, head->aging, head->customer_id, head->gender,
                head->device_type, head->customer_login_type, head->product_category,
                head->product, head->sales, head->quantity, head->discount,
                head->profit, head->shipping_cost, head->order_priority,
                head->payment_method);
        head = head->next;
    }
    fclose(fp);
    printf("Data saved to CSV.\n");
}

// Main function
int main() {
    Record* directory = NULL;
    int choice, customer_id;

    loadFromCSV(&directory, "E-Commerce Dataset.csv");

    while (1) {
        printf("\nDirectory Management System\n");
        printf("1. Insert Record\n");
        printf("2. Search Record (by Customer ID)\n");
        printf("3. Delete Record (by Customer ID)\n");
        printf("4. Modify Record (by Customer ID)\n");
        printf("5. Display All Records\n");
        printf("6. Save Records to CSV\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Exiting.\n");
            break;
        }

        switch (choice) {
            case 1: {
                char order_date[MAX_LEN], time[MAX_LEN], gender[MAX_LEN], device_type[MAX_LEN], customer_login_type[MAX_LEN];
                char product_category[MAX_LEN], product[MAX_LEN], order_priority[MAX_LEN], payment_method[MAX_LEN];
                int aging, customer_id, quantity;
                float sales, discount, profit, shipping_cost;

                printf("Enter Order Date: ");
                scanf("%s", order_date);
                printf("Enter Time: ");
                scanf("%s", time);
                printf("Enter Aging: ");
                scanf("%d", &aging);
                printf("Enter Customer ID: ");
                scanf("%d", &customer_id);
                printf("Enter Gender: ");
                scanf("%s", gender);
                printf("Enter Device Type: ");
                scanf("%s", device_type);
                printf("Enter Customer Login Type: ");
                scanf("%s", customer_login_type);
                printf("Enter Product Category: ");
                scanf("%s", product_category);
                printf("Enter Product: ");
                scanf("%s", product);
                printf("Enter Sales: ");
                scanf("%f", &sales);
                printf("Enter Quantity: ");
                scanf("%d", &quantity);
                printf("Enter Discount: ");
                scanf("%f", &discount);
                printf("Enter Profit: ");
                scanf("%f", &profit);
                printf("Enter Shipping Cost: ");
                scanf("%f", &shipping_cost);
                printf("Enter Order Priority: ");
                scanf("%s", order_priority);
                printf("Enter Payment Method: ");
                scanf("%s", payment_method);

                insertRecord(&directory, order_date, time, aging, customer_id, gender, device_type,
                             customer_login_type, product_category, product, sales, quantity,
                             discount, profit, shipping_cost, order_priority, payment_method);
                printf("Record inserted successfully.\n");
                break;
            }
            case 2:
                printf("Enter Customer ID to search: ");
                scanf("%d", &customer_id);
                Record* rec = searchRecord(directory, customer_id);
                if (rec) {
                    displayRecord(rec);
                } else {
                    printf("Record not found.\n");
                }
                break;
            case 3:
                printf("Enter Customer ID to delete: ");
                scanf("%d", &customer_id);
                deleteRecord(&directory, customer_id);
                break;
            case 4:
                printf("Enter Customer ID to modify: ");
                scanf("%d", &customer_id);
                modifyRecord(directory, customer_id);
                break;
            case 5:
                displayRecords(directory);
                break;
            case 6:
                saveToCSV(directory, "E-Commerce Dataset.csv");
                break;
            case 7:
                saveToCSV(directory, "E-Commerce Dataset.csv");
                freeRecords(directory);
                printf("Exiting program.\n");
                return 0;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    freeRecords(directory);
    return 0;
}