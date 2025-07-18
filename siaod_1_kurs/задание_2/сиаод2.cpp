#include <cstdlib>
#include <iostream>
#include <ctime> 
using namespace std;

struct MyStruct
{
    int n;
    static const int N = 100;
    int A[N];
    int temp1, temp2;
    int element;
   
    MyStruct(int n) : n{n}
    {
        if (n > N)
        {
            cout << "Не правильное значение n";
            this->n = -1;
        }
    }
    
    void create(int temp)
    {     
        if (n == -1)
        {
            cout << "Измените n в область допустимых значений" << endl;
            return;
        }
        if (temp == 0)
        {
            for (int i = 0; i < n; i++)
            {
                cout << "Введите значение " << i << endl;
                cin >> temp1;
                A[i] = temp1;
            }
            for (int i = n; i < N; i++)            
                A[i] = 0;
            
        }
        else if (temp == 1)
        {
            for (int i = 0; i < n; i++)                         
                A[i] = rand();
            for (int i = n; i < N; i++)            
                A[i] = 0;
            
            
        }
        else
            cout << "Вы ввели не правильное значение нужно 0 или 1" << endl;
    }
    
    void print()
    {
        if (n == -1)
        {
            cout << "Измените n в область допустимых значений" << endl;
            return;
        }
        for (int pos = 0; pos < n; pos++)
        {
            cout << "Элемент " << pos << " = " << A[pos] << endl;
        }
    }
    int deletePos(int pos)
    {
        if (n == -1)
        {
            cout << "Измените n в область допустимых значений" << endl;
            return -1;
        }
        if (pos <= n && pos >= 0)
        {
            for (int i = pos; i < n; i++)
            {
                A[i] = A[i+1];
            }
            n--;
            return 0;
        }
        else
        {
            cout << "нет заданной позиции" << endl;
            return -1;
        }
        
    }
    
    int addPos(int pos, int element)
    {       
        if (n == -1)
        {
            cout << "Измените n в область допустимых значений" << endl;
            return -1;
        }
        if (pos <= n && pos >= 0)
        {
            n++;
            if (n > N)
            {
                cout << "n массив выходит за область допустимых значений" << endl;
                return -1;
            }
            temp1 = A[pos];
            A[pos] = element;
            for (int i = pos+1; i < n; i++)
            {               
                temp2 = A[i];
                A[i] = temp1;
                temp1 = A[i + 1];
                temp1 = temp2;
            }
            return 0;
        }
        else
        {
            cout << "нет заданной позиции" << endl;
            return -1;
        }
    }
    
    int findElement(int temp2)
    {
        temp1 = 1;
        int t;
        if (n == -1)
        {
            cout << "Измените n в область допустимых значений" << endl;
            return -1;
        }
        for (int pos = 0; pos < n; pos++)
        {
            t = temp2;
            for (int i = 10; t != 0; i *= 10)
            {             
                temp1 = t % 10;
                if ((A[pos] % temp1) != 0)
                {
                    break;
                }
                if ((A[pos] % temp1 == 0) && (t < 10))
                    return pos;
                t = temp2 / i;
            }
        }
        return -1;
    }
    
    int addElement(int temp2, int element)
    {
        temp1 = 1;
        int t;
        if (n == -1)
        {
            cout << "Измените n в область допустимых значений" << endl;
            return -1;
        }
        for (int pos = 0; pos < n; pos++)
        {
            t = temp2;
            for (int i = 10; t != 0; i *= 10)
            {
                temp1 = t % 10;
                if ((A[pos] % temp1) != 0)
                {
                    break;
                }
                if ((A[pos] % temp1 == 0) && (t < 10))
                {
                    addPos(pos + 1, element);
                    return pos+1;
                }
                t = temp2 / i;
            }
        }
        return -1;
    }
    
    void deleteKrat3()
    {
        if (n == -1)
        {
            cout << "Измените n в область допустимых значений" << endl;
            return;
        }
        for (int pos = 0; pos < n; pos++)
        {
            if (A[pos] % 3 == 0)
                deletePos(pos);
        }
    }
};

int main()
{
    setlocale(LC_ALL, "Rus");
    MyStruct myStruct(20);
    myStruct.create(1);
    myStruct.deleteKrat3();



    myStruct.print();    
}
