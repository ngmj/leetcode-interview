#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int maxRange = 0;
        for ( int i = 0; i < heights.size(); i++ )
        {
            int minHeight = std::numeric_limits<int>::max();
            for ( int j = i; j < heights.size(); j++ )
            {
                minHeight = std::min( minHeight, heights[j] );
                maxRange = std::max( maxRange, minHeight*(j - i + 1) );
            }
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
