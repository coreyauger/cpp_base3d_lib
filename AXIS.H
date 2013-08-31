/*
 *	Author: Corey Auger (corey@coreyauger.com)
 *
 *	Axis
 *
 *  TODO: Re-evaluate whether these should be public
 *	      or private. -lw 04/03/20
 */
#ifndef AXIS_H
#define AXIS_H
#include "Point.h"
#include "Vector.h"


namespace Affine{
	
	class Axis
	{
	public:
		Vector		mX;				// X Axis of this local system
		Vector		mY;				// Y Axis
		Vector		mZ;				// Z Axis
	};
	
	
} // end Affine namespace

#endif
