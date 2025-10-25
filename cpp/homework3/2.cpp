#include <iostream> 
#include <string>   


std::string get_month(int month_number) {
    switch (month_number) {
        case 1:  return "Январь";
        case 2:  return "Февраль";
        case 3:  return "Март";
        case 4:  return "Апрель";
        case 5:  return "Май";
        case 6:  return "Июнь";
        case 7:  return "Июль";
        case 8:  return "Август";
        case 9:  return "Сентябрь";
        case 10: return "Октябрь";
        case 11: return "Ноябрь";
        case 12: return "Декабрь";
        default: return "Неверный номер месяца";
    }
}

int main() {
    int month_number = 0;


    std::cout << "Введите порядковый номер месяца (1-12): ";
    std::cin >> month_number;


    std::string month_name = get_month(month_number);


    std::cout << "Название месяца: " << month_name << std::endl;

    return 0;
}
