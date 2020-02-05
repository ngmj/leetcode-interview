
#include <stdio.h>
#include <vector>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) 
    {
        if ( nullptr == head )
        {
            return head;
        }
        ListNode tmpNode(0);
        ListNode* prev = &tmpNode;
        prev->next = head; 
        ListNode* current = head;
        ListNode* next = current->next;            
        bool bCurDel = false;
        while ( next )
        {
            if ( current->val == next->val )
            {
                next = next->next;
                bCurDel = true;
            } else if ( bCurDel )
            {
                prev->next = next;
                current = next;
                next = next->next;
                bCurDel = false;
            } else
            {
                prev = current;
                current = next;
                next = next->next;
            }
        }
        if ( bCurDel )
        {
            prev->next = next;
            current = next;
            bCurDel = false;
        }
        head = tmpNode.next;
        return head;
    }
};

ListNode* newList( vector<int> &vals )
{
    ListNode *tmp = new ListNode(0);
    ListNode *tmpHead = tmp;
    for ( auto &val: vals )
    {
        ListNode* h = new ListNode( val );
        tmp->next = h;
        tmp = h;
    }
    tmp = tmpHead;
    delete tmp;
    return tmp->next;
}

void DelList( ListNode* head )
{
    while ( head )
    {
        ListNode *tmp = head->next;
        delete head;
        head = tmp;
    }
}

void PrintList( ListNode* head )
{
    while ( head )
    {
        fprintf( stdout, "%d\t", head->val );
        head = head->next;
    }
}

int main()
{
    vector<int> vals = { 1,2,3,3,4,4,5 };
    ListNode* head = newList( vals );

    Solution solution;
    ListNode* dup = solution.deleteDuplicates( head );
    PrintList( dup );
    DelList( dup );
    return 0;
}
