#include <fstream>
#include "../Headers/logger.h"
using namespace std;
using namespace Hippocrates;

auto Logger::CreateLoggingDirs() -> void {
	timestamp = chrono::system_clock::now();

	auto* pathType = experimental::filesystem::current_path().c_str();
	auto currentDir = GetCurrentDir(pathType);
	auto logFolder = GetLogFolder(pathType);
	auto logFileExtension = GetLogFileExtension(pathType);


	auto dumpDir(currentDir + logFolder);
	if (!experimental::filesystem::exists(dumpDir)) {
		experimental::filesystem::create_directory(dumpDir);
	}


	auto sessionDir = GetSessionDir(dumpDir);
	if (!experimental::filesystem::exists(sessionDir)) {
		experimental::filesystem::create_directory(sessionDir);
	}

	SetFullLoggingPath(sessionDir);
}

auto Logger::GetCurrentDir(const char*) -> string {
	return std::string((char*)std::experimental::filesystem::current_path().c_str());
}

auto Logger::GetCurrentDir(const wchar_t*) -> wstring {
	return std::wstring((wchar_t*)std::experimental::filesystem::current_path().c_str());
}

auto Logger::GetLogFolder(const string&) -> string {
	return string("/json_dumps/");
}
auto Logger::GetLogFolder(const wstring&) -> wstring {
	return wstring(L"/json_dumps/");
}
auto Logger::GetLogFileExtension(const string&) -> string {
	return string(".json");
}
auto Logger::GetLogFileExtension(const wstring&) -> wstring {
	return wstring(L".json");
}

auto Logger::GetSessionDir(const string& dumpDir) -> string {
	return string(dumpDir + to_string(timestamp.time_since_epoch().count()) + "/");
}

auto  Logger::GetSessionDir(const wstring& dumpDir) -> wstring {
	return wstring(dumpDir + to_wstring(timestamp.time_since_epoch().count()) + L"/");
}

auto Logger::GetLogFileName(const string& sessionDir, size_t generationsPassed) -> string {
	return string(sessionDir + "generation_" + to_string(generationsPassed) + GetLogFileExtension(sessionDir));
}

auto Logger::GetLogFileName(const wstring& sessionDir, size_t generationsPassed) -> wstring {
	return wstring(sessionDir + L"generation_" + to_wstring(generationsPassed) + GetLogFileExtension(sessionDir));
}

auto Hippocrates::Logger::SetFullLoggingPath(const std::string& path) -> void {
	fullLoggingPathOnUnix = path;
}

auto Hippocrates::Logger::SetFullLoggingPath(const std::wstring& path) -> void {
	fullLoggingPathOnWindows = path;
}

auto Logger::LogGeneration(size_t generation, const std::string& log) -> void {
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
	if (!fullLoggingPathOnWindows.empty()) {
		auto logFileName = GetLogFileName(fullLoggingPathOnWindows, generation);
		ofstream logFile(logFileName);
		logFile << log;
		logFile.close();

		return;
	}
#else
	if (!fullLoggingPathOnUnix.empty()) {
		auto logFileName = GetLogFileName(fullLoggingPathOnUnix, generation);
		ofstream logFile(logFileName);
		logFile << log;
		logFile.close();

		return;
	}
#endif
	throw runtime_error("No logging directory found. Did you forget to call Logger::CreateLoggingDirs()?");
}
