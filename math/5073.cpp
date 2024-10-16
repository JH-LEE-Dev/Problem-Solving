#include <iostream>
#include <vector>
#include <cmath>

#define endl '\n'
using namespace std;

bool isValid(const int A, const int B, const int C)
{
    int maxValue = max(A, max(B, C));

    if (maxValue == A)
    {
        return A < (B + C);
    }

    if (maxValue == B)
    {
        return B < (A + C);
    }

    if (maxValue == C)
    {
        return C < (A + B);
    }
}

bool isScalene(const int A, const int B, const int C)
{
    return (A != B && A != C && B != C);
}

bool isEquilateral(const int A, const int B, const int C)
{
    return (A == B && A == C && B == C);
}

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int A{ 0 }, B{ 0 }, C{ 0 };

    while (1)
    {
        cin >> A >> B >> C;

        if (A == 0 && B == 0 && C == 0)
        {
            return 0;
        }

        if (!isValid(A, B, C))
        {
            cout << "Invalid" << endl;

            continue;
        }

        if (isScalene(A, B, C))
        {
            cout << "Scalene" << endl;

            continue;
        }

        if (isEquilateral(A, B, C))
        {
            cout << "Equilateral" << endl;

            continue;
        }

        cout << "Isosceles" << endl;
    }

    return 0;
}