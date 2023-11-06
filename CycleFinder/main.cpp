#include <fstream>
#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <windows.h>

struct Tree {
    std::string value;
    int level{};
    Tree *father{};
    std::vector<Tree *> sons;
};

void readFromFile(const std::string &inputPath, Tree *&root) {
    std::ifstream inputFile(inputPath);
    if (!inputFile.is_open()) {
        throw std::runtime_error("Не удалось открыть файл \"" + inputPath + "\" для чтения");
    }

    std::string line;
    Tree *last = nullptr;
    int lastLevel = 0;

    while (not inputFile.eof()) {
        std::getline(inputFile, line);
        if (line.empty()) continue;
        int level = 0;
        size_t length = line.length();
        while (line[level] == '.') level++;
        auto *current = new Tree;
        current->value = line.substr(level, length - level);
        current->level = level;
        if (level == 0) {
            root = current;
        } else if (last != nullptr && level == lastLevel) {
            last->father->sons.push_back(current);
            current->father = last->father;
        } else if (last != nullptr && level > lastLevel) {
            last->sons.push_back(current);
            current->father = last;
        } else if (last != nullptr) {
            auto father = last;
            for (int i = 0; i <= lastLevel - level; ++i) father = father->father;
            father->sons.push_back(current);
            current->father = father;
        }
        lastLevel = level;
        last = current;
    }

    inputFile.close();
}

void writeToConsole(Tree *root) {
    std::stack<Tree *> stack;
    stack.push(root);

    while (!stack.empty()) {
        Tree *current = stack.top();
        int level = current->level;
        stack.pop();

        for (int i = 0; i < level; ++i) {
            std::cout << '.';
        }
        std::cout << current->value << std::endl;

        for (auto it = current->sons.rbegin(); it != current->sons.rend(); ++it) {
            stack.push(*it);
        }
    }
}

int main(int argc, char *argv[]) {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // Обработка аргументов командной строки
    std::string inputPath = "input.txt";
    if (argc == 3 && strcmp(argv[1], "-f") == 0) {
        inputPath = argv[2];
    }

    Tree *root = nullptr;

    readFromFile(inputPath, root);
    writeToConsole(root);
}
