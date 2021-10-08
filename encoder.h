#pragma once

#include "streamwrapper.h"
#include "huffmantable.h"

class Encoder {
private:
    bool empty_;
    StreamWrapper out_;
    HuffmanTableCreator huffman_table_creator_;
    HuffmanTable huffman_table_;

    void ConfigureHuffmanTable(std::istream& in, const std::string& name);

    void WriteWord(Word::WordType word);

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