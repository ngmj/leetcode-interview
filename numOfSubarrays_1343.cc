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
  int numOfSubarrays(const vector<int>& arr, int k, int threshold) {
    int num = 0;
    long total = 0;
    long target = k * threshold;
    int i = 0, j = 0;
    for (j = 0; j < k && j < arr.size(); ++j) {
      total += arr[j];
    }
    num += total >= target ? 1 : 0;

    for (; j < arr.size(); ++j, ++i) {
      total -= arr[i];
      total += arr[j];
      if (total >= target) { num++; }
    }
    return num;
  }
};

int main() {
    Solution sol;
    cout << (sol.numOfSubarrays({2,2,2,2,5,5,5,8}, 3, 4) == 3) << endl;
    cout << (sol.numOfSubarrays({1,1}, 1, 0) == 2) << endl;
    cout << (sol.numOfSubarrays({11,13,17,23,29,31,7,5,2,3}, 3, 5) == 6) << endl;
    cout << (sol.numOfSubarrays({7,7,7,7,7,7,7}, 7, 7) == 1) << endl;
    return 0;
}
