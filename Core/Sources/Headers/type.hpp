#pragma once
#include <vector>
#include <string>
#include <type_traits>
#include <locale>
#include <codecvt>
#include <any>

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
	std::any s;
	if (std::is_same<file_string_t, std::string>::value)
		s = std::to_string(t);
	else
		s = std::to_wstring(t);
	return std::any_cast<file_string_t>(s);
}

template<typename T>
file_string_t literal_as_file_string(T t) {
	std::any s;
	static std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	if (std::is_same<file_string_t, std::string>::value)
		s = std::string(t);
	else 
		s = converter.from_bytes(t);
	return std::any_cast<file_string_t>(s);
}

}
