#include "VFactory.h"
#include "VPlayingField.h"

NAMESPACE_VIEW_B

IVPlayingField* VFactory::createPlayingField(IVMaster* master, LPlayingField* field)
{
	return new VPlayingField(master, field);
}

NAMESPACE_VIEW_E