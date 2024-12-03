#include <bits/stdc++.h>
using namespace std;
int main()
{

    int t;
    cin >> t;
    while (t--)
    {

        string a, b;
        cin >> a >> b;
       
        while (1)
        { int z = a.find(b);
            if (z != -1)
            {
                a.erase(z, b.size());
                a.insert(a.begin() + z, '#');
            }

            else
            {
                break;  
            }
           
        }
         cout << a << endl;
        }

    return 0;
}