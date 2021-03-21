#pragma once

#define M_RADPI 57.295779513082f

//https://www.codeproject.com/Articles/69941/Best-Square-Root-Method
double inline __declspec (naked) __fastcall FastSQRT(double n){
	_asm fld qword ptr[esp + 4]
		_asm fsqrt
	_asm ret 8
}

#define IntervalPerTick (1.f/64.f)
#define TICK_INTERVAL (IntervalPerTick)
#define TIME_TO_TICKS( dt )		( (int)( 0.5f + (float)(dt) / TICK_INTERVAL ) )
#define TICKS_TO_TIME( t )		( TICK_INTERVAL * ( t ) )
#define ROUND_TO_TICKS( t ) ( TICK_INTERVAL * TIME_TO_TICKS( t ) )