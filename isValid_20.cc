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
 * https://leetcode-cn.com/problems/valid-parentheses/
 * */
using namespace std;

typedef vector<vector<int>> VVI;
typedef vector<int> VI;
typedef long long LL;
LL MAX_LL = std::numeric_limits<LL>::max();;
int MAX_INT = std::numeric_limits<int>::max();;

class Solution {
public:
    bool isValid(string s) 
    {
        if ( s.size() < 1 )
        {
            return true;
        } 
        stack<char> sc;
        unordered_map<char, char> c2c = { {')', '('}, {']', '['}, {'}', '{'} };
        for ( size_t i = 0; i < s.size(); i++ )
        {
            auto iter = c2c.find( s[i] );
            if ( c2c.end() == iter ) 
            {
                sc.push( s[i] );
                continue;
            }
            if ( !sc.empty() && sc.top() == iter->second )
            {
                sc.pop();
                continue;
            }
            return false;
        }
        return sc.empty() == true;
    }
};

int main()
{
    Solution sol;
    string s = "({[]})";
    cout << s << " - " << ( sol.isValid(s) == true ) << endl;
    s = "({[]}";
    cout << s << " - " << ( sol.isValid(s) == false ) << endl;
    s = "()[]{}";
    cout << s << " - " << ( sol.isValid(s) == true ) << endl;
    s = "([)]";
    cout << s << " - " << ( sol.isValid(s) == false ) << endl;
    return 0;
}
