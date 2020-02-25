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
 *
 * https://leetcode-cn.com/problems/search-a-2d-matrix-ii/
 * 基于中间一条线，竖着扫描，直到找到一个值，该值比target大，前它的前一个值比target小（二分查找这样的值）
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
        if (matrix.size() < 1) {
            return false;
        }
        return searchMatrix(matrix, 0, 0, matrix.size()-1, matrix[0].size()-1, target);
    }

    bool searchMatrix(vector<vector<int>>& matrix, int si, int sj, int ei, int ej, int target) {
        if (si > ei || sj > ej) {
            return false; 
        }

        int mj = sj + (ej - sj) / 2;
        // 基于中间一条线，竖着扫描，直到找到一个值，该值比target大，前它的前一个值比target小
        /*
        int i = si;
        while (i <= ei && matrix[i][mj] < target) {
            ++i;
        }*/
        // 优化一下进行二分查找这样的值
        int s = si, e = ei;
        while (s <= e) {
            int m = s + (e - s) / 2;
            if (matrix[m][mj] == target) {
                return true;
            } else if (matrix[m][mj] < target) {
                s = m + 1;
            } else {
                e = m - 1;
            }
        }
        // e是下界首个小于target的下标，s是上界首个大于target的下标
        // 这里取s
        return searchMatrix(matrix, s, sj, ei, mj - 1, target) 
            || searchMatrix(matrix, si, mj + 1, s - 1, ej, target);
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
