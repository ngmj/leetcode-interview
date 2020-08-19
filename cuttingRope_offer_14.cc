#include <vector>
#include <limits>
#include <iostream>
#include <algorithm>
#include <map>
#include <list>
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
 * list: push_back, push_front, insert(pos, val), front, remove(val), erase(iter)
 *
 * iter = lower_bound(start, end, val) 返回[start, end)>=val的第一个位置（下界）
 * iter = upper_bound(start, end, val) 返回[start, end)>val的第一个位置（上界）
 * 如(11,12) lower_bound查找11，返回0；upper_bound则返回1
 * https://leetcode-cn.com/classic/problems/jian-sheng-zi-ii-lcof/description/
 * dp求解，dp[n]表示n长度的绳子拆成至少两份的最优解，则
 *  dp[n] = max{i*dp[n-i]表示拆成i长度的一份，剩下的继续拆（至少两份）, 
 *              i*(n-i)示拆成i长度的一份，剩下的不拆}, i=1~n-1;
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

// 答案需要取模 1e9+7（1000000007），如计算初始结果为：1000000008，请返回 1。
const int kMod = 1e9+7;
class Solution {
public:
  int cuttingRope(int n) {
    vector<int> dp(n+1, 1);
    for (int i = 2; i <= n; ++i) {
      int ans = 1;
      for (int j = 1; j < i; ++j) {
        int tmp = max(j*dp[i-j] % kMod, j*(i-j) % kMod);
        if (tmp > ans) { ans = tmp; }
      }
      dp[i] = ans;
    }
    return dp[n];
  }
};

int main() {
    Solution sol;
    cout << (sol.cuttingRope(2) == 1) << endl;
    cout << (sol.cuttingRope(10) == 36) << endl;
    return 0;
}
