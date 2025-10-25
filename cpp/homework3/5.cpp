#include <iostream>
#include <iomanip>

double calculate_function(double x) 
{    
    return (x != -1.0) ? 1.0 / ((1.0 + x) * (1.0 + x)) : 0.0;
}

int main() 
{
    double a = 0.0;
    double b = 0.0;
    double h = 0.0;

    std::cout << "Введите начало интервала a: ";
    std::cin >> a;

    std::cout << "Введите конец интервала b: ";
    std::cin >> b;

    std::cout << "Введите шаг h: ";
    std::cin >> h;

    // Проверка корректности шага
    if (h <= 0 || a > b) 
    {
        std::cout << "Некорректные значения интервала или шага.\n";
        return 1;
    }

    std::cout << "\nТаблица значений функции y = 1/((1+x)^2)\n";
    std::cout << std::setw(10) << "x" << std::setw(15) << "y\n";
    std::cout << "--------------------------\n";

    for (double x = a; x <= b; x += h) 
    {
        // Проверка, что знаменатель не равен нулю
        if (x == -1.0) 
        {
            std::cout << std::setw(10) << x << std::setw(15) << "не определено\n";
        } 
        else 
        {
            double y = calculate_function(x);
            std::cout << std::setw(10) << x 
                      << std::setw(15) << std::setprecision(6) << y << "\n";
        }
    }

    return 0;
}
