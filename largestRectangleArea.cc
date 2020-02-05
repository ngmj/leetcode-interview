#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int maxRange = 0;
        int lastLeftH = 0;
        for ( int i = 0; i < heights.size(); i++ )
        {
            if ( 0 != i && 0 != heights[i-1] && heights[i] <= lastLeftH )
            {
                continue;
            }
            int j = i + 1; // 指向下一个元素
            int leftH = heights[i]; // 矩形左边界高度
            while ( j < heights.size() && 0 != heights[j] )
            {
                if ( heights[j] < leftH )
                {
                    maxRange = std::max( maxRange, leftH * ( j - i ) );
                    leftH = heights[j];
                }
                j++;
            }
            maxRange = std::max( maxRange, leftH * ( j - i ) );
            lastLeftH = leftH;
        }
        return maxRange;
    }
};

int main()
{
    // vector<int> heights = { 0,5,0,6 }; // ==>6
    // vector<int> heights = { 2,1,5,6,2,3 }; // ==>10
    // vector<int> heights = { 1,1,1,1,1,1 }; // ==>6
    vector<int> heights = { 0,1,0,2,1,0,1,3,2,1,2,1 }; // ==>6
    Solution solution;
    cout << solution.largestRectangleArea( heights ) << endl;
    return 0;
}
