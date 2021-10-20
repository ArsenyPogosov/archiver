#pragma once

#include <functional>
#include <string>
#include <vector>

class ArgumentsParserException: public std::exception {

};

class ArgumentsParser {
public:
	using Action = std::function<void(std::vector<std::string>&)>;

	ArgumentsParser();

	void AddPattern(const std::vector<std::string> &pattern_template, const Action &action);

	void SetDefault(const Action& default_action);

	void Execute(int argc, char** argv) const;

private:
	inline static const std::string ARGUMENT_ = ".";
	inline static const std::string ARGUMENTS_PACK_ = "*";
	inline static const std::string SKIP_ = "?";

	struct Pattern {
	public:
		std::vector<std::string> pattern_template_;
		Action action_;

		Pattern(const std::vector<std::string> &pattern_template, const Action &action);
	};

	std::vector<Pattern> patterns_;
	Action default_;
};