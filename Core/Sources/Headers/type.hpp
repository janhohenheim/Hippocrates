#pragma once
#include <vector>
#include <string>
#include <type_traits>
#include <locale>
#include <codecvt>

#ifdef __has_include
#if __has_include(<filesystem>) && !defined _WIN32
		#include <filesystem>
		#define HIPPOCRATES_HAS_FILESYSTEM
	#elif __has_include (<experimental/filesystem>)
		#include <experimental/filesystem>
		#define HIPPOCRATES_HAS_EXPERIMENTAL_FILESYSTEM	
	#endif
#else
	#include <experimental/filesystem>
	#define HIPPOCRATES_HAS_EXPERIMENTAL_FILESYSTEM
#endif 

#ifdef __has_include
	#if __has_include(<any>) && !defined _WIN32
		#include <any>
		#define HIPPOCRATES_HAS_ANY
	#elif __has_include (<experimental/any>)
		#include <experimental/any>
		#define HIPPOCRATES_HAS_EXPERIMENTAL_ANY
	#endif
#else
	#ifdef _WIN32
		#include <any>
		#define HIPPOCRATES_HAS_ANY
	#else
		#include <experimental/any>
		#define HIPPOCRATES_HAS_EXPERIMENTAL_ANY
	#endif
#endif 


namespace Hippocrates::Type {

#ifdef _WIN32
#define HIPPOCRATES_SSCANF sscanf_s
#else
#define HIPPOCRATES_SSCANF sscanf
#endif

#ifdef HIPPOCRATES_HAS_FILESYSTEM 
	namespace Filesystem = ::std::filesystem;
#elif defined HIPPOCRATES_HAS_EXPERIMENTAL_FILESYSTEM
	namespace Filesystem = ::std::experimental::filesystem;
#endif

#ifdef HIPPOCRATES_HAS_ANY 
	using Any = ::std::any;
	#define HIPPOCRATES_ANY_CAST std::any_cast
#elif defined HIPPOCRATES_HAS_EXPERIMENTAL_ANY
	using Any = ::std::experimental::any;
	#define HIPPOCRATES_ANY_CAST std::experimental::any_cast
#endif


using connection_weight_t = float;
using neuron_value_t = float;
using neuron_values_t = ::std::vector<neuron_value_t>;
using fitness_t = double;

using file_string_t = Filesystem::path::string_type;

template<typename T>
static inline file_string_t to_file_string(const T& t) {
	Any s;
	if (std::is_same<file_string_t, std::string>::value)
		s = std::to_string(t);
	else
		s = std::to_wstring(t);
	return HIPPOCRATES_ANY_CAST<file_string_t>(s);
}

static inline file_string_t literal_as_file_string(const char* t) {
	Any s;
	static std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	if (std::is_same<file_string_t, std::string>::value)
		s = std::string(t);
	else 
		s = converter.from_bytes(t);
	return HIPPOCRATES_ANY_CAST<file_string_t>(s);
}

}
