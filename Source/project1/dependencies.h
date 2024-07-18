<<<<<<< HEAD
#pragma once

#ifndef DEP
#define DEP

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <string>

#include <math.h>
#include <vector>
#include <utility>
#include <random>

#include <stdexcept>
#include <locale>
#include <codecvt>

#include "cppOpt.h"

using namespace std;

#define SMALL_FLOAT 0.000001f

/* String Formatting Function (Use it like fprint) */
template<typename ... Args> string string_format(const std::string& format, Args ... args)
{
	size_t size = snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
	if (size <= 0) { throw std::runtime_error("Error during formatting."); }
	std::unique_ptr<char[]> buf(new char[size]);
	snprintf(buf.get(), size, format.c_str(), args ...);
	return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
}

=======
#pragma once

#ifndef DEP
#define DEP

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <string>

#include <math.h>
#include <vector>
#include <utility>
#include <random>

#include <stdexcept>
#include <locale>
#include <codecvt>

#include "cppOpt.h"

using namespace std;

#define SMALL_FLOAT 0.000001f

/* String Formatting Function (Use it like fprint) */
template<typename ... Args> string string_format(const std::string& format, Args ... args)
{
	size_t size = snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
	if (size <= 0) { throw std::runtime_error("Error during formatting."); }
	std::unique_ptr<char[]> buf(new char[size]);
	snprintf(buf.get(), size, format.c_str(), args ...);
	return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
}

>>>>>>> 286a07f11cee1864cde8ba04f7ca282468cb8acb
#endif DEP