#include <vector>
#include <limits>
#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <stack>
#include <queue>
#include <deque>
#include <unordered_set>
#include <unordered_map>
#include "string_util.h"

/*
 * stack: top(), pop(), push(), empty()
 * queue: front(), back(), push(), pop(), empty()
 * priority_queue: top(), push(), pop(), empty()
 * deque: front(), back(), push_back(), pop_back, push_front, pop_front(), empty(), clear()
 * https://leetcode-cn.com/problems/sliding-window-maximum/
 * queue<int>, 保证头部是当前队列中最大值，处理当前元素时，遵循如下规则
 * 1、如果队列不为空，且当前元素比头大，则清空队列，当前元素入队列
 * 2、否则如果队列不为空，入队列，并出头部（未思考到位，出队列头时要依然保证下一个头是最大，所以入队列前循环检查）
 * 3、否则入队列
 *
 * 第2次思考的方法
 * 队列保存元素下标（因为会有清空队列的操作，所以入第i元素，出第i-k元素，队列头的下标得满足）
 * 1、入第i元素前，出第i-k元素
 * 2、入第i个元素
 * 3、循环出队列，直到队列头是最大值（要遍历一轮，再出队列）
 *
 * 第3次思考的方法
 * 保证队列是降序队列即可保证每次出头后，头依然是最大值
 * 1、入第i元素前，出第i-k元素
 * 2、将队尾小于等于第i个元素弹出队列
 * */
using namespace std;

typedef vector<vector<int>> VVI;
typedef vector<int> VI;
typedef long long LL;
LL MAX_LL = std::numeric_limits<LL>::max();;
int MAX_INT = std::numeric_limits<int>::max();;

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) 
    {
        vector<int> ans;
        if ( nums.size() < 1 )
        {
            return ans;
        }
        deque<int> qi; // 保存nums下标
        for ( size_t i = 0; i < nums.size(); i++ )
        {
            if ( !qi.empty() && i >= k && qi.front() <= i - k )
            {
                // 第i个元素要进队列，则应该淘汰i-k个元素，检查队列头的下标是否小于i - k
                qi.pop_front();
            }

            // 保证队列是严格降序的
            // 这样下一轮头出队列后，头部自然就是最大值
            while ( !qi.empty() && nums[qi.back()] <= nums[i] )
            {
                qi.pop_back();
            }

            qi.push_back(i);
            if ( i >= k - 1 )
            {
                ans.push_back( nums[qi.front()] );
            }
        }
        return ans;
    }
};

int main()
{
    Solution sol;
    vector<int> nums1 = { 1,3,-1,-3,5,3,6,7 };
    int k1 = 3;
    cout << VectorToString(sol.maxSlidingWindow(nums1, k1)) << endl;
    vector<int> nums2 = {1,3,1,2,0,5};
    int k2 = 3;
    cout << VectorToString(sol.maxSlidingWindow(nums2, k2)) << endl;
    return 0;
}
