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
 * dp + 剪枝，时间复杂度O(lgn*n^2)
 * 性能很差
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
class Solution {
public:
    bool canCross(vector<int>& stones) {
        if (stones.size() < 2) {
            return true;
        }

        vector<vector<bool>> dp(stones.size(), vector<bool>(stones.size(), false));
        dp[0][0] = true;
        dp[0][1] = stones[1] - stones[0] == 1 ? true : false;
        int maxStep = 1;
        for (int j = 2; j < stones.size(); ++j) {
            if (maxStep + 1 < stones[j] - stones[j-1]) {
                return false; // 无论如何都无法跳过当前坑
            }
            for (int i = 1; i < j; ++i) {
                for (auto d: direction) {
                    int val = 2*stones[i] - stones[j] + d;
                    auto iter = lower_bound(stones.begin(), stones.begin() + i - 1, val);
                    if (stones.end() != iter && val == *iter) {
                        dp[i][j] = dp[iter - stones.begin()][i];
                        if (dp[i][j]) {
                            maxStep = max(maxStep, stones[j] - stones[i]);
                        }
                        cout << "(" << i << "," << j << ")  ->  (" 
                            << (iter - stones.begin()) << ", " << i << ")" 
                            << ", maxStep " << maxStep << endl;
                    }
                }
            }
        }

        for (int i = 0; i < stones.size(); ++i) {
            if (dp[i][stones.size() - 1]) {
                return true;
            }
        }
        return false;
    }
};

int main() {
    Solution sol;
    vector<int> s1 = {0,1,3,5,6,8,12,17};
    cout << sol.canCross(s1) << endl;
    vector<int> s2 = {0,1,2,3,4,8,9,11};
    cout << sol.canCross(s2) << endl;
    return 0;
}
