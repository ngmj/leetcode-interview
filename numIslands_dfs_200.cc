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
 *
 * iter = lower_bound(start, end, val) 返回[start, end)>=val的第一个位置（下界）
 * iter = upper_bound(start, end, val) 返回[start, end)>val的第一个位置（上界）
 * 如(11,12) lower_bound查找11，返回0；upper_bound则返回1
 *
 * https://leetcode-cn.com/problems/number-of-islands/
 * dfs
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

vector<int> dx = {-1, 1, 0, 0};
vector<int> dy = {0, 0, -1, 1};
class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        if (grid.size() < 1 || grid[0].size() < 1) {
            return 0;
        }
        int m = grid.size();
        int n = grid[0].size();
        int ans = 0;
        vector<vector<bool>> visisted(m, vector<bool>(n, false));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dfs(grid, visisted, i, j)) {
                    ans++;
                }
            }
        }
        return ans;
    }

    bool dfs(vector<vector<char>>& grid, vector<vector<bool>>& visisted, int i, int j) {
        if (i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size() 
                || '0' == grid[i][j] || visisted[i][j]) {
            return false;
        }

        visisted[i][j] = true;
        for (int d = 0; d < 4; ++d) {
            dfs(grid, visisted, i+dx[d], j+dy[d]);
        }
        return true;
    }
};

int main() {
    Solution sol;
    vector<vector<char>> g1 = { {'1', '1', '1', '1', '0'},
                                {'1', '1', '0', '1', '0'},
                                {'1', '1', '0', '0', '0'},
                                {'0', '0', '0', '0', '0'} };
    cout << sol.numIslands(g1) << endl;
    return 0;
}
