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
 * https://leetcode-cn.com/problems/multiply-strings/
 * 思路，ans[i+j] += num1[i] * num2[j]
 *       再逐个处理ans里的进制
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
  string multiply(const string &num1, const string &num2) {
    if (num1.size() < 1 || num2.size() < 1) { return ""; }
    // NOTE: 注意这里
    if (num1 == "0" || num2 == "0") { return "0"; } 
    vector<int> n1(num1.size(), 0), n2(num2.size(), 0);
    int j = 0;
    for (int i = num1.size()-1; i >= 0; --i) {
      n1[j++] = num1[i] - '0';
    }
    j = 0;
    for (int i = num2.size()-1; i >=0; --i) {
      n2[j++] = num2[i] - '0';
    }

    vector<int> ans;
    for (int i = 0; i < n2.size(); ++i) {
      for (int j = 0; j < n1.size(); ++j) {
        int v = n2[i] * n1[j];
        int idx = i + j;
        if (ans.size() < idx + 1) {
          ans.push_back(v);
        } else {
          ans[idx] += v;
        }
      }
    }

    for (int i = 0; i < ans.size() - 1; ++i) {
      int v = ans[i];
      if (v < 10) { continue; }
      ans[i] = v % 10;
      ans[i+1] += v / 10;
    }
    int v = ans.back();
    if (v > 9) {
      ans[ans.size() - 1] = v % 10;
      ans.push_back(v / 10);
    }
    string s;
    s.resize(ans.size());
    j = 0;
    for (int i = ans.size() - 1; i >= 0; --i) {
      s[j++] = ans[i] + '0';
    }
    return s;
  }
};

int main() {
    Solution sol;
    cout << (sol.multiply("2", "3") == "6") << endl;
    cout << (sol.multiply("123", "456") == "56088") << endl;
    return 0;
}
