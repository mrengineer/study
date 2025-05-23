# Task 14

from collections import Counter

print("--- ЗАДАЧА 1 ---")
# Задача 1: Подсчет итогового количества голосов у каждого кандидата
inputs = [
    "5",
    "McCain 10",
    "McCain 5",
    "Obama 9",
    "Obama 8",
    "McCain 1"
]
input = lambda: inputs.pop(0)

n = int(input())
votes = {}
for _ in range(n):
    name, count = input().split()
    votes[name] = votes.get(name, 0) + int(count)
for name in sorted(votes):
    print(name, votes[name])

print("--- ЗАДАЧА 2 ---")
# Задача 2: Найти самое часто встречающееся слово
inputs = [
    1,
    "apple orange banana banana orange"
]
input = lambda: inputs.pop(0)

n = int(input())
words = input().split()
counter = Counter(words)
max_count = max(counter.values())
most_common_words = [word for word, count in counter.items() if count == max_count]
print(min(most_common_words))

print("--- ЗАДАЧА 3 ---")
# Задача 3: Проверка доступа к файлам
inputs = [
    4,
    "helloworld.exe R X",
    "pinglog W R",
    "nya R",
    "goodluck X W R",
    5,
    "read nya",
    "write helloworld.exe",
    "execute nya",
    "read pinglog",
    "write pinglog"
]
input = lambda: inputs.pop(0)

n = int(input())
permissions = {}
for _ in range(n):
    parts = input().split()
    permissions[parts[0]] = set(parts[1:])
m = int(input())

print("m=", m)
operation_map = {'read': 'R', 'write': 'W', 'execute': 'X'}
for _ in range(m):
    op, filename = input().split()
    if operation_map[op] in permissions.get(filename, set()):
        print('OK')
    else:
        print('Access denied')

print("--- ЗАДАЧА 4 ---")
# Задача 4: Частотный словарь слов в тексте
inputs = [
    "9",
    "hi",
    "hi",
    "what is your name",
    "my name is bond",
    "james bond",
    "my name is damme",
    "van damme",
    "claude van damme",
    "jean claude van damme"
]
input = lambda: inputs.pop(0)

n = int(input())
words = []
for _ in range(n):
    words += input().split()
freq = Counter(words)
items = sorted(freq.items(), key=lambda x: (-x[1], x[0]))
for word, _ in items:
    print(word)

print("--- ЗАДАЧА 5 ---")
# Задача 5: Определить, в какой стране находится город
inputs = [
    5,
    "A B",
    "C D",
    "E F",
    "G H",
    "I J",
    5,
    "J",
    "H",
    "F",
    "D",
    "B"
]
input = lambda: inputs.pop(0)

n = int(input())
city_to_country = {}
for _ in range(n):
    parts = input().split()
    country = parts[0]
    for city in parts[1:]:
        city_to_country[city] = country
m = int(input())
for _ in range(m):
    print(city_to_country[input()])

print("--- ЗАДАЧА 6 ---")
# Задача 6: Создание латино-английского словаря
inputs = [
    3,
    "apple - malum, pomum, popula",
    "fruit - baca, bacca, popum",
    "punishment - malum, multa"
]
input = lambda: inputs.pop(0)

n = int(input())
latin_dict = {}
for _ in range(n):
    eng, latin = input().split(' - ')
    for lat in latin.split(', '):
        latin_dict.setdefault(lat, set()).add(eng)
for lat in sorted(latin_dict):
    print(f"{lat} - {', '.join(sorted(latin_dict[lat]))}")
    
    
    
print("--- ЗАДАЧА 7 ---")
# Задача 7: Подсчет ошибок в ударениях
inputs = [
    4,
    "cAnnot",
    "cannOt",
    "fOund",
    "pAge",
    "thE pAge cAnnot be found"
]
input = lambda: inputs.pop(0)

n = int(input())

dictionary = {}
for _ in range(n):
    word = input()
    base = word.lower().replace("'", '')
    dictionary.setdefault(base, set()).add(word)


words = input().split()
errors = 0

for word in words:
    base = word.lower().replace("'", '')
    if word not in dictionary.get(base, {}):

        if sum(1 for c in word if c.isupper()) != 1:
            print("FIAL", word)
            errors += 1    

print(errors)
