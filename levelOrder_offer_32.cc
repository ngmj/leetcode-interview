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
#include "serialize_deserialize_tree.hpp"

/*
 * stack: top(), pop(), push(), empty()
 * queue: front(), back(), push(), pop(), empty()
 * priority_queue: top(), push(), pop(), empty()
 *  std::priority_queue<int> 默认是大根堆，
 *  std::priority_queue<int, std::vector<int>, std::greater<int> > 小根堆
 * deque: front(), back(), push_back(), pop_back, push_front, pop_front(), empty(), clear()
 * */
/**
* Definition for a binary tree node.
* struct TreeNode {
*     int val;
*     TreeNode *left;
*     TreeNode *right;
*     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
* };
BFS, 通过获取queue的size 得到当前层的节点数
每次保存vector，然后根据层数决定正序 or 逆序输出
*/
using namespace std;

typedef vector<vector<int>> VVI;
typedef vector<int> VI;
typedef long long LL;
LL MAX_LL = std::numeric_limits<LL>::max();;
int MAX_INT = std::numeric_limits<int>::max();;

class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> ans;
        queue<TreeNode*> q;
        if ( nullptr == root ) {
            return ans;
        }
        q.push(root);
        int level = 1;
        while ( !q.empty() ) {
            vector<int> level_ans;
            for ( int i = q.size(); i > 0; i-- ) {
                TreeNode* data = q.front();
                q.pop();
                level_ans.push_back( data->val );
                if ( data->left ) {
                    q.push( data->left );
                }
                if ( data->right ) {
                    q.push( data->right );
                }
            }
            if (0 == level++ % 2) {
              reverse(level_ans.begin(), level_ans.end());
            }
            ans.push_back( move( level_ans ) );
        }
        return ans;
    }   
};

void print( const vector<vector<int>> &levels ) {
    for ( auto &vec: levels ) {
        cout << "[ ";
        for ( auto &v: vec ) {
            cout << v << " ";
        }
        cout << "]" << endl;
    }
}

int main() {    
    string data = "[3,9,20,null,null,15,7]";
    Codec cc;
    TreeNode* root = cc.deserialize( data );

    Solution sol;
    vector<vector<int>> levels = sol.levelOrder( root );
    print( levels );
    return 0;
}
