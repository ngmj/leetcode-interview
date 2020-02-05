#include <stdio.h>
#include <utility>
#include <limits>
#include <string>
#include <iostream>
#include <stack>

#include "serialize_deserialize_tree.hpp"

using namespace std;

class Solution {
public:
    TreeNode* recoverFromPreorder(string s) {
        const char* p = s.c_str();
        size_t pLen = s.size();
        int num = 0;
        int h = 0;
        p = getNumAndLength( p, pLen, num, h );
        if ( nullptr == p )
        {
            return nullptr;
        }
        TreeNode *head = new TreeNode( num );
        stack<pair<TreeNode*, int> > st;
        st.push( make_pair( head, h ) );
        while ( pLen > 0 )
        {
            auto parent = st.top(); 
            p = getNumAndLength( p, pLen, num, h );
            while ( parent.second >= h )
            {
                st.pop();
                parent = st.top();
            }

            TreeNode* parentNode = parent.first;
            TreeNode* currNode = new TreeNode( num );
            if ( nullptr == parentNode->left )
            {
                parentNode->left = currNode;
            } else
            {
                parentNode->right = currNode;
            }
            st.push( make_pair( currNode, h ) );
        }
        return head;
    }

    // 返回下一个
    const char* getNumAndLength( const char   *p,
                                 size_t       &len,
                                 int          &num,
                                 int          &h ) const
    {
        if ( 0 == len )
        {
            return nullptr;
        }

        h = 0;
        num = 0;
        while ( len > 0 && '-' == *p )
        {
            h++;
            p++;
            len--;
        }

        while ( len > 0 && '-' != *p )
        {
            num = num * 10 + *p - '0';
            p++;
            len--;
        }
        return p;
    }

private:
};

int main()
{
    string s = "1-2--3---4-5--6---7"; 
    Solution solution;
    TreeNode * head = solution.recoverFromPreorder( s );
    
    PrintTree( head );
    return 0;
}
