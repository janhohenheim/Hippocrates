#pragma once
#include <string>
#include <experimental/filesystem>
#include <chrono>
namespace JNF_NEAT {

	class Logger {
		public:
			void CreateLoggingDirs();
			void LogGeneration(std::size_t generation, const std::string& log);

		private:
			std::string GetCurrentDir(const char *);
			std::wstring GetCurrentDir(const wchar_t *);
			
			std::string GetLogFolder(const std::string&);
			std::wstring GetLogFolder(const std::wstring&);
			
			
			std::string GetSessionDir(const std::string& dumpDir);
			std::wstring GetSessionDir(const std::wstring& dumpDir);

			std::string GetLogFileExtension(const std::string&);
			std::wstring GetLogFileExtension(const std::wstring&);
			
			std::string GetLogFileName(const std::string& sessionDir, std::size_t generationsPassed);
			std::wstring GetLogFileName(const std::wstring& sessionDir, std::size_t generationsPassed);
			
			void SetFullLoggingPath(const std::string& path);
			void SetFullLoggingPath(const std::wstring& path);

		private:
			std::chrono::system_clock::time_point timestamp;
			std::string fullLoggingPathOnUnix;
			std::wstring fullLoggingPathOnWindows;
	};

}