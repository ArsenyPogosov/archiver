#pragma once

#include "streamwrapper.h"
#include "huffmantable.h"
#include "binarytrie.h"

class Decoder {
private:
    bool is_done_;
    StreamWrapper in_;
    HuffmanTableCreator huffman_table_creator_;
    BinaryTrie code_table_;

    Word::WordType ReadWord();

    void ReadHuffmanTable();
    void ReadName(std::string& name);
    void ReadContent(std::ostream& out);

public:
    class DecoderException : public std::exception {
        const char* what() const throw() {
            return "Decoder failed";
        }
    };

    Decoder();

    void Start(std::istream& in);
    void Get(std::ostream& out, std::string& name);
    bool IsDone();
};