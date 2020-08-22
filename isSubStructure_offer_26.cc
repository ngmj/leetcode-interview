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

class Solution {
public:
  bool isSubStructure(TreeNode* A, TreeNode* B) {
    if (nullptr == A || nullptr == B) {
      return false;
    }
    return pot(A, B);
  }

  bool pot(TreeNode* A, TreeNode* B) {
    if (nullptr == A) { return false; }
    bool ismatch = false;
    if (A->val == B->val) {
      ismatch = match(A->left, B->left) && match(A->right, B->right);
    }
    if (ismatch) { return ismatch; }
    if (pot(A->left, B)) {
      return true;
    }
    return pot(A->right, B);
  }
  bool match(TreeNode* A, TreeNode* B) {
    if (nullptr == B) { return true; }
    if (nullptr == A && nullptr != B) { return false; }
    return (A->val == B->val) && match(A->left, B->left) && match(A->right, B->right);
  }
};

int main() {
    Solution sol;
    Codec cc;
    string data1 = "[3,4,5,1,2]";
    string data2 = "[4,1]";
    cout << (sol.isSubStructure(cc.deserialize(data1), cc.deserialize(data2)) == true) << endl; 
    string data3 = "[1,2,3]";
    string data4 = "[3,1]";
    cout << (sol.isSubStructure(cc.deserialize(data3), cc.deserialize(data4)) == false) << endl;
    return 0;
}
