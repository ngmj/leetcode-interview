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
    string longestPalindrome(string s) {
        if (s.size() < 2) {
            return s;
        } 
        int index = 0, ans = 1;
        vector<vector<bool>> state(s.size(), vector<bool>(s.size()+1, false));
        state[0][1] = true;
        state[0][2] = false; 
        for (int i = 1; i < s.size(); ++i) {
            state[i][1] = true;
            state[i][2] = s[i] == s[i-1];
            if (state[i][2]) {
                index = i;
                ans = 2;
            }
        }
        for (int l = 3; l <= s.size(); ++l) {
            for (int i = l-1; i < s.size(); ++i) {
                state[i][l] = state[i-1][l-2] && s[i-l+1] == s[i];
                if (state[i][l]) {
                    ans = l;
                    index = i;
                }
            }
        }
        return s.substr(index-ans+1, ans);
    }
};

int main() {
    Solution sol;
    string s = "";
    s = "zzzz";
    cout << s << "|" << ( sol.longestPalindrome( s ) == s ) << endl;

    s = "bb";
    cout << s << "|" << ( sol.longestPalindrome( s ) == "bb" ) << endl;

    s = "cbbd";
    cout << s << "|" << ( sol.longestPalindrome( s ) == "bb" ) << endl;

    s = "babad";
    cout << s << "|" << ( sol.longestPalindrome( s ) == "bab" || sol.longestPalindrome( s ) == "aba" ) << endl;

    return 0;
}
