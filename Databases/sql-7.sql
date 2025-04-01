-- Postgres

-- 1) Найти среднее количество страниц
SELECT AVG(pages) AS avg_pages FROM Books;

-- 2) Найти общую стоимость всех книг в наличии
SELECT SUM(price) AS total_price FROM Books WHERE in_stock = true;

-- 3) Найти самый ранний и самый поздний год публикации
SELECT MIN(publication_year) AS earliest_year, MAX(publication_year) AS latest_year FROM Books;

-- 4) Найти общую сумму штрафов за просрочку
SELECT SUM(late_fee) AS total_late_fees FROM Loans;

-- 5) Найти все книги, название которых содержит букву "а" на второй позиции
SELECT * FROM Books WHERE title LIKE '_а%';

-- 6) Найти все книги, автор которых содержит "ов" в любом месте фамилии
SELECT * FROM Books 
JOIN Authors ON Books.author_id = Authors.author_id 
WHERE Authors.name LIKE '%ов%';

-- 7) Найти все книги, название которых заканчивается на "мир" или "ство"
SELECT * FROM Books WHERE title LIKE '%мир' OR title LIKE '%ство';

-- 8) Вывести уникальные значения количества страниц, отсортированные по возрастанию
SELECT DISTINCT pages FROM Books ORDER BY pages ASC;

-- 9) Вывести первые 3 самые толстые книги (по количеству страниц)
SELECT * FROM Books ORDER BY pages DESC LIMIT 3;

-- 10) Вывести все книги, отсортированные по году публикации по возрастанию
SELECT * FROM Books ORDER BY publication_year ASC;

-- 11) Выбрать все книги, количество страниц которых находится в диапазоне от 300 до 500
SELECT * FROM Books WHERE pages BETWEEN 300 AND 500;

-- 12) Выбрать все книги с названиями "1984", "Старик и море" или "Война и мир"
SELECT * FROM Books WHERE title IN ('1984', 'Старик и море', 'Война и мир');
