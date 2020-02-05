#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include "string_util.h"

/*
 * https://leetcode-cn.com/problems/3sum/ 
 * sort 数组
 * 挑选中间数，然后左后双指针 
 * */
using namespace std;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> res;
        if ( nums.size() < 3 )
        {
            return res;
        }
        std::sort( nums.begin(), nums.begin() + nums.size() );

        for ( size_t i = 0; i < nums.size() - 2; i++ )
        {
            size_t first = i + 1;
            size_t last = nums.size() - 1;
            while ( first < last )
            {
                // 三个数同正同负，则退出
                if ( nums[i] > 0 || nums[last] < 0 )
                {
                    break;
                }
                int sum = nums[i] + nums[first] + nums[last];
                if ( 0 == sum )
                {
                    res.push_back( { nums[i], nums[first], nums[last] } );
                    while ( first < last && nums[first] == nums[++first] ) { }
                } else if ( sum > 0 )
                {
                    while ( first < last && nums[last] == nums[--last] ) { }
                } else
                {
                    while ( first < last && nums[first] == nums[++first] ) { }
                }
            }
            while ( i < nums.size() - 2 && nums[i] == nums[i+1] ) { i++; }
        }
        return res;
    }
};

void Sol( vector<int> &nums )
{
    Solution sol;
    vector<vector<int>> res = sol.threeSum( nums );
    cout << VectorToString(nums);
    for ( auto &vec: res )
    {
        cout << " | " << VectorToString( vec );
    }
    cout << endl;
}

int main()
{
    vector<int> nums1 = { -1, 0, 1, 2, -1, -4 };
    Sol( nums1 );

    vector<int> nums2 = { 0, 0, 0, 0, 0 };
    Sol( nums2 );

    vector<int> nums3 = {};
    Sol( nums3 );

    return 0;
}
