#pragma once

#include <exception>
#include <iostream>
#include <string>

#include "binarytrie.h"
#include "huffmantable.h"
#include "streamwrapper.h"

class Decoder {
public:
	class DecoderException : public std::exception {
		[[nodiscard]] const char* what() const noexcept override {
			return "Decoder failed";
		}
	};

	Decoder();

	void Start(std::istream& in);
	void Get(std::ostream& out, std::string& name);
	[[nodiscard]] bool IsDone() const;

private:
    bool is_done_;
    StreamWrapper in_;
    BinaryTrie code_table_;

    Word::WordType ReadWord();

    void ReadHuffmanTable();
    void ReadName(std::string& name);
    void ReadContent(std::ostream& out);
};