#include <iostream>
#include <vector>
#include <unordered_set>

#define endl '\n'
using namespace std;

unordered_set<string> keyword(200'005);
unordered_set<string> keyword_check(200'005);
vector<string> word(200'005);

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int N{ 0 }, M{ 0 };
    cin >> N >> M;

    for (int i{ 0 }; i < N; ++i)
    {
        string input;
        cin >> input;
        keyword.insert(input);
        keyword_check.insert(input);
    }

    for (int i{ 0 }; i < M; ++i)
    {
        cin >> word[i];
        vector<string> tempKeyword;

        string temp;

        for (int j{ 0 }; j < word[i].size(); ++j)
        {
            if (word[i][j] == ',')
            {
                if (keyword.find(temp) != keyword.end())
                {
                    keyword.erase(temp);
                }

                temp = "";
            }
            else
            {
                temp += word[i][j];
            }
        }

        if (keyword.find(temp) != keyword.end())
        {
            keyword.erase(temp);
        }

        cout << keyword.size() << endl;
    }

    return 0;
}