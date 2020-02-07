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
 * https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-ii/
 * 参见experience.md 买卖股票的通用求解
  **/
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
    int maxProfit(int K, vector<int>& prices) {
        // 挑选买卖点
        vector<int> buy_sell;
        buy_sell.reserve(prices.size());
        for (int i = 0; i < prices.size(); ++i) {
            int pre = i != 0 ? prices[i-1] : MAX_INT;
            int next = (i != prices.size() - 1) ? prices[i+1] : MIN_INT;
            if ((prices[i] <= pre && prices[i] < next) 
                    || (prices[i] > pre && prices[i] >= next)) {
                // 一定留意 pre >= val < next是买点
                // 一定留意 pre < val >= next是卖点
                buy_sell.push_back(prices[i]);
            }
        }
        if (K > buy_sell.size() / 2) {
            return maxProfit(buy_sell);
        }
        vector<vector<vector<int>>> dp(buy_sell.size()+1, vector<vector<int>>(K+1, vector<int>(2, 0)));
        for (int k = 0; k < K+1; ++k) {
            dp[0][k][1] = MIN_INT;
        }
        for (int i = 0; i < buy_sell.size()+1; ++i) {
            dp[i][0][1] = MIN_INT;
        }
        for (int k = 1; k < K+1; ++k) {
            for (int i = 1; i < buy_sell.size()+1; ++i) {
                dp[i][k][0] = max(dp[i-1][k][0], dp[i-1][k][1] + buy_sell[i-1]);
                dp[i][k][1] = max(dp[i-1][k][1], dp[i-1][k-1][0] - buy_sell[i-1]);    
            }
        }
        
        return dp[buy_sell.size()][K][0];
    }

    int maxProfit(vector<int>& prices) {
        int ans = 0;
        for (int i = 1; i < prices.size(); ++i) {
            if (prices[i] > prices[i-1]) {
                ans += prices[i] - prices[i-1];
            }            
        }
        return ans;
    }
};

int main() {
    Solution sol;
    vector<int> p1 = {2,4,1};
    cout << sol.maxProfit(2, p1) << endl;
    vector<int> p2 = {3,2,6,5,0,3};
    cout << sol.maxProfit(2, p2) << endl;
    vector<int> p3 = {7,6,4,3,1};
    cout << sol.maxProfit(2, p3) << endl;
    vector<int> p4 = {1,2,4,2,5,7,2,4,9,0};
    cout << sol.maxProfit(2, p4) << endl;

    return 0;
}
