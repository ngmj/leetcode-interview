#include <iostream>
#include <vector>

using namespace std;
/*
 * https://leetcode-cn.com/problems/longest-palindromic-substring/solution/zui-chang-hui-wen-zi-chuan-by-leetcode/
 * lcs最长公共字串+check公共字串*/

class Solution {
public:
    string longestPalindrome(string s) {
        if ( s.size() < 1 )
        {
            return "";
        }
        string s2;
        s2.reserve( s.size() );
        s2.assign( s.rbegin(), s.rend() );

        vector<vector<int> > res( s.size() + 1, vector<int>( s2.size() + 1, 0 ) );
        vector<vector<int> > coords( s.size() + 1, vector<int>() );
        for ( int i = 1; i < s.size() + 1; i++ )
        {
            for ( int j = 1; j < s2.size() + 1; j++ )
            {
                if ( s[i-1] == s2[j-1] )
                {
                    res[i][j] = res[i-1][j-1] + 1;
                }

                int len = res[i][j];
                if ( len > 1 )
                {
                    coords[len].push_back( i-1 );
                }
            }
        }

        for ( int i = s.size(); i > 0; i-- )
        {
            if ( coords[i].size() > 0 )
            {
                for ( auto &idx: coords[i] )
                {
                    if ( check( s, idx, i ) )
                    {
                        return s.substr( idx-i+1, i );
                    }
                }
            }
        }
        return s.substr(0, 1);
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

    s = "bb";
    cout << s << "|" << ( sol.longestPalindrome( s ) == "bb" ) << endl;

    s = "cbbd";
    cout << s << "|" << ( sol.longestPalindrome( s ) == "bb" ) << endl;

    s = "babad";
    cout << s << "|" << ( sol.longestPalindrome( s ) == "bab" || sol.longestPalindrome( s ) == "aba" ) << endl;

    return 0;
}
