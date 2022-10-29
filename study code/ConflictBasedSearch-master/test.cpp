#include <iostream>
#include <algorithm>
#include <vector>
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

int main()
{
    vector<vector<int>> a = {{3, 3}, {2, 2},{1,8}, {8, 10}, {15, 18}};
    sort(a.begin(), a.end());
    merge1(a);
    return 0;
}