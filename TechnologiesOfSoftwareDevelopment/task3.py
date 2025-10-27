# task13.py
# Примеры классов с использованием свойств, статических методов и магии

# ------------------------------
# Задача 1. Класс Car с атрибутом класса и статическим методом
# ------------------------------
class Car:

    total_cars = 0

    def __init__(self, brand: str, model: str, year: int):
        self._brand = brand
        self._model = model
        self._year = year
        Car.total_cars += 1

    # Все данные — через property
    @property
    def brand(self):
        return self._brand

    @property
    def model(self):
        return self._model

    @property
    def year(self):
        return self._year

    @staticmethod
    def is_vintage(year: int) -> bool:
        return (2025 - year) > 30

    def __str__(self):
        return f"Car({self._brand}-{self._model}, year={self._year})"


# ------------------------------
# Задача 2. Класс Temperature с магическими методами и статическими конвертерами
# ------------------------------
class Temperature:

    def __init__(self, celsius: float):
        self._celsius = celsius

    @property
    def celsius(self):
        return self._celsius

    @staticmethod
    def from_fahrenheit(f: float):
        c = (f - 32) * 5 / 9
        return Temperature(c)

    @staticmethod
    def from_kelvin(k: float):
        c = k - 273.15
        return Temperature(c)

    def __add__(self, other):
        if isinstance(other, Temperature):
            return Temperature(self._celsius + other._celsius)
        elif isinstance(other, (int, float)):
            return Temperature(self._celsius + other)
        return NotImplemented

    def __sub__(self, other):
        if isinstance(other, Temperature):
            return Temperature(self._celsius - other._celsius)
        elif isinstance(other, (int, float)):
            return Temperature(self._celsius - other)
        return NotImplemented

    def __repr__(self):
        return f"Temperature({self._celsius:.2f} °C)"


# ------------------------------
# Задача 3. Класс Student с атрибутом класса, статическим методом и eq/hash
# ------------------------------
class Student:

    next_id = 1

    def __init__(self, name: str):
        if not Student.validate_name(name):
            raise ValueError("Имя должно содержать только буквы и не быть пустым.")
        self._name = name
        self._student_id = Student.next_id
        Student.next_id += 1

    @property
    def name(self):
        return self._name

    @property
    def student_id(self):
        return self._student_id

    @staticmethod
    def validate_name(name: str) -> bool:
        return name.isalpha() and len(name) > 0

    def __eq__(self, other):
        if isinstance(other, Student):
            return self._student_id == other._student_id
        return NotImplemented

    def __hash__(self):
        return hash(self._student_id)

    def __repr__(self):
        return f"Student({self._name}, id={self._student_id})"


# ------------------------------
# Задача 4. Класс Rectangle с контролем атрибутов, статикой и магией
# ------------------------------
class Rectangle:
    
    count = 0

    def __init__(self, width: float, height: float):
        if width <= 0 or height <= 0:
            raise ValueError("Стороны должны быть положительными.")
        self._width = width
        self._height = height
        Rectangle.count += 1

    @property
    def width(self):
        return self._width

    @property
    def height(self):
        return self._height

    @property
    def area(self):
        return self._width * self._height

    @staticmethod
    def is_square(width, height):
        return width == height

    def __mul__(self, factor: float):
        if not isinstance(factor, (int, float)):
            return NotImplemented
        return Rectangle(self._width * factor, self._height * factor)

    def __str__(self):
        return f"Rectangle({self._width}x{self._height})"

    def __repr__(self):
        return f"Rectangle(width={self._width}, height={self._height})"


# ------------------------------
# Задача 5. Класс Library с управлением книгами
# ------------------------------
class Library:
    
    books = []

    @staticmethod
    def format_book_info(title: str, author: str) -> str:
        return f"«{title}» by {author}"

    def add_book(self, title: str, author: str):
        book = {"title": title, "author": author}
        Library.books.append(book)

    def __len__(self):
        return len(Library.books)

    def __getitem__(self, index):
        return Library.books[index]

    def __contains__(self, title):
        return any(book["title"] == title for book in Library.books)


# ------------------------------
# Проверка в main
# ------------------------------
def main():
    print("=== Проверка задач ===")

    # Task 1
    car1 = Car("Toyota", "Camry", 1990)
    car2 = Car("Tesla", "Model 3", 2020)
    print(car1)
    print("Всего машин:", Car.total_cars)
    print("car1 винтажный:", Car.is_vintage(car1.year))
    print()

    # Task 2
    t1 = Temperature(25)
    t2 = Temperature.from_fahrenheit(77)
    print(t1 + 5)
    print(t1 - t2)
    print()

    # Task 3
    s1 = Student("Ivan")
    s2 = Student("Petr")
    print(s1, s2)
    print("Равны?", s1 == s2)
    s3 = s1
    print("s1 == s3:", s1 == s3)
    print()

    # Task 4
    r1 = Rectangle(3, 4)
    r2 = r1 * 2
    print(r1, "Площадь:", r1.area)
    print(r2, "Площадь:", r2.area)
    print("Квадрат?", Rectangle.is_square(5, 5))
    print("Всего прямоугольников:", Rectangle.count)
    print()

    # Task 5
    lib = Library()
    lib.add_book("1984", "George Orwell")
    lib.add_book("Brave New World", "Aldous Huxley")
    print("Всего книг:", len(lib))
    print("Книга[0]:", lib[0])
    print("'1984' в библиотеке?", "1984" in lib)


if __name__ == "__main__":
    main()
