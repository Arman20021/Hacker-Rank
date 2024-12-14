#include <bits/stdc++.h>

using namespace std;

int main()
{
    int N;
    cin >> N;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (i == j && i == (N - 1) / 2) {
                cout << "X"; // Center position
            } else if (i == j) {
                cout << "\\"; // Left diagonal
            } else if (i + j == N - 1) {
                cout << "/"; // Right diagonal
            } else {
                cout << " "; // Empty spaces
            }
        }
        cout << endl;
    }

    return 0;
}
