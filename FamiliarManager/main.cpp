/**
 * В общежитии живет N студентов. При поселении каждый студент представил список своих знакомых.
 * Каждое воскресение организуется вечер знакомств, когда знакомые любого студента знакомятся между
 * собой. Выяснить, через сколько недель познакомятся два указанных студента (8).
 */

#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <unordered_map>

void readFromFile(std::ifstream &inputFile, std::vector<std::vector<int>> &graph,
                  std::unordered_map<std::string, int> &vertexes) {
    std::string from;
    std::string to;
    int fromIndex = 0;
    int toIndex = 1;

    while (inputFile >> from >> to) {
        if (vertexes.find(from) != vertexes.end()) {
            toIndex = fromIndex;
            fromIndex = vertexes[from];
        } else {
            vertexes[from] = fromIndex;
            graph.emplace_back();
        }

        if (vertexes.find(to) != vertexes.end()) {
            toIndex = vertexes[to];
        } else {
            vertexes[to] = toIndex;
            graph.emplace_back();
        }

        graph[fromIndex].push_back(toIndex);
        graph[toIndex].push_back(fromIndex);

        fromIndex = (int) vertexes.size();
        toIndex = fromIndex + 1;
    }
}

int main(int argc, char *argv[]) {
    // Обработка аргументов командной строки
    std::string inputPath = "input.txt";
    if (argc == 3 && std::strcmp(argv[1], "-f") == 0) {
        inputPath = argv[2];
    }

    std::ifstream inputFile(inputPath);
    if (!inputFile.is_open()) {
        throw std::runtime_error("Не удалось открыть файл \"" + inputPath + "\" для чтения");
    }

    std::unordered_map<std::string, int> vertexes;
    std::vector<std::vector<int>> graph;

    readFromFile(inputFile, graph, vertexes);

    std::cout << "Студенты" << std::endl;
    for (const auto& vertex: vertexes) {
        std::cout << vertex.first << std::endl;
    }

    std::string first;
    std::string second;

    std::cout << std::endl << "Введите первого студента: ";
    std::cin >> first;

    int firstIndex = vertexes.at(first);

    std::cout << "Введите второго студента: ";
    std::cin >> second;

    int secondIndex = vertexes.at(second);

    std::cout << firstIndex << secondIndex << std::endl;

    return 0;
}
