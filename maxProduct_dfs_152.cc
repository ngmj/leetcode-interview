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
 * 采用dfs求解
 *  会超时，但是为了练习，必须会用recursion求解
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
        this->ans = MIN_INT;
        dfs(nums, 0, 1);
        return this->ans;
    }

    void dfs(vector<int>& nums, int i, int res) {
        if (i >= nums.size()-1) {
            this->ans = max(this->ans, res*nums[i]);
            return;
        }

        dfs(nums, i+1, 1);
        // 每次选择当前值相乘时，都要记录比较下
        this->ans = max(this->ans, res*nums[i]);
        dfs(nums, i+1, res*nums[i]);
    }
private:
    int ans;
};

int main() {
    Solution sol;
    vector<int> p1 = {2, 3, -2, 4};
    cout << sol.maxProduct(p1) << endl;
    vector<int> p2 = {-2, 0, -1};
    cout << sol.maxProduct(p2) << endl;
    return 0;
}
