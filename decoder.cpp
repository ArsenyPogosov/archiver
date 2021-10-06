#include "decoder.h"

uint16_t Decoder::ReadWord() {
    BinaryTrieIterator it = code_table_.Begin();
    while (!it.IsTerminal()) {
        char h = 0;
        in_.Read(&h, 1);
        it.Move(h);
    }

    return it.GetWord();
}

void Decoder::ReadHuffmanTable() {
    size_t symbols_count = 0;
    in_.Read(reinterpret_cast<char*>(&symbols_count), 9);

    SizesTable sizes_table(symbols_count);
    for (auto& [word, _] : sizes_table) {
        word = 0;
        if (in_.Eof()) {
            throw DecoderException();
        }
        in_.Read(reinterpret_cast<char*>(&word), 9);
    }

    for (size_t i = 0, len = 1; i < symbols_count; ++len) {
        size_t last = 0;
        if (in_.Eof()) {
            throw DecoderException();
        }
        in_.Read(reinterpret_cast<char*>(&last), 9);
        last += i;

        for (; i < last; ++i) {
            sizes_table[i].second = len;
        }
    }

    code_table_.Clear();
    HuffmanTable huffman_table = huffman_table_creator_.CreateFromSizes(sizes_table);
    for (const auto& [word, code] : huffman_table) {
        code_table_.AddWord(word, code.first.data(), code.second);
    }
}

void Decoder::ReadName(std::string& name) {
    name.clear();
    for (uint16_t current_word = ReadWord(); current_word != FILENAME_END; current_word = ReadWord()) {
        name += static_cast<char>(current_word);
    }
}

void Decoder::ReadContent(std::ostream& out) {
    while (true) {
        uint16_t current_word = ReadWord();
        if (current_word == ONE_MORE_FILE) {
            break;
        }
        if (current_word == ARCHIVE_END) {
            is_done_ = true;
            break;
        }

        out.write(reinterpret_cast<char*>(&current_word), 1);
    }
}

Decoder::Decoder() : in_(nullptr) {
}

void Decoder::Start(std::istream& in) {
    in_ = StreamWrapper(static_cast<std::iostream*>(&in));
    is_done_ = false;
}

void Decoder::Get(std::ostream& out, std::string& name) {
    try {
        ReadHuffmanTable();
        ReadName(name);
        ReadContent(out);
    } catch (const std::iostream::failure& e) {
        throw;
    } catch (...) {
        throw DecoderException();
    }
}

bool Decoder::IsDone() {
    return is_done_;
}
