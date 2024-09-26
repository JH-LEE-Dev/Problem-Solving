#include <iostream>
#include <string>
#include <vector>
using namespace std;

//#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>

vector<string> arr(3);

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int index{ 0 }, delta{ 0 };

    for (int i = 0; i < 3; ++i)
    {
        cin >> arr[i];

        if (arr[i] != "Fizz" && arr[i] != "FizzBuzz" && arr[i] != "Buzz")
        {
            index = i;
            delta = 3 - i;
        }
    }

    int modulo = stoi(arr[index]) + delta;

    if (modulo % 3 == 0 && modulo % 5 == 0)
    {
        cout << "FizzBuzz";
    }

    if (modulo % 3 != 0 && modulo % 5 == 0)
    {
        cout << "Buzz";
    }

    if (modulo % 3 == 0 && modulo % 5 != 0)
    {
        cout << "Fizz";
    }

    if (modulo % 3 != 0 && modulo % 5 != 0)
    {
        cout << modulo;
    }

    //_CrtDumpMemoryLeaks();
    return 0;
}