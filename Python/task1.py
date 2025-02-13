import math


print("Задача 1")
#Задача 1
def is_natural(n):
    return isinstance(n, int) and n > 0

n = 42445
print("Число натуральное?", is_natural(n))
print("Последняя цифра как остаток от деления:", n % 10)

print("-----")

#Задача 2
print("Задача 2")
v = int(input("Скорость, натуральное число, при движении в обратном направлении с минусом: "))  # скорость (км/ч)
t = int(input("Время движения, натуральное число: "))  # время (ч)

mkad_length = 109  # длина МКАД (км)

position = (v * t) % mkad_length  # вычисляем позицию
print("Позиция:", position, "км")


print("-----")

#Задача 3
print("Задача 3")

n = float(input("Путь машины за день, км, "))
m = float(input("Маршрут"))

days = math.ceil(m / n)  # округляем вверх, чтобы учесть оставшийся путь
print("Для приодоления маршрута требуется, дней: ", days)

print("-----")

#Задача 4
print("Задача 4")

a = int(input("Цена, рублей за пирожок, "))
b = int(input("Цена, копеек за пирожок, "))
n = int(input("Купить, штук "))

# Общая стоимость в копейках
total = (a * 100 + b) * n

# Конвертируем в рубли и копейки
rubles = total // 100
kops = total % 100

print(rubles, "Руб ", kops, " коп")

print("-----")


#Задача 5
print("Задача 5")

h1 = int(input())  # Часы первого момента
m1 = int(input())  # Минуты первого момента
s1 = int(input())  # Секунды первого момента

h2 = int(input())  # Часы второго момента
m2 = int(input())  # Минуты второго момента
s2 = int(input())  # Секунды второго момента

seconds1 = h1 * 3600 + m1 * 60 + s1
seconds2 = h2 * 3600 + m2 * 60 + s2

# Вычисляем разницу во времени
seconds_difference = seconds2 - seconds1

# Вывод результата
print(seconds_difference)
