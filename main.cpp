#include <iostream>
#include <string>
#include <vector>

#include "archiver.h"
#include "argumentsparser.h"
#include "decoder.h"
#include "encoder.h"
#include "helper.h"
#include "unarchiver.h"

int main(int argc, char* argv[]) {

	ArgumentsParser parser;

	parser.AddPattern({"?", "-c", ".", "*"}, [](std::vector<std::string>& args) {
		std::string archive_name = args.front();
		args.erase(args.begin());
		try {
			Archiver::Archive(archive_name, args);
		} catch (const std::iostream::failure& e) {
			std::cout << "Unable to read/write to file.";
		} catch (const Encoder::EncoderException& e) {
			std::cout << "Fail to encode.";
		}
	});

	parser.AddPattern({"?", "-d", "."}, [](std::vector<std::string>& args) {
		try {
			Unarchiver::Unarchive(args[0]);
		} catch (const std::iostream::failure &e) {
			std::cout << "Can't read/write to file.";
		} catch (const Decoder::DecoderException &e) {
			std::cout << "Fail to decode. Archive has probably been corrupted.";
		}
	});

	parser.AddPattern({"?", "-h"}, [](std::vector<std::string>& args) {
		Helper::Help(std::cout);
	});

	parser.SetDefault([](std::vector<std::string>& args) {
		Helper::Help(std::cout);
	});

	parser.Execute(argc, argv);

    return 0;
}