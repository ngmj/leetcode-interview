#include <stdio.h>
#include <limits>
#include <string>
#include <iostream>
#include <stack>

#include "serialize_deserialize_tree.hpp"

using namespace std;

class Solution {
public:
    int minCameraCover(TreeNode* root) {
        stack<TreeNode*> mystack; int ans = 0;
        TreeNode* last = nullptr;
        if(root == nullptr) {return 0;}
        while(root || !mystack.empty())
        {
            while(root)
            {
               mystack.push(root);
               root = root->left;
            }

                root = mystack.top();
                if(!root->right || root->right == last)  
                {
                    if((root->left && root->left->val == 2) || (root->right && root->right->val == 2))
                    {
                        root->val = 1;
                    }
                    if((root->left && root->left->val == 0) || (root->right && root->right->val == 0))
                    {
                        root->val = 2;
                        ans++;
                    }
                    mystack.pop();
                    last = root;
                    root = nullptr;
                }
                else
                {
                root = root->right;
                }
        }
        if(last->val == 0)
        {
           ans++;
        }
        return ans;   
    }
};

int main()
{
    string data = "[0,0,null,null,0,0,null,null,0,0]";
    Codec cc;
    TreeNode* root = cc.deserialize( data );

    Solution solution;
    cout << solution.minCameraCover( root ) << endl;;

    cc.DelTree( root );
    return 0;
}
