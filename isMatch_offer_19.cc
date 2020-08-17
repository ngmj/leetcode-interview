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
  string Clear(const string &p) {
    int i = 0;
    while ('*' == p[i]) { ++i; }
    if (i > 0) {
      return p.substr(i, p.size() - i);
    }
    return p;
  }
  bool IsEqual(char c1, char c2) {
    if ('.' == c2) { return true; }
    return c1 == c2;
  }
  bool isMatch(const string &s, const string &p) {
    string np = Clear(p);
    vector<vector<bool>> dp(s.size()+1, vector<bool>(np.size()+1, false));
    dp[0][0] = true;
    // 从0开始，因为s = "", p = "a*"照样是可以匹配的，
    // 即dp[0][0~j]是需要计算的
    for (int i = 0; i <= s.size(); ++i) {
      for (int j = 1; j <= np.size(); ++j) {
        if (i > 0 && IsEqual(s[i-1], np[j-1])) {
          dp[i][j] = dp[i-1][j-1];
        }
        if ('*' == np[j-1]) {
          bool flag = dp[i][j-2]; // 0个前面字符
          if (i > 0 && IsEqual(s[i-1], np[j-2])) { // 1个或以上
            flag = flag || dp[i-1][j];
          }
          dp[i][j] = flag;
        }
      }
    }
    return dp[s.size()][np.size()];
  }
};

int main() {
    Solution sol;
    cout << (sol.isMatch("", "c*") == true) << endl;
    cout << (sol.isMatch("aa", "a") == false) << endl;
    cout << (sol.isMatch("aa", "a*") == true) << endl;
    cout << (sol.isMatch("ab", ".*") == true) << endl;
    cout << (sol.isMatch("aab", "c*a*b") == true) << endl;
    cout << (sol.isMatch("mississippi", "mis*is*p*.") == false) << endl;
    return 0;
}
