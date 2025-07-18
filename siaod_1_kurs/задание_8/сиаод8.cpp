#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Структура узла списка
struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

// Класс стека на основе списка
class Stack {
private:
    Node* top;

public:
    Stack() : top(nullptr) {}

    // Проверка на пустоту
    bool isEmpty() {
        return top == nullptr;
    }

    // Добавление элемента в стек
    void add(int val) {
        Node* newNode = new Node(val);
        newNode->next = top;
        top = newNode;
    }

    // Удаление элемента из стека
    void del() {
        if (isEmpty()) {
            cout << "Stack is empty. Cannot delete." << endl;
            return;
        }
        Node* temp = top;
        top = top->next;
        delete temp;
    }

    // Получение верхнего элемента стека без удаления
    int peek() {
        if (isEmpty()) {
            cout << "Stack is empty. Cannot peek." << endl;
            return -1;
        }
        return top->data;
    }
};

// Функция для вычисления значения выражения в постфиксной нотации
int evaluatePostfix(string expression) {
    Stack stack;
    for (char& c : expression) {
        if (isdigit(c)) {
            stack.add(c - '0');
        }
        else {
            int operand2 = stack.peek();
            stack.del();
            int operand1 = stack.peek();
            stack.del();
            switch (c) {
            case '+':
                stack.add(operand1 + operand2);
                break;
            case '-':
                stack.add(operand1 - operand2);
                break;
            case '*':
                stack.add(operand1 * operand2);
                break;
            case '/':
                stack.add(operand1 / operand2);
                break;
            }
        }
    }
    return stack.peek();
}

int main() {
    // Запуск тестирования
    string exp = "3333***";
    cout << "Expression: " << exp << endl;
    cout << "Result: " << evaluatePostfix(exp) << endl;
    return 0;
}
