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
        if ( cameras.count(root) 
                || cameras.count( root->left ) 
                || cameras.count(root->right) )
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
        if ( cameras.count( node->left ) 
                && cameras.count( node->right ) ) 
        {
            return n + m;
        } else if ( cameras.count( node->left ) || nullptr == node->left ) 
        {
            if ( false == checkNode( node->right ) )
            {
                return n + m;
            } else
            {
                cameras.insert( node );
                return n + m + 1;
            }
        } else if ( cameras.count( node->right ) || nullptr == node->right )
        {
            if ( false == checkNode( node->left ) )
            {
                return n + m;
            } else
            {
                cameras.insert( node );
                return n + m + 1;
            }
        }

        if ( false == checkNode( node->left ) && false == checkNode( node->right ) )
        {
            return n + m;
        }
        
        cameras.insert( node );
        return n + m + 1;
    }

    // 检测node是否需要被监视
    bool checkNode( TreeNode* node )
    {
        if ( cameras.count( node ) )
        {
            return false;
        }
        // 如果是空节点，则当前节点不需要被监视
        if ( nullptr == node )
        {
            return false;
        }
        // NOTE: 如果是叶子节点，则当前节点一定没有被监视
        else if ( ( nullptr == node->left 
                    && nullptr == node->right ) )
        {
            return true;
        }
        
        if ( cameras.count( node->left ) 
                || cameras.count( node->right ) )
        {
            return false;
        }
        return true;
    }
private:
    unordered_set<TreeNode*> cameras;
};

int main()
{
    string data = "[0,0,null,null,0,0,null,null,0,0]"; // 2
    // string data = "[0,0,null,0,null,0,null,null,0]"; // 2
    // string data = "[0,null,0,null,0,null,0]"; // 2
    // string data = "[0]"; // 1
    // string data = "[0,0,null,0,0]"; // 2
    // string data = "[0,null,0,0,0,0,0,null,null,null,0,0,null,null,0,0]"; // 3
    Codec cc;
    TreeNode* root = cc.deserialize( data );

    Solution solution;
    cout << solution.minCameraCover( root ) << endl;;

    cc.DelTree( root );
    return 0;
}
