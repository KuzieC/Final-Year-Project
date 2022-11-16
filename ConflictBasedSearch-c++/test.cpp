#include <iostream>
#include <algorithm>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

void prin(vector<vector<int>> &inter)
{
    for (auto i : inter)
    {
        for (auto j : i)
        {
            cout << j;
        }
        cout << " ";
    }
    cout << endl;
}

vector<vector<int>> merge1(vector<vector<int>> &intervals)
{
    int k = intervals.size();
    bool changed = false;
    vector<vector<int>> ans;
    ans.push_back(intervals.front());
    for (int i = 1; i < k; i++)
    {
        vector<int> &temp1 = ans[ans.size()-1];
        vector<int> &temp2 = intervals[i];
        if (temp2.front() > temp1.back())
        {
            ans.push_back(intervals[i]);
        }
        else{
            temp1.back() = max(temp1.back(), temp2.back());
        }
    }
    return intervals;
}
void mm (){
    unordered_multimap<string,int> umm2({ { "apple", 1 },
          { "ball", 2 },
          { "apple", 10 },
          { "cat", 7 },
          { "dog", 9 },
          { "cat", 6 },
          { "apple", 1 } });
    auto range = umm2.equal_range("apple");
    for (auto it = range.first; it != range.second; ++it) {
        cout << it->first << ' ' << it->second << '\n';
    }
    
}
int main()
{
    mm();
    return 0;
}