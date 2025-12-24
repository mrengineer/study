#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <vector>

namespace app_config {
    const size_t SUBJECTS_COUNT = 5;
    const size_t MAX_STUDENTS = 100;
}


// Структура даты. пока храним только год
struct Date {
    int year;
};


// Структура студента все данные сгрупированы
struct Student {
    std::string last_name;
    std::string first_name;
    std::string middle_name;
    Date birth_date;
    int grades[app_config::SUBJECTS_COUNT];
};


// Сравнение студентов фамилия -> год рождения
bool isStudentLess(const Student& a, const Student& b) {
    if (a.last_name != b.last_name) {
        return a.last_name < b.last_name;
    }

    return a.birth_date.year < b.birth_date.year;
}


// Универсальная сортировка выбором
// Работает с массивом и с vector через operator[]
template <typename Container, typename Compare>
void selectionSort(Container& data, size_t size, Compare compare) {
    for (size_t i = 0; i < size; ++i) {
        size_t min_index = i;

        for (size_t j = i + 1; j < size; ++j) {
            if (compare(data[j], data[min_index])) {
                min_index = j;
            }
        }

        if (i != min_index) {
            auto temp = data[i];
            data[i] = data[min_index];
            data[min_index] = temp;
        }
    }
}


// Чтение студентов из файла
std::pair<int, size_t> readStudents(const std::string& file_name,
                                    Student* students) {
    std::ifstream file(file_name);
    int group_number = 0;
    size_t count = 0;

    if (!file.is_open()) {
        std::cout << "Error: cannot open input file\n";
        return {group_number, count};
    }

    file >> group_number;

    while (file && count < app_config::MAX_STUDENTS) {
        Student student;

        file >> student.last_name
             >> student.first_name
             >> student.middle_name
             >> student.birth_date.year;

        for (size_t i = 0; i < app_config::SUBJECTS_COUNT; ++i) {
            file >> student.grades[i];
        }

        if (file) {
            students[count] = student;
            ++count;
        }
    }

    return {group_number, count};
}


// Вывод массива студентов
void printStudentsToConsole(const Student* students, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        std::cout << students[i].last_name << " "
                  << students[i].first_name << " "
                  << students[i].middle_name << " "
                  << students[i].birth_date.year << " ";

        for (size_t j = 0; j < app_config::SUBJECTS_COUNT; ++j) {
            std::cout << students[i].grades[j] << " ";
        }

        std::cout << "\n";
    }
}


// Вывод вектора студентов
void printStudentsToConsole(const std::vector<Student>& students) {
    for (size_t i = 0; i < students.size(); ++i) {
        std::cout << students[i].last_name << " "
                  << students[i].first_name << " "
                  << students[i].middle_name << " "
                  << students[i].birth_date.year << " ";

        for (size_t j = 0; j < app_config::SUBJECTS_COUNT; ++j) {
            std::cout << students[i].grades[j] << " ";
        }

        std::cout << "\n";
    }
}


// Запись студентов в файл
void writeStudents(const std::string& file_name,
                   int group_number,
                   const Student* students,
                   size_t size) {
    std::ofstream file(file_name);

    if (!file.is_open()) {
        std::cout << "Error: cannot open output file\n";
        return;
    }

    file << "Group number: " << group_number << "\n";

    for (size_t i = 0; i < size; ++i) {
        file << students[i].last_name << " "
             << students[i].first_name << " "
             << students[i].middle_name << " "
             << students[i].birth_date.year << " ";

        for (size_t j = 0; j < app_config::SUBJECTS_COUNT; ++j) {
            file << students[i].grades[j] << " ";
        }

        file << "\n";
    }
}


// Точка входа
int main() {
    Student students[app_config::MAX_STUDENTS];

    std::cout << "Reading students from input.txt\n";

    auto result = readStudents("input.txt", students);
    int group_number = result.first;
    size_t students_count = result.second;

    std::cout << "Students read from file:\n";
    printStudentsToConsole(students, students_count);

    std::cout << "Sorting array of students\n";
    selectionSort(students, students_count, isStudentLess);

    std::cout << "Sorted students (array):\n";
    printStudentsToConsole(students, students_count);

    std::cout << "Demonstrating vector sorting\n";

    std::vector<Student> students_vector;
    for (size_t i = 0; i < students_count; ++i) {
        students_vector.push_back(students[i]);
    }

    selectionSort(students_vector, students_vector.size(), isStudentLess);

    std::cout << "Sorted students (vector):\n";
    printStudentsToConsole(students_vector);

    std::cout << "Writing result to output.txt\n";
    writeStudents("output.txt", group_number, students, students_count);

    std::cout << "Done\n";
    return 0;
}
