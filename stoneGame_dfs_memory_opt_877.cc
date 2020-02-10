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
 * dfs，记忆搜索，时间复杂度O(n^2)
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

typedef pair<int, int> AB;
inline int diff_AB(AB &p) {
    return p.first - p.second;
}

class Solution {
public:
    bool stoneGame(vector<int>& piles) {
        A = 0, B = 0;
        vector<vector<AB>> mm(piles.size() + 1, vector<AB>(piles.size() + 1, AB()));
        AB ans = dfs(piles, mm, 0, piles.size() - 1);
        return ans.first > ans.second;
    }

    AB dfs(vector<int>& piles, vector<vector<AB>> &mm, int s, int e) {
        if (e - s <= 1) {
            int val1 = piles[s];
            int val2 = piles[e];
            mm[s][e] = val1 < val2 ? make_pair(val2, val1) : make_pair(val1, val2);
            return mm[s][e]; 
        }

        vector<AB> result(3, AB());

        result[0] = mm[s + 2][e];
        if (result[0].first < 1) {
            result[0] = dfs(piles, mm, s + 2, e);
        }
        result[0].first += max(piles[s], piles[s+1]);
        result[0].second += min(piles[s], piles[s+1]);

        result[1] = mm[s + 1][e - 1];
        if (result[1].first < 1) {
            result[1] = dfs(piles, mm, s + 1, e - 1);
        }
        result[1].first += max(piles[s], piles[e]);
        result[1].second += min(piles[s], piles[e]);

        result[2] = mm[s][e - 2];
        if (result[2].first < 1) {
            result[2] = dfs(piles, mm, s, e - 2);
        }
        result[2].first += max(piles[e-1], piles[e]);
        result[2].second += min(piles[e-1], piles[e]);
        
        AB ans;
        for (auto res: result) {
            if (diff_AB(res) > diff_AB(ans)) {
                ans = res;
            }
        }

        mm[s][e] = ans;
        return ans; 
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
