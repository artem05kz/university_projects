#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <clocale>

using namespace std;

struct Str {
    static const int INITIAL_CAPACITY = 10;
    int capacity;
    int size;
    char strok[1000];
    char** wordArray;
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
void deleteSubstring(Str& str, int startIndex, int length);
// Метод для вставки подстроки в строку
void insertSubstring(Str& str, int index, const char* substring);
// Метод для выделения подстроки в тексте
char* getSubstring(const Str& str, int startIndex, int length);
// Метод, отвечающая за инициализацию всех начальных данных.
void initStr(Str& str);
// Метод, отвечающая за очистку памяти.
void freeStr(Str& str);
// меню
void menu(Str& str);
// Метод для вывода слов которые общие для двух предложений
void findCommonWords(Str& sentence1, Str& sentence2);

int main()
{
    setlocale(LC_ALL, "Rus");
    Str strok;
    inputString(strok);
    initStr(strok);
    menu(strok);
    return 0;
}
void menu(Str& str)
{
    char choice;
    printf("\nМеню:\n");
    printf("1. Ввести строку\n");
    printf("2. Вывести строку\n");
    printf("3. Получить слова\n");
    printf("4. Получить подстроку\n");
    printf("5. Удалить подстроку\n");
    printf("6. Вставить подстроку\n");
    printf("7. Вывести массив слов\n");
    printf("8. Общие слова для изначальной строки и произвошльной\n");
    printf("0. Выйти\n");
    do {
        printf("\nВыберите операцию: ");
        scanf(" %c", &choice);
        getchar();
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
        case '4': {
            int startIndex, length;
            printf("Введите начальный индекс и длину подстроки: ");
            scanf("%d %d", &startIndex, &length);
            getchar();
            char* substring = getSubstring(str, startIndex, length);
            if (substring != nullptr) {
                printf("Подстрока: %s\n", substring);
                free(substring); // освобождаем память, выделенную под подстроку
            }
            break;
        }
        case '5': {
            int startIndex, length;
            printf("Введите начальный индекс и длину подстроки для удаления: ");
            scanf("%d %d", &startIndex, &length);
            getchar();
            deleteSubstring(str, startIndex, length);
            printf("Подстрока удалена.\n");
            break;
        }
        case '6': {
            int index;
            char substring[100];
            printf("Введите индекс для вставки подстроки и саму подстроку: ");
            scanf("%d %s", &index, substring);
            getchar();
            insertSubstring(str, index, substring);
            printf("Подстрока вставлена.\n");
            break;
        }
        case '7':
            printWordArray(str);
            break;
        case '8':
            Str sentence2;
            inputString(sentence2);
            initStr(sentence2);
            findCommonWords(str, sentence2);
            break;
        case '0':
            printf("Программа завершена.\n");
            break;
        default:
            printf("Неверный выбор. Пожалуйста, попробуйте снова.\n");
        }
    } while (choice != '0');
}
void initStr(Str& str) 
{
    str.capacity = Str::INITIAL_CAPACITY;
    str.size = 0;
    str.wordArray = (char**)malloc(str.capacity * sizeof(char*));
}
void inputString(Str& str) 
{
    printf("Запишите вашу строку: ");
    fgets(str.strok, sizeof(str.strok), stdin);
    for (int i = 0; i < sizeof(str.strok); ++i) {
        if (str.strok[i] == '\n') {
            str.strok[i] = '\0';
            break;
        }
    }
}
void freeStr(Str& str) 
{
    for (int i = 0; i < str.size; i++) {
        free(str.wordArray[i]);
    }
    free(str.wordArray);
}

void print(Str& str)
{
    printf("Строка: %s\n", str.strok);
}
void selectWords(Str& str) 
{
    char* token = strtok(str.strok, " ");
    while (token != NULL) {
        if (str.size >= str.capacity) {
            // Увеличиваем емкость массива wordArray вдвое
            str.capacity *= 2;
            str.wordArray = (char**)realloc(str.wordArray, str.capacity * sizeof(char*));
        }
        // Выделение памяти для нового слова
        str.wordArray[str.size] = (char*)malloc((strlen(token) + 1) * sizeof(char));
        // Копирование слова в выделенную память с помощью 
        strcpy(str.wordArray[str.size], token);
        str.size++;
        // след слово
        token = strtok(NULL, " ");
    }
}
void deleteSubstring(Str& str, int startIndex, int length) 
{
    if (startIndex < 0 || startIndex >= str.size || length <= 0 || startIndex + length > str.size) {
        printf("Ошибка: неверные параметры для удаления подстроки.\n");
        return;
    }
    // Сдвигаем символы на место удаленной подстроки
    for (int i = startIndex + length; i <= str.size; ++i) {
        str.strok[i - length] = str.strok[i];
    }
    // Обновляем размер строки
    str.size -= length;
    str.strok[str.size] = '\0'; // Устанавливаем новый нуль
}
void insertSubstring(Str& str, int index, const char* substring) 
{
    if (index < 0 || index > str.size) {
        printf("Ошибка: неверный индекс для вставки подстроки.\n");
        return;
    }
    int substringLength = strlen(substring);
    // Проверяем, достаточно ли памяти для вставки подстроки
    if (str.size + substringLength >= sizeof(str.strok)) {
        printf("Ошибка: недостаточно места для вставки подстроки.\n");
        return;
    }
    // Сдвигаем символы, чтобы освободить место для вставки
    for (int i = str.size; i >= index; --i) {
        str.strok[i + substringLength] = str.strok[i];
    }
    // Копируем подстроку в строку
    strcpy(&str.strok[index], substring);
    // Обновляем размер строки
    str.size += substringLength;
}
char* getSubstring(const Str& str, int startIndex, int length) 
{
    if (startIndex < 0 || startIndex >= str.size || length <= 0 || startIndex + length > str.size) {
        printf("Ошибка: неверные параметры для выделения подстроки.\n");
        return nullptr;
    }

    // Выделяем память под подстроку
    char* substring = (char*)malloc((length + 1) * sizeof(char)); // +1 для нуль-терминатора
    if (substring == nullptr) {
        printf("Ошибка: не удалось выделить память для подстроки.\n");
        return nullptr;
    }

    // Копируем подстроку из исходной строки
    strncpy(substring, &str.strok[startIndex], length);
    substring[length] = '\0'; // Устанавливаем нуль-терминатор

    return substring;
}
void printWordArray(Str& str)
{
    for (int i = 0; i < str.size; ++i) {
        printf("\n");
        printf("%s", str.wordArray[i]);
        printf(" ");
    }
}

void findCommonWords(Str& sentence1,Str& sentence2) 
{
    printf("Общие слова:\n");
    bool foundCommon = false;
    selectWords(sentence1);
    selectWords(sentence2);
    // Проходим по всем словам первого предложения
    for (int i = 0; i < sentence1.size; ++i) {
        // Проходим по всем словам второго предложения
        for (int j = 0; j < sentence2.size; ++j) {
            // Если находим общее слово, выводим его
            if (strcmp(sentence1.wordArray[i], sentence2.wordArray[j]) == 0) {
                printf("%s\n", sentence1.wordArray[i]);
                foundCommon = true;
                break; // переходим к следующему слову первого предложения
            }
        }
    }
    if (!foundCommon) {
        printf("Общих слов нет.\n");
    }
}