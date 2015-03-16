#pragma once

#include <string>
#include <time.h>
#include <sstream>
#include <vector>

#include <iostream>
#include <stdio.h>
//#include <winsock2.h> 
#include "LibString.h"


using namespace std;

namespace Vektoria
{

class CNetworkPackage
{
	int uid;
	int timeToLive;
protected:
	int type;
public:
	CNetworkPackage();
	CNetworkPackage(int timeToLive);
	int GetUId();
	virtual int GetType() = 0;
	int GetTimeToLive();
	virtual string ToString();
	virtual string Serialise() = 0;
	virtual CNetworkPackage* GenerateObject(string serialisedString) = 0;

};

}