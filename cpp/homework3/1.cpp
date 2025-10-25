#include <iostream>
#include <cmath>

int main() {
    std::cout << "Введите координату x: ";
    double x;
    std::cin >> x;

    std::cout << "Введите координату y: ";
    double y;
    std::cin >> y;

    const double RADIUS = 3.0;
    double distanceSquared = x * x + y * y;

    if (y < 0) {
        std::cout << "Нет\n";
    } else if (distanceSquared < RADIUS * RADIUS) {
        std::cout << "Да\n";
    } else if (distanceSquared == RADIUS * RADIUS) {
        std::cout << "На границе\n";
    } else {
        std::cout << "Нет\n";
    }

    return 0;
}
