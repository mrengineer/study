# Работа №8 от 09.04.2025

# 1
print("1) Петя перешёл в другую школу. На уроке физкультуры ему понадобилось определить своё место в строю.")
print("Введите рост учеников через пробел (невозрастающий порядок):")
heights_input = input()
heights = heights_input.split()
for i in range(len(heights)):
    heights[i] = int(heights[i])

print("Введите рост Пети:")
petya = int(input())

position = 1
for h in heights:
    if petya <= h:
        position += 1
print("Петя должен встать на позицию:", position)

print("\n" + "-"*50 + "\n")

# 2
print("2) Дан список, упорядоченный по неубыванию. Определите, сколько в нём различных элементов.")
numbers_input = input("Введите список чисел: ")
numbers = numbers_input.split()
for i in range(len(numbers)):
    numbers[i] = int(numbers[i])

unique = []
for num in numbers:
    if num not in unique:
        unique.append(num)

print("Количество различных элементов:", len(unique))

print("\n" + "-"*50 + "\n")

# 3
print("3) Переставьте соседние элементы списка.")
numbers = input("Введите список чисел: ").split()
for i in range(len(numbers)):
    numbers[i] = int(numbers[i])

for i in range(0, len(numbers) - 1, 2):
    temp = numbers[i]
    numbers[i] = numbers[i + 1]
    numbers[i + 1] = temp

print("Результат:", numbers)

print("\n" + "-"*50 + "\n")

# 4
print("4) В списке все элементы различны. Поменяйте местами минимальный и максимальный элемент.")
numbers = input("Введите список чисел: ").split()
for i in range(len(numbers)):
    numbers[i] = int(numbers[i])

min_index = 0
max_index = 0
for i in range(len(numbers)):
    if numbers[i] < numbers[min_index]:
        min_index = i
    if numbers[i] > numbers[max_index]:
        max_index = i

# меняем местами
temp = numbers[min_index]
numbers[min_index] = numbers[max_index]
numbers[max_index] = temp

print("Результат:", numbers)

print("\n" + "-"*50 + "\n")

# 5
print("5) Удалите элемент с индексом k, сдвинув остальные элементы влево, затем удалите последний с помощью pop().")
numbers = input("Введите список чисел: ").split()
for i in range(len(numbers)):
    numbers[i] = int(numbers[i])

k = int(input("Введите индекс: "))

for i in range(k, len(numbers) - 1):
    numbers[i] = numbers[i + 1]

numbers.pop()
print("Результат:", numbers)

print("\n" + "-"*50 + "\n")

# 6
print("6) Посчитайте количество пар равных элементов в списке.")
numbers = input("Введите список чисел: ").split()
for i in range(len(numbers)):
    numbers[i] = int(numbers[i])

count = 0
for i in range(len(numbers)):
    for j in range(i + 1, len(numbers)):
        if numbers[i] == numbers[j]:
            count += 1

print("Количество пар:", count)

print("\n" + "-"*50 + "\n")

# 7
print("7) Выведите те элементы списка, которые встречаются только один раз.")
numbers = input("Введите список чисел: ").split()
for i in range(len(numbers)):
    numbers[i] = int(numbers[i])

for i in range(len(numbers)):
    if numbers.count(numbers[i]) == 1:
        print(numbers[i], end=' ')
print()

print("\n" + "-"*50 + "\n")

# 8
print("8) Найти количество элементов, которые меньше 0.")
numbers = input("Введите список чисел: ").split()
for i in range(len(numbers)):
    numbers[i] = int(numbers[i])

count = 0
for i in numbers:
    if i < 0:
        count += 1

print("Количество отрицательных чисел:", count)

print("\n" + "-"*50 + "\n")

# 9
print("9) Заполнить массив нулями, кроме первого и последнего элементов, которые равны 1.")
n = int(input("Введите длину массива: "))
a = []

for i in range(n):
    a.append(0)

if n >= 1:
    a[0] = 1
if n >= 2:
    a[n - 1] = 1

print("Результат:", a)

print("\n" + "-"*50 + "\n")

# 10
print("10) Заполнить массив чередующимися нулями и единицами, начиная с нуля.")
n = int(input("Введите длину массива: "))
a = []

for i in range(n):
    if i % 2 == 0:
        a.append(0)
    else:
        a.append(1)

print("Результат:", a)

print("\n" + "-"*50 + "\n")

# 11
print("11) Заполнить массив последовательными нечетными числами, начиная с единицы.")
n = int(input("Введите длину массива: "))
a = []

number = 1
for i in range(n):
    a.append(number)
    number += 2

print("Результат:", a)
