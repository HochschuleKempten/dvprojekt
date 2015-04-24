// stdafx.h : Includedatei für Standardsystem-Includedateien
// oder häufig verwendete projektspezifische Includedateien,
// die nur in unregelmäßigen Abständen geändert werden.
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>



// Hier auf zusätzliche Header, die das Programm erfordert, verweisen.

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
