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
 * dfs + 状态记录
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
    unordered_map<int, string> stat;
    string ans = dfs(cost, target, stat);
    return ans.size() > 0 ? ans : "0";
  }

  string dfs(const vector<int>& cost, int target,
           unordered_map<int, string> &stat) {
    if (target <= 0) { return ""; }
    auto iter = stat.find(target);
    if (stat.end() != iter) { return iter->second; }
    string ans = "";
    for (int i = 0; i < cost.size(); ++i) {
      string tmp = "";
      if (target < cost[i]) { continue; }
      else if (target == cost[i]) { tmp = to_string(i+1); }
      else {
        string s = dfs(cost, target - cost[i], stat);
        if (s.size() < 1) { continue; }
        if (s[0] - '0' < i + 1) {
          tmp = to_string(i+1) + s;
        } else {
          tmp = s + to_string(i+1);
        }
      }
      if (Compare(tmp, ans)) {
        ans = tmp;
      }
    }
    stat[target] = ans;
    return ans;
  }

  bool Compare(const string &s1, const string &s2) {
    if (s1.size() != s2.size()) { return s1.size() > s2.size(); }
    return s1 > s2;
  }
};

int main() {
    Solution sol;
    cout << (sol.largestNumber(vector<int>{4,3}, 7) == "21") << endl;
    cout << (sol.largestNumber(vector<int>{4,3,2,5,6,7,2,5,5}, 9) == "7772") << endl;
    return 0;
}
