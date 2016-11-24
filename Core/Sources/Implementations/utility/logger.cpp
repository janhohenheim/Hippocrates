#include <fstream>

#include "utility/logger.hpp"

using namespace Hippocrates;
using namespace Hippocrates::Utility;

auto Logger::CreateLoggingDirs() -> void {
	timestamp = std::chrono::system_clock::now();

	auto* pathType = std::experimental::filesystem::current_path().c_str();
	auto currentDir = GetCurrentDir(pathType);
	auto logFolder = GetLogFolder(pathType);
	auto logFileExtension = GetLogFileExtension(pathType);


	auto dumpDir(currentDir + logFolder);
	if (!std::experimental::filesystem::exists(dumpDir)) {
		std::experimental::filesystem::create_directory(dumpDir);
	}


	auto sessionDir = GetSessionDir(dumpDir);
	if (!std::experimental::filesystem::exists(sessionDir)) {
		std::experimental::filesystem::create_directory(sessionDir);
	}

	SetFullLoggingPath(sessionDir);
}

auto Logger::GetCurrentDir(const char*) -> std::string {
	return std::string((char*)std::experimental::filesystem::current_path().c_str());
}

auto Logger::GetCurrentDir(const wchar_t*) -> std::wstring {
	return std::wstring((wchar_t*)std::experimental::filesystem::current_path().c_str());
}

auto Logger::GetLogFolder(const std::string&) -> std::string {
	return std::string("/json_dumps/");
}

auto Logger::GetLogFolder(const std::wstring&) -> std::wstring {
	return std::wstring(L"/json_dumps/");
}

auto Logger::GetLogFileExtension(const std::string&) -> std::string {
	return std::string(".json");
}

auto Logger::GetLogFileExtension(const std::wstring&) -> std::wstring {
	return std::wstring(L".json");
}

auto Logger::GetSessionDir(const std::string& dumpDir) -> std::string {
	return std::string(dumpDir + std::to_string(timestamp.time_since_epoch().count()) + "/");
}

auto  Logger::GetSessionDir(const std::wstring& dumpDir) -> std::wstring {
	return std::wstring(dumpDir + std::to_wstring(timestamp.time_since_epoch().count()) + L"/");
}

auto Logger::GetMetadataFileName(const std::string &sessionDir) -> std::string {
	return sessionDir + "meta" + GetLogFileExtension(sessionDir);
}

auto Logger::GetMetadataFileName(const std::wstring &sessionDir) -> std::wstring {
	return sessionDir + L"meta" + GetLogFileExtension(sessionDir);
}

auto Logger::GetLogFileName(const std::string& sessionDir, std::size_t generationsPassed) -> std::string {
	return std::string(sessionDir + "generation_" + std::to_string(generationsPassed) + GetLogFileExtension(sessionDir));
}

auto Logger::GetLogFileName(const std::wstring& sessionDir, std::size_t generationsPassed) -> std::wstring {
	return std::wstring(sessionDir + L"generation_" + std::to_wstring(generationsPassed) + GetLogFileExtension(sessionDir));
}

auto Logger::SetFullLoggingPath(const std::string& path) -> void {
	fullLoggingPathOnUnix = path;
}

auto Logger::SetFullLoggingPath(const std::wstring& path) -> void {
	fullLoggingPathOnWindows = path;
}

auto Logger::LogGeneration(std::size_t generation, const std::string& log) -> void {
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
	if (!fullLoggingPathOnWindows.empty()) {
		auto logFileName = GetLogFileName(fullLoggingPathOnWindows, generation);
		std::ofstream logFile(logFileName);
		logFile << log;
		logFile.close();

		return;
	}
#else
	if (!fullLoggingPathOnUnix.empty()) {
		auto logFileName = GetLogFileName(fullLoggingPathOnUnix, generation);
		std::ofstream logFile(logFileName);
		logFile << log;
		logFile.close();

		return;
	}
#endif
	throw std::runtime_error("No logging directory found. Did you forget to call Logger::CreateLoggingDirs()?");
}

auto Logger::LogMetadata(Type::fitness_t maxFitness) -> void {
	metaData += "{\"max_fitness\":" + std::to_string(maxFitness) + "},";
	auto logToPrint = "{\"generations\":[" + metaData.substr(0, metaData.length() - 1) + "]}";

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
	if (!fullLoggingPathOnWindows.empty()) {
		auto logFileName = GetMetadataFileName(fullLoggingPathOnWindows);
		std::ofstream logFile(logFileName);
		logFile << logToPrint;
		logFile.close();

		return;
	}
#else
	if (!fullLoggingPathOnUnix.empty()) {
		auto logFileName = GetMetadataFileName(fullLoggingPathOnUnix);
		std::ofstream logFile(logFileName);
		logFile << logToPrint;
		logFile.close();

		return;
	}
#endif
	throw std::runtime_error("No logging directory found. Did you forget to call Logger::CreateLoggingDirs()?");
}
