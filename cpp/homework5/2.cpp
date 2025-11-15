#include <iostream>
#include <iomanip>
#include <cmath>

int main()
{
    unsigned int k = 0;
    double x = 0.0;
    double sum = 0.0;

    std::cout << "enter real x: ";
    std::cin >> x;

    std::cout << "enter natural k: ";
    std::cin >> k;

    if (k == 0)
    {
        std::cout << "k must be > 0\n";
        return 1;
    }

    for (unsigned int n = 1; n <= k; ++n)
        sum += std::pow(x, n) / n;

    std::cout << "sum S = " << std::setprecision(6) << sum << "\n";

    return 0;
}
