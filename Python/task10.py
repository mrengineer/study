# Работа №10 от 23.04.2025

print("1. Даны четыре действительных числа: x1, y1, x2, y2. Найти расстояние между точками (x1,y1) и (x2,y2).")

import math

def distance(x1, y1, x2, y2):
    return math.sqrt((x2 - x1)**2 + (y2 - y1)**2)

print("Расстояние =", distance(1, 2, 4, 6))

print("2. Найти среднее арифметическое нескольких чисел.")

def average(a, b, c):
    return (a + b + c) / 3

print("Среднее арифметическое =", average(3, 7, 5))

print("3. Найти наименьшее из четырех чисел.")

def minimum(a, b, c, d):
    return min(a, b, c, d)

print("Минимальное число =", minimum(5, 2, 8, 1))

print("4. Функция голосования: вернуть то значение (True или False), которое встречается чаще среди трёх значений.")

def vote(x, y, z):
    if [x, y, z].count(True) > [x, y, z].count(False):
        return True
    else:
        return False

print("Результат голосования:", vote(True, False, True))

print("5. Суммировать все целые числа от start до end включительно. Если start > end, поменять местами.")

def sum_range(start, end):
    if start > end:
        start, end = end, start
    total = 0
    for i in range(start, end + 1):
        total += i
    return total

print("Сумма чисел от 8 до 3 =", sum_range(8, 3))

print("6. Перевести число из десятичной системы в систему счисления с основанием n (1 < n < 10).")

def to_base_n(number, n):
    result = ''
    while number > 0:
        result = str(number % n) + result
        number = number // n
    return result

print("Число 45 в системе с основанием 3:", to_base_n(45, 3))

print("7. Подсчитать количество гласных русских букв в строке.")

def count_vowels(text):
    vowels = 'аяуюоеёэиы'
    count = 0
    for letter in text.lower():
        if letter in vowels:
            count += 1
    return count

print("Количество гласных:", count_vowels("Привет, как дела?"))

print("8. Найти n-е число Фибоначчи.")

def fibonacci(n):
    a = 0
    b = 1
    for i in range(n):
        a, b = b, a + b
    return a

print("7-е число Фибоначчи:", fibonacci(7))

print("9. Проверить, являются ли две строки анаграммами.")

def are_anagrams(s1, s2):
    return sorted(s1) == sorted(s2)

print("Являются ли 'listen' и 'silent' анаграммами:", are_anagrams("listen", "silent"))

print("10. Проверить, является ли число числом Армстронга.")

def is_armstrong(n):
    digits = str(n)
    power = len(digits)
    total = 0
    for d in digits:
        total += int(d) ** power
    return total == n

print("153 - число Армстронга?", is_armstrong(153))
