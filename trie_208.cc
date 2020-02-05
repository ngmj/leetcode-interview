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
 * */
using namespace std;

typedef vector<vector<int>> VVI;
typedef vector<int> VI;
typedef long long LL;
LL MAX_LL = std::numeric_limits<LL>::max();;
int MAX_INT = std::numeric_limits<int>::max();;

const int TRIE_NODE_NUM = 26;

struct TrieNode {
    TrieNode *child[TRIE_NODE_NUM];
    bool is_word;
    TrieNode() : is_word(false) {
        for ( int i = 0; i < TRIE_NODE_NUM; i++ ) {
            child[i] = nullptr;
        }
    }
    ~TrieNode() {
        for ( int i = 0; i < TRIE_NODE_NUM; i++ ) {
            if ( child[i] ) {
                delete child[i];
                child[i] = nullptr;
            }
        }
    }
};

class Trie { 
public:
    /** Initialize your data structure here. */
    Trie() {
        root_ = new TrieNode();
    }

    ~Trie() {
        delete root_;
    }

    /** Inserts a word into the trie. */
    void insert(string word) {
        TrieNode *node = root_;
        for ( auto &c: word ) {
            TrieNode *&currNode = node->child[c - 'a'];
            if ( nullptr == currNode ) {
                currNode = new TrieNode();
            }
            node = currNode;
        }
        node->is_word = true;
    }

    /** Returns if the word is in the trie. */
    bool search(string word) {
        TrieNode *node = root_;
        for ( auto &c: word ) {
            TrieNode *currNode = node->child[c - 'a'];
            if ( nullptr == currNode ) {
                return false;
            }
            node = currNode;
        }
        return node->is_word == true;
    }

    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        TrieNode *node = root_;
        for ( auto &c: prefix ) {
            TrieNode *currNode = node->child[c - 'a'];
            if ( nullptr == currNode ) {
                return false;
            }
            node = currNode;
        }
        return true;
    }
private:
    TrieNode *root_;
};

int main() {
    Trie* obj = new Trie();
    obj->insert("apple");
    cout << ( obj->search("apple") == true ) << endl;
    cout << ( obj->search("app") == false ) << endl;
    cout << ( obj->startsWith("app") == true ) << endl;
    obj->insert("app");
    cout << ( obj->search("app") == true ) << endl;
    delete obj;
    return 0;
}
