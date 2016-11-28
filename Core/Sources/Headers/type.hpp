#pragma once
#include <vector>
#include <string>
#include <type_traits>

#ifdef __has_include
#if __has_include(<filesystem>) && !defined _WIN32
		#include <filesystem>
		namespace Hippocrates::Type::Filesystem = ::std::filesystem;
	#elif __has_include (<experimental/filesystem>)
		#include <experimental/filesystem>
		namespace Hippocrates::Type::Filesystem = ::std::experimental::filesystem;
	#endif

#else
	#include <filesystem>
	namespace Hippocrates::Type::Filesystem = ::std::filesystem;
#endif 


namespace Hippocrates::Type {

#ifdef _WIN32
#define HIPPOCRATES_SSCANF sscanf_s
#else
#define HIPPOCRATES_SSCANF sscanf
#endif



using connection_weight_t = float;
using neuron_value_t = float;
using neuron_values_t = ::std::vector<neuron_value_t>;
using fitness_t = double;

using file_string_t = Filesystem::path::string_type;


#if std::is_same<file_string_t, std::string>
	#define HIPPOCRATES_LITERAL_AS_FILE_STRING(x) x
	template<typename T>
	auto to_file_string(T t) { return std::to_string(t); }
#else
	#define HIPPOCRATES_LITERAL_AS_FILE_STRING(x) L##x
	template<typename T>
	auto to_file_string(T t) { return std::to_wstring(t); }
#endif

}
