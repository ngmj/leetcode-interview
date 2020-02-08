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
 *  std::priority_queue<int> 默认是大根堆，
 *  std::priority_queue<int, std::vector<int>, std::greater<int> > 小根堆
 * deque: front(), back(), push_back(), pop_back, push_front, pop_front(), empty(), clear()
 * https://leetcode-cn.com/problems/longest-increasing-subsequence/submissions/
 * dp解法
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

        int ans = 0;
        vector<int> dp(nums.size(), 0);
        for (int i = 0; i < nums.size(); ++i) {
            int max = 0;
            for (int j = 0; j < i; ++j) {
                if (nums[j] < nums[i]) {
                    max = std::max(max, dp[j]);
                }
            }
            dp[i] = max + 1;
            ans = std::max(ans, dp[i]);
        }
        return ans;
    }
};

int main() {
    Solution sol;
    vector<int> nums1 = {10,9,2,5,3,7,101,18};
    cout << sol.lengthOfLIS(nums1) << endl;
    return 0;
}
