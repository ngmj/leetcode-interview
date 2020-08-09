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
  int maximumSwap(int num) {
    if (num == 0) { return num; }
    vector<int> vec1;
    vector<pair<int, int>> pos;
    vec1.reserve(10);
    pos.reserve(10);
    while (num) {
      int i = num % 10;
      vec1.push_back(i);
      num = num / 10;
    }
    int max = -1, p = -1;
    for (int i = 0; i < vec1.size(); ++i) {
      if (vec1[i] > max) {
        pos.push_back(make_pair(vec1[i], i));
        max = vec1[i];
        p = i;
      } else {
        pos.push_back(make_pair(max, p));
      }
    }
    for (int i = vec1.size() - 1; i >= 0; --i) {
      if (vec1[i] < pos[i].first) {
        int tmp = vec1[i];
        vec1[i] = pos[i].first;
        vec1[pos[i].second] = tmp;
        break;
      }
    }
    int ans = 0;
    for (int i = vec1.size() - 1; i >= 0; --i) {
      ans = ans*10 + vec1[i];
    }
    return ans;
  }
};

int main() {
    Solution sol;
    cout << (sol.maximumSwap(2736) == 7236) << endl;
    return 0;
}
