#include "argumentsparser.h"

void ArgumentParser::AddPattern(const std::vector<std::string> &pattern_template, const Action &action) {
	patterns_.emplace_back(pattern_template, action);
}

ArgumentParser::ArgumentParser(): patterns_(), default_([](const std::vector<std::string>&) {
	throw ArgumentsParserException();
}) {

}

void ArgumentParser::SetDefault(const Action& default_action) {
	default_ = default_action;
}

void ArgumentParser::Execute(int argc, char** argv) {
	std::vector<std::string> arguments(argc);
	for (int i = 0; i < argc; ++i) {
		arguments[i] = std::string(argv[i]);
	}

	for (const auto& pattern : patterns_) {
		std::vector<std::string> needed_arguments;

		bool matched = true;
		for (size_t i = 0; i < pattern.pattern_template_.size(); ++i) {
			if (pattern.pattern_template_[i] == ARGUMENTS_PACK_) {
				std::copy(arguments.begin() + i, arguments.end(), std::back_inserter(needed_arguments));
				break;
			}

			if (i >= arguments.size()) {
				matched = false;
				break;
			}

			if (pattern.pattern_template_[i] == ARGUMENT_) {
				needed_arguments.push_back(arguments[i]);
				continue;
			}

			if (arguments[i] != pattern.pattern_template_[i]) {
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

ArgumentParser::Pattern::Pattern(const std::vector<std::string>& pattern_template, const Action &action) :
		pattern_template_(pattern_template), action_(action) {

}
