#pragma once

#include <iostream>

class StreamWrapper {
public:
	explicit StreamWrapper(std::iostream* stream);

	void Read(char* result, size_t n);

	void Write(const char* data, size_t n);
	void Flush();

	[[nodiscard]] bool Eof() const;

private:
    std::iostream* stream_;
	std::iostream& GetStream() {
		return *stream_;
	}
	[[nodiscard]] const std::iostream& GetStream() const {
		return *stream_;
	}

    char buffer_;
    uint_fast8_t buffer_len_;

    void ReadBuffer();
    void WriteBuffer();
};