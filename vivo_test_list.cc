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
#include "serialize_deserialize_tree.hpp"
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

struct ListNode {
  int val{0};
  ListNode *pre{nullptr}, *next{nullptr};
  ListNode() = default;
  explicit ListNode(int v) : val(v), pre(nullptr), next(nullptr) {}
};

class Solution {
public:
  ListNode* BuildDList(const vector<int> &v) {
    if (v.size() < 1) { return nullptr; }
    ListNode head;
    for (auto i: v) {
      ListNode *n = new ListNode(i);
      n->next = head.next;
      n->pre = &head;
      if (head.next) { head.next->pre = n; }
      head.next = n;
    }
    head.next->pre = nullptr;
    return head.next;
  }
  ListNode* reverseK(ListNode* node, const int k) {
    if (nullptr == node || k < 2) { return node; }
    ListNode *head = new ListNode(0);
    ListNode *first = node;
    int i = 0;
    while (node) {
      i++;
      if (i == k) {
        ListNode* tail = node;
        ListNode* next = tail->next;
        head->next = reverse(first, node);
        first = next;
        i = 0;
      }
      node = node->next;
    }
  }
};

int main() {
    Solution sol;
    ListNode* head = sol.BuildDList(vector<int>({1, 2, 3}));
    return 0;
}
