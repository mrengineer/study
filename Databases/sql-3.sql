-- Для Postgres
-- В консоли: sudo -u postgres psql


-- Создание
CREATE DATABASE OnlineStore;

\c onlinestore;


CREATE TABLE Users (
    UserId SERIAL PRIMARY KEY,
    UserName VARCHAR(50) NOT NULL,
    Email VARCHAR(100) NOT NULL UNIQUE,
    RegistrationDate TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);


CREATE TABLE Products (
    ProductId SERIAL PRIMARY KEY,
    ProductName VARCHAR(100) NOT NULL,
    Price DECIMAL(10, 2) NOT NULL,
    StockQuantity INT NOT NULL
);


CREATE TABLE Orders (
    OrderId SERIAL PRIMARY KEY,
    UserId INT NOT NULL,
    OrderDate TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    TotalAmount DECIMAL(10, 2) NOT NULL,
    FOREIGN KEY (UserId) REFERENCES Users(UserId) ON DELETE CASCADE
);


CREATE TABLE OrderItems (
    OrderItemId SERIAL PRIMARY KEY,
    OrderId INT NOT NULL,
    ProductId INT NOT NULL,
    Quantity INT NOT NULL,
    Price DECIMAL(10, 2) NOT NULL,
    FOREIGN KEY (OrderId) REFERENCES Orders(OrderId) ON DELETE CASCADE,
    FOREIGN KEY (ProductId) REFERENCES Products(ProductId) ON DELETE CASCADE
);


INSERT INTO Users (UserName, Email) VALUES
('Vasly', 'vasya88@email.com'),
('Dimitry', 'dima@example.com'),
('Boris', 'boris@example.com');


INSERT INTO Products (ProductName, Price, StockQuantity) VALUES
('iPhone 16', 1200.00, 12),
('Lamp', 25.50, 25),
('Headphones', 152.00, 42);


INSERT INTO Orders (UserId, TotalAmount) VALUES
(1, 1200.00),
(2, 255.00),
(3, 152.00);


INSERT INTO OrderItems (OrderId, ProductId, Quantity, Price) VALUES
(1, 1, 1, 1200.00),
(1, 2, 1, 255.00),
(2, 3, 2, 152.00);
