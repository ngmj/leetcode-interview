#include <string>
#include <vector>
#include <iostream>

using namespace std;
/*
https://leetcode-cn.com/problems/delete-operation-for-two-strings/
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

        for ( size_t i = 1; i < word2.size() + 1; i++ )
        {
            for ( size_t j = 1; j < word1.size() + 1; j++ )
            {
                if ( word1[j-1] == word2[i-1] )
                {
                    m[i][j] = std::max( std::max( m[i][j-1], m[i-1][j] ), m[i-1][j-1] + 1 );
                } else
                {
                    m[i][j] = std::max( std::max( m[i][j-1], m[i-1][j] ), m[i-1][j-1] );
                }
            }
        }
        int maxSameLen = m[word2.size()][word1.size()];
        return word1.size() + word2.size() - 2*maxSameLen;
    }
};

int main()
{
    string s, p;
    Solution sol;

    s = "a";
    p = "a.*";
    cout << s << ":" << p << "|" << ( sol.minDistance( s, p ) == 2 ) << endl;

    s = "sea";
    p = "eat";
    cout << s << ":" << p << "|" << ( sol.minDistance( s, p ) == 2 ) << endl;

}
