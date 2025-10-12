"""
Task 1. ООП Классы, инкапсуляция, свойства и наследование.
"""

from datetime import datetime


# === Task 1. Класс "Книга" с валидацией года издания ===
# Book: хранит данные о книге, проверяет корректность года издания.
class Book:
    def __init__(self, title: str, author: str, year: int):
        self._title = title
        self._author = author
        self.year = year  # валидация через сеттер

    @property
    def title(self):
        """Название книги (только чтение)."""
        return self._title

    @property
    def author(self):
        """Автор книги (только чтение)."""
        return self._author

    @property
    def year(self):
        """Год издания книги (с валидацией)."""
        return self._year

    @year.setter
    def year(self, value: int):
        current_year = datetime.now().year
        if not (1 <= value <= current_year):
            raise ValueError(f"Год издания должен быть от 1 до {current_year}")
        self._year = value

    def display_info(self):
        """Выводит информацию о книге."""
        print(f"Книга: '{self._title}' — {self._author}, {self._year}")


# === Task 2. Класс "Банковский счёт" с защитой баланса ===
# BankAccount: позволяет безопасно пополнять и снимать средства.
class BankAccount:
    def __init__(self, balance: float = 0.0):
        if balance < 0:
            raise ValueError("Начальный баланс не может быть отрицательным")
        self._balance = balance

    def deposit(self, amount: float):
        """Пополнение счёта."""
        if amount <= 0:
            raise ValueError("Сумма пополнения должна быть положительной")
        self._balance += amount

    def withdraw(self, amount: float):
        """Снятие средств со счёта."""
        if amount <= 0:
            raise ValueError("Сумма снятия должна быть положительной")
        if amount > self._balance:
            raise ValueError("Недостаточно средств на счёте")
        self._balance -= amount

    @property
    def balance(self):
        """Выводит текущее состояние счёта."""
        return f"Баланс счета: {self._balance:.2f} руб."

    def __del__(self):
        print(f"Счет закрыт. Остаток: {self.balance}")



# === Task 3. Класс "Автомобиль" с ограничением скорости ===
# Car: хранит параметры машины и контролирует скорость.
class Car:
    def __init__(self, brand: str, model: str, max_speed: int):
        self._brand = brand
        self._model = model
        self._max_speed = max_speed
        self._speed = 0

    @property
    def speed(self):
        """Текущая скорость автомобиля."""
        return self._speed

    @speed.setter
    def speed(self, value: int):
        if value < 0:
            raise ValueError("Скорость не может быть отрицательной")
        if value > self._max_speed:
            raise ValueError("Скорость превышает максимальную")
        self._speed = value

    def accelerate(self, value: int):
        """Увеличивает скорость на заданное значение (до max_speed)."""
        self.speed = min(self._speed + value, self._max_speed)

    def brake(self):
        """Останавливает автомобиль."""
        self._speed = 0

    def __str__(self):
        return f"{self._brand} {self._model}: {self._speed}/{self._max_speed} км/ч"


# === Task 4. Класс "Студент" с динамическим списком оценок ===
# Student: хранит оценки и вычисляет средний балл.
class Student:
    def __init__(self, name: str):
        self._name = name
        self._grades = []

    def add_grade(self, grade: int):
        """Добавляет оценку, если она в диапазоне 1–5."""
        if 1 <= grade <= 5:
            self._grades.append(grade)
        else:
            raise ValueError("Оценка должна быть от 1 до 5")

    @property
    def average_grade(self):
        """Возвращает средний балл."""
        return sum(self._grades) / len(self._grades) if self._grades else 0

    def __str__(self):
        avg = f"{self.average_grade:.2f}"
        return f"Студент {self._name}, Средний балл: {avg}"


# === Task 5. Класс "Фигура" с наследованием поведения ===
# Shape (абстрактный класс) и Rectangle (наследник с площадью).
class Shape:
    def __init__(self, color: str):
        if not color:
            raise ValueError("Цвет не может быть пустым")
        self._color = color

    @property
    def color(self):
        """Цвет фигуры."""
        return self._color

    @color.setter
    def color(self, value: str):
        if not value:
            raise ValueError("Цвет не может быть пустым")
        self._color = value

    def area(self):
        """Абстрактный метод — должен быть переопределён"""
        raise NotImplementedError("Метод должен быть реализован в подклассе")

    def display_info(self):
        """Вывод информации о фигуре."""
        print(f"Фигура цвета {self._color}, площадь {self.area():.2f}")


class Rectangle(Shape):
    def __init__(self, color: str, width: float, height: float):
        super().__init__(color)
        self._width = width
        self._height = height

    def area(self):
        """Вычисляет площадь прямоугольника."""
        return self._width * self._height


# === Проверка работы всех классов ===
def main():
    print("=== Проверка классов ===\n")

    # Task 1
    print("1) Book:")
    book = Book("Мастер и Маргарита", "М. Булгаков", 1967)
    book.display_info()
    print()

    # Task 2
    print("2) BankAccount:")
    acc = BankAccount(1000)
    acc.deposit(500)
    acc.withdraw(200)
    print(acc.balance)
    del acc
    print()

    # Task 3
    print("3) Car:")
    car = Car("Toyota", "Corolla", 180)
    car.accelerate(120)
    print(car)
    car.brake()
    print(car)
    print()

    # Task 4
    print("4) Student:")
    student = Student("Иван")
    for grade in [5, 4, 5, 3]:
        student.add_grade(grade)
    print(student)
    print()

    # Task 5
    print("5) Rectangle (Shape):")
    rect = Rectangle("синий", 3, 4)
    rect.display_info()
    print()


if __name__ == "__main__":
    main()
