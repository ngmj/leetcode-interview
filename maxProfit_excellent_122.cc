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
 * https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-ii/
 * 可以假设所有买点卖点都是最佳的，所以我们只需要计算利润即可
 * 比如 1,2,3,4 不用考虑何时买，何时卖，只要后一天比前一天价格高，则计入利润
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
    int maxProfit(vector<int>& prices) {
        int ans = 0;
        for (int i = 1; i < prices.size(); ++i) {
            if (prices[i] > prices[i-1]) {
                ans += prices[i] - prices[i-1];
            }            
        }
        return ans;
    }
};

int main() {
    Solution sol;
    vector<int> p1 = {7,1,5,3,6,4};
    cout << sol.maxProfit(p1) << endl;
    vector<int> p2 = {7,6,4,3,1};
    cout << sol.maxProfit(p2) << endl;
    vector<int> p3 = {1,2,3,4,5};
    cout << sol.maxProfit(p3) << endl;
    vector<int> p4 = {2,2,5};
    cout << sol.maxProfit(p4) << endl;

    return 0;
}
