/*
Задано  сильно ветвящееся дерево. При  его  вводе  могли
быть  сделаны ошибки.  Провести проверку на отсутствие циклов,
то есть повторяющихся вершин.  При обнаружении цикла выдать на
экран последовательность вершин, составляющих цикл (10).
*/
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <windows.h>

int main(int argc, char *argv[]) {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // Обработка аргументов командной строки
    std::string inputPath = "input.txt";
    if (argc == 3 && strcmp(argv[1], "-f") == 0) {
        inputPath = argv[2];
    }

    std::ifstream inputFile(inputPath);
    if (!inputFile.is_open()) {
        throw std::runtime_error("Не удалось открыть файл \"" + inputPath + "\" для чтения");
    }

    std::vector<std::string> stack;
    std::string line;
    int lastLevel = 0;

    while (std::getline(inputFile, line)) {
        if (line.empty()) continue;
        int level = 0;
        while (line[level] == '.') level++;
        size_t length = line.length();

        std::string value = line.substr(level, length - level);

        if (level == 0) {
            stack.push_back(value);
            continue;
        }

        if (level > lastLevel) {
            stack.push_back(value);
        } else {
            for (int i = 0; i < lastLevel - level + 1; ++i) stack.pop_back();
            stack.push_back(value);
        }
        lastLevel = level;

        auto found = std::find(stack.begin(), stack.end(), value);
        if (found != stack.end() - 1) {
            for (; found != std::prev(stack.end()); ++found) {
                std::cout << *found << " --> ";
            }
            std::cout << value << std::endl;
        }
    }
}
