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
 * https://leetcode-cn.com/problems/number-of-burgers-with-no-waste-of-ingredients/
 * */
using namespace std;

class Solution {
public:
    vector<int> numOfBurgers(int tomatoSlices, int cheeseSlices) {
        if ( tomatoSlices == 0 && cheeseSlices == 0 )
        {
            return {0, 0};
        }        
        if ( tomatoSlices % 2 != 0 )
        {
            return {};
        }

        int total_jumbo = tomatoSlices / 2 - cheeseSlices;
        int total_small = cheeseSlices - total_jumbo;
        if ( total_jumbo < 0 || total_small < 0 )
        {
            return {};
        }
        
        return { total_jumbo, total_small };
    }
};

int main()
{
    Solution sol;
    vector<int> ans1 = sol.numOfBurgers( 16, 7 );
    cout << ( ans1[0] == 1 && ans1[1] == 6 ) << endl;

    vector<int> ans2 = sol.numOfBurgers( 17, 4 );
    cout << ( ans2.size() == 0 ) << endl;
    return 0;
}
