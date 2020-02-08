#include <vector>
#include <limits>
#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <stack>
#include <queue>
#include <deque>
#include <unordered_set>
#include <unordered_map>
#include "string_util.h"

/*
 * stack: top(), pop(), push(), empty()
 * queue: front(), back(), push(), pop(), empty()
 * priority_queue: top(), push(), pop(), empty()
 *  std::priority_queue<int> 默认是大根堆，
 *  std::priority_queue<int, std::vector<int>, std::greater<int> > 小根堆
 * deque: front(), back(), push_back(), pop_back, push_front, pop_front(), empty(), clear()
 *
 * iter = lower_bound(start, end, val) 返回[start, end)>=val的第一个位置（下界）
 * iter = upper_bound(start, end, val) 返回[start, end)>val的第一个位置（上界）
 * 如(11,12) lower_bound查找11，返回0；upper_bound则返回1
 *
 * https://leetcode-cn.com/problems/longest-increasing-subsequence/submissions/
 * 奇技淫巧的解法，思路是
 *  维护一个上升子序列，
 *  如果新加入的元素也是满足上升的，则add
 *  否则，二分查找到一个位置替换掉那个比当前val大的元素，以便尽可能降低当前子序列中元素值
 * 注意最后只有上升子序列长度是准确的，但是上升子序列本身未必是正确的
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
    int lengthOfLIS(vector<int>& nums) {
        vector<int> lis;
        lis.reserve(nums.size());
        for (auto &val: nums) {
            if (lis.size() < 1 || val > lis.back()) {
                lis.push_back(val);
            } else {
                // 一定得是lower_bound，考虑(4,10,4,5)
                auto iter = lower_bound(lis.begin(), lis.end(), val);
                if (lis.end() != iter) {
                    *iter = val;
                }
            }
        }
        return lis.size();
    }
};

int main() {
    Solution sol;
    vector<int> nums1 = {4,10,4,3,8,9};
    cout << sol.lengthOfLIS(nums1) << endl;
    return 0;
}
