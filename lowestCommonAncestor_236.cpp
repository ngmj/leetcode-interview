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
 * https://leetcode-cn.com/problems/lowest-common-ancestor-of-a-binary-tree/
 * 二叉树公共祖先，采用后序遍历 
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
        // 方法1 
        // TreeNode* anc = nullptr;
        // isMatch(root, p, q, anc);
        // return anc;
        // 方法2
        return findPorQ(root, p, q);
    }
    // 返回p或q是否在root这颗树里，ancestor表示公共祖先 
    bool isMatch( TreeNode* root, TreeNode* p, TreeNode* q, TreeNode* &ancestor )
    {
        if ( nullptr == root ) return false;
        // root是q或p就返回是错的，因为另一可能在的左右子树，所以实际要继续便利root的左右子树
        // if ( root == p || root == q ) return true;
        TreeNode* ancL = nullptr, *ancR = nullptr;
        bool bL = isMatch( root->left, p, q, ancL );
        bool bR = isMatch( root->right, p, q, ancR );
        // 跨两个分支
        if ( bL == true && bR == true )
        {
            ancestor = root;
            return true;
        } else if ( ( bL || bR ) )
        {
            if ( root == p || root == q )
            {
                ancestor = root;
            } else
            {
                ancestor = ancL != nullptr ? ancL : ancR;
            }
            return true;
        }
        if ( root == p || root == q )
        {
            return true;
        }
        return false;
    }
    // 返回公共祖先
    TreeNode* findPorQ( TreeNode* root, TreeNode* p, TreeNode* q )
    {
        if ( nullptr == root || root == p || root == q ) return root;
        TreeNode *l = findPorQ( root->left, p, q );
        TreeNode *r = findPorQ( root->right, p, q );
        if ( l && r ) return root;
        return l != nullptr ? l : r;
    }
};

TreeNode* getNode( TreeNode* root, int val )
{
    if ( nullptr == root ) return nullptr;
    if ( val == root->val )
    {
        return root;
    } 
    TreeNode* l = getNode( root->left, val );
    TreeNode* r = getNode( root->right, val );
    return l != nullptr ? l : r; 
}

int main()
{
    Solution sol;
    string data = "[3,5,1,6,2,0,8,null,null,7,4]"; 
    Codec cc;
    TreeNode *head = cc.deserialize( data );
    TreeNode *p = getNode(head, 3);
    TreeNode *q = getNode(head, 1);
    TreeNode* node = sol.lowestCommonAncestor( head, p, q );
    cout << (node->val == 3) << endl;
    return 0;
}
