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
 * 给定一个整数数组，返回所有数对之间的第 k 个最小距离。一对 (A, B) 的距离被定义为 A 和 B 之间的绝对差值
 * 解法 二分查找 + 双指针：
 *  二分法：
 *    s、m、e表示距离
 *    target表示小于等于该距离的"元素对"数（双指针来算）
 *      有序数组num，已知num[j] - num[i] <= target, i是首个小于等于target的下标，此时满足条件的"数对"是count
 *                   求j往后挪一个，count该如何加多少，分析如下
 *                    若num[j+1] - num[i] <= target ，则增加了 j+1 - i个数对，因为(i, j+1), (i+1, j+1) ...与前面每个数对都满足
 *                    若不满足，则i往后挪，直到满足num[j+1] - num[i] <= target，此时增加了j+1 - i个数对 
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
  int smallestDistancePair(vector<int>& nums, int k) {
    std::sort(nums.begin(), nums.end());
    int s = 0, e = nums[nums.size() - 1] - nums[0];
    while (s < e) {
      int m = s + (e - s) / 2;
      int lessOrEqualM = cal(nums, m);
      // 如果nums中小于等于m的数对 大于k，则第k个小的"数对差"一定在[0, m]中
      if (lessOrEqualM > k) {
        // 比如1 1 1，差值小于等于0时的 数堆有3个，但不能因为就把e设置为m-1
        e = m; // 不能是m-1，因为有相同差值，会多累计
      } else if (lessOrEqualM < k) {
        // 说明"数对差"值的上限太小
        s = m + 1;
      } else if (lessOrEqualM == k) {
        // return m; // m可能不是一个真实存在的值，而是一个界
        e = m;
      }
    }
    return s; // 绝不会走到这
  }
  
  // 差值小于等于target的"数对"有多少
  int cal(vector<int>& nums, int target) {
    int i = 0, j = 1, count = 0;
    // 双指针
    for (; j < nums.size(); ++j) {
      while (nums[j] - nums[i] > target) { i++; }
      count += j - i; // (i, j), (i+1, j), ..., (j-1, j) 都满足条件，共j-i个
    }
    return count;
  }
};

int main() {
    Solution sol;
    vector<int> nums = {1,3,1};
    cout << (sol.smallestDistancePair(nums, 1) == 0) << endl;
    return 0;
}
