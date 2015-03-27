#include "VFactory.h"
#include "VPlayingField.h"

NAMESPACE_VIEW_B

IVPlayingField* VFactory::createPlayingField()
{
	return new VPlayingField();
}

NAMESPACE_VIEW_E