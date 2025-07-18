#include <vector>
#include <iostream>
#include <cstdlib>
#include <iostream>
#include <stdlib.h>
#include <ctime> 
using namespace std;
typedef unsigned int typesize;
struct MyStruct
{
    typesize size;
    int* A;
};
//создание массива в структуре
void createArray(MyStruct& s, int n);
//удаление массива в структуре
void deleteArray(MyStruct& s);
//заполнение структуры данных значениями
void fill(MyStruct& s, int temp);
//вывод структуры в консоль
void print(MyStruct s);
//удалить элемент в заданной позиции
int deletePos(MyStruct& s, typesize pos);
//вставить элемент в заданную позицию
int addPos(MyStruct& s, typesize pos, int element);
//Найти позицию элемента массива значение которого делится на каждую из цифр числа*
int findElement(MyStruct& s, int temp2);
//Вставить в массив новый элемент после элемента, значение	которого делится на каждую цифру значения
int addElement(MyStruct& s, int temp2, int element);
//Удалить из массива все элементы, кратные трем
void deleteKrat3(MyStruct& s);
//Сформировать новый массив из чисел исходного, которые делятся на каждую цифру числа.
void newArray(MyStruct& s, int temp2);
// текстовое меню для управления программой
void menu(MyStruct& A);

int main()
{
    setlocale(LC_ALL, "Rus");
    MyStruct A;
    menu(A);
}
void menu(MyStruct& A)
{
    cout << "Доступные функции программы" << endl
        << "1. создание массива в структуре - createArray" << endl
        << "2. удаление массива в структуре - deleteArray" << endl
        << "3. заполнение структуры данных значениями - fill" << endl
        << "4. вывод структуры в консоль - print" << endl
        << "5. удалить элемент в заданной позиции - deletePos" << endl
        << "6. вставить элемент в заданную позицию - addPos" << endl
        << "7. Найти позицию элемента массива значение которого делится на каждую из цифр числа - findElement" << endl
        << "8. Вставить в массив новый элемент после элемента, значение которого делится на каждую цифру значения - addElement" << endl
        << "9. Удалить из массива все элементы, кратные трем - deleteKrat3" << endl
        << "10. Сформировать новый массив из чисел исходного, которые делятся на каждую цифру числа - newArray" << endl
        << "0. Выход" << endl << endl;
    int choice, pos, element;  
    while (true)
    {
        cout << "Выберете функцию программы = ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "Количество элементов в массиве = ";
            cin >> element;
            createArray(A, element);
            break;
        case 2:
            deleteArray(A);
            break;
        case 3:
            cout << "Введите 0 или 1 для выбора метода заполнения вручную или с помощью случайных чисел = ";
            cin >> element;
            fill(A, element);
            break;
        case 4:
            print(A);
            break;
        case 5:
            cout << "Введите позицию элемента = ";
            cin >> pos;
            deletePos(A, pos);
            break;
        case 6:
            cout << "Введите позицию элемента = ";
            cin >> pos;
            cout << "Введите элемент который надо вставить = ";
            cin >> element;
            addPos(A, pos, element);
            break;
        case 7:
            cout << "Введите число на которое надо делить = ";
            cin >> element;
            findElement(A, element);
            break;
        case 8:
            cout << "Введите какой элемент нужно вставить = ";
            cin >> pos;
            cout << "Введите число на которое надо делить = ";
            cin >> element;
            addElement(A, pos, element);
            break;
        case 9:
            deleteKrat3(A);
            break;
        case 10:
            cout << "Введите число на которое надо делить = ";
            cin >> element;
            newArray(A, element);
            break;
        case 0:
            cout << "Выход" << endl << endl;
            return;
        default:
            cout << "Не правильный выбор" << endl;
            break;
        }
    }
    
}

void createArray(MyStruct& s, int n)
{
    s.size = n;
    if (s.size < 0)
    {
        cout << "Вы ввели не правильное значение n";
        return;
    }
    s.A = (int*)malloc(s.size * sizeof(int));
}
void deleteArray(MyStruct& s)
{
    free(s.A);
}
void fill(MyStruct& s, int temp)
{
    typesize temp1;
    if(s.size < 0)
    {
        cout << "В массиве нет ячеек";
        return;
    }
    if (temp == 0)
    {
        for (typesize i = 0; i < s.size; i++)
        {
            cout << "Введите значение " << i << endl;
            cin >> temp1;
            s.A[i] = temp1;
        }
    }
    else if (temp == 1)
    {
        for (typesize i = 0; i < s.size; i++)
            s.A[i] = rand();

    }
    else
    {
        cout << "Вы ввели не правильное значение нужно 0 или 1" << endl;
        return;
    }
}
void print(MyStruct s)
{
    cout << "Множество чисел \n";
    for (typesize pos = 0; pos < s.size; pos++)
    {
        cout << "Элемент " << pos << " = " << s.A[pos] << endl;
    }
}
int deletePos(MyStruct& s, typesize pos)
{
    if (pos <= s.size && pos >= 0)
    {
        for (typesize i = pos; i < s.size; i++)
        {
            s.A[i] = s.A[i + 1];
        }
        s.size--;
        s.A = (int*)realloc(s.A, s.size * sizeof(int));
        return 0;
    }
    else
    {
        cout << "нет заданной позиции" << endl;
        return -1;
    }
}
int addPos(MyStruct& s, typesize pos, int element)
{
    if (pos <= s.size && pos >= 0)
    {
        s.size++;
        s.A = (int*)realloc(s.A, s.size * sizeof(int));
        for (int i = s.size; i > pos; i--)
        {
            s.A[i] = s.A[i-1];
        }
        s.A[pos] = element;
        return 0;
    }
    else
    {
        cout << "нет заданной позиции" << endl;
        return -1;
    }
}
int findElement(MyStruct& s, int temp2)
{
    int temp1 = 1;
    int t;
    for (int pos = 0; pos < s.size; pos++)
    {
        t = temp2;
        for (int i = 10; t != 0; i *= 10)
        {
            temp1 = t % 10;
            if ((s.A[pos] % temp1) != 0)
            {
                break;
            }
            if ((s.A[pos] % temp1 == 0) && (t < 10))
                return pos;
            t = temp2 / i;
        }
    }
    return -1;
}
int addElement(MyStruct& s, int temp2, int element)
{
    int temp1 = 1;
    int t;
    for (int pos = 0; pos < s.size; pos++)
    {
        t = temp2;
        for (int i = 10; t != 0; i *= 10)
        {
            temp1 = t % 10;
            if ((s.A[pos] % temp1) != 0)
            {
                break;
            }
            if ((s.A[pos] % temp1 == 0) && (t < 10))
            {
                addPos(s, pos + 1, element);
                return pos + 1;
            }
            t = temp2 / i;
        }
    }
    return -1;
}
void deleteKrat3(MyStruct& s)
{
    for (int pos = 0; pos < s.size; pos++)
    {
        if (s.A[pos] % 3 == 0)
            deletePos(s, pos);
    }
}
void newArray(MyStruct& s, int temp2)
{
    int pos;
    int count = 0;
    int* B = (int*)malloc(s.size * sizeof(int));
    for (int i = 0; i < s.size; i++)
    {
        pos = findElement(s, temp2);
        if (pos != -1)
        {
            B[count] = s.A[pos];
            count++;
            deletePos(s, pos);
        }
    }
    s.size = count;
    free((void*)s.A);
    B = (int*)realloc(B, s.size * sizeof(int));
    s.A = B;
}
