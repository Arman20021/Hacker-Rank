#include <bits/stdc++.h>
using namespace std;
int main()
{

    int t;
    cin >> t;
    while (t--)
    {
        int id1, id2, id3;
        string name1, name2, name3;
        char sec1, sec2, sec3;
        int mark1, mark2, mark3;

        cin >> id1>>name1>> sec1 >> mark1;
        cin >> id2>>name2>> sec2 >> mark2;
        cin >> id3>>name3>> sec3 >> mark3;

       int max_mark=max({mark1,mark2,mark3});
       if(max_mark==mark1)
       {
          cout<< id1<<" "<<name1<<" "<< sec1 <<" "<< mark1<<endl;
       }

       else if(max_mark==mark2)
       {
          cout<< id2<<" "<<name2<<" "<< sec2 <<" "<< mark2<<endl;
       }
        else
       {
          cout<< id3<<" "<<name3<<" "<< sec3 <<" "<< mark3<<endl;
       }


        

    }

    return 0;
}