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
 * https://leetcode-cn.com/problems/stone-game/
 * dp
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
    bool stoneGame(vector<int>& piles) {
        int ans = 0;
        vector<vector<int>> dp(piles.size(), vector<int>(piles.size(), 0));
        for (int i = 0; i < piles.size() - 1; ++i) {
            dp[i][i+1] = abs(piles[i] - piles[i+1]);
        }
        for (int len = 4; len <= piles.size(); len += 2) {
            for (int i = 0; i < piles.size() - len + 1; ++i) {
                int j = i + len - 1;
                int val1 = dp[i+2][j] + abs(piles[i] - piles[i+1]);
                int val2 = dp[i+1][j-1] + abs(piles[i] - piles[j]);
                int val3 = dp[i][j-2] + abs(piles[j-1] - piles[j]);
                dp[i][j] = max(val1, max(val2, val3));
            }
        }
        return dp[0][piles.size()-1] > 0;
    }
};

int main() {
    Solution sol;
    vector<int> p1 = {5,3,4,5};
    cout << sol.stoneGame(p1) << endl;
    return 0;
}
