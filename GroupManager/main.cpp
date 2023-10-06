#include <string>
#include <fstream>
#include <iostream>
#include <windows.h>

struct Group {
    std::string group;
    std::string faculty;
    std::string course;
    Group *next;
    Group *nextFaculty;
    Group *nextCourse;

    Group(const std::string &group, const std::string &faculty, const std::string &course, Group *next = nullptr,
          Group *nextFaculty = nullptr, Group *nextCourse = nullptr) : group(group), faculty(faculty), course(course),
                                                                       next(next), nextFaculty(nextFaculty),
                                                                       nextCourse(nextCourse) {}
};

// ������� ��� �������� ���������� � �������� ��������
std::string trim(const std::string &str) {
    size_t first = str.find_first_not_of(" \t\n\r"); // ������� ������ �������� ������
    size_t last = str.find_last_not_of(" \t\n\r"); // ������� ��������� �������� ������
    if (first == std::string::npos) // �� ������, ���� ������ �������� ������ �������
        return "";
    return str.substr(first, (last - first + 1));
}

// ������� ��� ������ ����� �� �����
std::string readWord(std::ifstream &inputFile) {
    std::string word;
    char ch;
    while (inputFile.get(ch)) {
        if (ch != '|' && ch != '\n') {
            word += ch;
        } else if (!word.empty()) {
            return trim(word);
        }
    }
    return word.empty() ? "" : trim(word);
}

// ��������� ��� ������ ������ �� �����
void readFile(std::ifstream &inputFile) {

}

int main(int argc, char *argv[]) {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::string inputPath = "input.txt";
    if (argc == 3 && strcmp(argv[1], "-f") == 0) {
        inputPath = argv[2];
    }

    std::ifstream inputFile(inputPath);
    if (!inputFile.is_open()) {
        std::cerr << "�� ������� ������� ���� ��� ������: " << inputPath << std::endl;
        return 1;
    }

    readFile(inputFile);
}
