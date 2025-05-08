import random

# Работа №12 от 07.05.2025

# 1) Сформировать квадратную матрицу n x n, на главной диагонали которой находятся случайные числа из диапазона [1; 9], а остальные числа равны 1.
def create_diagonal_matrix(n):
    """Создает квадратную матрицу n x n, где на главной диагонали случайные числа от 1 до 9, остальное — единицы."""
    matrix = []
    for i in range(n):
        row = []
        for j in range(n):
            if i == j:
                row.append(random.randint(1, 9))
            else:
                row.append(1)
        matrix.append(row)
    return matrix

print("1) Диагональная матрица:")
m1 = create_diagonal_matrix(4)
for row in m1:
    print(row)


# 2) Заполнить матрицу так, чтобы сумма элементов в каждой строке была равна номеру этой строки.
def row_sum_matrix(n, m):
    """Создает матрицу n x m, где сумма элементов в строке i равна i."""
    matrix = []
    for i in range(1, n + 1):
        row = [0] * (m - 1)
        row_sum = sum(row)
        last_element = i - row_sum
        row.append(last_element)
        matrix.append(row)
    return matrix

print("\n2) Матрица с суммой строки = номеру строки:")
m2 = row_sum_matrix(4, 5)
for row in m2:
    print(row)


# 3) Сформировать матрицу, состоящую из нулей и единиц, причем количество единиц строго равно количеству строк.
def zero_one_matrix(rows, cols):
    """Создает матрицу rows x cols с нулями и единицами, где число единиц = числу строк."""
    matrix = [[0 for _ in range(cols)] for _ in range(rows)]
    for i in range(rows):
        j = random.randint(0, cols - 1)
        matrix[i][j] = 1
    return matrix

print("\n3) Матрица из 0 и 1, единиц столько же, сколько строк:")
m3 = zero_one_matrix(5, 6)
for row in m3:
    print(row)


# 4) В данной матрице найти наименьший элемент в каждой строке.
def min_in_rows(matrix):
    """Возвращает список минимальных значений каждой строки."""
    return [min(row) for row in matrix]

print("\n4) Минимальные элементы в строках предыдущей матрицы:")
print(min_in_rows(m3))


# 5) В матрице найти номер строки, в которой произведение чисел минимально.
def row_with_min_product(matrix):
    """Находит индекс строки с минимальным произведением элементов."""
    min_product = float('inf')
    min_index = -1
    for i, row in enumerate(matrix):
        product = 1
        for num in row:
            product *= num
        if product < min_product:
            min_product = product
            min_index = i
    return min_index

print("\n5) Индекс строки с минимальным произведением элементов:")
print(row_with_min_product(m2))


# 6) Найдите наибольший элемент матрицы и заменить все нечетные элементы на него.
def replace_odds_with_max(matrix):
    """Заменяет все нечетные элементы матрицы на её максимальный элемент."""
    max_val = max(max(row) for row in matrix)
    for i in range(len(matrix)):
        for j in range(len(matrix[0])):
            if matrix[i][j] % 2 != 0:
                matrix[i][j] = max_val
    return matrix

print("\n6) Заменяем нечетные элементы на максимум в матрице:")
m4 = [row[:] for row in m2]  # Копия m2
m4 = replace_odds_with_max(m4)
for row in m4:
    print(row)


# 7) Для данной матрицы найдите транспонированную матрицу.
def transpose_matrix(matrix):
    """Возвращает транспонированную матрицу."""
    return [[matrix[j][i] for j in range(len(matrix))] for i in range(len(matrix[0]))]

print("\n7) Транспонированная матрица:")
m5 = transpose_matrix(m2)
for row in m5:
    print(row)


# 8) Найдите сумму всех элементов матрицы.
def sum_of_matrix(matrix):
    """Возвращает сумму всех элементов матрицы."""
    return sum(sum(row) for row in matrix)

print("\n8) Сумма всех элементов в матрице:")
print(sum_of_matrix(m2))
