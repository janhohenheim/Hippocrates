#include <fstream>

#include "utility/logger.hpp"

using namespace Hippocrates;
using namespace Hippocrates::Utility;

auto Logger::CreateLoggingDirs() -> void {
	timestamp = std::chrono::system_clock::now();

	auto currentDir = GetCurrentDir();
	auto logFolder = GetLogFolder();
	auto logFileExtension = GetLogFileExtension();


	auto dumpDir(currentDir + logFolder);
	if (!Type::Filesystem::exists(dumpDir)) {
		Type::Filesystem::create_directory(dumpDir);
	}


	auto sessionDir = GetSessionDir(dumpDir);
	if (!Type::Filesystem::exists(sessionDir)) {
		Type::Filesystem::create_directory(sessionDir);
	}

	fullLoggingPath = sessionDir;
}

auto Logger::GetCurrentDir() const -> Type::file_string_t {
	return Type::Filesystem::current_path();
}

auto Logger::GetLogFolder() const -> Type::file_string_t {
	return Type::literal_as_file_string("/json_dumps/");
}

auto Logger::GetLogFileExtension() const -> Type::file_string_t {
	return Type::literal_as_file_string(".json");
}


auto Logger::GetSessionDir(const Type::file_string_t& dumpDir) const -> Type::file_string_t {
	return Type::file_string_t(dumpDir + Type::to_file_string(timestamp.time_since_epoch().count()) + Type::literal_as_file_string("/"));
}

auto Logger::GetMetadataFileName(const Type::file_string_t &sessionDir) const -> Type::file_string_t {
	return sessionDir + Type::literal_as_file_string("meta") + GetLogFileExtension();
}


auto Logger::GetLogFileName(const Type::file_string_t& sessionDir, std::size_t generationsPassed) const -> Type::file_string_t {
	return Type::file_string_t(sessionDir + Type::literal_as_file_string("generation_") + Type::to_file_string(generationsPassed) + GetLogFileExtension());
}


auto Logger::LogGeneration(std::size_t generation, const std::string& log) -> void {
	if (fullLoggingPath.empty()) 
		throw std::runtime_error("No logging directory found. Did you forget to call Logger::CreateLoggingDirs()?");
	
	auto logFileName = GetLogFileName(fullLoggingPath, generation);
	std::ofstream logFile(logFileName);
	logFile << log;
	logFile.close();
}

auto Logger::LogMetadata(Type::fitness_t maxFitness) -> void {
	metaData += "{\"max_fitness\":" + std::to_string(maxFitness) + "},";
	auto log = "{\"generations\":[" + metaData.substr(0, metaData.length() - 1) + "]}";

	if (fullLoggingPath.empty()) 
		throw std::runtime_error("No logging directory found. Did you forget to call Logger::CreateLoggingDirs()?");
	
	auto logFileName = GetMetadataFileName(fullLoggingPath);
	std::ofstream logFile(logFileName);
	logFile << log;
	logFile.close();
}
