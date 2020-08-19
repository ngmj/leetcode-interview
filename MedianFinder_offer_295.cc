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
 * https://leetcode-cn.com/classic/problems/shu-ju-liu-zhong-de-zhong-wei-shu-lcof/description/
 * 查找流数据中位数，借鉴查找滑动窗口流数据的最大值
 * 0 1 2（存在大顶堆big）  3 4 5（存在小顶堆small）
 * 方便rebalance，左右调整，保证big存小数，small存大数，且big size = small size + 1
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

class MedianFinder {
public:
  /** initialize your data structure here. */
  MedianFinder() {
  }

  void addNum(int num) {
    if (heap_big_.empty() || num <= heap_big_.top()) {
      heap_big_.push(num);
      if (heap_big_.size() > heap_small_.size() + 1) {
        int tmp = heap_big_.top();
        heap_big_.pop();
        heap_small_.push(tmp);
      } 
    } else {
      heap_small_.push(num);
      if (heap_small_.size() > heap_big_.size()) {
        int tmp = heap_small_.top();
        heap_small_.pop();
        heap_big_.push(tmp);
      }
    }
  }

  double findMedian() {
    if (heap_big_.size() == heap_small_.size() + 1) {
      return heap_big_.top();
    }
    return 1.0 * (heap_big_.top() + heap_small_.top()) / 2;
  }
private:
  priority_queue<int> heap_big_;
  priority_queue<int, vector<int>, greater<int>> heap_small_;
};

int main() {
  MedianFinder finder;
  finder.addNum(1);
  finder.addNum(2);
  cout << (finder.findMedian() == 1.5) << endl;
  finder.addNum(3);
  cout << (finder.findMedian() == 2) << endl;
  return 0;
}
