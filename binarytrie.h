#pragma once

#include <array>

class BinaryTrieIterator {
private:
    struct Node {
        uint16_t word_;
        std::array<Node*, 2> links_;

        Node();
        ~Node();
    };

    Node* current_;
    BinaryTrieIterator(Node* current);

public:
    void Move(char path, bool push = false);
    bool IsTerminal();
    uint16_t GetWord();
    void SetWord(uint16_t word);

    friend class BinaryTrie;
};

class BinaryTrie {
private:
    BinaryTrieIterator begin_;

public:
    BinaryTrie();
    ~BinaryTrie();

    void AddWord(uint16_t word, const char* path, size_t path_len);
    BinaryTrieIterator Begin();

    void Clear();
};