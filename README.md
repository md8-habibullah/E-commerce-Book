# E-Commerce Book Management System

A robust, terminal-based E-Commerce application for book inventory management and customer ordering. This system has been migrated from flat-file storage to **SQLite3**, ensuring data integrity, security, and high performance.

## Features

### User Portal

- **Secure Registration**: Create an account with unique credentials.
- **Encrypted-style Login**: Secure session access with limited login attempts.
- **Browse Inventory**: View a real-time list of available books directly from the database.
- **Order Management**: Place orders for books and view your personalized order history.
- **Password Recovery**: Simple recovery tool for forgotten passwords.

### Admin Panel

- **Inventory Control**: Add new books, edit existing details, or remove stock with immediate database updates.
- **Stock Tracking**: Real-time monitoring of price and quantity.
- **Secure Access**: Dedicated admin login portal.

---

## Quick Start

### For Linux:

```bash
gcc *.c -o run -lsqlite3 && ./run
```

### For Advanced Compilation (explicit file listing):

```bash
gcc ./admin.c ./admin_login.c ./cart.c ./forget_pass.c ./login.c ./main.c ./order.c ./register.c ./user.c ./book_controler.c ./total.h -o run -lsqlite3 && ./run
```

---

## System Architecture

The project follows a modular C architecture, utilizing SQLite3 for relational data management.

| Component          | Responsibility                                     |
| ------------------ | -------------------------------------------------- |
| `main.c`           | Entry point and database connection handler.       |
| `book_controler.c` | Core logic for CRUD operations on book data.       |
| `order.c`          | Handles transaction records and history retrieval. |
| `setup.sql`        | Database schema initialization and demo data.      |
| `total.h`          | Global definitions and shared database pointer.    |

---

## Prerequisites

Ensure you have the SQLite development headers installed:

# For Ubuntu/Debian

```bash
sudo apt install libsqlite3-dev
```

# For Fedora/RHEL

```bash
sudo dnf install sqlite-devel
```

# For Arch Linux

```bash
sudo pacman -S sqlite
```

# For Windows (using vcpkg)

```bash
vcpkg install sqlite3:x64-windows
```

# For Windows (using Chocolatey)

```bash
choco install sqlite
```

## Installation & Setup

1. **Clone the repository:**

```bash
git clone <your-repo-link>
cd E-commerce-Book

```

2. **Initialize the Database:**
   Use the provided SQL script to create the tables and seed demo data:

```bash
sqlite3 ecommerce.db < setup.sql

```

3. **Compile the Project:**
   Link the `sqlite3` library during compilation:

```bash
gcc *.c -o run -lsqlite3

```

4. **Run the Application:**

```bash
./run

```

---

## Database Schema

The system utilizes four main tables:

- **`users`**: Stores customer profiles (ID, Username, Email, Password).

- **`admins`**: Stores administrative credentials.

- **`books`**: Inventory details including Title, Author, Price, and Quantity.

- **`orders`**: Transaction logs linked to user accounts.

---

## Security & Optimization

- **SQL Injection Protection**: Implemented using `sqlite3_prepare_v2` and parameter binding (`?`).
- **Data Integrity**: Relational constraints and foreign keys ensure consistent order history.
- **Performance**: Replaced O(N) file-parsing loops with indexed SQL queries for near-instant data retrieval.

---
