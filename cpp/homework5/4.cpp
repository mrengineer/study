#include <iostream>
#include <iomanip>
#include <cmath>
#include <utility>   // for std::pair
#include <limits>

#ifndef NAN
#define NAN std::numeric_limits<double>::quiet_NaN()
#endif

// helper function returns pair(F(x), n_terms)
std::pair<double, unsigned int> calculate_function(double x, double epsilon)
{
    double sum = 1.0;
    double term = (x * x) / 4.0;
    unsigned int n = 1;

    // add terms until difference < epsilon
    while (std::fabs(term) >= epsilon)
    {
        sum += term;
        ++n;
        term = std::pow(x, n + 1) / std::pow(4.0, n);
        if (std::isnan(term) || std::isinf(term)) 
            return std::make_pair(NAN, n);
    }

    return std::make_pair(sum, n);
}

int main()
{
    double a = 0.1;
    double b = 0.9;
    const double STEP = 0.1;
    double epsilon = 0.0;

    std::cout << "enter accuracy epsilon (>0): ";
    std::cin >> epsilon;

    if (epsilon <= 0)
    {
        std::cout << "epsilon must be > 0\n";
        return 1;
    }

    std::cout << "\nTable of F(x)\n";
    std::cout << std::setw(5) << "No"
              << std::setw(12) << "x"
              << std::setw(20) << "F(x)"
              << std::setw(15) << "terms n\n";
    std::cout << "--------------------------------------------------\n";

    unsigned int index = 1;
    for (double x = a; x <= b + 1e-9; x += STEP)
    {
        auto result = calculate_function(x, epsilon);

        std::cout << std::setw(5) << index
                  << std::setw(12) << std::fixed << std::setprecision(2) << x;

        if (std::isnan(result.first))
        {
            std::cout << std::setw(20) << "undefined"
                      << std::setw(15) << result.second << "\n";
        }
        else
        {
            std::cout << std::setw(20) << std::setprecision(6) << result.first
                      << std::setw(15) << result.second << "\n";
        }

        ++index;
    }

    return 0;
}
