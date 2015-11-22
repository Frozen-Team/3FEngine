#include "f_file_loader.hpp"

#include <fstream>

#include <fcomponents/f_logger.hpp>

namespace fengine
{
	namespace futils
	{
		FFileLoader::FFileLoader(const FString & file_path)
		{
			LoadFile(file_path);
		}

		void FFileLoader::LoadFile(const FString& file_path)
		{
			std::ifstream in_file;
			in_file.open(file_path.c_str());
			if (in_file.is_open())
			{
				data.assign(std::istreambuf_iterator<char>(in_file), std::istreambuf_iterator<char>());
			}
			else 
			{
				data.clear();
				LOG(WARNING) << "Cannot load file: " << file_path;
			}	
		}

		const FString& FFileLoader::ToString()
		{
			return data;
		}
	}
}
