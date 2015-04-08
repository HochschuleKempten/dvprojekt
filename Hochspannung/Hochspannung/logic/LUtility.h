#ifndef _LUTILITY_H_
#define _LUTILITY_H_

#include <vector>
#include <string>
#include <sstream>
#include <regex>
#include <typeinfo>
#include <Windows.h>

inline std::vector<std::string> split(std::string str, const char delimiter)
{
	std::vector<std::string> internal;
	std::stringstream ss(str); // Turn the string into a stream.
	std::string tok;

	while (getline(ss, tok, delimiter)) {
		internal.push_back(tok);
	}

	return internal;
}

/**
 * @brief returns the class name for an identifier.
 *
 * Example usage:
 * @code
 * //The calls are done via the appropriate macro
 * getClassName(this):
 * getClassName(*this);
 * getClassName(VPlayingField);
 * @endcode
 */
inline std::string getClassName(const std::type_info& typeInfo)
{
	//Types look like: class HighVoltage::view::VPlayingField
	//Pointer(x86) look like: class HighVoltage::view::VPlayingField *
	//Pointer(x64) look like: class HighVoltage::view::VPlayingField * __ptr64
	std::regex txt_regex("class (?:\\w+::)*(\\w+)(?: \\*(?: \\w+)?)?$");
	std::smatch base_match;

	//Don't use a temporary string object here, because the results will refer to it
	std::string fullName = typeInfo.name();

	if (std::regex_search(fullName, base_match, txt_regex)) {
		return base_match[1].str();
	}
	else {
		return std::string();
	}
}

#define getClassName(type) getClassName(typeid(type))

/**
 * @brief Helper exception class for the assert macro.
 */
class ExceptionOutputDebug : public std::exception
{
public:
	inline ExceptionOutputDebug(const std::string& e)
	{
		OutputDebugString("EXCEPTION! ");
		OutputDebugString(e.c_str());
		OutputDebugString("\n");
		if (1) // avoids C4702 (unreachable code)
			throw e;
	}
};

#ifdef _DEBUG
/*
 * @def ASSERT(cond, msgExpr)
 * Use this macro to check conditions at runtime in debug mode
 * Type in the conditition the behaviour you desire (the assertion fails if your condition fails)
 */
#define ASSERT(cond, msgExpr) if(!(cond)){ std::stringstream s; s << __FILE__ << "(" << __LINE__ << "): The condition " << #cond << " fails (" << msgExpr << ")" << std::endl; throw ExceptionOutputDebug(s.str()); }
#else
#define ASSERT(cond, msgExpr)
#endif

#ifdef _DEBUG
/*
 * @def DEBUG_OUTPUT(msgExpr)
 * Useful macro to print something to the visual studio output window
 */
#define DEBUG_OUTPUT(msgExpr) do { std::stringstream s; s << __FILE__ << "(" << __LINE__ << "): " << msgExpr << std::endl; OutputDebugString(s.str().c_str()); } while(0)
#else
#define DEBUG_OUTPUT(msgExpr)
#endif

#endif //_LUTILITY_H_
