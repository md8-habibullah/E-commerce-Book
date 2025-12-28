# E-Commerce Book Management System

A robust, terminal-based E-Commerce application for book inventory management and customer ordering. This system has been migrated from flat-file storage to **SQLite3**, ensuring data integrity, transaction security, and high performance.

**Repository URL:** https://github.com/md8-habibullah/E-commerce-Book.git

---

## Features

### User Portal
* **Secure Authentication:** User registration and login with encrypted-style session handling.
* **Shopping Cart System:** Users can add multiple items to a cart, view summaries, and checkout in bulk.
* **Tiered Discount System:** Automatic discounts applied at checkout based on total order value:
    * 20% Discount for orders above 1999.00 Taka
    * 10% Discount for orders above 1499.00 Taka
    * 5% Discount for orders above 999.00 Taka
* **Comprehensive Order History:** Tracks order status (Pending, Delivered, Cancelled), delivery addresses, and contact numbers.
* **Account Recovery:** Functionality to retrieve lost passwords using email verification.

### Admin Panel
* **Inventory Management:** Add, edit, or delete books from the live database.
* **Order Fulfillment:** View detailed order lists including delivery addresses and phone numbers.
* **Status Updates:** Administrators can update order statuses (e.g., from Pending to Delivered).
* **Secure Access:** Dedicated login portal for administrative tasks.

---

## Installation and Setup

### 1. Windows Environment

To run this application on Windows, you must have a C compiler (GCC) and the SQLite3 library installed.

#### Prerequisites
It is recommended to use **MSYS2** or **MinGW** to obtain GCC. You can install SQLite3 via a package manager like Chocolatey or vcpkg.

**Using Chocolatey:**
```powershell
choco install sqlite

```

#### Compilation and Execution

1. **Clone the Repository:**
```powershell
git clone https://github.com/md8-habibullah/E-commerce-Book.git
cd E-commerce-Book

```


2. **Initialize the Database:**
Run the SQL setup script to create the required tables and insert demo data.
```powershell
sqlite3 ecommerce.db < setup.sql

```


3. **Compile the Application:**
Ensure you link the SQLite3 library.
```powershell
gcc *.c -o run.exe -lsqlite3

```


4. **Run:**
```powershell
./run.exe

```



### 2. Linux Environment

You must install the GCC compiler and SQLite development headers. Choose the command corresponding to your distribution.

#### Install Dependencies

**Debian / Ubuntu / Kali / Mint:**

```bash
sudo apt update
sudo apt install build-essential libsqlite3-dev

```

**Fedora / RHEL / CentOS / AlmaLinux:**

```bash
sudo dnf install gcc sqlite-devel

```

**Arch Linux / Manjaro / EndeavourOS:**

```bash
sudo pacman -S base-devel sqlite

```

#### Compilation and Execution

1. **Clone the Repository:**
```bash
git clone https://github.com/md8-habibullah/E-commerce-Book.git
cd E-commerce-Book

```


2. **Initialize the Database:**
```bash
sqlite3 ecommerce.db < setup.sql

```


3. **Compile the Application:**
```bash
gcc *.c -o run -lsqlite3

```


4. **Run:**
```bash
./run

```



---

## System Architecture

The project utilizes a modular C architecture backed by a relational SQLite3 database.

| Component | Responsibility |
| --- | --- |
| **main.c** | Application entry point and database connection lifecycle. |
| **cart.c** | Manages shopping cart operations, bill calculation, and discount logic. |
| **order.c** | Handles order processing, delivery details, and history retrieval. |
| **book_controler.c** | Performs CRUD operations (Create, Read, Update, Delete) on inventory. |
| **user.c** | Manages the user dashboard and navigation logic. |
| **admin.c** | Provides the administrative interface for stock and order management. |
| **setup.sql** | Database schema definition and initial data seeding. |

---

## Database Schema

The system uses a relational schema with five primary tables:

1. **users**: Stores customer credentials (ID, Username, Email, Password).
2. **admins**: Stores administrative access credentials.
3. **books**: Inventory data including Title, Author, Price, and Stock Quantity.
4. **cart**: Temporary storage for items selected by the user before checkout.
5. **orders**: Permanent transaction records containing:
* Product Details
* Price (post-discount)
* Delivery Address & Phone Number
* Order Status (Pending/Delivered/Cancelled)



---

## Security and Optimization

* **SQL Injection Prevention:** All user inputs are sanitized using `sqlite3_prepare_v2` and parameter binding.
* **Data Integrity:** Foreign key constraints ensure that cart items and orders are strictly linked to valid users.
* **Performance:** Indexed SQL queries replace file-based parsing, offering immediate data retrieval and updates.

---
