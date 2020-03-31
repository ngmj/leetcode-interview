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

class Solution {
public:
    int longestValidParentheses(string s) {
        vector<int> dp(s.size(), 0);
        int ans = 0;
        for (int i = 1; i < s.size(); ++i) {
            if ('(' == s[i]) { // ...(
                continue;
            } else if (')' == s[i-1]) { // ...))
                int pre = i - dp[i-1] - 1;
                if (pre > -1 && '(' == s[pre]) {
                    // [pre-1] (....) 特别留意这块 
                    if (pre > 0) {
                        dp[i] = dp[pre-1] + dp[i-1] + 2;
                    } else {
                        dp[i] = dp[i-1] + 2;
                    }
                }
            } else if (i > 1) { // ...()
                dp[i] = dp[i-2] + 2;
            } else { // ()
                dp[i] = 2;
            }
            if (dp[i] > ans) {
                ans = dp[i];
            }
        }
        return ans;
    }
};

int main() {
    Solution sol;    
    string s = "";
    s = "()(()";
    cout << s << "|" << ( sol.longestValidParentheses( s ) == 2 ) << endl;

    s = "()()";
    cout << s << "|" << ( sol.longestValidParentheses( s ) == 4 ) << endl;

    s = "(()";
    cout << s << "|" << ( sol.longestValidParentheses( s ) == 2 ) << endl;

    s = ")()())";
    cout << s << "|" << ( sol.longestValidParentheses( s ) == 4 ) << endl;

    s = "(";
    cout << s << "|" << ( sol.longestValidParentheses( s ) == 0 ) << endl;
    
    s = ")";
    cout << s << "|" << ( sol.longestValidParentheses( s ) == 0 ) << endl;

    s = "(()()())";
    cout << s << "|" << ( sol.longestValidParentheses( s ) == 8 ) << endl;
    return 0;
}
