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
    typesize rows{};
    typesize columns{};
    int** A = nullptr;
};
//создание массива в структуре
int createArray(MyStruct& s, typesize rows, typesize columns);
//заполнение структуры данных значениями
int fill(MyStruct& s, int temp);
//вывод массива на экран построчно
void print(MyStruct s);
//Дана квадратная матрица. Найти определитель данной матрицы методом Гаусса.
float determinant(MyStruct& s);
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
        << "4. Найти определитель данной матрицы методом Гаусса - determinant" << endl
        << "0. Выход" << endl << endl;
    int choice, pos, rows, columns, temp;
    while (true)
    {
        cout << "Выберете функцию программы = ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "Количество элементов в строке и в столбце = ";
            cin >> rows >> columns;
            createArray(A, rows, columns);
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
            cout << "Определитель равен = " << determinant(A) << endl;
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

int createArray(MyStruct& s, typesize rows, typesize columns)
{
    if (s.rows >= 0 && s.columns >= 0)
    {
        s.rows = rows;
        s.columns = columns;
        s.A = new int* [rows];
        for (int i = 0; i < rows; i++)
            s.A[i] = new int[columns];
        return 0;
    }
    cout << "Вы ввели не правильное значение size\n";
    return 1;
}
int fill(MyStruct& s, int temp)
{
    typesize temp1;
    if (s.rows < 0 || s.columns < 0)
    {
        cout << "В массиве нет ячеек";
        return 1;
    }
    if (temp == 0)
    {
        for (typesize i = 0; i < s.rows; i++)
        {
            for (typesize j = 0; j < s.columns; j++)
            {
                cout << "Введите значение для строки " << i << " и столбца " << j << " = " << endl;
                cin >> temp1;
                s.A[i][j] = temp1;
            }
        }
        return 0;
    }
    else if (temp == 1)
    {
        for (typesize i = 0; i < s.rows; i++)
        {
            for (typesize j = 0; j < s.columns; j++)
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
    if (s.rows < 0 || s.columns < 0)
        return;
    cout << "Множество чисел \n";
    for (typesize i = 0; i < s.rows; i++)
    {
        for (typesize j = 0; j < s.columns; j++)
        {
            cout << setw(5) << s.A[i][j] << " ";
        }
        cout << endl;
    }
}
float determinant(MyStruct& s)
{
    int columns{}, rows{};
    if (s.columns > s.rows)
    {
        columns = s.columns - (s.columns - s.rows);
        rows = s.rows;
    }
    else if (s.rows > s.columns)
    {
        rows = s.rows - (s.rows - s.columns);
        columns = s.columns;
    }
    else
    {
        rows = s.rows;
        columns = s.columns;
    }
    int** matrix{ new int* [rows] {} };
    for (typesize i = 0; i < rows; i++)
    {
        matrix[i] = new int[columns] {};
    }
    for (typesize i = 0; i < rows; i++)
    {
        for (typesize j = 0; j < columns; j++)
        {
            matrix[i][j] = s.A[i][j];
        }
    }
    double det = 1;
    int size = rows;
    for (int i = 0; i < size; ++i)
    {
        double mx = fabs(matrix[i][i]);
        int idx = i;
        for (int j = i + 1; j < size; ++j)
            if (mx < fabs(matrix[i][j])) mx = fabs(matrix[i][idx = j]);
        if (idx != i)
        {
            for (int j = i; j < size; ++j)
            {
                double t = matrix[j][i];
                matrix[j][i] = matrix[j][idx];
                matrix[j][idx] = t;
            }
            det = -det;
        }
        for (int k = i + 1; k < size; ++k)
        {
            double t = matrix[k][i] / matrix[i][i];

            for (int j = i; j < size; ++j)
                matrix[k][j] -= matrix[i][j] * t;
        }
    }
    for (int i = 0; i < size; ++i) det *= matrix[i][i];
    return det;
}

