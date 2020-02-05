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
#include <iomanip>
#include "string_util.h"

/*
 * stack: top(), pop(), push(), empty()
 * queue: front(), back(), push(), pop(), empty()
 * priority_queue: top(), push(), pop(), empty()
 *  std::priority_queue<int> 默认是大根堆，
 *  std::priority_queue<int, std::vector<int>, std::greater<int> > 小根堆
 * deque: front(), back(), push_back(), pop_back, push_front, pop_front(), empty(), clear()
 * x^5-2*x^4+3*x^3-4*x^2-5*x-6=0, x(精确到小数点后14位)=
 * 一元4次方程，可以通过求根公式求解，n>=5时，求根公式失效
 * 牛顿切线法、牛顿割线法、二分法、劈因子法、林士谔—赵访熊法
 * 根据题意，是精确到小数点后14位即可，故而采用二分法求解最快
 * */
using namespace std;

typedef vector<vector<int>> VVI;
typedef vector<int> VI;
typedef long long LL;
LL MAX_LL = std::numeric_limits<LL>::max();;
int MAX_INT = std::numeric_limits<int>::max();;


double polynomial(double x)
{
    double x2 = x*x;
    double x3 = x2*x;
    double x4 = x3*x;
    double x5 = x4*x;
    return x5 - 2*x4 + 3*x3 - 4*x2 - 5*x - 6;
}

int main()
{
    // 因为polynomial(0) 为负数，故而从0开始往后寻找正数
    double s = 0, e;
    while (true)
    {
        e = s+1;
        if ( polynomial(e) > 0 )
        {
            break;
        }
        s = e;
    }
    cout << s << endl;
    cout << e << endl;

    // s=2, e=3，切割2~3，每次切10等分，相当于每次计算小数点更后一位
    int times = 15;
    double slice = 1;
    while ( times-- )
    {
        slice = slice * 0.10000000000000000;
        while ( true )
        {
            e = s+slice;
            if ( polynomial(e) > 0 )
            {
                break;
            }
            s = e;
        }
    }
    fprintf( stdout, "%.15f\n", s );
    fprintf( stdout, "%.15f\n", e );
    cout << setprecision(15) << s << endl;
    cout << setprecision(15) << e << endl;
    return 0;
}
