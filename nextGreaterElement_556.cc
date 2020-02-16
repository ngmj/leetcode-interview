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
 * priority_queue: top(), pop(), push(), empty()
 *  std::priority_queue<int> 默认是大根堆，
 *  std::priority_queue<int, std::vector<int>, std::greater<int> > 小根堆
 * queue: front(), back(), push(), pop(), empty()
 * deque: front(), back(), push_back(), pop_back, push_front, pop_front(), empty(), clear()
 *
 * iter = lower_bound(start, end, val) 返回[start, end)>=val的第一个位置（下界）
 * iter = upper_bound(start, end, val) 返回[start, end)>val的第一个位置（上界）
 * 如(11,12) lower_bound查找11，返回0；upper_bound则返回1
 * https://leetcode-cn.com/problems/next-greater-element-iii/
 * */
using namespace std;

typedef vector<vector<int>> VVI;
typedef vector<int> VI;
typedef unsigned int UI;
typedef long long LL;
typedef unsigned long long ULL;
LL MAX_LL = std::numeric_limits<LL>::max();
LL MIN_LL = std::numeric_limits<LL>::min();
int MAX_INT = std::numeric_limits<int>::max();
int MIN_INT = std::numeric_limits<int>::min();

class Solution {
public:
    int nextGreaterElement(int n) {
        if (n < 10) {
            return -1;
        }

        // n => 95761, val => <1,6,7,5,9>
        vector<int> val;
        while (n) {
            val.push_back(n % 10);
            n /= 10;
        }
        
        int target_index = -1;
        vector<int> reduce_val;
        for (int i = 1; i < val.size(); ++i) {
            if (val[i] < val[i-1]) {
                target_index = i;
                reduce_val.push_back(val[i]);
                break;
            }
        }

        if (-1 == target_index) {
            return -1;
        }

        /*
        for (int i = 0; i < target_index; ++i) {
            if( val[i] > val[target_index] && val[i] < replace_val) {
                if (MAX_INT != replace_val) {
                    reduce_val.push_back(replace_val);
                }
                replace_val = val[i];
            } else {
                reduce_val.push_back(val[i]);
            }
        }*/
        // 优化一下，val数组是逆序的，可知0~target_index-1都是升序，
        // 所以从前到后找第一个比target_index大的就是目标值，替换target_index
        int replace_index = -1; 
        for (int i = 0; i < target_index; ++i) {
            if (val[i] > val[target_index]) {
                replace_index = i;
                break;
            } else {
                reduce_val.push_back(val[i]);
            }
        }

        for (int i = replace_index + 1; i < target_index; ++i) {
            reduce_val.push_back(val[i]);
        }

        long ans = 0;
        for (int i = val.size() - 1; i > target_index; --i) {
            ans = ans *10 + val[i];
        }

        ans = ans * 10 + val[replace_index];
        sort(reduce_val.begin(), reduce_val.end());
        for (auto v: reduce_val) {
            ans = ans * 10 + v;
        }
        return ans > MAX_INT ? -1 : ans;
    }
};

int main() {
    Solution sol;
    cout << sol.nextGreaterElement(12) << endl;
    cout << sol.nextGreaterElement(12443322) << endl;
    cout << sol.nextGreaterElement(12222333) << endl;
    cout << sol.nextGreaterElement(3569) << endl;
    cout << sol.nextGreaterElement(95761) << endl;
    return 0;
}
