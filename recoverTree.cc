#include <stdio.h>
#include <limits>
#include <vector>
#include <queue>
#include <unordered_set>

#include "serialize_deserialize_tree.hpp"

using namespace std;

class Solution {
public:
    void recoverTree(TreeNode* root) {
        if ( nullptr == root 
                || ( nullptr == root->left && nullptr == root->right ) )
        {
            return;
        }
        vector<TreeNode*> vec;
        vec.reserve( 10 );
        midVisitTree( root, vec );
        TreeNode *error1 = nullptr, *error2 = nullptr;
        for ( size_t i = 1; i < vec.size(); i++ )
        {
            if ( vec[i]->val < vec[i - 1]->val )
            {
                error1 = vec[i];
            }
        }

        if ( nullptr != error1 )
        {
            for ( size_t i = 0; i < vec.size(); i++ )
            {
                if ( vec[i]->val > error1->val )
                {
                    error2 = vec[i];
                    break;
                }
            }

            if ( nullptr != error2 )
            {
                int tmpVal = error1->val;
                error1->val = error2->val;
                error2->val = tmpVal;
            }
        }
        return;
    }

    void midVisitTree( TreeNode* root, vector<TreeNode*> &vec ) {
        if ( nullptr == root )
        {
            return;
        }

        midVisitTree( root->left, vec );
        vec.push_back( root );
        midVisitTree( root->right, vec );
    }
};

int main()
{
    string data = "[3,1,4,null,null,2]";
    Codec cc;
    TreeNode* root = cc.deserialize( data );

    Solution solution;
    solution.recoverTree( root );

    PrintTree( root );
    cc.DelTree( root );
    return 0;
}
