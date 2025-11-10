#include <iostream>
#include <iomanip>
#include <cmath>

// Auxiliary function for calculating y = f(x)
double calculate_function(double x) {
    // Function is defined piecewise:
    // y = 1 / ((0.1 + x)^2)   for x >= 0.9
    // y = (0.2 * x) + 0.1     for 0 <= x < 0.9
    // y = (x^2) + 0.2         for x < 0

    if (x >= 0.9) {
        double denominator = std::pow(0.1 + x, 2);

        // Check for division by zero
        if (denominator == 0) {
            throw std::runtime_error("Function is undefined (division by zero).");
        }

        return 1 / denominator;
    }
    else if (x >= 0 && x < 0.9) {
        return (0.2 * x) + 0.1;
    }
    else { // x < 0
        return std::pow(x, 2) + 0.2;
    }
}

int main() {
    double start_x;
    double end_x;
    double step;

    std::cout << "Enter the start of the interval (a): ";
    std::cin >> start_x;

    std::cout << "Enter the end of the interval (b): ";
    std::cin >> end_x;

    std::cout << "Enter the step (h): ";
    std::cin >> step;

    // Step validation
    if (step <= 0) {
        std::cout << "Error: step must be a positive number." << std::endl;
        return 0;
    }

    std::cout << std::fixed << std::setprecision(6);
    std::cout << "\nTable of function values: y = f(x)\n";
    std::cout << "--------------------------------------------\n";
    std::cout << "    x\t\t|\t    y\n";
    std::cout << "--------------------------------------------\n";

    for (double x = start_x; x <= end_x; x += step) {
        try {
            double y = calculate_function(x);
            std::cout << std::setw(10) << x << "  |  " << std::setw(10) << y << std::endl;
        } catch (const std::runtime_error& e) {
            std::cout << std::setw(10) << x << "  |  " << e.what() << std::endl;
        }
    }

    std::cout << "--------------------------------------------\n";
    return 0;
}
