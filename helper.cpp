#include "archiver.h"

#include <iostream>
#include <string>

const std::string HELP = "archiver -c archive_name file1 [file2 ...] - archive fil1, file2, ... and save the result in archive_name.\n"
                         "archiver -d archive_name - unarchive files from archive_name and put them in the current directory.\n"
                         "archiver -h - show help for program usage.";

namespace Helper {
	void Help(std::ostream &out) {
		out << HELP << '\n';
	}
}