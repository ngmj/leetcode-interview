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
 * https://leetcode-cn.com/problems/find-winner-on-a-tic-tac-toe-game/
 * */
using namespace std;

class Solution {
public:
    string tictactoe(vector<vector<int>>& moves) {
        if ( moves.size() < 5 )
        {
            return "Pending";
        } else if ( moves.size() == 5 )
        {
            return isSuccess( moves[0], moves[2], moves[4] ) ? "A" : "Pending";
        } else if ( moves.size() == 6 )
        {
            return isSuccess( moves[1], moves[3], moves[5] ) ? "B" : "Pending";
        } else if ( moves.size() == 7 )
        {
            return isSuccess( moves[0], moves[2], moves[4], moves[6] ) ? "A" : "Pending";
        } else if ( moves.size() == 8 )
        {
            return isSuccess( moves[1], moves[3], moves[5], moves[7] ) ? "B" : "Pending";
        }
        
        return isSuccess( moves[0], moves[2], moves[4], moves[6], moves[8] ) ? "A" : "Draw";
    }

    bool isSuccess( vector<int> &a, vector<int> &b, vector<int> &c )
    {
        if ( a[0] == b[0] )
        {
            return a[0] == c[0];
        } else if ( a[1] == b[1] )
        {
            return a[1] == c[1];
        }
        
       if ( a[0] == c[0] || a[1] == c[1] )
       {
           return false;
       }

       return ratio( a, b ) * ratio( a, c ) == 1;
    }

    int ratio( vector<int> &a, vector<int> &b )
    {
        return ( a[1] - b[1] ) / ( a[0] - b[0] );
    }

    bool isSuccess( vector<int> &a, vector<int> &b, vector<int> &c, vector<int> &d )
    {
        return isSuccess( a, b, c ) || isSuccess( a, b, d ) || isSuccess( a, c, d ) || isSuccess( b, c, d );
    }

    bool isSuccess( vector<int> &a, vector<int> &b, vector<int> &c, vector<int> &d, vector<int> &e )
    {
        return isSuccess( a, b, c, d ) || isSuccess( a, b, c, e ) || isSuccess( a, b, d, e ) || isSuccess( a, c, d, e ) || isSuccess( b, c, d, e );
    }
};

int main()
{
    Solution sol;
    vector<vector<int> > moves1 =  { { 0,0 }, {2,0}, {1,1}, {2,1}, {2,2} };
    cout << ( sol.tictactoe( moves1 ) == "A" ) << endl;

    vector<vector<int> > moves2 = { {0,0},{1,1},{0,1},{0,2},{1,0},{2,0} };
    cout << ( sol.tictactoe( moves2 ) == "B" ) << endl;

    vector<vector<int> > moves3 = {{0,0},{1,1},{2,0},{1,0},{1,2},{2,1},{0,1},{0,2},{2,2}}; 
    cout << ( sol.tictactoe( moves3 ) == "Draw" ) << endl;
    
    vector<vector<int> > moves4 = {{0,0},{1,1}}; 
    cout << ( sol.tictactoe( moves4 ) == "Pending" ) << endl;
    return 0;
}
