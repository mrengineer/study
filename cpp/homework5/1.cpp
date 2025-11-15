#include <iostream>
#include <cmath>

int main() {
    int n;
    
    std::cout << "Enter n (natural number): ";
    std::cin >> n;


    // Тут можно было бы еще добавить проверку что число целое, однако суть упражнения не в проверке ввода
    if (!std::cin || n <= 0) {
        std::cout << "Error: n must be a natural number (> 0)\n";
        return 1;
    }


    double sum = 0.0;

    for (int i = 1; i <= n; ++i) {
        sum += std::pow(i, 2);
    }

    std::cout << "Result S = " << sum << std::endl;

    return 0;
}
