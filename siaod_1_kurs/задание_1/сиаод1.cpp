#include <iostream>
#include <vector>

using namespace std;
int main() 
{
    setlocale(LC_ALL, "Rus");
    int n;
    cout << "Введите количество чисел в последовательности: ";
    n = 5000;

    vector<int> posled(n);
    int start = 1;
    int end = 111111;
    int x = rand() % (end - start + 1) + start;
    for (int i = 0; i < n; i++) 
    {
        x = rand() % (end - start + 1) + start;
        posled[i] = x;
    }
    
    int originalNum = 0;
    int reverseNum = 0;
    int palindromeCount = 0;
    int temp;
    for (int i = 0; i < n; i++) 
    {
        originalNum = posled[i];
        reverseNum = 0;
        while (originalNum > 0)
        {
            temp = originalNum % 10;
            reverseNum = reverseNum * 10 + temp;
            originalNum = originalNum / 10;
        }
        if (posled[i]  == reverseNum)
        {
            palindromeCount++;
        }
    }
    
    cout << "posled = {";
    for (int i = 0; i < n; i++)
    {
        cout << posled[i] << ",";
    }
    cout << "}\n";
    cout << "palindromeCount: " << palindromeCount;
    cin >> n;
    return 0;
}