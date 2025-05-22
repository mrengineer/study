-- -------------------------------
-- Создание таблицы сотрудников
-- -------------------------------
CREATE TABLE employees (
    employee_id INT PRIMARY KEY,
    first_name VARCHAR(50),
    last_name VARCHAR(50),
    email VARCHAR(100),
    phone_number VARCHAR(20),
    hire_date DATE,
    job_id VARCHAR(10),
    salary DECIMAL(10,2),
    commission_pct DECIMAL(4,2),
    manager_id INT,
    department_id INT
);

-- Добавление данных в employees
INSERT INTO employees VALUES 
(1, 'John', 'Doe', 'john.doe@example.com', '555-1001', '2020-01-15', 'IT_PROG', 75000, 0.05, NULL, 10),
(2, 'Jane', 'Smith', 'jane.smith@example.com', '555-1002', '2019-03-22', 'SA_REP', 65000, 0.10, 1, 20),
(3, 'Robert', 'Johnson', 'robert.j@example.com', '555-1003', '2021-05-10', 'IT_PROG', 80000, NULL, 1, 10),
(4, 'Emily', 'Davis', 'emily.d@example.com', '555-1004', '2018-11-05', 'HR_REP', 60000, NULL, NULL, 30),
(5, 'Michael', 'Brown', 'michael.b@example.com', '555-1005', '2022-02-18', 'SA_REP', 70000, 0.15, 1, 20);

-- -------------------------------
-- Таблица отделов
-- -------------------------------
CREATE TABLE departments (
    department_id INT PRIMARY KEY,
    department_name VARCHAR(50),
    manager_id INT,
    location_id INT
);

-- Данные по отделам
INSERT INTO departments VALUES
(10, 'IT', 1, 100),
(20, 'Sales', 1, 200),
(30, 'HR', 4, 300),
(40, 'Finance', NULL, 400);

-- -------------------------------
-- Таблица заказов
-- -------------------------------
CREATE TABLE orders (
    order_id INT PRIMARY KEY,
    customer_id INT,
    order_date DATE,
    total_amount DECIMAL(10,2),
    status VARCHAR(20)
);

-- Данные заказов
INSERT INTO orders VALUES
(101, 1, '2023-01-15', 1200.50, 'COMPLETED'),
(102, 2, '2023-01-16', 850.75, 'COMPLETED'),
(103, 1, '2023-01-17', 340.20, 'CANCELLED'),
(104, 3, '2023-01-18', 1560.00, 'PENDING'),
(105, 2, '2023-01-19', 720.30, 'COMPLETED');

-- -------------------------------
-- Таблица истории зарплат
-- -------------------------------
CREATE TABLE salary_history (
    history_id INT PRIMARY KEY,
    employee_id INT,
    old_salary DECIMAL(10,2),
    new_salary DECIMAL(10,2),
    change_date DATE,
    changed_by VARCHAR(50)
);

-- Данные истории зарплат
INSERT INTO salary_history VALUES
(1, 2, 60000, 65000, '2022-06-15', 'admin'),
(2, 3, 75000, 80000, '2022-07-20', 'admin');


-- 1. Стаж сотрудника в годах
CREATE OR REPLACE FUNCTION get_experience_years(emp_id INT)
RETURNS INT AS $$
DECLARE
    years INT;
BEGIN
    SELECT EXTRACT(YEAR FROM AGE(current_date, hire_date)) INTO years
    FROM employees WHERE employee_id = emp_id;
    RETURN years;
END;
$$ LANGUAGE plpgsql;

-- 2. Проверка, существует ли сотрудник с указанной почтой
CREATE OR REPLACE FUNCTION employee_exists(email_input VARCHAR)
RETURNS BOOLEAN AS $$
DECLARE
    result BOOLEAN;
BEGIN
    SELECT EXISTS(SELECT 1 FROM employees WHERE email = email_input) INTO result;
    RETURN result;
END;
$$ LANGUAGE plpgsql;

-- 3. Получить имя и фамилию менеджера по сотруднику
CREATE OR REPLACE FUNCTION get_manager_name(emp_id INT)
RETURNS TEXT AS $$
DECLARE
    mgr_name TEXT;
BEGIN
    SELECT CONCAT(first_name, ' ', last_name) INTO mgr_name
    FROM employees
    WHERE employee_id = (SELECT manager_id FROM employees WHERE employee_id = emp_id);
    RETURN mgr_name;
END;
$$ LANGUAGE plpgsql;

-- 4. Общая сумма заказов клиента
CREATE OR REPLACE FUNCTION total_orders_sum(cust_id INT)
RETURNS DECIMAL(10,2) AS $$
DECLARE
    total DECIMAL(10,2);
BEGIN
    SELECT COALESCE(SUM(total_amount), 0) INTO total
    FROM orders
    WHERE customer_id = cust_id;
    RETURN total;
END;
$$ LANGUAGE plpgsql;

-- 5. Список сотрудников в отделе, разделённый запятыми
CREATE OR REPLACE FUNCTION list_employees_by_department(dept_id INT)
RETURNS TEXT AS $$
DECLARE
    emp_list TEXT;
BEGIN
    SELECT STRING_AGG(CONCAT(first_name, ' ', last_name), ', ') INTO emp_list
    FROM employees
    WHERE department_id = dept_id;
    RETURN emp_list;
END;
$$ LANGUAGE plpgsql;

-- 6. Проверка, является ли сотрудник менеджером
CREATE OR REPLACE FUNCTION is_manager(emp_id INT)
RETURNS BOOLEAN AS $$
DECLARE
    result BOOLEAN;
BEGIN
    SELECT EXISTS(SELECT 1 FROM employees WHERE manager_id = emp_id) INTO result;
    RETURN result;
END;
$$ LANGUAGE plpgsql;

-- 7. Максимальная зарплата в отделе
CREATE OR REPLACE FUNCTION max_salary_by_department(dept_id INT)
RETURNS DECIMAL(10,2) AS $$
DECLARE
    max_salary DECIMAL(10,2);
BEGIN
    SELECT MAX(salary) INTO max_salary
    FROM employees
    WHERE department_id = dept_id;
    RETURN max_salary;
END;
$$ LANGUAGE plpgsql;

-- 8. Налог на зарплату (20% от суммы выше 60000)
CREATE OR REPLACE FUNCTION calc_salary_tax(emp_id INT)
RETURNS DECIMAL(10,2) AS $$
DECLARE
    tax DECIMAL(10,2);
    salary_amt DECIMAL(10,2);
BEGIN
    SELECT salary INTO salary_amt FROM employees WHERE employee_id = emp_id;
    IF salary_amt > 60000 THEN
        tax := (salary_amt - 60000) * 0.20;
    ELSE
        tax := 0;
    END IF;
    RETURN tax;
END;
$$ LANGUAGE plpgsql;

-- 9. Кол-во завершенных заказов клиента
CREATE OR REPLACE FUNCTION completed_orders_count(cust_id INT)
RETURNS INT AS $$
DECLARE
    count_orders INT;
BEGIN
    SELECT COUNT(*) INTO count_orders
    FROM orders
    WHERE customer_id = cust_id AND status = 'COMPLETED';
    RETURN count_orders;
END;
$$ LANGUAGE plpgsql;

-- Проверим парочку
SELECT get_experience_years(2);
SELECT employee_exists('jane.smith@example.com');
