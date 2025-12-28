-- setup.sql
-- 1. Users Table
CREATE TABLE
    IF NOT EXISTS users (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        username TEXT NOT NULL UNIQUE,
        email TEXT NOT NULL,
        password TEXT NOT NULL
    );

-- 2. Admins Table
CREATE TABLE
    IF NOT EXISTS admins (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        username TEXT NOT NULL UNIQUE,
        password TEXT NOT NULL
    );

-- 3. Books Table
CREATE TABLE
    IF NOT EXISTS books (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        title TEXT NOT NULL,
        author TEXT NOT NULL,
        price REAL NOT NULL,
        quantity INTEGER NOT NULL
    );

-- 4. Orders Table
CREATE TABLE
    IF NOT EXISTS orders (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        username TEXT NOT NULL,
        book_id INTEGER,
        book_name TEXT,
        price REAL,
        order_date TEXT,
        FOREIGN KEY (username) REFERENCES users (username)
    );

-- Demo Data
INSERT INTO
    admins (username, password)
VALUES
    ('admin', 'password'),
    ('zhd', '123');

INSERT INTO
    users (username, email, password)
VALUES
    ('test', 'test@email', '111'),
    ('zihad', 'zihad@mail', '1234');

INSERT INTO
    books (title, author, price, quantity)
VALUES
    ('BookA', 'AuthorA', 100.0, 5),
    ('BookB', 'AuthorB', 200.0, 3),
    ('BookC', 'AuthorC', 300.0, 7);