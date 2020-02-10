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
 * https://leetcode-cn.com/problems/frog-jump/
 * dfs，时间复杂度O(lgn*n^2)
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

const static vector<int> directions = {-1, 0, 1};
class Solution {
public:
    bool canCross(vector<int>& stones) {
        if (stones.size() < 2) {
            return true;
        }
        // 0表示走不通，1表示走得通，-1表示没走过
        vector<vector<int>> mm(stones.size(), vector<int>(stones.size(), -1));
        return dfs(stones, mm, -1, 0, "");
    }

    // 站在第i个石头上，上一个石头是pre，求接下来能否跳完
    bool dfs(vector<int>& stones, vector<vector<int>> &mm, int pre, int i, string path) {
        path += "->" + to_string( stones[i] );
        // 青蛙只要跳到最后一个石头就成功了，无需再往后跳了
        if (i >= stones.size() - 1) {
            cout << path << "#" << endl;
            return true;
        }

        if (1 == mm[pre+1][i]) {
            return true;
        } else if (0 == mm[pre+1][i]) {
            return false;
        }

        int diff = 0;
        if (pre > -1) {
            diff = stones[i] - stones[pre];
        }

        for (auto s: directions) {
            int nextStep = diff + s;
            if (nextStep < 1) {
                continue;
            }
            
            int nextStone = stones[i] + nextStep;
            auto iter = lower_bound(stones.begin() + i + 1, stones.end(), nextStone);
            if (stones.end() != iter && *iter == nextStone) {
                if (dfs(stones, mm, i, iter - stones.begin(), path)) {
                    mm[i+1][iter - stones.begin()] = 1;
                    return true;
                }
            }
        }

        cout << path << endl;
        mm[pre+1][i] = 0;
        return false;
    }
};

int main() {
    Solution sol;
    vector<int> s1 = {0,1,3,5,6,8,12,17};
    cout << sol.canCross(s1) << endl;
    vector<int> s2 = {0,1,2,3,4,8,9,11};
    cout << sol.canCross(s2) << endl;
    return 0;
}
