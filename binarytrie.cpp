#include "binarytrie.h"

BinaryTrieIterator::Node::Node() {
    word_ = -1;
    links_[0] = links_[1] = 0;
}

BinaryTrieIterator::Node::~Node() {
    if (links_[0]) {
        delete links_[0];
    }
    if (links_[1]) {
        delete links_[1];
    }
}

BinaryTrieIterator::BinaryTrieIterator(Node* current) {
    current_ = current;
}

void BinaryTrieIterator::Move(char path, bool push) {
    if (!(current_->links_[static_cast<size_t>(path)])) {
        if (!push) {
            throw std::out_of_range("BinaryTrie out of range");
        }
        current_->links_[static_cast<size_t>(path)] = new Node();
    }
    current_ = current_->links_[static_cast<size_t>(path)];
}

bool BinaryTrieIterator::IsTerminal() {
    return current_->word_ != static_cast<Word::WordType>(-1);
}

Word::WordType BinaryTrieIterator::GetWord() {
    return current_->word_;
}

void BinaryTrieIterator::SetWord(Word::WordType word) {
    current_->word_ = word;
}

BinaryTrie::BinaryTrie() : begin_(new BinaryTrieIterator::Node()) {
}

BinaryTrie::~BinaryTrie() {
    delete begin_.current_;
}

void BinaryTrie::AddWord(Word::WordType word, const char* path, size_t path_len) {
    BinaryTrieIterator it = begin_;
    for (size_t i = 0; i < path_len; ++i) {
        it.Move((path[i / 8] >> (i % 8)) & 1, true);
    }
    it.SetWord(word);
}

BinaryTrieIterator BinaryTrie::Begin() {
    return begin_;
}

void BinaryTrie::Clear() {
    delete begin_.current_;
    begin_ = BinaryTrieIterator(new BinaryTrieIterator::Node());
}
