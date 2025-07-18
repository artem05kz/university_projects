#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <ctime> 
#include <iomanip>
using namespace std;
typedef unsigned int typesize;
typedef int typeitem;
struct MyStruct
{
    typesize size;
    int A[2][20];
};
//создание массива в структуре
int createArray(MyStruct& s, int size);
//заполнение структуры данных значениями
int fill(MyStruct& s, int temp);
//вывод массива на экран построчно
void print(MyStruct s);
//Дана квадратная матрица. Найти определитель данной матрицы методом Гаусса.
int matrix2X2(MyStruct& s, typesize pos);
// текстовое меню для управления программой
void menu(MyStruct& s);

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
        << "2. заполнение структуры данных значениями - fill" << endl
        << "3. вывод массива на экран построчно - print" << endl
        << "4. Найти определитель данной матрицы методом Гаусса - matrix2X2" << endl
        << "0. Выход" << endl << endl;
    int choice, pos, size, temp;
    while (true)
    {
        cout << "Выберете функцию программы = ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "Количество элементов в строке = ";
            cin >> size;          
            createArray(A, size);
            break;
        case 2:
            cout << "0 – для заполнения массива вручную\n1 – для заполнения массива с использование  датчика случайных чисел\n = ";
            cin >> temp;
            fill(A, temp);
            break;
        case 3:
            print(A);
            break;
        case 4:
            cout << "выбор первого элемента в матрице = ";
            cin >> pos;           
            cout << "Определитель равен = " << matrix2X2(A, pos) << endl;
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

int createArray(MyStruct& s, int size)
{
    if (size > 0 && size < 21)
    {
        s.size = size;
        return 0;
    }
    cout << "Вы ввели не правильное значение size\n";
    return 1;
}
int fill(MyStruct& s, int temp)
{
    typesize temp1;
    if (s.size < 0)
    {
        cout << "В массиве нет ячеек";
        return 1;
    }
    if (temp == 0)
    {
        for (typesize i = 0; i < 2; i++)
        {
            for (typesize j = 0; j < s.size; j++)
            {
                cout << "Введите значение для строки" << i << "и столбца" << j << " = ";
                cin >> temp1;
                s.A[i][j] = temp1;
            }       
        }
        return 0;
    }
    else if (temp == 1)
    {
        for (typesize i = 0; i < 2; i++)
        {
            for (typesize j = 0; j < s.size; j++)
            {
                s.A[i][j] = rand();
            }
        }
        return 0;
    }
    else
    {
        cout << "Вы ввели не правильное значение нужно 0 или 1" << endl;
        return 1;
    }
}
void print(MyStruct s)
{
    if (s.size < 0 && s.size > 20)
        return;
    cout << "Множество чисел \n";
    for (typesize i = 0; i < 2; i++)
    {
        for (typesize j = 0; j < s.size; j++)
        {
            cout << setw(5) << s.A[i][j] << " ";
        }  
        cout << endl;
    }
}
int matrix2X2(MyStruct& s, typesize pos)
{
    pos -= 1;
    if (pos > 19)
        return 1;
    int matrix[2][2];
    for (typesize i = 0; i < 2; i++)
    {
        for (typesize j = 0; j < 2; j++)
        {
            matrix[i][j] = s.A[i][j + pos];
        }
    }
    // Приведение матрицы к треугольному виду
    if (matrix[0][0] == 0)
    {
        swap(matrix[0][0], matrix[1][0]);
        swap(matrix[0][1], matrix[1][1]);
        return -1*(matrix[0][0] * matrix[1][1]);
    }
    else if(matrix[1][0] == 0)
        return matrix[0][0] * matrix[1][1];
    double delitel = (double)matrix[1][0] / (double)matrix[0][0];
    matrix[1][0] = (delitel * matrix[0][0])- matrix[1][0];
    return matrix[0][0] * matrix[1][1];
}