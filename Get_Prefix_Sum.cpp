#include <bits/stdc++.h>
using namespace std;

int main()
{
  int n;
  cin >> n;

  vector<int> v(n + 1);
  for (int i = 1; i <= n; i++)
  {
    cin >> v[i];
  }

  vector<long long int> pre(n + 1);
  pre[1] = v[1];
  for (int i = 2; i <= n; i++)
  {
    pre[i] = pre[i - 1] + v[i];
  }

  sort(pre.begin() + 1, pre.end(), greater<long long int>());

  for (int i = 1; i <= n; i++)
  {
    cout << pre[i] << " ";
  }
  cout << endl;

  return 0;
}
