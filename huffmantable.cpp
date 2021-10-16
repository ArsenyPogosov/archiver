#include "huffmantable.h"

#include <algorithm>
#include <cstring>

#include "priorityqueue.h"

HuffmanTable HuffmanTableCreator::CreateFromSizes(SizesTable sizes_table) {
    if (sizes_table.empty()) {
        return {};
    }

    std::sort(sizes_table.begin(), sizes_table.end(), [](std::pair<Word::WordType, size_t> a, std::pair<Word::WordType, size_t> b) {
        return std::tie(a.second, a.first) < std::tie(b.second, b.first);
    });

    size_t max_size = sizes_table.back().second;
    char current_code[max_size / 8 + 1];
    memset(current_code, 0, max_size / 8 + 1);
    size_t current_size = 0;

    const auto add1 = [&]() {
        for (size_t i = current_size - 1; i != static_cast<size_t>(-1); --i) {
            current_code[i / 8] ^= (1 << (i % 8));
            if (current_code[i / 8] & (1 << (i % 8))) {
                break;
            }
        }
    };

    HuffmanTable result;
    for (const auto& [word, size] : sizes_table) {
        while (current_size < size) {
            ++current_size;
        }

        result[word] = {std::vector<char>(current_code, current_code + (current_size + 7) / 8), current_size};

        add1();
    }

    return result;
}

HuffmanTable HuffmanTableCreator::CreateFromFrequency(const FrequencyTable& frequency_table) {
    return CreateFromSizes(CountSizes(frequency_table));
}

SizesTable HuffmanTableCreator::CountSizes(const FrequencyTable& frequency_table) {
	if (frequency_table.empty()) {
		return {};
	}

	size_t n = frequency_table.size();

	struct Node {
		int weight_;
		Word::WordType min_word_;
		size_t parent_;

		explicit Node(int weight = 0, Word::WordType min_word = 0, size_t parent = -1) {
			weight_ = weight;
			min_word_ = min_word;
			parent_ = parent;
		};
	};

	std::vector<Node> huffman_nodes;
	huffman_nodes.reserve(n * 2 - 1);

	PriorityQueue<std::pair<std::pair<int, Word::WordType>, size_t>> low_weight_first;

	const auto add_node = [&](int weight, Word::WordType min_word, size_t l = -1, size_t r = -1) {
		size_t it = huffman_nodes.size();
		huffman_nodes.emplace_back(weight);
		low_weight_first.Push({std::pair<int, Word::WordType>{weight, min_word}, it});
		if (l != static_cast<size_t>(-1)) {
			huffman_nodes[l].parent_ = it;
		}
		if (r != static_cast<size_t>(-1)) {
			huffman_nodes[r].parent_ = it;
		}
	};

	for (auto& [word, frequency] : frequency_table) {
		add_node(frequency, word);
	}

	while (low_weight_first.Size() > 1) {
		size_t first = low_weight_first.Top().second;
		low_weight_first.Pop();
		size_t second = low_weight_first.Top().second;
		low_weight_first.Pop();

		add_node(huffman_nodes[first].weight_ + huffman_nodes[second].weight_,
		         std::min(huffman_nodes[first].min_word_, huffman_nodes[second].min_word_), first, second);
	}

	std::vector<size_t> sizes(n * 2 - 1);
	for (int i = n * 2 - 3; i >= 0; --i) {
		sizes[i] = sizes[huffman_nodes[i].parent_] + 1;
	}

	std::vector<std::pair<Word::WordType, size_t>> result;
	{
		size_t i = 0;
		for (const auto& [word, _] : frequency_table) {
			result.emplace_back(word, sizes[i]);
			++i;
		}
	}

	return result;
}
