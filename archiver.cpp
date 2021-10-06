#include "archiver.h"

#include <fstream>

Archiver::Archiver(std::ostream* logger) {
    logger_ = logger;
}

void Archiver::Archive(const std::string& archive_name, const std::vector<std::string>& file_names) {
    try {
        std::ofstream archive_file(archive_name, std::ofstream::binary);
        archive_file.exceptions(std::ofstream::badbit);

        encoder_.Start(archive_file);
        for (const auto& name : file_names) {
            std::ifstream file(name, std::ifstream::binary);
            file.exceptions(std::ifstream::badbit);
            encoder_.Add(file, name);
        }
        encoder_.Stop();
    } catch (const std::iostream::failure& e) {
        (*logger_) << "Can't read/write to file.";
    } catch (const Encoder::EncoderException& e) {
        (*logger_) << "Fail to encode.";
    }
}

void Archiver::Unarchive(const std::string& archive_name) {
    try {
        std::ifstream archive_file(archive_name, std::ifstream::binary);
        archive_file.exceptions(std::ifstream::badbit);

        decoder_.Start(archive_file);
        while (!decoder_.IsDone()) {
            std::string name;
            std::ofstream file(TEMP_FILE_NAME, std::ofstream::binary);
            file.exceptions(std::ofstream::badbit);

            decoder_.Get(file, name);
            file.close();

            rename(TEMP_FILE_NAME.c_str(), name.c_str());
        }
    } catch (const std::iostream::failure& e) {
        (*logger_) << "Can't read/write to file.";
        std::remove(TEMP_FILE_NAME.c_str());
    } catch (const Decoder::DecoderException& e) {
        (*logger_) << "Fail to decode. Archive has probably been corrupted";
        std::remove(TEMP_FILE_NAME.c_str());
    }
}

void Archiver::WriteHelp() {
    (*logger_) << HELP << '\n';
}
