#include <iostream>
#include <iomanip>
#include <cmath>        // для isnan() и NAN
#include <limits>       // на случай, если NAN не определён

#ifndef NAN
#define NAN std::numeric_limits<double>::quiet_NaN()
#endif

double calculate_function(double x)
{
    if (x == -1.0)
        return NAN; // Возвращаем "не число", если знаменатель 0
    return 1.0 / ((1.0 + x) * (1.0 + x));
}

int main()
{
    double a = 0.0;
    double b = 0.0;
    double h = 0.0;

    std::cout << "Enter start of the interval (a): ";
    std::cin >> a;

    std::cout << "Enter end of the interval (b): ";
    std::cin >> b;

    std::cout << "Enter step (h): ";
    std::cin >> h;

    // Проверка корректности шага и интервала
    if (h <= 0 || a > b)
    {
        std::cout << "Invalid interval or step.\n";
        return 1;
    }

    std::cout << "\nTable of function values y = 1/((1+x)^2)\n";
    std::cout << std::setw(10) << "x" << std::setw(15) << "y\n";
    std::cout << "--------------------------\n";

    for (double x = a; x <= b; x += h)
    {
        double y = calculate_function(x);

        std::cout << std::setw(10) << x;
        if (std::isnan(y))
        {
            std::cout << std::setw(15) << "undefined\n";
        }
        else
        {
            std::cout << std::setw(15) << std::setprecision(6) << y << "\n";
        }
    }

    return 0;
}
