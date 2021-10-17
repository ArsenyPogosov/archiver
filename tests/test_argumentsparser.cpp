#include <catch.hpp>

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "argumentsparser.h"

TEST_CASE("ArgumentsParser") {
	ArgumentParser parser;

	std::ostringstream out;
	parser.AddPattern({"-s", "*"}, [&out](const std::vector<std::string>& args) {
		int result = 0;
		for (const auto&i: args) {
			result += stoi(i);
		}

		out << result;
	});

	parser.AddPattern({(char*) ("?"), (char*) ("-s"), (char*) ("?"), (char*) ("*")}, [&out](const std::vector<std::string>& args) {
		int result = 0;
		for (const auto&i: args) {
			result += stoi(i);
		}

		out << result;
	});

	parser.AddPattern({"--equal", ".", "==", "."}, [&out](const std::vector<std::string>& args) {
		out << (args[0] == args[1]);
	});

	{
		char* args[] = {(char*) ("-s"), (char*) ("2"), (char*) ("3")};
		parser.Execute(3, static_cast<char**>(args));
		out << '\n';
	}
	{
		char* args[] = {(char*) ("-s")};
		parser.Execute(1, static_cast<char**>(args));
		out << '\n';
	}
	{
		char* args[] = {(char*) ("1"), (char*) ("-s"), (char*) ("2"), (char*) ("228"), (char*) ("1337")};
		parser.Execute(5, static_cast<char**>(args));
		out << '\n';
	}
	{
		char* args[] = {(char*) ("--equal"), (char*) ("biba"), (char*) ("=="), (char*) ("boba")};
		parser.Execute(4, static_cast<char**>(args));
		out << '\n';
	}

	REQUIRE(out.str() == "5\n0\n1565\n0\n");

	// TODO add exception check
	/*
	try {
		char* args[] = {(char*) ("--equal"), (char*) ("void"), (char*) ("==")};
		parser.Execute(3, static_cast<char**>(args));
		out << '\n';
	} catch (ArgumentsParserException()) {
		return;
	}
	 */
}
