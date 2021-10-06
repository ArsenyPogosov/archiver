#include <catch.hpp>
#include "priorityqueue.h"

TEST_CASE("PriorityQueue") {
    std::vector<std::pair<char, int>> queries{{0, 228}, {0, 10}, {0, 300}, {1, 10}, {2, -1},  {1, 228}, {0, 7},
                                              {1, 7},   {2, -1}, {1, 228}, {2, -1}, {1, 300}, {2, -1}};

    PriorityQueue<int> queue;
    for (const auto& [type, data] : queries) {
        if (type == 0) {
            queue.Push(data);
        } else if (type == 1) {
            REQUIRE(data == queue.Top());
        } else {
            queue.Pop();
        }
    }
    REQUIRE(queue.Empty());
}
