#include "VFactory.h"
#include "VPlayingField.h"

NAMESPACE_VIEW_B

VFactory::VFactory(IVMaster* vMaster):
	IVFactory(vMaster)
{
}

VFactory::~VFactory()
{

}

IVPlayingField* VFactory::createPlayingField(LPlayingField* field)
{
	return new VPlayingField(m_vMaster, field);
}

NAMESPACE_VIEW_E