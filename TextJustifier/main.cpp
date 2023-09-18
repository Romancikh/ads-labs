#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <codecvt>
#include <locale>

// Функция для получения аргументов командной строки
std::vector<std::pair<std::string, std::string>> getCommandLineArguments(int argc, char *argv[]) {
    std::vector<std::pair<std::string, std::string>> arguments;
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        std::size_t pos = arg.find('=');
        if (pos != std::string::npos) {
            std::string key = arg.substr(2, pos - 2); // Извлечение ключа аргумента
            std::string value = arg.substr(pos + 1); // Извлечение значения аргумента
            arguments.emplace_back(key, value);
        }
    }
    return arguments;
}

// Функция для чтения слова из файла
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

// Функция для получения длины строки UTF-8
std::size_t getLength(std::string &utf8String) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::wstring wideString = converter.from_bytes(utf8String); // Преобразование UTF-8 строки в wstring
    return wideString.length();
}

// Функция для получения количества пробелов между словами
int getSpacesAmount(int wordsAmount, int freeSpace) {
    if (wordsAmount == 1) {
        return 0;
    }
    int spacesCount = freeSpace / (wordsAmount - 1);
    if (freeSpace % (wordsAmount - 1) != 0) {
        spacesCount++;
    }
    return spacesCount;
}

int main(int argc, char *argv[]) {
    // Получение аргументов командной строки
    std::vector<std::pair<std::string, std::string>> arguments = getCommandLineArguments(argc, argv);

    // Установка значений по умолчанию для пути к входному файлу, пути к выходному файлу, ширины строки и отступа абзаца
    std::string inputPath = "input.txt";
    std::string outputPath = "output.txt";
    int lineWidth = 80;
    int indentWidth = 4;

    // Обработка аргументов командной строки
    for (const auto &[key, value]: arguments) {
        if (key == "input-file") {
            inputPath = value;
        } else if (key == "output-file") {
            outputPath = value;
        } else if (key == "line-width") {
            try {
                lineWidth = std::stoi(value);
            } catch (const std::exception &error) {
                std::cerr << "Не удалось получить значение ширины строки, взято значение по умолчанию: 80."
                          << std::endl;
            }
        } else if (key == "indent-width") {
            try {
                indentWidth = std::stoi(value);
            } catch (const std::exception &error) {
                std::cerr << "Не удалось получить значение ширины отступа, взято значение по умолчанию: 4."
                          << std::endl;
            }
        } else {
            std::cerr << "Недопустимый аргумент командной строки: " << key << std::endl;
            return 1;
        }
    }

    // Проверка наличия недопустимых входных данных
    if (indentWidth >= lineWidth) {
        std::cerr << "Ширина отступа больше или равна ширине строки." << std::endl;
        return 1;
    }

    // Открытие файлов для чтения и записи
    std::ifstream inputFile(inputPath);
    if (!inputFile.is_open()) {
        std::cerr << "Не удалось открыть файл для чтения: " << inputPath << std::endl;
        return 1;
    }

    std::ofstream outputFile(outputPath);
    if (!outputFile.is_open()) {
        std::cerr << "Не удалось открыть файл для записи: " << outputPath << std::endl;
        return 1;
    }

    // Обработка текста
    std::vector<std::string> words;
    bool isLastLine = false;
    while (!inputFile.eof()) {
        int currentLength = indentWidth;
        outputFile << std::string(indentWidth, ' ');
        indentWidth = 0;
        if (!words.empty()) {
            currentLength = static_cast<int>(getLength(words.back())) + 1;
        }
        while (currentLength - 1 <= lineWidth) {
            std::string word = readWord(inputFile);
            if (getLength(word) > static_cast<std::size_t>(lineWidth)) {
                std::cerr << "Слово больше чем ширина строки: " << word << std::endl;
                return 1;
            }
            words.push_back(word);
            currentLength += static_cast<int>(getLength(word)) + 1;
            if (word.empty()) {
                isLastLine = true;
                break;
            }
        }
        currentLength -= static_cast<int>(getLength(words.back())) + static_cast<int>(words.size());
        int freeSpace = lineWidth - currentLength;
        while (words.size() > 1) {
            int spacesAmount = getSpacesAmount(static_cast<int>(words.size()) - 1, freeSpace);
            if (isLastLine) {
                spacesAmount = 1;
                if (words.size() == 2 && words.back().empty()) {
                    spacesAmount = 0;
                }
            }
            outputFile << words.front() << std::string(spacesAmount, ' ');
            freeSpace -= spacesAmount;
            words.erase(words.begin());
        }
        outputFile << std::endl;
    }

    // Закрытие файлов
    inputFile.close();
    outputFile.close();

    return 0;
}
