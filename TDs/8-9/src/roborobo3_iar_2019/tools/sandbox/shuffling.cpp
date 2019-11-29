#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    int a[10]={0,1,2,3,4,5,6,7,8,9};

    for (unsigned i = 0; i < 10; i++)
    {
        cout << a[i];
    }
    cout << endl;

    random_shuffle(&a[0],&a[10]);

    for (unsigned i = 0; i < 10; i++)
    {
        cout << a[i];
    }
    cout << endl;
}

