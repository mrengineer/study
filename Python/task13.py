# Множества
import random
import string
from collections import Counter

def create_set(numbers):
    """Принимает список чисел и возвращает множество уникальных элементов."""
    return set(numbers)

def union_sets(set1, set2):
    """Возвращает объединение двух множеств."""
    return set1 | set2

def intersection_sets(set1, set2):
    """Возвращает пересечение двух множеств."""
    return set1 & set2

def difference_sets(set1, set2):
    """Возвращает разность двух множеств (элементы из первого, которых нет во втором)."""
    return set1 - set2

def symmetric_difference_sets(set1, set2):
    """Возвращает симметрическую разность двух множеств."""
    return set1 ^ set2

def remove_duplicates(lst):
    """Удаляет дубликаты из списка, используя множество."""
    return list(set(lst))

def is_subset(set1, set2):
    """Проверяет, является ли первое множество подмножеством второго."""
    return set1.issubset(set2)

def is_disjoint(set1, set2):
    """Проверяет, не пересекаются ли два множества."""
    return set1.isdisjoint(set2)

def unique_elements_in_lists(lst1, lst2):
    """Возвращает элементы, которые встречаются только в одном из списков."""
    return set(lst1) ^ set(lst2)

def word_frequency_analysis(text):
    """Возвращает множество уникальных слов в тексте (без учёта регистра)."""
    words = text.lower().split()
    return set(words)

def find_missing_number(lst, n):
    """Находит одно пропущенное число в списке от 1 до n."""
    expected = set(range(1, n + 1))
    actual = set(lst)
    missing = expected - actual
    return missing.pop() if missing else None

def is_pangram(text):
    """Проверяет, является ли строка панграммой (содержит все буквы алфавита)."""
    return set(string.ascii_lowercase).issubset(set(text.lower()))

def common_friends(friends1, friends2):
    """Находит общих друзей из двух списков."""
    return set(friends1) & set(friends2)

def generate_unique_random_numbers(n, min_val, max_val):
    """Генерирует n уникальных случайных чисел в заданном диапазоне."""
    result = set()
    while len(result) < n:
        result.add(random.randint(min_val, max_val))
    return list(result)

def are_anagrams(word1, word2):
    """Проверяет, являются ли два слова анаграммами."""
    return Counter(word1) == Counter(word2)

def color_cubes_analysis(n, m, colors_a, colors_b):
    """Анализирует множества цветов кубиков у двух детей: общие, уникальные у каждого."""
    set_a = set(colors_a)
    set_b = set(colors_b)

    both = sorted(set_a & set_b)
    only_a = sorted(set_a - set_b)
    only_b = sorted(set_b - set_a)

    return {
        'both': (len(both), both),
        'only_a': (len(only_a), only_a),
        'only_b': (len(only_b), only_b)
    }

def common_and_all_languages(students_languages):
    """Определяет языки, которые знают все и хотя бы один из учеников.
    
    Возвращает два списка: языки, которые знают все, и языки, которые знает хотя бы один.
    """
    all_lang_sets = [set(langs) for langs in students_languages]
    common = sorted(set.intersection(*all_lang_sets))
    any_known = sorted(set.union(*all_lang_sets))
    return common, any_known

def main():
    # Примеры заданий 1–15
    print("1.", create_set([1, 2, 2, 3, 4, 4]))
    print("2.", union_sets({1, 2, 3}, {3, 4, 5}))
    print("3.", intersection_sets({1, 2, 3}, {3, 4, 5}))
    print("4.", difference_sets({1, 2, 3}, {3, 4, 5}))
    print("5.", symmetric_difference_sets({1, 2, 3}, {3, 4, 5}))
    print("6.", remove_duplicates([1, 2, 2, 3, 4, 4]))
    print("7.", is_subset({1, 2}, {1, 2, 3}))
    print("8.", is_disjoint({1, 2}, {3, 4}))
    print("9.", unique_elements_in_lists([1, 2, 3], [3, 4, 5]))
    print("10.", word_frequency_analysis("Python is great and python is fun"))
    print("11.", find_missing_number([1, 2, 4, 5], 5))
    print("12.", is_pangram("The quick brown fox jumps over the lazy dog"))
    print("13.", common_friends(["Alice", "Bob", "Charlie"], ["Bob", "Diana"]))
    print("14.", generate_unique_random_numbers(5, 0, 10))
    print("15.", are_anagrams("listen", "silent"))

    # Задание 16
    print("16.")
    n, m = 4, 3
    colors_a = [0, 1, 2, 3]
    colors_b = [2, 1, 4]
    result = color_cubes_analysis(n, m, colors_a, colors_b)
    print(result['both'][0])
    print(*result['both'][1])
    print(result['only_a'][0])
    print(*result['only_a'][1])
    print(result['only_b'][0])
    print(*result['only_b'][1])

    # Задание 17
    print("17.")
    students_languages = [
        ["Russian", "English", "Japanese"],
        ["Russian", "English"],
        ["English"]
    ]
    common, any_known = common_and_all_languages(students_languages)
    print(len(common))
    for lang in common:
        print(lang)
    print(len(any_known))
    for lang in any_known:
        print(lang)

if __name__ == "__main__":
    main()
