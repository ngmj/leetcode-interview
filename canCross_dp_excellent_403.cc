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
 * https://leetcode-cn.com/problems/frog-jump/
 * dp + hashset，时间复杂度O(lgn*n^2) 或者O(n^2)
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

const static vector<int> direction = {-1, 0, 1};

// 时间复杂度O(lgn*n^2)
class Solution {
public:
    bool canCross(vector<int>& stones) {
        if (stones.size() < 2) {
            return true;
        }

        // dp[i]表示跳到第i个石头 所有可能的前一跳的步数
        // NOTE: i是下标
        vector<unordered_set<int>> dp(stones.size(), unordered_set<int>(stones.size()));
        dp[0].insert(0);

        for (int i = 0; i < stones.size(); ++i) {
            auto &stepSet = dp[i];
            for (auto s: stepSet) {
                for (auto d: direction) {
                    int nextStep = s + d;
                    if (nextStep > 0) {
                        int val = stones[i] + nextStep;
                        auto iter = lower_bound(stones.begin() + i + 1, stones.end(), val);
                        if (stones.end() != iter && *iter == val) {
                            dp[iter - stones.begin()].insert(nextStep);
                        }
                    }
                    
                }
            }
        }

        return dp[stones.size()-1].size() > 0;
    }
};

// 时间复杂度O(n^2)，用haspmap替换二分查找
class Solution2 {
public:
    bool canCross(vector<int>& stones) {
        if (stones.size() < 2) {
            return true;
        }

        // dp[i]表示跳到第i个石头 所有可能的前一跳的步数
        // NOTE: i表示val
        unordered_map<int, unordered_set<int>> dp(stones.size());
        for (auto val: stones) {
            dp.insert(make_pair(val, unordered_set<int>(stones.size())));
        }
        dp[stones[0]].insert(0);

        for (auto val: stones) {
            for (auto s: dp[val]) {
                for (auto d: direction) {
                    int nextStep = s + d;
                    if (nextStep > 0) {
                        int nextVal = val + nextStep;
                        /*
                        auto iter = lower_bound(stones.begin() + i + 1, stones.end(), val);
                        if (stones.end() != iter && *iter == val) {
                            dp[iter - stones.begin()].insert(nextStep);
                        }*/
                        // 用hashmap查找代替了二分查找
                        auto iter = dp.find(nextVal);
                        if (dp.end() != iter) {
                            iter->second.insert(nextStep);
                        }
                    }
                }
            }
        }

        return dp[stones[stones.size()-1]].size() > 0;
    }
};

int main() {
    // Solution sol;
    Solution2 sol;
    vector<int> s1 = {0,1,3,5,6,8,12,17};
    cout << sol.canCross(s1) << endl;
    vector<int> s2 = {0,1,2,3,4,8,9,11};
    cout << sol.canCross(s2) << endl;
    return 0;
}
