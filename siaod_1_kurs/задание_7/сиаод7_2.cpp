#include <iostream>
#include <string>

using namespace std;

// Структура для представления узла списка областей знаний
struct KnowledgeAreaNode {
    string name;                    // Название области знания
    KnowledgeAreaNode* next;        // Указатель на следующий узел списка областей знаний
};

// Структура для представления узла двунаправленного списка книг
struct BookNode {
    int inventoryNumber;            // Инвентарный номер книги (ключ)
    string author;                  // Автор книги
    string title;                   // Название книги
    int year;                       // Год издания
    KnowledgeAreaNode* knowledgeAreas; // Указатель на список областей знаний
    BookNode* prev;                 // Указатель на предыдущий узел двунаправленного списка
    BookNode* next;                 // Указатель на следующий узел двунаправленного списка
};

// меню
void displayMenu(BookNode*& bookList);

// Функция для создания нового узла списка областей знаний
KnowledgeAreaNode* createKnowledgeAreaNode(const string& name) {
    return new KnowledgeAreaNode{ name, nullptr };
}

// Функция для создания нового узла двунаправленного списка книг
BookNode* createBookNode(int inventoryNumber, const string& author, const string& title, int year, KnowledgeAreaNode* knowledgeAreas) {
    return new BookNode{ inventoryNumber, author, title, year, knowledgeAreas, nullptr, nullptr };
}

// Функция для добавления новой области знания в список областей знаний книги
void addKnowledgeArea(BookNode* book, const string& areaName) {
    KnowledgeAreaNode* newNode = createKnowledgeAreaNode(areaName);
    if (!book->knowledgeAreas) {
        book->knowledgeAreas = newNode;
    }
    else {
        KnowledgeAreaNode* current = book->knowledgeAreas;
        while (current->next) {
            current = current->next;
        }
        current->next = newNode;
    }
}

// Функция для создания двунаправленного списка книг из n узлов
BookNode* createBookList(int n) {
    BookNode* head = nullptr;
    for (int i = 0; i < n; ++i) {
        int inventoryNumber;
        string author, title;
        int year;

        // Пример для демонстрации:
        inventoryNumber = i + 1;
        author = "Author" + to_string(i + 1);
        title = "Title" + to_string(i + 1);
        year = 2000 + i;

        // Создаем узел книги и добавляем его в список
        BookNode* newNode = createBookNode(inventoryNumber, author, title, year, nullptr);
        if (!head) {
            head = newNode;
        }
        else {
            BookNode* current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = newNode;
            newNode->prev = current;
        }
    }
    return head;
}

// Функция для вывода списка книг в двух направлениях
void printBookList(const BookNode* head) {
    const BookNode* current = head;
    cout << "Книги слева направо: ";
    while (current) {
        cout << current->inventoryNumber << " ";
        current = current->next;
    }
    cout << endl;

    // Выводим список в обратном порядке
    cout << "Книги справа налево: ";
    current = head;
    while (current->next) {
        current = current->next;
    }
    while (current) {
        cout << current->inventoryNumber << " ";
        current = current->prev;
    }
    cout << endl;
}

// Функция для поиска узла с заданным инвентарным номером книги
BookNode* findBookByInventoryNumber(const BookNode* head, int inventoryNumber) {
    const BookNode* current = head;
    while (current) {
        if (current->inventoryNumber == inventoryNumber) {
            return const_cast<BookNode*>(current);
        }
        current = current->next;
    }
    return nullptr;
}
// Функция для вывода информации о книге по её инвентарному номеру
void printBookInfoByInventoryNumber(const BookNode* head, int inventoryNumber) {
    BookNode* book = findBookByInventoryNumber(head, inventoryNumber);
    if (book) {
        cout << "=== Book Information ===" << endl;
        cout << "Inventory Number: " << book->inventoryNumber << endl;
        cout << "Author: " << book->author << endl;
        cout << "Title: " << book->title << endl;
        cout << "Year: " << book->year << endl;
    }
    else {
        cout << "Book not found" << endl;
    }
}
// Функция для вывода областей знаний и книг, которые к ним принадлежат
void printKnowledgeAreasAndBooks(const BookNode* head) {
    // Проходим по списку книг и выводим информацию о каждой книге и её областях знаний
    const BookNode* currentBook = head;
    while (currentBook) {
        cout << "=== Book Information ===" << endl;
        cout << "Title: " << currentBook->title << endl;
        cout << "Author: " << currentBook->author << endl;
        cout << "Year: " << currentBook->year << endl;
        cout << "Knowledge Areas: ";
        KnowledgeAreaNode* currentKnowledge = currentBook->knowledgeAreas;
        while (currentKnowledge) {
            cout << currentKnowledge->name << ", ";
            currentKnowledge = currentKnowledge->next;
        }
        cout << endl;
        currentBook = currentBook->next;
    }
}

// Функция для перемещения части списка, начиная с заданного узла, в начало списка
void movePartOfListToStart(BookNode*& head, int startInventoryNumber) {
    // Находим узел, с которого нужно начать перемещение
    BookNode* startNode = findBookByInventoryNumber(head, startInventoryNumber);
    if (!startNode || !startNode->next) {
        return; // Узел не найден или нет узлов после него
    }

    // Находим последний узел в текущем списке
    BookNode* lastNode = startNode;
    while (lastNode->next) {
        lastNode = lastNode->next;
    }

    // Перемещаем часть списка в начало
    lastNode->next = head;
    head->prev = lastNode;
    head = startNode->next;
    head->prev = nullptr;
    startNode->next = nullptr;
}

int main() {
    setlocale(LC_ALL, "Russian");
    // Создаем список книг
    int n = 5; // Количество книг
    BookNode* bookList = createBookList(n);

    // Добавляем 1 область знаний для книг для теста
    BookNode* currentBook = bookList;
    while (currentBook) {
        addKnowledgeArea(currentBook, "Область знаний 1");
        currentBook = currentBook->next;
    }

    while (true) {
        displayMenu(bookList);
    }

    return 0;
}

// Функция для вывода меню и обработки выбора пользователя
void displayMenu(BookNode*& bookList) {
    char choice;
    int inventoryNumber;
    cout << "===== Меню =====" << endl;
    cout << "1. Вывести список книг" << endl;
    cout << "2. Найти книгу по инвентарному номеру" << endl;
    cout << "3. Переместите часть списка в начало" << endl;
    cout << "4. Вывести информацию о книге по ее номеру" << endl;
    cout << "5. Вывести информацию о областях знаний" << endl;
    cout << "6. Выход" << endl;
    cout << "Введите свой выбор: ";
    cin >> choice;

    switch (choice) {
    case '1':
        cout << "=== Список книг ===" << endl;
        printBookList(bookList);
        break;
    case '2':
        cout << "Введите инвентарный номер для поиска: ";
        cin >> inventoryNumber;
        {
            BookNode* foundBook = findBookByInventoryNumber(bookList, inventoryNumber);
            if (foundBook) {
                cout << "Найденная книга: " << foundBook->title << endl;
            }
            else {
                cout << "Книга не найдена" << endl;
            }
        }
        break;
    case '3':
        cout << "Введите инвентарный номер, с которого вы начнете перемещение: ";
        cin >> inventoryNumber;
        movePartOfListToStart(bookList, inventoryNumber);
        cout << "Часть списка перемещена для успешного запуска" << endl;
        break;
    case '4':
        cout << "Введите инвентарный номер книги: ";
        cin >> inventoryNumber;
        printBookInfoByInventoryNumber(bookList, inventoryNumber);
        break;
    case '5':
        cout << "=== Области знаний и книги ===" << endl;
        printKnowledgeAreasAndBooks(bookList);
        break;
    case '6':
        cout << "выход из программы" << endl;
        exit(0);
    default:
        cout << "Неверный выбор" << endl;
        break;
    }
}


