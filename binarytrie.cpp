#include "binarytrie.h"

Node::Node(): links_{nullptr, nullptr} {
	word_ = BinaryTrie::NOT_TERMINAL_;
}

Node::~Node() {
	if (links_[0]) {
		delete links_[0];
	}
	if (links_[1]) {
		delete links_[1];
	}
}

void BinaryTrieSmartNode::Move(char path, bool push) {
	if (!(current_->links_[static_cast<size_t>(path)])) {
		if (!push) {
			throw std::out_of_range("BinaryTrie out of range");
		}
		current_->links_[static_cast<size_t>(path)] = new Node();
	}
	current_ = current_->links_[static_cast<size_t>(path)];
}

bool BinaryTrieSmartNode::IsTerminal() {
	return current_->word_ != static_cast<Word::WordType>(BinaryTrie::NOT_TERMINAL_);
}

Word::WordType BinaryTrieSmartNode::GetWord() {
	return current_->word_;
}

void BinaryTrieSmartNode::SetWord(Word::WordType word) {
	current_->word_ = word;
}

BinaryTrieSmartNode::BinaryTrieSmartNode(Node* current) {
    current_ = current;
}

BinaryTrie::BinaryTrie() : begin_(new Node()) {
}

BinaryTrie::~BinaryTrie() {
    delete begin_.current_;
}

void BinaryTrie::AddWord(Word::WordType word, const char* path, size_t path_len) {
    BinaryTrieSmartNode it = begin_;
    for (size_t i = 0; i < path_len; ++i) {
        it.Move(static_cast<char>((path[i / 8] >> (i % 8)) & 1), true);
    }
    it.SetWord(word);
}

BinaryTrieSmartNode BinaryTrie::Begin() {
    return begin_;
}

void BinaryTrie::Clear() {
    delete begin_.current_;
    begin_ = BinaryTrieSmartNode(new Node());
}
