#pragma once

#include <iostream>

class StreamWrapper {
private:
    std::iostream* stream_;

    char buffer_;
    uint_fast8_t buffer_len_;

    void ReadBuffer();
    void WriteBuffer();

public:
    StreamWrapper(std::iostream* stream);

    void Read(char* result, size_t n);

    void Write(const char* data, size_t n);
    void Flush();

    bool Eof();
};