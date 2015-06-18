#pragma once
#include "VGeneral.h"
#include "VScreenIngame.h"

NAMESPACE_VIEW_B

class VScreenIngame;

class VContextInfo
{

public:
	explicit VContextInfo(VScreenIngame* vScreenIngame);
	~VContextInfo();
private:
	
	VScreenIngame* m_vScreenIngame;
	std::unordered_map<std::string, std::string> m_infoValues;

public:
	void updateValue(const std::string& name, const std::string& value);

	void showContextInfo();
	
};

NAMESPACE_VIEW_E
