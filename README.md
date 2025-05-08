# DSA
This project is a C-based E-commerce Record Management System that uses a **hash table with chaining** to efficiently store and manage customer transaction data. It employs **hashing** on the `customer_id` to calculate an index where the record will be stored. In case of **hash collisions**, the system uses **singly linked lists** to store multiple records at the same index (a technique known as chaining). Each node in the linked list contains fields like order date, time, aging, customer ID, gender, product details, sales, discount, profit, shipping cost, and more.

The program provides a **menu-driven interface** with the following functionalities:

1. **Insert**: Adds a new record to the hash table.
2. **Search**: Finds and displays a record based on the customer ID.
3. **Delete**: Removes a record from the system.
4. **Modify**: Edits existing record fields.
5. **Display All**: Shows all stored records.
6. **Save to CSV**: Writes all records to a CSV file.
7. **Load from CSV**: Reads records from a CSV file during startup.

This project demonstrates the integration of **data structures** and **file handling** in C, making it ideal for learning core concepts like hashing, collision resolution, and dynamic data management.
