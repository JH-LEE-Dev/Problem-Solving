#include <iostream>
#include <vector>
#include <limits>

#define endl '\n'
using namespace std;

vector<int> cnt;
vector<int> orderCnt(205, 0);
vector<int> score(205, numeric_limits<int>::max());
vector<int> game(1005, 0);
vector<int> fifth_order(205, 0);

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int T{ 0 }, N{ 0 };
    cin >> T;

    for (int i{ 0 }; i < T; ++i)
    {
        cnt = vector<int>(205, 0);
        score = vector<int>(205, numeric_limits<int>::max());
        fifth_order = vector<int>(205, 0);
        orderCnt = vector<int>(205, 0);

        cin >> N;

        for (int j{ 1 }; j <= N; ++j)
        {
            cin >> game[j];
            ++cnt[game[j]];
        }

        int order{ 1 };

        for (int j{ 1 }; j <= N; ++j)
        {
            if (cnt[game[j]] == 6)
            {
                ++orderCnt[game[j]];
                if (orderCnt[game[j]] == 5)
                {
                    fifth_order[game[j]] = order;
                }
                else if (orderCnt[game[j]] <= 5)
                {
                    if (score[game[j]] == numeric_limits<int>::max())
                    {
                        score[game[j]] = 0;
                        score[game[j]] += order;
                    }
                    else
                    {
                        score[game[j]] += order;
                    }

                }

                ++order;
            }
        }

        int minScore{ numeric_limits<int>::max() };
        int winTeam{ 1 };

        for (int j{ 1 }; j < 201; ++j)
        {
            if (minScore > score[j])
            {
                minScore = score[j];
                winTeam = j;
            }
            else if (minScore == score[j])
            {
                if (fifth_order[winTeam] > fifth_order[j])
                {
                    winTeam = j;
                }
            }
        }

        cout << winTeam << endl;
    }

    return 0;
}