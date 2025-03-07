-- Для Postgres
-- В консоли: sudo -u postgres psql

-- Создание базы данных task4
CREATE DATABASE task4;
\c task4;


-- Создание таблицы департаментов
CREATE TABLE departments (
    department_id SERIAL PRIMARY KEY,
    name VARCHAR(255) NOT NULL
);

-- Создание таблицы сотрудников
CREATE TABLE employees (
    employee_id SERIAL PRIMARY KEY,
    name VARCHAR(255) NOT NULL,
    department_id INT REFERENCES departments(department_id),
    birthday DATE
);

-- Создание таблицы зарплат
CREATE TABLE salaries (
    salary_id SERIAL PRIMARY KEY,
    employee_id INT REFERENCES employees(employee_id),
    amount DECIMAL(10, 2) NOT NULL
);

-- Заполнение таблицы departments
INSERT INTO departments (name) VALUES
('Отдел поиска внеземных цивилизаций'),
('Отдел проектирования проектов'),
('Бухгалтерия');

-- Заполнение таблицы employees
INSERT INTO employees (name, department_id, birthday) VALUES
('Иванов Иван Иванович', 1, '1985-06-15'),
('Петров Иван Сергеевич', 2, '1990-09-21'),
('Сидоров Петр Никанорович', 2, '1787-03-12');

-- Заполнение таблицы salaries
INSERT INTO salaries (employee_id, amount) VALUES
(1, 50000.00),
(2, 70000.00),
(3, 45000.00);

-- 1) Вывести все поля из таблицы departments
SELECT * FROM departments;

-- 2) Вывести только ФИО сотрудников, у которых идентификатор департамента равен 2
SELECT name FROM employees WHERE department_id = 2;

-- 3) Вывести все поля из таблицы salaries, для которых amount больше или равно 30000 и строго меньше 70000
SELECT * FROM salaries WHERE amount >= 30000 AND amount < 70000;

-- 4) Вывести все поля из таблицы employees, у которых поле name равно 'Иванов Иван Иванович'
SELECT * FROM employees WHERE name = 'Иванов Иван Иванович';
