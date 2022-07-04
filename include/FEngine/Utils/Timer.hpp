#ifndef TIMER_H
#define TIMER_H

#include <ctime>

//***THIS IS NOT MY CODE***
//Credit goes to sfuo for writing this amazing Timer class
//Class link: https://www.daniweb.com/programming/software-development/code/428040/simple-timer-class-c
//sfuo: daniweb.com/members/559812/sfuo

class Timer {
public:

	Timer();
	bool isStarted();
	bool isStopped();
	bool isPaused();
	bool isActive();

	void pause();
	void resume();
	void stop();
	void start();
	void reset();

	float getElapsedTime();

private:

     clock_t startedAt = 0;
     clock_t pausedAt = 0;
     bool started = false;
     bool paused = false;

};


#endif
