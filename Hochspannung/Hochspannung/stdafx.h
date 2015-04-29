// stdafx.h : Includedatei f�r Standardsystem-Includedateien
// oder h�ufig verwendete projektspezifische Includedateien,
// die nur in unregelm��igen Abst�nden ge�ndert werden.
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>



// Hier auf zus�tzliche Header, die das Programm erfordert, verweisen.

#include <boost\asio.hpp>
#include <vector>
#include <map>
#include <list>
#include <string>
#include <sstream>
#include <memory>
#include "logic/LUtility.h"
#include "logic/cpplinq.hpp"

#include <boost\thread\thread.hpp>
#include <boost\asio\ip\tcp.hpp>
#include <boost\asio\deadline_timer.hpp>
