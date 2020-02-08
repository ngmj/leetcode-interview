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
 *
 * iter = lower_bound(start, end, val) 返回[start, end)>=val的第一个位置（下界）
 * iter = upper_bound(start, end, val) 返回[start, end)>val的第一个位置（上界）
 * 如(11,12) lower_bound查找11，返回0；upper_bound则返回1
 * https://leetcode-cn.com/problems/coin-change/
 * 类似爬楼梯，比如coins = [1, 2, 5], amount = 11，每次可以趴1、2、5阶梯，求问趴到11阶最少用几步
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
    int coinChange(vector<int>& coins, int amount) {
        if (coins.size() < 1 || amount < 1) {
            return 0;
        }
        vector<int> dp(amount+1, MAX_INT);
        dp[0] = 0;
        for (int i = 1; i < amount+1; ++i) {
            int res = MAX_INT;
            for (int j = 0; j < coins.size(); ++j) {
                if (coins[j] <= i) {
                    res = min(res, dp[i-coins[j]]);
                }
            }
            if (res < MAX_INT) {
                dp[i] = res + 1;
            }
        }
        return dp[amount] < MAX_INT ? dp[amount] : -1;
    }
};

int main() {
    Solution sol;
    vector<int> coins1 = {1, 2, 5};
    cout << sol.coinChange(coins1, 11) << endl;
    vector<int> coins2 = {2};
    cout << sol.coinChange(coins2, 3) << endl;
    vector<int> coins3 = {5,2,1};
    cout << sol.coinChange(coins3, 4) << endl;
    return 0;
}
