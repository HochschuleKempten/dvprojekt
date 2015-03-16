////////////////////////////////////////////////////
/// @file Singleton.h
/// @description Interface for single-instance global classes.
/// See: http://www.codeproject.com/Articles/4750/Singleton-Pattern-A-review-and-analysis-of-existin for implementation details.
///
/// @author Matthias Sommer
/// ** Copyright (c) Matthias Sommer **
/// ** This file is part of vektoria **
////////////////////////////////////////////////////
#pragma once
#include <cassert>	// assert

using namespace std;

namespace Vektoria
{
	template <class TDerived>
	class ISingleton
	{
	public:
		// Functions
		// Get the single instance.
		template <typename... TArgs>
		inline static TDerived& Singleton(TArgs... args)
		{
			if (!pInstance)
			{
				if (bDestroyed)
				{
					bDestroyed = false;
				}
				pInstance = new TDerived(forward<TArgs>(args)...);
				AtDestruction(ISingleton::DestroySingleton);
			}
			return *pInstance;
		}

		// Destroy the single instance.
		inline static void DestroySingleton(void)
		{
			if (pInstance)
			{
				delete pInstance;
				pInstance = nullptr;
				bDestroyed = true;
			}
		}


	protected:
		// Protected constructor
		inline explicit ISingleton(void)
		{
			assert(!pInstance);
			pInstance = static_cast<TDerived*>(this);
			bDestroyed = false;
		}

		// Destructor
		inline ~ISingleton(void)
		{
			pInstance = nullptr;
			bDestroyed = true;
		}


	private:
		// Private data
		static TDerived* pInstance;	// The single instance.
		static bool bDestroyed;


		// Private copy constructor
		inline explicit ISingleton(const ISingleton<TDerived>&) {}


		// Overloaded assignment operator.
		inline ISingleton& operator=(const ISingleton<TDerived>&) { return *this; }


		// Private functions
		// To call ISingleton::Destroy at destruction.
		inline static void AtDestruction(void(*pFunction)())
		{
			atexit(pFunction); // Call destroy at exit.
		}
	};


	template <class TDerived> 
	TDerived* ISingleton<TDerived>::pInstance = nullptr;

	template <class TDerived>
	bool ISingleton<TDerived>::bDestroyed = false;
 }