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
 * priority_queue: top(), pop(), push(), empty()
 *  std::priority_queue<int> 默认是大根堆，
 *  std::priority_queue<int, std::vector<int>, std::greater<int> > 小根堆
 * queue: front(), back(), push(), pop(), empty()
 * deque: front(), back(), push_back(), pop_back, push_front, pop_front(), empty(), clear()
 *
 * iter = lower_bound(start, end, val) 返回[start, end)>=val的第一个位置（下界）
 * iter = upper_bound(start, end, val) 返回[start, end)>val的第一个位置（上界）
 * 如(11,12) lower_bound查找11，返回0；upper_bound则返回1
 * https://leetcode-cn.com/problems/next-greater-element-ii/
 *
 * 维护非递归上升栈（即5 3 3 1这样的），入栈的是元素下标
 * 这道题含义说得不够清楚，是真正的循环数组，比如[5,4,3,2,1]，输出的是[-1,5,5,5,5]
 * 第一轮处理，正常按照非递归上升栈出入数组，
 * 第二轮处理，栈内元素，如果不是循环数组，那么此时栈内元素应该都是-1，但是是循环的，所以除了栈底的元素对应-1，剩下都是栈低
 * 
 * 上面思路是错的，考虑[1,2,3,2,1]
 * 老老实实再来一轮循环处理数组把，此时不用压入栈，只要val > 栈顶元素，则出栈
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
    vector<int> nextGreaterElements(vector<int>& nums) {
        if (nums.size() < 1) {
            return vector<int>();
        }

        vector<int> ans(nums.size(), -1);
        stack<int> ordered_stack;
        int max_val = MIN_INT;
        for (int i = 0; i < nums.size(); ++i) {
            while (!ordered_stack.empty() && nums[ordered_stack.top()] < nums[i]) {
                ans[ordered_stack.top()] = nums[i];
                ordered_stack.pop();
            }
            ordered_stack.push(i);
            if (nums[i] > max_val) {
                max_val = nums[i];
            }
        }

        // 细节很重要，比如考虑[1,1,1]这样的数组，最大值有可能等于栈内元素
        for (auto val: nums) {
            while (!ordered_stack.empty() && nums[ordered_stack.top()] < val) {
                ans[ordered_stack.top()] = val;
                ordered_stack.pop();
            }
            if (val == max_val) {
                break;
            }
        }
        return ans;
    }
};

int main() {
    Solution sol;
    vector<int> n1 = {1,2,3};
    cout << VectorToString(sol.nextGreaterElements(n1)) << endl;
    vector<int> n2 = {1,2,3,4,3};
    cout << VectorToString(sol.nextGreaterElements(n2)) << endl;
    vector<int> n3 = {5,4,3,2,1};
    cout << VectorToString(sol.nextGreaterElements(n3)) << endl;
    vector<int> n4 = {1,1,1,1,1};
    cout << VectorToString(sol.nextGreaterElements(n4)) << endl;
    return 0;
}
