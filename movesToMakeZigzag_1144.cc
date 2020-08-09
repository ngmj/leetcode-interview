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
  int movesToMakeZigzag(const vector<int>& nums) {
    if (nums.size() < 2) { return 0; }
    int ans1 = movesToMakeZigzag(nums, 0, nums.size() - 1);
    int ans2 = movesToMakeZigzag(nums, 1, nums.size() - 1);
    if (nums[0] >= nums[1]) {
      ans2 += nums[0] - nums[1] + 1;
    }
    return min(ans1, ans2);
  }
  int movesToMakeZigzag(const vector<int>& nums, int s, int e) {
    if (e - s < 1) { return 0; }
    int ans = 0;
    for (int i = s + 1; i <= e; ++i, ++i) {
      int min = nums[i-1];
      if (i+1 <= e) {
        if (nums[i+1] < min) { min = nums[i+1]; }
      }
      if (nums[i] >= min) {
        ans += nums[i] - min + 1;
      }
    }
    return ans; 
  }
};

int main() {
    Solution sol;
    cout << (sol.movesToMakeZigzag({9,6,1,6,2,1,3}) == 9) << endl;
    cout << (sol.movesToMakeZigzag({1, 2, 3}) == 2) << endl;
    cout << (sol.movesToMakeZigzag({9,6,1,6,2}) == 4) << endl;
    return 0;
}
