/* Имеется файл записей с некоторым ключевым полем. Построить в оперативной памяти идеально сбалансированное бинарное
 * дерево поиска и обеспечить поиск указанных записей (7). */

#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <iomanip>

struct Tree {
    int key{};
    std::string value;
    Tree *right{};
    Tree *left{};
};

Tree *fillTree(const std::vector<std::pair<int, std::string>> &vertexes, int start, int end) {
    if (end < start) {
        return nullptr;
    }

    int mid = (start + end) / 2;
    auto *node = new Tree;

    node->key = vertexes[mid].first;
    node->value = vertexes[mid].second;
    node->left = fillTree(vertexes, start, mid - 1);
    node->right = fillTree(vertexes, mid + 1, end);

    return node;
}

void deleteTree(Tree *node) {
    if (node == nullptr) {
        return;
    }

    deleteTree(node->left);
    deleteTree(node->right);

    delete node;
}

void printTree(Tree *node, int indent = 0) {
    if (node != nullptr) {
        if (node->right) {
            printTree(node->right, indent + 4);
        }

        if (indent) {
            std::cout << std::string(indent, ' ');
        }

        if (node->right) {
            std::cout << " /" << std::endl << std::string(indent, ' ');
        }

        std::cout << node->key << std::endl << ' ';

        if (node->left) {
            std::cout << std::string(indent + 1, ' ') << '\\' << std::endl;
            printTree(node->left, indent + 4);
        }
    }
}

Tree *searchTree(Tree *node, int key) {
    if (node == nullptr || key == node->key) {
        return node;
    }
    if (key < node->key) {
        return searchTree(node->left, key);
    }
    return searchTree(node->right, key);
}

int main(int argc, char *argv[]) {
    std::string inputPath = "input.txt";
    if (argc == 3 && std::strcmp(argv[1], "-f") == 0) {
        inputPath = argv[2];
    }

    std::ifstream inputFile(inputPath);
    if (!inputFile.is_open()) {
        throw std::runtime_error("Не удалось открыть файл \"" + inputPath + "\" для чтения");
    }

    std::vector<std::pair<int, std::string>> vertexes;
    int key;
    std::string record;
    while (inputFile >> key >> record) {
        vertexes.emplace_back(key, record);
    }

    std::sort(vertexes.begin(), vertexes.end());

    auto root = fillTree(vertexes, 0, (int) vertexes.size() - 1);

    int command;
    while (true) {
        std::cout << "0. Выход\n1. Поиск\n2. Вывести\n\033[1;33mКоманда: \033[0m";
        std::cin >> command;
        Tree *node;

        switch (command) {
            case 0:
                deleteTree(root);
                return 0;
            case 1:
                std::cout << "\033[1;34mНайти: \033[0m";
                int searchKey;
                std::cin >> searchKey;
                node = searchTree(root, searchKey);
                if (node == nullptr) {
                    std::cout  <<  "\033[1;31mНе найдено\033[0m" << std::endl;
                } else {
                    std::cout   << "\033[1;32mНайдено: " << node->value << "\033[0m" << std::endl;
                }
                break;
            case 2:
                printTree(root);
                std::cout << std::endl;
                break;
        }
    }
}