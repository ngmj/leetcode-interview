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
 * https://leetcode-cn.com/problems/nth-digit/
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
  int findNthDigit(int n) {
    if (n < 10) { return n; }
    unordered_map<int, int> slot = {{1, 10}}; 
    int acc = 10; int scale = 1;
    for (int i = 2; i < 9; ++i) {
      scale *= 10;
      acc += i * scale * 9;
      slot[i] = acc;
    }

    int slot_id = 0;
    for (int i = 1; i < 9; ++i) {
      slot_id = i;
      if (n < slot[i]) {
        break;
      }
    }
    // 落在slot_id位数区间内
    n = n - slot[slot_id-1];
    int ans = n / slot_id;
    return ans - ans / 10 * 10;
  }
};

int main() {
    Solution sol;
    cout << (sol.findNthDigit(100) == 5) << endl;
    return 0;
}
