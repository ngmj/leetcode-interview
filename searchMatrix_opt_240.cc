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
 * https://leetcode-cn.com/problems/search-a-2d-matrix-ii/
 * 巧解，从左下角开始（或右上角，仅能是这两处）执行如下操作
 * 0、超出边界 return false
 * 1、val == target return true
 * 2、val > targe 往上走
 * 3、val < target 往左走
 *
 * 时间复杂度是O(m+n)
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
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int i = matrix.size() - 1, j = 0;
        while (i > -1 && j < matrix[0].size()) {
            if (matrix[i][j] == target) {
                return true;
            } else if (matrix[i][j] > target) {
                --i;
            } else {
                ++j;
            }
        }
        return false;
    }
};

int main() {
    Solution sol;
    vector<vector<int>> matrix1 = {
          {1,   4,  7},
          {2,   5,  8},
          {3,   6,  9} };
    cout << sol.searchMatrix(matrix1, 5) << endl;

    vector<vector<int>> matrix2 = {{5,6,10,14},{6,10,13,18},{10,13,18,19}};
    cout << sol.searchMatrix(matrix2, 14) << endl;

    vector<vector<int>> matrix = {
          {1,   4,  7, 11, 15},
          {2,   5,  8, 12, 19},
          {3,   6,  9, 16, 22},
          {10, 13, 14, 17, 24},
          {18, 21, 23, 26, 30} };
    cout << sol.searchMatrix(matrix, 5) << endl;
    return 0;
}
