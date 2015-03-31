#ifndef _LUTILITY_H_
#define _LUTILITY_H_

#include <vector>
#include <string>
#include <sstream>

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

#endif //_LUTILITY_H_
