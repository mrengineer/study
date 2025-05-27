# Task 15
# База с интерфейсом на питоне

import sqlite3
from datetime import datetime, date

# Создание подключения к базе данных
def create_connection():
    try:
        conn = sqlite3.connect('todo.db')
        return conn
    except sqlite3.Error as e:
        print(f"Ошибка подключения к SQLite: {e}")
    return None

# Создание таблицы tasks
def create_table(conn):
    try:
        cursor = conn.cursor()
        cursor.execute('''
            CREATE TABLE IF NOT EXISTS tasks (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                title TEXT NOT NULL,
                description TEXT,
                status TEXT DEFAULT 'не выполнено',
                deadline DATE,
                created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
            )
        ''')
        conn.commit()
    except sqlite3.Error as e:
        print(f"Ошибка при создании таблицы: {e}")

# Добавление задачи
def add_task(conn):
    title = input("Введите название задачи: ").strip()
    if not title:
        print("Ошибка: название задачи не может быть пустым")
        return
    description = input("Введите описание (необязательно): ").strip() or None
    deadline = input("Введите срок (YYYY-MM-DD, необязательно): ").strip() or None

    if deadline:
        try:
            datetime.strptime(deadline, '%Y-%m-%d')
        except ValueError:
            print("Неверный формат даты.")
            return

    try:
        conn.execute('''
            INSERT INTO tasks (title, description, deadline)
            VALUES (?, ?, ?)
        ''', (title, description, deadline))
        conn.commit()
        print("Задача добавлена.")
    except sqlite3.Error as e:
        print(f"Ошибка при добавлении: {e}")

# Просмотр всех задач
def view_all_tasks(conn):
    cursor = conn.cursor()
    cursor.execute('SELECT id, title, description, status, deadline, created_at FROM tasks ORDER BY created_at DESC')
    tasks = cursor.fetchall()
    if not tasks:
        print("Список задач пуст.")
        return
    for t in tasks:
        print(f"\nID: {t[0]} | Название: {t[1]} | Статус: {t[3]} | Дедлайн: {t[4]}")
        if t[2]:
            print(f"Описание: {t[2]}")
        print(f"Создано: {t[5]}")
        print("-" * 30)

# Изменить статус задачи
def update_status(conn):
    try:
        task_id = int(input("Введите ID задачи: "))
        new_status = input("Введите новый статус (не выполнено/в процессе/выполнено): ").strip()
        if new_status not in ('не выполнено', 'в процессе', 'выполнено'):
            print("Недопустимый статус.")
            return
        conn.execute('UPDATE tasks SET status = ? WHERE id = ?', (new_status, task_id))
        conn.commit()
        print("Статус обновлен.")
    except ValueError:
        print("Ошибка: ID должен быть числом.")
    except sqlite3.Error as e:
        print(f"Ошибка обновления: {e}")

# Удаление задачи
def delete_task(conn):
    try:
        task_id = int(input("Введите ID задачи для удаления: "))
        conn.execute('DELETE FROM tasks WHERE id = ?', (task_id,))
        conn.commit()
        print("Задача удалена.")
    except ValueError:
        print("Ошибка: ID должен быть числом.")
    except sqlite3.Error as e:
        print(f"Ошибка удаления: {e}")

# Поиск задач по названию
def search_tasks(conn):
    keyword = input("Введите строку для поиска в названии: ").strip()
    cursor = conn.cursor()
    cursor.execute("SELECT id, title, status FROM tasks WHERE title LIKE ?", ('%' + keyword + '%',))
    results = cursor.fetchall()
    if results:
        for t in results:
            print(f"ID: {t[0]} | Название: {t[1]} | Статус: {t[2]}")
    else:
        print("Задачи не найдены.")

# Просмотр просроченных задач
def view_overdue_tasks(conn):
    today = date.today().isoformat()
    cursor = conn.cursor()
    cursor.execute('''
        SELECT id, title, status, deadline FROM tasks
        WHERE status = 'не выполнено' AND deadline IS NOT NULL AND deadline < ?
    ''', (today,))
    overdue = cursor.fetchall()
    if overdue:
        print("\nПросроченные задачи:")
        for t in overdue:
            print(f"ID: {t[0]} | Название: {t[1]} | Статус: {t[2]} | Дедлайн: {t[3]}")
    else:
        print("Нет просроченных задач.")

# Главное меню
def main():
    conn = create_connection()
    if conn:
        create_table(conn)
        while True:
            print("\nМеню:")
            print("1. Добавить задачу")
            print("2. Просмотреть все задачи")
            print("3. Изменить статус задачи")
            print("4. Удалить задачу")
            print("5. Поиск задач по названию")
            print("6. Просмотр просроченных задач")
            print("0. Выход")

            choice = input("Выберите действие: ").strip()
            if choice == "1":
                add_task(conn)
            elif choice == "2":
                view_all_tasks(conn)
            elif choice == "3":
                update_status(conn)
            elif choice == "4":
                delete_task(conn)
            elif choice == "5":
                search_tasks(conn)
            elif choice == "6":
                view_overdue_tasks(conn)
            elif choice == "0":
                conn.close()
                print("Выход из программы.")
                break
            else:
                print("Неверный ввод. Попробуйте снова.")
    else:
        print("Не удалось подключиться к базе данных.")

if __name__ == "__main__":
    main()
