#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int longestValidParentheses(string s) {
        int ans = 0;
        vector<int> dp( s.size(), 0 );
        for ( size_t i = 1; i < s.size(); i++ )
        {
            if ( s[i] == '(' )
            {
                continue;
            }
            if ( s[i-1] == '(' ) // xxxx()
            {
                if ( i > 1 )
                {
                    dp[i] = dp[i-2] + 2;
                } else
                {
                    dp[i] = 2;
                }
            } else  // xxxx))
            {
                int idx = i - 1 - dp[i-1];
                if ( idx > -1 && s[idx] == '(' )
                {
                    if ( idx > 0 )
                    {
                        dp[i] = dp[i-1] + dp[idx-1] + 2;
                    } else
                    {
                        dp[i] = dp[i-1] + 2;
                    }
                }
            }

            if ( dp[i] > ans )
            {
                ans = dp[i];
            }
        }
        return ans;
    }
};

int main()
{
    string s;
    Solution sol;

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
