#pragma once

class IVPlayingField;
class IVMaster;
class LPlayingField;

class IVFactory
{
protected:
	IVMaster* m_vMaster;

public:
	IVFactory(IVMaster* vMaster) :
		m_vMaster(vMaster)
	{
	};
	virtual ~IVFactory(){};
	virtual IVPlayingField* createPlayingField(LPlayingField* field) = 0;
};

