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
 * https://leetcode-cn.com/problems/find-all-anagrams-in-a-string/
 * 双指针，左右指针同时滑动，因为顺序无关，所以字符串转换为map，左右指针滑动时，对map进行增删
 * 左右指针往右滑动，map增删，如果两个map相同，则是可行解
 * （两个map相同，可以通过一个match来进行，指针一边滑动，一遍map增删，一遍对success_match进行更新）
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
    vector<int> findAnagrams(string s, string p) {
        if (s.size() < p.size()) {
            return vector<int>();
        }

        // 1. 初始化
        vector<int> ans;
        unordered_map<char, int> s_map(s.size());
        unordered_map<char, int> p_map(p.size());
        for (auto c: p) {
            p_map[c]++;
        }
        int success_match = 0;

        // 2. 从左往右滑动p.size()个大小
        int l = 0, r = 0;
        while (r < s.size()) {
            char c = s[r++];
            auto iter = p_map.find(c);
            if (p_map.end() != iter) {
                s_map[c]++;
                if (s_map[c] == iter->second) {
                    success_match++;
                }

                while (success_match == p_map.size() && l < r) {
                    char c = s[l++];
                    auto iter = p_map.find(c);
                    if (p_map.end() != iter) {
                        s_map[c]--;
                        if (s_map[c] < iter->second) {
                            success_match--;
                            if (r - l + 1 == p.size()) {
                                ans.push_back(l-1);
                            } else {
                                s_map.clear();
                                success_match = 0;
                                l = r;
                            }
                        }
                    }
                }
            } else {
                s_map.clear();
                success_match = 0;
                l = r;
            }
        }

        return ans;
    }
};

int main() {
    Solution sol;
    cout << VectorToString(sol.findAnagrams("abaacbabc", "abc")) << endl;
    cout << VectorToString(sol.findAnagrams("cbaebabacd", "abc")) << endl;
    cout << VectorToString(sol.findAnagrams("abab", "ab")) << endl;
    return 0;
}
