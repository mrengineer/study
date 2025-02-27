
print("ЗАНЯТИЕ 3. Строки\n\n")
print("1) Дана строка. Если она начинается на 'abc', то заменить их на 'www', иначе добавить в конец строки 'zzz'.")

s = input("Введите строку. Результат зависит от того, есть ли в начале 'abc': ")
s = s.replace('abc', 'www', 1) if s.startswith('abc') else s + 'zzz'  
print(s)
print('\n')


print("2) Дана строка. Если ее длина больше 10, то оставить в строке только первые 6 символов, иначе дополнить строку символами 'o' до длины 12.")

s = input("Введите сроку более или менее 10 символов: ")
s = s[:6] if len(s) > 10 else s.rjust(12, 'o')
print("Сделано при помощи слайса, как наиболее лаконичного способа")
print(s)
print('\n')

print("3) Дана строка. Определить, содержит ли строка только символы 'a', 'b', 'c' или нет.")
def contains_only_abc(s):
    for char in s:
        if char not in ('a', 'b', 'c'):
            return False
    return True

# Ввод строки от пользователя
user_input = input("Введите строку: ")

# Проверка и вывод результата
if contains_only_abc(user_input):
    print("Строка содержит только символы 'a', 'b', 'c'.")
else:
    print("Строка содержит другие символы.")

print('\n')


print("4) Дана строка. Заменить все символы 'a' и 'b' на 'A' и 'B' соответственно.")
user_input = input("Введите строку: ")

# Замена символов 'a' на 'A' и 'b' на 'B'
user_input = user_input.replace('a', 'A').replace('b', 'B')

print("Результат:", user_input)

print('\n')



print("5) Дана строка. Если она заканчивается на 'xyz', то заменить их на '123', иначе добавить в начало строки 'abc'.")

# Ввод строки от пользователя
user_input = input("Введите строку: ")

# Проверка, заканчивается ли строка на 'xyz'
if user_input.endswith('xyz'):
    user_input = user_input[:-3] + '123'
else:
    user_input = 'abc' + user_input

print("Результат:", user_input)

print('\n')



print("6) Дана строка. Если она содержит подстроку 'hello', то удалить ее из строки, иначе добавить подстроку 'world' в конец строки.")

# Ввод строки от пользователя
user_input = input("Введите строку: ")

# Проверка, содержит ли строка подстроку 'hello'
if 'hello' in user_input:
    user_input = user_input.replace('hello', '')
else:
    user_input = user_input + 'world'

print("Результат:", user_input)

print('\n')


print("7) Дана строка. Если длина строки четная, то перевернуть ее (реверсировать), иначе удалить из нее все пробелы.")

# Ввод строки от пользователя
user_input = input("Введите строку: ")

# Проверка длины строки
if len(user_input) % 2 == 0:
    user_input = user_input[::-1]  # Переворачиваем строку
else:
    user_input = user_input.replace(' ', '')  # Удаляем все пробелы

print("Результат:", user_input)

print('\n')
