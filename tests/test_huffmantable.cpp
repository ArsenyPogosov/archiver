#include <catch.hpp>

#include "huffmantable.h"

TEST_CASE("Create from sizes") {
    std::vector<std::pair<SizesTable, HuffmanTable>> tests(4);
    tests[0].first = {};

    tests[1].first = {{3, 1}, {4, 2}, {5, 2}};
    tests[1].second[3] = {{0b00000000}, 1};
    tests[1].second[4] = {{0b00000001}, 2};
    tests[1].second[5] = {{0b00000011}, 2};

    tests[2].first = {{0, 2}, {1, 3}, {2, 1}, {3, 3}};
    tests[2].second[0] = {{static_cast<char>(0b00000001)}, 2};
    tests[2].second[1] = {{static_cast<char>(0b00000011)}, 3};
    tests[2].second[2] = {{static_cast<char>(0b00000000)}, 1};
    tests[2].second[3] = {{static_cast<char>(0b00000111)}, 3};

    tests[3].first = {{0, 1}, {1, 2}, {2, 3}, {3, 7}, {4, 8}, {5, 9}};
    tests[3].second[0] = {{static_cast<char>(0b00000000)}, 1};
    tests[3].second[1] = {{static_cast<char>(0b00000001)}, 2};
    tests[3].second[2] = {{static_cast<char>(0b00000011)}, 3};
    tests[3].second[3] = {{static_cast<char>(0b00000111)}, 7};
    tests[3].second[4] = {{static_cast<char>(0b01000111)}, 8};
    tests[3].second[5] = {{static_cast<char>(0b11000111), static_cast<char>(0b00000000)}, 9};

    Huffman huffman;

    for (const auto& [test, right_result] : tests) {
        REQUIRE(right_result == huffman.CreateFromSizes(test));
    }
}

TEST_CASE("Create from frequency") {
    std::vector<std::pair<FrequencyTable, HuffmanTable>> tests(4);
    tests[0].first = {};

    tests[1].first = {{3, 1}, {4, 2}, {5, 5}};
    tests[1].second[3] = {{0b00000001}, 2};
    tests[1].second[4] = {{0b00000011}, 2};
    tests[1].second[5] = {{0b00000000}, 1};

    tests[2].first = {{0, 10}, {1, 11}, {2, 12}, {3, 13}};
    tests[2].second[0] = {{static_cast<char>(0b00000000)}, 2};
    tests[2].second[1] = {{static_cast<char>(0b00000010)}, 2};
    tests[2].second[2] = {{static_cast<char>(0b00000001)}, 2};
    tests[2].second[3] = {{static_cast<char>(0b00000011)}, 2};

    tests[3].first = {{0, 18}, {1, 8}, {2, 33}, {3, 9}, {4, 15}, {5, 22}};
    tests[3].second[0] = {{static_cast<char>(0b00000000)}, 2};
    tests[3].second[1] = {{static_cast<char>(0b00000111)}, 4};
    tests[3].second[2] = {{static_cast<char>(0b00000010)}, 2};
    tests[3].second[3] = {{static_cast<char>(0b00001111)}, 4};
    tests[3].second[4] = {{static_cast<char>(0b00000011)}, 3};
    tests[3].second[5] = {{static_cast<char>(0b00000001)}, 2};

    Huffman huffman;

    for (const auto& [test, right_result] : tests) {
        auto res = huffman.CreateFromFrequency(test);
        REQUIRE(right_result == huffman.CreateFromFrequency(test));
    }
}