#include <iostream>
#include <unordered_map>
#include <vector>


#define endl '\n'
using namespace std;

unordered_map<long long, long long> map;
vector<long long> inputArr(500005, 0);

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int N{ 0 }, M{ 0 };
    cin >> N;

    for (int i{ 0 }; i < N; ++i)
    {
        long long input{ 0 };
        cin >> input;

        if (map.find(input) == map.end())
            map.insert({ input,1 });
        else
            ++map[input];
    }

    cin >> M;

    for (int i{ 0 }; i < M; ++i)
    {
        cin >> inputArr[i];
    }

    for (int i{ 0 }; i < M; ++i)
    {
        cout << map[inputArr[i]] << ' ';
    }

    return 0;
}