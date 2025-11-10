#include <stdio.h>
#include <math.h>

// 1. Сравнение трёх чисел
void compare_three_numbers() {
    int a, b, c;
    printf("\n[1] Сравнение трёх чисел\nВведите три целых числа: ");
    scanf("%d %d %d", &a, &b, &c);

    if (a == b && b == c) {
        printf("Все числа равны\n");
    } else if (a >= b && a >= c && !(a == b && a == c)) {
        if ((a == b) || (a == c))
            printf("Несколько чисел равны и максимальны\n");
        else
            printf("Наибольшее число %d\n", a);
    } else if (b >= a && b >= c) {
        if (b == c)
            printf("Несколько чисел равны и максимальны\n");
        else
            printf("Наибольшее число %d\n", b);
    } else {
        printf("Наибольшее число %d\n", c);
    }
}

// 2. Уравнение прямой
void line_equation() {
    double x1, y1, x2, y2;
    printf("\n[2] Уравнение прямой\nВведите координаты двух точек (x1 y1 x2 y2): ");
    scanf("%lf %lf %lf %lf", &x1, &y1, &x2, &y2);

    if (x1 == x2) {
        printf("Прямая вертикальная, угловой коеффициент не опредлён\n");
    } else {
        double k = (y2 - y1) / (x2 - x1);
        double b = y1 - k * x1;
        printf("Уравнение: y = %.2fx + %.2f\n", k, b);
    }
}

// 3. Расчёт сдачи
void calculate_change() {
    double S, P;
    printf("\n[3] Расчёт сдачи\nВведите сумму покупки и сумму внесённую покупателем: ");
    scanf("%lf %lf", &S, &P);

    if (P < S)
        printf("Недастаточно денег, нехватает %.2f руб\n", S - P);
    else
        printf("Сдача %.2f руб.\n", P - S);
}

// 4. Проверка делимости
void check_divisibility() {
    int a, b;
    printf("\n[4] Проверка делимости\nВведите два числа: ");
    scanf("%d %d", &a, &b);

    if (b == 0)
        printf("Ошибка деление на ноль!\n");
    else if (a % b == 0)
        printf("Делится без остатка\n");
    else
        printf("Не делится, остаток = %d\n", a % b);
}

// 5. Калькулятор двух чисел
void calculator() {
    double a, b;
    char op;
    printf("\n[5] Калькулятор\nВведите выражение (напр: 5.2 * 3): ");
    scanf("%lf %c %lf", &a, &op, &b);

    switch (op) {
        case '+': printf("Результат %.2f\n", a + b); break;
        case '-': printf("Результат %.2f\n", a - b); break;
        case '*': printf("Результат %.2f\n", a * b); break;
        case '/':
            if (b == 0)
                printf("Ошибка деление на ноль!\n");
            else
                printf("Результат %.2f\n", a / b);
            break;
        default: printf("Неизвстная операция\n");
    }
}

// 6. Температурный классификатор
void temperature_classifier() {
    double t;
    printf("\n[6] Температура воздуха\nВведите t (°C): ");
    scanf("%lf", &t);

    if (t < -20)
        printf("Очень холодно\n");
    else if (t < 0)
        printf("Холодно.\n");
    else if (t < 10)
        printf("Прохладно\n");
    else if (t < 25)
        printf("Тепло\n");
    else
        printf("Жарко\n");
}

// 7. Проверка високосного года
void check_leap_year() {
    int year;
    printf("\n[7] Високосный год?\nВведите год: ");
    scanf("%d", &year);

    if ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0))
        printf("Да, високосный\n");
    else
        printf("Обычный год\n");
}

// 8. Квадратное уравнение
void quadratic_equation() {
    double a, b, c;
    printf("\n[8] Квадратное уравнение\nВведите a b c: ");
    scanf("%lf %lf %lf", &a, &b, &c);

    if (a == 0) {
        printf("Это не квадратное ур-е\n");
        return;
    }

    double D = b*b - 4*a*c;

    if (D > 0) {
        double x1 = (-b + sqrt(D)) / (2*a);
        double x2 = (-b - sqrt(D)) / (2*a);
        printf("Два корня: x1=%.2f x2=%.2f\n", x1, x2);
    } else if (D == 0) {
        double x = -b / (2*a);
        printf("Один корень x=%.2f\n", x);
    } else {
        printf("Корней нет\n");
    }
}

// 9. Оценка успеваемости
void grade_evaluation() {
    int x;
    printf("\n[9] Оценка успеваемости\nВведите баллы (0–100): ");
    scanf("%d", &x);

    if (x < 0 || x > 100)
        printf("Ошибка: неверное значенее\n");
    else if (x < 50)
        printf("Неудовлетворительно\n");
    else if (x < 70)
        printf("Удовлетворительно\n");
    else if (x < 85)
        printf("Хорошо\n");
    else
        printf("Отлично!\n");
}

// 10. Проверка треугольника
void triangle_check() {
    double a, b, c;
    printf("\n[10] Проверка треугольника\nВведите три стороны: ");
    scanf("%lf %lf %lf", &a, &b, &c);

    if (a + b > c && a + c > b && b + c > a) {
        if (a == b && b == c)
            printf("Равносторонний треугольник\n");
        else if (a == b || b == c || a == c)
            printf("Равнобедренный\n");
        else
            printf("Разносторонний треугольник\n");
    } else {
        printf("Треугольник не существует\n");
    }
}

int main() {
    printf("=== Задание 6 на C ===\n");

    compare_three_numbers();
    line_equation();
    calculate_change();
    check_divisibility();
    calculator();
    temperature_classifier();
    check_leap_year();
    quadratic_equation();
    grade_evaluation();
    triangle_check();

    printf("\nКонец\n");
    return 0;
}
