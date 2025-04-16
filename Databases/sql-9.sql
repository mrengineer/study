-- Работа №9 от 15.04.2025
-- Агрегатные функции и запросы в запросах

-- 0. Создание таблиц

-- Таблица сотрудников
CREATE TABLE employees (
  id SERIAL PRIMARY KEY,
  name VARCHAR(100),
  department VARCHAR(50),
  salary NUMERIC(10,2),
  hire_date DATE
);

-- Таблица проектов
CREATE TABLE projects (
  id SERIAL PRIMARY KEY,
  name VARCHAR(100),
  budget NUMERIC(12,2),
  start_date DATE,
  manager_id INTEGER REFERENCES employees(id)
);

-- Вставка данных
INSERT INTO employees (name, department, salary, hire_date) VALUES
('Иван Петров', 'IT', 85000, '2020-03-15'),
('Мария Сидорова', 'HR', 75000, '2019-07-22'),
('Алексей Иванов', 'IT', 92000, '2018-11-05'),
('Елена Кузнецова', 'Finance', 88000, '2021-01-30'),
('Дмитрий Смирнов', 'IT', 78000, '2022-06-10'),
('Ольга Васильева', 'HR', 82000, '2020-09-17');

INSERT INTO projects (name, budget, start_date, manager_id) VALUES
('Внедрение CRM', 500000, '2023-01-10', 1),
('Обучение персонала', 150000, '2023-03-05', 2),
('Автоматизация отчетов', 300000, '2023-02-15', 3),
('Оптимизация бюджета', 250000, '2023-04-01', 4);

-- 1. Сотрудники, принятые раньше всех
SELECT name, hire_date
FROM employees
WHERE hire_date = (SELECT MIN(hire_date) FROM employees);

-- 2. Проекты с бюджетом выше среднего
SELECT name, budget
FROM projects
WHERE budget > (SELECT AVG(budget) FROM projects);

-- 3. IT-сотрудники с зарплатой выше средней по отделу
SELECT name, salary
FROM employees
WHERE department = 'IT'
  AND salary > (SELECT AVG(salary) FROM employees WHERE department = 'IT');

-- 4. Второй по величине бюджет проекта
SELECT DISTINCT budget
FROM projects
ORDER BY budget DESC
OFFSET 1 LIMIT 1;

-- 5. Сотрудники с зарплатой выше средней в своем отделе
SELECT name, salary, department
FROM employees e
WHERE salary > (
    SELECT AVG(salary)
    FROM employees
    WHERE department = e.department
);

-- 6. Проекты, начавшиеся раньше всех
SELECT name, start_date
FROM projects
WHERE start_date = (SELECT MIN(start_date) FROM projects);

-- 7. Количество сотрудников в каждом отделе
SELECT department, COUNT(*) AS employee_count
FROM employees
GROUP BY department;

-- 8. Сотрудники с зарплатой выше 80% всех зарплат
SELECT name, salary
FROM employees
WHERE salary > (
    SELECT PERCENTILE_CONT(0.8) WITHIN GROUP (ORDER BY salary)
    FROM employees
);

-- 9. Проекты с бюджетом больше, чем у "Обучение персонала"
SELECT name, budget
FROM projects
WHERE budget > (
    SELECT budget FROM projects WHERE name = 'Обучение персонала'
);

-- 10. Последние принятые сотрудники в каждом отделе
SELECT name, department, hire_date
FROM employees e
WHERE hire_date = (
    SELECT MAX(hire_date)
    FROM employees
    WHERE department = e.department
);

-- 11. Средняя зарплата без самого высокооплачиваемого
SELECT AVG(salary)
FROM employees
WHERE salary < (SELECT MAX(salary) FROM employees);

-- 12. Проекты, которыми управляют IT-сотрудники
SELECT p.name
FROM projects p
JOIN employees e ON p.manager_id = e.id
WHERE e.department = 'IT';

-- 13. Сотрудники с зарплатой в пределах 10% от средней
SELECT name, salary
FROM employees
WHERE ABS(salary - (SELECT AVG(salary) FROM employees)) <= (SELECT AVG(salary) * 0.1 FROM employees);

-- 14. Отделы, где нет сотрудников с зарплатой ниже 80000
SELECT department
FROM employees
GROUP BY department
HAVING MIN(salary) >= 80000;

-- 15. Сотрудники, принятые в тот же год, что и "Внедрение CRM"
SELECT name, hire_date
FROM employees
WHERE EXTRACT(YEAR FROM hire_date) = (
    SELECT EXTRACT(YEAR FROM start_date)
    FROM projects
    WHERE name = 'Внедрение CRM'
);

-- 16. Проекты с бюджетом больше суммы всех HR-проектов
SELECT name, budget
FROM projects
WHERE budget > (
    SELECT SUM(p.budget)
    FROM projects p
    JOIN employees e ON p.manager_id = e.id
    WHERE e.department = 'HR'
);

-- 17. Сотрудники, управляющие проектами с бюджетом > 200000
SELECT DISTINCT e.name
FROM employees e
JOIN projects p ON p.manager_id = e.id
WHERE p.budget > 200000;
