#include <catch.hpp>
#include "binarytrie.h"

TEST_CASE("BinaryTrie") {
    std::vector<std::pair<uint16_t, std::pair<std::vector<char>, size_t>>> words{
        {0, {{0b00000000}, 1}}, {1, {{0b00000010}, 2}}, {2, {{0b00001111}, 4}}, {3, {{0b00011101}, 5}},
        {4, {{0b00011100}, 5}}, {5, {{0b00011011}, 5}}, {6, {{0b00011010}, 5}}, {7, {{0b00001100}, 4}},
    };

    BinaryTrie trie;
    for (const auto& [word, code] : words) {
        trie.AddWord(word, code.first.data(), code.second);
    }

    for (const auto& [word, code] : words) {
        BinaryTrieIterator it = trie.Begin();
        for (size_t i = 0; i < code.second; ++i) {
            it.Move((code.first[i / 8] >> (i % 8) & 1));
        }
        REQUIRE((it.IsTerminal() && it.GetWord() == word));
    }
}
