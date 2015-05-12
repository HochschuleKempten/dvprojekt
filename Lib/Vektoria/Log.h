////////////////////////////////////////////////////
/// @file Log.h
/// @description Class for writing debug/log data to files.
/// 
/// @author Matthias Sommer
/// ** Copyright (c) Matthias Sommer ** 
/// ** This file is part of vektoria **
////////////////////////////////////////////////////
#pragma once
#include "Singleton.h"

#include <string>		// string
#include <fstream>		// ofstream
#include <sstream>		// stringstream
#include <iostream>		// cout, cerr
#include <iomanip>		// setw, setfill

//using namespace std;

namespace Vektoria
{
	#define VEKTORIA_LOG_FILTER 0


	// Possible log levels.
	// When used as filter ELL_DEBUG means log everything and ELL_NONE means log (nearly) nothing.
	// When used to print logging information ELL_DEBUG will have lowest priority while ELL_NONE messages are never filtered and always printed.
	enum ELogLevel
	{
		ELL_DEBUG,			// Used for printing information helpful in debugging.
		ELL_INFORMATION,	// Useful information to print. For example hardware infos or something started / stopped.
		ELL_WARNING,		// Warnings that something isn't as expected and can cause oddities. 
		ELL_ERROR,			// Something went wrong. 
		ELL_NONE			// Logs with ELL_NONE will never be filtered. And used as filter it will remove all logging except ELL_NONE messages.
	};


	// Log event argument.
	struct SLogEventArg
	{
		// Data
		std::string sMessage;
		ELogLevel eLogLevel;
		bool bMaskDebug;


		// Constructors
		// Standard constructor
		SLogEventArg(const std::string& sMessage, ELogLevel eLogLevel, bool bMaskDebug) : sMessage(sMessage), eLogLevel(eLogLevel), bMaskDebug(bMaskDebug) {}
	};


	class CLog : public ISingleton<CLog>
	{
	public:
		// Stream object which targets a log.
		// (You can stream control operations to this object too, such as std::setw() and std::setfill() to control formatting.)
		// A stream logger object makes it simpler to send various things to a log.
		// You can just use the operator<< implementation to stream	anything to the log, which is cached until a Stream::Flush is encountered, or the stream itself is destroyed, 
		// at which point the cached contents are sent to the underlying log. 
		// You can use CLog::GetStream() directly without assigning it to a local variable and as soon as the streaming is finished, the object will be destroyed and the message logged.
		// Note: A stream object is not thread safe, so do not pass it between threads. Multiple threads can hold their own stream instances pointing at the same Log though and that is threadsafe.
		class CStream
		{
		public:
			// Simple type to indicate a flush of the stream to the log.
			struct Flush {};


			// Constructors
			// Standard constructor
			CStream(CLog* pLog, ELogLevel eLogLevel, bool bMaskDebug) : pLog(pLog), eLogLevel(eLogLevel), bMaskDebug(bMaskDebug) {}

			// Copy constructor
			CStream(const CStream& stream) : pLog(stream.pLog), eLogLevel(stream.eLogLevel), bMaskDebug(stream.bMaskDebug)
			{
				this->stream.str(stream.stream.str());	// Explicit copy of stream required, cause gcc doesn't like implicit.
			}

			// Destructor
			~CStream(void)
			{
				// Flush on destroy.
				if (stream.tellp() > 0)
				{
					pLog->LogMessage(stream.str(), eLogLevel, bMaskDebug);
				}
			}


			// Operator overloads
			// Overloaded operator<<.
			template <typename T>
			CStream& operator<< (const T& v)
			{
				stream << v;
				return *this;
			}

			// Overloaded operator<<.
			CStream& operator<< (const Flush& flush)
			{
				(void)flush;
				pLog->LogMessage(stream.str(), eLogLevel, bMaskDebug);
				stream.str("");
				return *this;
			}


		protected:
			// Protected datas
			CLog* pLog;				// The target log.
			ELogLevel eLogLevel;	// The log level.
			bool bMaskDebug;		// Indicates whether debug output is maked.
			typedef std::stringstream CLogStream;
			CLogStream stream;		// The base stream.
		};


		// Constructors
		// Standard constructor
		CLog(const std::string& sLogName = "vektoria.log", bool bDebugOutput = true, bool bFileOutput = true);

		// Destructors
		~CLog(void);


		// Functions
		// Log a message to the debugger and to log file (the default is "vektoria.log").
		void LogMessage(const std::string& sMessage, ELogLevel eLogLevel = ELL_DEBUG, bool bMaskDebug = false);

		// Get a stream object targeting this log.
		CStream GetStream(ELogLevel eLogLevel = ELL_DEBUG, bool bMaskDebug = false) { return CStream(this, eLogLevel, bMaskDebug); }

		// Get the name of the log.
		const std::string& GetLogName(void) const { return sLogName; }

		// Set the log filter level.
		void SetLogFilter(ELogLevel eLogFilter) { this->eLogFilter = eLogFilter; }

		// Get whether debug output is enabled for this log.
		bool DebugOutput(void) const { return bDebugOutput; }

		// Enable output of log messages to the debugger.
		void EnableDebugOutput(void) { bDebugOutput = true; }

		// Disable output of log messages to the debugger.
		void DisableDebugOutput(void) { bDebugOutput = false; }
		
		// Get whether file output is suppressed for this log.
		bool FileOutput(void) const { return bFileOutput; }
		
		// Get whether time stamps are printed for this log.
		bool TimeStampEnabled(void) const { return bTimeStamp; }

		// Enable time stamps.
		void EnableTimeStamp(void) { bTimeStamp = true; }

		// Disable time stamps.
		void DisableTimeStamp(void) { bTimeStamp = false; }


	protected:
		// Protected data
		std::ofstream log;		// The output stream.
		std::string sLogName;	// The name of the log file.

		ELogLevel eLogFilter;	// The log filter.

		bool bDebugOutput;	// Indicates whether debug output is enabled for this log.
		bool bFileOutput;	// Indicates whether file output is enabled for this log.
		bool bTimeStamp;	// Indicates whether time stamps are printed for this log.
	};


	// Used for printing information helpful in debugging.
	#define LOG_DEBUG CLog::Singleton().GetStream(ELL_DEBUG)

	// Useful information to print. For example hardware infos or something started / stopped.
	#define LOG_INFO CLog::Singleton().GetStream(ELL_INFORMATION)

	// Warnings that something isn't as expected and can cause oddities. 
	#define LOG_WARNING CLog::Singleton().GetStream(ELL_WARNING)

	// Something went wrong. 
	#define LOG_ERROR CLog::Singleton().GetStream(ELL_ERROR)

	// Flush the stream to the log and start a new line.
	#define ENDL CLog::CStream::Flush()
}