-- Создание базы данных
CREATE DATABASE functions_practice;
\c functions_practice;

-- Таблица для строковых функций
CREATE TABLE strings_data (
    id SERIAL PRIMARY KEY,
    name VARCHAR(100),
    email VARCHAR(100),
    address TEXT,
    comment TEXT,
    phone VARCHAR(20)
);

INSERT INTO strings_data (name, email, address, comment, phone) VALUES
('Иван Иванов', 'ivan@mail.com', 'ул. Ленина, 10, кв. 5', 'Первый клиент', '+79161234567'),
('Петр Петров', 'petr@gmail.com', 'пр. Мира, 15', NULL, '89161234568'),
('Мария Сидорова', 'maria@yandex.ru', 'ул. Гагарина, 3, кв. 12', 'VIP клиент', '+79161234569'),
('Алексей Алексеев', 'alex@mail.com', 'ул. Садовая, 7', 'Не звонить вечером', '89161234570'),
('Елена Прекрасная', NULL, 'пр. Победы, 33, кв. 45', 'Новый клиент', '+79161234571');

-- Таблица для математических функций
CREATE TABLE math_data (
    id SERIAL PRIMARY KEY,
    product_name VARCHAR(100),
    price NUMERIC(10, 2),
    quantity INTEGER,
    discount NUMERIC(5, 2),
    weight NUMERIC(10, 3)
);

INSERT INTO math_data (product_name, price, quantity, discount, weight) VALUES
('Ноутбук', 75000.00, 5, 10.00, 2.500),
('Смартфон', 45000.00, 10, 5.00, 0.350),
('Наушники', 5000.00, 20, NULL, 0.250),
('Монитор', 30000.00, 8, 15.00, 5.700),
('Клавиатура', 2500.00, 15, 0.00, 0.800);

-- Таблица для дат и времени
CREATE TABLE dates_data (
    id SERIAL PRIMARY KEY,
    event_name VARCHAR(100),
    start_date DATE,
    end_date DATE,
    event_time TIME,
    created_at TIMESTAMP
);

INSERT INTO dates_data (event_name, start_date, end_date, event_time, created_at) VALUES
('Конференция', '2023-05-15', '2023-05-17', '09:00:00', '2023-01-10 10:30:00'),
('Выставка', '2023-06-01', '2023-06-05', '10:00:00', '2023-02-15 14:20:00'),
('Семинар', '2023-04-10', '2023-04-10', '14:30:00', '2023-03-01 09:15:00'),
('Тренинг', '2023-07-20', '2023-07-22', '11:00:00', '2023-01-25 16:45:00'),
('Презентация', '2023-08-12', '2023-08-12', '18:00:00', '2023-04-05 12:10:00');

-- Таблица для условных выражений
CREATE TABLE conditional_data (
    id SERIAL PRIMARY KEY,
    employee_name VARCHAR(100),
    salary NUMERIC(10, 2),
    department VARCHAR(50),
    bonus NUMERIC(10, 2),
    performance_score INTEGER
);

INSERT INTO conditional_data (employee_name, salary, department, bonus, performance_score) VALUES
('Александр', 85000.00, 'IT', 15000.00, 90),
('Ольга', 75000.00, 'HR', 5000.00, 75),
('Дмитрий', 60000.00, 'Sales', NULL, 60),
('Наталья', 95000.00, 'Management', 20000.00, 95),
('Сергей', 50000.00, 'Support', 3000.00, 55);

-- =======================
-- ЗАПРОСЫ: STRINGS_DATA
-- =======================

-- 1. Извлеките домены из email-адресов
SELECT email, SPLIT_PART(email, '@', 2) AS domain FROM strings_data;

-- 2. Преобразуйте имена в верхний регистр, а email в нижний
SELECT UPPER(name), LOWER(email) FROM strings_data;

-- 3. Найдите длину каждого адреса в символах
SELECT address, LENGTH(address) AS address_length FROM strings_data;

-- 4. Извлеките первые 5 символов из каждого комментария
SELECT comment, SUBSTRING(comment FROM 1 FOR 5) AS first_five FROM strings_data;

-- 5. Замените все вхождения 'ул.' на 'улица' в адресах
SELECT REPLACE(address, 'ул.', 'улица') AS modified_address FROM strings_data;

-- 6. Объедините имя и телефон через дефис
SELECT CONCAT(name, ' - ', phone) AS name_phone FROM strings_data;

-- 7. Найдите позицию символа '@' в каждом email
SELECT email, POSITION('@' IN email) AS at_position FROM strings_data;

-- 8. Удалите все пробелы из телефонных номеров
SELECT phone, REPLACE(phone, ' ', '') AS no_spaces FROM strings_data;

-- 9. Извлеките фамилии из поля name
SELECT name, SPLIT_PART(name, ' ', 2) AS lastname FROM strings_data;

-- 10. Для записей с NULL в комментарии выведите 'Нет комментария'
SELECT COALESCE(comment, 'Нет комментария') AS comment_display FROM strings_data;

-- ====================
-- ЗАПРОСЫ: MATH_DATA
-- ====================

-- 1. Конечная цена с учетом скидки
SELECT product_name, price - (price * COALESCE(discount, 0)/100) AS final_price FROM math_data;

-- 2. Общая стоимость товара
SELECT product_name, price * quantity AS total_value FROM math_data;

-- 3. Округлите цены до ближайшей 1000
SELECT product_name, ROUND(price, -3) AS rounded_price FROM math_data;

-- 4. Логарифм цены по основанию 10
SELECT product_name, LOG(10, price) AS log10_price FROM math_data;

-- 5. Квадратный корень из веса
SELECT product_name, SQRT(weight) AS sqrt_weight FROM math_data;

-- 6. Средняя цена товаров без скидки
SELECT AVG(price) AS avg_price FROM math_data;

-- 7. На сколько процентов ноутбук дороже смартфона
SELECT 
    100.0 * (n.price - s.price) / s.price AS percentage_more
FROM 
    (SELECT price FROM math_data WHERE product_name = 'Ноутбук') n,
    (SELECT price FROM math_data WHERE product_name = 'Смартфон') s;

-- 8. Округлите вес до 1 знака
SELECT product_name, ROUND(weight, 1) AS rounded_weight FROM math_data;

-- 9. Разница между макс и мин ценой
SELECT MAX(price) - MIN(price) AS price_range FROM math_data;

-- 10. НДС 18% от цены
SELECT product_name, price * 0.18 AS VAT FROM math_data;

-- ====================
-- ЗАПРОСЫ: DATES_DATA
-- ====================

-- 1. Продолжительность событий
SELECT event_name, end_date - start_date AS duration_days FROM dates_data;

-- 2. Извлеките год, месяц, день
SELECT event_name, EXTRACT(YEAR FROM start_date) AS year,
       EXTRACT(MONTH FROM start_date) AS month,
       EXTRACT(DAY FROM start_date) AS day FROM dates_data;

-- 3. Добавьте 7 дней к дате начала
SELECT event_name, start_date + INTERVAL '7 days' AS new_start_date FROM dates_data;

-- 4. Разница в месяцах между created_at и start_date
SELECT event_name, DATE_PART('month', AGE(start_date, created_at)) AS month_diff FROM dates_data;

-- 5. День недели начала события
SELECT event_name, TO_CHAR(start_date, 'Day') AS weekday FROM dates_data;

-- 6. Извлеките час из времени
SELECT event_name, EXTRACT(HOUR FROM event_time) AS hour FROM dates_data;

-- 7. События текущего года
SELECT * FROM dates_data WHERE EXTRACT(YEAR FROM start_date) = EXTRACT(YEAR FROM CURRENT_DATE);

-- 8. Добавьте 2ч30м к времени
SELECT event_name, event_time + INTERVAL '2 hours 30 minutes' AS new_time FROM dates_data;

-- 9. Формат даты как "15 May 2023"
SELECT event_name, TO_CHAR(start_date, 'DD Mon YYYY') AS formatted_date FROM dates_data;

-- 10. Сколько дней до события от created_at
SELECT event_name, start_date - created_at::date AS days_until_event FROM dates_data;

-- ==========================
-- ЗАПРОСЫ: CONDITIONAL_DATA
-- ==========================

-- 1. Классификация по зарплате
SELECT employee_name,
       CASE 
           WHEN salary < 60000 THEN 'Junior'
           WHEN salary BETWEEN 60000 AND 90000 THEN 'Middle'
           ELSE 'Senior'
       END AS level
FROM conditional_data;

-- 2. Замените NULL бонусы на 0
SELECT employee_name, COALESCE(bonus, 0) AS safe_bonus FROM conditional_data;

-- 3. CASE по performance_score
SELECT employee_name,
       CASE 
           WHEN performance_score < 60 THEN 'Low'
           WHEN performance_score <= 80 THEN 'Medium'
           ELSE 'High'
       END AS performance_level
FROM conditional_data;

-- 4. Разница с средней по отделу
SELECT c.employee_name, 
       c.salary - (SELECT AVG(salary) FROM conditional_data WHERE department = c.department) AS diff_avg
FROM conditional_data c;

-- 5. GREATEST из зарплаты и бонуса
SELECT employee_name, GREATEST(salary, COALESCE(bonus, 0)) AS max_value FROM conditional_data;

-- 6. Подсчет сотрудников с зарплатой >70000 по отделам
SELECT department, COUNT(*) FILTER (WHERE salary > 70000) AS count_high_paid FROM conditional_data GROUP BY department;

-- 7. Премия как 10% или текущий бонус
SELECT employee_name,
       CASE 
           WHEN bonus IS NULL THEN salary * 0.10
           ELSE bonus
       END AS final_bonus
FROM conditional_data;

-- 8. Категории отделов
SELECT employee_name,
       CASE 
           WHEN department IN ('IT', 'Management') THEN 'Tech'
           ELSE 'Non-tech'
       END AS dept_category
FROM conditional_data;

-- 9. Сотрудники выше среднего по отделу
SELECT * FROM conditional_data c
WHERE performance_score > (
    SELECT AVG(performance_score)
    FROM conditional_data
    WHERE department = c.department
);
