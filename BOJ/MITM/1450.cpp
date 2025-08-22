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
#include <string>

#define endl '\n'
#define INF numeric_limits<int>::max()
using namespace std;
int N{ 0 }, S{ 0 };
vector<int> arr;
vector<long long> sum_A;
vector<long long> sum_B;
long long result{ 0 };

void func(int idx, long long sum, vector<int> back, int backFlag)
{
    if (idx == back.size())
    {
        if (sum > S)
            return;

        if (backFlag)
            sum_A.push_back(sum);
        else
            sum_B.push_back(sum);

        return;
    }

    sum += back[idx];
    func(idx + 1, sum, back, backFlag);
    sum -= back[idx];
    func(idx + 1, sum, back, backFlag);
}

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> N >> S;

    for (int i{ 0 }; i < N; ++i)
    {
        int weight{ 0 };
        cin >> weight;
        arr.push_back(weight);
    }

    vector<int> arr_A(arr.begin(), arr.begin() + N / 2);
    vector<int> arr_B(arr.begin() + N / 2, arr.end());

    func(0, 0, arr_A, true);
    func(0, 0, arr_B, false);

    sort(sum_A.begin(), sum_A.end());
    sort(sum_B.begin(), sum_B.end());

    for (auto& it : sum_A)
    {
        result += upper_bound(sum_B.begin(), sum_B.end(), S - it) - sum_B.begin();
    }

    cout << result;

    return 0;
}