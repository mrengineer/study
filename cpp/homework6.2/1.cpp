#include <iostream>
#include <utility>

bool hasAllUniqueDigits(int number);
int* removeElementsWithUniqueDigits(const int array[], size_t size, size_t& newSize);
void printArray(const int array[], size_t size);

int main() 
{
    size_t arraySize;
    
    std::cout << "Enter array size: ";
    std::cin >> arraySize;
    
    if (arraySize == 0) 
    {
        std::cout << "Array size must be greater than 0" << std::endl;
        return 1;
    }
    
    int* originalArray = new int[arraySize];
    
    std::cout << "Enter array elements:" << std::endl;
    for (size_t i = 0; i < arraySize; ++i) 
    {
        std::cout << "Element [" << i << "]: ";
        std::cin >> originalArray[i];
    }
    
    std::cout << "\nOriginal array:" << std::endl;
    printArray(originalArray, arraySize);
    
    size_t newSize;
    int* resultArray = removeElementsWithUniqueDigits(originalArray, arraySize, newSize);
    
    std::cout << "\nArray after removing elements with all unique digits:" << std::endl;
    if (newSize > 0) 
    {
        printArray(resultArray, newSize);
    } 
    else 
    {
        std::cout << "Array is empty" << std::endl;
    }
    
    delete[] originalArray;
    delete[] resultArray;
    
    return 0;
}

bool hasAllUniqueDigits(int number) 
{
    if (number < 0) 
    {
        number = -number;
    }
    
    // Для однозначных чисел - цифры не могут быть не уникальными
    if (number < 10) 
    {
        return false;
    }
    
    bool digits[10] = {false};
    
    while (number > 0) 
    {
        int digit = number % 10;
        
        if (digits[digit]) 
        {
            return false; // Нашли повторяющуюся цифру
        }
        
        digits[digit] = true;
        number /= 10;
    }
    
    return true; // Все цифры уникальны
}

int* removeElementsWithUniqueDigits(const int array[], size_t size, size_t& newSize) 
{
    size_t countToKeep = 0;
    
    for (size_t i = 0; i < size; ++i) 
    {
        if (!hasAllUniqueDigits(array[i])) 
        {
            ++countToKeep;
        }
    }
    
    newSize = countToKeep;
    
    if (newSize == 0) 
    {
        return nullptr;
    }
    
    int* resultArray = new int[newSize];
    size_t resultIndex = 0;
    
    for (size_t i = 0; i < size; ++i) 
    {
        if (!hasAllUniqueDigits(array[i])) 
        {
            resultArray[resultIndex] = array[i];
            ++resultIndex;
        }
    }
    
    return resultArray;
}

void printArray(const int array[], size_t size) 
{
    for (size_t i = 0; i < size; ++i) 
    {
        std::cout << array[i];
        if (i < size - 1) 
        {
            std::cout << " ";
        }
    }
    std::cout << std::endl;
}