#include <iostream>

int main() {

    std::cout << "Числа через цикл while: ";
    int i = 1;
    while (i <= 21) {
        std::cout << i << " ";
        i += 2;
    }
    std::cout << std::endl;

    std::cout << "Числа через цикл do-while: ";
    i = 1;
    do {
        std::cout << i << " ";
        i += 2;
    } while (i <= 21);
    std::cout << std::endl;


    std::cout << "Числа через цикл for: ";
    for (int j = 1; j <= 21; j += 2) {
        std::cout << j << " ";
    }
    std::cout << std::endl;

    return 0;
}
