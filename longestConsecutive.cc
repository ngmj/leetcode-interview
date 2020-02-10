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
 *
 * https://leetcode-cn.com/problems/longest-consecutive-sequence/
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
    int longestConsecutive(vector<int>& nums) {
        unordered_map<int, int> val_2_cnt(nums.size());
        for (auto val: nums) {
            val_2_cnt.insert(make_pair(val, 0));
        }
        
        int ans = 0;
        for (auto val: nums) {
            int res = dfs(val, val_2_cnt);
            if (res > ans) {
                ans = res;
            }
        }
        return ans;
    }

    int dfs(int val, unordered_map<int, int> &val_2_cnt) {
        auto iter = val_2_cnt.find(val);
        if (val_2_cnt.end() == iter) {
            return 0;
        } else if (iter->second > 0) {
            return iter->second;
        }
        
        iter->second = 1 + dfs(val - 1, val_2_cnt);
        return iter->second;
    }
};

int main() {
    Solution sol;
    vector<int>  n1 = {100, 4, 200, 1, 3, 2};
    cout << sol.longestConsecutive(n1) << endl;
    return 0;
}
