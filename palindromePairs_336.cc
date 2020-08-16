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
 * 求每个字符串去除回文后的翻转串，在不在剩余的hashmap中，比如
 * abcd 去除a、d和空三个回文串，依次剩下的三个子串翻转，得到dcb、cba、dcba 
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
  vector<vector<int>> palindromePairs(const vector<string>& words) {
    unordered_map<string, int> hw;
    hw.reserve(words.size());
    for (int i = 0; i < words.size(); ++i) {
      hw.insert(make_pair(words[i], i));
    }
    vector<vector<int>> ans;
    for (int i = 0; i < words.size(); ++i) {
      auto &str = words[i];
      string tmp = reverse(str, 0, str.size()-1);
      auto iter = hw.find(tmp);
      if (hw.end() != iter && i != iter->second) {
        ans.push_back({i, iter->second});
      }
      // j是回文长度
      // NOTE: {"a", ""} 这两个也可以拼接成回文串
      for (int j = 1; j <= str.size(); ++j) {
        if (isPalindrome(str, 0, j-1)) {
          string tmp = reverse(str, j, str.size()-1);
          auto iter = hw.find(tmp); 
          if (hw.end() != iter) {
            ans.push_back({iter->second, i});
          }
        }
        if (isPalindrome(str, str.size()-j, str.size()-1)) {
          string tmp = reverse(str, 0, str.size()-j-1);
          auto iter = hw.find(tmp); 
          if (hw.end() != iter) {
            ans.push_back({i, iter->second});
          }
        }
      } 
    }
    return ans;
  }

  string reverse(const string &str, int s, int e) {
    if (e < s) { return ""; }
    string tmp;
    tmp.resize(e-s+1);
    int i = 0;
    while (e >= s) {
      tmp[i++] = str[e--];
    }
    return tmp;
  }

  bool isPalindrome(const string &str, int s, int e) {
    while(s <= e) {
      if (str[s] == str[e]) { ++s; --e; }
      else { return false; }
    }
    return true;
  }
};

int main() {
    Solution sol;
    vector<vector<int>>({{0, 1}});
    cout << (sol.palindromePairs({"abcd","dcba","lls","s","sssll"}) 
            == vector<vector<int>>({{0,1}, {1,0}, {3,2}, {2,4}})
            ) << endl;
    cout << (sol.palindromePairs({"a", ""}) 
            == vector<vector<int>>({{1,0}, {0,1}})) << endl;
    return 0;
}
