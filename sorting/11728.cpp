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

int A{ 0 }, B{ 0 };
vector<int> seqA;
vector<int> seqB;

vector<int> merge(vector<int>& seq_1, vector<int> seq_2)
{
    vector<int> returnSeq;

    auto iter_1 = seq_1.begin();
    auto iter_2 = seq_2.begin();

    while (1)
    {
        if (iter_1 == seq_1.end() || iter_2 == seq_2.end())
        {
            break;
        }

        if (*iter_1 > *iter_2)
        {
            returnSeq.push_back(*iter_2);
            ++iter_2;
        }
        else
        {
            returnSeq.push_back(*iter_1);
            ++iter_1;
        }
    }

    if (iter_1 != seq_1.end())
    {
        while (iter_1 != seq_1.end())
        {
            returnSeq.push_back(*iter_1);
            ++iter_1;
        }
    }

    if (iter_2 != seq_2.end())
    {
        while (iter_2 != seq_2.end())
        {
            returnSeq.push_back(*iter_2);
            ++iter_2;
        }
    }

    return returnSeq;
}

vector<int> mergeSort(vector<int> seq)
{
    if (seq.size() < 2)
        return seq;

    int middle{ (int)seq.size() / 2 };

    auto leftSeq = mergeSort(vector<int>(seq.begin(), seq.begin() + middle));
    auto rightSeq = mergeSort(vector<int>(seq.begin() + middle, seq.end()));

    return merge(leftSeq, rightSeq);
}

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> A >> B;

    for (int i{ 0 }; i < A; ++i)
    {
        int input{ 0 };
        cin >> input;

        seqA.push_back(input);
    }

    for (int i{ 0 }; i < B; ++i)
    {
        int input{ 0 };
        cin >> input;

        seqB.push_back(input);
    }

    mergeSort(seqA);
    mergeSort(seqB);

    vector<int> result = merge(seqA, seqB);

    for (auto& it : result)
    {
        cout << it << " ";
    }

    return 0;
}