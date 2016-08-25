#pragma once
#include <string>
#include <experimental/filesystem>
#include <chrono>
namespace JNF_NEAT {

	class Logger {
		public:
			auto CreateLoggingDirs() -> void;
            auto LogGeneration(std::size_t generation, const std::string& log) -> void;

		private:
			auto GetCurrentDir(const char *) -> std::string;
			auto GetCurrentDir(const wchar_t *) -> std::wstring;
			
			auto GetLogFolder(const std::string&) -> std::string;
			auto GetLogFolder(const std::wstring&) -> std::wstring;
			 
			 
			auto GetSessionDir(const std::string& dumpDir) -> std::string;
			auto GetSessionDir(const std::wstring& dumpDir) -> std::wstring;
             
			auto GetLogFileExtension(const std::string&) -> std::string;
			auto GetLogFileExtension(const std::wstring&) -> std::wstring;
			 
			auto GetLogFileName(const std::string& sessionDir, std::size_t generationsPassed) -> std::string;
			auto GetLogFileName(const std::wstring& sessionDir, std::size_t generationsPassed) -> std::wstring;
			
            auto SetFullLoggingPath(const std::string& path) -> void;
            auto SetFullLoggingPath(const std::wstring& path) -> void;

		private:
			std::chrono::system_clock::time_point timestamp;
			std::string fullLoggingPathOnUnix;
			std::wstring fullLoggingPathOnWindows;
	};

}