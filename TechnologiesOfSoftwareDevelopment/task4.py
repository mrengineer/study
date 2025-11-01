
# Задача 1. Система уведомлений через разные каналы
from abc import ABC, abstractmethod


class NotificationService(ABC):
    """Абстрактный сервис уведомлений."""

    @abstractmethod
    def send(self, message: str):
        """Отправка уведомления."""
        pass


class EmailService(NotificationService):
    def send(self, message: str):
        print(f"[Email] Отправлено: {message}")


class SMSService(NotificationService):
    def send(self, message: str):
        print(f"[SMS] Отправлено: {message}")


class PushService(NotificationService):
    def send(self, message: str):
        print(f"[Push] Отправлено: {message}")


# Задача 2. Платёжные процессоры: карта, PayPal, крипто

class PaymentProcessor(ABC):
    """Абстрактный класс платёжного процессора"""

    @abstractmethod
    def validate_payment(self, data):
        pass

    @abstractmethod
    def process_payment(self, amount: float):
        pass


class CreditCardProcessor(PaymentProcessor):
    def __init__(self, card_number: str, cvv: str):
        self.card_number = card_number
        self.cvv = cvv
        self.validate_payment({"card_number": card_number, "cvv": cvv})

    def validate_payment(self, data):
        if not (data["card_number"].isdigit() and len(data["card_number"]) == 16):
            raise ValueError("Надо 16 цифр")
        if not (data["cvv"].isdigit() and len(data["cvv"]) in (3, 4)):
            raise ValueError("CVV - 3 или 4 цифры")
        return True

    def process_payment(self, amount: float):
        print(f"[CreditCard] Оплачено {amount:.2f} руб")


class PayPalProcessor(PaymentProcessor):
    def __init__(self, email: str):
        self.email = email
        self.validate_payment({"email": email})

    def validate_payment(self, data):
        if "@" not in data["email"]:
            raise ValueError("Некорректный email.")
        return True

    def process_payment(self, amount: float):
        print(f"[PayPal] Оплачено {amount:.2f} руб.")


class CryptoProcessor(PaymentProcessor):
    def __init__(self, wallet_address: str):
        self.wallet_address = wallet_address
        self.validate_payment({"wallet_address": wallet_address})

    def validate_payment(self, data):
        if not data["wallet_address"].startswith("bc1"):
            raise ValueError("Некорректный адрес кошелька (должен начинаться с bc1).")
        return True

    def process_payment(self, amount: float):
        print(f"[Crypto] Оплачено {amount:.2f} в BTC.")



# Задача 3.  try...except...else...finally

def safe_square_input():
    """Запрашивает число, возводит в квадрат, обрабатывает ошибки"""
    try:
        num = float(input("Введите число: "))
    except ValueError:
        print("Ошибка: введено не число")
    else:
        print(f"Результат: {num ** 2}")
    finally:
        print("Операция завершена")



# Задача 4. Проверка данных и обработка исключений

def process_data(data):
    """Проверяет список на корректность данных"""
    try:
        if not isinstance(data, list):
            raise TypeError("Ожидается список")
        if not data:
            raise ValueError("Пусто!")
        if not all(isinstance(x, (int, float)) for x in data):
            raise TypeError("Список должен содержать только числа")
    except (TypeError, ValueError) as e:
        print(f"Ошибка: {e}")
    else:
        print("Список корректен. Среднее значение:", sum(data) / len(data))
    finally:
        print("Проверка данных завершена")


# Задача 5. Контекстный менеджер SafeFile
class SafeFile:
    """Контекстный менеджер для безопасного открытия файлов"""

    def __init__(self, filename, mode):
        self.filename = filename
        self.mode = mode
        self.file = None

    def __enter__(self):
        try:
            self.file = open(self.filename, self.mode, encoding="utf-8")
            return self.file
        except Exception as e:
            with open("error.log", "a", encoding="utf-8") as log:
                log.write(f"Ошибка при открытии {self.filename}: {e}\n")
            return None

    def __exit__(self, exc_type, exc_val, exc_tb):
        if self.file:
            self.file.close()
        return True

def main():
    print("\n=== Задача 1: Уведомления ===")
    message = "Добро пожаловать!"
    for service in (EmailService(), SMSService(), PushService()):
        service.send(message)

    print("\n=== Задача 2: Платёжные процессоры ===")
    try:
        cc = CreditCardProcessor("1234567812345678", "123")
        cc.process_payment(1500)
    except ValueError as e:
        print("Ошибка:", e)

    try:
        pp = PayPalProcessor("user@example.com")
        pp.process_payment(299.99)
    except ValueError as e:
        print("Ошибка:", e)

    try:
        crypto = CryptoProcessor("bc1xyz123")
        crypto.process_payment(0.0023)
    except ValueError as e:
        print("Ошибка:", e)

    print("\n=== Задача 3: Безопасный ввод ===")
    safe_square_input()

    print("\n=== Задача 4: Проверка данных ===")
    process_data([1, 2, 3])
    process_data("строка")
    process_data([])
    process_data([1, "x", 3])

    print("\n=== Задача 5: SafeFile ===")
    with SafeFile("test.txt", "w") as f:
        if f:
            f.write("Hello, world!")

    with SafeFile("/nonexistent/folder/file.txt", "r") as f:
        if f is None:
            print("Ошибка при открытии файла обработана безопасно")


if __name__ == "__main__":
    main()
