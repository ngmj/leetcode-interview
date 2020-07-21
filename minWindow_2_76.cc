#include <vector>
#include <limits>
#include <iostream>
#include <algorithm>
#include <map>
#include <list>
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
 * list: push_back, push_front, insert(pos, val), front, remove(val), erase(iter)
 *
 * iter = lower_bound(start, end, val) 返回[start, end)>=val的第一个位置（下界）
 * iter = upper_bound(start, end, val) 返回[start, end)>val的第一个位置（上界）
 * 如(11,12) lower_bound查找11，返回0；upper_bound则返回1
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
    string minWindow(string s, string t) {
        if (s == "" || t == "" || s.size() < t.size()) {
            return "";
        }
        std::unordered_map<char, int> c2i;
        int tn = t.size();
        c2i.reserve(tn);
        for (auto &c: t) {
            c2i[c]++;
        }
        int i = 0, j = 0, ans = s.size() + 1, start = -1;
        while (j < s.size()) {
            auto iter = c2i.find(s[j]);
            if (c2i.end() != iter && --(iter->second) >= 0) {
                tn--;
            }
            if (0 == tn) { // 可行解
                while (i <= j) {
                    auto iter = c2i.find(s[i++]);
                    if (c2i.end() != iter) {
                        if (++(iter->second) > 0) { // 当前最优解
                            tn++;
                            int len = j - i + 2;
                            if (len < ans) {
                                ans = len;
                                start = i-1;
                            }
                            break;
                        }
                    }
                }
            }
            ++j;
        }
        if (start >= 0) {
            return s.substr(start, ans);
        }
        return "";
    }
};

int main() {
    Solution sol;
    cout << (sol.minWindow("a", "b") == "") << endl;
    cout << (sol.minWindow("a", "a") == "a") << endl;
    cout << (sol.minWindow("ADOBECODEBANC", "ABC") == "BANC") << endl;
    return 0;
}
