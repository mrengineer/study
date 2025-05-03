# 11 от 30.04.2025

# 1. Напишите функцию `greet(name)`, которая принимает имя и выводит "Привет, [name]!"
def greet(name: str) -> None:
    """Выводит приветствие с именем"""
    print(f"Привет, {name}!")
greet("Аня")

# 2. Создайте функцию `is_even(num)`, которая возвращает True, если число чётное, и False - если нечётное
def is_even(num: int) -> bool:
    """Возвращает True, если число чётное, иначе False."""
    return num % 2 == 0
print(is_even(4))

# 3. Напишите функцию `max_of_two(a, b)`, которая возвращает наибольшее из двух чисел
def max_of_two(a: int, b: int) -> int:
    """Возвращает наибольшее из двух чисел"""
    return a if a > b else b
print(max_of_two(10, 5))

# 4. Создайте функцию `sum_numbers(a, b=0, c=0)`, которая возвращает сумму a + b + c (b и c по умолчанию 0)
def sum_numbers(a: int, b: int = 0, c: int = 0) -> int:
    """Возвращает сумму трёх чисел."""
    return a + b + c
print(sum_numbers(1, 2))

# 5. Напишите функцию `average(*args)`, вычисляющую среднее значение переданных чисел
def average(*args: float) -> float:
    """Возвращает среднее значение из переданных чисел."""
    return sum(args) / len(args) if args else 0
print(average(3, 4, 5))

# 6. Создайте функцию `format_info(**kwargs)`, которая форматирует переданные именованные аргументы в строку
def format_info(**kwargs: str) -> str:
    """Форматирует именованные аргументы в строку."""
    return ', '.join(f"{k}: {v}" for k, v in kwargs.items())
print(format_info(name="Иван", age="20"))

# 7. Напишите функцию `square(x)`, возвращающую квадрат числа
def square(x: int) -> int:
    """Возвращает квадрат числа."""
    return x * x
print(square(6))

# 8. Создайте функцию `calc(a, b)`, возвращающую разность и произведение двух чисел (в виде кортежа)
def calc(a: int, b: int) -> tuple[int, int]:
    """Возвращает разность и произведение двух чисел"""
    return a - b, a * b
print(calc(7, 3))

# 9. Напишите функцию `is_palindrome(s)`, проверяющую, является ли строка палиндромом
def is_palindrome(s: str) -> bool:
    """Проверяет, является ли строка палиндромом."""
    return s == s[::-1]
print(is_palindrome("шалаш"))

# 10. Создайте функцию `counter()`, увеличивающую глобальную переменную count на 1 при каждом вызове
count = 0
def counter() -> None:
    """Увеличивает глобальную переменную count на 1"""
    global count
    count += 1
    print(count)
counter()
counter()

# 11. Напишите функцию `add_to_list(lst, item)`, добавляющую item в список lst
def add_to_list(lst: list, item: any) -> None:
    """Добавляет элемент в список."""
    lst.append(item)
my_list = [1, 2]
add_to_list(my_list, 3)
print(my_list)

# 12. Создайте функцию `test_scope()`, демонстрирующую разницу между локальной и глобальной переменной
x = 10
def test_scope() -> None:
    """Показывает разницу между глобальной и локальной переменной"""
    x = 5
    print("Локальный x:", x)
test_scope()
print("Глобальный x:", x)

# 13. Создайте лямбда-функцию `double`, которая удваивает переданное число
double = lambda x: x * 2
print(double(7))

# 14. Используя filter() и лямбду, отфильтруйте чётные числа из списка [1, 2, 3, 4, 5, 6]
nums = [1, 2, 3, 4, 5, 6]
even_nums = list(filter(lambda x: x % 2 == 0, nums))
print(even_nums)

# 15. Отсортируйте список строк ["яблоко", "груша", "апельсин", "банан"] по длине слов с помощью sorted() и лямбды
fruits = ["яблоко", "груша", "апельсин", "банан"]
sorted_fruits = sorted(fruits, key=lambda x: len(x))
print(sorted_fruits)

# 16. Напишите рекурсивную функцию `factorial(n)`, вычисляющую факториал числа
def factorial(n: int) -> int:
    """Вычисляет факториал числа."""
    if n == 0:
        return 1
    return n * factorial(n - 1)
print(factorial(5))

# 17. Создайте рекурсивную функцию `fib(n)`, возвращающую n-е число Фибоначчи
def fib(n: int) -> int:
    """Возвращает n-е число Фибонач"""
    if n <= 1:
        return n
    return fib(n - 1) + fib(n - 2)
print(fib(6))

# 18. Напишите рекурсивную функцию `sum_digits(n)`, вычисляющую сумму цифр числа
def sum_digits(n: int) -> int:
    """Вычисляет сумму цифр числа."""
    if n == 0:
        return 0
    return n % 10 + sum_digits(n // 10)
print(sum_digits(123))

# 19. Создайте функцию `print_numbers(n)`, рекурсивно выводящую числа от n до 1
def print_numbers(n: int) -> None:
    """Рекурсивно выводит числа от n до 1"""
    if n == 0:
        return
    print(n)
    print_numbers(n - 1)
print_numbers(5)

# 20. Напишите рекурсивную функцию `is_power_of_two(n)`, проверяющую, является ли число степенью двойки
def is_power_of_two(n: int) -> bool:
    """Проверяет, является ли число степенью двойк и"""
    if n == 1:
        return True
    if n < 1 or n % 2 != 0:
        return False
    return is_power_of_two(n // 2)
print(is_power_of_two(8))
