#include <vector>
#include <limits>
#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <stack>
#include <queue>
#include <deque>
#include <unordered_set>
#include <unordered_map>
#include "string_util.h"

/*
 * stack: top(), pop(), push(), empty()
 * queue: front(), back(), push(), pop(), empty()
 * priority_queue: top(), push(), pop(), empty()
 *  std::priority_queue<int> 默认是大根堆，
 *  std::priority_queue<int, std::vector<int>, std::greater<int> > 小根堆
 * deque: front(), back(), push_back(), pop_back, push_front, pop_front(), empty(), clear()
 * https://leetcode-cn.com/problems/kth-largest-element-in-a-stream/
 * 思路维护一个k元素的小根堆（优先队列）
 * */
using namespace std;

typedef vector<vector<int>> VVI;
typedef vector<int> VI;
typedef long long LL;
LL MAX_LL = std::numeric_limits<LL>::max();;
int MAX_INT = std::numeric_limits<int>::max();;

class KthLargest {
public:
    KthLargest(int k, vector<int>& nums) {
        m_k = k;
        for ( auto &n: nums )
        {
            add(n);
        }
    }

    int add(int val) {
        if ( m_minHeap.size() < m_k )
        {
            m_minHeap.push( val );
        } else if ( val > m_minHeap.top() )
        {
            m_minHeap.pop();
            m_minHeap.push( val );
        }
        return m_minHeap.top();
    }
private:
    int m_k;
    std::priority_queue<int, std::vector<int>, std::greater<int> > m_minHeap;
};

int main()
{
    int k = 3;
    vector<int> arr = {4,5,8,2};
    KthLargest kthLargest(3, arr);
    cout << ( kthLargest.add(3) == 4 ) << endl;
    cout << ( kthLargest.add(5) == 5 ) << endl;
    cout << ( kthLargest.add(10) == 5 ) << endl;
    cout << ( kthLargest.add(9) == 8 ) << endl;
    cout << ( kthLargest.add(4) == 8 ) << endl;
    /*
    kthLargest.add(3);   // returns 4
    kthLargest.add(5);   // returns 5
    kthLargest.add(10);  // returns 5
    kthLargest.add(9);   // returns 8
    kthLargest.add(4);   // returns 8
    */
    return 0;
}
