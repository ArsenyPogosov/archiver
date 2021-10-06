#pragma once

#include "streamwrapper.h"
#include "huffmantable.h"
#include "binarytrie.h"

class Decoder {
private:
    const uint16_t FILENAME_END = 256;
    const uint16_t ONE_MORE_FILE = 257;
    const uint16_t ARCHIVE_END = 258;

    bool is_done_;
    StreamWrapper in_;
    HuffmanTableCreator huffman_table_creator_;
    BinaryTrie code_table_;

    uint16_t ReadWord();

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