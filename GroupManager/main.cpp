#include <iostream>
#include <string>
#include <windows.h>
#include <fstream>

// Функция для чтения слова из файла
std::string readWord(std::ifstream &inputFile) {
    std::string word;
    char ch;
    while (inputFile.get(ch)) {
        if (ch != '|' && ch != '\n') {
            word += ch;
        } else if (!word.empty()) {
            return word;
        }
    }
    return word.empty() ? "" : word;
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
}
