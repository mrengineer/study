#include <iostream>

bool isValidDecimal(const char* const text) {   // const для защиты данных
    const char* p = text;

    // Пропуск пробелов в начале
    while (*p == ' ') {
        ++p;
    }

    // Опциональный знак
    if (*p == '+' || *p == '-') {
        ++p;
    }

    bool hasDigitsBeforeDot = false;
    bool hasDigitsAfterDot = false;

    // Цифры до точки
    while (*p >= '0' && *p <= '9') {
        hasDigitsBeforeDot = true;
        ++p;
    }

    // Точка
    if (*p == '.') {
        ++p;

        // Цифры после точки
        while (*p >= '0' && *p <= '9') {
            hasDigitsAfterDot = true;
            ++p;
        }
    }

    // Должна быть хотя бы одна цифра где-либо
    if (!hasDigitsBeforeDot && !hasDigitsAfterDot) {
        return false;
    }

    // Пропуск пробелов в конце
    while (*p == ' ') {
        ++p;
    }

    // Конец строки?
    return *p == '\0';
}

// Интерфейс
int main() {
    const size_t INPUT_SIZE = 256;      // const naming rule
    char text[INPUT_SIZE];

    std::cout << "Enter text: ";

    std::cin.getline(text, INPUT_SIZE);

    bool result = isValidDecimal(text);

    std::cout << "Valid decimal: " << (result ? "yes" : "no") << std::endl; 

    return 0;
}
