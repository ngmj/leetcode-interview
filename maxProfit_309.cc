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
 * https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/
 * 状态：dp[i][0 or 1]
 * 转义方程：dp[i][0] = max(dp[i-1][0], dp[i-1][1]+val)
 *           dp[i][1] = max(dp[i-1][1], dp[i-2][0]-val)
 * 初始状态：dp[0][0] = 0, dp[1][0] = 0, dp[0][1] = MIN_INT, dp[1][1] = -val
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
    int maxProfit(vector<int>& prices) {
        if (prices.size() < 2) {
            return 0;
        }
        vector<vector<int>> dp(prices.size()+1, vector<int>(2, 0));
        dp[0][1] = MIN_INT;
        dp[1][1] = -prices[0];
        for (int i = 2; i < prices.size()+1; ++i) {
            dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i-1]);
            dp[i][1] = max(dp[i-1][1], dp[i-2][0] - prices[i-1]);
        }
        return dp[prices.size()][0];
    }
};

int main() {
    Solution sol;
    vector<int> p1 = {1,2,3,0,2};
    cout << sol.maxProfit(p1) << endl;
    return 0;
}
