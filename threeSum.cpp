#include <vector>
#include <iostream>
#include <unordered_map>
#include "string_util.h"

/*
 * https://leetcode-cn.com/problems/two-sum/
 * 1轮 hash表存储target-num[i]
 * 2轮 遍历num是否存在于hash表中，存在则表明有该值
 * */
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> res;
        res.reserve(2);
        unordered_map<int, int> pair2Idx;
        pair2Idx.reserve( nums.size() );
        for ( size_t i = 0; i < nums.size(); i++ )
        {
            pair2Idx.insert( make_pair(target - nums[i], i) );
        }

        for ( size_t i = 0; i < nums.size(); i++ )
        {
            auto iter = pair2Idx.find( nums[i] );
            if ( pair2Idx.end() != iter 
                    && iter->second != i )
            {
                res.push_back( i );
                res.push_back( iter->second );
                break;
            }
        }
        return res;
    }
};

int main()
{
    Solution sol;
    vector<int> nums1 = { 2, 7, 11, 15 };
    int target1 = 9;
    cout << VectorToString(nums1) << " - " << target1 << "|" << VectorToString(sol.twoSum( nums1, target1 )) << endl;
}
