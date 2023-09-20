#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <fstream>

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

// Функция для получения элемента списка
std::vector<std::string> readItem(std::ifstream &inputFile) {
    std::string group = readWord(inputFile);
    std::string faculty = readWord(inputFile);
    std::string course = readWord(inputFile);
    std::vector<std::string> item = {group, faculty, course};
    return item;
}

struct Group {
    std::string value;
    Group *next;
};

struct Course {
    std::string value;
    Course *next;
    Group *group;
};

struct Faculty {
    std::string value;
    Faculty *next;
    Course *course;
};

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
}
