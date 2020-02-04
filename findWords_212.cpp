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
#include "trie.hpp"

/*
 * stack: top(), pop(), push(), empty()
 * queue: front(), back(), push(), pop(), empty()
 * priority_queue: top(), push(), pop(), empty()
 *  std::priority_queue<int> 默认是大根堆，
 *  std::priority_queue<int, std::vector<int>, std::greater<int> > 小根堆
 * deque: front(), back(), push_back(), pop_back, push_front, pop_front(), empty(), clear()
 * */
using namespace std;

typedef vector<vector<int>> VVI;
typedef vector<int> VI;
typedef long long LL;
LL MAX_LL = std::numeric_limits<LL>::max();;
int MAX_INT = std::numeric_limits<int>::max();;

class Solution {
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        if (board.size() < 1 || words.size() < 1) {
            return vector<string>();
        }

        Trie t;
        for (auto &word: words) {
            t.insert(word);
        }
        
        vector<vector<bool>> visited(board.size(), vector<bool>(board[0].size(), false));
        int m = board.size();
        int n = board[0].size();
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                dfs(board, i, j, visited, "", &t);
            }
        }
        vector<string> result;
        for (auto &word: this->ans) {
            result.push_back(word);
        }
        return result;
    }

    void dfs(vector<vector<char>>& board, int i, int j, vector<vector<bool>> &visited, string word, Trie *root) {
        int m = board.size();
        int n = board[0].size();
        if (i < 0 || i >= m || j < 0 || j >= n || visited[i][j]) {
            return;
        }

        word = word + board[i][j];
        Trie *node = root->getSubTrie(board[i][j]);
        if (node && node->isWord()) {
            this->ans.insert(word);
        } else if ( nullptr == node ) {
            return; 
        }
        
        visited[i][j] = true;

        dfs(board, i, j+1, visited, word, node);
        dfs(board, i+1, j, visited, word, node);
        dfs(board, i, j-1, visited, word, node);
        dfs(board, i-1, j, visited, word, node);

        visited[i][j] = false;
    }
private:
    unordered_set<string> ans;
};

int main() {
    Solution sol;
    /*
    vector<string> words = {"oath","pea","eat","rain"};
    vector<vector<char>> board = {
        {'o','a','a','n'},
        {'e','t','a','e'},
        {'i','h','k','r'},
        {'i','f','l','v'}};
    */
    
    vector<string> words = {"aaab","aaa"};
    vector<vector<char>> board = {
        {'a','b'},
        {'a','a'}};
    vector<string> ans = sol.findWords(board, words);
    cout << VectorToString(ans) << endl;
    return 0;
}
