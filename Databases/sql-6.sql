INSERT INTO Products (ProductName, Manufacturer, ProductCount, Price) VALUES
('Pixel 6', 'Google', 10, 599.99),
('iPhone 13', 'Apple', 5, 799.99),
('MacBook Air', 'Apple', 3, 999.99),
('Surface Pro 8', 'Microsoft', 2, 1299.99),
('Galaxy S22', 'Samsung', 7, 899.99),
('Redmi Note 11', 'Xiaomi', 12, 299.99),
('Vivo X60', 'Vivo', 8, 499.99),
('Asus ROG Pro', 'Asus', 4, 1799.99),
('Dell XPS 13', 'Dell', 6, 1399.99),
('Lenovo Yoga', 'Lenovo', 9, 1099.99),
('MacBook Pro', 'Apple', 1, 1999.99);


-- 1. Найти все продукты, название которых содержит букву "e" на третьей позиции.
SELECT * FROM Products WHERE ProductName LIKE '__e%';

-- 2. Найти все продукты, производитель которых содержит "oo" в любом месте названия.
SELECT * FROM Products WHERE Manufacturer LIKE '%oo%';

-- 3. Найти все продукты, название которых заканчивается на "Air" или "Pro".
SELECT * FROM Products WHERE ProductName LIKE '%Air' OR ProductName LIKE '%Pro';

-- 4. Вывести уникальные значения количества продуктов на складе, отсортированные по возрастанию.
SELECT DISTINCT ProductCount FROM Products ORDER BY ProductCount ASC;

-- 5. Вывести продукты, начиная с 3-го по порядку, и показать только 4 записи.
SELECT * FROM Products ORDER BY Id LIMIT 4 OFFSET 2;

-- 6. Вывести первые 5 самых дорогих продуктов.
SELECT * FROM Products ORDER BY Price DESC LIMIT 5;

-- 7. Вывести все продукты, отсортированные по цене по убыванию.
SELECT * FROM Products ORDER BY Price DESC;

-- 8. Вывести уникальных производителей из таблицы Products.
SELECT DISTINCT Manufacturer FROM Products;

-- 9. Выбрать все продукты, количество которых на складе находится в диапазоне от 0 до 5.
SELECT * FROM Products WHERE ProductCount BETWEEN 0 AND 5;

-- 10. Выбрать все продукты, названия которых — iPhone 13, MacBook Air или Surface Pro 8.
SELECT * FROM Products WHERE ProductName IN ('iPhone 13', 'MacBook Air', 'Surface Pro 8');

-- 11. Выбрать все продукты, цена которых равна 599.99, 799.99 или 1299.99.
SELECT * FROM Products WHERE Price IN (599.99, 799.99, 1299.99);
