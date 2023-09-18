#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <windows.h>

// ������� ��� ��������� ���������� ��������� ������
std::vector<std::pair<std::string, std::string>> getCommandLineArguments(int argc, char *argv[]) {
    std::vector<std::pair<std::string, std::string>> arguments;
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        std::size_t pos = arg.find('=');
        if (pos != std::string::npos) {
            std::string key = arg.substr(2, pos - 2); // ���������� ����� ���������
            std::string value = arg.substr(pos + 1); // ���������� �������� ���������
            arguments.emplace_back(key, value);
        }
    }
    return arguments;
}

// ������� ��� ������ ����� �� �����
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

// ������� ��� ��������� ���������� �������� ����� �������
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
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // ��������� ���������� ��������� ������
    std::vector<std::pair<std::string, std::string>> arguments = getCommandLineArguments(argc, argv);

    // ��������� �������� �� ��������� ��� ���� � �������� �����, ���� � ��������� �����, ������ ������ � ������� ������
    std::string inputPath = "input.txt";
    std::string outputPath = "output.txt";
    int lineWidth = 80;
    int indentWidth = 4;

    // ��������� ���������� ��������� ������
    for (const auto &[key, value]: arguments) {
        if (key == "input-file") {
            inputPath = value;
        } else if (key == "output-file") {
            outputPath = value;
        } else if (key == "line-width") {
            try {
                lineWidth = std::stoi(value);
            } catch (const std::exception &error) {
                std::cerr << "�� ������� �������� �������� ������ ������, ����� �������� �� ���������: 80."
                          << std::endl;
            }
        } else if (key == "indent-width") {
            try {
                indentWidth = std::stoi(value);
            } catch (const std::exception &error) {
                std::cerr << "�� ������� �������� �������� ������ �������, ����� �������� �� ���������: 4."
                          << std::endl;
            }
        } else {
            std::cerr << "������������ �������� ��������� ������: " << key << std::endl;
            return 1;
        }
    }

    // �������� ������� ������������ ������� ������
    if (indentWidth >= lineWidth) {
        std::cerr << "������ ������� ������ ��� ����� ������ ������." << std::endl;
        return 1;
    }

    // �������� ������ ��� ������ � ������
    std::ifstream inputFile(inputPath);
    if (!inputFile.is_open()) {
        std::cerr << "�� ������� ������� ���� ��� ������: " << inputPath << std::endl;
        return 1;
    }

    std::ofstream outputFile(outputPath);
    if (!outputFile.is_open()) {
        std::cerr << "�� ������� ������� ���� ��� ������: " << outputPath << std::endl;
        return 1;
    }

    // ��������� ������
    std::vector<std::string> words;
    bool isLastLine = false;
    while (!inputFile.eof()) {
        int currentLength = indentWidth;
        outputFile << std::string(indentWidth, ' ');
        indentWidth = 0;
        if (!words.empty()) {
            currentLength = static_cast<int>(words.back().length()) + 1;
        }
        while (currentLength - 1 <= lineWidth) {
            std::string word = readWord(inputFile);
            if (word.length() > static_cast<std::size_t>(lineWidth)) {
                std::cerr << "����� ������ ��� ������ ������: " << word << std::endl;
                return 1;
            }
            words.push_back(word);
            currentLength += static_cast<int>(word.length()) + 1;
            if (word.empty()) {
                isLastLine = true;
                break;
            }
        }
        currentLength -= static_cast<int>(words.back().length()) + static_cast<int>(words.size());
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

    // �������� ������
    inputFile.close();
    outputFile.close();

    return 0;
}
