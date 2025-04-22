-- Задание 10

-- 1. Создание таблиц

CREATE TABLE customers (
    customer_id INT PRIMARY KEY,
    customer_name VARCHAR(50),
    email VARCHAR(50)
);

CREATE TABLE orders (
    order_id INT PRIMARY KEY,
    customer_id INT,
    order_date DATE,
    amount DECIMAL(10, 2)
);

-- Вставка данных
INSERT INTO customers (customer_id, customer_name, email) VALUES
    (1, 'Alice', 'alice@email.com'),
    (2, 'Bob', 'bob@email.com'),
    (3, 'Charlie', 'charlie@email.com');

INSERT INTO orders (order_id, customer_id, order_date, amount) VALUES
    (1, 1, '2023-01-15', 100.50),
    (2, 1, '2023-02-20', 200.75),
    (3, 2, '2023-03-10', 150.00),
    (4, NULL, '2023-04-05', 300.00);

-- 2 Найти всех клиентов и их заказы (только те, у кого есть заказы)

SELECT
    c.customer_id,
    c.customer_name,
    o.order_id,
    o.order_date,
    o.amount
FROM
    customers c
INNER JOIN
    orders o ON c.customer_id = o.customer_id;

-- 3. Найти всех клиентов, включая тех, у кого нет заказов

SELECT
    c.customer_id,
    c.customer_name,
    o.order_id,
    o.order_date,
    o.amount
FROM
    customers c
LEFT JOIN
    orders o ON c.customer_id = o.customer_id;

-- 4. Найти все заказы, включая те, у которых нет клиента

SELECT
    o.order_id,
    o.order_date,
    o.amount,
    c.customer_id,
    c.customer_name
FROM
    customers c
RIGHT JOIN
    orders o ON c.customer_id = o.customer_id;



-- Таблицы студентов и специальностей

CREATE TABLE majors (
    major_id INT PRIMARY KEY,
    major_name VARCHAR(50)
);

CREATE TABLE students (
    student_id INT PRIMARY KEY,
    student_name VARCHAR(50),
    major_id INT
);

INSERT INTO majors VALUES
    (1, 'Computer Science'),
    (2, 'Mathematics'),
    (3, 'Physics');

INSERT INTO students VALUES
    (1, 'John', 1),
    (2, 'Alice', 2),
    (3, 'Bob', 1),
    (4, 'Eve', NULL),
    (5, 'Charlie', 3);

--  4. Найти всех студентов и их специальности (неявное соединение)
SELECT s.student_id, s.student_name, m.major_name
FROM students s, majors m
WHERE s.major_id = m.major_id;

-- 5. Найти все специальности, включая те, на которых нет студентов
SELECT m.major_id, m.major_name, s.student_name
FROM majors m
LEFT JOIN students s ON m.major_id = s.major_id;

-- Таблицы авторов и книг

CREATE TABLE authors (
    author_id INT PRIMARY KEY,
    author_name VARCHAR(50)
);

CREATE TABLE books (
    book_id INT PRIMARY KEY,
    book_title VARCHAR(100),
    author_id INT,
    published_year INT
);

INSERT INTO authors VALUES
    (1, 'J.K. Rowling'),
    (2, 'George Orwell'),
    (3, 'Agatha Christie');

INSERT INTO books VALUES
    (1, 'Harry Potter 1', 1, 1997),
    (2, '1984', 2, 1949),
    (3, 'Murder on the Orient Express', 3, 1934),
    (4, 'Harry Potter 2', 1, 1998),
    (5, 'Animal Farm', 2, 1945),
    (6, 'The Great Gatsby', NULL, 1925);

-- Найти все книги и их авторов
SELECT b.book_title, a.author_name, b.published_year
FROM books b
LEFT JOIN authors a ON b.author_id = a.author_id;

-- 7. Найти всех авторов и количество их книг
SELECT a.author_name, COUNT(b.book_id) AS book_count
FROM authors a
LEFT JOIN books b ON a.author_id = b.author_id
GROUP BY a.author_name;

-- 8. Найти все книги, включая те, у которых автор неизвестен
SELECT b.book_title, a.author_name
FROM books b
LEFT JOIN authors a ON b.author_id = a.author_id;



-- 9. Сотрудлники
CREATE TABLE employees2 (
    emp_id INT PRIMARY KEY,
    emp_name VARCHAR(50),
    manager_id INT
);

INSERT INTO employees2 VALUES
    (1, 'CEO', NULL),
    (2, 'Manager 1', 1),
    (3, 'Manager 2', 1),
    (4, 'Employee 1', 2),
    (5, 'Employee 2', 2),
    (6, 'Employee 3', 3);

-- Найти всех сотрудников и их менеджеров
SELECT e.emp_name AS employee, m.emp_name AS manager
FROM employees2 e
LEFT JOIN employees2 m ON e.manager_id = m.emp_id;

-- 10. Таблицы продаж и продуктов

CREATE TABLE products2 (
    product_id INT PRIMARY KEY,
    product_name VARCHAR(50),
    category VARCHAR(50)
);

CREATE TABLE sales (
    sale_id INT PRIMARY KEY,
    product_id INT,
    sale_date DATE,
    quantity INT,
    price DECIMAL(10, 2)
);

INSERT INTO products2 VALUES
    (1, 'Laptop', 'Electronics'),
    (2, 'Smartphone', 'Electronics'),
    (3, 'Desk Chair', 'Furniture'),
    (4, 'Coffee Table', 'Furniture');

INSERT INTO sales VALUES
    (1, 1, '2023-01-10', 2, 1200.00),
    (2, 2, '2023-01-15', 3, 800.00),
    (3, 1, '2023-02-05', 1, 1200.00),
    (4, 3, '2023-02-20', 5, 150.00),
    (5, NULL, '2023-03-01', 10, 5.00);

-- Найти общую выручку по категориям
SELECT p.category, SUM(s.quantity * s.price) AS total_revenue
FROM sales s
LEFT JOIN products2 p ON s.product_id = p.product_id
GROUP BY p.category;

-- Найти все продукты, включая те, которые не продавались
SELECT p.product_name, s.sale_id
FROM products2 p
LEFT JOIN sales s ON p.product_id = s.product_id;

-- 11. Таблицы курсов и преподавателей

CREATE TABLE instructors (
    instructor_id INT PRIMARY KEY,
    instructor_name VARCHAR(50),
    department VARCHAR(50)
);

CREATE TABLE courses (
    course_id INT PRIMARY KEY,
    course_name VARCHAR(50),
    instructor_id INT
);

INSERT INTO instructors VALUES
    (1, 'Dr. Smith', 'Computer Science'),
    (2, 'Dr. Johnson', 'Mathematics'),
    (3, 'Dr. Williams', 'Physics');

INSERT INTO courses VALUES
    (1, 'Database Systems', 1),
    (2, 'Calculus', 2),
    (3, 'Quantum Mechanics', 3),
    (4, 'Algorithms', 1),
    (5, 'Linear Algebra', NULL);

-- Найти все курсы и их преподавателей
SELECT c.course_name, i.instructor_name
FROM courses c
LEFT JOIN instructors i ON c.instructor_id = i.instructor_id;

-- Найти всех преподавателей и количество их курсов
SELECT i.instructor_name, COUNT(c.course_id) AS course_count
FROM instructors i
LEFT JOIN courses c ON i.instructor_id = c.instructor_id
GROUP BY i.instructor_name;




CREATE TABLE airlines (
    airline_id INT PRIMARY KEY,
    airline_name VARCHAR(50)
);

CREATE TABLE flights (
    flight_id INT PRIMARY KEY,
    flight_number VARCHAR(10),
    departure_airport VARCHAR(3),
    arrival_airport VARCHAR(3),
    airline_id INT
);

INSERT INTO airlines VALUES
    (1, 'Delta'),
    (2, 'United'),
    (3, 'American');

INSERT INTO flights VALUES
    (1, 'DL123', 'JFK', 'LAX', 1),
    (2, 'UA456', 'ORD', 'SFO', 2),
    (3, 'AA789', 'DFW', 'MIA', 3),
    (4, 'DL456', 'ATL', 'SEA', 1),
    (5, 'XX999', 'LAX', 'ORD', NULL);

-- Найти все рейсы и авиакомпании
SELECT f.flight_number, f.departure_airport, f.arrival_airport, a.airline_name
FROM flights f
LEFT JOIN airlines a ON f.airline_id = a.airline_id;
