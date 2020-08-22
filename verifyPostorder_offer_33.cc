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
 * 思路, (i,j)找到首个比val[j]大的值，划分成两个子数组(i, m-1) (m, j-1)分别递归验证，
 *       注意在找m的过程中，要一边找，一边验证val(i, m-1) < val[j], val(m, j-1) > val[j]
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
    return searhAndCheck(postorder, 0, postorder.size()-1);
  }
  bool searhAndCheck(const vector<int>& postorder, int i, int j) {
    if (i >= j) { return true; }
    // 找到首个比postorder[j]大的值下标m，[i, m-1], [m, j-1]
    int a = i;
    while (postorder[a] < postorder[j]) { ++a; };
    int m = a;
    while (postorder[a] > postorder[j]) { ++a; };
    return a == j && searhAndCheck(postorder, i, m-1) && searhAndCheck(postorder, m, j-1);
  }
};

int main() {
    Solution sol;
    cout << (sol.verifyPostorder({1,2,5,3}) == true) << endl;
    cout << (sol.verifyPostorder({1,3,2}) == true) << endl;
    cout << (sol.verifyPostorder({1,6,3,2,5}) == false) << endl;
    cout << (sol.verifyPostorder({1,3,2,6,5}) == true) << endl;
    return 0;
}
