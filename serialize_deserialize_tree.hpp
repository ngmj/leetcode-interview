#include <string.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {} 
};

class Codec {
public:
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if ( nullptr == root )
        {
            return "";
        }
        
        string data;
        data.append( "[" );
        queue<TreeNode*> q;
        q.push( root );
        while ( !q.empty() )
        {
            TreeNode* tmp = q.front();
            q.pop();
            if ( tmp )
            {
                data.append( to_string( tmp->val ) + "," );
                q.push( tmp->left );
                q.push( tmp->right );
            } else
            {
                data.append( "null," );
            }
        }

        if ( data.size() > 1 )
        {
            data[data.size() - 1] = ']';
        } else
        {
            data.append( "]" );
        }
        return data;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if ( '[' != data[0] || ']' != data[data.size() - 1] )
        {
            return nullptr;
        }

        vector<char*> rstVec;
        data[data.size() - 1] = '\0';
        split( (char*)data.c_str() + 1, ',', rstVec );

        if ( rstVec.size() < 1 || "null" == rstVec[0] )
        {
            return nullptr;
        }

        TreeNode* root = new TreeNode( atoi( rstVec[0] ) );
        queue<TreeNode*> q;
        q.push( root  );

        size_t i = 1;
        size_t sz = rstVec.size();
        while ( !q.empty() )
        {
            TreeNode *tmp = q.front();
            q.pop();
            if ( i + 1 > sz )
            {
                continue;
            }
            char* leftVal = rstVec[i++];
            if ( 0 != strncmp( "null", leftVal, 4 ) )
            {
                tmp->left = new TreeNode( atoi( leftVal ) );
                q.push( tmp->left );
            }

            if ( i + 1 > sz )
            {
                continue;
            }
            char* rightVal = rstVec[i++];
            if ( 0 != strncmp( "null", rightVal, 4 ) )
            {
                tmp->right = new TreeNode( atoi( rightVal ) );
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

private:
    void split( char *pSrc, const char c, vector<char*> &rstVec )
    {
        if ( nullptr == pSrc )
        {
            return;
        }

        char *tmp = pSrc;
        char* seq = tmp;
        while ( *tmp != '\0' )
        {
            if ( *tmp == c )
            {
                *tmp = '\0';
                if ( seq != tmp )
                {
                    rstVec.push_back( seq );
                }
                seq = tmp + 1;
            }
            tmp++;
        }

        if ( seq != tmp )
        {
            rstVec.push_back( seq );
        }
        return;
    }
};

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

/*
int main()
{
    string data = "[1,2,3,null,null,4,5]";
    Codec cc;
    TreeNode *head = cc.deserialize( data );
    PrintTree( head );
    cout << cc.serialize( head ) << endl;
    return 0;
}
*/
