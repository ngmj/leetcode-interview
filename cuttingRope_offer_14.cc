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
#include "serialize_deserialize_tree.hpp"
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
 * https://leetcode-cn.com/classic/problems/jian-sheng-zi-lcof/description/
 * dp[n] = max{i*dp[n-i], i*(n-i)}
 *             分成i长度端，剩下的n-i分成至少两段；只分成两段i和n-i长度
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
  int cuttingRope(int n) {
    vector<int> dp(n+1, 0);
    dp[2] = 1;
    for (int i = 3; i <= n; ++i) {
      int ans = 0;
      for (int j = 1; j <= i; ++j) {
        ans = max(max(j*dp[i-j], j*(i-j)), ans);
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
