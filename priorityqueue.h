#pragma once

#include <exception>

template <typename T, typename comp = std::less<T>>
class PriorityQueue {
public:
	T Top() const {
		if (content_.empty()) {
			throw std::out_of_range("Trying to Top from empty PriorityQueue");
		}

		return content_[0];
	}

	void Pop() {
		if (content_.empty()) {
			throw std::out_of_range("Trying to Pop from empty PriorityQueue");
		}

		content_[0] = content_.back();
		content_.pop_back();
		MoveDown(0);
	}

	void Push(const T &to_push) {
		content_.push_back(to_push);
		MoveUp(content_.size() - 1);
	}

	[[nodiscard]] size_t Size() const {
		return content_.size();
	}

	[[nodiscard]] bool Empty() const {
		return content_.empty();
	}

private:
    std::vector<T> content_;
	void MoveUp(size_t i) {
		while (i > 0 && comp()(content_[i], content_[(i - 1) / 2])) {
			std::swap(content_[i], content_[(i - 1) / 2]);
			i = (i - 1) / 2;
		}
	}

	void MoveDown(size_t i) {
		while (i * 2 + 1 < content_.size()) {
			size_t min_child = i * 2 + 1;
			if (i * 2 + 2 < content_.size() && comp()(content_[i * 2 + 2], content_[i * 2 + 1])) {
				min_child = i * 2 + 2;
			}

			if (comp()(content_[min_child], content_[i])) {
				std::swap(content_[min_child], content_[i]);
				i = min_child;
			} else {
				break;
			}
		}
	}
};