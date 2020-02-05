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
 * https://leetcode-cn.com/problems/triangle/
 * 从上往下，从右往左扫描
 * for (i : 1 ~ m) {
 *  for (j : n ~ 1) {
 *      opt[j] = min(opt[j-1], opt[j]) + val[i][j]
 *  }
 *  opt[0] = opt[0] + val[i][0]
 * }
 * */
using namespace std;

typedef vector<vector<int>> VVI;
typedef vector<int> VI;
typedef long long LL;
LL MAX_LL = std::numeric_limits<LL>::max();;
int MAX_INT = std::numeric_limits<int>::max();;

class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int m = triangle.size();
        if (m < 1) {
            return 0;
        }
        int n = triangle[m-1].size();
        if (n < 1) {
            return 0;
        }
        
        vector<LL> opt(m, 0);
        opt[0] = triangle[0][0];
        for (int i = 1; i < m; ++i) {
            // 更新当前行最后一个元素
            int n = triangle[i].size();
            opt[n-1] = opt[n-2] + triangle[i][n-1];
            for (int j = n-2; j > 0; --j) {
                opt[j] = min(opt[j-1], opt[j]) + triangle[i][j];
            }
            // 更新当前行第一个元素
            opt[0] = opt[0] + triangle[i][0];
        }

        int ans = MAX_INT;
        for (auto val: opt) {
            if (val < ans) {
                ans = val;
            }
        }
        return ans;
    }
};

int main() {
    Solution sol;
    vector<vector<int>> triangle = {
            {2},
            {3,4},
            {6,5,7},
            {4,1,8,3}};
    cout << sol.minimumTotal(triangle) << endl;
    return 0;
}
