# task2.py


# 1) Банковские счета
class BankAccount:
    """Базовый банковский счет: account_number и balance доступны только через свойства."""

    def __init__(self, account_number: str, balance: float = 0.0):
        if not account_number:
            raise ValueError("account_number должен быть непустым")
        if balance < 0:
            raise ValueError("Начальный баланс не может быть отрицательным")
        self._account_number = account_number
        self._balance = float(balance)

    @property
    def account_number(self) -> str:
        """Номер счета (только чтение)."""
        return self._account_number

    @property
    def balance(self) -> float:
        """Баланс (только чтение)."""
        return self._balance

    def deposit(self, amount: float) -> bool:
        """Пополнение: проверка единоразово в родителе. Возвращает True при успехе."""
        if amount <= 0:
            raise ValueError("Сумма пополнения должна быть положительной")
        self._balance += amount
        return True

    def withdraw(self, amount: float) -> bool:
        """Снятие: проверка единоразово в родителе. Возвращает True при успехе."""
        if amount <= 0:
            raise ValueError("Сумма снятия должна быть положительной")
        if amount > self._balance:
            raise ValueError("Недостаточно средств")
        self._balance -= amount
        return True

    def display_info(self) -> None:
        """Вывод информации о счёте (использует свойства)."""
        print(f"Счет №{self.account_number}, Баланс: {self.balance}")

    def __del__(self):
        # Формат вывода - точно как просили: "Счет закрыт Остаток: {balance}"
        try:
            bal = self.balance
        except Exception:
            bal = "unknown"
        print(f"Счет закрыт Остаток: {bal}")


class SavingsAccount(BankAccount):
    """Сберегательный счет: добавляет процентную ставку и расширяет display_info."""

    def __init__(self, account_number: str, balance: float, interest_rate: float):
        if interest_rate < 0:
            raise ValueError("Процентная ставка не может быть отрицательной")
        super().__init__(account_number, balance)
        self._interest_rate = float(interest_rate)

    @property
    def interest_rate(self) -> float:
        """Процентная ставка (только чтение)."""
        return self._interest_rate

    def display_info(self) -> None:
        """Выводит базовую информацию и ставку, используя super()."""
        super().display_info()
        print(f"Процентная ставка: {self.interest_rate}%")


# 2) Обучающие курсы
class Course:
    """Базовый курс с приватными _title и _duration; только чтение через свойства."""

    def __init__(self, title: str, duration: float):
        if not title:
            raise ValueError("title не может быть пустым")
        if duration <= 0:
            raise ValueError("duration должен быть положительным")
        self._title = title
        self._duration = float(duration)

    @property
    def title(self) -> str:
        return self._title

    @property
    def duration(self) -> float:
        return self._duration

    def display_info(self) -> None:
        print(f"Курс: {self.title}, Длительность: {self.duration} ч.")


class MentoredCourse(Course):
    """Курс с обязательным наставником; display_info добавляет строку с наставником."""

    def __init__(self, title: str, duration: float, mentor: str):
        if not mentor:
            raise ValueError("mentor обязателен и не может быть пустым")
        super().__init__(title, duration)
        self._mentor = mentor

    @property
    def mentor(self) -> str:
        return self._mentor

    def display_info(self) -> None:
        super().display_info()
        print(f"[Mentor: {self.mentor}]")


# 3) Животные
class Animal:
    """Базовое животное: приватное имя и общий звук."""

    def __init__(self, name: str):
        if not name:
            raise ValueError("name не может быть пустым")
        self._name = name

    @property
    def name(self) -> str:
        return self._name

    def make_sound(self) -> str:
        return "Some sound"

    def display_info(self) -> None:
        print(f"Животное: {self.name}")


class Pet(Animal):
    """Домашний питомец: владелец обязателен; использует super() для вывода имени."""

    def __init__(self, name: str, owner_name: str):
        if not owner_name:
            raise ValueError("owner_name обязателен и не может быть пустым")
        super().__init__(name)
        self._owner_name = owner_name

    @property
    def owner_name(self) -> str:
        return self._owner_name

    def make_sound(self) -> str:
        return "Some pet sound"

    def display_info(self) -> None:
        # Используем родительский вывод имени, затем добавляем владельца — без дублирования логики.
        super().display_info()
        print(f"Владелец: {self.owner_name}")

# ---------------------------------------------------------------------
# 4) Геометрические фигуры: прямоугольник и квадрат — width/height только для чтения в Rectangle, side в Square доступен для записи.
class Rectangle:
    """Прямоугольник с приватными _width и _height; только чтение width/height и метод площади."""

    def __init__(self, width: float, height: float):
        if width <= 0 or height <= 0:
            raise ValueError("width и height должны быть положительными")
        self._width = float(width)
        self._height = float(height)

    @property
    def width(self) -> float:
        return self._width

    @property
    def height(self) -> float:
        return self._height

    def calculate_area(self) -> float:
        return self._width * self._height


class Square(Rectangle):
    """Квадрат: конструктор принимает side и использует родительский конструктор; side — read/write."""

    def __init__(self, side: float):
        if side <= 0:
            raise ValueError("side должен быть положительным")
        super().__init__(side, side)

    @property
    def side(self) -> float:
        # Возвращаем width (они равны)
        return self.width

    @side.setter
    def side(self, value: float) -> None:
        if value <= 0:
            raise ValueError("side должен быть положительным")
        # инкапсуляция — поля остаются приватными.
        self._width = self._height = float(value)

# 5) Пользователи системы
class User:
    """Пользователь с приватными _username и _email; только чтение через свойства."""

    def __init__(self, username: str, email: str):
        if not username:
            raise ValueError("username не может быть пустым")
        if not email or "@" not in email:
            raise ValueError("email должен быть корректным")
        self._username = username
        self._email = email

    @property
    def username(self) -> str:
        return self._username

    @property
    def email(self) -> str:
        return self._email

    def display_info(self) -> None:
        print(f"Пользователь: {self.username}, Email: {self.email}")


class Admin(User):
    """Администратор с набором прав (permissions) — проверка корректности перед сохранением."""

    def __init__(self, username: str, email: str, permissions):
        if permissions is None:
            raise ValueError("permissions обязателен")
        # Нормализуем ожидаемый формат: список строк
        if not isinstance(permissions, (list, tuple)):
            raise TypeError("permissions должен быть списком или кортежем строк")
        if not all(isinstance(p, str) and p for p in permissions):
            raise ValueError("Каждый permission должен быть непустой строкой")
        super().__init__(username, email)
        # Храним как tuple чтобы предотвратить модификацию извне (immutable-ish)
        self._permissions = tuple(permissions)

    @property
    def permissions(self):
        return self._permissions

    def display_info(self) -> None:
        super().display_info()
        print(f"Права: {', '.join(self.permissions)}")

# Тесты / запуск в main — проверка каждого задания
if __name__ == "__main__":
    print("\n--- Задача 1: Банковские счета ---")
    acc = SavingsAccount("ACC-001", 1000.0, 2.5)
    try:
        acc.deposit(150.0)
        acc.withdraw(50.0)
    except Exception as e:
        print("Ошибка операции:", e)
    acc.display_info()
    # пробуем обратиться к приватному атрибуту напрямую (пользователь может, но требования выполнены — доступ через свойства)
    print("account_number (через property):", acc.account_number)
    print("balance (через property):", acc.balance)

    print("\n--- Задача 2: Курсы ---")
    course = MentoredCourse("Python ООП", 30, "Елена")
    course.display_info()

    print("\n--- Задача 3: Животные ---")
    pet = Pet("Шарик", "Ольга")
    pet.display_info()
    print("make_sound:", pet.make_sound())

    print("\n--- Задача 4: Фигуры ---")
    sq = Square(4)
    print("width:", sq.width, "height:", sq.height, "side:", sq.side)
    print("area:", sq.calculate_area())
    sq.side = 7
    print("after set side -> area:", sq.calculate_area())

    print("\n--- Задача 5: Пользователи ---")
    admin = Admin("admin", "admin@example.com", ["add_user", "delete_user"])
    admin.display_info()
