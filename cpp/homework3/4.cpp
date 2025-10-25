#include <iostream>

int main() 
{
    // Константы для размеров таблицы
    const int ROW_COUNT = 4;
    const int COLUMN_COUNT = 6;
    const int CELL_VALUE = 5;

    
    std::cout << "Программа выводит таблицу " 
              << ROW_COUNT << "x" << COLUMN_COUNT 
              << " с числом " << CELL_VALUE << " в каждой ячейке.\n\n";

    
    for (int row = 0; row < ROW_COUNT; ++row) 
    {
        for (int col = 0; col < COLUMN_COUNT; ++col) 
        {
            std::cout << CELL_VALUE;
            std::cout << ((col < COLUMN_COUNT - 1) ? '\t' : '\n');
        }
    }

    return 0;
}
