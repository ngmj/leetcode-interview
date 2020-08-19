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
 * https://leetcode-cn.com/problems/powx-n/
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
  double myPow(double x, int n) {
    if (abs(x - 1.00000) < .000001) { return x; }
    else if (abs(x - 0.00000) < .000001) { return x; }
    long pn = n < 0 ? -1l*n : n;
    double px = x < 0 ? -1*x : x;
    unordered_map<long, double> stats;
    double ans = dfs(px, pn / 2, stats) * dfs(px, pn - pn / 2, stats);
    if (n < 0) {
      ans = 1.0 / ans;
    }
    if (x < 0 && pn % 2) {
      ans = -1 * ans;
    }
    return ans;
  }
  
  double dfs(double x, long n, unordered_map<long, double> &stats) {
    if (n == 0) { return 1; }
    else if (n == 1) { return x; }

    auto iter = stats.find(n);
    if (stats.end() != iter) { return iter->second; }
    double ans = dfs(x, n / 2, stats) * dfs(x, n - n / 2, stats);
    stats[n] = ans;
    return ans;
  }
};

int main() {
    Solution sol;
    cout << (abs(sol.myPow(2.00000, 10) - 1024.00000) < 0.000001) << endl;
    cout << (abs(sol.myPow(2.10000, 3) - 9.26100) < 0.000001) << endl;
    cout << (abs(sol.myPow(2.00000, -2) - 0.25000) < 0.000001) << endl;
    return 0;
}
