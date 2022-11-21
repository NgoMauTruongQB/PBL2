#include "Vector.h"
#include <iostream>
using namespace std;

int main()
{
    vector<int> a;
    int n = 10;
    for (int i = 0; i < n; i ++)
    {
        a.push_back(i);
    }
    for (int i = 0 ; i < a.size(); i++)
    {
        cout << a.at(i) << " ";
    }
    cout << endl;
    a.insert(2, 111);
    a.erase(5);
    a.clear();
    for (int i = 0 ; i < a.size(); i++)
    {
        cout << a.at(i) << " ";
    }
    cout << endl << a.data() << endl;
    cout << &a.at(0) << endl;
    return 0;
}