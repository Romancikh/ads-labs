/**
 * Задано сильно ветвящееся дерево. При его вводе могли быть сделаны ошибки.  Провести проверку на отсутствие циклов,
 * то есть повторяющихся вершин.  При обнаружении цикла выдать на экран последовательность вершин, составляющих цикл (10).
 */

#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <cstring>

void printCycle(const std::vector<int> &cycle, std::unordered_map<std::string, int> vertexes) {
    for (int v: cycle) {
        auto it = std::find_if(vertexes.begin(), vertexes.end(),
                               [&v](const auto pair) { return pair.second == v; });
        std::cout << it->first << " ";
    }
}

std::vector<int> getCycle(std::vector<int> &from, int lastVertex) {
    std::vector<int> cycle = {lastVertex};
    for (int v = from[lastVertex]; v != lastVertex; v = from[v]) {
        cycle.push_back(v);
    }
    cycle.push_back(lastVertex);
    std::reverse(cycle.begin(), cycle.end());
    return cycle;
}

void dfs(std::vector<std::vector<int>> &graph, int v, std::vector<int> &visited, std::vector<int> &from,
         std::vector<int> &cycle) {
    visited[v] = 1;

    for (int to: graph[v]) {
        if (to == from[v]) {
            continue;
        }
        if (visited[to] == 0) {
            from[to] = v;
            dfs(graph, to, visited, from, cycle);
            if (!cycle.empty()) {
                return;
            }
        } else if (visited[to] == 1) {
            from[to] = v;
            cycle = getCycle(from, to);
            return;
        }
    }
}

void readFromFile(std::ifstream &inputFile, std::vector<std::vector<int>> &graph,
                  std::unordered_map<std::string, int> &vertexes) {
    std::string line;
    int lastLevel = 0;
    std::vector<int> from;
    int index = 0;

    while (std::getline(inputFile, line)) {
        if (line.empty()) continue;

        graph.emplace_back();

        int level = 0;
        while (line[level] == '.') level++;
        std::string value = line.substr(level, line.length() - level);

        if (vertexes.find(value) != vertexes.end()) {
            index = vertexes[value];
        } else {
            vertexes[value] = index;
        }

        if (level == 0) {
            from.push_back(index);
        } else if (level > lastLevel) {
            graph[from.back()].push_back(index);
            graph[index].push_back(from.back());
            from.push_back(index);
        } else if (level < lastLevel) {
            for (int i = 0; i < lastLevel - level + 1; ++i) {
                from.pop_back();
            }
            graph[from.back()].push_back(index);
            graph[index].push_back(from.back());
            from.push_back(index);
        } else {
            from.pop_back();
            graph[from.back()].push_back(index);
            graph[index].push_back(from.back());
            from.push_back(index);
        }
        lastLevel = level;
        index = (int) vertexes.size();
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

    std::vector<int> visited(vertexes.size());
    std::vector<int> from(vertexes.size(), -1);
    std::vector<int> cycle;

    for (int v = 0; cycle.empty() && v < vertexes.size(); v++) {
        if (!visited[v]) {
            dfs(graph, v, visited, from, cycle);
        }
    }

    if (!cycle.empty()) {
        std::cout << "Yes" << std::endl;
        printCycle(cycle, vertexes);
    } else {
        std::cout << "No" << std::endl;
    }
}
