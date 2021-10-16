#pragma once

#include <unordered_map>
#include <vector>

#include "word.h"

namespace Huffman {
	using HuffmanTable = std::unordered_map<Word::WordType, std::pair<std::vector<char>, size_t>>;
	using FrequencyTable = std::vector<std::pair<Word::WordType, int>>;
	using SizesTable = std::vector<std::pair<Word::WordType, size_t>>;

	HuffmanTable CreateFromSizes(SizesTable sizes_table);
	HuffmanTable CreateFromFrequency(const FrequencyTable& frequency_table);
};