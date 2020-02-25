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
 * https://leetcode-cn.com/problems/find-first-and-last-position-of-element-in-sorted-array/
 * 实现lower_bound和upper_bound
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
    vector<int> searchRange(vector<int>& nums, int target) {
        if (nums.size() < 1) {
            return vector<int>{-1, -1};
        }
        int ansLower = -1, ansUpper = -1;
        auto iter = lower_bound(nums.begin(), nums.end(), target);
        ansLower = iter != nums.end() && *iter == target ? iter - nums.begin() : -1;
        iter = upper_bound(nums.begin(), nums.end(), target);
        if (nums.end() == iter && nums[nums.size() - 1] == target) {
            ansUpper = nums.size() - 1;
        } else if (iter != nums.begin() && *(iter - 1) == target) {
            ansUpper = iter - nums.begin() - 1;
        } else {
            ansUpper = -1;
        }
        return vector<int>{ansLower, ansUpper};
    }
};

int main() {
    Solution sol;
    vector<int> v1 = {5,7,7,8,8,10};
    cout << VectorToString(sol.searchRange(v1, 8)) << endl;
    cout << VectorToString(sol.searchRange(v1, 6)) << endl;
    vector<int> v2 = {5,7,7,8,8,10};
    return 0;
}
