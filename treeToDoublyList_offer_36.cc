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
 * https://leetcode-cn.com/classic/problems/er-cha-sou-suo-shu-yu-shuang-xiang-lian-biao-lcof/description/
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
using Node = TreeNode;
class Solution {
public:
  Node* treeToDoublyList(Node* root) {
    if (nullptr == root) { return root; }
    pair<Node*, Node*> ht = link(root);
    ht.first->left = ht.second;
    ht.second->right = ht.first;
    return ht.first;
  }

  pair<Node*, Node*> link(Node* root) {
    if (nullptr == root) { return make_pair<Node*>(nullptr, nullptr); }
    pair<Node*, Node*> left_ht = link(root->left);
    pair<Node*, Node*> right_ht = link(root->right);
    if (left_ht.second) { // left tail
      left_ht.second->right = root;
      root->left = left_ht.second;
    }
    if (right_ht.first) { // right head
      root->right = right_ht.first;
      right_ht.first->left = root;
    }
    Node *head = root, *tail = root;
    if (left_ht.first) { 
      head = left_ht.first;
    }
    if (right_ht.second) {
      tail = right_ht.second;
    }
    return make_pair(head, tail);
  }
};

void print(TreeNode *head) {
  TreeNode *next = head;
  while (next->right != head) {
    cout << next->val << "->";
    next = next->right;
  }
  cout << next->val << endl;
  
  next = head->left;
  while (next != head) {
    cout << next->val << "->";
    next = next->left;
  }
  cout << next->val << endl;
}

int main() {
    Solution sol;
    string data = "[4,2,5,1,3]";
    Codec cc;
    TreeNode *head = cc.deserialize(data);
    TreeNode *list = sol.treeToDoublyList(head);
    print(list);
    return 0;
}
