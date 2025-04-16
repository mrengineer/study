# Работа №9 от 16.04.2025

import random

# Задайте массив для использования далее:
array = [11, 3, 5, 11, 7, 3, 3, 11, 2, 9, 7, 9, 9, 12321, 121, 34543, 22, 44, 66, 8, 8, 8, 10, 15]

# 1) Удалить в массиве все числа, которые повторяются более двух раз.
print("Задача 1: Удалить в массиве все числа, которые повторяются более двух раз.")

counts = {}
for num in array:
    if num in counts:
        counts[num] += 1
    else:
        counts[num] = 1

filtered_array = []
for num in array:
    if counts[num] <= 2:
        filtered_array.append(num)

print("Результат:", filtered_array)

# 2) Найдите наибольший нечетный элемент.
print("\nЗадача 2: Найдите наибольший нечетный элемент.")

odd_numbers = []
for num in array:
    if num % 2 != 0:
        odd_numbers.append(num)

if len(odd_numbers) > 0:
    max_odd = odd_numbers[0]
    for n in odd_numbers:
        if n > max_odd:
            max_odd = n
    print("Наибольший нечетный элемент:", max_odd)
else:
    print("Нечетных элементов нет.")

# 3) Найдите два наименьших элемента.
print("\nЗадача 3: Найдите два наименьших элемента.")

if len(array) >= 2:
    sorted_array = sorted(array)
    min1 = sorted_array[0]
    min2 = sorted_array[1]
    print("Два наименьших элемента:", min1, "и", min2)
else:
    print("Недостаточно элементов.")

# 4) Найти наиболее часто встречающийся элемент.
print("\nЗадача 4: Найти наиболее часто встречающийся элемент.")

most_common = None
highest_count = 0
for num in counts:
    if counts[num] > highest_count:
        highest_count = counts[num]
        most_common = num

print("Наиболее часто встречающийся элемент:", most_common)

# 5) Проверить, является ли массив возрастающим или убывающим.
print("\nЗадача 5: Проверить, является ли массив возрастающим или убывающим.")

is_increasing = True
is_decreasing = True

for i in range(1, len(array)):
    if array[i] > array[i - 1]:
        is_decreasing = False
    elif array[i] < array[i - 1]:
        is_increasing = False

if is_increasing:
    print("Массив является строго возрастающим.")
elif is_decreasing:
    print("Массив является строго убывающим.")
else:
    print("Массив не является ни возрастающим, ни убывающим.")

# 6) Проверить, является ли массив арифметической или геометрической прогрессией.
print("\nЗадача 6: Проверить, является ли массив арифметической или геометрической прогрессией.")

def is_arithmetic(seq):
    if len(seq) < 2:
        return False
    difference = seq[1] - seq[0]
    for i in range(2, len(seq)):
        if seq[i] - seq[i - 1] != difference:
            return False
    return True

def is_geometric(seq):
    if len(seq) < 2 or seq[0] == 0:
        return False
    ratio = seq[1] / seq[0]
    for i in range(2, len(seq)):
        if seq[i - 1] == 0 or seq[i] / seq[i - 1] != ratio:
            return False
    return True

if is_arithmetic(array):
    print("Массив является арифметической прогрессией.")
elif is_geometric(array):
    print("Массив является геометрической прогрессией.")
else:
    print("Массив не является ни арифметической, ни геометрической прогрессией.")

# 7) Найти три последовательных элемента с максимальной суммой.
print("\nЗадача 7: Найти три последовательных элемента с максимальной суммой.")

if len(array) < 3:
    print("Недостаточно элементов в массиве.")
else:
    max_sum = array[0] + array[1] + array[2]
    max_triplet = [array[0], array[1], array[2]]

    for i in range(len(array) - 2):
        a = array[i]
        b = array[i + 1]
        c = array[i + 2]
        current_sum = a + b + c

        if current_sum > max_sum:
            max_sum = current_sum
            max_triplet = [a, b, c]

    print("Три элемента с максимальной суммой:", max_triplet)
    print("Сумма:", max_sum)

# 8) Удалить все наибольшие элементы.
print("\nЗадача 8: Удалить все наибольшие элементы.")

max_element = array[0]
for num in array:
    if num > max_element:
        max_element = num

result_array = []
for num in array:
    if num != max_element:
        result_array.append(num)

print("Результат:", result_array)

# 9) Удалить все положительные палиндромы.
print("\nЗадача 9: Удалить все положительные палиндромы.")

def is_palindrome(n):
    str_n = str(n)
    return str_n == str_n[::-1]

result = []
for num in array:
    if num > 0 and is_palindrome(num):
        continue
    result.append(num)

print("Результат:", result)

# 10) Перемешать массив случайным образом.
print("\nЗадача 10: Перемешать массив случайным образом.")

shuffled_array = array.copy()
random.shuffle(shuffled_array)

print("Перемешанный массив:", shuffled_array)
