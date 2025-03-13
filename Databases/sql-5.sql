INSERT INTO Products (ProductName, Manufacturer, ProductCount, Price) VALUES
('Galaxy S21', 'Samsung', 15, 1200),
('iPhone 13', 'Apple', 20, 1100),
('Redmi Note 10', 'Xiaomi', 30, 300),
('Mate 40', 'Huawei', 10, 950),
('ThinkPad X1', 'Lenovo', 5, 1500),
('MacBook Air', 'Apple', 8, 999),
('iPad', 'Apple', 12, 700),
('Galaxy Note 20', 'Samsung', 0, 900),
('P40 Pro', 'Huawei', 18, 1100),
('LG OLED TV', 'LG', 25, 2000),
('Aspire 7', 'Acer', 10, 800),
('Legion 5', 'Lenovo', 6, 1200),
('VivoBook', 'Asus', 20, 600),
('Galaxy Tab S7', 'Samsung', 5, 650),
('iMac', 'Apple', 4, 1700),
('ZenBook', 'Asus', 15, 950),
('IdeaPad 3', 'Lenovo', 9, 400),
('MateBook D14', 'Huawei', 11, 750),
('ROG Phone 5', 'Asus', 7, 999),
('Surface Pro', 'Microsoft', 12, 1300);

-- 1) Измените производителя всех товаров с ценой выше 1000 на "PremiumBrands".
UPDATE Products SET Manufacturer = 'PremiumBrands' WHERE Price > 1000;

-- 2) Обновите производителя товара с Id = 10 на "LG".
UPDATE Products SET Manufacturer = 'LG' WHERE Id = 10;

-- 3) Для товара с Id = 7 измените название на "iPad Pro", производителя на "Apple", количество на 25 и цену на 999.99.
UPDATE Products SET ProductName = 'iPad Pro', Manufacturer = 'Apple', ProductCount = 25, Price = 999.99 WHERE Id = 7;

-- 4) Удалите все товары, у которых количество (ProductCount) равно 0.
DELETE FROM Products WHERE ProductCount = 0;

-- 5) Удалите все товары производителя "Huawei".
DELETE FROM Products WHERE Manufacturer = 'Huawei';

-- 6) Удалите все товары, цена которых меньше 50.
DELETE FROM Products WHERE Price < 50;

-- 7) Удалите все товары, цена которых больше 1000 и количество которых меньше 10.
DELETE FROM Products WHERE Price > 1000 AND ProductCount < 10;

-- 8) Удалите товар с названием "Galaxy Note 20".
DELETE FROM Products WHERE ProductName = 'Galaxy Note 20';

-- 9) Удалите товар с Id = 3.
DELETE FROM Products WHERE Id = 3;

-- 10) Удалите все товары с Id от 10 до 20.
DELETE FROM Products WHERE Id BETWEEN 10 AND 20;

-- 11) Удалите все записи из таблицы Products.
DELETE * FROM Products;
