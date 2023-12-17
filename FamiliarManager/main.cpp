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
#include <limits>
#include <queue>
#include <cmath>

const int INF = std::numeric_limits<int>::max();

std::vector<int> bfs(std::vector<std::vector<int>> &graph, int start) {
    std::vector<int> distance(graph.size(), INF);
    std::queue<int> queue;

    distance[start] = 0;
    queue.push(start);

    while (not queue.empty()) {
        int vertex = queue.front();
        queue.pop();

        for (int to: graph[vertex]) {
            if (distance[to] == INF) {
                distance[to] = distance[vertex] + 1;
                queue.push(to);
            }
        }
    }

    return distance;
}

void readFromFile(std::ifstream &inputFile, std::vector<std::vector<int>> &graph,
                  std::unordered_map<std::string, int> &vertexes) {
    std::string from, to;

    while (inputFile >> from >> to) {
        auto addVertex = [&](const std::string &vertex) {
            if (vertexes.find(vertex) == vertexes.end()) {
                vertexes[vertex] = (int) graph.size();
                graph.emplace_back();
            }
            return vertexes[vertex];
        };

        int fromIndex = addVertex(from);
        int toIndex = addVertex(to);

        graph[fromIndex].push_back(toIndex);
        graph[toIndex].push_back(fromIndex);
    }
}

std::string week(std::vector<int> distance, int finish) {
    int distance1 = distance[finish];
    if (distance1 <= 1) return "Уже знакомы";
    if (distance1 == INF) return "Не могут познакомится";
    return "Познакомятся через " + std::to_string((int) ceil(log2(distance1))) + " недель";
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

    std::unordered_map<std::string, int> vertexes;
    std::vector<std::vector<int>> graph;

    readFromFile(inputFile, graph, vertexes);

    std::cout << "Студенты" << std::endl;
    for (const auto &vertex: vertexes) {
        std::cout << vertex.first << std::endl;
    }

    std::string first;
    std::string second;

    while (true) {
        std::cout << std::endl << "Введите первого студента: ";
        std::cin >> first;

        if (vertexes.find(first) == vertexes.end()) return 0;
        int firstIndex = vertexes.at(first);

        std::cout << "Введите второго студента: ";
        std::cin >> second;

        if (vertexes.find(first) == vertexes.end()) return 0;
        int secondIndex = vertexes.at(second);

        std::cout << week(bfs(graph, firstIndex), secondIndex) << std::endl;
    }
}
