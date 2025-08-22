#include <iostream>
#include <unordered_set>

#define endl '\n'
using namespace std;

unordered_set<string> player;

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int N{ 0 };
    char Game;

    cin >> N >> Game;

    for (int i{ 0 }; i < N; ++i)
    {
        string input;
        cin >> input;
        player.insert(input);
    }

    switch (Game)
    {
    case 'Y':
        cout << player.size();
        break;
    case 'F':
        cout << player.size() / 2;
        break;
    case 'O':
        cout << player.size() / 3;
        break;
    }

    return 0;
}