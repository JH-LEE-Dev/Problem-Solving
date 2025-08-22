#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int N{ 0 }, count{ 1 }, result{ 666 };
    cin >> N;

    while (count != N)
    {
        ++result;
        if (to_string(result).find("666") != std::string::npos)
        {
            ++count;
        }
    }
    cout << result;

    return 0;
}