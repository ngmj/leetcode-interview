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
 * https://leetcode-cn.com/classic/problems/er-cha-sou-suo-shu-de-hou-xu-bian-li-xu-lie-lcof/description/
 * 思路, 将当前序列颠倒，然后用单调递增栈做
 * (https://leetcode-cn.com/problems/er-cha-sou-suo-shu-de-hou-xu-bian-li-xu-lie-lcof/comments/)
 *       if val > stack.top() 
 *         return false 
 *       else
 *         一直将栈内元素弹出直到单调递增
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
  bool verifyPostorder(const vector<int>& postorder) {
    stack<int> inc;
    // 假装当前树是MAX_INT的左子树
    inc.push(MAX_INT);
    int pre = inc.top();
    // root->right（比root大）->left（比root小）
    for (int i = postorder.size()-1; i > -1; --i) {
      int val = postorder[i];
      if (val > pre) { return false; } 
      // pre会一直回退到上一层的树根
      while (!inc.empty() && val < inc.top()) { pre = inc.top(); inc.pop(); }
      inc.push(val);
    }
    return true;
  }
};

int main() {
    Solution sol;
    cout << (sol.verifyPostorder({1,3,2}) == true) << endl;
    cout << (sol.verifyPostorder({1,6,3,2,5}) == false) << endl;
    cout << (sol.verifyPostorder({1,3,2,6,5}) == true) << endl;
    return 0;
}
