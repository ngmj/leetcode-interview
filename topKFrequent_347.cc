#include <vector>
#include <limits>
#include <iostream>
#include <algorithm>
#include <map>
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
 *
 * iter = lower_bound(start, end, val) 返回[start, end)>=val的第一个位置（下界）
 * iter = upper_bound(start, end, val) 返回[start, end)>val的第一个位置（上界）
 * 如(11,12) lower_bound查找11，返回0；upper_bound则返回1
 * https://leetcode-cn.com/problems/top-k-frequent-elements/
 * 统计每个元素出现次数，然后维护小根堆
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
    struct Node {
        int val;
        int num;
        explicit Node(int v) : val(v), num(1) {}
        bool operator < (const Node &n) const 
        { 
            return num < n.num;
        }
        bool operator > (const Node &n) const
        {
            return !operator<(n);
        }
    };
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, Node> val_2_num(nums.size());
        for (auto v: nums) {
            auto iter = val_2_num.find(v);
            if (val_2_num.end() != iter) {
                iter->second.num++;
            } else {
                val_2_num.insert(make_pair(v, Node(v)));
            }
        }
        priority_queue<Node, vector<Node>, greater<Node>> st;
        for (auto &kv: val_2_num) {
            if (st.size() < k) {
                st.push(kv.second);
                continue;
            }

            if (st.top() < kv.second) {
                st.pop();
                st.push(kv.second);
            }
        }
        vector<int> ans;
        ans.reserve(k);
        while (!st.empty()) {
            ans.push_back(st.top().val);
            st.pop();
        }
        return ans;
    } 
};

int main() {
    Solution sol;
    vector<int> n1 = {1,1,1,2,2,3};
    cout << VectorToString(sol.topKFrequent(n1, 2)) << endl;
    vector<int> n2 = {3,0,1,0};
    cout << VectorToString(sol.topKFrequent(n2, 1)) << endl;
    return 0;
}
