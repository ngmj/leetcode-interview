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
 * https://leetcode-cn.com/problems/path-sum-ii/
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
  vector<vector<int>> pathSum(TreeNode* root, int sum) {
    stack<int> s;
    pot(root, s, sum);
    return ans;
  }
  void pot(TreeNode* root, stack<int> &path, int sum) {
    if (root == nullptr) { return; }
    path.push(root->val);
    if (root->left == nullptr && root->right == nullptr) {
      if (root->val == sum) {
        stack<int> copy = path;
        vector<int> tmp(copy.size(), 0);
        int i = copy.size() - 1;
        while (i > -1) {
          tmp[i] = copy.top(); copy.pop();
          --i;
        }
        ans.push_back(move(tmp));
      }
    }
    int reseve_val = sum - root->val;
    pot(root->left, path, reseve_val);
    pot(root->right, path, reseve_val);
    path.pop();
    return;
  }
private:
  vector<vector<int>> ans;
};

int main() {
    Solution sol;
    string data = "[5,4,8,11,null,13,4,7,2,null,null,5,1]";
    Codec cc;
    TreeNode *head = cc.deserialize( data );
    cout << (sol.pathSum( head, 22 ) == vector<vector<int>>({{5,4,11,2}, {5,8,4,5}})) << endl;    
    return 0;
}
