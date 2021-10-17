#include "streamwrapper.h"

StreamWrapper::StreamWrapper(std::iostream* stream) {
	stream_ = stream;
	buffer_ = buffer_len_ = 0;
}

void StreamWrapper::Read(char* result, size_t n) {
	for (size_t i = 0; i < n; ++i) {
		if (!buffer_len_) {
			ReadBuffer();
		}

		result[i / 8] ^= (result[i / 8] & (1 << (i % 8))) ^ ((buffer_ & 1) << (i % 8));
		buffer_ >>= 1;
		--buffer_len_;
	}
}

void StreamWrapper::Write(const char* data, size_t n) {
	for (size_t i = 0; i < n; ++i) {
		if (buffer_len_ == 8) {
			WriteBuffer();
		}

		buffer_ ^= (buffer_ & (1 << buffer_len_)) ^ (((data[i / 8] >> (i % 8)) & 1) << buffer_len_);
		++buffer_len_;
	}
}

void StreamWrapper::Flush() {
	if (buffer_len_) {
		for (size_t i = buffer_len_; i < 8; ++i) {
			buffer_ ^= (buffer_ & (1 << i));
		}
		WriteBuffer();
	}
}

bool StreamWrapper::Eof() const {
	return GetStream().eof();
}

void StreamWrapper::ReadBuffer() {
	GetStream().read(&buffer_, 1);
    buffer_len_ = 8;
}

void StreamWrapper::WriteBuffer() {
	GetStream().write(&buffer_, 1);
    buffer_len_ = 0;
}
