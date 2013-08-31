//////////////////////////////////////////////////////////////////////////
//
//	CLASS: PLANE
//	Stores the normal to the plane as well as (float d) the smallest
//	distance from the plane to the origin.
//	Constructor takes a point on the plane as well as the plane normal.
//	It normalizes the normal(required in distance equation) and stores it
//	(float d) takes more work to claculate.
//	pane equation -> Ax + Bx + Cx + D = 0
//	where A,B,C are the x,y,z of the normal and
//	D = -N ^ P0
//	since P0 is a vector that in a dot product would yield its length to the origin
//	or a hypotinus angle and the cosine of the angle... thus giving us the length of
//     	the adgacent tri or the length that we are looking for
//	fabs(D) gives us the distance to a parrellel plane that passes through the origin
//
//	Distance Function:
//	return 0		-> if the point is on the plane
//	return +float 	-> if point is on same side as normal ... front
//	return -float 	-> if point is on opposite side of normal .. back
//
///////////////////////////////////////////////////////////////////////////

#ifndef PLANE_H
#define PLANE_H

#include <memory>
#include "Scalar.h"
#include "Point.h"
#include "Vector.h"
#include "Constants.h"


namespace Affine{

	class Plane
	{
	public:
			Plane(const Vector &norm, const Point &p0);
			Plane( const Plane &inSource );
		virtual ~Plane() {};
		Scalar 		distance( const Point &p ) const;
		const Point& 	getPoint() const { return (*mPoint); }
		const Vector& 	getNormal() const { return (*mNormal); }
		
	private:
		std::auto_ptr< Point >		mPoint;				// point on plane
		std::auto_ptr< Vector > 	mNormal;			// normal of plane
		Scalar 				mDistance;			// distance to parrelle plane passing through origin
	//  ADD A RAY INTERSECT FUNCTION IN HERE LATTER
	};
} // end Affine namespace


#endif
