#include <stdio.h>

// 1. Подсчитать положительные отрицательные и нули в массиве
void count_types(int *arr, int n) {
    int pos = 0, neg = 0, zeros = 0;

    for (int i = 0; i < n; i++) {
        if (arr[i] > 0) pos++;
        else if (arr[i] < 0) neg++;
        else zeros++;
    }

    printf("Положит:%d  Отриц:%d  Нулей:%d\n", pos, neg, zeros);
}

// 2. Найти индекс первого отрицательного
int first_negative(int *arr, int n) {
    for (int i = 0; i < n; i++)
        if (arr[i] < 0)
            return i;
    return -1;
}

// 3. Заменить отрицательные на 0
void replace_negatives(int *arr, int n) {
    for (int i = 0; i < n; i++)
        if (arr[i] < 0)
            arr[i] = 0;
    printf("Отрицательные заменены на 0\n");
}

// 4. Сумма элементов на чётных позициях
int sum_even_positions(int *arr, int n) {
    int s = 0;
    for (int i = 0; i < n; i += 2)
        s += arr[i];
    return s;
}

// 5–6. Подсчёт локальных минимумов
int count_local_min(int *arr, int n) {
    int cnt = 0;

    for (int i = 0; i < n; i++) {
        int left_ok = (i == 0) || (arr[i] < arr[i - 1]);
        int right_ok = (i == n - 1) || (arr[i] < arr[i + 1]);

        if (left_ok && right_ok)
            cnt++;
    }

    return cnt;
}

// 7. Первый и последний max + сумма между ними
int sum_between_max(int *arr, int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];

    int first = -1, last = -1;

    for (int i = 0; i < n; i++)
        if (arr[i] == max) {
            if (first == -1) first = i;
            last = i;
        }

    if (first == last) {
        printf("Максимум один и суммировать нечего\n");
        return 0;
    }

    int sum = 0;
    for (int i = first + 1; i < last; i++)
        sum += arr[i];

    return sum;
}

// 8. Количество уникальных значений
int count_unique(int *arr, int n) {
    int uniq = 0;

    for (int i = 0; i < n; i++) {
        int repeats = 0;
        for (int j = 0; j < n; j++)
            if (arr[i] == arr[j] && i != j)
                repeats = 1;

        if (!repeats) uniq++;
    }
    return uniq;
}

// 9. Переворот массива
void reverse_array(int *arr, int n) {
    for (int i = 0; i < n / 2; i++) {
        int tmp = arr[i];
        arr[i] = arr[n - 1 - i];
        arr[n - 1 - i] = tmp;
    }
    printf("Массив перевернут\n");
}

// Печать массива
void print_arr(int *arr, int n) {
    printf("Массив: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int arr[10] = {3, -1, 0, 5, 5, -8, 2, 5, 1, -3};
    int n = 10;


    printf("ВНИМАНИЕ!!! Исходный массив будет изменён функцией и поступит на вход следующей\n");

    printf("== Проверка функций ==\n");
    printf("Исходный массив:\n");
    print_arr(arr, n);
    printf("\n");

    count_types(arr, n);

    int fn = first_negative(arr, n);
    printf("Первый отриц индекс: %d\n", fn);

    replace_negatives(arr, n);
    print_arr(arr, n);

    printf("Сумма на чётных позициях: %d\n", sum_even_positions(arr, n));

    printf("Локальных минимумов: %d\n", count_local_min(arr, n));

    printf("Сум между первым и последним max: %d\n", sum_between_max(arr, n));

    printf("Уникальных значений: %d\n", count_unique(arr, n));

    printf("\nМассив был:\n");
    print_arr(arr, n);
    reverse_array(arr, n);
    print_arr(arr, n);

    printf("Все!\n");
    return 0;
}
