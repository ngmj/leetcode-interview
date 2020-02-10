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
 * https://leetcode-cn.com/problems/next-greater-element-i/
 * 寻找下一个比当前元素大的值下标，
 * 维护一个单调非上升栈
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
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        stack<int> s;
        unordered_map<int, int> val_2_val(nums2.size());
        for (auto val: nums2) {
            if (s.empty()) {
                 s.push(val);
                 continue;
            }

            while (!s.empty() && s.top() < val) {
                val_2_val.insert(make_pair(s.top(), val));
                s.pop();
            }
            s.push(val);
        }
        
        vector<int> ans(nums1.size(), -1);
        for (int i = 0; i < nums1.size(); ++i) {
            auto iter = val_2_val.find(nums1[i]);
            if (val_2_val.end() == iter) {
                continue;
            }
            ans[i] = iter->second; 
        }
        return ans;
    }
};

int main() {
    Solution sol;
    vector<int> n1 = {4,1,2};
    vector<int> n2 = {1,3,4,2};
    cout << VectorToString(sol.nextGreaterElement(n1, n2)) << endl;
    return 0;
}
