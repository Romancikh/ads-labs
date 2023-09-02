#include <fstream>
#include <iostream>

int main() {
    std::ifstream inputFile("input.txt"); // Открытие файла для чтения
    std::ofstream outputFile("output.txt"); // Открытие файла для записи

    if (!inputFile.is_open()) {
        std::cout << "Не удалось открыть файл для чтения." << std::endl;
        return 1;
    }
    if (!outputFile.is_open()) {
        std::cout << "Не удалось открыть файл для записи." << std::endl;
        return 1;
    }

    return 0;
}
