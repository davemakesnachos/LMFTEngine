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

#define D_2_R 3.141592654/180.0
#define R_2_D 180.0/3.141592654

#define RAD2DEG(x) x * R_2_D
#define DEG2RAD(x) x * D_2_R

#endif /* _TYPES_H */