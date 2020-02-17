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
 *
 * https://leetcode-cn.com/problems/longest-substring-without-repeating-characters/
 * 三种解法
 * 1、for(i: 0 ~ n-1)
 *      for (j: i+1 ~n-1)
 *          s[i~j]判重（可以改进为map）
 *     时间复杂度O(n^2), 空间复杂度O(m)
 * 2、s与s求最长公共字串，动态规划求解，时间复杂度O(2*n)，空间复杂度O(1)
 * 3、双指针，滑动窗口，map统计，时间复杂度O(n)，空间复杂度O(m)
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
    int lengthOfLongestSubstring(string s) {
        if (s.size() < 1) {
            return 0;
        }

        int ans = 0;
        int l = 0, r = 0;
        unordered_map<char, int> val_2_index(s.size());
        while (r < s.size()) {
            char c = s[r];
            auto iter = val_2_index.find(c);
            if (val_2_index.end() != iter && iter->second >= 0) {
                // 抹掉l～iter->second的所有字符，l指向iter->second+1
                while (l <= iter->second) {
                    val_2_index[s[l++]] = -1;
                }
                // 下面这个答案也是成立的，只是val_2_index并不是保存可行解的字符
                // 为啥val_2_index不用重置l～iter->second？？？
                // 因为即使r之后的元素在val_2_index
                // l = max(l, iter->second + 1);
            }
            ans = max(ans, r - l + 1);
            val_2_index[c] = r;
            ++r;
        }
        return ans;
    }
};

int main() {
    Solution sol;
    cout << sol.lengthOfLongestSubstring("abc") << endl;
    cout << sol.lengthOfLongestSubstring("pwwkew") << endl;
    cout << sol.lengthOfLongestSubstring("abcabcbb") << endl;
    cout << sol.lengthOfLongestSubstring("bbbbb") << endl;
    return 0;
}
