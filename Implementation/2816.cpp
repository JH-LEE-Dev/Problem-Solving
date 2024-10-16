#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

#define endl '\n'
using namespace std;

vector<string> channel(105, "");
string order{ "" };
int kbs1{ 0 }, kbs2{ 0 };

void rearrangeKBS1()
{
    for (int i{ 0 }; i < kbs1; ++i)
    {
        order += '1';
    }

    while (kbs1 != 0)
    {
        order += '4';

        if (channel[kbs1 - 1] == "KBS2")
        {
            kbs2 += 1;
        }

        swap(channel[kbs1], channel[kbs1 - 1]);


        kbs1 -= 1;
    }
}

void rearrangeKBS2()
{
    for (int i{ 0 }; i < kbs2; ++i)
    {
        order += '1';
    }

    while (kbs2 != 1)
    {
        order += '4';

        swap(channel[kbs2], channel[kbs2 - 1]);

        kbs2 -= 1;
    }
}

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int N{ 0 };

    cin >> N;

    for (int i{ 0 }; i < N; ++i)
    {
        cin >> channel[i];

        if (channel[i] == "KBS1")
        {
            kbs1 = i;
        }

        if (channel[i] == "KBS2")
        {
            kbs2 = i;
        }
    }

    rearrangeKBS1();
    rearrangeKBS2();

    cout << order;

    return 0;
}