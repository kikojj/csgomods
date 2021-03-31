#pragma once

#define MATH_PI_RAD 57.295779513082f
#define INTERVAL_PER_TICK (1.f/64.f)
#define TICK_INTERVAL			(INTERVAL_PER_TICK)
#define TIME_TO_TICKS(dt) ((int)( 0.5f + (float)(dt) / TICK_INTERVAL ))
#define TICKS_TO_TIME(t)	(TICK_INTERVAL * ( t ))
#define ROUND_TO_TICKS(t) (TICK_INTERVAL * TIME_TO_TICKS( t ))

double inline __declspec (naked) __fastcall fast_sqrt(double n) {
	_asm fld qword ptr[esp + 4]
		_asm fsqrt
	_asm ret 8
}