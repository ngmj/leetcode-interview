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
 * https://leetcode-cn.com/problems/powx-n/
 * 分而治之
 * */
using namespace std;

typedef vector<vector<int>> VVI;
typedef vector<int> VI;
typedef long long LL;
LL MAX_LL = std::numeric_limits<LL>::max();;
int MAX_INT = std::numeric_limits<int>::max();;

class Solution {
public:
    double myPow(double x, int n) {
        if ( 0 == x || 1 == x )
        {
            return x;
        }

        unsigned int param = n;

        if ( n < 0 )
        {
            x = 1 / x;
            param = -1*param;
        }

        return Pow(x, param);
    }

    double Pow(double x, unsigned int n) {
        if ( 0 == n )
        {
            return 1;
        }

        unsigned int n1 = n / 2;
        unsigned int n2 = n % 2;

        double ans = myPow(x, n1);
        return n2 ? ans*ans*x : ans*ans;
    }
};

int main()
{
    Solution sol;
    cout << (sol.myPow(1, -2147483648)) << endl;
    cout << (sol.myPow(2.00000, 10)) << endl;
    cout << (sol.myPow(2.10000, 3))<< endl;
    cout << (sol.myPow(2.00000, -2)) << endl;
    return 0;
}
