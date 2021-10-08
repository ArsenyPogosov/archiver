#pragma once

#include <cstdint>

namespace Word {
    typedef uint16_t WordType;
    const size_t WordLen = 9;

    const WordType FILENAME_END = 256;
    const WordType ONE_MORE_FILE = 257;
    const WordType ARCHIVE_END = 258;
}