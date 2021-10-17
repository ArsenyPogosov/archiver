#pragma once

#include <string>
#include <vector>

namespace Archiver {
	void Archive(const std::string& archive_name, const std::vector<std::string>& file_names);
};