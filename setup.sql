 -- 1. Wipe everything for a fresh start
DROP TABLE IF EXISTS
  cart;

DROP TABLE IF EXISTS
  orders;

DROP TABLE IF EXISTS
  books;

DROP TABLE IF EXISTS
  admins;

DROP TABLE IF EXISTS
  users;

-- 2. Users Table
CREATE TABLE
  users (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    username TEXT NOT NULL UNIQUE,
    email TEXT NOT NULL,
    password TEXT NOT NULL
  );

-- 3. Admins Table
CREATE TABLE
  admins (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    username TEXT NOT NULL UNIQUE,
    password TEXT NOT NULL
  );

-- 4. Books Table
CREATE TABLE
  books (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    title TEXT NOT NULL,
    author TEXT NOT NULL,
    price REAL NOT NULL,
    quantity INTEGER NOT NULL
  );

-- 5. Orders Table (Consolidated with Status and Location)
CREATE TABLE
  orders (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    username TEXT NOT NULL,
    book_id INTEGER,
    book_name TEXT,
    price REAL,
    order_date TEXT,
    delivery_address TEXT NOT NULL,
    phone_number TEXT NOT NULL,
    status TEXT DEFAULT 'Pending',
    FOREIGN KEY (username) REFERENCES users (username)
  );

-- 6. Cart Table
CREATE TABLE
  cart (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    username TEXT NOT NULL,
    book_id INTEGER NOT NULL,
    book_name TEXT NOT NULL,
    price REAL NOT NULL,
    FOREIGN KEY (username) REFERENCES users (username),
    FOREIGN KEY (book_id) REFERENCES books (id)
  );

-- 7. Formal Demo Data
-- Admins
INSERT INTO
  admins (username, password)
VALUES
  ('admin', 'password'),
  ('habibi', 'habibi'),
  ('mahruf', 'mahruf'),
  ('gehad', 'gehad');

-- Users (CSE Students context)
INSERT INTO
  users (username, email, password)
VALUES
  ('zihad_cse', 'zihad@university.edu.bd', '1234'),
  ('lovely_student', 'cse_student@bd.com', 'pass123'),
  ('habibi','habibi@mail.com', 'habibi'),
  ('mahruf','mahruf@mail.com', 'mahruf'),
  ('gehad','gehad@mail.com', 'gehad');

-- Books (Academic & Popular Bangladeshi titles)
INSERT INTO
  books (title, author, price, quantity)
VALUES
  ('Data Structures', 'Seymour Lipschutz', 450.0, 20),
  ('Operating Systems', 'Silberschatz', 600.0, 15),
  ('Paradoxical Sajid', 'Arif Azad', 350.0, 100),
  ('Himu Samagra', 'Humayun Ahmed', 850.0, 10),
  (
    'Programming in ANSI C',
    'E. Balagurusamy',
    250.0,
    50
  ),
  ('Atomic Habits', 'James Clear', 300.0, 40);

-- Initial Orders for testing the "Vast info" view
INSERT INTO
  orders (
    username,
    book_id,
    book_name,
    price,
    order_date,
    delivery_address,
    phone_number,
    status
  )
VALUES
  (
    'zihad_cse',
    1,
    'Data Structures',
    450.0,
    '29-12-2025',
    'CSE Hall, Dhaka University',
    '01711223344',
    'Delivered'
  ),
  (
    'lovely_student',
    3,
    'Paradoxical Sajid',
    350.0,
    '29-12-2025',
    'Mirpur-10, Dhaka',
    '01900112233',
    'Pending'
  );