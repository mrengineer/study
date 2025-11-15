#include <iostream>
#include <iomanip>
#include <cmath>

int main()
{
    double epsilon = 0.0;
    std::cout << "enter accuracy epsilon (>0): ";
    std::cin >> epsilon;

    if (epsilon <= 0)
    {
        std::cout << "epsilon must be > 0\n";
        return 1;
    }

    double sum = 0.0;
    double term = 0.0;
    unsigned int i = 1;

    do
    {
        term = 1.0 / (i * i);
        sum += term;
        ++i;
    } 
    while (term >= epsilon);

    std::cout << "sum S = " << std::setprecision(10) << sum << "\n";
    std::cout << "number of terms n = " << i - 1 << "\n";

    return 0;
}
