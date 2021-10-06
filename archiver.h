#pragma once

#include "encoder.h"
#include "decoder.h"

#include <string>

class Archiver {
private:
    std::string HELP =
        "archiver -c archive_name file1 [file2 ...] - archive fil1, file2, ... and save the result in archive_name.\n"
        "archiver -d archive_name - unarchive files from archive_name and put them in the current directory.\n"
        "archiver -h - show help for program usage.";

    std::string TEMP_FILE_NAME = "~tempfile";

    std::ostream* logger_;
    Encoder encoder_;
    Decoder decoder_;

public:
    Archiver(std::ostream* logger);

    void Archive(const std::string& archive_name, const std::vector<std::string>& file_names);

    void Unarchive(const std::string& archive_name);

    void WriteHelp();
};