#include <iostream>
#include <vector>

using namespace std;
/*
 * https://leetcode-cn.com/problems/longest-palindromic-substring/solution/zui-chang-hui-wen-zi-chuan-by-leetcode/
 * 动态规划求解
 * res[i, j] 表示s[i~j]是否是回文
 * res[i, j] = res[i+1, j-1] && s[i] == s[j]
 * 初始化一个回文长度的即res[i, i] = true
 * 初始化两个回文长度的即res[i, i+1] = s[i] == s[i+1]
 * 以此类推求res[i, j]
 * */

class Solution {
public:
    string longestPalindrome(string s) {
        if ( s.size() < 1 )
        {
            return "";
        }

        vector<vector<bool> > res( s.size(), vector<bool>( s.size(), false ) );
        int ansIdx = 0;
        int ansLen = 1;
        for ( int i = 0; i < s.size(); i++ )
        {
            res[i][i] = true;
        }

        for ( int i = 0; i < s.size() - 1; i++ )
        {
            res[i][i+1] = s[i] == s[i+1];
            if ( res[i][i+1] )
            {
                ansIdx = i;
                ansLen = 2;
            }
        }

        for (int len = 3; len <= s.size(); len++)
        {
            for ( int i = 0; i < s.size() - len + 1; i++ )
            {
                res[i][i+len-1] = res[i+1][i+len-2] && s[i] == s[i+len-1];
                if ( res[i][i+len-1] )
                {
                    ansLen = len;
                    ansIdx = i;
                }
            }
        }
        return s.substr(ansIdx, ansLen);
    }
};

int main()
{
    string s;
    Solution sol;

    s = "bb";
    cout << s << "|" << ( sol.longestPalindrome( s ) == "bb" ) << endl;

    s = "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz";
    cout << s << "|" << ( sol.longestPalindrome( s ) == s ) << endl;

    s = "cbbd";
    cout << s << "|" << ( sol.longestPalindrome( s ) == "bb" ) << endl;

    s = "babad";
    cout << s << "|" << ( sol.longestPalindrome( s ) == "bab" || sol.longestPalindrome( s ) == "aba" ) << endl;

    return 0;
}
