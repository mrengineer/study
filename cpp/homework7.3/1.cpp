#include <iostream>
#include <string>
#include <cctype>

/*
    ИСПРАВЛЕНО:
    Используется std::string вместо char*
*/


bool startsWithUpperCase(const std::string& word)
{
    if (word.empty())
        return false;

    return std::isupper(static_cast<unsigned char>(word[0]));
}

int main()
{
    std::string input;

    std::cout << "Enter text: ";
    std::getline(std::cin, input);

    std::string result;
    size_t i = 0;
    size_t length = input.length();

    while (i < length)
    {
        // Пропуск пробелов
        while (i < length && std::isspace(static_cast<unsigned char>(input[i])))
            ++i;

        if (i >= length)
            break;

        size_t start = i;

        // Поиск конца слова
        while (i < length && !std::isspace(static_cast<unsigned char>(input[i])))
            ++i;

        size_t wordLength = i - start;
        std::string word = input.substr(start, wordLength);

        if (!startsWithUpperCase(word))
        {
            if (!result.empty())
                result += " ";
            result += word;
        }
    }

    std::cout << "Result: " << result << std::endl;

    return 0;
}
