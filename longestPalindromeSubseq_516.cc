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
 * https://leetcode-cn.com/problems/longest-palindromic-subsequence/
=》解法：dp[i][j] 表示i~j的最长回文子序列长度；dp[i][j] = dp[i+1][j-1] + 2 if val[i] == val[j]
                                                          max(dp[i+1][j], dp[i][j-1]) if val[i] != val[j]
         意遍历顺序，i 从最后一个字符开始往前遍历，j 从 i + 1 开始往后遍历，这样可以保证每个子问题都已经算好了。
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
  int longestPalindromeSubseq(const string &s) {
    if (s.size() < 1) { return 0; }
    vector<vector<int>> dp(s.size(), vector<int>(s.size(), 0));
    for (int i = 0; i < s.size(); ++i) {
      dp[i][i] = 1;
    }
    for (int i = s.size()-1; i >= 0; --i) {
      for (int j = i + 1; j < s.size(); ++j) {
        if (s[i] == s[j]) { dp[i][j] = dp[i+1][j-1] + 2; }
        else { dp[i][j] = max(dp[i+1][j], dp[i][j-1]); }
      }
    }
    return dp[0][s.size()-1];
  }
};

int main() {
    Solution sol;
    cout << (sol.longestPalindromeSubseq("bbbab") == 4) << endl;
    cout << (sol.longestPalindromeSubseq("cbbd") == 2) << endl;
    return 0;
}
