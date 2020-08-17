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
 * https://leetcode-cn.com/problems/shu-zu-zhong-de-ni-xu-dui-lcof/
 * 后插法，binary_search插入位置，统计
 * 超时了
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
  int BS(vector<int>& nums, int s, int e, int val) {
    // 因为不一定能够找到符合条件的位置
    while (s <= e) {
      int m = s + (e - s) / 2;
      if (nums[m] <= val) {
        e = m - 1;
      } else {
        s = m + 1;
      }
    }
    // 退出循环前 s和e同时指向了一个元素，此时退出有两种情况
    // s指向当前元素的可能要不就是s是起始位置，要不就是经过条件判断挪到了当前位置
    // nums[s或e] <= val， e左移动一个，e要不就是"溢出"要不就是符合条件的值（因为e-1是经过s扫描的）
    // nums[s或e] > val，s往右，此时e是答案
    // 最终就是e答案
    // 此时nums[e] > val >= nums[s] 或者s or e溢出
    return e; 
  }

  int reversePairs(vector<int>& nums) {
    int ans = 0;
    for (int i = 1; i < nums.size(); ++i) {
      int idx = BS(nums, 0, i - 1, nums[i]);
      if (idx > -1) { ans += idx + 1; }
      // 将tmp挪到该在的位置
      int tmp = nums[i];
      for (int s = i - 1; s > idx; --s) {
        nums[s+1] = nums[s];
      }
      nums[idx+1] = tmp;
    }
    return ans;
  }
};

int main() {
    Solution sol;
    vector<int> vec = {7,5,6,4};
    cout << (sol.reversePairs(vec) == 5) << endl;
    return 0;
}
