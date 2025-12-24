#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>

namespace app_config {
    const int MIN_TWO_DIGIT = 10;
    const int MAX_TWO_DIGIT = 99;
}

bool isTwoDigit(const int value)
{
    // проверка на двухзначное число, знак не учитываем
    const int abs_value = std::abs(value);
    return abs_value >= app_config::MIN_TWO_DIGIT &&
           abs_value <= app_config::MAX_TWO_DIGIT;
}

int main()
{
    size_t elements_count = 0;
    int replacement_value = 0;

    std::cout << "Enter number of elements: ";
    std::cin >> elements_count;

    // выделяем память под массив заранее
    std::vector<int> numbers(elements_count);

    std::cout << "Enter replacement value x: ";
    std::cin >> replacement_value;

    std::cout << "Enter elements:" << std::endl;

    // ввод массива через стандартный алгоритм
    std::generate(
        numbers.begin(),
        numbers.end(),
        []() {
            int value = 0;
            std::cin >> value;
            return value;
        }
    );

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

    // замена всех двухзначных чисел на x
    std::replace_if(
        numbers.begin(),
        numbers.end(),
        isTwoDigit,
        replacement_value
    );

    std::cout << "Modified sequence:" << std::endl;

    std::for_each(
        numbers.begin(),
        numbers.end(),
        [](const int value) {
            std::cout << value << " ";
        }
    );

    std::cout << std::endl;
    std::cout << "Processing finished" << std::endl;

    return 0;
}
