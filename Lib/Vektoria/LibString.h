#pragma once

#include <iostream>
#include <cctype>
#include <string>
#include <vector>
using namespace std;

namespace Vektoria
{
class CLibString
{
public:
	CLibString(void);
	~CLibString(void);

	static string toLower(const string str);
	static string toUpper(const string str);
	static string rTrim(const string str);
	static string lTrim(const string str);
	static string trim(const string str);

	static vector<string> explode(const string delimiter, const string str);
	static string implode(const string glue, const vector<string> &pieces);

};

}