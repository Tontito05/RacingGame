#pragma once

#include "Globals.h"
#include "Timer.h"

class Timer
{
public:

	// Constructor
	Timer();

	void Start();
	double ReadSec() const;
	void Stop();
	void continueTimer();

private:

    // Start time in seconds
	double started_at; 
	double paused_at = 0;

	bool time_paused;
};