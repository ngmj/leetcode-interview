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
    // 找元素比它左边的都要小，比右边的都要大，返回一个元素的下标即可
    // 如果存在，返回下标
    // 如果不存在，返回-1
    // 分治法查找
    int find_target(vector<int> &val) {
        int ans = -1;
        find_target_index(val, 0, val.size() - 1, ans);
        return ans;
    } 

    // 返回最大最小元素下标
    pair<int, int> find_target_index(vector<int> &val, int s, int e, int &ans) {
        if (e == s) {
            ans = s;
            return make_pair(val[s], val[s]);
        }

        int m = s + (e - s) / 2;
        int ansL = -1, ansR = -1;
        const auto& pairL = find_target_index(val, s, m, ansL);
        const auto& pairR = find_target_index(val, m + 1, e, ansR);
        
        if (ansL > -1 && val[ansL] > pairR.first) {
            ans = ansL;
        } else if (ans < 0 && ansR > -1 && val[ansR] < pairL.second) {
            ans = ansR;
        }

        return make_pair(max(pairL.first, max(val[m], pairR.first)), 
               min(pairL.second, min(val[m], pairR.second)));
    }

    // 查找元素比它左边的都要小，比右边的都要大，返回所有这样的元素
    // 动态规划求解
    // 从前到后扫描，arrayL[i]表示截止到第i个元素（不含第i个）的最小值
    // 从后往前扫描，arrayR[i]表示截止到第i个元素（不含第i个）的最大值
    // 再扫描一遍，根据arrayR[i] < val[i] < arrayL[i]
    vector<int> find_all_target(vector<int> &val) {
        vector<int> ans;
        vector<int> minL(val.size(), MAX_INT);
        vector<int> maxR(val.size(), MIN_INT);
        for (int i = 1; i < val.size(); ++i) {
            minL[i] = min(minL[i-1], val[i-1]); 
        }

        for (int i = val.size() - 2; i >= 0; --i) {
            maxR[i] = max(maxR[i+1], val[i+1]);
        }

        for (int i = 0; i < val.size(); ++i) {
            if (val[i] < minL[i] && val[i] > maxR[i]) {
                ans.push_back(val[i]);
            }
        }
        return ans;
    }
};

int main() {
    Solution sol;
    {
        vector<int> v0 = {12, 11, 8, 5, 4};
        cout << sol.find_target(v0) << endl;
        vector<int> v1 = {12, 12, 8, 5, 4};
        cout << sol.find_target(v1) << endl;
        vector<int> v2 = {1, 2, 3, 4, 5};
        cout << sol.find_target(v2) << endl;
        vector<int> v3 = {9, 11, 8, 5, 6};
        cout << sol.find_target(v3) << endl;
    }
    cout << "=====================================" << endl;
    {
        vector<int> v1 = {12, 11, 8, 5, 4};
        cout << VectorToString(sol.find_all_target(v1)) << endl;
        vector<int> v2 = {1, 2, 3, 4, 5};
        cout << VectorToString(sol.find_all_target(v2)) << endl;
        vector<int> v3 = {9, 11, 8, 5, 6};
        cout << VectorToString(sol.find_all_target(v3)) << endl;
    }
    return 0;
}
