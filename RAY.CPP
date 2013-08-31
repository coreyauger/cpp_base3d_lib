
#include "Ray.h"


namespace Affine{
	
	
	Ray::Ray( const Point &p, const Vector &d, const Scalar t ) 
		:
		mPoint( new Point(p) ),
		mDirection( new Vector(d) ),
		mT( t )
	{
		return;
	}
	
	Ray::Ray( const Point &p1, const Point &p2 )
		:
		mPoint( new Point(p1) ),
		mDirection( new Vector(p2-p1) ),
		mT( mDirection->length() )
	{
		return;
	}
	
	Ray::Ray( const Ray& inSource )
		:
		mPoint( new Point( (*inSource.mPoint) ) ),
		mDirection( new Vector( (*inSource.mDirection ) ) ),
		mT( inSource.mT )
	{
		return;
	}
	
	
	const Ray& Ray::operator=( const Ray& inOther )
	{
		(*mPoint) = (*inOther.mPoint);
		(*mDirection) = (*inOther.mDirection);
		mT = inOther.mT;
		return *this;
	}
	
	
	Scalar Ray::distanceToPoint( const Point &inPoint ) const
	{
		Vector a;
		Scalar t,b,c;
		a = inPoint - *mPoint;
		t = a.dot(a);
		b = ((inPoint-(*mPoint)).dot( *mDirection ));// * ((inPoint-(*mPoint)).dot( mDirection ));
		b *= b;
		c = mDirection->dot( *mDirection );
		b = b/c;
		return sqrtf( t-b );
	}
	
	Point* Ray::getPointFromScaler( const Scalar inHit) const
	{
		Point *pointHit;
		pointHit = new Point();
		*pointHit = ((*mDirection) * inHit) + (*mPoint); 
		return pointHit;
	}
	
	
	int Ray::getIntersection( const Plane &inPlane, Point &outIntersection) const 
	{
		Vector			direction, L1;
		Scalar			linelength, dist_from_plane;
		Scalar			percentage;
	
		linelength = mDirection->dot( inPlane.getNormal() );
		if( fabsf( linelength ) < SMALL )return false; 
	
		L1 = inPlane.getPoint() - (*mPoint);
	
		dist_from_plane = L1.dot( inPlane.getNormal() );
	
		// How far from Linestart , intersection is as a percentage of 0 to 1 
		percentage = dist_from_plane / linelength; 
	
		// The plane is behind the start of the line or
		// The line does not reach the plane
		if ( percentage < 0.0f || percentage > 1.0f ) return false;
	
		// add the percentage of the line to line start
		outIntersection = ((*mDirection) * percentage) + (*mPoint);
		return true;
	}
	
	
	const Vector& Ray::getDirection() const
	{
		return (*mDirection);
	}
	
	const Point& Ray::getOrigin() const
	{
		return (*mPoint);
	}

} // end Affine namspace

