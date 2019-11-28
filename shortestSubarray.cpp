#include <vector>
#include <iostream>
#include <limits>
#include <deque>
#include "string_util.h"

using namespace std;

/*
 * https://leetcode-cn.com/problems/shortest-subarray-with-sum-at-least-k/solution/he-zhi-shao-wei-k-de-zui-duan-zi-shu-zu-by-leetcod/
 * opt(y) 表示对于固定的 y，满足 P[x] <= P[y] - K 最大的 x
 * */

class Solution {
    typedef long long LL;
    typedef long L;
public:
    int shortestSubarray(vector<int>& A, int K) {
        vector<L> sum( A.size()+1, 0 );
        for ( size_t i = 0; i < A.size(); i++ )
        {
            sum[i+1] = sum[i] + A[i]; 
        }

        deque<int> de; // opt(y) candidates, as indices of P
        size_t ans = A.size() + 1;
        for ( size_t i = 0; i < A.size() + 1; i++ )
        {
            while ( !de.empty() && sum[ de.back() ] > sum[i] )
            {
                de.pop_back();
            }
            while ( !de.empty() && sum[i] - sum[de.front()] >= K )
            {
                ans = std::min( ans, i - de.front() );
                de.pop_front();
            }
            de.push_back( i );
        }

        if ( ans < A.size() + 1 )
        {
            return ans;
        }
        return -1;
    }
};

int main()
{
    Solution sol;
    int K;

    vector<int> A3 = {2,-1,2};
    K = 3;
    cout << VectorToString(A3) << " - " << K << " | " << ( sol.shortestSubarray( A3, K ) == 3 ) << endl;

    vector<int> A1 = {1};
    K = 1;
    cout << VectorToString(A1) << " - " << K << " | " << ( sol.shortestSubarray( A1, K ) == 1 ) << endl;

    vector<int> A2 = {1,2};
    K = 4;
    cout << VectorToString(A2) << " - " << K << " | " << ( sol.shortestSubarray( A2, K ) == -1 ) << endl;

    vector<int> A4 = {48,99,37,4,-31};
    K = 140;
    cout << VectorToString(A4) << " - " << K << " | " << ( sol.shortestSubarray( A4, K ) == 2 ) << endl;

    vector<int> A5 = {56,-21,56,35,-9};
    K = 61;
    cout << VectorToString(A5) << " - " << K << " | " << ( sol.shortestSubarray( A5, K ) == 2 ) << endl;

    vector<int> A6 = {84,-37,32,40,95};
    K = 167;
    cout << VectorToString(A6) << " - " << K << " | " << ( sol.shortestSubarray( A6, K ) == 3 ) << endl;
     
    vector<int> A7 = {44,-25,75,-50,-38,-42,-32,-6,-40,-47};
    K = 19;
    cout << VectorToString(A7) << " - " << K << " | " << ( sol.shortestSubarray( A7, K ) == 1 ) << endl;
}
