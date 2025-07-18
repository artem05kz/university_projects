#include <vector>
#include <iostream>
#include <cstdlib>
#include <iostream>
#include <stdlib.h>
#include <ctime> 
#include <iomanip>
using namespace std;
typedef unsigned int typesize;
struct MyStruct
{
    typesize rows{};
    typesize columns{2};
    vector<vector<int>> A;
};

//создание массива в структуре
int createArray(MyStruct& s, int rows);
//заполнение структуры данных значениями
int fill(MyStruct& s, int temp);
//вывод массива на экран построчно
void print(MyStruct s);
/*На плоскости задано множество точек с целочисленными координатами.
Необходимо найти количество отрезков, обладающих следующими
свойствами :
1) оба конца отрезка принадлежат заданному множеству;
2) ни один конец отрезка не лежит на осях координат;
3) отрезок пересекается ровно с одной осью координат.*/
int specOtrez(MyStruct& s);
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
        << "4. Поиск специальных отрезков - specOtrez" << endl
        << "0. Выход" << endl << endl;
    int choice, pos, size, temp;
    while (true)
    {
        cout << "Выберете функцию программы = ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "Количество отрезков = ";
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
            cout << "Количество специальных отрезков: " << specOtrez(A) << endl;
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
int createArray(MyStruct& s, int rows)
{
    if (rows < 0)
    {
        cout << "Вы ввели не правильное значение n";
        return 1;
    }
    s.rows = rows;
    s.A.reserve(rows);
    for (int i = 0; i < rows; ++i) 
    {
        s.A.push_back(vector<int>(s.columns));
    }
    return 0;
}
int fill(MyStruct& s, int temp)
{
    if (s.rows < 0 || s.columns < 0)
    {
        cout << "В массиве нет ячеек";
        return 1;
    }
    if (temp == 0)
    {
        for (typesize i = 0; i < s.rows; i++)
        {
                cout << "Введите значения для " << i+1 << " координат х и y точки = " << endl;
                cin >> s.A[i][0] >> s.A[i][1];
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
    cout << "Множество чисел \n";
    for (int i = 0; i < s.rows; i++) 
    {
        for (int j = 0; j < s.columns; j++) 
        {
            cout << setw(5) << (j == 0 ? "x:" : "y:") << s.A[i][j] << " ";
        }
        cout << endl;
    }
}
int specOtrez(MyStruct& s)
{
    int count = 0;
    int n = s.A.size();

    // Перебираем все возможные пары точек
    for (int i = 0; i < n; ++i) 
    {
        for (int j = i + 1; j < n; ++j) 
        {
            int x1 = s.A[i][0];
            int y1 = s.A[i][1];
            int x2 = s.A[j][0];
            int y2 = s.A[j][1];

            // Проверяем, что обе точки не лежат на осях координат
            if (x1 != 0 && y1 != 0 && x2 != 0 && y2 != 0) 
            {
                // Проверяем, пересекается ли отрезок ровно с одной осью координат
                if ((x1 > 0 && x2 < 0 && y1 > 0 && y2 > 0) || (x1 > 0 && x2 > 0 && y1 < 0 && y2 > 0) || (x1 > 0 && x2 < 0 && y1 < 0 && y2 < 0) || (x1 < 0 && x2 < 0 && y1 > 0 && y2 < 0))
                {
                    count++;
                }
            }
        }
    }

    return count;
}