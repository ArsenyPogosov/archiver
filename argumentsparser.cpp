#include "argumentsparser.h"

#include "string"
#include "vector"

void ArgumentsParser::AddPattern(const std::vector<std::string> &pattern_template, const Action &action) {
	patterns_.emplace_back(pattern_template, action);
}

ArgumentsParser::ArgumentsParser(): patterns_(), default_([](const std::vector<std::string>&) {
	throw ArgumentsParserException();
}) {

}

void ArgumentsParser::SetDefault(const Action& default_action) {
	default_ = default_action;
}

void ArgumentsParser::Execute(int argc, char** argv) const {
	std::vector<std::string> arguments(argc);
	for (int i = 0; i < argc; ++i) {
		arguments[i] = std::string(argv[i]);
	}

	for (const auto& pattern : patterns_) {
		std::vector<std::string> needed_arguments;

		bool matched = true;
		for (size_t i = 0, j = 0; i < pattern.pattern_template_.size(); ++i, ++j) {
			if (pattern.pattern_template_[i] == ARGUMENTS_PACK_) {
				std::copy(arguments.begin() + j, arguments.end(), std::back_inserter(needed_arguments));
				break;
			}

			if (j >= arguments.size()) {
				matched = false;
				break;
			}

			if (pattern.pattern_template_[i] == SKIP_) {
				continue;
			}

			if (pattern.pattern_template_[i] == ARGUMENT_) {
				needed_arguments.push_back(arguments[j]);
				continue;
			}

			if (pattern.pattern_template_[i] != arguments[j]) {
				matched = false;
				break;
			}
		}

		if (matched) {
			pattern.action_(needed_arguments);
			return;
		}
	}

	default_(arguments);
}

ArgumentsParser::Pattern::Pattern(const std::vector<std::string>& pattern_template, const Action &action) :
		pattern_template_(pattern_template), action_(action) {

}
