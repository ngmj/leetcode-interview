#include <stdio.h>
#include <limits>
#include <string>
#include <iostream>
#include <unordered_set>

#include "serialize_deserialize_tree.hpp"

using namespace std;

class Solution {
public:
    int minCameraCover(TreeNode* root) {
        if ( nullptr == root ) 
        {
            return 0;
        }
        int n = getCameraCover( root, nullptr );
        if ( 1 == root->val ) 
        {
            return n;
        } else
        {
            return n + 1;
        }
    }

    int getCameraCover(TreeNode* node, TreeNode* parent) {
        if ( nullptr == node 
                || ( nullptr == node->left && nullptr == node->right ) )
        {
            return 0;
        }

        int n = getCameraCover( node->left, node );
        int m = getCameraCover( node->right, node );
        if ( ( nullptr == node->left || 1 == node->left->val )
                && ( nullptr == node->right || 1 == node->right->val ) ) 
        {
            return n + m;
        } else if ( nullptr == node->left || 1 == node->left->val ) 
        {
            if ( nullptr == node->right )
            {
                return n + m;
            } else
            {
                if ( parent ) parent->val = 1;
                node->val = 1;
                node->right->val = 1;
                return n + m + 1;
            }
        } else if ( nullptr == node->right || 1 == node->right->val ) 
        {
            if ( nullptr == node->left )
            {
                return n + m;
            } else
            {
                if ( parent ) parent->val = 1;
                node->val = 1;
                node->left->val = 1;
                return n + m + 1;
            }
        }

        if ( parent ) parent->val = 1;
        node->val = 1;
        node->left->val = 1;
        node->right->val = 1;
        return n + m + 1;
    }

private:
};

int main()
{
    string data = "[0,0,null,null,0,0,null,null,0,0]"; // 2
    // string data = "[0,0,null,0,null,0,null,null,0]"; // 2
    // string data = "[0,null,0,null,0,null,0]"; // 2
    // string data = "[0]"; // 1
    // string data = "[0,0,null,0,0]"; // 1
    // string data = "[0,null,0,0,0,0,0,null,null,null,0,0,null,null,0,0]"; // 3
    Codec cc;
    TreeNode* root = cc.deserialize( data );

    Solution solution;
    cout << solution.minCameraCover( root ) << endl;;

    cc.DelTree( root );
    return 0;
}
