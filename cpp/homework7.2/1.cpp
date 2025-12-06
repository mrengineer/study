#include <iostream>
#include <cstring>
#include <cctype>

// Увеличивает динамический массив на delta символов
char* resizeBuffer(char* buffer, size_t oldSize, size_t newSize) {
    char* newBuffer = new char[newSize];
    if (buffer != nullptr) {
        std::memcpy(newBuffer, buffer, oldSize);
        delete[] buffer;
    }
    return newBuffer;
}

// Удаляет все вхождения подстроки pattern из строки source
// Формирует результат с многократным увеличением динамического массива
char* removeSubstrings(const char* const source, const char* const pattern) {
    const size_t sourceLength = std::strlen(source);
    const size_t patternLength = std::strlen(pattern);

    // Пустой паттерн — возвращаем копию
    if (patternLength == 0) {
        char* copy = new char[sourceLength + 1];
        std::strcpy(copy, source);
        return copy;
    }

    char* result = nullptr;
    size_t resultSize = 0;      // текущая длина результата
    size_t bufferSize = 0;      // реальный выделенный размер

    const char* readPtr = source;

    while (*readPtr != '\0') {
        const char* found = std::strstr(readPtr, pattern);

        if (found == nullptr) {
            // Копируем остаток строки по одному символу
            while (*readPtr != '\0') {
                // увеличиваем буфер на 1 символ + '\0'
                bufferSize = resultSize + 2;
                result = resizeBuffer(result, resultSize + 1, bufferSize);

                result[resultSize] = *readPtr;
                resultSize++;
                readPtr++;
            }
            break;
        }

        // Копируем часть до найденного совпадения
        size_t chunk = static_cast<size_t>(found - readPtr);
        for (size_t i = 0; i < chunk; i++) {
            bufferSize = resultSize + 2;
            result = resizeBuffer(result, resultSize + 1, bufferSize);

            result[resultSize] = readPtr[i];
            resultSize++;
        }

        readPtr = found + patternLength;
    }

    // Завершающий нулевой символ
    bufferSize = resultSize + 1;
    result = resizeBuffer(result, resultSize + 1, bufferSize);
    result[resultSize] = '\0';

    return result;
}

int main() {
    const size_t MAX_LEN = 256;

    char source[MAX_LEN];
    char pattern[MAX_LEN];

    std::cout << "Enter S: ";
    std::cin.getline(source, MAX_LEN);

    std::cout << "Enter S0: ";
    std::cin.getline(pattern, MAX_LEN);

    char* result = removeSubstrings(source, pattern);

    std::cout << "Result: " << result << std::endl;

    delete[] result;

    return 0;
}
