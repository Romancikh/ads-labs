#include <string>
#include <fstream>
#include <iostream>
#include <windows.h>

// Функция для удаления лидирующих и конечных символов
std::string trim(const std::string &str) {
    size_t first = str.find_first_not_of(" \t\n\r"); // Находим первый значащий символ
    size_t last = str.find_last_not_of(" \t\n\r"); // Находим последний значащий символ
    if (first == std::string::npos) // На случай, если строка содержит только пробелы
        return "";
    return str.substr(first, (last - first + 1));
}

// Функция для чтения слова из файла
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

struct Group {
    std::string value;
    Group *next{};
    Group *nextFaculty{};
    Group *nextCourse{};
};

struct Faculty {
    std::string value;
    Faculty *next{};
    Group *groupHead{};
};

// Процедура для добавления нового факультета
void insertFaculty(Faculty *&facultyHead, const std::string &faculty) {
    Faculty *current = facultyHead;

    while (current != nullptr) {
        if (current->value == faculty) {
            return;
        }
        current = current->next;
    }

    auto *newFaculty = new Faculty;
    newFaculty->value = faculty;
    newFaculty->next = facultyHead;
    facultyHead = newFaculty;
}

// Функция для получения нужного узла по значению
Faculty *getCurrentFaculty(Faculty *facultyHead, const std::string &faculty) {
    Faculty *current = facultyHead;
    while (current != nullptr) {
        if (current->value == faculty) {
            return current;
        }
        current = current->next;
    }
    return current;
}

struct Course {
    std::string value;
    Course *next{};
    Group *groupHead{};
};

// Процедура для добавления нового курса
void insertCourse(Course *&courseHead, const std::string &course) {
    Course *current = courseHead;

    while (current != nullptr) {
        if (current->value == course) {
            return;
        }
        current = current->next;
    }

    auto *newCourse = new Course;
    newCourse->value = course;
    newCourse->next = courseHead;
    courseHead = newCourse;
}

// Функция для получения нужного узла по значению
Course *getCurrentCourse(Course *courseHead, const std::string &course) {
    Course *current = courseHead;
    while (current != nullptr) {
        if (current->value == course) {
            return current;
        }
        current = current->next;
    }
    return current;
}

// Процедура для добавления нового факультета
void insertGroup(Group *&groupHead, const std::string &group) {
    auto *newGroup = new Group;
    newGroup->value = group;
    newGroup->next = groupHead;
    groupHead = newGroup;
}

// Процедура для чтения и сохранения данных из файла
void readFile(const std::string &inputPath, Group *&groupHead, Faculty *&facultyHead, Course *&courseHead) {
    std::ifstream inputFile(inputPath);
    if (!inputFile.is_open()) {
        throw std::runtime_error("Не удалось открыть файл \"" + inputPath + "\" для чтения");
    }

    std::string group;
    std::string faculty;
    std::string course;

    while (true) {
        group = readWord(inputFile);
        faculty = readWord(inputFile);
        course = readWord(inputFile);

        if (group.empty() || faculty.empty() || course.empty()) {
            break; // Прекращаем чтение при пустых строках
        }

        insertFaculty(facultyHead, faculty);
        insertCourse(courseHead, course);
        insertGroup(groupHead, group);

        // Связываю группы одного факультета
        Faculty *facultyNode = getCurrentFaculty(facultyHead, faculty);
        groupHead->nextFaculty = facultyNode->groupHead;
        facultyNode->groupHead = groupHead;

        // Связываю группы одного курса
        Course *courseNode = getCurrentCourse(courseHead, course);
        groupHead->nextCourse = courseNode->groupHead;
        courseNode->groupHead = groupHead;
    }

    inputFile.close();
}

// Процедуры вывода
void printAllGroups(Group *groupHead) {
    Group *current = groupHead;
    while (current != nullptr) {
        std::cout << "Группа: " << current->value << std::endl;
        current = current->next;
    }
}

void printAllFaculties(Faculty *facultyHead) {
    Faculty *current = facultyHead;
    while (current != nullptr) {
        std::cout << "Факультет: " << current->value << std::endl;
        current = current->next;
    }
}

void printAllCourses(Course *courseHead) {
    Course *current = courseHead;
    while (current != nullptr) {
        std::cout << "Курс: " << current->value << std::endl;
        current = current->next;
    }
}

void printGroupsByFaculty(Faculty *facultyHead, const std::string &faculty) {
    Faculty *currentFaculty = facultyHead;

    while (currentFaculty != nullptr) {
        if (currentFaculty->value == faculty) {
            break;
        }
        currentFaculty = currentFaculty->next;
    }

    if (currentFaculty == nullptr) {
        std::cout << "Данные по факультету \"" << faculty << "\" не найдены" << std::endl;
        return;
    }

    std::cout << faculty << std::endl;
    Group *currentGroup = currentFaculty->groupHead;
    while (currentGroup != nullptr) {
        std::cout << "Группа: " << currentGroup->value << std::endl;
        currentGroup = currentGroup->nextFaculty;
    }
}

void printGroupsByCourse(Course *courseHead, const std::string &course) {
    Course *currentCourse = courseHead;

    while (currentCourse != nullptr) {
        if (currentCourse->value == course) {
            break;
        }
        currentCourse = currentCourse->next;
    }

    if (currentCourse == nullptr) {
        std::cout << "Данные по курсу \"" << course << "\" не найдены" << std::endl;
        return;
    }

    std::cout << course << std::endl;
    Group *currentGroup = currentCourse->groupHead;
    while (currentGroup != nullptr) {
        std::cout << "Группа: " << currentGroup->value << std::endl;
        currentGroup = currentGroup->nextCourse;
    }
}

void clear(Group *groupHead, Faculty *facultyHead, Course *courseHead) {
    while (groupHead != nullptr) {
        Group *temp = groupHead;
        groupHead = groupHead->next;
        delete temp;
    }

    while (facultyHead != nullptr) {
        Faculty *temp = facultyHead;
        facultyHead = facultyHead->next;
        delete temp;
    }

    while (courseHead != nullptr) {
        Course *temp = courseHead;
        courseHead = courseHead->next;
        delete temp;
    }
}

int readNumber(const std::string &prompt) {
    std::cout << prompt;
    int number;
    std::cin >> number;
    while (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(256, '\n');
        std::cout << "Неверный ввод. Пожалуйста, введите целое число: ";
        std::cin >> number;
    }
    return number;
}

std::string readString(const std::string &prompt) {
    std::cout << prompt;
    std::string str;
    std::cin.ignore();
    std::getline(std::cin, str);
    return str;
}

int main(int argc, char *argv[]) {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // Обработка аргументов командной строки
    std::string inputPath = "input.txt";
    if (argc == 3 && strcmp(argv[1], "-f") == 0) {
        inputPath = argv[2];
    }

    Group *groupHead = nullptr;
    Faculty *facultyHead = nullptr;
    Course *courseHead = nullptr;

    readFile(inputPath, groupHead, facultyHead, courseHead);

    int command = -1;
    while (command != 0) {
        std::cout << "Что вывести?" << "\n1. Все группы\n2. Группы по факультету\n3. Группы по курсу\n0. Выход"
                  << std::endl;
        command = readNumber("Введите номер команды: ");
        switch (command) {
            case 1:
                printAllGroups(groupHead);
                break;
            case 2: {
                std::cout << "Выберете факультет" << std::endl;
                printAllFaculties(facultyHead);
                std::string faculty = readString("Введите название факультета: ");
                printGroupsByFaculty(facultyHead, faculty);
                break;
            }
            case 3: {
                std::cout << "Выберете курс" << std::endl;
                printAllCourses(courseHead);
                std::string course = readString("Введите название курса: ");
                printGroupsByCourse(courseHead, course);
                break;
            }
            case 0:
                break;
            default:
                std::cerr << "Неправильная команда" << std::endl;
                break;
        }
    }

    clear(groupHead, facultyHead, courseHead);
}
