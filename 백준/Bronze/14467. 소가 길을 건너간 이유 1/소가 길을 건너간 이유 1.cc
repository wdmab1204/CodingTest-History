#include <vector>
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

int main(){
    int k, result = 0;
    cin >> k;
    unordered_map<int,int> map;
    while(k--)
    {
        int n, dir;
        cin>>n>>dir;
        if(map.find(n) == map.end())
            map[n] = dir;
        else
        {
            if(map[n] != dir)
                result++;
            map[n]=dir;
        }
    }
    cout<<result;
}
