#pragma once

#include "Vektoria\Root.h"
#include "VektoriaMath\Util.h"
#include <vector>
#include <map>

using namespace Vektoria;

#define NAMESPACE_VIEW_B namespace HighVoltage{ namespace view{
#define NAMESPACE_VIEW_E }}
#define DEBUG_OUTPUT(expr) do { std::stringstream s; s << expr << std::endl; OutputDebugString(s.str().c_str()); } while(0)
