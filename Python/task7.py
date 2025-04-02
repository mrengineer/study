import random
import string

# 1. Генерация пароля
print("1) Написать алгоритм генерации пароля.")
digits = string.digits
letters = string.ascii_letters
punctuation = string.punctuation
all_chars = digits + letters + punctuation
password = ""
for i in range(12):
    password += random.choice(all_chars)
print("Сгенерированный пароль:", password)

# 2. Извлечение имени файла без расширения
print("\n2) Дана строка, содержащая полное имя файла. Выделите из этой строки имя файла без расширения.")
filepath = r'c:\WebServers\home\testsite\www\myfile.txt'
parts = filepath.split('\\')
filename_with_ext = parts[-1]
filename = filename_with_ext.split('.')[0]
print("Имя файла:", filename)

# 3. Удаление лишних пробелов
print("\n3) Удалить в строке все лишние пробелы.")
text = "  Это   тестовая    строка   "
words = text.split()
clean_text = ' '.join(words)
print("Удалены лишние пробелы:", clean_text)

# 4. Удаление всех цифр из строки
print("\n4) Удалить в строке все цифры.")
text_with_digits = "Тест123 строка456"
no_digits_text = ""
for c in text_with_digits:
    if not c.isdigit():
        no_digits_text += c
print("Удалены цифры:", no_digits_text)

# 5. Проверка корректности email
print("\n5) Дан email в строке. Определить, является ли он корректным.")
email = "example@email.com"
if "@" in email and "." in email.split("@")[1]:
    domain_parts = email.split(".")
    if len(domain_parts[-1]) >= 2:
        email_valid = True
    else:
        email_valid = False
else:
    email_valid = False
print("Корректность email:", email_valid)

# 6. Генерация email
print("\n6) Написать алгоритм генерации email.")
email_domains = ['gmail.com', 'yahoo.com', 'outlook.com']
name = ""
for i in range(8):
    name += random.choice(string.ascii_lowercase + string.digits)
random_email = name + "@" + random.choice(email_domains)
print("Сгенерированный email:", random_email)

# 7. Разделение числа на тройки цифр
print("\n7) Дано натуральное число. Получить строку, в которой тройки цифр этого числа разделены пробелом.")
number = 1234567
number_str = str(number)
formatted_number = ""
count = 0
for i in range(len(number_str) - 1, -1, -1):
    formatted_number = number_str[i] + formatted_number
    count += 1
    if count % 3 == 0 and i != 0:
        formatted_number = " " + formatted_number
print("Число с пробелами:", formatted_number)

# 8. Первые буквы слов
print("\n8) Вывести текст, составленный из первых букв всех слов.")
text = "Это тестовая строка для примера"
first_letters = ""
for word in text.split():
    first_letters += word[0]
print("Первые буквы слов:", first_letters)
