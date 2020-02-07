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
 * https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/
 * 题目有个坑在与买卖一次只收一次手续费，与常识相悖，易出错
 * 状态：dp[i][0 or 1]
 * 转义方程：dp[i][0] = max(dp[i-1][0], dp[i-1][1]+val-fee) 卖需要付手续费
 *           dp[i][1] = max(dp[i-1][1], dp[i-1][0]-val) 买不用付手续费
 * 初始状态：dp[0][0] = 0, dp[0][1] = MIN_INT
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
    int maxProfit(vector<int>& prices, int fee) {
        if (prices.size() < 2) {
            return 0;
        }
        vector<vector<LL>> dp(prices.size()+1, vector<LL>(2, 0));
        dp[0][1] = MIN_INT;
        for (int i = 1; i < prices.size()+1; ++i) {
            dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i-1] - fee);
            dp[i][1] = max(dp[i-1][1], dp[i-1][0] - prices[i-1]);
        }
        return dp[prices.size()][0];
    }
};

int main() {
    Solution sol;
    vector<int> p1 = {1, 3, 2, 8, 4, 9};
    cout << sol.maxProfit(p1, 2) << endl;
    return 0;
}
