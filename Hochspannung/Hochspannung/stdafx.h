// stdafx.h : Includedatei f�r Standardsystem-Includedateien
// oder h�ufig verwendete projektspezifische Includedateien,
// die nur in unregelm��igen Abst�nden ge�ndert werden.
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>



// Hier auf zus�tzliche Header, die das Programm erfordert, verweisen.

#include <boost/asio.hpp>
#include <vector>
#include <array>
#include <map>
#include <list>
#include <string>
#include <sstream>
#include <memory>
#include <random>
#include <chrono>
#include "logic/LUtility.h"
#include "logic/Array2D.h"
#include "logic/cpplinq.hpp"

#include <boost/thread/thread.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <boost/graph/strong_components.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/lookup_edge.hpp>
