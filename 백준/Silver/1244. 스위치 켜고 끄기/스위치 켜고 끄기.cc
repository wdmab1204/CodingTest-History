#include <vector>
#include <iostream>

using namespace std;

int main(){
    int length;
    cin>>length;
    vector<int> v(length+1);
    for(int i=1; i<=length; i++)
    {
        cin>>v[i];
    }
    
    int peoplecnt;
    cin>>peoplecnt;
    while(peoplecnt-->0)
    {
        int gender, num;
        cin>>gender>>num;
        if(gender == 1)
        {
            int k = 1;
            while(num * k <= length)
            {
                v[num * k] = 1 - v[num*k];
                k++;
            }
        }
        else
        {
            v[num] = 1 - v[num];
            int i = num -1;
            int j = num +1;
            while(i >= 1 && j <=length)
            {
                if(v[i] != v[j])
                    break;
                
                v[i] = 1 - v[i];
                v[j] = 1 - v[j];
                i-=1;
                j+=1;
            }
        }
    }
    
    for(int i=1; i<=length; i++)
    {
        cout<<v[i]<<" ";
        if (i%20 == 0) cout<<endl;
    }
}