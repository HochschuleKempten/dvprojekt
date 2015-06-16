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

inline std::string getFileExtension(const std::string& fileName)
{
	std::regex txt_regex("\\.([^.]+)$");
	std::smatch base_match;
	std::regex_search(fileName, base_match, txt_regex);

	if (base_match.size() == 2)
	{
		return base_match[1].str();
	}
	else
	{
		return "";
	}
}

inline std::vector<std::string> split(const std::string& str, const char delimiter)
{
	std::vector<std::string> internal;
	std::stringstream ss(str); // Turn the std::string into a stream.
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

	//Don't use a temporary std::string object here, because the results will refer to it
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
#define CATCH(tryExpr, error, catchExpr) try { tryExpr; } catch (const error& e) { catchExpr; }
#else
#define CATCH(tryExpr, error, catchExpr) tryExpr
#endif

#ifdef _DEBUG
/*
* @def ASSERT1(msgExpr)
* This macro always fails and throws an exception with the given message. Use it when you want to prohibit that certain code is reached.
* E. g. when you want to make sure that you never reach the <code>default</code> block in a <code>switch</code> statement.
*/
#define ASSERT1(msgExpr) {std::stringstream s; \
						s << getFileBase(__FILE__) << "(" << __LINE__ << "): Assert failed (" << msgExpr << ")" << std::endl; \
						OutputDebugString("EXCEPTION! "); \
						OutputDebugString(s.str().c_str()); \
						OutputDebugString("\n"); \
						throw std::string(s.str());}

/*
 * @def ASSERT2(cond, msgExpr)
 * Use this macro to check conditions at runtime in debug mode
 * Type in the condition the behavior you desire (the assertion fails if your condition fails)
 */
#define ASSERT2(cond, msgExpr) if(!(cond)) { \
								 std::stringstream s; \
								 s << getFileBase(__FILE__) << "(" << __LINE__ << "): The condition " << #cond << " fails (" << msgExpr << ")" << std::endl; \
								 OutputDebugString("EXCEPTION! "); \
								 OutputDebugString(s.str().c_str()); \
								 OutputDebugString("\n"); \
								 throw std::string(s.str()); \
							  }
#else
#define ASSERT1(msgExpr)
#define ASSERT2(cond, msgExpr)
#endif //_DEBUG

//Allows macro overloading for the assert macro based on http://stackoverflow.com/questions/11974170/overloading-a-macro
#define N_ARGS_IMPL2(_1, _2, count, ...) \
   count
#define N_ARGS_IMPL(args) \
   N_ARGS_IMPL2 args
#define N_ARGS(...) N_ARGS_IMPL((__VA_ARGS__, 2, 1, 0))
/* Pick the right helper macro to invoke. */
#define CHOOSER2(count) ASSERT##count
#define CHOOSER1(count) CHOOSER2(count)
#define CHOOSER(count)  CHOOSER1(count)
/* The actual macro. */
#define ASSERT_GLUE(x, y) x y
#define ASSERT(...) \
   ASSERT_GLUE(CHOOSER(N_ARGS(__VA_ARGS__)), \
               (__VA_ARGS__))

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
	lStdHandle = reinterpret_cast<long>(GetStdHandle(STD_OUTPUT_HANDLE));
	hConsoleHandle = _open_osfhandle(lStdHandle, _O_TEXT);
	pFile = _fdopen(hConsoleHandle, "w");
	*stdout = *pFile;
	setvbuf(stdout, nullptr, _IONBF, 0);
}
#endif // _DEBUG

inline float AngleToRad(float fAngle) {
	return CASTS<float>(((2.0f * M_PI) / 360.0f) * fAngle);
}

inline float RadToAngle(float fRadiant) {
	return CASTS<float>((360.0f / (2.0f * M_PI)) * fRadiant);
}

//http://en.cppreference.com/w/cpp/types/numeric_limits/epsilon
template<class T>
inline typename std::enable_if<!std::numeric_limits<T>::is_integer, bool>::type
almost_equal(T x, T y, int ulp)
{
	// the machine epsilon has to be scaled to the magnitude of the values used
	// and multiplied by the desired precision in ULPs (units in the last place)
	return std::abs(x - y) < std::numeric_limits<T>::epsilon() * std::abs(x + y) * ulp
		// unless the result is subnormal
		|| std::abs(x - y) < std::numeric_limits<T>::min();
}
#endif //_LUTILITY_H_
