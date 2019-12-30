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
 * https://leetcode-cn.com/problems/lowest-common-ancestor-of-a-binary-search-tree/
 * 二叉搜索树的公共祖先，很简单，判断两个节点的val值跟当前节点的val比较就可以确定
 * */
using namespace std;

typedef vector<vector<int>> VVI;
typedef vector<int> VI;
typedef long long LL;
LL MAX_LL = std::numeric_limits<LL>::max();;
int MAX_INT = std::numeric_limits<int>::max();;

/**
 *   Definition for a binary tree node.
 *   struct TreeNode {
 *       int val;
 *       TreeNode *left;
 *       TreeNode *right;
 *       TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 *   };
 */
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if ( root == p || root == q ) return root;
        if ( root->val < p->val && root->val < q->val ) return lowestCommonAncestor(root->right, p, q);
        else if ( root->val > p->val && root->val > q->val ) return lowestCommonAncestor(root->left, p, q);
        return root;
    }
};

TreeNode* getNode( TreeNode* root, int val )
{
    if ( val == root->val )
    {
        return root;
    } else if ( val < root->val )
    {
        return getNode(root->left, val);
    }
    return getNode(root->right, val);
}

int main()
{
    Solution sol;
    string data = "[6,2,8,0,4,7,9,null,null,3,5]";
    Codec cc;
    TreeNode *head = cc.deserialize( data );
    TreeNode *p = getNode(head, 3);
    TreeNode *q = getNode(head, 5);
    TreeNode* node = sol.lowestCommonAncestor( head, p, q );
    cout << (node->val == 4) << endl;
    return 0;
}
