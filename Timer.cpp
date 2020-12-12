#include "Timer.hpp"

Timer::Timer() {
	startedAt = 0;
	pausedAt = 0;
	paused = false;
	started = false;
}

bool Timer::isStarted() {
	return started;
}

bool Timer::isStopped() {
	return !started;
}

bool Timer::isPaused() {
	return paused;
}

bool Timer::isActive()
{
	return !paused & started;
}

void Timer::pause() {
	if( paused || !started )
		return;

	paused = true;
	pausedAt = clock();
}

void Timer::resume() {
	if( !paused )
		return;

	paused = false;
	startedAt += clock() - pausedAt;
}

void Timer::stop() {
	started = false;
}

void Timer::start() {
	if( started )
		return;

	started = true;
	paused = false;
	startedAt = clock();
}

void Timer::reset() {
	paused = false;
	startedAt = clock();
}

clock_t Timer::getElapsedTime() {
	if( !started )
		return 0;

	if( paused )
		return pausedAt - startedAt;

	return clock() - startedAt;
}
