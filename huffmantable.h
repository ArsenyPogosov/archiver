#pragma once

#include "word.h"

#include <unordered_map>
#include <vector>


using HuffmanTable = std::unordered_map<Word::WordType, std::pair<std::vector<char>, size_t>>;
using FrequencyTable = std::vector<std::pair<Word::WordType, int>>;
using SizesTable = std::vector<std::pair<Word::WordType, size_t>>;

class HuffmanTableCreator {
private:
    SizesTable CountSizes(const FrequencyTable& frequency_table);

public:
    HuffmanTable CreateFromSizes(SizesTable sizes_table);
    HuffmanTable CreateFromFrequency(const FrequencyTable& frequency_table);
};