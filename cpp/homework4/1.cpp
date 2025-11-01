#include <iostream>
#include <iomanip>

int main() {
    // Константы начальных значений последовательности
    const double B1 = 0.5;
    const double B2 = 0.2;

    
    int n;

    std::cout << "Введите количество элементов последовательности n: ";
    std::cin >> n;

    
    if (n < 1) {
        std::cout << "Ошибка: n должно быть больше 0." << std::endl;
        return 0;
    }

    
    double b_prev = B1;
    double b_curr = B2;

    std::cout << std::fixed << std::setprecision(6);
    std::cout << "b1 = " << b_prev << std::endl;

    if (n > 1) {
        std::cout << "b2 = " << b_curr << std::endl;
    }

    // Вычисление последовательности по формуле вариант 12
    for (int i = 2; i < n; i++) {
        double b_next = b_curr * b_curr + b_prev / i;

        std::cout << "b" << (i + 1) << " = " << b_next << std::endl;

        b_prev = b_curr;
        b_curr = b_next;
    }

    return 0;
}
