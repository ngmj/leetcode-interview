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
 * 前缀和，两个元素差值为k的个数（类似两个元素和问题，hash解）
 * sum[j] - sum[i] = k，以j为尾，sum[i] = sum[j] - k在前面hash中出现的次数
 * 一边sum，一边计算，如果先算完hash，再套公式，就需要考虑j != i了，反而麻烦
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
  int subarraySum(const vector<int>& nums, int k) {
    unordered_map<int, int> h;
    h.reserve(nums.size());
    int ans = 0;
    int sum = 0; 
    for (int i = 0; i < nums.size(); ++i) {
      sum += nums[i];
      // 1. sum[i] = sum[j] - k，差值是否满足（从2个位置的开始和）
      int target = sum - k;
      auto iter = h.find(target);
      if (h.end() != iter) {
        ans += iter->second;
      }
      // 2. sum[j] == k? 即从头到当前位置的和是否满足
      if (sum == k) {
        ans++;
      }
      // 一定放在后面，因为sum是以j为尾部的前缀和，h是0～j-1的前缀和统计值
      h[sum]++;
    }
    return ans;
  }
};

int main() {
    Solution sol;
    cout << (sol.subarraySum({1}, 0) == 0) << endl;
    cout << (sol.subarraySum({1,-1,1}, 0) == 2) << endl;
    cout << (sol.subarraySum({1,2,3}, 3) == 2) << endl;
    return 0;
}
