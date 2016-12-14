#pragma once
#include <string>
#include <chrono>

#include "type.hpp"

namespace Hippocrates::Utility {

class Logger {
public:
	auto CreateLoggingDirs() -> void;
	auto LogGeneration(std::size_t generation, std::ostream& logstream) -> void;
	auto LogMetadata(Type::fitness_t maxFitness) -> void;

private:
	auto GetCurrentDir() -> Type::file_string_t;
	auto GetLogFolder() -> Type::file_string_t;
	auto GetSessionDir(const Type::file_string_t& dumpDir) -> Type::file_string_t;

	auto GetLogFileExtension() -> Type::file_string_t;

	auto GetMetadataFileName(const Type::file_string_t &sessionDir) -> Type::file_string_t;
	auto GetLogFileName(const Type::file_string_t& sessionDir, std::size_t generationsPassed) -> Type::file_string_t;

	auto SetFullLoggingPath(const Type::file_string_t& path) -> void;

private:
	std::chrono::system_clock::time_point timestamp;
	Type::file_string_t fullLoggingPath;
	std::string metaData;
};

}
