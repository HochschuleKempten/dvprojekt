#pragma once

#pragma warning ( push )
#pragma warning ( disable: 4201 )	//Occurs in HVector.h
#include <Vektoria\Root.h>
#include <VektoriaMath\Util.h>
#pragma warning ( pop )

#include "../logic/LUtility.h"

//Include only if no precompiled header is set
#ifndef _VECTOR_
#include <vector>
#include <map>
#include <list>
#include <string>
#include <sstream>
#include <memory>
#endif

using namespace Vektoria;

#define NAMESPACE_VIEW_B namespace HighVoltage{
#define NAMESPACE_VIEW_E }
