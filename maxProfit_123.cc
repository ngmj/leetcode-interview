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
    int maxProfit(vector<int>& prices) {
        vector<vector<vector<int>>> dp(prices.size()+1, vector<vector<int>>(3, vector<int>(2, 0)));
        for (int k = 0; k < 3; ++k) {
            dp[0][k][1] = MIN_INT;
        }
        for (int i = 0; i < prices.size()+1; ++i) {
            dp[i][0][1] = MIN_INT;
        }
        for (int k = 1; k < 3; ++k) {
            for (int i = 1; i < prices.size()+1; ++i) {
                dp[i][k][0] = max(dp[i-1][k][0], dp[i-1][k][1] + prices[i-1]);
                dp[i][k][1] = max(dp[i-1][k][1], dp[i-1][k-1][0] - prices[i-1]);    
            }
        }
        
        return dp[prices.size()][2][0];
    }
};

int main() {
    Solution sol;
    vector<int> p1 = {3,3,5,0,0,3,1,4};
    cout << sol.maxProfit(p1) << endl;
    vector<int> p2 = {1,2,3,4,5};
    cout << sol.maxProfit(p2) << endl;
    vector<int> p3 = {7,6,4,3,1};
    cout << sol.maxProfit(p3) << endl;
    vector<int> p4 = {1,2,4,2,5,7,2,4,9,0};
    cout << sol.maxProfit(p4) << endl;

    return 0;
}
