# ЗАДАЧА 1
# Для каждого класса определите максимальный балл, который набрал школьник, не ставший победителем в данном классе.

def second_best_per_class(data):
    classes = {}
    for fam, name, cls, score in data:
        cls = int(cls)
        score = int(score)
        if cls not in classes:
            classes[cls] = []
        classes[cls].append(score)

    result = []
    for cls in sorted(classes):
        scores = sorted(classes[cls], reverse=True)
        max_score = scores[0]
        for score in scores:
            if score < max_score:
                result.append(score)
                break
    return result

print("ЗАДАЧА 1:")
test_data1 = [
    ["Иванов", "Сергей", 9, 80],
    ["Сергеев", "Петр", 10, 82],
    ["Петров", "Василий", 11, 82],
    ["Васильев", "Андрей", 9, 81],
    ["Андреев", "Александр", 10, 81],
    ["Александров", "Роман", 9, 81],
    ["Романов", "Иван", 11, 83]
]
print(*second_best_per_class(test_data1))  # 80 81 82


# ЗАДАЧА 2
# Найти наибольший балл среди призеров и количество таких участников

def top_prize_info(data):
    scores = [int(row[3]) for row in data]
    max_score = max(scores)
    second_best = max([s for s in scores if s < max_score])
    count = scores.count(second_best)
    return second_best, count

print("\nЗАДАЧА 2:")
test_data2 = [
    ["Иванов", "Сергей", 9, 92],
    ["Сергеев", "Петр", 10, 91],
    ["Петров", "Василий", 11, 92],
    ["Васильев", "Иван", 9, 93]
]
print(*top_prize_info(test_data2))  # 92 2


# ЗАДАЧА 3 
# Фамилия и имя участника, набравшего наибольший балл, но не победителя. Если таких несколько — вывести их количество.

def second_best_name(data):
    scores = [int(row[3]) for row in data]
    max_score = max(scores)
    second_best_score = max([s for s in scores if s < max_score])
    second_best_people = [row[:2] for row in data if int(row[3]) == second_best_score]

    if len(second_best_people) == 1:
        fam, name = second_best_people[0]
        return f"{fam} {name}"
    else:
        return len(second_best_people)

print("\nЗАДАЧА 3:")
test_data3 = [
    ["Иванов", "Сергей", 9, 93],
    ["Сергеев", "Петр", 10, 91],
    ["Петров", "Василий", 11, 92],
    ["Васильев", "Иван", 9, 93]
]
print(second_best_name(test_data3))  # Петров Василий

test_data3b = test_data3 + [["Сидоров", "Максим", 11, 92]]
print(second_best_name(test_data3b))  # 2


# ЗАДАЧА 4
# Определите школы с наибольшим числом участников

def most_participants(lines):
    from collections import defaultdict
    counts = defaultdict(int)
    for line in lines:
        parts = line.split()
        school = int(parts[2])
        counts[school] += 1
    max_val = max(counts.values())
    return sorted([k for k, v in counts.items() if v == max_val])

print("\nЗАДАЧА 4:")
lines4 = [
    "Иванов Сергей 14 56",
    "Сергеев Петр 23 74",
    "Петров Василий 3 99",
    "Васильев Андрей 3 56",
    "Андреев Роман 14 75",
    "Романов Иван 27 68"
]
print(*most_participants(lines4))  # 3 14


# ЗАДАЧА 5
# Определите школы с минимальным числом участников (но хотя бы 1 участник)

def least_participants(lines):
    from collections import defaultdict
    counts = defaultdict(int)
    for line in lines:
        parts = line.split()
        school = int(parts[2])
        counts[school] += 1
    min_val = min(counts.values())
    return sorted([k for k, v in counts.items() if v == min_val])

print("\nЗАДАЧА 5:")
print(*least_participants(lines4))  # 23 27


# ЗАДАЧА 6
# Список участников, отсортированный по фамилии

def sorted_by_lastname(lines):
    people = []
    for line in lines:
        parts = line.split()
        fam, name, _, score = parts
        people.append((fam, name, int(score)))
    people.sort()
    return [f"{f} {n} {s}" for f, n, s in people]

print("\nЗАДАЧА 6:")
print("\n".join(sorted_by_lastname(lines4)))


# ЗАДАЧА 7
# Школы, где есть хотя бы один победитель (с максимальным баллом)

def schools_with_winners(lines):
    data = [line.split() for line in lines]
    scores = [int(row[3]) for row in data]
    max_score = max(scores)
    schools = set()
    for row in data:
        if int(row[3]) == max_score:
            schools.add(int(row[2]))
    return sorted(schools)

print("\nЗАДАЧА 7:")
lines7 = [
    "Иванов Сергей 13 80",
    "Сергеев Петр 26 70",
    "Сергеев Андрей 35 80",
    "Петров Василий 13 80",
    "Иванов Роман 35 70",
    "Иванов Иван 26 70"
]
print(*schools_with_winners(lines7))  # 13 35


# ЗАДАЧА 8
# Школы, у которых средний балл выше общего среднего

def schools_above_average(lines):
    from collections import defaultdict
    school_scores = defaultdict(list)
    all_scores = []
    for line in lines:
        parts = line.split()
        school = int(parts[2])
        score = int(parts[3])
        school_scores[school].append(score)
        all_scores.append(score)
    avg_total = sum(all_scores) / len(all_scores)
    result = []
    for school, scores in school_scores.items():
        avg = sum(scores) / len(scores)
        if avg > avg_total:
            result.append(school)
    return sorted(result)

print("\nЗАДАЧА 8:")
print(*schools_above_average(lines7))  # 13


# ЗАДАЧА 9
# Школы, из которых больше всего победителей

def schools_with_most_winners(lines):
    from collections import defaultdict
    data = [line.split() for line in lines]
    max_score = max([int(row[3]) for row in data])
    win_counts = defaultdict(int)
    for row in data:
        if int(row[3]) == max_score:
            win_counts[int(row[2])] += 1
    max_winners = max(win_counts.values())
    return sorted([k for k, v in win_counts.items() if v == max_winners])

print("\nЗАДАЧА 9:")
lines9 = [
    "Иванов Сергей 13 70",
    "Сергеев Петр 13 60",
    "Сергеев Андрей 20 70",
    "Петров Василий 20 70",
    "Иванов Роман 70 60",
    "Иванов Иван 70 60"
]
print(*schools_with_most_winners(lines9))  # 20
