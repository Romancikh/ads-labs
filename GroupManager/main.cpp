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

Group *getFacultyHead(Group *head, const std::string &faculty) {
    Group *current = head;
    while (current != nullptr) {
        if (current->faculty == faculty) {
            return current;
        }
        current = current->next;
    }
    return current;
}

Group *getCourseHead(Group *head, const std::string &course) {
    Group *current = head;
    while (current != nullptr) {
        if (current->course == course) {
            return current;
        }
        current = current->next;
    }
    return current;
}

void insertGroup(Group *&head, const std::string &group, const std::string &faculty, const std::string &course) {
    Group *facultyHead = getFacultyHead(head, faculty);
    Group *courseHead = getCourseHead(head, course);
    auto *newGroup = new Group(group, faculty, course);
    newGroup->next = head;
    newGroup->nextFaculty = facultyHead;
    newGroup->nextCourse = courseHead;
    head = newGroup;
}

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



void printAllGroups(Group *head) {
    Group *current = head;
    while (current != nullptr) {
        std::cout << "������: " << current->group
                  << ", ���������: " << current->faculty
                  << ", ����: " << current->course
                  << std::endl;
        current = current->next;
    }
}

void printGroupsByFaculty(Group *head, const std::string &faculty) {
    std::cout << faculty << std::endl;
    Group *current = getFacultyHead(head, faculty);
    if (!current) {
        std::cout << "������ �� �������" << std::endl;
        return;
    }
    while (current != nullptr) {
        std::cout << "������: " << current->group
                  << ", ����: " << current->course
                  << std::endl;
        current = current->nextFaculty;
    }
}

void printGroupsByCourse(Group *head, const std::string &course) {
    std::cout << course << std::endl;
    Group *current = getCourseHead(head, course);
    if (!current) {
        std::cout << "������ �� �������" << std::endl;
        return;
    }
    while (current != nullptr) {
        std::cout << "������: " << current->group
                  << ", ���������: " << current->faculty
                  << std::endl;
        current = current->nextCourse;
    }
}

// ��������� ��� ������ ������ �� �����
void readFile(const std::string &inputPath, Group *&head) {
    std::ifstream inputFile(inputPath);
    if (!inputFile.is_open()) {
        throw std::runtime_error("�� ������� ������� ���� \"" + inputPath + "\" ��� ������");
    }

    std::string group;
    std::string faculty;
    std::string course;

    while (true) {
        group = readWord(inputFile);
        faculty = readWord(inputFile);
        course = readWord(inputFile);

        if (group.empty() || faculty.empty() || course.empty()) {
            break; // ���������� ������ ��� ������ �������
        }

        insertGroup(head, group, faculty, course);
    }

    inputFile.close();
}

int main(int argc, char *argv[]) {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // ��������� ���������� ��������� ������
    std::string inputPath = "input.txt";
    if (argc == 3 && strcmp(argv[1], "-f") == 0) {
        inputPath = argv[2];
    }

    Group *groupHead = nullptr;

    readFile(inputPath, groupHead);
}
