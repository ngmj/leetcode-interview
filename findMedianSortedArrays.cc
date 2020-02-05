#include <string>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>

using namespace std;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int n1Len = nums1.size();
        int n2Len = nums2.size();
        if ( 0 == n1Len && 0 == n2Len )
        {
            return 0.0;
        }
        
        auto *pA = &nums1;
        auto *pB = &nums2;
        if ( n1Len < n2Len )
        {
            pA = &nums2;
            pB = &nums1;
        }

        int m = pA->size();
        int n = pB->size();

        if ( 0 == n )
        {
            return ( 1.0 * (*pA)[m/2] + (*pA)[(m - 1)/2] ) / 2;
        }

        // 以pA为基准，进行二叉搜索
        int aL = 0, aR = m; // i 取值范围是0 到m，含义是左边范围内有多少个元素
        int i = 0, j = 0;
        while ( true )
        {
            i = ( aL + aR ) / 2;
            j = ( m + n ) / 2 - i;
            int nRet = check( pA, pB, i, j , m, n );
            if ( nRet < 0 ) // 左范围元素少，i在( i + 1, aR )搜索
            {
                aL = i + 1;
            } else if ( nRet > 0 ) // 左范围元素多，i在( aL, i -1 )搜索
            {
                aR = i - 1;
            } else
            {
                break;
            }
        }

        int maxLeft = getLMax( pA, pB, i, j , m, n );
        int minRight = getRMin( pA, pB, i, j , m, n );

        if (  0 == ( m + n ) % 2 )
        {
            return 1.0 * ( maxLeft + minRight ) / 2;
        }
        return max( maxLeft, minRight );
    }
protected:
    int getLMax( const vector<int> *pV,
                 int               lNum, // make sure idx >= 0
                 int               len )
    {
       if ( lNum > len )
       {
            return (*pV)[len - 1];
       } 
       return (*pV)[lNum - 1];
    }
    int getLMax( const vector<int> *pA,
                 const vector<int> *pB,
                 int               i,
                 int               j,
                 int               m,
                 int               n )
    {
        if ( i <= 0 )
        {
            // return (*pB)[j - 1];
            return getLMax( pB, j, n );
        } else if ( j <= 0 )
        {
            // return (*pA)[i - 1];
            return getLMax( pA, i, m );
        }
        else if ( i > m )
        {
            i = m; 
        } 
        else if ( j > n )
        {
            j = n;
        }
        return std::max( (*pA)[i - 1], (*pB)[j - 1] );
    }
    int getRMin( const vector<int> *pA,
                 const vector<int> *pB,
                 int               i,
                 int               j,
                 int               m,
                 int               n )
    {
        if ( i >= m )
        {
            return (*pB)[j];
        } else if ( j >= n )
        {
            return (*pA)[i];
        }
        return std::min( (*pA)[i], (*pB)[j] );
    }
    
    int check( const vector<int> *pA,
               const vector<int> *pB,
               int               i,
               int               j,
               int               m,
               int               n )
    {
        if ( i < 0 || j > n )
        {
            return -1; // i右移
        }
        else if ( i > m || j < 0 )
        {
            return 1; // i左移
        }

        int areaL = getLMax( pA, pB, i, j, m, n );
        int areaR = getRMin( pA, pB, i, j, m, n );
        if ( areaL <= areaR )
        {
            return 0;
        }

        // NOTE走到这，i是可能等于0，比如输入[1] [2]
        //             j也是可能等n，比如[1,2,4] [3]
        if ( i == 0 || j == n )
        {
            return -1; // i右移
        }
        else if ( i == m || j == 0 )
        {
            return 1; // i左移
        }
        else if ( (*pA)[i - 1] > (*pB)[j] )
        {
            return 1;
        }
        return -1;
    }
};



int main()
{
    vector<int> A = { 4 };
    vector<int> B = { 1, 2, 3, 5, 6 };
    Solution solution;
    double rst = solution.findMedianSortedArrays( A, B );
    fprintf( stdout, "%f\n", rst );
}
