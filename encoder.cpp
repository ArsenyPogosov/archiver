#include "encoder.h"

#include <algorithm>

Encoder::Encoder() : empty_(false), out_(nullptr) {
}

void Encoder::Start(std::ostream& out) {
	out_ = StreamWrapper(static_cast<std::iostream*>(&out));
	empty_ = true;
}

void Encoder::Stop() {
	WriteWord(Word::ARCHIVE_END);
	out_.Flush();
}

void Encoder::Add(std::istream& in, const std::string& name) {
	if (empty_) {
		empty_ = false;
	} else {
		WriteWord(Word::ONE_MORE_FILE);
	}

	try {
		ConfigureHuffmanTable(in, name);
		WriteHuffmanTable();
		WriteName(name);
		WriteContent(in);
	} catch (const std::iostream::failure& e) {
		throw;
	} catch (...) {
		throw EncoderException();
	}
}

void Encoder::ConfigureHuffmanTable(std::istream& in, const std::string& name) {
    std::unordered_map<Word::WordType, int> count;

    count[Word::FILENAME_END] = count[Word::ONE_MORE_FILE] = count[Word::ARCHIVE_END] = 1;
    for (const auto& i : name) {
        ++count[static_cast<Word::WordType>(i)];
    }
    char word;
    while (in.get(word)) {
        ++count[static_cast<Word::WordType>(word)];
    }

    Huffman::FrequencyTable frequency_table;
    for (const auto& i : count) {
        frequency_table.push_back(i);
    }

    huffman_table_ = Huffman::CreateFromFrequency(frequency_table);

    in.clear();
    in.seekg(0);
}

void Encoder::WriteWord(Word::WordType word) {
    out_.Write(huffman_table_[word].first.data(), huffman_table_[word].second);
}

void Encoder::WriteHuffmanTable() {
    size_t symbols_count = huffman_table_.size();
    out_.Write(reinterpret_cast<char*>(&symbols_count), Word::WordLen);

    std::vector<std::pair<size_t, Word::WordType>> canonical_order;
    canonical_order.reserve(symbols_count);
    for (const auto& [word, data] : huffman_table_) {
        canonical_order.emplace_back(data.second, word);
    }
    std::sort(canonical_order.begin(), canonical_order.end());
    for (const auto& [_, word] : canonical_order) {
        out_.Write(reinterpret_cast<const char*>(&word), Word::WordLen);
    }

    size_t max_size = canonical_order.back().first;
    std::vector<size_t> count_size(max_size);
    for (const auto& [size, _] : canonical_order) {
        ++count_size[size - 1];
    }
    for (const auto& i : count_size) {
        out_.Write(reinterpret_cast<const char*>(&i), Word::WordLen);
    }
}

void Encoder::WriteName(const std::string& name) {
    for (const auto& i : name) {
        WriteWord(static_cast<Word::WordType>(i));
    }
    WriteWord(Word::FILENAME_END);
}

void Encoder::WriteContent(std::istream& in) {
    char word;
    while (in.get(word)) {
        WriteWord(static_cast<Word::WordType>(word));
    }
}
