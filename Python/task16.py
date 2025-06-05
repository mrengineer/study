# Task 16
# Скрапинг в базу

import requests
from bs4 import BeautifulSoup   #можно еще поработать через selenium
import sqlite3
import time
import logging

# Настройка логирования
logging.basicConfig(
    filename='scraper.log',
    level=logging.INFO,
    format='%(asctime)s - %(levelname)s - %(message)s'
)

BASE_URL = "https://books.toscrape.com/catalogue/page-{}.html"
BOOK_BASE_URL = "https://books.toscrape.com/catalogue/{}"

# Создание базы данных
conn = sqlite3.connect("books.db")
c = conn.cursor()
c.execute('''
    CREATE TABLE IF NOT EXISTS books (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        title TEXT,
        url TEXT,
        upc TEXT,
        product_type TEXT,
        price_excl_tax TEXT,
        price_incl_tax TEXT,
        tax TEXT,
        availability TEXT,
        num_reviews INTEGER,
        description TEXT
    )
''')
conn.commit()

def get_book_links():
    book_links = []
    for page in range(1, 51):
        url = BASE_URL.format(page)
        logging.info(f"Парсинг страницы каталога: {url}")
        try:
            response = requests.get(url)
            response.raise_for_status()
        except Exception as e:
            logging.error(f"Ошибка при запросе {url}: {e}")
            continue

        soup = BeautifulSoup(response.text, "html.parser")
        articles = soup.select("article.product_pod h3 a")
        for a in articles:
            title = a.get("title")
            relative_url = a.get("href", "").replace("../../../", "")
            book_url = BOOK_BASE_URL.format(relative_url)
            book_links.append((title, book_url))
        time.sleep(0.5)
    return book_links

def parse_book_page(title, url):
    logging.info(f"Парсинг книги: {title} ({url})")
    try:
        response = requests.get(url)
        response.raise_for_status()
    except Exception as e:
        logging.error(f"Ошибка при запросе страницы книги {url}: {e}")
        return None

    soup = BeautifulSoup(response.text, "html.parser")
    desc_tag = soup.select_one("#product_description ~ p")
    description = desc_tag.text.strip() if desc_tag else ""
    rows = soup.select("table.table.table-striped tr")
    data = {row.th.text.strip(): row.td.text.strip() for row in rows}

    return {
        "title": title,
        "url": url,
        "upc": data.get("UPC", ""),
        "product_type": data.get("Product Type", ""),
        "price_excl_tax": data.get("Price (excl. tax)", ""),
        "price_incl_tax": data.get("Price (incl. tax)", ""),
        "tax": data.get("Tax", ""),
        "availability": data.get("Availability", ""),
        "num_reviews": int(data.get("Number of reviews", 0)),
        "description": description
    }

def save_to_db(book):
    if book is None:
        return
    try:
        c.execute('''
            INSERT INTO books (title, url, upc, product_type, price_excl_tax, price_incl_tax, tax, availability, num_reviews, description)
            VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)
        ''', (
            book["title"], book["url"], book["upc"], book["product_type"],
            book["price_excl_tax"], book["price_incl_tax"], book["tax"],
            book["availability"], book["num_reviews"], book["description"]
        ))
        conn.commit()
        logging.info(f"Сохранена книга: {book['title']}")
    except Exception as e:
        logging.error(f"Ошибка при сохранении книги {book['title']}: {e}")

if __name__ == "__main__":
    try:
        links = get_book_links()
        logging.info(f"Найдено книг: {len(links)}")

        for idx, (title, url) in enumerate(links, 1):
            logging.info(f"[{idx}] Обработка: {title}")
            book_data = parse_book_page(title, url)
            save_to_db(book_data)
            time.sleep(0.3)
    finally:
        conn.close()
        logging.info("Готово. Все данные сохранены в books.db")
