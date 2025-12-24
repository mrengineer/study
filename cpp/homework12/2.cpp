#include <iostream>
#include <vector>
#include <algorithm>

namespace app_config {
    const size_t INITIAL_SIZE = 8;
}

int main()
{
    // исходные данные заданы прямо в коде
    std::vector<int> numbers = {
        10, 20, 30, 40, 50, 60, 70, 80
    };

    size_t k1 = 0;
    size_t k2 = 0;

    std::cout << "Enter k1: ";
    std::cin >> k1;

    std::cout << "Enter k2: ";
    std::cin >> k2;

    std::cout << std::endl;
    std::cout << "Original sequence:" << std::endl;

    std::for_each(
        numbers.begin(),
        numbers.end(),
        [](const int value) {
            std::cout << value << " ";
        }
    );

    std::cout << std::endl << std::endl;

    if (k1 <= k2 && k2 < numbers.size()) {

        // получаем итераторы начала и конца диапазона
        auto first_to_remove = numbers.begin();
        std::advance(first_to_remove, static_cast<std::ptrdiff_t>(k1));

        auto last_to_remove = numbers.begin();
        std::advance(last_to_remove, static_cast<std::ptrdiff_t>(k2 + 1));

        // удаляем элементы по диапазону итераторов
        numbers.erase(first_to_remove, last_to_remove);
    }

    std::cout << "Modified sequence:" << std::endl;

    std::for_each(
        numbers.begin(),
        numbers.end(),
        [](const int value) {
            std::cout << value << " ";
        }
    );

    std::cout << std::endl;
    std::cout << "Done!" << std::endl;

    return 0;
}
