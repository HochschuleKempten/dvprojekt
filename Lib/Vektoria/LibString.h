#pragma once

#include <iostream>
#include <cctype>
#include <string>
#include <vector>

namespace Vektoria
{
class CLibString
{
public:
	CLibString(void);
	~CLibString(void);

	static std::string toLower(const std::string str);
	static std::string toUpper(const std::string str);
	static std::string rTrim(const std::string str);
	static std::string lTrim(const std::string str);
	static std::string trim(const std::string str);

	static std::vector<std::string> explode(const std::string delimiter, const std::string str);
	static std::string implode(const std::string glue, const std::vector<std::string> &pieces);

};

}