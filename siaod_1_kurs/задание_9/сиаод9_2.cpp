#include <iostream>
using namespace std;
struct Node {
    char data;
    Node* next;
};
//Создает однонаправленный список длиной length, запрашивая у пользователя ввод символов для каждого узла.
Node* createList(int length) {
    if (length <= 0) return nullptr;

    Node* head = new Node();
    Node* current = head;
    cout << "Введите символы для списка: ";
    for (int i = 0; i < length; ++i) {
        char ch;
        cin >> ch;
        current->data = ch;
        if (i < length - 1) {
            current->next = new Node();
            current = current->next;
        }
        else {
            current->next = nullptr;
        }
    }
    return head;
}
//Использует два указателя: left и right. right двигается к концу списка, а left двигается навстречу right, когда стек разворачивается. Проверка осуществляется по парам элементов.
bool isPalindromeHelper(Node*& left, Node* right) {
    if (right == nullptr) return true;

    bool isPal = isPalindromeHelper(left, right->next);
    if (!isPal) return false;

    bool isCurrentPairEqual = (left->data == right->data);
    left = left->next;

    return isCurrentPairEqual;
}

bool isPalindrome(Node* head) {
    return isPalindromeHelper(head, head);
}

void deleteList(Node* head) {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    setlocale(LC_ALL, "Rus");
    int length;
    cout << "Введите длину списка: ";
    cin >> length;

    if (length % 2 != 0) {
        cerr << "Длина списка должна быть четной." << endl;
        return 1;
    }

    Node* head = createList(length);

    if (isPalindrome(head)) {
        cout << "Этот список является палиндромом." << endl;
    }
    else {
        cout << "Этот список не является палиндромом." << endl;
    }

    deleteList(head);
    return 0;
}
