#include <string>
#include <fstream>
#include <iostream>
#include <windows.h>

struct Group {
    std::string group;
    std::string faculty;
    std::string course;
    Group *next;
    Group *nextFaculty;
    Group *nextCourse;

    Group(const std::string &group, const std::string &faculty, const std::string &course, Group *next = nullptr,
          Group *nextFaculty = nullptr, Group *nextCourse = nullptr) : group(group), faculty(faculty), course(course),
                                                                       next(next), nextFaculty(nextFaculty),
                                                                       nextCourse(nextCourse) {}
};

// Функция для удаления лидирующих и конечных символов
std::string trim(const std::string &str) {
    size_t first = str.find_first_not_of(" \t\n\r"); // Находим первый значащий символ
    size_t last = str.find_last_not_of(" \t\n\r"); // Находим последний значащий символ
    if (first == std::string::npos) // На случай, если строка содержит только пробелы
        return "";
    return str.substr(first, (last - first + 1));
}

// Функция для чтения слова из файла
std::string readWord(std::ifstream &inputFile) {
    std::string word;
    char ch;
    while (inputFile.get(ch)) {
        if (ch != '|' && ch != '\n') {
            word += ch;
        } else if (!word.empty()) {
            return trim(word);
        }
    }
    return word.empty() ? "" : trim(word);
}

// Процедура для чтения данных из файла
void readFile(std::ifstream &inputFile) {

}

int main(int argc, char *argv[]) {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::string inputPath = "input.txt";
    if (argc == 3 && strcmp(argv[1], "-f") == 0) {
        inputPath = argv[2];
    }

    std::ifstream inputFile(inputPath);
    if (!inputFile.is_open()) {
        std::cerr << "Не удалось открыть файл для чтения: " << inputPath << std::endl;
        return 1;
    }

    readFile(inputFile);
}
