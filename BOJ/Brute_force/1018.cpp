#include <iostream>
#include <string>
#include <limits>
using namespace std;

string W[8] = {
        "WBWBWBWB",
        "BWBWBWBW",
        "WBWBWBWB",
        "BWBWBWBW",
        "WBWBWBWB",
        "BWBWBWBW",
        "WBWBWBWB",
        "BWBWBWBW"
};

string B[8] = {
        "BWBWBWBW",
        "WBWBWBWB",
        "BWBWBWBW",
        "WBWBWBWB",
        "BWBWBWBW",
        "WBWBWBWB",
        "BWBWBWBW",
        "WBWBWBWB"
};

string board[50];

int wCounting(int x, int y)
{
    int count{ 0 };

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (board[x + i][y + j] != W[i][j])
                count++;
        }

    }

    return count;
}

int bCounting(int x, int y)
{
    int count{ 0 };

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (board[x + i][y + j] != B[i][j])
                count++;
        }

    }

    return count;
}

int main()
{
    int count{ 0 };
    int result = numeric_limits<int>::max();

    int N{ 0 }, M{ 0 };

    cin >> N >> M;

    for (int i = 0; i < N; i++)
        cin >> board[i];

    for (int i = 0; i + 8 <= N; i++)
    {
        for (int j = 0; j + 8 <= M; j++)
        {
            int tmp{ 0 };
            tmp = min(wCounting(i, j), bCounting(i, j));

            result = min(tmp, result);
        }
    }

    cout << result;

    return 0;
}