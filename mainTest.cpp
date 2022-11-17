#include "Vector.h"
using namespace std;

int main()
{
    vector<int> a;
    int n = 50;
    for (int i = 0; i < n; i ++)
    {
        a.push_back(i);
    }
    cout << a[30];
    a.insert(0,2);
    cout << a[0];
    a.clear();
    return 0;
}