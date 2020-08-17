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
 * 完全背包问题：dp[i][j] = max{dp[i-1][j], dp[i][j-cost[i]] + value[i]}
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
  string largestNumber(const vector<int>& cost, int target) {
    vector<vector<string>> dp(cost.size() + 1, vector<string>(target+1, "0"));
    for (int i = 0; i < cost.size() + 1; ++i) {
      dp[i][0] = "";
    }
    for (int i = 1; i < cost.size() + 1; ++i) {
      for (int j = 1; j < target + 1; ++j) {
        string a = dp[i-1][j];
        string b = "0";
        if (j >= cost[i-1] && "0" != dp[i][j-cost[i-1]]) { 
          b = to_string(i) + dp[i][j-cost[i-1]]; // i放在首位一定是当前选择最优
        }
        if ("0" == a || Compare(b, a)) {
          dp[i][j] = b;
        } else {
          dp[i][j] = a;
        }
      }
    }
    return dp[cost.size()][target]; 
  }

  bool Compare(const string &s1, const string &s2) {
    if (s1.size() != s2.size()) { return s1.size() > s2.size(); }
    return s1 > s2;
  }
};

int main() {
    Solution sol;
    cout << (sol.largestNumber(vector<int>{4,3,2}, 5) == "32") << endl;
    cout << (sol.largestNumber(vector<int>{4,3}, 7) == "21") << endl;
    cout << (sol.largestNumber(vector<int>{4,3,2,5,6,7,2,5,5}, 9) == "7772") << endl;
    return 0;
}
