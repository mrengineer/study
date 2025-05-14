-- Создание таблицы employees
CREATE TABLE employees (
    id SERIAL PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    position VARCHAR(100),
    salary NUMERIC(10, 2),
    department_id INTEGER
);

-- Вставка данных в таблицу employees
INSERT INTO employees (name, position, salary, department_id) VALUES
('Иван Петров', 'Разработчик', 85000, 1),
('Елена Смирнова', 'Менеджер проектов', 95000, 1),
('Алексей Козлов', 'Аналитик данных', 78000, 2),
('Ольга Новикова', 'Дизайнер', 65000, 3),
('Дмитрий Иванов', 'Тестировщик', 60000, 1);

INSERT INTO employees (name, position, salary) VALUES
('Сергей Бездепартаментный', 'Консультант', 55000),
('Анна Вольная', 'Фрилансер', 70000);

INSERT INTO employees (name, position, salary, department_id) VALUES
('Михаил Директоров', 'Генеральный директор', 250000, NULL),
('Наталья Замова', 'Заместитель директора', 180000, NULL),
('Павел ITшный', 'Руководитель IT-отдела', 150000, 1),
('Ирина Продажная', 'Руководитель отдела продаж', 140000, 2);

INSERT INTO employees (name, position, salary, department_id) VALUES
('Артем Стажеров', 'Стажер-разработчик', 30000, 1),
('Юлия Помощница', 'Ассистент менеджера', 35000, 2),
('Андрей Тестировщик', 'Junior QA', 40000, 1);

INSERT INTO employees (name, position, salary, department_id) VALUES
('Александр Программистов', 'Разработчик', 90000, 1),
('Екатерина Программистова', 'Разработчик', 92000, 1),
('Виктор Аналитиков', 'Аналитик данных', 80000, 2),
('Татьяна Аналитикова', 'Аналитик данных', 82000, 2);

INSERT INTO employees (name, position, salary, department_id) VALUES
('Петр Тестович', 'Тестировщик', 58000, 1),
('Светлана Тестова', 'Тестировщик', 62000, 1),
('Георгий Тестов', 'Тестировщик', 59000, 1);

INSERT INTO employees (name, position, salary, department_id) VALUES
('Максим Богачев', 'Архитектор', 200000, 1),
('Анастасия Беднова', 'Уборщик офиса', 25000, NULL);

-- Создание таблицы departments
CREATE TABLE departments (
    id SERIAL PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    location VARCHAR(100),
    budget NUMERIC(15, 2)
);

-- Средняя зарплата по отделам
CREATE VIEW avg_salary_by_department AS
SELECT department_id, AVG(salary) AS avg_salary
FROM employees
WHERE department_id IS NOT NULL
GROUP BY department_id;

-- Сотрудники вместе с информацией об отделе
CREATE VIEW employee_with_department AS
SELECT e.id, e.name, e.position, e.salary,
       d.name AS department_name, d.location, d.budget
FROM employees e
LEFT JOIN departments d ON e.department_id = d.id;

-- Пять сотрудников с самыми высокими зарплатами
CREATE VIEW top_5_highest_paid AS
SELECT id, name, position, salary
FROM employees
ORDER BY salary DESC
LIMIT 5;

-- Сотрудники, у которых не указан отдел
CREATE VIEW employees_without_department AS
SELECT id, name, position, salary
FROM employees
WHERE department_id IS NULL;

-- Названия отделов и их бюджеты
CREATE VIEW department_budgets AS
SELECT id AS department_id, name AS department_name, budget
FROM departments;

-- Все сотрудники из IT-отдела (можно добавлять, обновлять и удалять)
CREATE VIEW it_employees_updatable AS
SELECT * FROM employees
WHERE department_id = 1
WITH CHECK OPTION;

-- Сравнение зарплаты сотрудника со средней по компании
CREATE VIEW employee_salary_comparison AS
SELECT id, name, position, salary,
       salary - (SELECT AVG(salary) FROM employees) AS salary_diff_from_avg
FROM employees;

-- Суммарные траты на зарплату в отделе и процент от бюджета
CREATE VIEW department_expenses AS
SELECT d.id AS department_id, d.name AS department_name,
       SUM(e.salary) AS total_salary_expense,
       d.budget,
       ROUND(SUM(e.salary) * 100.0 / d.budget, 2) AS budget_usage_percent
FROM departments d
JOIN employees e ON d.id = e.department_id
GROUP BY d.id, d.name, d.budget;

-- Рейтинг сотрудников по зарплате внутри отдела (упрощённый без оконных функций)
CREATE VIEW employee_ranking AS
SELECT e1.id, e1.name, e1.position, e1.salary, e1.department_id,
       (SELECT COUNT(*) FROM employees e2
        WHERE e2.department_id = e1.department_id AND e2.salary > e1.salary) + 1 AS salary_rank
FROM employees e1
WHERE e1.department_id IS NOT NULL;

-- Число сотрудников в разных локациях
CREATE VIEW location_summary AS
SELECT d.location, COUNT(e.id) AS employee_count
FROM employees e
JOIN departments d ON e.department_id = d.id
GROUP BY d.location;

-- Диапазоны зарплат по каждой должности
CREATE VIEW salary_ranges AS
SELECT position, MIN(salary) AS min_salary,
       AVG(salary) AS avg_salary, MAX(salary) AS max_salary
FROM employees
GROUP BY position;

-- Сотрудники из отделов, где траты на зарплату превышают 80% бюджета
CREATE VIEW employees_with_low_budget AS
SELECT e.*
FROM employees e
JOIN (
    SELECT d.id
    FROM departments d
    JOIN employees e ON d.id = e.department_id
    GROUP BY d.id, d.budget
    HAVING SUM(e.salary) > d.budget * 0.8
) over_budget_departments
ON e.department_id = over_budget_departments.id;

-- Количество сотрудников в отделе и процент от общего числа
CREATE VIEW department_headcount_report AS
SELECT d.name AS department_name,
       COUNT(e.id) AS employee_count,
       ROUND(COUNT(e.id) * 100.0 /
             (SELECT COUNT(*) FROM employees WHERE department_id IS NOT NULL), 2) AS percent_of_total
FROM departments d
LEFT JOIN employees e ON d.id = e.department_id
GROUP BY d.name;

-- Все сведения о сотрудниках с привязкой к отделу (если есть)
CREATE VIEW employee_details AS
SELECT e.id, e.name, e.position, e.salary, e.department_id,
       d.name AS department_name, d.location, d.budget
FROM employees e
LEFT JOIN departments d ON e.department_id = d.id;
