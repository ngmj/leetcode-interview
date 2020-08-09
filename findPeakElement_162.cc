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
 * 折半
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
  int findPeakElement(const vector<int>& nums) {
    int s = 0, e = nums.size() - 1;
    while (s < e) {
      int m = s + (e - s) / 2;
      // 因为m跟右边的比过来，没符合，所以可以s = m+1
      if (m + 1 <= e && nums[m+1] > nums[m]) { s = m + 1; }
      // m未跟左边比过，所以e=m
      else { e = m; }
    }
    return s;
  }
};

int main() {
    Solution sol;
    cout << (sol.findPeakElement({1,2,3,1}) == 2) << endl;
    cout << (sol.findPeakElement({1,2,1,3,5,6,4}) == 5 || 
             sol.findPeakElement({1,2,1,3,5,6,4}) == 2) << endl;
    return 0;
}
