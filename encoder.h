#pragma once

#include "huffmantable.h"
#include "streamwrapper.h"

class Encoder {
public:
	class EncoderException : public std::exception {
		[[nodiscard]] const char* what() const noexcept override {
			return "Encoder failed";
		}
	};

	Encoder();

	void Start(std::ostream& out);
	void Stop();

	void Add(std::istream& in, const std::string& name = "");

private:
    bool empty_;
    StreamWrapper out_;
    Huffman::HuffmanTable huffman_table_;

    void ConfigureHuffmanTable(std::istream& in, const std::string& name = "");

    void WriteWord(Word::WordType word);

    void WriteHuffmanTable();
    void WriteName(const std::string& name);
    void WriteContent(std::istream& in);
};