
print("ЗАНЯТИЕ 5\n\n")

input("# 1) Квадрат из звездочек")
n = 7  # Задайте нужное значение n
for i in range(n):
    row = ''
    for j in range(n):
        row += '*'
    print(row)

input("# 2) Сумма 1 + 1/2 + 1/3 + ... + 1/n")
n = 10  # Задайте нужное значение n
harmonic_sum = 0
for i in range(1, n + 1):
    harmonic_sum += 1 / i
print(f'Сумма ряда: {harmonic_sum}')


input("# 3) Четырехзначные числа с разными цифрами")
for num in range(1000, 10000):
    num_str = str(num)
    unique = True
    for i in range(len(num_str)):
        for j in range(i + 1, len(num_str)):
            if num_str[i] == num_str[j]:
                unique = False
                break
        if not unique:
            break
    if unique:
        print(num)


input("# 4) Четырехзначные числа без цифр 5 и 6")
for num in range(1000, 10000):
    num_str = str(num)
    if '5' not in num_str and '6' not in num_str:
        print(num)


input("# 5) Найти четырехзначные числа, которые в 600 раз больше суммы своих цифр")
count = 0
for num in range(1000, 10000):
    num_str = str(num)
    digit_sum = 0
    for digit in num_str:
        digit_sum += int(digit)
    if num == 600 * digit_sum:
        print(num)
        count += 1
print(f'Всего таких чисел: {count}')


input("# 6) Треугольник из звездочек")
n = 4  # Задайте нужное значение n
for i in range(1, n + 1):
    row = ''
    for j in range(i):
        row += '*'
    print(row)


input("# 7) Несчастливые билеты (сумма цифр делится на 13)")
for ticket in range(100000, 1000000):
    ticket_str = str(ticket)
    digit_sum = 0
    for digit in ticket_str:
        digit_sum += int(digit)
    if digit_sum % 13 == 0:
        print(ticket)
