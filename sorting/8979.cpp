#include <iostream>
#include <vector>
#include <algorithm>

#define endl '\n'
using namespace std;

struct Medals
{
    int m_gold{ 0 };
    int m_silver{ 0 };
    int m_bronze{ 0 };
    int m_number{ 0 };
};

vector<Medals> nation(1005);

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int N{ 0 }, K{ 0 }, order{ 1 };
    cin >> N >> K;

    for (int i{ 0 }; i < N; ++i)
    {
        int number{ 0 };
        cin >> number;

        Medals input;
        cin >> input.m_gold >> input.m_silver >> input.m_bronze;
        input.m_number = number;
        nation[number - 1] = input;
    }

    for (int i{ 0 }; i < N; ++i)
    {
        if (nation[i].m_number == K)
            continue;

        if (nation[i].m_gold != nation[K - 1].m_gold)
        {
            if (nation[i].m_gold > nation[K - 1].m_gold)
            {
                ++order;
            }
        }
        else
        {
            if (nation[i].m_silver != nation[K - 1].m_silver)
            {
                if (nation[i].m_silver > nation[K - 1].m_silver)
                {
                    ++order;
                }
            }
            else
            {
                if (nation[i].m_bronze != nation[K - 1].m_bronze)
                {
                    if (nation[i].m_bronze > nation[K - 1].m_bronze)
                    {
                        ++order;
                    }
                }
            }
        }
    }

    cout << order;

    return 0;
}