#pragma once

#pragma warning ( push )
#pragma warning ( disable: 4201 )	//Occurs in HVector.h
#include "Vektoria\Root.h"
#include "VektoriaMath\Util.h"
#pragma warning ( pop )

#include "../logic/LGeneral.h"
#include "../logic/LUtility.h"
#include <vector>
#include <map>
#include <list>

using namespace Vektoria;

#define NAMESPACE_VIEW_B namespace HighVoltage{ //namespace view{
#define NAMESPACE_VIEW_E }
