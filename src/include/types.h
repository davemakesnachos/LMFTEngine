#ifndef _TYPES_H_
#define _TYPES_H_
#include <SDL2/SDL.h>

typedef SDL_Event SystemEventType;

class Vec2 {
public:
	Vec2(void) { x=0; y=0; };
	Vec2(float _x, float _y) { x=_x; y=_y; };

	float x;
	float y;
};

#endif /* _TYPES_H */