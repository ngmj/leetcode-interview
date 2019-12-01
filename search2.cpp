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
 * https://leetcode-cn.com/problems/search-in-rotated-sorted-array-ii/
 * 1. s, m, e 这两个区间内一定有一个是有序的，另一个是旋转数组（或也是有序，不过当作旋转数组递归处理也不会错）
 * 2. 假设[s, m) 是有序数组，则二分查找，另一边递归调用search即可
 * 因为元素由重复，无法通过s, m, e三个位置值，判断哪边有序，考虑0 1 -1 0 0 0 0
 * 虽然nums[s] <= nums[m] 但是s，m区间却不是有序的，
 * 问题变为如果比较三点值，求有序区间？
 * 消除首位重复值，确保s e两处是不同的，中间值m，则可以通过nums[s] <= nums[m]判断左区间是有序的
 * 时间复杂度O(lgn)，最差情况是O(n), 空间复杂度O(1)
 * */
using namespace std;

class Solution {
public:
    bool search(vector<int>& nums, int target)
    {
        return search( nums, 0, nums.size() - 1, target );
    }

    bool search( vector<int>& nums, int s, int e, int target )
    {
        if ( e < s )
        {
            return false;
        }

        while ( s < e && nums[s] == nums[e] ){ e--; }

        if ( nums[s] < nums[e] )
        {
            return binarySearch( nums, s, e, target );
        }

        int m = (s + e) / 2;
        if ( target == nums[m] )
        {
            return true;
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
        return false;
    }

    bool binarySearch( vector<int>& nums, int s, int e, int target )
    {
        while ( s <= e )
        {
            int m = (s + e) / 2;
            if ( target == nums[m] )
            {
                return true;
            } else if ( target < nums[m] )
            {
                e = m - 1;
            } else
            {
                s = m + 1;
            }
        }

        return false;
    }
};

int main()
{
    Solution sol;
    vector<int> nums1 = {2,5,6,0,0,1,2};
    int target1 = 0;
    cout << VectorToString( nums1 ) << " | " << target1 << " | " << ( sol.search( nums1, target1 ) == true ) << endl;

    int target2 = 3;
    cout << VectorToString( nums1 ) << " | " << target2 << " | " << ( sol.search( nums1, target2 ) == false ) << endl;
    return 0;
} 
