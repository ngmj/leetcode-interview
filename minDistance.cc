#include <string>
#include <vector>
#include <iostream>

using namespace std;
/*
https://leetcode-cn.com/problems/edit-distance/
*/

class Solution {
public:
    int minDistance(string word1, string word2) {
        vector<vector<int> > m;
        m.reserve( word2.size() + 1 );
        for ( size_t i = 0; i < word2.size() + 1; i++ )
        {
            m.push_back( vector<int>( word1.size() + 1, 0 ) );
        }

        m[0][0] = 0; // 皆为空
        // 初始化第一行（word2为空）
        for ( size_t j = 1; j < word1.size()+1; j++ )
        {
            m[0][j] = m[0][j-1] + 1;
        }
        
        // 初始化第一列（word1为空）
        for ( size_t i = 1; i < word2.size() + 1; i++ )
        {
            m[i][0] = m[i-1][0] + 1;
        }

        for ( size_t i = 1; i < word2.size() + 1; i++ )
        {
            for ( size_t j = 1; j < word1.size()+1; j++ )
            {
                if ( word1[j-1] == word2[i-1] )
                {
                    m[i][j] = std::min( std::min( m[i][j-1]+1, m[i-1][j]+1 ), m[i-1][j-1] );
                } else
                {
                    m[i][j] = std::min( std::min( m[i][j-1]+1, m[i-1][j]+1 ), m[i-1][j-1]+1 );
                }
            }
        }
        return m[word2.size()][word1.size()];
    }
};

int main()
{
    string s, p;
    Solution sol;

    s = "a";
    p = "a.*";
    cout << s << ":" << p << "|" << ( sol.minDistance( s, p ) == 2 ) << endl;

    s = "horse";
    p = "ros";
    cout << s << ":" << p << "|" << ( sol.minDistance( s, p ) == 3 ) << endl;

    s = "intention";
    p = "execution";
    cout << s << ":" << p << "|" << ( sol.minDistance( s, p ) == 5 ) << endl;

}
