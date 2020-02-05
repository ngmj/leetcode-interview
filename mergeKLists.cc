
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
    ListNode* mergeKLists(vector<ListNode*>& head) 
    {
        size_t len = head.size();
        if ( len < 1 )
        {
            return nullptr;
        } else if ( len < 2 )
        {
            return head[0];
        }
        size_t span = ( len + 1 ) / 2;
        size_t lastResLen = len;
        while ( span > 1 )
        {
            for ( size_t i = 0; i < span; i++ )
            {
                if ( i + span >= lastResLen )
                {
                    break;
                }
                head[i] = mergeKLists( head[i], head[i+span] );
            }
            lastResLen = span;
            span = ( span + 1 ) / 2;
        }
        return mergeKLists( head[0], head[1] );
    }

    ListNode* mergeKLists(ListNode *list1, ListNode *list2) {
        if ( nullptr == list1 )
        {
            return list2;
        } else if ( nullptr == list2 )
        {
            return list1;
        }

        ListNode newList(0);
        ListNode *tmp = &newList;
        while ( nullptr != list1 
                && nullptr != list2 )
        {
            if ( list1->val > list2->val )
            {
                tmp->next = list2;
                list2 = list2->next;
            } else 
            {
                tmp->next = list1;
                list1 = list1->next;
            } 
            tmp = tmp->next;
        }

        if ( nullptr != list1 )
        {
            tmp->next = list1;
        } else 
        {
            tmp->next = list2;
        }
        return newList.next;
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
    vector<int> val1 = { 1, 4, 5 };
    vector<int> val2 = { 1, 3, 4 };
    vector<int> val3 = { 2, 6 };
    ListNode* head1 = newList( val1 );
    ListNode* head2 = newList( val2 );
    ListNode* head3 = newList( val3 );
    vector<ListNode*> lists;
    lists.push_back( head1 );
    lists.push_back( head2 );
    lists.push_back( head3 );

    Solution solution;
    ListNode* mergeList = solution.mergeKLists( lists );
    PrintList( mergeList );
    DelList( mergeList );
    return 0;
}
