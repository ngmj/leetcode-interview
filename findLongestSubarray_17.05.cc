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
  vector<string> findLongestSubarray(const vector<string>& array) {
    if (array.size() < 1) { return vector<string>(); }
    vector<short> flags(array.size(), -1);
    for (int i = 0; i < array.size(); ++i) {
      char c = array[i][0];
      if ((c <= 'Z' && c >= 'A') 
          || (c <= 'z' && c >= 'a')) {
        flags[i] = 1;
      }
    } 
    int ans = 0, b = 0;
    vector<int> sum(array.size(), 0);
    sum[0] = flags[0];
    unordered_map<int, int> h; // h[sum]下标
    h.reserve(flags.size());
    h[sum[0]] = 0;
    for (int i = 1; i < flags.size(); ++i) {
      sum[i] = sum[i-1] + flags[i];
      // 计算(0~i)数字字母相同的位置
      if (0 == sum[i]) {
        if (i + 1 > ans) { 
          ans = i + 1; 
          b = 0;
          continue;
        } 
      } else {
        auto iter = h.find(sum[i]);
        if (h.end() != iter) {
          int len = i - iter->second;
          if (len > ans) {
            ans = len;
            b = iter->second + 1;
          }
        } else {
          h[sum[i]] = i; // 相同sum只记录最左端
        }
      }
    }
    vector<string> s;
    if (ans > 0) {
      for (int i = b; i < b + ans; ++i) {
        s.push_back(array[i]);
      }
    }
    return s;
  }
};

int main() {
    Solution sol;
    cout << (sol.findLongestSubarray({"A","1","B","C","D","2","3","4","E","5","F","G","6","7","H","I","J","K","L","M"})
              == vector<string>({"A","1","B","C","D","2","3","4","E","5","F","G","6","7"})) << endl;
    cout << (sol.findLongestSubarray({"A","A"}) == vector<string>({})) << endl;
    return 0;
}
