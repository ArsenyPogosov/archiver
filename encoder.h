#pragma once

#include "streamwrapper.h"
#include "huffmantable.h"

class Encoder {
private:
    const uint16_t FILENAME_END = 256;
    const uint16_t ONE_MORE_FILE = 257;
    const uint16_t ARCHIVE_END = 258;

    bool empty_;
    StreamWrapper out_;
    HuffmanTableCreator huffman_table_creator_;
    HuffmanTable huffman_table_;

    void ConfigureHuffmanTable(std::istream& in, const std::string& name);

    void WriteWord(uint16_t word);

    void WriteHuffmanTable();
    void WriteName(const std::string& name);
    void WriteContent(std::istream& in);

public:
    class EncoderException : public std::exception {
        const char* what() const throw() {
            return "Encoder failed";
        }
    };

    Encoder();

    void Start(std::ostream& out);
    void Stop();

    void Add(std::istream& in, const std::string& name);
};