#include "unarchiver.h"

#include <fstream>
#include <string>

const std::string TEMP_FILE_NAME = "~tempfile";

namespace Unarchiver {
	void Unarchive(const std::string &archive_name) {
		try {
			std::ifstream archive_file(archive_name, std::ifstream::binary);
			archive_file.exceptions(std::ifstream::badbit);

			Decoder decoder;
			decoder.Start(archive_file);
			while (!decoder.IsDone()) {
				std::string name;
				std::ofstream file(TEMP_FILE_NAME, std::ofstream::binary);
				file.exceptions(std::ofstream::badbit);
				decoder.Get(file, name);
				file.close();

				rename(TEMP_FILE_NAME.c_str(), name.c_str());
			}
		} catch(...) {
			std::remove(TEMP_FILE_NAME.c_str());
			throw;
		}
	}
}
