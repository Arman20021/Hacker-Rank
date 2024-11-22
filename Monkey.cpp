#include <bits/stdc++.h>

using namespace std;

int main()
{
  char s[100001];

  while (cin.getline(s, 100001))
  {
    int a = strlen(s);
    sort(s, (s + a));
    for (int i = 0; i < a; i++)
    {
      s[i] != ' ' ? cout << s[i] : cout << "";
    }

    cout << endl;
  }
  return 0;
}
