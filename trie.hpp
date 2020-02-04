#include <string>

class Trie { 
    enum { TRIE_NODE_NUM = 26 };
public:
    /** Initialize your data structure here. */
    Trie() : is_word_(false) {
    }

    ~Trie() {
        for ( int i = 0; i < TRIE_NODE_NUM; i++ ) {
            if ( child_[i] ) {
                delete child_[i];
                child_[i] = nullptr;
            }
        }
    }

    /** Inserts a word into the trie. */
    void insert(const std::string &word) {
        if ( word.size() < 1 ) {
            return;
        }
        Trie *t = this;
        for ( auto &c: word ) {
            Trie *&currTrie = t->child_[c - 'a'];
            if ( nullptr == currTrie ) {
                currTrie = new Trie();
            }
            t = currTrie;
        }
        t->is_word_ = true;
    }

    /** Returns if the word is in the trie. */
    bool search(const std::string &word) {
        Trie *t = this;
        for ( auto &c: word ) {
            Trie *currTrie = t->child_[c - 'a'];
            if ( nullptr == currTrie ) {
                return false;
            }
            t = currTrie;
        }
        return t->is_word_ == true;
    }

    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(const std::string &prefix) {
        Trie *t = this;
        for ( auto &c: prefix ) {
            Trie *currTrie = t->child_[c - 'a'];
            if ( nullptr == currTrie ) {
                return false;
            }
            t = currTrie;
        }
        return true;
    }

    Trie* getSubTrie(const char c) {
        return this->child_[c - 'a'];
    }

    bool isWord() const {
        return is_word_;
    }

private:
    Trie *child_[TRIE_NODE_NUM] {nullptr};
    bool is_word_;
};

