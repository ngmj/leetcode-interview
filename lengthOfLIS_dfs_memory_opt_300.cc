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
 *
 * https://leetcode-cn.com/problems/longest-increasing-subsequence/
 * dfs + 记忆搜索，时间负责度O(n^2)，考虑斐波那契数列 树状图，有一半被cache住了
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
    int lengthOfLIS(vector<int>& nums) {
        if (nums.size() < 1) {
            return 0;
        }
        vector<vector<int>> mm(nums.size(), vector<int>(nums.size(), -1));
        return dfs(nums, mm, 0, -1);
    }

    // 以pre_index为最长子序列最后一个元素，i为最长子序列起始元素 
    int dfs(vector<int>& nums, vector<vector<int>> &mm, int i, int pre_index) {
        if (i >= nums.size()) {
            return 0;
        }

        if (mm[pre_index + 1][i] > -1) {
            return mm[pre_index + 1][i];
        }

        int val1 = 0, val2 = 0;
        if (pre_index < 0 || nums[i] > nums[pre_index]) {
            val1 = dfs(nums, mm, i + 1, i) + 1;
        }

        val2 = dfs(nums, mm, i + 1, pre_index);
        mm[pre_index + 1][i] = max(val1, val2);
        return mm[pre_index + 1][i];
    }
};

int main() {
    Solution sol;
    vector<int> nums1 = {10,9,2,5,3,7,101,18};
    cout << sol.lengthOfLIS(nums1) << endl;
    return 0;
}
