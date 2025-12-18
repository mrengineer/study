#include <iostream>
#include <fstream>
#include <string>
#include <vector>

namespace config
{
    const int CURRENT_YEAR = 2025;
    const double DEFAULT_SALARY_LIMIT = 1000.0;
}

// структура сотрудника
struct employee
{
    std::string full_name;
    int hire_year;
    std::string position;
    double salary;
    int work_experience;
};

// шаблонная функция вывода
template <typename T>
void write_value(std::ofstream& file, const T& value)
{
    file << value;
}

// перегрузка подсчёта стажа
int calculate_experience(int hire_year)
{
    return config::CURRENT_YEAR - hire_year;
}

// перегрузка с параметром
int calculate_experience(int hire_year, int current_year)
{
    return current_year - hire_year;
}

// чтение из файла
void read_employees(const std::string& file_name,
                    std::vector<employee>& employees)
{
    std::ifstream input_file(file_name);

    if (!input_file)
    {
        std::cout << "Input file open error\n";
        return;
    }

    employee temp_employee;

    while (input_file >> temp_employee.full_name
                      >> temp_employee.hire_year
                      >> temp_employee.position
                      >> temp_employee.salary)
    {
        temp_employee.work_experience =
            calculate_experience(temp_employee.hire_year);

        employees.push_back(temp_employee);
    }
}

// запись сотрудников с маленькой зарплатой
size_t write_low_salary_employees(const std::string& file_name,
                                  const std::vector<employee>& employees,
                                  double salary_limit = config::DEFAULT_SALARY_LIMIT)
{
    std::ofstream output_file(file_name);

    if (!output_file)
    {
        std::cout << "Output file open error\n";
        return 0;
    }

    size_t written_count = 0;

    output_file << "Employees with low salary\n\n";

    for (size_t i = 0; i < employees.size(); i++)
    {
        if (employees[i].salary < salary_limit)
        {
            write_value(output_file, "Name: ");
            write_value(output_file, employees[i].full_name);
            write_value(output_file, "\n");

            write_value(output_file, "Position: ");
            write_value(output_file, employees[i].position);
            write_value(output_file, "\n");

            write_value(output_file, "Hire year: ");
            write_value(output_file, employees[i].hire_year);
            write_value(output_file, "\n");

            write_value(output_file, "Experience: ");
            write_value(output_file, employees[i].work_experience);
            write_value(output_file, " years\n");

            write_value(output_file, "Salary: ");
            write_value(output_file, employees[i].salary);
            write_value(output_file, "\n\n");

            written_count++;
        }
    }

    return written_count;
}

int main()
{
    std::vector<employee> employees;
    double salary_limit;

    std::cout << "Enter salary limit: ";
    std::cin >> salary_limit;

    read_employees("input.txt", employees);

    std::cout << "Read employees count: "
              << employees.size() << "\n";

    size_t written_count =
        write_low_salary_employees("output.txt",
                                   employees,
                                   salary_limit);

    std::cout << "Written employees count: "
              << written_count << "\n";

    std::cout << "Processing finished\n";
    std::cout << "Check output.txt file\n";

    return 0;
}
