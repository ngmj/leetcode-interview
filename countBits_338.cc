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
 * https://leetcode-cn.com/problems/counting-bits/
 * 动态规划，x & (x - 1)表示消掉最后一个1，所以count[x] = count[x & (x - 1)] + 1
 * */
using namespace std;

typedef vector<vector<int>> VVI;
typedef vector<int> VI;
typedef long long LL;
LL MAX_LL = std::numeric_limits<LL>::max();;
int MAX_INT = std::numeric_limits<int>::max();;

class Solution {
public:
    vector<int> countBits(int num) {
        vector<int> ans(num + 1, 0);
        for (int i = 1; i <= num; i++) {
            ans[i] = ans[i & (i -1 )] + 1;
        }
        return ans;
    }
};

int main() {
    Solution sol;
    cout << VectorToString(sol.countBits(2)) << endl;
    cout << VectorToString(sol.countBits(5)) << endl;
    return 0;
}
