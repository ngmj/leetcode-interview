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
 * https://leetcode-cn.com/problems/multi-search-lcci/
 * 对small建立trie树，big从头开始便利，记录完整字符数目
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

struct Trie {
  Trie *data[26] = {nullptr};
  int idx = {-1};
  ~Trie() {
    for (int i = 0; i < 26; ++i) {
      if (data[i]) {
        delete data[i];
        data[i] = nullptr;
      }
    }
  }
};

class Solution {
public:
  void Insert(Trie *root, string s, int idx) {
    if (s.size() < 1) { return; }
    Trie *curr = root;
    for (int i = 0; i < s.size(); ++i) {
      int j = s[i] - 'a';
      if (nullptr == curr->data[j]) { 
        curr->data[j] = new Trie();
      }
      curr = curr->data[j]; 
    }
    curr->idx = idx;
  }

  vector<vector<int>> multiSearch(const string &big, const vector<string>& smalls) {
    vector<vector<int>> ans(smalls.size(), vector<int>());
    if (big.size() < 1 || smalls.size() < 1) { return ans; }
    Trie *root = new Trie();
    for (int i = 0; i < smalls.size(); ++i) {
      Insert(root, smalls[i], i); 
    }
    for (int i = 0; i < big.size(); ++i) {
      Trie *curr = root;
      for (int s = i; s < big.size(); ++s) {
        int j = big[s] - 'a';
        if (nullptr == curr->data[j]) { break; }
        curr = curr->data[j];
        if (curr->idx > -1) {
          ans[curr->idx].push_back(i); 
        } 
      }
    }
    delete root;
    return ans;
  }
};

int main() {
    Solution sol;
    cout << (sol.multiSearch("misis", {"is"}) 
             == vector<vector<int>>({{1,3}})) << endl;
    cout << (sol.multiSearch("mississippi", {"is","ppi","hi","sis","i","ssippi"}) 
             == vector<vector<int>>({{1,4},{8},{},{3},{1,4,7,10},{5}})) << endl;
    return 0;
}
