#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <stack>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <limits>
#include "string_util.h"

/*
 * https://leetcode-cn.com/problems/palindrome-partitioning-iii/
 * cost[i][j] 表示s[i~j]修改为回文串需要的次数
 * array[i][k] 表示前i个字符修改为k个不相交的回文串需要的最小次数
 * array[i][k] = min{ array[t][k-1] + cost[t][i-1] }
 * 以上公式i=1~s.size(); k=2~K&&k<=i; t=k-1~i-1
 * 一定留意
 * 1、整个计算过程array[i][k]必须是有效计算，即i>=k且k>0，否则会出现异常
 * 2、k从2开始，因为如果k=1，则会出现min{ array[t][k-1] + cost[t][i-1] }计算时，array[t][k-1] k为0的情况
 * */
using namespace std;

typedef vector<vector<int>> VVI;
typedef vector<int> VI;
typedef long long LL;
LL MAX_LL = std::numeric_limits<LL>::max();;
int MAX_INT = std::numeric_limits<int>::max();;

class Solution {
public:
    int palindromePartition(string S, int K) {
        if ( S.size() < 1 || S.size() <= K )
        {
            return 0;
        }

        VVI array( S.size()+1, VI( K+1, 0 ) );
        VVI cost( S.size(), VI( S.size(), 0 ) );
        for ( size_t i = 0; i < S.size(); i++ )
        {
            for ( size_t j = i+1; j < S.size(); j++ )
            {
                cost[i][j] = palindrome(S, i, j);
            }
        }

        for ( int i = 1; i <= S.size(); i++ )
        {
            array[i][1] = cost[0][i-1];
        }

        for ( int i = 1; i <= S.size(); i++ )
        {
            for ( int k = 2; k < i && k <= K; k++ )
            {
                int ans = MAX_INT;
                for ( int t = k-1; t <= i-1; t++ )
                {
                    int tmp = array[t][k-1] + cost[t][i-1];
                    if ( tmp < ans )
                    {
                        ans = tmp;
                    }
                }
                array[i][k] = ans;
            }
        }

        return array[S.size()][K];
    }

    int palindrome( string str, int i, int j )
    {
        if ( str.size() < 2 )
        {
            return 0;
        }

        int ans = 0;
        int s = i, e = j; 
        while ( s < e )
        {
            if ( str[s] != str[e] )
            {
                ans++;
            }
            s++, e--;
        }
        return ans;
    }
};

int main()
{
    Solution sol;
    string s0 = "ihh";
    int k0 = 2;
    cout << s0 << " | " << k0 << " | " << ( sol.palindromePartition( s0, k0 ) == 0 ) << endl;

    string s1 = "abc";
    int k1 = 2;
    cout << s1 << " | " << k1 << " | " << ( sol.palindromePartition( s1, k1 ) == 1 ) << endl;

    string s2 = "aabbc";
    int k2 = 3;
    cout << s2 << " | " << k2 << " | " << ( sol.palindromePartition( s2, k2 ) == 0 ) << endl;

    string s3 = "leetcode";
    int k3 = 8;
    cout << s3 << " | " << k3 << " | " << ( sol.palindromePartition( s3, k3 ) == 0 ) << endl;
    return 0;
}
