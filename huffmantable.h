#pragma once

#include <unordered_map>
#include <vector>

using HuffmanTable = std::unordered_map<uint16_t, std::pair<std::vector<char>, size_t>>;
using FrequencyTable = std::vector<std::pair<uint16_t, int>>;
using SizesTable = std::vector<std::pair<uint16_t, size_t>>;

class HuffmanTableCreator {
private:
    SizesTable CountSizes(const FrequencyTable& frequency_table);

public:
    HuffmanTable CreateFromSizes(SizesTable sizes_table);
    HuffmanTable CreateFromFrequency(const FrequencyTable& frequency_table);
};