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
 * 从低往上，从左往右扫描
 * opt[0~n-1] = val[m-1][0~n-1]
 * for (i : m-2 ~ 0) {
 *  for (j : 0 ~ n-1) {
 *      opt[j] = min(opt[j], opt[j+1]) + val[i][j]
 *  }
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
        
        vector<int> opt = triangle[m-1];
        for (int i = m-2; i >= 0; --i) {
            n = triangle[i].size();
            for (int j = 0; j < n; ++j) {
                opt[j] = min(opt[j], opt[j+1]) + triangle[i][j];
            }
        }

        return opt[0];
    }
};

int main() {
    Solution sol;
    vector<vector<int>> triangle1 = {{1}, {2, 3}};
    cout << sol.minimumTotal(triangle1) << endl;

    vector<vector<int>> triangle3 = {{2},{3,4},{6,5,7},{4,1,8,3}};
    cout << sol.minimumTotal(triangle3) << endl;

    vector<vector<int>> triangle2 = {
            {2},
            {3,4},
            {6,5,7},
            {4,1,8,3}};
    cout << sol.minimumTotal(triangle2) << endl;
    return 0;
}
