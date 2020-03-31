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
    vector<string> generateParenthesis(int n) {
        string s = "";
        n_ = n;
        ans_.reserve(100);
        dfs(s, 0, 0);
        return move(ans_);
    }

    void dfs(string s, int l, int r) {
        if (l < r || l > n_ || r > n_) {
            return;
        } else if (l == n_ && r == n_) {
            ans_.push_back(s);
        }
        dfs(s+")", l, r+1);
        dfs(s+"(", l+1, r);
    }
private:
    int n_;
    vector<string> ans_;
};

int main() {
    Solution sol;
    int n = 0;
    vector<string> ans;
    
    n = 0;
    ans = sol.generateParenthesis( n );
    cout << n << " | " << VectorToString( ans ) << endl; 
    
    n = 1;
    ans = sol.generateParenthesis( n );
    cout << n << " | " << VectorToString( ans ) << endl; 
    
    n = 2;
    ans = sol.generateParenthesis( n );
    cout << n << " | " << VectorToString( ans ) << endl; 
    
    n = 3;
    ans = sol.generateParenthesis( n );
    cout << n << " | " << VectorToString( ans ) << endl; 
    
    n = 4;
    ans = sol.generateParenthesis( n );
    cout << n << " | " << VectorToString( ans ) << endl; 
 
    return 0;
}
