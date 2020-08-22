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
 * https://leetcode-cn.com/classic/problems/ba-shu-zu-pai-cheng-zui-xiao-de-shu-lcof/description/
 * 冒泡排序，比较a > b？？（ab和ba哪个更大），如34 3，则3应该是大于34
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

struct Comp{
  bool operator()(const string &a, const string &b) {
    string sa = a + b;
    string sb = b + a;
    return sa < sb;
  }
};
class Solution {
public:
  string minNumber(const vector<int>& nums) {
    vector<string> nums_str(nums.size(), "");
    for (int i = 0; i < nums.size(); ++i) {
      nums_str[i] = to_string(nums[i]);
    }
    sort(nums_str.begin(), nums_str.end(), Comp());
    string ans = "";
    for (auto &s: nums_str) {
      ans.append(s);
    }
    return ans;
  }
};

int main() {
    Solution sol;
    cout << (sol.minNumber({10,2}) == "102") << endl;
    cout << (sol.minNumber({3,30,34,5,9}) == "3033459") << endl;
    return 0;
}
