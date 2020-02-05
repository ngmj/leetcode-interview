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
 * https://leetcode-cn.com/problems/word-search/
 * dfs搜索，两层for循环board
 * */
using namespace std;

typedef vector<vector<int>> VVI;
typedef vector<int> VI;
typedef long long LL;
LL MAX_LL = std::numeric_limits<LL>::max();;
int MAX_INT = std::numeric_limits<int>::max();;

class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        if (board.size() < 1 || word.size() < 1) {
            return false;
        }
        int m = board.size();
        int n = board[0].size();
        vector<vector<bool>> visisted(m, vector<bool>(n, false));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if ( dfs(board, visisted, word, i, j, 0) ) {
                    return true;
                }
            }
        }
        return false;
    }

    bool dfs(vector<vector<char>> &board, vector<vector<bool>> &visisted, string &word, int i, int j, int k){
        int m = board.size();
        int n = board[0].size();
        if (i < 0 || i >= m || j < 0 || j >= n || visisted[i][j]) {
            return false;
        }

        if (k < word.size() && board[i][j] == word[k]) {
            if (k == word.size() - 1) {
                return true;
            }
        } else {
            return false;
        }

        visisted[i][j] = true;
        if ( dfs(board, visisted, word, i, j + 1, k + 1) ) {
            return true;
        }
        if ( dfs(board, visisted, word, i + 1, j, k + 1) ) {
            return true;
        }
        if ( dfs(board, visisted, word, i, j - 1, k + 1) ) {
            return true;
        }
        if ( dfs(board, visisted, word, i - 1, j, k + 1) ) {
            return true;
        }
        visisted[i][j] = false;
        return false; 
    }
};

int main() {
    Solution sol;
    vector<vector<char>> board = {
        {'a','b'},
        {'a','a'}};
    cout << sol.exist(board, "aaabc") << endl;
 
    return 0;
}
