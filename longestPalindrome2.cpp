#include <iostream>
#include <vector>

using namespace std;
/*
 * https://leetcode-cn.com/problems/longest-palindromic-substring/solution/zui-chang-hui-wen-zi-chuan-by-leetcode/
 * 暴力计算（容易超时）
 * */

class Solution {
public:
    string longestPalindrome(string s) {
        if ( s.size() < 1 )
        {
            return "";
        }

        int idx = 0;
        int len = 1;

        for ( int i = 0; i < s.size() - 1; i++ )
        {
            for ( int j = s.size() - 1; j >= i; j-- )
            {
                int tmpLen = j - i + 1;
                if ( check(s, j, tmpLen) )
                {
                    if ( tmpLen > len )
                    {
                        len = tmpLen;
                        idx = i;
                    }

                    if ( len == s.size() )
                    {
                        break;
                    }
                }

                if ( len == s.size() )
                {
                    break;
                }
            }
        }
        return s.substr(idx, len);
    }

    bool check( const string &s,
                int          idx,
                int          len )
    {
        // i 指向尾部，j指向头部
        for ( int i = idx, j = idx - len + 1; j <= i; i--, j++ )
        {
            if ( s[i] != s[j] )
            {
                return false;
            }
        }
        return true;
    }
};

int main()
{
    string s;
    Solution sol;

    s = "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz";
    cout << s << "|" << ( sol.longestPalindrome( s ) == s ) << endl;

    s = "bb";
    cout << s << "|" << ( sol.longestPalindrome( s ) == "bb" ) << endl;

    s = "cbbd";
    cout << s << "|" << ( sol.longestPalindrome( s ) == "bb" ) << endl;

    s = "babad";
    cout << s << "|" << ( sol.longestPalindrome( s ) == "bab" || sol.longestPalindrome( s ) == "aba" ) << endl;

    return 0;
}
