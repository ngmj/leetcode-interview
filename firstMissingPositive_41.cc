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
 * 假设数组长度未n，
 * 1、如果有缺失的，那么缺失的那个数字一定在1～n内
 * 2、如果数组是值也是1～n的（数组本身没有却），那么缺失的是n+1
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
  int firstMissingPositive(const vector<int>& nums) {
    if (nums.size() < 1) { return 1; }
    vector<int> flags(nums.size(), -1);
    int sz = nums.size();
    for (int i = 0; i < sz; ++i) {
      if (nums[i] < 1 || nums[i] > sz) { continue; }
      flags[nums[i]-1] = 0;
    }
    int ans = 0;
    for (int i = 0; i < sz; ++i) {
      if (flags[i] == -1) {
        ans = i + 1;
        break;
      } 
    }
    return ans > 0 ? ans : sz + 1;
  }
};

int main() {
    Solution sol;
    cout << (sol.firstMissingPositive({1,2,0}) == 3) << endl;
    cout << (sol.firstMissingPositive({3,4,-1,1}) == 2) << endl;
    cout << (sol.firstMissingPositive({7,8,9,11,12}) == 1) << endl;
    return 0;
}
