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
 * */
using namespace std;

typedef vector<vector<int>> VVI;
typedef vector<int> VI;
typedef long long LL;
LL MAX_LL = std::numeric_limits<LL>::max();;
int MAX_INT = std::numeric_limits<int>::max();;

class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> ans;
        if ( n < 1 ) {
            return ans;
        }
        generateParenthesis( "", n, 0, 0, ans );
        return ans;
    }
    void generateParenthesis( const string &s, 
                              const int     n, 
                              const int     ln, 
                              const int     rn, 
                              vector<string> &ans ) {
        if ( s.size() == 2*n ) {
            ans.push_back( s );
            return;
        }

        if ( ln > rn ) {
            generateParenthesis( s + ')', n, ln, rn + 1, ans );
        }
        if ( ln < n ) {
            generateParenthesis( s + '(', n, ln + 1, rn, ans );
        }
    }
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
