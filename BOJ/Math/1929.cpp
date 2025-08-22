#include <iostream>
#include <vector>

#define endl '\n'
using namespace std;

std::vector<bool> isPrime(1'000'005, true);

void sieveOfEratosthenes(int n)
{
    isPrime[0] = false;
    isPrime[1] = false;

    for (int i{ 0 }; i * i <= n; i++)
    {
        if (isPrime[i])
        {
            for (int j{ i * i }; j <= n; j += i)
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

    int N{ 0 }, M{ 0 };
    cin >> N >> M;

    sieveOfEratosthenes(M);

    for (int i{ N }; i <= M; ++i)
    {
        if (isPrime[i] == true)
            cout << i << endl;
    }

    return 0;
}