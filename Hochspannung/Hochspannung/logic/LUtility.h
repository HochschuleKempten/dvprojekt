#ifndef _LUTILITY_H_
#define _LUTILITY_H_
#define _USE_MATH_DEFINES

#include <vector>
#include <string>
#include <sstream>
#include <regex>
#include <typeinfo>
#include <Windows.h>
#include <fcntl.h>
#include <io.h>
#include <math.h>

inline std::vector<std::string> split(const std::string& str, const char delimiter)
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
 * Make sure you use the appropriate macro instead of this function.
 *
 * Example usage:
 * @code
 * //The calls are done via the appropriate macro
 * getClassName(this):
 * getClassName(*this);
 * getClassName(VPlayingField);
 * @endcode
 *
 * @param typeInfo The type you want the class name be retrieved from (from the macro).
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

inline std::string getFileBase(const std::string &str)
{
	return str.substr(str.find_last_of("\\") + 1);
}

#ifdef _DEBUG
/*
* @def DEBUG_OUTPUT(msgExpr)
* Useful macro to print something to the visual studio output window
*/
#define DEBUG_OUTPUT(msgExpr) { std::stringstream s; \
								s << getFileBase(__FILE__) << "(" << __LINE__ << "): " << msgExpr << std::endl; \
								OutputDebugString(s.str().c_str()); }
#else
#define DEBUG_OUTPUT(msgExpr)
#endif //_DEBUG

#ifdef _DEBUG
/*
* @def DEBUG_EXPRESSION(expr)
* This macro can be used to write single line expressions which will be evaluated only in debug mode
*/
#define DEBUG_EXPRESSION(expr) expr
#else
#define DEBUG_EXPRESSION(expr)
#endif //_DEBUG

#ifdef _DEBUG
/*
 * @def ASSERT(cond, msgExpr)
 * Use this macro to check conditions at runtime in debug mode
 * Type in the condition the behavior you desire (the assertion fails if your condition fails)
 */
#define ASSERT(cond, msgExpr) if(!(cond)) { \
								 std::stringstream s; \
								 s << getFileBase(__FILE__) << "(" << __LINE__ << "): The condition " << #cond << " fails (" << msgExpr << ")" << std::endl; \
								 OutputDebugString("EXCEPTION! "); \
								 OutputDebugString(s.str().c_str()); \
								 OutputDebugString("\n"); \
								 throw std::string(s.str()); \
							  }
#else
#define ASSERT(cond, msgExpr)
#endif //_DEBUG

#ifdef _DEBUG
#include <boost\numeric\conversion\cast.hpp>
/*
* @def CASTS
* This macro performs a (static) cast between types. In debug mode this is done using <code>boost::numeric_cast</code> with runtime checks
* and in release mode this is just done using normal <code>CASTS</code> (without the cost of runtime checks).
*/
#define CASTS boost::numeric_cast
#else
#define CASTS static_cast
#endif //_DEBUG

#ifdef _DEBUG
/*
* @def CASTD
* This macro performs a dynamic cast in debug mode (with type checks) and a static cast in release mode (without any checks).
*/
#define CASTD dynamic_cast
#else
#define CASTD static_cast
#endif //_DEBUG

#define NON_COPYABLE(className) private: \
									className(const className&) = delete; \
									className(const className&&) = delete; \
									className& operator=(const className&) = delete; \
									className& operator=(const className&&) = delete

#ifdef _DEBUG
/**
 * Call this method at application startup to redirect stdout to a newly created console (if there´s not already one)
 */
inline void redirectIOToConsole()
{
	int hConsoleHandle;
	long lStdHandle;
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	FILE* pFile;

	// allocate a console for this app
	AllocConsole();

	// set the screen buffer to be big enough to let us scroll text
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleInfo);
	consoleInfo.dwSize.Y = 500;
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), consoleInfo.dwSize);

	// redirect unbuffered STDOUT to the console
	lStdHandle = (long)GetStdHandle(STD_OUTPUT_HANDLE);
	hConsoleHandle = _open_osfhandle(lStdHandle, _O_TEXT);
	pFile = _fdopen(hConsoleHandle, "w");
	*stdout = *pFile;
	setvbuf(stdout, NULL, _IONBF, 0);
}
#endif // _DEBUG

inline float AngleToRad(float fAngle) {
	return CASTS<float>((M_PI_2 * fAngle) / 360.0);
}

inline float RadToAngle(float fRadiant) {
	return CASTS<float>((360.0f * fRadiant) / M_PI_2);
}
#endif //_LUTILITY_H_
