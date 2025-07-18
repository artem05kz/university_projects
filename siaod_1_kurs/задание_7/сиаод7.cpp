#include <iostream>
#include <unordered_map>
using namespace std;


// Структура для представления узла списка
struct Node {
    char data;  // Информационная часть узла
    int count;  // Количество вхождений символа
    Node* next; // Указатель на следующий узел
};

// Функция для вставки узла в начало списка
void insertNode(Node*& head, char value) {
    // Проверяем, существует ли уже узел с данным значением
    Node* current = head;
    while (current) {
        if (current->data == value) {
            // Увеличиваем количество вхождений и выходим
            current->count++;
            return;
        }
        current = current->next;
    }

    // Если символа еще нет в списке, добавляем его в конец
    Node* newNode = new Node{ value, 1, nullptr };
    if (!head) {
        head = newNode;
    }
    else {
        current = head;
        while (current->next) {
            current = current->next;
        }
        current->next = newNode;
    }
}

// Функция для вывода списка в консоль
void printNode(Node* head) {
    Node* current = head;
    while (current) {
        cout << current->data << "(" << current->count << ") ";
        current = current->next;
    }
    cout << endl;
}

// Функция для удаления узла с символом, который чаще всего встречается в списке
void deleteMost(Node*& head) {
    if (!head) {
        return; // Список пуст
    }

    // Используем хэш-таблицу для подсчета количества вхождений символов
    unordered_map<char, int> countMap;
    Node* current = head;
    while (current) {
        countMap[current->data]++;
        current = current->next;
    }

    // Находим символ с максимальным количеством вхождений
    char mostFrequent = head->data;
    int maxCount = countMap[head->data];
    current = head->next;
    while (current) {
        if (countMap[current->data] > maxCount) {
            mostFrequent = current->data;
            maxCount = countMap[current->data];
        }
        current = current->next;
    }

    // Удаляем узел с найденным символом
    Node* prev = nullptr;
    current = head;
    while (current) {
        if (current->data == mostFrequent) {
            if (prev) {
                prev->next = current->next;
            }
            else {
                head = current->next;
            }
            delete current;
            break;
        }
        prev = current;
        current = current->next;
    }
}

// Функция для перемещения первых m узлов в конец списка
void moveFirstToEnd(Node*& head, int m) {
    if (!head || m <= 0) {
        return; // Список пуст или некорректное значение m
    }

    Node* current = head;
    int count = 1;
    while (current->next && count < m) {
        current = current->next;
        count++;
    }

    if (count < m) {
        return; // В списке меньше m узлов
    }

    // Находим последний узел в текущем списке
    Node* lastNode = current;
    while (lastNode->next) {
        lastNode = lastNode->next;
    }

    // Перемещаем первые m узлов в конец списка
    lastNode->next = head;
    head = current->next;
    current->next = nullptr;
}

int main() {
    setlocale(LC_ALL, "Russian");
    
    Node* head = nullptr;

    // Вставляем символы в список
    insertNode(head, 'a');
    insertNode(head, 'b');
    insertNode(head, 'c');
    insertNode(head, 'b');
    insertNode(head, 'd');
    insertNode(head, 'c');
    insertNode(head, 'b');
    insertNode(head, 'a');
    insertNode(head, 'c');
    insertNode(head, 'd');
    insertNode(head, 'e');
    insertNode(head, 'f');
    // Выводим список в консоль
    cout << "Оригинальный список: ";
    printNode(head);

    // Удаляем узел с символом, который чаще всего встречается в списке
    deleteMost(head);
    cout << "Список после удаления наиболее часто встречающегося узла: ";
    printNode(head);

    // Перемещаем первые m узлов в конец списка
    int m = 3;
    moveFirstToEnd(head, m);
    cout << "Список после первого перемещения " << m << " узлы до конца: ";
    printNode(head);
    return 0;
}
