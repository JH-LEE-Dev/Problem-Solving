#include <iostream>
#include <vector>

#define endl '\n'
using namespace std;

vector<int> titleScore(100'005);
vector<string> titleName(100'005);
vector<int> scores(100'005, 0);

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int N{ 0 }, M{ 0 };
    cin >> N >> M;

    for (int i{ 0 }; i < N; ++i)
    {
        int score{ 0 };
        string input;
        cin >> input >> score;

        titleScore[i] = score;
        titleName[i] = input;
    }

    for (int i{ 0 }; i < M; ++i)
    {
        cin >> scores[i];

        cout << titleName[distance(titleScore.begin(), lower_bound(titleScore.begin(), titleScore.begin() + N, scores[i]))] << endl;
    }

    return 0;
}