#include <string>
#include <vector>
#include <iostream>

#include "string_util.h" 

using namespace std;
using namespace common_modules::util;
/*
https://leetcode-cn.com/problems/uncrossed-lines/
*/

class Solution {

struct LineInfo
{
    int maxLineNum; // 截至到当前最大线段数
    int x; // 边界直线的下标
    int y; // 边界直线的下标
    LineInfo()
        : maxLineNum(0)
        , x(-1)
        , y(-1)
    {}
};
public:
    int maxUncrossedLines(vector<int>& A, vector<int>& B) {
        vector<vector<LineInfo> > m( A.size() + 1, vector<LineInfo>( B.size() + 1, LineInfo() ) );
        for ( size_t i = 1; i < A.size() + 1; i++ )
        {
            for ( size_t j = 1; j < B.size()+1; j++ )
            {
                LineInfo li1 = m[i-1][j-1];
                if ( m[i-1][j].maxLineNum > li1.maxLineNum )
                {
                    li1 = m[i-1][j];
                }
                // 以A[i-1] ~ B[li1.y+1~j-1]
                for ( int k = li1.y+1; k <= j - 1; k++ )
                {
                    if ( A[i-1] == B[k] )
                    {
                        li1.maxLineNum++;
                        li1.x = i - 1;
                        li1.y = k;
                        break;
                    }
                }

                LineInfo li2 = m[i-1][j-1];
                if ( m[i][j-1].maxLineNum > li2.maxLineNum )
                {
                    li2 = m[i][j-1];
                }
                // 以A[li2.x+1~i-1] ~ B[j-1]
                for ( int l = li2.x+1; l <= i - 1; l++ )
                {
                    if ( A[l] == B[j-1] )
                    {
                        li2.maxLineNum++;
                        li2.x = l;
                        li2.y = j-1;
                        break;
                    }
                }

                m[i][j] = li1.maxLineNum > li2.maxLineNum ? li1 : li2;
            }
        }
        return m[A.size()][B.size()].maxLineNum;
    }
};

int main()
{
    string s, p;
    Solution sol;

    vector<int> A1 = { 1, 4, 2 };
    vector<int> B1 = { 1, 2, 4 };
    cout << VectorToString(A1) << ":" << VectorToString(B1) << "|" << ( sol.maxUncrossedLines( A1, B1 ) == 2 ) << endl;

    vector<int> A2 = { 2,5,1,2,5 };
    vector<int> B2 = { 10,5,2,1,5,2 };
    cout << VectorToString(A2) << ":" << VectorToString(B2) << "|" << ( sol.maxUncrossedLines( A2, B2 ) == 3 ) << endl;

    vector<int> A3 = { 1,3,7,1,7,5 };
    vector<int> B3 = { 1,9,2,5,1 };
    cout << VectorToString(A3) << ":" << VectorToString(B3) << "|" << ( sol.maxUncrossedLines( A3, B3 ) == 2 ) << endl;
}
