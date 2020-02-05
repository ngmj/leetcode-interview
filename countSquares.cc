#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <stack>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include "string_util.h"

/*
 * https://leetcode-cn.com/problems/count-square-submatrices-with-all-ones/
 * 动态规划求解
 * storage[i][j]表示以matrix[i-1][j-1]为右下角的正方形的最大变长
 * storage[i][j] 的值有以下几种情况
 * matrix[i-1][j-1] = 0
 *  storage[i][j]=0
 * matrix[i-1][j-1] = 1
 *  edge = std::min(storage[i-1][j]，storage[i][j-1])
 *      如果matrix[i-edge-1][j-edge-1]=1，storage[i][j]=edge+1
 *      否则storage[i][j]=edge > 0 ? edge : 1;
 * */
using namespace std;

class Solution {
public:
    int countSquares(vector<vector<int>>& matrix) {
        if ( matrix.size() < 1 )
        {
            return 0;
        }

        int ans = 0;
        int Y = matrix.size();
        int X = matrix[0].size();
        vector<vector<int>> storage( Y+1, vector<int>( X+1, 0 ) );
        for ( int i = 1; i < Y+1; i++ )
        {
            for ( int j = 1; j < X+1; j++ )
            {
                if ( 0 == matrix[i-1][j-1] )
                {
                    storage[i][j] = 0;
                    continue;
                }

                int top = storage[i-1][j];
                int left = storage[i][j-1];
                int edge = std::min(top, left);
                if ( matrix[i-edge-1][j-edge-1] )
                {
                    storage[i][j] = edge+1;
                } else
                {
                    storage[i][j] = edge > 0 ? edge: 1;
                } 

                ans += storage[i][j];
            }
        } 
        return ans;
    }
};

int main()
{
    Solution sol;
    vector<vector<int> > matrix1 = {
          {0,1,1,1},
          {1,1,1,1},
          {0,1,1,1} 
    };
    cout << ( sol.countSquares( matrix1 ) == 15 ) << endl;

    vector<vector<int> > matrix2 = {
        {1,0,1},
        {1,1,0},
        {1,1,0}
    };
    cout << ( sol.countSquares( matrix2 ) == 7 ) << endl;
    return 0;
}
