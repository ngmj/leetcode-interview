#include <string>
#include <vector>
#include <iostream>

using namespace std;
/*
1、收拢连续的**的通配符
2、p进行分组，如 a.*b* =》a、.*、b* 3个数组
3、动态规划计算
字符串：m(0~M)
正则：n(0~N)
f(M, N) = {
    if ( n[N]带通配符 ) // 如b*
    {
        if ( n[N] == m[M] )
        {
            // <= f(M-1, N-1) || f(M-1, N) || f(M, N-1)
            <= f(M-1, N) || f(M, N-1) // 优化一下，因为f(M-1, N-1)和f(M-1, N)结果一定是一样的
        } else
        {
            <= f(M, N-1)
        }
    } else if ( n[N] != m[M] ) // n[N]不带通配符，且最后字符串不匹配，直接返回失败
    {
        <= false
    } else // n[N]不带通配符，且最后字符串可以匹配上，则只要前面的字符串也能跟n(0~N-1)匹配上即可
    {
        <= f(M-1, N-1)
    }
}
*/

#define NORMAL(c) ( c != '.' && c != '*' && c != '\0' )

struct PS
{
    char c; // must be a~z 或 .
    char p;
    PS() : c( '\0' ), p ( '\0' ){}
    bool operator == ( const char t )
    {
        if ( t == c || c == '.' )
        {
            return true; 
        }
        return false;
    }
    bool operator != ( const char t )
    {
        return !( operator == (t) );
    }
};

class Solution {
public:
    void shrink( string p,
                 string &reg )
    {
        size_t i = 0;
        while ( i < p.size() )
        {
            if ( NORMAL( p[i] ) || p[i] == '.' )
            {
                reg.push_back( p[i] );
                i++;
            } else if ( reg.size() < 1 )
            {
                i++;
                continue;
            } else if ( reg[ reg.size() - 1 ] == '*' )
            {
                i++;
                continue;
            } else
            {
                reg.push_back( p[i] );
                i++;
            }
        }
    }

    void makePS( const string &p,
                 vector<PS>   &ps )
    {
        size_t len = p.size();
        size_t i = 0;
        while ( i < len )
        {
            if ( NORMAL( p[i] ) || p[i] == '.' )
            {
                PS onePs;
                onePs.c = p[i];
                i++;
                if ( i < len && p[i] == '*' )
                {
                    onePs.p = p[i];
                    i++;
                }
                ps.push_back( onePs );
            } else
            {
                cout << "error" << endl;
            }
        }
    }

    bool isMatch(string s, string p) 
    {
        string reg;
        reg.reserve( p.size() );
        shrink( p, reg );

        vector<PS> ps;
        makePS( reg, ps );

        // 初始化一个 [ s.size() + 1 ][ ps.size() + 1 ] 二维数组
        // 第一行表示s空时的情况
        // 第一列表示ps空时的情况

        vector<vector<bool> > m;
        m.reserve( s.size() + 1 );
        for ( size_t i = 0; i < s.size() + 1; i++ )
        {
            m.push_back( vector<bool>( ps.size() + 1, false ) );
        }

        m[0][0] = 1; // s与ps皆为空
        // 初始化第一行（s为空）
        for ( size_t j = 1; j < ps.size()+1; j++ )
        {
            if ( ps[j-1].p == '*' )
            {
                m[0][j] = m[0][j-1];
            } else
            {
                m[0][j] = false;
            }
        }
        // 第一列（ps为空）除了m[0][0]外，皆为false

        for ( size_t i = 1; i < s.size() + 1; i++ )
        {
            for ( size_t j = 1; j < ps.size() + 1; j++ )
            {
                if ( ps[j-1].p == '*' )
                {
                    if ( ps[j-1] == s[i-1] )
                    {
                        // m[i][j] = m[i][j-1] || m[i-1][j-1] || m[i-1][j];
                        m[i][j] = m[i][j-1] || m[i-1][j];
                    } else
                    {
                        m[i][j] = m[i][j-1];
                    }
                } else if ( ps[j-1] != s[i-1] )
                {
                    m[i][j] = false;
                } else
                {
                    m[i][j] = m[i-1][j-1];
                }
            }
        }
        return m[s.size()][ps.size()];
    }
};

int main()
{
    string s, p;
    Solution sol;

    s = "a";
    p = "a.*";
    cout << s << ":" << p << "|" << ( sol.isMatch( s, p ) == true ) << endl;

    s = "aab";
    p = "a*c*b";
    cout << s << ":" << p << "|" << ( sol.isMatch( s, p ) == true ) << endl;

    s = "ab";
    p = ".*..";
    cout << s << ":" << p << "|" << ( sol.isMatch( s, p ) == true ) << endl;

    s = "";
    p = ".*";
    cout << s << ":" << p << "|" << ( sol.isMatch( s, p ) == true ) << endl;

    s = "aa";
    p = "a*";
    cout << s << ":" << p << "|" << ( sol.isMatch( s, p ) == true ) << endl;

    s = "";
    p = "*";
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

    s = "aa";
    p = ".*";
    cout << s << ":" << p << "|" << ( sol.isMatch( s, p ) == true ) << endl;

    s = "mississippi";
    p = "mis*is*p*.";
    cout << s << ":" << p << "|" << ( sol.isMatch( s, p ) == false ) << endl;

    s = "mississippi";
    p = "mis*is*ip*.";
    cout << s << ":" << p << "|" << ( sol.isMatch( s, p ) == true ) << endl;

}
