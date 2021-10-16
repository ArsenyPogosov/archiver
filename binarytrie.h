#pragma once

#include <array>

#include "word.h"

struct Node {
	Word::WordType word_;
	std::array<Node*, 2> links_;

	Node();
	~Node();
};

class BinaryTrieSmartNode {
public:
	void Move(char path, bool push = false);
	bool IsTerminal();
	Word::WordType GetWord();
	void SetWord(Word::WordType word);

private:

    Node* current_;
    explicit BinaryTrieSmartNode(Node* current);

	friend class BinaryTrie;
};

class BinaryTrie {
public:
	static const Word::WordType NOT_TERMINAL_ = -1;

	BinaryTrie();
	~BinaryTrie();

	void AddWord(Word::WordType word, const char* path, size_t path_len);
	BinaryTrieSmartNode Begin();

	void Clear();

private:
    BinaryTrieSmartNode begin_;
};