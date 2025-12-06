#include <iostream>
#include <cstring>
#include <cctype>

// Проверяет, есть ли в слове заглавная буква
bool hasUpperCase(const char* word) {
    for (int i = 0; word[i] != '\0'; i++) {
        if (std::isupper(static_cast<unsigned char>(word[i]))) {
            return true;
        }
    }
    return false;
}

int main() {
    char input[2048];

    std::cout << "Enter text: ";
    std::cin.getline(input, 2048);

    // Двумерный динамический массив слов
    char** words = nullptr;
    int wordCount = 0;

    int len = strlen(input);
    int i = 0;

    // Парсим строку вручную
    while (i < len) {

        // Пропускаем разделители
        while (i < len && std::isspace(static_cast<unsigned char>(input[i]))) {
            i++;
        }
        if (i >= len) break;

        // Начало слова
        int start = i;

        // Ищем конец слова
        while (i < len && !std::isspace(static_cast<unsigned char>(input[i]))) {
            i++;
        }

        int end = i;
        int wordLen = end - start;

        // Копируем слово во временный буфер
        char* word = new char[wordLen + 1];
        std::memcpy(word, &input[start], wordLen);
        word[wordLen] = '\0';

        // Проверяем слово
        if (!hasUpperCase(word)) {

            
            char** newWords = new char*[wordCount + 1];

            for (int j = 0; j < wordCount; j++) {
                newWords[j] = words[j];
            }

            newWords[wordCount] = word;

            delete[] words;
            words = newWords;
            wordCount++;

        } else {
            // Слово не подходит — удаляем буфер
            delete[] word;
        }
    }

    // Склеиваем результат в вывод
    std::cout << "Result: ";

    for (int j = 0; j < wordCount; j++) {
        std::cout << words[j];
        if (j < wordCount - 1)
            std::cout << " ";
    }

    std::cout << std::endl;

    // Освобождаем память
    for (int j = 0; j < wordCount; j++) {
        delete[] words[j];
    }
    delete[] words;

    return 0;
}
