#pragma once 
#include <fstream>
#include <vector>
#include <string>
#include <string_view>
#include <filesystem>
#include <stdexcept>

inline std::vector<char> BinaryFileToBuffer(const std::filesystem::path& path)
{
	std::ifstream file(path, std::ios::ate | std::ios::binary);

	if (!file.is_open())
	{
		throw std::runtime_error("failed to open file: " + path.string());
	}

	size_t fileSize = (size_t)file.tellg();
	std::vector<char> buffer(fileSize);

	file.seekg(0);
	file.read(buffer.data(), fileSize);

	file.close();
	return buffer;
}