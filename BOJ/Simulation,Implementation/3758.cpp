#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

#define endl '\n'
using namespace std;

struct Team
{
    int ID{ 0 };
    int score{ 0 };
    int submitCount{ 0 };
    int lastSubmit{ 0 };
};

//vector<int> problem(10'005, 0);
//vector<int> lastSubmit(105, 0);
//vector<int> submitCount(100, 0);
//vector<vector<int>> teamScore(105, vector<int>(10'005, 0));
//vector<int> teamTotalScore(105, 0);
//vector<Team> result(105);

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int T{ 0 };
    int n{ 0 }, k{ 0 }, t{ 0 }, m{ 0 };

    cin >> T;

    for (int i{ 0 }; i < T; ++i)
    {
        vector<int> problem(10'005, 0);
        vector<int> lastSubmit(105, 0);
        vector<int> submitCount(100, 0);
        vector<vector<int>> teamScore(105, vector<int>(10'005, 0));
        vector<int> teamTotalScore(105, 0);
        vector<Team> result(105);

        cin >> n >> k >> t >> m;
        int order{ 0 };

        for (int j{ 0 }; j < m; ++j)
        {
            int teamID{ 0 }, problemID{ 0 }, score{ 0 };
            cin >> teamID >> problemID >> score;
            lastSubmit[teamID] = order;

            if (teamScore[teamID][problemID] < score)
            {
                teamTotalScore[teamID] -= teamScore[teamID][problemID];
                teamTotalScore[teamID] += score;
                teamScore[teamID][problemID] = score;
            }

            ++order;
            ++submitCount[teamID];
        }

        for (int j{ 1 }; j <= n; ++j)
        {
            Team temp;
            temp.ID = j;
            temp.lastSubmit = lastSubmit[j];
            temp.score = teamTotalScore[j];
            temp.submitCount = submitCount[j];
            result[j] = temp;
        }

        Team Target{ result[t] };
        int TargetOrder{ 1 };
        for (int j{ 1 }; j <= n; ++j)
        {
            if (result[j].ID == t)
                continue;

            if (result[j].score != Target.score)
            {
                if (result[j].score > Target.score)
                {
                    ++TargetOrder;
                }
            }
            else
            {
                if (result[j].submitCount != Target.submitCount)
                {
                    if (result[j].submitCount < Target.submitCount)
                    {
                        ++TargetOrder;
                    }
                }
                else
                {
                    if (result[j].lastSubmit < Target.lastSubmit)
                    {
                        ++TargetOrder;
                    }
                }
            }
        }

        cout << TargetOrder << endl;
    }

    return 0;
}