#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1007
#define LINE_LEN 2048

typedef struct Record {
    char order_date[20];
    char time[20];
    char aging[20];
    int customer_id;
    char gender[10];
    char device_type[20];
    char customer_login_type[20];
    char product_category[50];
    char product[50];
    float sales;
    int quantity;
    float discount;
    float profit;
    float shipping_cost;
    char order_priority[10];
    char payment_method[20];
    struct Record* next;
} Record;

Record* hash_table[MAX];

// Hash function
int hash(int customer_id) {
    return customer_id % MAX;
}

// Insert record(solving collision using chaining)
void insert_record(Record r) {
    int index = hash(r.customer_id);
    Record* new_record = (Record*)malloc(sizeof(Record));
    *new_record = r;
    new_record->next = hash_table[index];
    hash_table[index] = new_record;
    printf("Record inserted successfully.\n");
}

// Search record
Record* search_record(int customer_id) {
    int index = hash(customer_id);
    Record* curr = hash_table[index];
    while (curr) {
        if (curr->customer_id == customer_id) return curr;
        curr = curr->next;
    }
    return NULL;
}

// Delete record
int delete_record(int customer_id) {
    int index = hash(customer_id);
    Record* curr = hash_table[index];
    Record* prev = NULL;
    while (curr) {
        if (curr->customer_id == customer_id) {
            if (prev) prev->next = curr->next;
            else hash_table[index] = curr->next;
            free(curr);
            return 1;
        }
        prev = curr;
        curr = curr->next;
    }
    return 0;
}

// Modify record
int modify_record(int customer_id) {
    Record* rec = search_record(customer_id);
    if (rec) {
        printf("Enter new gender: ");
        scanf("%s", rec->gender);
        printf("Enter new device type: ");
        scanf("%s", rec->device_type);
        printf("Enter new product: ");
        scanf("%s", rec->product);
        printf("Enter new sales: ");
        scanf("%f", &rec->sales);
        printf("Enter new quantity: ");
        scanf("%d", &rec->quantity);
        printf("Enter new discount: ");
        scanf("%f", &rec->discount);
        printf("Enter new profit: ");
        scanf("%f", &rec->profit);
        printf("Enter new shipping cost: ");
        scanf("%f", &rec->shipping_cost);
        printf("Enter new order priority: ");
        scanf("%s", rec->order_priority);
        printf("Enter new payment method: ");
        scanf("%s", rec->payment_method);
        return 1;
    }
    return 0;
}

// Display full record with all fields
void display_all() {
    for (int i = 0; i < MAX; i++) {
        Record* curr = hash_table[i];
        while (curr) {
            printf("Order_Date: %s\n", curr->order_date);
            printf("Time: %s\n", curr->time);
            printf("Aging: %s\n", curr->aging);
            printf("Customer_Id: %d\n", curr->customer_id);
            printf("Gender: %s\n", curr->gender);
            printf("Device_Type: %s\n", curr->device_type);
            printf("Customer_Login_type: %s\n", curr->customer_login_type);
            printf("Product_Category: %s\n", curr->product_category);
            printf("Product: %s\n", curr->product);
            printf("Sales: %.2f\n", curr->sales);
            printf("Quantity: %d\n", curr->quantity);
            printf("Discount: %.2f\n", curr->discount);
            printf("Profit: %.2f\n", curr->profit);
            printf("Shipping_Cost: %.2f\n", curr->shipping_cost);
            printf("Order_Priority: %s\n", curr->order_priority);
            printf("Payment_method: %s\n\n", curr->payment_method);
            curr = curr->next;
        }
    }
}

// Save to CSV
void save_to_csv(const char* filename) {
    FILE* fp = fopen(filename, "w");
    if (!fp) {
        printf("Error opening file for writing.\n");
        return;
    }
    fprintf(fp, "Order_Date,Time,Aging,Customer_Id,Gender,Device_Type,Customer_Login_type,Product_Category,Product,Sales,Quantity,Discount,Profit,Shipping_Cost,Order_Priority,Payment_method\n");
    for (int i = 0; i < MAX; i++) {
        Record* curr = hash_table[i];
        while (curr) {
            fprintf(fp, "%s,%s,%s,%d,%s,%s,%s,%s,%s,%.2f,%d,%.2f,%.2f,%.2f,%s,%s\n",
                    curr->order_date, curr->time, curr->aging, curr->customer_id, curr->gender, curr->device_type, curr->customer_login_type, curr->product_category, curr->product, curr->sales, curr->quantity, curr->discount, curr->profit, curr->shipping_cost, curr->order_priority, curr->payment_method);
            curr = curr->next;
        }
    }
    fclose(fp);
    printf("Records saved to CSV.\n");
}

// Load from CSV
void load_from_csv(const char* filename) {
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        printf("File not found. Starting with empty records.\n");
        return;
    }
    char line[LINE_LEN];
    fgets(line, LINE_LEN, fp);  // Skip header
    while (fgets(line, LINE_LEN, fp)) {
        Record r;

        // Strip the newline character
        line[strcspn(line, "\n")] = 0;

        // Tokenize and process fields
        char* token = strtok(line, ",");
        if (token) strcpy(r.order_date, token);

        token = strtok(NULL, ",");
        if (token) strcpy(r.time, token);

        token = strtok(NULL, ",");
        if (token) strcpy(r.aging, token);

        token = strtok(NULL, ",");
        if (token) r.customer_id = atoi(token);

        token = strtok(NULL, ",");
        if (token) strcpy(r.gender, token);

        token = strtok(NULL, ",");
        if (token) strcpy(r.device_type, token);

        token = strtok(NULL, ",");
        if (token) strcpy(r.customer_login_type, token);

        token = strtok(NULL, ",");
        if (token) strcpy(r.product_category, token);

        token = strtok(NULL, ",");
        if (token) strcpy(r.product, token);

        token = strtok(NULL, ",");
        if (token) r.sales = atof(token);

        token = strtok(NULL, ",");
        if (token) r.quantity = atoi(token);

        token = strtok(NULL, ",");
        if (token) r.discount = atof(token);

        token = strtok(NULL, ",");
        if (token) r.profit = atof(token);

        token = strtok(NULL, ",");
        if (token) r.shipping_cost = atof(token);

        token = strtok(NULL, ",");
        if (token) strcpy(r.order_priority, token);

        token = strtok(NULL, ",");
        if (token) strcpy(r.payment_method, token);

        r.next = NULL;
        insert_record(r);
    }
    fclose(fp);
}

int main() {
    int choice, cust_id;
    Record r;
    const char* filename = "E-commerce Dataset.csv";

    load_from_csv(filename);

    while (1) {
        printf("\n--- MENU ---\n");
        printf("1. Insert Record\n");
        printf("2. Search Record\n");
        printf("3. Delete Record\n");
        printf("4. Modify Record\n");
        printf("5. Display All Records\n");
        printf("6. Save Records to CSV\n");
        printf("7. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Order Date: "); scanf("%s", r.order_date);
                printf("Time: "); scanf("%s", r.time);
                printf("Aging: "); scanf("%s", r.aging);
                printf("Customer ID: "); scanf("%d", &r.customer_id);
                printf("Gender: "); scanf("%s", r.gender);
                printf("Device Type: "); scanf("%s", r.device_type);
                printf("Customer Login Type: "); scanf("%s", r.customer_login_type);
                printf("Product Category: "); scanf("%s", r.product_category);
                printf("Product: "); scanf("%s", r.product);
                printf("Sales: "); scanf("%f", &r.sales);
                printf("Quantity: "); scanf("%d", &r.quantity);
                printf("Discount: "); scanf("%f", &r.discount);
                printf("Profit: "); scanf("%f", &r.profit);
                printf("Shipping Cost: "); scanf("%f", &r.shipping_cost);
                printf("Order Priority: "); scanf("%s", r.order_priority);
                printf("Payment Method: "); scanf("%s", r.payment_method);
                insert_record(r);
                break;
            case 2:
                printf("Enter Customer ID to search: "); scanf("%d", &cust_id);
                Record* found = search_record(cust_id);
                if (found)
                    printf("Order_Date: %s\nTime: %s\nAging: %s\nCustomer_Id: %d\nGender: %s\nDevice_Type: %s\nCustomer_Login_type: %s\nProduct_Category: %s\nProduct: %s\nSales: %.2f\nQuantity: %d\nDiscount: %.2f\nProfit: %.2f\nShipping_Cost: %.2f\nOrder_Priority: %s\nPayment_method: %s\n\n",
                           found->order_date, found->time, found->aging, found->customer_id, found->gender, found->device_type, found->customer_login_type, found->product_category, found->product, found->sales, found->quantity, found->discount, found->profit, found->shipping_cost, found->order_priority, found->payment_method);
                else
                    printf("Record not found.\n");
                break;
            case 3:
                printf("Enter Customer ID to delete: "); scanf("%d", &cust_id);
                if (delete_record(cust_id)) printf("Record deleted.\n");
                else printf("Record not found.\n");
                break;
            case 4:
                printf("Enter Customer ID to modify: "); scanf("%d", &cust_id);
                if (modify_record(cust_id)) printf("Record modified.\n");
                else printf("Record not found.\n");
                break;
            case 5:
                display_all();
                break;
            case 6:
                save_to_csv(filename);
                break;
            case 7:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}
