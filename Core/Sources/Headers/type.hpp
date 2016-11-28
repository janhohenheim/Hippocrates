#pragma once
#include <vector>
#include <string>
#include <type_traits>
#include <locale>
#include <codecvt>

#ifdef __has_include
#if __has_include(<filesystem>) && !defined _WIN32
		#include <filesystem>
		namespace Filesystem = ::std::filesystem;
	#elif __has_include (<experimental/filesystem>)
		#include <experimental/filesystem>
		namespace Filesystem = ::std::experimental::filesystem;
	#endif

#else
	#include <experimental/filesystem>
	namespace Filesystem = ::std::experimental::filesystem;
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

template<typename T>
file_string_t to_file_string(T t) {
	if (std::is_same<file_string_t, std::string>::value)
		return *reinterpret_cast<file_string_t*>(&std::to_string(t));

	return *reinterpret_cast<file_string_t*>(&std::to_wstring(t));
}

template<typename T>
file_string_t literal_as_file_string(T t) {
	if (std::is_same<file_string_t, std::string>::value)
		return *reinterpret_cast<file_string_t*>(&std::string(t));

	static std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	return *reinterpret_cast<file_string_t*>(&converter.from_bytes(t));
}

}
