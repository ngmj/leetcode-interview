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
    bool isMatch(string s, string p) {
        if (s != "" && p == "") {
            return false;
        }
        vector<vector<bool>> dp(s.size()+1, vector<bool>(p.size()+1, false));
        dp[0][0] = true;
        for (int j = 0; j < p.size(); ++j) {
            if ('*' == p[j] && j > 0 && dp[0][j-1]) {
                dp[0][j+1] = true;
                // dp[0][j] = true;
            }
        }
        for (int i = 0; i < s.size(); ++i) {
            for (int j = 0; j < p.size(); ++j) {
                if (s[i] == p[j] || '.' == p[j]) {
                    dp[i+1][j+1] = dp[i][j];
                } else if (j > 0) {
                    /*
                    if (s[i] == p[j-1]) {
                        dp[i+1][j+1] = dp[i][j-1] || dp[i][j+1] || dp[i][j];
                    }
                    */
                    if (s[i] == p[j-1]) {
                        dp[i+1][j+1] = dp[i+1][j-1] || dp[i+1][j] || dp[i][j+1];
                    } else if ('.' == p[j-1]) {
                        dp[i+1][j+1] = dp[i+1][j-1] || dp[i+1][j] || dp[i][j];
                    } else {
                        dp[i+1][j+1] = dp[i+1][j-1];
                    } 
                } else {
                    dp[i+1][j+1] = false;
                }
            }
        }
        return dp[s.size()][p.size()];
    }

    int isEqual(const string &s, const string &p, 
            const vector<vector<short>> &state, int i, int j) {
        if (j < 0) {
            return 0;
        }
        if (state[i][j] != -1) {
            return state[i][j];
        }
        if (p[j] != '.' && p[j] != '*') {
            return s[i] == p[j] ? 1 : 0;
        } else if (p[j] == '.') {
            return 1;
        }
        return isEqual(s, p, state, i, j-1);
    }
};

int main() {
    Solution sol;
    string s, p;
    s = "aaba";
    p = "ab*a*c*a";
    cout << s << ":" << p << "|" << ( sol.isMatch( s, p ) == false ) << endl;

    s = "aa";
    p = "c*a*";
    cout << s << ":" << p << "|" << ( sol.isMatch( s, p ) == true ) << endl;

    s = "ab";
    p = ".*";
    cout << s << ":" << p << "|" << ( sol.isMatch( s, p ) == true ) << endl;

    s = "aa";
    p = "a*";
    cout << s << ":" << p << "|" << ( sol.isMatch( s, p ) == true ) << endl;

    s = "aa";
    p = "a*c*a";
    cout << s << ":" << p << "|" << ( sol.isMatch( s, p ) == true ) << endl;

    s = "a";
    p = ".*";
    cout << s << ":" << p << "|" << ( sol.isMatch( s, p ) == true ) << endl;

    s = "";
    p = ".*";
    cout << s << ":" << p << "|" << ( sol.isMatch( s, p ) == true ) << endl;

    s = "a";
    p = "a.*";
    cout << s << ":" << p << "|" << ( sol.isMatch( s, p ) == true ) << endl;

    s = "";
    p = ".";
    cout << s << ":" << p << "|" << ( sol.isMatch( s, p ) == false ) << endl;

    s = "aaa";
    p = "aaaa";
    cout << s << ":" << p << "|" << ( sol.isMatch( s, p ) == false ) << endl;

    s = "aa";
    p = "a";
    cout << s << ":" << p << "|" << ( sol.isMatch( s, p ) == false ) << endl;

    s = "mississippi";
    p = "mis*is*p*.";
    cout << s << ":" << p << "|" << ( sol.isMatch( s, p ) == false ) << endl;

    s = "mississippi";
    p = "mis*is*ip*.";
    cout << s << ":" << p << "|" << ( sol.isMatch( s, p ) == true ) << endl;


    return 0;
}
