#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <stack>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include "string_util.h"

/*
 * https://leetcode-cn.com/problems/search-in-rotated-sorted-array/
 * 1. s, m, e 这两个区间内一定有一个是有序的，另一个是旋转数组（或也是有序，不过当作旋转数组递归处理也不会错）
 * 2. 假设[s, m) 是有序数组，则二分查找，另一边递归调用search即可
 * 时间复杂度O(lgn), 空间复杂度O(1)
 * */
using namespace std;

class Solution {
public:
    int search(vector<int>& nums, int target)
    {
        return search( nums, 0, nums.size() - 1, target );
    }

    int search( vector<int>& nums, int s, int e, int target )
    {
        if ( e < s )
        {
            return -1;
        }
        int m = (s + e) / 2;
        if ( target == nums[m] )
        {
            return m;
        }

        if ( nums[s] <= nums[m] )
        {
            if ( target < nums[m] && target >= nums[s] )
            {
                return binarySearch( nums, s, m-1, target );
            } else
            {
                return search( nums, m+1, e, target );
            }
        } else
        {
            if ( target > nums[m] && target <= nums[e] )
            {
                return binarySearch( nums, m+1, e, target );
            } else
            {
                return search( nums, s, m-1, target );
            }
        }
        return -1;
    }

    int binarySearch( vector<int>& nums, int s, int e, int target )
    {
        while ( s <= e )
        {
            int m = (s + e) / 2;
            if ( target == nums[m] )
            {
                return m;
            } else if ( target < nums[m] )
            {
                e = m - 1;
            } else
            {
                s = m + 1;
            }
        }

        return -1;
    }
};

int main()
{
    Solution sol;
    vector<int> nums1 = {4,5,6,7,0,1,2};
    int target1 = 0;
    cout << VectorToString( nums1 ) << " | " << target1 << " | " << ( sol.search( nums1, target1 ) == 4 ) << endl;

    int target2 = 3;
    cout << VectorToString( nums1 ) << " | " << target2 << " | " << ( sol.search( nums1, target2 ) == -1 ) << endl;
    return 0;
} 
