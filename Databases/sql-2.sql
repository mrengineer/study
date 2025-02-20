-- Для Postgres

CREATE DATABASE Shop;

-- Перейти к БД shop. Я делал в DBeaver, там это делается в графическом интефрейсе.

-- Таблица пользователей
CREATE TABLE Users (
    UserID SERIAL PRIMARY KEY,
    UserName VARCHAR(255) NOT NULL
);

-- Таблица заказов
CREATE TABLE Orders (
    OrderID SERIAL PRIMARY KEY,
    UserID INT,
    OrderDate TIMESTAMP NOT NULL,
    FOREIGN KEY (UserID) REFERENCES Users(UserID) ON DELETE CASCADE ON UPDATE CASCADE
);

-- Таблица продуктов
CREATE TABLE Products (
    ProductID SERIAL PRIMARY KEY,
    ProductName VARCHAR(255) NOT NULL
);

-- Таблица деталей заказов
CREATE TABLE OrderDetails (
    OrderDetailID SERIAL PRIMARY KEY,
    OrderID INT,
    ProductID INT,
    Quantity INT NOT NULL,
    FOREIGN KEY (OrderID) REFERENCES Orders(OrderID) ON DELETE CASCADE ON UPDATE CASCADE,
    FOREIGN KEY (ProductID) REFERENCES Products(ProductID) ON DELETE CASCADE ON UPDATE CASCADE
);

-- Таблица платежей
CREATE TABLE Payments (
    PaymentID SERIAL PRIMARY KEY,
    OrderID INT,
    PaymentDate TIMESTAMP NOT NULL,
    FOREIGN KEY (OrderID) REFERENCES Orders(OrderID) ON DELETE CASCADE ON UPDATE CASCADE
);
