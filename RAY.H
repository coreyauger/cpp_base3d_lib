//////////////////////////////////////////////////////////////////////////
//
//	CLASS: RAY
//	DEFINITION:
//	Rays are expressed here by the parametric exation:
//	P(t) = P0 + tV
//
//	Where P0 is the starting possiotion of the ray and T is any real number
//	representing the "distance" or "time" travelled down the direction Vector V.
//	We can use this to also represent a line
//
//	Distance functions calaulate the shortest distance from a (POINT)
//	Using Pathagrean and some basic Vector math to do it.
//
//	In the future we might want to do the shortest distance between another
//	ray... this is not so trivial, so I will wait till I require an application
//	of this to get it going.
//
///////////////////////////////////////////////////////////////////////////

#ifndef RAY_H
#define RAY_H

#include "Scalar.h"
#include <memory>
#include "Point.h"
#include "Vector.h"
#include "Plane.h"

namespace Affine{

	class 	Plane;
	class	Point;
	class 	Vector;
	
	class Ray
	{
	private:
		
		std::auto_ptr< Point >	mPoint;			// Starting position of the Ray
		std::auto_ptr< Vector >	mDirection;		// Direction Vector of the Ray	
		Scalar			mT;			// "Time" Scaler for the direction Vector		
	public:	
			 Ray( const Point &p, const Vector &d, const Scalar t=1.0 ); 
			 Ray( const Point &p1, const Point &p2 );
			 Ray( const Ray &inSource );		// copy construstor
		virtual  ~Ray() {};
		const Ray& operator=( const Ray& inOther );
		Scalar 	 distanceToPoint( const Point &inPoint )const;		// Get the shortest distance from a point to our line
		Point* 	 getPointFromScaler( const float inHit )const;
		int	 getIntersection( const Plane &inPlane, Point& outIntersection)const;
		const Vector& getDirection() const;
		const Point&  getOrigin() const; 
	};


}
#endif
