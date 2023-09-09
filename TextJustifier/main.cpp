/*
 * Автор: Кутимский Роман
 * Группа: ПС-21
 *
 * Условие задачи №21:
 * В текстовом файле записан отдельный абзац. Переносов слов нет. Выровнять строки абзаца по ширине.
 * Иными словами, правые границы строк выравниваются по заданной позиции за счет вставки дополнительных
 * пробелов между словами. Первая строка абзаца должна иметь заданный отступ, а остальные строки должны
 * начинаться с первой позиции. Последняя строка абзаца по правому краю не выравнивается. Число строк в
 * исходном и конечном файлах может отличаться (8).
 *
 * Используемые ресурсы:
 * 1. https://metanit.com/cpp/tutorial
 * 2. https://learn.microsoft.com/ru-ru/cpp/cpp
 *
 * Среда разработки: CLion 2023.2.1
 * Версия C++: C++17
 *
 * Примечание:
 *
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <codecvt>
#include <locale>

std::vector<std::pair<std::string, std::string>> parseArguments(int argc, char *argv[]) {
    std::vector<std::pair<std::string, std::string>> arguments;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        size_t pos = arg.find('=');

        if (pos != std::string::npos) {
            std::string key = arg.substr(2, pos - 2); // Извлечение ключа аргумента
            std::string value = arg.substr(pos + 1); // Извлечение значения аргумента
            arguments.emplace_back(key, value);
        }

    }

    return arguments;
}

std::string readWord(std::ifstream &inputFile) {
    std::string word;
    char ch;

    while (inputFile.get(ch)) {
        if (ch != ' ' && ch != '\n') {
            word += ch;
        } else if (!word.empty()) {
            return word;
        }
    }

    return word.empty() ? "" : word;
}

size_t getLength(std::string &utf8String) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::wstring wideString = converter.from_bytes(utf8String); // Преобразование UTF-8 строки в wstring
    return wideString.length();
}

int main(int argc, char *argv[]) {
    std::vector<std::pair<std::string, std::string>> arguments = parseArguments(argc, argv);

    std::string inputPath = "input.txt";
    std::string outputPath = "output.txt";

    int width = 80;
    int indent = 4;

    // Обработка аргументов
    for (const auto &arg: arguments) {
        if (arg.first == "input-file") {
            inputPath = arg.second;
        }
        if (arg.first == "output-file") {
            outputPath = arg.second;
        }
        if (arg.first == "width") {
            try {
                width = std::stoi(arg.second);
            } catch (const std::exception &error) {
                std::cerr << "Не удалось получить значение ширины, взято значение по умолчанию: 80." << std::endl;
            }
        }
        if (arg.first == "indent") {
            try {
                indent = std::stoi(arg.second);
            } catch (const std::exception &error) {
                std::cerr << "Не удалось получить значение отступа, взято значение по умолчанию: 4." << std::endl;
            }
        }
    }

    std::ifstream inputFile(inputPath); // Открытие файла для чтения
    std::ofstream outputFile(outputPath); // Открытие файла для записи

    if (!inputFile.is_open()) {
        std::cerr << "Не удалось открыть файл для чтения." << std::endl;
        return 1;
    }
    if (!outputFile.is_open()) {
        std::cerr << "Не удалось открыть файл для записи." << std::endl;
        return 1;
    }

    // Закрытие файлов
    inputFile.close();
    outputFile.close();

    return 0;
}
