#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <map>
#include <algorithm>
#include <limits>
#include <tuple>

#define endl '\n'
#define INF numeric_limits<int>::max()
using namespace std;

vector<bool> isPrime(4'000'005, true);

void primeCheck(int num)
{
    isPrime[0] = false;
    isPrime[1] = false;

    for (int i{ 2 }; i * i <= num; ++i)
    {
        if (isPrime[i] == true)
        {
            for (int j = i * i; j <= num; j += i)
            {
                isPrime[j] = false;
            }
        }
    }
}

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int N{ 0 };
    cin >> N;
    primeCheck(N);

    int left{ 2 }, right{ 2 };

    int sum{ right }, count{ 0 };

    while (left <= right)
    {
        if (sum < N)
        {
            ++right;
            while (isPrime[right] == false)
            {
                ++right;
            }

            sum += right;
        }
        else
        {
            if (sum == N)
            {
                ++count;
                sum -= left;

                ++left;
                while (isPrime[left] == false)
                {
                    ++left;
                }
            }
            else
            {
                sum -= left;
                ++left;
                while (isPrime[left] == false)
                {
                    ++left;
                }
            }
        }
    }

    cout << count;

    return 0;
}