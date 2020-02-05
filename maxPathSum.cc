#include <stdio.h>
#include <limits>
#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {} 
};
int nullVal = std::numeric_limits<int>::lowest();

class Solution {
    int maxSum;
public:
    int maxPathSum(TreeNode* root) {
        maxSum = std::numeric_limits<int>::lowest();
        maxOldPathSum( root );
        return maxSum;
    }

    // 返回包含root节点（不掉头）的最大路径，即std::max( root + left, root + right )
    // 计算过程中更新maxSum（可掉头情况）
    int maxOldPathSum( TreeNode* root ) {
        if ( nullptr == root )
        {
            return std::numeric_limits<int>::lowest();
        }

        int maxLeft = maxOldPathSum( root->left );
        int maxRight = maxOldPathSum( root->right );
        int maxPriPathSum = root->val;
        if ( maxLeft < 0 && maxRight < 0 )
        {
            maxSum = std::max( maxSum, root->val );
        } else if ( maxLeft < 0 )
        {
            maxSum = std::max( maxSum, root->val + maxRight );
            maxPriPathSum += maxRight;
        } else if ( maxRight < 0 )
        {
            maxSum = std::max( maxSum, root->val + maxLeft );
            maxPriPathSum += maxLeft;
        } else
        {
            maxSum = std::max( maxSum, root->val + maxLeft + maxRight );
            maxPriPathSum = std::max( root->val + maxLeft, root->val + maxRight );
        }
        return maxPriPathSum;
    }
};

// 假设负数表示nullptr
TreeNode* newTree( vector<int> &vals )
{
    size_t sz = vals.size();
    if ( sz < 1 )
    {
        return nullptr;
    }
    TreeNode* root = new TreeNode( vals[0] );
    queue<TreeNode*> q;
    q.push( root  );

    size_t i = 1;
    while ( !q.empty() )
    {
        TreeNode *tmp = q.front();
        q.pop();
        if ( i + 1 > sz )
        {
            continue;
        }
        int leftVal = vals[i++];
        if ( leftVal != nullVal )
        {
            tmp->left = new TreeNode( leftVal );
            q.push( tmp->left );
        }

        if ( i + 1 > sz )
        {
            continue;
        }
        int rightVal = vals[i++];
        if ( rightVal != nullVal )
        {
            tmp->right = new TreeNode( rightVal );
            q.push( tmp->right );
        }
    }
    return root;
}

void DelTree( TreeNode* root )
{
    if ( nullptr == root )
    {
        return;
    }
    DelTree( root->left );
    DelTree( root->right );
    if ( root )
    {
        delete root;
    }
}

void PrintTree( TreeNode* root )
{
    if ( nullptr == root )
    {
        return;
    }
    
    queue<TreeNode*> q;
    q.push( root );
    while ( !q.empty() )
    {
        TreeNode* tmp = q.front();
        q.pop();
        if ( tmp )
        {
            fprintf( stdout, "%d\t", tmp->val );
            q.push( tmp->left );
            q.push( tmp->right );
        }
    }
}

int main()
{
    vector<int> vals = { -10, 9, 20, nullVal, nullVal, 15, 7 };
    // vector<int> vals = { -3, nullVal, -2 };
    TreeNode* root = newTree( vals );

    Solution solution;
    fprintf( stdout, "%d\n", solution.maxPathSum( root ) );

    PrintTree( root );
    DelTree( root );
    return 0;
}
