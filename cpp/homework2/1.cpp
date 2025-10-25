#include <iostream>
#include <cmath>    // Для std::pow
#include <iomanip>  // Для форматирования вывода

// Функция f(n, x) возвращает x^n / n
double f(int n, double x) {
    return std::pow(x, n) / n;
}

int main() {
    // Ввод пользователя
    double x = 0.0;
    std::cout << "Введите значение x: ";
    std::cin >> x;

    // Вычисление выражения (x^2)/2 + (x^4)/4 + (x^6)/6
    double result = f(2, x) + f(4, x) + f(6, x);

    // Вывод результата с точностью до 6 знаков после запятой
    std::cout << std::fixed << std::setprecision(6);
    std::cout << "Значение выражения (x^2)/2 + (x^4)/4 + (x^6)/6 равно: " 
              << result << std::endl;

    return 0;
}
