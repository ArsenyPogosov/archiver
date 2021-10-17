#pragma once

#include <string>
#include <vector>
#include <functional>

class ArgumentsParserException: public std::exception {

};

class ArgumentParser {
public:
	using Action = std::function<void(const std::vector<std::string>&)>;

	ArgumentParser();

	void AddPattern(const std::vector<std::string> &pattern_template, const Action &action);

	void SetDefault(const Action& default_action);

	void Execute(int argc, char** argv);

private:
	inline static const std::string ARGUMENT_ = ".";
	inline static const std::string ARGUMENTS_PACK_ = "*";

	struct Pattern {
	public:
		std::vector<std::string> pattern_template_;
		Action action_;

		Pattern(const std::vector<std::string> &pattern_template, const Action &action);
	};

	std::vector<Pattern> patterns_;
	Action default_;
};