#pragma once

#include <unordered_map>
#include <vector>

#include "word.h"

// TODO move this
using HuffmanTable = std::unordered_map<Word::WordType, std::pair<std::vector<char>, size_t>>;
using FrequencyTable = std::vector<std::pair<Word::WordType, int>>;
using SizesTable = std::vector<std::pair<Word::WordType, size_t>>;

class HuffmanTableCreator {
public:
	static HuffmanTable CreateFromSizes(SizesTable sizes_table);
	static HuffmanTable CreateFromFrequency(const FrequencyTable& frequency_table);

private:
    static SizesTable CountSizes(const FrequencyTable& frequency_table);
};