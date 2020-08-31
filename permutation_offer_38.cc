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
  vector<string> permutation(const string &s) {
    if (s.size() < 1) { return ans; }
    // 在一次res生成中visisted表示s的哪些下标已经遍历过了
    unordered_map<int, bool> visisted;
    dfs(s, visisted, "", 0);
    return ans;
  }
  void dfs(const string &s, unordered_map<int, bool> &visisted, string res, int i) {
    if (i > s.size() - 1) { ans.push_back(move(res)); return; }
    // 表示当前位置i，已经有哪些字符出现过，防止出现重复，比如aa
    // 第一个a在i=0时，生成过，第一个a再处理时，就要跳过
    unordered_set<char> st;
    for (int j = 0; j < s.size(); ++j) {
      if (visisted[j]) { continue; }
      if (st.count(s[j])) { continue; }
      st.insert(s[j]);
      visisted[j] = true;
      string tmp = res;
      tmp.append(1, s[j]);
      dfs(s, visisted, tmp, i+1);
      visisted[j] = false;
    }
  }
private:
  vector<string> ans;
};

int main() {
    Solution sol;
    cout << (sol.permutation("ab") == vector<string>({"ab", "ba"})) << endl;
    return 0;
}
