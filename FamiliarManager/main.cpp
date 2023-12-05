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
    int indexFrom = 0;
    int indexTo = 1;

    while (inputFile >> from >> to) {
        if (vertexes.find(from) != vertexes.end()) {
            indexTo = indexFrom;
            indexFrom = vertexes[from];
        } else {
            vertexes[from] = indexFrom;
            graph.emplace_back();
        }

        if (vertexes.find(to) != vertexes.end()) {
            indexTo = vertexes[to];
        } else {
            vertexes[to] = indexTo;
            graph.emplace_back();
        }

        graph[indexFrom].push_back(indexTo);
        graph[indexTo].push_back(indexFrom);

        indexFrom = (int) vertexes.size();
        indexTo = indexFrom + 1;
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

    return 0;
}
