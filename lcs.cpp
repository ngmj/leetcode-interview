#include <string>
#include <vector>
#include <iostream>

using namespace std;
/*
 * 最长公共字串
*/

class Solution {
public:
    int lcs(string word1, string word2) {
        vector<vector<int> > res( word1.size() + 1, vector<int>( word2.size() + 1, 0 ) );
        int ans = 0;
        for ( size_t i = 1; i < word1.size() + 1; i++ )
        {
            for ( size_t j = 1; j < word2.size() + 1; j++ )
            {
                if ( word1[i-1] == word2[j-1] )
                {
                    res[i][j] = res[i-1][j-1] + 1;
                }

                if ( res[i][j] > ans )
                {
                    ans = res[i][j];
                }
            }
        }
        return ans;
    }
};

int main()
{
    string s, p;
    Solution sol;

    s = "";
    p = "";
    cout << s << ":" << p << "|" << ( sol.lcs( s, p ) == 0 ) << endl;

    s = "horse";
    p = "ros";
    cout << s << ":" << p << "|" << ( sol.lcs( s, p ) == 1 ) << endl;

    s = "helloworld";
    p = "loop";
    cout << s << ":" << p << "|" << ( sol.lcs( s, p ) == 2 ) << endl;
}
