#include "VFactory.h"
#include "VPlayingField.h"

NAMESPACE_VIEW_B


IVPlayingField* VFactory::createPlayingField(LPlayingField* field)
{
	return new VPlayingField(vMaster, field);
}


NAMESPACE_VIEW_E
