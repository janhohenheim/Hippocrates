#include "logger.h"
#include <fstream>
using namespace std;
using namespace JNF_NEAT;

void Logger::CreateLoggingDirs() {
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

string Logger::GetCurrentDir(const char*) {
	return std::string((char*)std::experimental::filesystem::current_path().c_str());
}

wstring Logger::GetCurrentDir(const wchar_t*) {
	return std::wstring((wchar_t*)std::experimental::filesystem::current_path().c_str());
}

string Logger::GetLogFolder(const string&) {
	return string("/json_dumps/");
}
wstring Logger::GetLogFolder(const wstring&) {
	return wstring(L"/json_dumps/");
}
string Logger::GetLogFileExtension(const string&) {
	return string(".json");
}
wstring Logger::GetLogFileExtension(const wstring&) {
	return wstring(L".json");
}

string Logger::GetSessionDir(const string& dumpDir) {
	return string(dumpDir + to_string(timestamp.time_since_epoch().count()) + "/");
}

wstring  Logger::GetSessionDir(const wstring& dumpDir) {
	return wstring(dumpDir + to_wstring(timestamp.time_since_epoch().count()) + L"/");
}

string  Logger::GetLogFileName(const string& sessionDir, size_t generationsPassed) {
	return string(sessionDir + "generation_" + to_string(generationsPassed) + GetLogFileExtension(sessionDir));
}

wstring Logger::GetLogFileName(const wstring& sessionDir, size_t generationsPassed) {
	return wstring(sessionDir + L"generation_" + to_wstring(generationsPassed) + GetLogFileExtension(sessionDir));
}

void JNF_NEAT::Logger::SetFullLoggingPath(const std::string& path){
	fullLoggingPathOnUnix = path;
}

void JNF_NEAT::Logger::SetFullLoggingPath(const std::wstring& path){
	fullLoggingPathOnWindows = path;
}

void Logger::LogGeneration(size_t generation, const std::string& log) {
	if (!fullLoggingPathOnWindows.empty()) {
		auto logFileName = GetLogFileName(fullLoggingPathOnWindows, generation);
		ofstream logFile(logFileName);
		logFile << log;
		logFile.close();
	} else 
	if (!fullLoggingPathOnUnix.empty()) {
		auto logFileName = GetLogFileName(fullLoggingPathOnUnix, generation);
		ofstream logFile(logFileName);
		logFile << log;
		logFile.close();
	} else {
		throw runtime_error("No logging directory found. Did you forget to call Logger::CreateLoggingDirs()?");
	}
}