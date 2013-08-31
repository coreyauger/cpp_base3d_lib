#include "Triangle.h"
//#include "Geometry.h"

#include <limits>

namespace Affine {

	Triangle::Triangle( const Point& a, const Point& b, const Point& c )
		:
		mPointA( new Point(a) ),
		mPointB( new Point(b) ),
		mPointC( new Point(c) ),
		mNormal( new Vector(   (*mPointB-*mPointA).cross( (*mPointC-*mPointA) )   ) )
	{
		mNormal->normalize();
		return;
	}
	
	
	Triangle::Triangle( const Triangle &inSource )
		:
		mPointA( new Point(*inSource.mPointA) ),
		mPointB( new Point(*inSource.mPointB) ),
		mPointC( new Point(*inSource.mPointC) ),
		mNormal( new Vector(*inSource.mNormal) )
	{
		return;
	}
	
	
	Triangle::~Triangle(){
		return;
	}	
		
		
	bool Triangle::intersect( const Ray &r, Scalar &t, Scalar &u, Scalar &v, const Scalar &tNear, const Scalar &tFar ) const {
		Vector edge1, edge2, tvec, pvec, qvec;
		Scalar det,inv_det;
	
		/* find vectors for two edges sharing vert0 */
		edge1 = *mPointB - *mPointA;
		edge2 = *mPointC - *mPointA;
	
		/* begin calculating determinant - also used to calculate U parameter */
		pvec = r.getDirection().cross( edge2 );
	
		/* if determinant is near zero, ray lies in plane of triangle */
		det = edge1.dot( pvec );
	
		if (det > -std::numeric_limits<Scalar>::epsilon() && 
			det < std::numeric_limits<Scalar>::epsilon() )
			return false;
		inv_det = 1.0 / det;
	
		/* calculate distance from vert0 to ray origin */
		tvec = r.getOrigin() - *mPointA;
	
		/* calculate U parameter and test bounds */
		u = tvec.dot( pvec ) * inv_det;
		if (u < 0.0 || u > 1.0)
			return false;
	
		/* prepare to test V parameter */
		qvec = tvec.cross( edge1 );
	
		/* calculate V parameter and test bounds */
		v = r.getDirection().dot( qvec ) * inv_det;
		if (v < 0.0 || u + v > 1.0)
			return false;
	
		/* calculate t, ray intersects triangle */
		t = edge2.dot( qvec )*inv_det;
	
		return true;
	}
	
	const Vector& Triangle::getNormal( ) const {
		return (*mNormal);
	}
	
	
	const Triangle& Triangle::operator=( const Triangle &other ){
		return *this;
	}
	
	Point& Triangle::operator[]( const unsigned int i ) const
	{
		switch(i) {	
			case 0:
				return *mPointA;
			case 1:
				return *mPointB;
			case 2:
				return *mPointC;
		}
		assert( !"Index out of range 0-3 in Triangle.h" );
		return *mPointA;
	}


} // end namespcae
