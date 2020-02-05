
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
        if ( nullptr == head || k < 2 )
        {
            return head;
        }
        
        bool bOnlyOne = false;
        ListNode* lastBegin = nullptr;
        ListNode* begin = head;
        ListNode* end = begin;
        while ( true )
        {
            int span = k;
            while ( --span && begin && end )
            {
                end = end->next;
            }

            if ( nullptr == begin || nullptr == end )
            {
                break;
            }

            ListNode* curBegin = begin; // 当前的begin即为翻转后的end
            ListNode* nextBegin = end->next;
            ListNode* newHead = reverseLists( begin, end );
            if ( false == bOnlyOne )
            {
                head = newHead;
                bOnlyOne = true;
            }

            if ( lastBegin )
            {
                lastBegin->next = newHead;
            }
            lastBegin = curBegin;
            
            begin = nextBegin;
            end = begin;
        }
        return head;
    }

    ListNode* reverseLists(ListNode *begin, ListNode *end) 
    {
        if ( nullptr == begin || nullptr == end || begin == end )
        {
            return begin;
        }

        ListNode* tmp = nullptr;
        ListNode* curr = begin;
        ListNode* next = curr->next;
        while ( next != end )
        {
            tmp = next->next;
            next->next = curr;
            curr = next;
            next = tmp;
        }
        tmp = end->next;
        end->next = curr;
        begin->next = tmp;
        return end;
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
    ListNode* revList = solution.reverseKGroup( head, 3 );
    PrintList( revList );
    DelList( revList );
    return 0;
}
