
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
    ListNode* reverseKGroup(ListNode* head, int k) 
    {
        ListNode* phead = nullptr;
        ListNode** ptail = &phead;
        ListNode* seg_head = nullptr;
        ListNode** seg_tail = &seg_head;
        while ( nullptr != head )
        {
            seg_head = nullptr;
            seg_tail = &seg_head;
            for ( size_t i = 0; i < k && head != nullptr; i++ )
            {
                ListNode* tmp = head;
                head = head->next;
                tmp->next = seg_head;
                seg_head = tmp;
            }
            *ptail = seg_head;
            ptail = seg_tail;
        }
        return phead;
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
    vector<int> val = { 1, 2, 3, 4, 5 };
    ListNode* head = newList( val );

    Solution solution;
    ListNode* revList = solution.reverseKGroup( head, 1 );
    PrintList( revList );
    DelList( revList );
    return 0;
}
