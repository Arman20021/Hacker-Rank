#include <bits/stdc++.h>
using namespace std;
int main()
{
    string name;
    getline(cin, name);
    stringstream ss(name);
    string word;
    int count = 0;
    while (ss >> word)
    {

        if (word == "Jessica")
        {
            count++;
        }
    }
    count >=1 ? cout << "YES" : cout << "NO";

    return 0;
}