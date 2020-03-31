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
 *
 * https://leetcode-cn.com/problems/reverse-words-in-a-string/
 * 跳过首位空格，然后分割空格，并且保存首个单词的指针
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
    string reverseWords(string s) {
        vector<const char*> pVec;
        char last_char = '\0';
        int i = 0;
        while (i < s.size()) {
            if (s[i] != ' ' && '\0' == last_char) {
                pVec.push_back(s.c_str() + i);
            } else if (s[i] == ' ') {
                s[i] = '\0';
            }
            last_char = s[i];
            ++i;
        }
        string ans = "";
        ans.reserve(s.size());
        for (int i = pVec.size() - 1; i > -1; --i) {
            const char *p = pVec[i];
            while ('\0' != *p) {
                ans.push_back(*p);
                p += 1;
            }
            if (i > 0) {
                ans.push_back(' ');
            }
        }
        return ans;
    }
};

int main() {
    Solution sol;
    cout << sol.reverseWords("the sky is blue") << endl;
    cout << sol.reverseWords("  hello  world!  ") << endl;
    return 0;
}
