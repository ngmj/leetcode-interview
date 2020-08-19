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
 * https://leetcode-cn.com/classic/problems/ju-zhen-zhong-de-lu-jing-lcof/description/
 * dfs，重点是记录一次访问过程中已经遍历过的节点，并且在回塑时，清除该标记
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

const vector<pair<int, int>> kPos = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}}; 
class Solution {
public:
  bool exist(const vector<vector<char>>& board, const string &word) {
    m = board.size(), n = board[0].size();
    vector<vector<bool>> visited(m, vector<bool>(n, false));
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        // board[i][j] == word[k] ???
        if (dfs(board, visited, word, i, j, 0)) {
          return true;
        }
      }
    }
    return false;
  }
  bool dfs(const vector<vector<char>>& board,
           vector<vector<bool>> &visited,
           const string &word,
           int i, int j, int k) {
    if (i < 0 || i >= m || j < 0 || j >= n || 
        board[i][j] != word[k] || visited[i][j]) {
      return false;
    }

    if (k == word.size() - 1) { 
      return true;
    }

    visited[i][j] = true;
    for (auto &p: kPos) {
      if (dfs(board, visited, word, i+p.first, j+p.second, k+1)) {
        return true;
      }
    }
    visited[i][j] = false;
    return false;
  }
private:
  int m;
  int n;
};

int main() {
    Solution sol;
    cout << (sol.exist(vector<vector<char>>({{'A','B','C','E'},{'S','F','C','S'},{'A','D','E','E'}}),
          "ABCCED") == true) << endl;
    cout << (sol.exist(vector<vector<char>>({{'a', 'b'}, {'c', 'd'}}), "abcd") == false) << endl;
    return 0;
}
