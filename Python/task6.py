print("ЗАНЯТИЕ 6\n\n")

# 1) Вывести двузначные числа, которые делятся на 4, но не делятся на 6
print("1) Двузначные числа, которые делятся на 4, но не делятся на 6:")
for number in range(10, 100):
    if number % 4 == 0 and number % 6 != 0:
        print(number)
print()

# 2) Найти сумму чисел от 100 до 200, которые делятся на 17
print("2) Сумма чисел от 100 до 200, которые делятся на 17:")
sum_numbers = 0
for number in range(100, 201):
    if number % 17 == 0:
        sum_numbers += number
print(sum_numbers)
print()

# 3) Найти произведение двузначных нечетных чисел, которые делятся на 13
print("3) Произведение двузначных нечетных чисел, которые делятся на 13:")
product = 1
for number in range(10, 100):
    if number % 13 == 0 and number % 2 != 0:
        product *= number
print(product)
print()

# 4) Вывести таблицу умножения
print("4) Таблица умножения:")
for i in range(1, 10):
    for j in range(1, 10):
        print(i * j, end="\t")  # "\t" ставит табуляцию для ровного вида
    print()
print()

# 5) Преобразовать число N в двоичную систему
print("5) Преобразование числа N в двоичную систему:")
N = int(input("Введите число N: "))
binary = ""
while N > 0:
    ostatok = N % 2
    binary = str(ostatok) + binary
    N = N // 2
print("В двоичной системе:", binary)
