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
 * priority_queue: top(), pop(), push(), empty()
 *  std::priority_queue<int> 默认是大根堆，
 *  std::priority_queue<int, std::vector<int>, std::greater<int> > 小根堆
 * queue: front(), back(), push(), pop(), empty()
 * deque: front(), back(), push_back(), pop_back, push_front, pop_front(), empty(), clear()
 *
 * iter = lower_bound(start, end, val) 返回[start, end)>=val的第一个位置（下界）
 * iter = upper_bound(start, end, val) 返回[start, end)>val的第一个位置（上界）
 * 如(11,12) lower_bound查找11，返回0；upper_bound则返回1
 * https://leetcode-cn.com/problems/maximum-subarray/
 * 分治法
 * 动态规划法
 * 贪心法（实际就是动态规划法+状态压缩）
 * */
using namespace std;

typedef vector<vector<int>> VVI;
typedef vector<int> VI;
typedef unsigned int UI;
typedef long long LL;
typedef unsigned long long ULL;
LL MAX_LL = std::numeric_limits<LL>::max();
LL MIN_LL = std::numeric_limits<LL>::min();
int MAX_INT = std::numeric_limits<int>::max();
int MIN_INT = std::numeric_limits<int>::min();

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int max_val = nums[0];
        // dp[i] = max(dp[i-1] + val, val) 以i为结尾的最大子序列
        // 状态压缩：sum=max(sum + val, val)
        int sum = nums[0]; 
        for (int i = 1; i < nums.size(); ++i) {
            int val = nums[i];
            sum += val;
            if (sum < val) {
                sum = val;
            } 
            max_val = max(sum, max_val);
        }
        return max_val;
    }
};

int main() {
    Solution sol;
    vector<int> n1 = {-2,1,-3,4,-1,2,1,-5,4};
    cout << sol.maxSubArray(n1) << endl;
    return 0;
}
