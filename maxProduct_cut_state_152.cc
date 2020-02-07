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
 * https://leetcode-cn.com/problems/maximum-product-subarray/
 * 一种朴素的想法，p[i]表示以i为下标的最优值，则p[i] = max(p[i-1]*val[i], val[i])
 *  但考虑到是相乘的形式，所以当前值的正负会影响到状态值，如果用上面状态转移 -1(-1), 2(2), -2(-2，但实际上应该是4)，
 *  所以p[i].max p[i].min搞两个状态值
 *  （这一类题，如果是满足单调性的，如连续子序列和，那么只要一个状态值和当前值比较即可；
 *  如果不是满足单调性的，那么就得考虑多个状态值的情况）
 * */
using namespace std;

typedef vector<vector<int>> VVI;
typedef vector<int> VI;
typedef unsigned int UI;
typedef long long LL;
typedef unsigned long long ULL;
LL MAX_LL = std::numeric_limits<LL>::max();;
LL MIN_LL = std::numeric_limits<LL>::min();;
int MAX_INT = std::numeric_limits<int>::max();;
int MIN_INT = std::numeric_limits<int>::min();;

class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int ans = nums[0]; 
        int max = nums[0];
        int min = nums[0];
        for (int i = 1; i < nums.size(); i++) {
            int val = nums[i];
            if (val > 0) {
                max = std::max(max*val, val); 
                min = std::min(min*val, val); 
            } else {
                int tmp = max;
                max = std::max(min*val, val); 
                min = std::min(tmp*val, val); 
            }

            if (max > ans) {
                ans = max;
            }
        }
        return ans;
    }
};

int main() {
    Solution sol;
    vector<int> p0 = {-4, -3, -2};
    cout << sol.maxProduct(p0) << endl;
    vector<int> p1 = {2, 3, -2, 4};
    cout << sol.maxProduct(p1) << endl;
    vector<int> p2 = {-2, 0, -1};
    cout << sol.maxProduct(p2) << endl;
    return 0;
}
