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
 * https://leetcode-cn.com/problems/can-make-palindrome-from-substring/
 * 前缀和的思路
 * sum[j]['a'~'z'] - sum[i]['a'~'z'] 其中奇数的字母个数n，如何n/2 <= k则返回true
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
  vector<bool> canMakePaliQueries(const string &s, const vector<vector<int>>& queries) {
    vector<vector<int>> sum(s.size()+1, vector<int>(26, 0));
    for (int i = 0; i < s.size(); ++i) {
      sum[i+1] = sum[i];
      sum[i+1][s[i] - 'a']++;
    } 
    vector<bool> ans(queries.size(), false);
    for (int q = 0; q < queries.size(); ++q) {
      auto &query = queries[q];
      int i = query[0], j = query[1], k = query[2];
      int odd = 0;
      for (int l = 0; l < 26; ++l) {
        int n = sum[j+1][l]-sum[i][l];
        if (n&1) { odd++; }
      }
      if ((odd >> 1) <= k) { ans[q] = true; }
    }
    return ans;
  }
};

int main() {
    Solution sol;
    cout << (sol.canMakePaliQueries("abcda", {{3,3,0},{1,2,0},{0,3,1},{0,3,2},{0,4,1}}) 
            == vector<bool>({true,false,false,true,true})) << endl;
    return 0;
}
