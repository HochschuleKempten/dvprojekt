////////////////////////////////////////////////////
/// @file Exception.h
/// @description When thrown, the exception provides information about an error that has occurred inside the engine.
/// @remarks This is the object that encapsulates the detail of a thrown exception.
/// The application using vektoria should always ensure that the exceptions are caught, 
/// so all vektoria engine functions should occur within a try{} catch (Vektoria::CException& e) {} block.
/// 
/// @author Matthias Sommer
/// ** Copyright (c) Vektoria ** 
/// ** This file is part of vektoria **
////////////////////////////////////////////////////
#ifndef EXCEPTION_H
#define EXCEPTION_H
#ifdef _WIN32
#pragma once
#endif

#include <exception>	// exception
#include <string>		// string
#include <cassert>		// assert

using namespace std;

namespace Vektoria
{
	// Static definitions of error types.
	enum EExceptionType
	{
		EET_CANNOT_WRITE_TO_FILE,
		EET_INVALID_STATE,
		EET_INVALID_PARAMETER,
		EET_RENDERAPI_ERROR,
		EET_INPUTAPI_ERROR,
		EET_DUPLICATE_ITEM,
		EET_ITEM_NOT_FOUND,
		EET_FILE_NOT_FOUND,
		EET_INTERNAL_ERROR,
		EET_RUNTIME_ASSERTION_FAILED,
		EET_NOT_IMPLEMENTED
	};

	// Array holding the exception type names.
	const char* const sExceptionTypeNames[] =
	{
		"cannot_write_to_file",
		"invalid_state",
		"invalid_paramter",
		"renderapi_error",
		"inputapi_error",
		"duplicate_item",
		"item_not_found",
		"file_not_found",
		"internal_error",
		"runtime_assertion_failed",
		"not_implemented"
	};


	class CException : public exception
    {
    public:
        // Constructors 
		// Standard constructor
		CException(EExceptionType eExceptionType, const string& sDescription, const string& sSource, const char* acFile, long lLine);

		// Copy constructor
		CException(const CException& exception);

		// Destructor 
		// Needed for compatibility with std::exception.
		~CException(void) throw() {}


		// Operator overloads
		// Overloaded assignment operator.
		CException& operator=(const CException& exception);


		// Functions
		// Get a string with the full description of this error.
		// The description contains the error number, the description supplied by the thrower, what routine threw the exception, and will also supply extra platform-specific information where applicable.
		virtual string GetFullDescription(void) const;

		// Get the error type.
		virtual EExceptionType GetExceptionType(void) const throw();

		// Get the source function.
		virtual const string& GetSource(void) const { return sSource; }

		// Get source file name.
		virtual const string& GetFile(void) const { return sFile; }
		 
		// Get line number.
		virtual long GetLine(void) const { return lLine; }

		// Get a string with the description of the exception.
		virtual const string& GetDescription(void) const { return sDescription; }

		// Override std::exception::what.
		virtual const char* what(void) const throw() { return GetFullDescription().c_str(); }


	protected:
		// Protected data
		EExceptionType eExceptionType;		// The error type.
		string sExceptionTypeName;			// The error type name.
		string sDescription;				// The description.
		string sSource;						// The source function.
		string sFile;						// The source file.
		long lLine;							// The line number.
    };


	// Throw an exception.
	#define THROW_EXCEPTION(eExceptionType, sDescription, sSource) throw CException(eExceptionType, sDescription, sSource, __FILE__, __LINE__ );


	#if VEKTORIA_ASSERT_MODE == 1	// 1 - RELEASE_EXCEPTIONS
	#if VEKTORIA_DEBUG
		// Evaluate assertion.
		// If the argument expression of this macro evaluates to zero (i.e., the expression is false), a message is written to the standard error device and abort is called, terminating the program execution.
		#define VEKTORIA_ASSERT(a, b) assert((a) && (b))
	#else
		// Evaluate assertion.
		// If the argument expression of this macro evaluates to zero (i.e., the expression is false), a "runtime_assertion_failed" exception is thrown.
		#define VEKTORIA_ASSERT(a, b) if (!(a)) THROW_EXCEPTION(EET_RUNTIME_ASSERTION_FAILED, (b), "No function info!")
	#endif	
	#else							// 0 - STANDARD
		// Evaluate assertion.
		// If the argument expression of this macro evaluates to zero (i.e., the expression is false), a message is written to the standard error device and abort is called, terminating the program execution.
		#define VEKTORIA_ASSERT(a, b) assert((a) && (b))
	#endif
}

#endif // EXCEPTION_H