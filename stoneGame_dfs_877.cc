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
 * https://leetcode-cn.com/problems/stone-game/
 * dfs，时间复杂度O(4^n)
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
    bool stoneGame(vector<int>& piles) {
        A = 0, B = 0;
        return dfs(piles, 0, piles.size() - 1);
    }

    bool dfs(vector<int>& piles, int s, int e) {
        if (e < s) {
            return A > B;
        }

        A += piles[s];
        B += piles[s+1];
        bool ff = dfs(piles, s + 2, e);
        B -= piles[s+1];

        B += piles[e];
        bool fl = dfs(piles, s + 1, e - 1);
        B -= piles[e];
        A -= piles[s];

        A += piles[e];
        B += piles[e-1];
        bool ll = dfs(piles, s, e - 2);
        B -= piles[e-1];
        
        B += piles[s];
        bool lf = dfs(piles, s + 1, e - 1);
        B -= piles[s];
        A -= piles[e];

        return ff || fl || ll || lf;
    }
private:
    int A, B;
};

int main() {
    Solution sol;
    vector<int> p1 = {5,3,4,5};
    cout << sol.stoneGame(p1) << endl;
    return 0;
}
