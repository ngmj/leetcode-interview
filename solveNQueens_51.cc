#include <vector>
#include <limits>
#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <stack>
#include <queue>
#include <deque>
#include <unordered_set>
#include <unordered_map>
#include "string_util.h"

/*
 * stack: top(), pop(), push(), empty()
 * queue: front(), back(), push(), pop(), empty()
 * priority_queue: top(), push(), pop(), empty()
 *  std::priority_queue<int> 默认是大根堆，
 *  std::priority_queue<int, std::vector<int>, std::greater<int> > 小根堆
 * deque: front(), back(), push_back(), pop_back, push_front, pop_front(), empty(), clear()
 * https://leetcode-cn.com/problems/n-queens/
 * DFS+剪枝（第i层j列放了一个queen，则
 *           1、j列设置为col[j]=1标记不能再放, 
 *           2、反斜杠设置为pie[i-j]=1标记不能放, 
 *           3、斜杠设置为na[i+j]=1标记不能再放）
 * */
using namespace std;

typedef vector<vector<int>> VVI;
typedef vector<int> VI;
typedef long long LL;
LL MAX_LL = std::numeric_limits<LL>::max();;
int MAX_INT = std::numeric_limits<int>::max();;

class Solution {
public:   
    vector<vector<string>> solveNQueens(int n) {
        unordered_set<int> col, pie, na; 
        vector<vector<string>> ans;
        DFS( n, vector<int>(), col, pie, na, ans );
        return ans;
    }   
   
    void DFS( const int                n,  
              vector<int>              levels,
              unordered_set<int>       &col, 
              unordered_set<int>       &pie,
              unordered_set<int>       &na,
              vector<vector<string>>   &ans
               ) { 
        if ( levels.size() == n ) { 
            vector<string> oneAns;
            generateOneAns( levels, n, oneAns );
            ans.push_back( move( oneAns ) );
            return;
        }   
        int i = levels.size();
        for ( int j = 0; j < n; j++ ) { 
            if ( 0 == col.count( j ) 
                    && 0 == pie.count( i - j ) 
                    && 0 == na.count( i + j ) ) { 
                levels.push_back( j );
                col.insert( j );
                pie.insert( i - j );
                na.insert( i + j );
                DFS( n, levels, col, pie, na, ans );
                levels.erase( levels.end() - 1 );
                col.erase( j );
                pie.erase( i - j );
                na.erase( i + j );
            }
        }
    }

    void generateOneAns( const vector<int> &levels,
                         const int         n,  
                         vector<string>    &oneAns ) { 
         for ( auto j: levels ) {
            string oneLine( n, '.' );
            oneLine[j] = 'Q';
            oneAns.push_back( move( oneLine ) );
        } 
    }
};

void print( const vector<vector<string>> &ans ) {
    for ( auto &oneAns: ans ) {
        cout << "=======================" << endl;
        for ( auto &oneLine: oneAns ) {
            cout << oneLine << endl;
        }
    }
}

int main() {
    Solution sol;
    vector<vector<string>> ans = sol.solveNQueens( 5 );
    print( ans );
    return 0;
}
