#include "archiver.h"

#include <fstream>
#include <string>
#include <vector>

#include "encoder.h"

namespace Archiver {
	void Archive(const std::string& archive_name, const std::vector<std::string>& file_names) {
		std::ofstream archive_file(archive_name, std::ofstream::binary);
		archive_file.exceptions(std::ofstream::badbit);

		Encoder encoder;
		encoder.Start(archive_file);
		for (const auto& name : file_names) {
		std::ifstream file(name, std::ifstream::binary);
		file.exceptions(std::ifstream::badbit);
		encoder.Add(file, name);
		}
		encoder.Stop();
	}
}
