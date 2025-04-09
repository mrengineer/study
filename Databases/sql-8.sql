-- Работа №8 от 08.04.2025
-- Для Postgres

-- Создание таблиц

CREATE TABLE Products
(
  Id SERIAL PRIMARY KEY,
  ProductName VARCHAR(30) NOT NULL,
  Company VARCHAR(20) NOT NULL,
  ProductCount INTEGER DEFAULT 0,
  Price NUMERIC NOT NULL
);

CREATE TABLE Customers
(
  Id SERIAL PRIMARY KEY,
  FirstName VARCHAR(30) NOT NULL
);

CREATE TABLE Orders
(
  Id SERIAL PRIMARY KEY,
  ProductId INTEGER NOT NULL REFERENCES Products(Id) ON DELETE CASCADE,
  CustomerId INTEGER NOT NULL REFERENCES Customers(Id) ON DELETE CASCADE,
  CreatedAt DATE NOT NULL,
  ProductCount INTEGER DEFAULT 1,
  Price NUMERIC NOT NULL
);

-- Наполнение таблиц данными

INSERT INTO Products(ProductName, Company, ProductCount, Price) 
VALUES 
  ('iPhone X', 'Apple', 2, 66000),
  ('iPhone 8', 'Apple', 2, 51000),
  ('iPhone 7', 'Apple', 5, 42000),
  ('Galaxy S9', 'Samsung', 2, 56000),
  ('Galaxy S8 Plus', 'Samsung', 1, 46000),
  ('Nokia 9', 'HDM Global', 2, 26000),
  ('Desire 12', 'HTC', 6, 38000);

INSERT INTO Customers(FirstName) 
VALUES 
  ('Tom'), 
  ('Bob'),
  ('Sam');

INSERT INTO Orders(ProductId, CustomerId, CreatedAt, ProductCount, Price) 
VALUES
(
  (SELECT Id FROM Products WHERE ProductName = 'Galaxy S9'),
  (SELECT Id FROM Customers WHERE FirstName = 'Tom'),
  '2017-07-11',
  2,
  (SELECT Price FROM Products WHERE ProductName = 'Galaxy S9')
),
(
  (SELECT Id FROM Products WHERE ProductName = 'iPhone 8'),
  (SELECT Id FROM Customers WHERE FirstName = 'Tom'),
  '2017-07-13',
  1,
  (SELECT Price FROM Products WHERE ProductName = 'iPhone 8')
),
(
  (SELECT Id FROM Products WHERE ProductName = 'iPhone 8'),
  (SELECT Id FROM Customers WHERE FirstName = 'Bob'),
  '2017-07-11',
  1,
  (SELECT Price FROM Products WHERE ProductName = 'iPhone 8')
);

-- Запросы

-- 1. Найти ID клиентов, общая сумма заказов которых превышает 5000
SELECT CustomerId
FROM Orders
GROUP BY CustomerId
HAVING SUM(ProductCount * Price) > 5000;

-- 2. Показать компании, у которых общее количество товаров меньше 10
SELECT Company
FROM Products
GROUP BY Company
HAVING SUM(ProductCount) < 10;

-- 3. Найти даты, когда общая сумма заказов превысила 10000
SELECT CreatedAt
FROM Orders
GROUP BY CreatedAt
HAVING SUM(ProductCount * Price) > 10000;

-- 4. Найти все товары, цена которых выше средней цены всех товаров
SELECT *
FROM Products
WHERE Price > (SELECT AVG(Price) FROM Products);

-- 5. Вывести имена клиентов, у которых нет ни одного заказа
SELECT FirstName
FROM Customers
WHERE Id NOT IN (SELECT DISTINCT CustomerId FROM Orders);

-- 6. Для каждой компании найти товар с максимальной ценой
SELECT Company, ProductName, Price
FROM Products p1
WHERE Price = (
  SELECT MAX(Price)
  FROM Products p2
  WHERE p2.Company = p1.Company
);

-- 7. Найти все заказы, содержащие товары компании 'Apple'
SELECT o.*
FROM Orders o
JOIN Products p ON o.ProductId = p.Id
WHERE p.Company = 'Apple';

-- 8. Вывести компании, у которых количество товаров больше среднего количества товаров на компанию
SELECT Company
FROM Products
GROUP BY Company
HAVING SUM(ProductCount) > (
  SELECT AVG(SumCount) 
  FROM (
    SELECT SUM(ProductCount) AS SumCount 
    FROM Products 
    GROUP BY Company
  ) AS CompanySums
);
