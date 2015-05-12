#pragma once
#include <Root.h>
#include <Util.h>
#include <Timer.h>
#include <Log.h>

namespace Vektoria
{

	class CGameBase
	{
	public:
		// Destructor
		~CGameBase(void) {}

		// Initialize the game.
		virtual void Init(void) = 0;

		// Tick (render) the game.
		virtual bool Tick(void)
		{
			if (FirstTick())
			{
				timer.SwitchFrameRateCalculationOn();
				bFirstTick = false;
			}
			timer.Tick(fTime, fTimeDelta);
			return false;
		}

		// Finalize the game.
		virtual void Fini(void) = 0;

		// Indicates wheather this is the first tick.
		bool FirstTick(void) const { return bFirstTick; }

		// Ge the current game time.
		float Time(void) const { return fTime; }

		// Get the time delta.
		float TimeDelta(void) const { return fTimeDelta; }


	protected:
		// Protected constructor
		CGameBase(void) : bFirstTick(true), fTime(0.0f), fTimeDelta(0.0f) {};


	private:
		// Private data
		CTimer timer;		// The timer.
		float fTime;		// The game time.
		float fTimeDelta;	// The time delta.
		bool bFirstTick;	// Indicates wheather this is the first tick.
	};

}