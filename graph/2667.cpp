#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>

#define endl '\n'
using namespace std;

int N{ 0 };
vector<vector<int>> table(26, vector<int>(26, 0));
vector<vector<bool>> visited(26, vector<bool>(26, 0));
vector<int> counting;
set<pair<int, int>> house;

void dfs()
{
    if (house.empty())
        return;

    queue<pair<int, int>> myQueue;
    myQueue.push(*house.begin());

    int Count{ 0 };

    while (!myQueue.empty())
    {
        pair<int, int> current_vertex = myQueue.front();
        myQueue.pop();

        if (visited[current_vertex.first][current_vertex.second] == false)
        {
            ++Count;

            house.erase(pair<int, int>(current_vertex.first, current_vertex.second));

            if (current_vertex.first - 1 >= 0)
            {
                if (visited[current_vertex.first - 1][current_vertex.second] == false && table[current_vertex.first - 1][current_vertex.second] == 1)
                    myQueue.push(pair<int, int>(current_vertex.first - 1, current_vertex.second));
            }

            if (current_vertex.second - 1 >= 0)
            {
                if (visited[current_vertex.first][current_vertex.second - 1] == false && table[current_vertex.first][current_vertex.second - 1] == 1)
                    myQueue.push(pair<int, int>(current_vertex.first, current_vertex.second - 1));
            }

            if (current_vertex.first + 1 >= 0)
            {
                if (visited[current_vertex.first + 1][current_vertex.second] == false && table[current_vertex.first + 1][current_vertex.second] == 1)
                    myQueue.push(pair<int, int>(current_vertex.first + 1, current_vertex.second));
            }

            if (current_vertex.second + 1 >= 0)
            {
                if (visited[current_vertex.first][current_vertex.second + 1] == false && table[current_vertex.first][current_vertex.second + 1] == 1)
                    myQueue.push(pair<int, int>(current_vertex.first, current_vertex.second + 1));
            }

            visited[current_vertex.first][current_vertex.second] = true;

            if (house.empty())
            {
                break;
            }
        }
    }

    counting.push_back(Count);
}

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> N;

    string input;

    for (int i{ 0 }; i < N; ++i)
    {
        cin >> input;

        for (int j{ 0 }; j < N; ++j)
        {
            table[i][j] = (int)input[j] - 48;
            if (table[i][j] == 1)
            {
                house.insert(pair<int, int>(i, j));
            }
        }
    }

    while (!house.empty())
    {
        dfs();
    }

    sort(counting.begin(), counting.end());

    cout << counting.size() << endl;
    for (auto& it : counting)
    {
        cout << it << endl;
    }

    return 0;
}