#pragma once

#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

namespace fgengine {
	namespace utils {
		class FileManager
		{
		public:
			FileManager();
			~FileManager();
			static std::string read(const std::string& filename);
		};
	}
}