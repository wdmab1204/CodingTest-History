#include <vector>
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

int main(){
    int arr[100][100] = {0,};
    
    int k, area = 0;
    cin>>k;
    while(k--)
    {
        int x,y;
        cin>>x>>y;
        for(int j=y; j<y+10; j++)
        {
            for(int i=x; i<x+10; i++)
            {
                arr[j][i]++;
                if(arr[j][i] == 1)
                    area++;
            }
        }
    }
    
    cout<<area;
}
