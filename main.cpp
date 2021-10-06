#include "archiver.h"

int main(int argc, char* argv[]) {
    Archiver archiver(&std::cout);

    if (argc <= 1) {
        return 0;
    }

    if (argv[1] == std::string("-c")) {
        if (argc <= 2) {
            std::cout << "archive_name is required.\n";
            return 0;
        }
        if (argc <= 3) {
            std::cout << "file1 is required.\n";
            return 0;
        }

        std::vector<std::string> file_names;
        for (size_t i = 3; i < static_cast<size_t>(argc); ++i) {
            file_names.push_back(argv[i]);
        }
        archiver.Archive(argv[2], file_names);

    } else if (argv[1] == std::string("-d")) {
        if (argc <= 2) {
            std::cout << "archive_name is required\n";
            return 0;
        }
        archiver.Unarchive(argv[2]);

    } else if (argv[1] == std::string("-h")) {
        archiver.WriteHelp();

    } else {
        std::cout << "This is not a command command. Use -h for help.\n";
        return 0;
    }

    return 0;
}