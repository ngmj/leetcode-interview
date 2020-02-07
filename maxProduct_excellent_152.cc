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
 * 参考题解，思路如下
 * 仔细想一个这个题在考什么，我们先把题目简单化，以方便理清思路。
 * 如果给定的数组全部都是正数，那么子数组最大的乘积是多少呢？很简单，把所有的数字相乘即可。
 * 但如果给定的数组存在负数呢，似乎这就变得麻烦些了。
 * 我们继续简化问题，如果出现了偶数个负数呢？此时最大乘积又变成了，把所有的数字相乘即可。
 * 所以，其实我们需要解决的问题就是，当出现奇数个负数的时候该怎么办。
 * 乘积理论上乘的数越多越好，但前提是必须保证负数是偶数个。
 * 那么对于一个有奇数个负数的数组，基于上边的原则，最大数的取值情况就是两种。
 * 剔除最左边那个含负数的数组，或者剔除右边那个含负数的数组
 *
 * 该题一定满足下面性质
 * 1、一定包含最左边元素的序列，或一定包含最右边元素的序列（两轮扫描）
 * 2、对于包含0的情况，每次遇到0，则重置起始元素值（将max置为1）
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
        int ans = MIN_INT;
        int max = 1;
        // 从左到右扫描
        for (int i = 0; i < nums.size(); ++i) {
            max = max*nums[i];
            ans = std::max(max, ans);
            if (0 == nums[i]) {
                max = 1;
            }
        }

        max = 1;
        // 从右到左扫描
        for (int i = nums.size()-1; i >= 0; --i) {
            max = max*nums[i];
            ans = std::max(max, ans);
            if (0 == nums[i]) {
                max = 1;
            }
        }
        return ans;
    }
};

int main() {
    Solution sol;
    vector<int> p1 = {2, 3, -2, 4};
    cout << sol.maxProduct(p1) << endl;
    vector<int> p2 = {-2, 0, -1};
    cout << sol.maxProduct(p2) << endl;
    return 0;
}
