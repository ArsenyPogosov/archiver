#include <catch.hpp>

#include <sstream>
#include <vector>

#include "streamwrapper.h"

std::vector<std::pair<std::vector<char>, size_t>> test = {
    {{0}, 1},
    {{0}, 5},
    {{1}, 7},
    {{0, 1}, 16},
    {{123, 32, 7, 18}, 30},
    {{12, 127, 17, 126, 111, 12, 125, 57, 3, 4, 0, 11}, 90},
};

TEST_CASE("StreamWrapper") {

    std::stringstream in;
    StreamWrapper inw(&in);
    for (const auto& [data, size] : test) {
        inw.Write(data.data(), size);
    }
    inw.Flush();

    std::stringstream out(in.str());
    StreamWrapper outw(&out);

    for (const auto& [data, size] : test) {
        char result[data.size()];
        outw.Read(result, size);
        bool good = true;
        for (size_t i = 0; i < size; ++i) {
            good &= ((data.data()[i / 8] >> (i % 8)) & 1) == ((result[i / 8] >> (i % 8)) & 1);
        }
        REQUIRE(good);
    }
}