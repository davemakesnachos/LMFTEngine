#ifndef _TIMER_H_
#define _TIMER_H_

#include <SDL2/SDL.h>

class Timer {
public:
	static unsigned long timestamp(void) {
		return (ticks() * 1000 / ticksFreq());
	}

	static void delay(unsigned long ms) {
		SDL_Delay(ms);
	}

	static unsigned long ticksFreq(void) {
		return SDL_GetPerformanceFrequency();
	}

	static unsigned long ticks(void) {
		return SDL_GetPerformanceCounter();
	}
};

#endif /* _TIMER_H_ */