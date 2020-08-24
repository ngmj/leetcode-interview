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
 * https://leetcode-cn.com/problems/binary-tree-cameras/
 * 每个节点有三个状态, [0,0,null,0,null,0,null]，在第三个节点放一个摄像头：
 * 0表示待覆盖，第一个0节点就是待覆盖
 * 1表示已覆盖, 第二个0节点
 * 2表示本节点有摄像机，第三个0节点
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
  int minCameraCover(TreeNode* root) {
    if (nullptr == root) { return 0; }
    int stat = pot(root);
    return stat == 0 ? ans + 1 : ans;
  }
  
  // 返回三个状态值 
  int pot(TreeNode* root) {
    if (nullptr == root) {
      return 1;
    } 
    int left = pot(root->left);
    int right = pot(root->right);
    if (left == 0 || right == 0) {
      ans += 1;
      return 2;
    } else if (left == 2 || right == 2) {
      return 1;
    }
    // left == 1 && right == 1
    return 0;
  }
private:
  int ans{0};
};

int main() {
    Solution sol;
    string data = "[0,0,null,0,0]";
    Codec cc;
    TreeNode *head = cc.deserialize( data );
    cout << (sol.minCameraCover(head) == 1) << endl;
    return 0;
}
