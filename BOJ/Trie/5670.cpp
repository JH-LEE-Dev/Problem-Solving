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
#include <cmath>
#include <bitset>
#include <iomanip>

using namespace std;

#define endl '\n'
#define INF numeric_limits<int>::max()
#define MAX 100'001
#define ROOT 0

int Unused{ 0 };

struct Node
{
    bool End{ false };                      // �ܾ� �� ����
    int ChildCnt{ 0 };                      // �ڽ� ����
    vector<pair<char, int>> Nxt;            // (����, ���� ��� �ε���)
};

vector<Node> Trie;
vector<string> Arr;

int C2i(char C)
{
    return C - 'a';
}

void Insert(const string& Str)
{
    int Cur{ ROOT };

    for (auto& C : Str)
    {
        ++Trie[Cur].ChildCnt;

        int NxtIdx = -1;

        for (auto& P : Trie[Cur].Nxt)
        {
            if (P.first == C)
            {
                NxtIdx = P.second;
                break;
            }
        }

        if (NxtIdx == -1)
        {
            Trie.push_back(Node());
            NxtIdx = ++Unused;
            Trie[Cur].Nxt.push_back({ C, NxtIdx });
        }

        Cur = NxtIdx;
    }

    Trie[Cur].End = true;
}

int Find(const string& Str)
{
    int Cur{ ROOT };

    int Cnt{ 1 };// ù ���ڴ� �ݵ�� ������ ��

    for (const auto& C : Str)
    {
        //���� ������ �θ� ������ �ڽ� ���� 1���� ũ�ų�, �θ� ���ڰ� � �ܾ��� ������ ���ڶ��,
        if (Cur != ROOT && (Trie[Cur].End == true || Trie[Cur].Nxt.size() != 1))
            ++Cnt;

        //���� ���ڿ��� �Ļ��� �ܾ �ϳ� ���̶�� �ٷ� ����.
        if (Trie[Cur].ChildCnt == 1)
            return Cnt;

        // ���� ��� ã��
        for (auto& P : Trie[Cur].Nxt)
        {
            if (P.first == C)
            {
                Cur = P.second;
                break;
            }
        }
    }

    return Cnt;
}

void Input(int N)
{
    Arr.resize(N);

    for (int i = 0; i < N; ++i)
    {
        cin >> Arr[i];

        Insert(Arr[i]);
    }
}

void Clear()
{
    Arr.clear();
    Trie.clear();
    Trie.push_back(Node()); //ROOT ����.
    Unused = 0;
}

void Solve()
{
    int N{ 0 };

    while (cin >> N)
    {
        Clear();
        Input(N);

        int Result{ 0 };
        for (int i = 0; i < N; ++i)
        {
            Result += Find(Arr[i]);
        }

        cout << fixed << setprecision(2) << (float)Result / N << endl;
    }
}

int main()
{
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    Solve();

    return 0;
}