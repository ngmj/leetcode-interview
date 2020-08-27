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
 * https://leetcode-cn.com/problems/letter-combinations-of-a-phone-number/
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

const unordered_map<int, vector<char>> m = {
  {2, {'a', 'b', 'c'}},
  {3, {'d', 'e', 'f'}},
  {4, {'g', 'h', 'i'}},
  {5, {'j', 'k', 'l'}},
  {6, {'m', 'n', 'o'}},
  {7, {'p', 'q', 'r', 's'}},
  {8, {'t', 'u', 'v'}},
  {9, {'w', 'x', 'y', 'z'}}};
class Solution {
public:
  vector<string> letterCombinations(const string &digits) {
    string s;
    s.resize(digits.size());
    dfs(s, digits, 0);
    return ans;
  }

  void dfs(string s, const string &digits, int i) {
    if (i > digits.size() - 1) {
      ans.push_back(s.c_str());
      return;
    }
    int c = digits[i] - '0';
    auto iter = m.find(c);
    if (m.end() == iter) { return; }
    for (auto &t: iter->second) {
      s[i] = t;
      dfs(s, digits, i+1);
    }
  }
private:
  vector<string> ans;
};

int main() {
    Solution sol;
    cout << (sol.letterCombinations("23") == 
          vector<string>({"ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"})) << endl;
    return 0;
}
