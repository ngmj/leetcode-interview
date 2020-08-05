#include <vector>
#include <limits>
#include <iostream>
#include <algorithm>
#include <map>
#include <list>
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
 * list: push_back, push_front, insert(pos, val), front, remove(val), erase(iter)
 *
 * iter = lower_bound(start, end, val) 返回[start, end)>=val的第一个位置（下界）
 * iter = upper_bound(start, end, val) 返回[start, end)>val的第一个位置（上界）
 * 如(11,12) lower_bound查找11，返回0；upper_bound则返回1
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

struct Point {
  int i = -1;
  int j = -1;
  
  Point(int ii, int jj) : i(ii), j(jj) {}

  bool operator<(const Point &p) const {
    return i < p.i || (i == p.i && j < p.j);
  }
};

class Solution {
public:
  int maxAreaOfIsland(vector<vector<int>>& grid) {
    set<Point> visited;
    int ans = 0;
    if (grid.size() < 1) {
      return ans;
    }
    int Y = grid.size(), X = grid[0].size();
    for (int i = 0; i < X; ++i) {
      for (int j = 0; j < Y; ++j) {
        if (0 == visited.count(Point(i, j))) {
          int rst = dfs(grid, j, i, Y, X, visited);
          ans = rst > ans ? rst: ans;
        }      
      }
    }
    return ans;
  }

  int dfs(vector<vector<int>>& grid, int j, int i, int Y, int X, set<Point> &visited) {
    if (j < 0 || j >= Y || i < 0 || i >= X || 0 == grid[j][i] || visited.count(Point(i, j))) {
      return 0;
    }
    visited.insert(Point(i, j));
    if (grid[j][i]) {
      int rst1 = dfs(grid, j+1, i, Y, X, visited);
      int rst2 = dfs(grid, j-1, i, Y, X, visited);
      int rst3 = dfs(grid, j, i+1, Y, X, visited);
      int rst4 = dfs(grid, j, i-1, Y, X, visited);
      return rst1 + rst2 + rst3 + rst4 + 1;
    }
    return 0;
  }
};

int main() {
    Solution sol;
    vector<vector<int>> grid1 = {{0,1,1,1,0}};
    cout << (sol.maxAreaOfIsland(grid1) == 3) << endl;
    vector<vector<int>> grid2 = {{0,0,1,0,0,0,0,1,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,1,1,1,0,0,0},
                                 {0,1,1,0,1,0,0,0,0,0,0,0,0},
                                 {0,1,0,0,1,1,0,0,1,0,1,0,0},
                                 {0,1,0,0,1,1,0,0,1,1,1,0,0},
                                 {0,0,0,0,0,0,0,0,0,0,1,0,0},
                                 {0,0,0,0,0,0,0,1,1,1,0,0,0},
                                 {0,0,0,0,0,0,0,1,1,0,0,0,0}};
    cout << (sol.maxAreaOfIsland(grid2) == 6) << endl;
    return 0;
}
