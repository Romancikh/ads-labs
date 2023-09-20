#include <iostream>
#include <string>
#include <windows.h>
#include <fstream>

struct Group {
    std::string value;
    Group *next;
};

struct Course {
    std::string value;
    Course *next;
    Group *headGroup;
};

struct Faculty {
    std::string value;
    Faculty *next;
    Course *headCourse;
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

// Процедура добавления данных
void push(Group *prev, std::string value) {
    Group newGroup = {value, nullptr};
    prev->next = &newGroup;
}

void push(Course *prev, std::string value, Group &headGroup) {
    Course newCourse = {value, nullptr, &headGroup};
    prev->next = &newCourse;
}

void push(Faculty *prev, std::string value, Course &headCourse) {
    Faculty newFaculty = {value, nullptr, &headCourse};
    prev->next = &newFaculty;
}

// Процедура для чтения данных из файла
void readFile(std::ifstream &inputFile) {
    Group headGroup = {readWord(inputFile), nullptr};
    Faculty headFaculty = {readWord(inputFile), nullptr, nullptr};
    Course headCourse = {readWord(inputFile), nullptr, &headGroup};
    headFaculty.headCourse = &headCourse;
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
