#include "Plane.h"

namespace Affine{

	Plane::Plane(const Vector &norm, const Point &p)
		:
		mPoint( new Point(p) ),
		mNormal( new Vector(norm) ),
		mDistance( (-(*mNormal)).dot( p ) )	
	{ 
		return;
	}
	
	Plane::Plane( const Plane& inSource )
		:
		mPoint( new Point( (*inSource.mPoint) ) ),
		mNormal( new Vector( (*inSource.mNormal) )),
		mDistance( inSource.mDistance )
	{
		return;
	}
	
	
	inline Scalar Plane::distance( const Point &p ) const
	{ 
		return ((mNormal->dot( p )) + mDistance ); 
	}

} // end Affine namespcae
