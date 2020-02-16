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
 * https://leetcode-cn.com/problems/minimum-window-substring/
 * 滑动窗口求解，指向S两个指针，left和right
 * 1、预处理，T转换为t_map<c, cnt>
 * 2、r往右滑动，每次s_map[c]++，如果t_map[c] == s_map[c]（这里只能是==，再往右滑动，s_map[c]还会++，如果写成<=，则会再次符合判断，导致success_match多加了1，==可以保证一个字符仅可能被success_match++一次），
 *      则表示已有一个字符match完毕，success_match++
 * 3、如果sucess_match == t_map的size，开始l往右滑动（收缩当前的可行解），如果t_map[c] > s_map[c], 表示已有一个字符不match，success_match--（保存当前一个可行解）
 * 4、跳转到2
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
    struct OneSol{
        int len;
        int s;
        OneSol(int _l, int _s) : len(_l), s(_s) {}
    };
public:
    string minWindow(string s, string t) {
        if (s.size() < 1 || t.size() < 1) {
            return "";
        }
        
        int l = 0, r = 0;
        unordered_map<char, int> t_map(t.size());
        unordered_map<char, int> s_map(s.size());
        // 1. 预处理，T转换为t_map<c, cnt>
        for (auto c: t) {
            t_map[c]++;   
        }

        OneSol ans(s.size()+1, -1);
        int success_match = 0;
        // 2. r往右滑动
        while (r < s.size()) {
            char c = s[r++];
            s_map[c]++;
            auto iter = t_map.find(c);
            // 2.1 有一个字符已经match
            // NOTE: 这里一定得是iter->second == s_map[c]，不可以写成iter->second <= s_map[c]
            if (t_map.end() != iter && iter->second == s_map[c]) {
                success_match++;
            }

            // 3. 所有字符都match了，这时候l开始往右移动，缩减可行解
            while (success_match == t_map.size() && l < r) {
                char c = s[l++];
                s_map[c]--;
                auto iter = t_map.find(c);
                // 3.1 不能再缩减，即为一个可行解
                if (t_map.end() != iter && iter->second > s_map[c]) {
                    if (r - l + 1 < ans.len) {
                        ans.len = r - l + 1;
                        ans.s = l - 1;
                    }
                    success_match--;
                }
            }
        }
        
       return ans.s == -1 ? "" : s.substr(ans.s, ans.len);
    }
};

int main() {
    Solution sol;
    cout << sol.minWindow("a", "a") << endl;
    cout << sol.minWindow("ADOBECODEBANC", "ABC") << endl;
    return 0;
}
