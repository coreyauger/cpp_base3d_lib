#include "Sphere.h"


namespace Affine{

	Sphere::Sphere( const Point& origin, const Scalar radius )
		: 
		mOrigin( new Point( origin ) ),
		mRadius( radius )
	{
		return;
	}
	
	Sphere::Sphere( const Sphere& inSource )
		:
		mOrigin( new Point(*inSource.mOrigin) ),
		mRadius( inSource.mRadius )
	{
		return;
	}

} // end Affine namespace

