#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Str
{
    static const int INITIAL_CAPACITY = 10;
    int size;
    string strok;
    vector<string> wordArray;
};

// Функции управления строкой
// Метод для ввода строки
void inputString(Str& str);
// Метод для вывода строки
void print(Str& str);
// Метод для вывода массива слов
void printWordArray(Str& str);
// Метод для выделения слов
void selectWords(Str& str);
// Метод для удаления подстроки из строки
void deleteSubstring(string& str, int startIndex, int length);
// Метод для вставки подстроки в строку
void insertSubstring(string& str, int index, string& substring);
// Метод для выделения подстроки в тексте
string getSubstring(string& str, int startIndex, int length);
// меню
void menu(Str& str);
// Метод для вывода слов которые общие для двух предложений
void findCommonWords(Str& sentence1, Str& sentence2);

int main()
{
    setlocale(LC_ALL, "Rus");
    Str strok;
    inputString(strok);
    menu(strok);
    return 0;

}

void menu(Str& str) 
{
    char choice;
    int startIndex, length, index;
    string substring;
    Str sentence2;
    cout << "\nМеню:" << endl;
    cout << "1. Ввести строку" << endl;
    cout << "2. Вывести строку" << endl;
    cout << "3. Получить слова" << endl;
    cout << "4. Получить подстроку" << endl;
    cout << "5. Удалить подстроку" << endl;
    cout << "6. Вставить подстроку" << endl;
    cout << "7. Вывести массив слов" << endl;
    cout << "8. Общие слова для изначальной строки и произвошльной" << endl;
    cout << "0. Выйти" << endl;
    cout << "\nВыберите операцию: ";
    do 
    {       
        cin >> choice;
        cin.ignore(); // Очищаем буфер ввода от лишних символов
        switch (choice) {
        case '1':
            inputString(str);
            break;
        case '2':
            print(str);
            break;
        case '3':
            selectWords(str);
            break;
        case '4':
            cout << "Введите начальный индекс и длину подстроки: ";
            cin >> startIndex >> length;
            cout << "Подстрока: " << getSubstring(str.strok, startIndex, length) << endl;
            break;
        case '5':
            cout << "Введите начальный индекс и длину подстроки для удаления: ";
            cin >> startIndex >> length;
            deleteSubstring(str.strok, startIndex, length);
            cout << "Подстрока удалена." << endl;
            break;
        case '6':
            cout << "Введите индекс для вставки подстроки и саму подстроку: ";
            cin >> index >> substring;
            insertSubstring(str.strok, index, substring);
            cout << "Подстрока вставлена." << endl;
            break;
        case '7':
            printWordArray(str);
            break;
        case '8':           
            inputString(sentence2);
            selectWords(sentence2);
            selectWords(str);
            findCommonWords(str, sentence2);
            break;
        case '0':
            cout << "Программа завершена." << endl;
            break;
        default:
            cout << "Неверный выбор." << endl;
        }
    } while (choice != '0');
}


void inputString(Str& str) 
{
    cout << "Запишите вашу строку: ";
    getline(cin, str.strok);
}
void print(Str& str) 
{
    cout << "Строка: " << str.strok << endl;
}
void selectWords(Str& str) 
{
    size_t pos = 0;
    string token;
    while ((pos = str.strok.find(' ')) != string::npos) {
        token = str.strok.substr(0, pos);
        str.wordArray.push_back(token);
        str.strok.erase(0, pos + 1);
    }
    // Добавим последнее слово в wordArray
    str.wordArray.push_back(str.strok);
}
void printWordArray(Str& str) 
{
    cout << "Массив слов:" << endl;
    for (const auto& word : str.wordArray) {
        cout << word << " ";
    }
    cout << endl;
}
string getSubstring(string& str, int startIndex, int length) 
{
    if (startIndex < 0 || startIndex >= str.size() || length <= 0 || startIndex + length > str.size()) {
        cout << "Ошибка: неверные параметры для выделения подстроки." << endl;
        return "";
    }
    return str.substr(startIndex, length);
}
void deleteSubstring(string& str, int startIndex, int length) 
{
    if (startIndex < 0 || startIndex >= str.size() || length <= 0 || startIndex + length > str.size()) {
        cout << "Ошибка: неверные параметры для удаления подстроки." << endl;
        return;
    }
    str.erase(startIndex, length);
}
void insertSubstring(string& str, int index, string& substring) 
{
    if (index < 0 || index > str.size()) {
        cout << "Ошибка: неверный индекс для вставки подстроки." << endl;
        return;
    }
    str.insert(index, substring);
}
void findCommonWords(Str& sentence1,Str& sentence2) 
{
    cout << "Общие слова:" << endl;
    bool foundCommon = false;
    for (const auto& word1 : sentence1.wordArray) 
    {
        for (const auto& word2 : sentence2.wordArray) 
        {
            if (word1 == word2) 
            {
                cout << word1 << endl;
                foundCommon = true;
                break;
            }
        }
    }
    if (!foundCommon) 
    {
        cout << "Общих слов нет." << endl;
    }
}
