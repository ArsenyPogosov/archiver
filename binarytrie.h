#pragma once

#include "word.h"

#include <array>

class BinaryTrieIterator {
private:
    struct Node {
        Word::WordType word_;
        std::array<Node*, 2> links_;

        Node();
        ~Node();
    };

    Node* current_;
    BinaryTrieIterator(Node* current);

public:
    void Move(char path, bool push = false);
    bool IsTerminal();
    Word::WordType GetWord();
    void SetWord(Word::WordType word);

    friend class BinaryTrie;
};

class BinaryTrie {
private:
    BinaryTrieIterator begin_;

public:
    BinaryTrie();
    ~BinaryTrie();

    void AddWord(Word::WordType word, const char* path, size_t path_len);
    BinaryTrieIterator Begin();

    void Clear();
};