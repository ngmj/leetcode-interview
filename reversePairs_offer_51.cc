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
 * 二路归并的思路，一边归并排序，一边统计假设
 * vec = A + B两半，AB内的逆序数已知，求A和B之间的逆序对 
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
  int reversePairs(vector<int>& nums) {
    vector<int> sorted(nums.size(), 0);
    return MergeSort(nums, sorted, 0, nums.size() - 1);
  }

  int MergeSort(vector<int>& nums, vector<int> &sorted, int s, int e) {
    if (e <= s) { return 0; }
    int m = s + (e - s) / 2;
    int ans = MergeSort(nums, sorted, s, m) + MergeSort(nums, sorted, m+1, e);
    int i = s, j = m+1, pos = s;
    while (i <= m && j <= e) {
      if (nums[i] <= nums[j]) { 
        sorted[pos++] = nums[i]; 
        ans += j - m - 1; // 前一个数组落元素时，再累加
        ++i;  
      }
      else { 
        sorted[pos++] = nums[j]; 
        ++j; 
      }
    }
    while (i <= m) {
      sorted[pos++] = nums[i];
      ans += e - m; 
      ++i;
    } 
    while (j <= e) {
      sorted[pos++] = nums[j];
      ++j;
    }
    // copy 
    for (int i = s; i <= e; ++i) {
      nums[i] = sorted[i];
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
