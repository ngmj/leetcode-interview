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
// #include "serialize_deserialize_tree.hpp"
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

typedef struct TreeNode {
  int val;
  TreeNode* left, *right;
  TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
} TreeNode;
class Solution {
public:
  TreeNode* BuildTree(const vector<string> &v) {
    if (v.size() < 1) { return nullptr; }
    TreeNode* head = new TreeNode(atoi(v[0].c_str()));
    queue<TreeNode*> q;
    q.push(head);
    int i = 1;
    while (!q.empty() && i < v.size()) {
      TreeNode* curr = q.front();
      q.pop();
      if ("null" != v[i]) {
        TreeNode* left = new TreeNode(atoi(v[i].c_str()));
        curr->left = left;
        q.push(left);
      }
      i++;
      if ("null" != v[i]) {
        TreeNode* right = new TreeNode(atoi(v[i].c_str()));
        curr->right = right;
        q.push(right);
      }
      i++;
    }
    return head;
  }
  void Destory(TreeNode* head) {
    if (nullptr == head) { return; }
    Destory(head->left);
    Destory(head->right);
    delete head;
    head = nullptr;
  }
  void Print(TreeNode* head) {
    if (nullptr == head) { return; }
    queue<TreeNode*> q;
    q.push(head);
    while (!q.empty()) {
      TreeNode* curr = q.front();
      q.pop();
      cout << " " << curr->val;
      if (nullptr != curr->left) {
        q.push(curr->left);
      } else {
        cout << " null";
      }
      if (nullptr != curr->right) {
        q.push(curr->right);
      } else {
        cout << " null";
      }
    }
  }
};

int main() {
    Solution sol;
    TreeNode* head = sol.BuildTree(vector<string>({"1", "2", "3", "null", "null", "4", "5"}));
    sol.Print(head);
    sol.Destory(head);
    return 0;
}
