#include "AxisAlignedBoundingBox.h"

#include "Constants.h"

namespace Affine{
	
	AxisAlignedBoundingBox::AxisAlignedBoundingBox()
		:
		mMax( new Point( -BIG, -BIG, -BIG ) ),
		mMin( new Point( BIG, BIG, BIG ) )
	{
		return;
	}
	
	AxisAlignedBoundingBox::AxisAlignedBoundingBox( const AxisAlignedBoundingBox& inSource )
		:
		mMax( new Point( (*inSource.mMax) ) ),
		mMin( new Point( (*inSource.mMin) ) )
	{
		return;
	}
	
	void AxisAlignedBoundingBox::reset()
	{
		mMax->set(-BIG ,-BIG, -BIG); 
		mMin->set(BIG, BIG, BIG);
	}
	
	void AxisAlignedBoundingBox::scale(const Scalar sx, const Scalar sy, const Scalar sz)
	{
		(*mMax)[0] *= sx; (*mMin)[0] *= sx;
		(*mMax)[1] *= sy; (*mMin)[1] *= sy;
		(*mMax)[2] *= sz; (*mMin)[2] *= sz; 
	}
	
	
	void AxisAlignedBoundingBox::addPoint(const Point &p)
	{
		if( p[0] > (*mMax)[0] )(*mMax)[0] = p[0];
		if( p[1] > (*mMax)[1] )(*mMax)[1] = p[1];
		if( p[2] > (*mMax)[2] )(*mMax)[2] = p[2];
	
		if( p[0] < (*mMin)[0] )(*mMin)[0] = p[0];
		if( p[1] < (*mMin)[1] )(*mMin)[1] = p[1];
		if( p[2] < (*mMin)[2] )(*mMin)[2] = p[2];
	}
	
	
	void AxisAlignedBoundingBox::addPoint(const Scalar &x, const Scalar &y, const Scalar &z)
	{
		if( x > (*mMax)[0] )(*mMax)[0] = x;
		if( y > (*mMax)[1] )(*mMax)[1] = y;
		if( z > (*mMax)[2] )(*mMax)[2] = z;
	
		if( x < (*mMin)[0] )(*mMin)[0] = x;
		if( y < (*mMin)[1] )(*mMin)[1] = y;
		if( z < (*mMin)[2] )(*mMin)[2] = z;
	}
	
	bool AxisAlignedBoundingBox::inBox( Object &test )
	{
		if( (test[0] < (*mMin)[0]) || (test[0] > (*mMax)[0]) ) return false;
		if( (test[1] < (*mMin)[1]) || (test[1] > (*mMax)[1]) ) return false;
		if( (test[2] < (*mMin)[2]) || (test[2] > (*mMax)[2]) ) return false;
		return true;
	}
	
	bool AxisAlignedBoundingBox::overlaps( const AxisAlignedBoundingBox &other ) {
		Point myMid = 0.5*(*mMax) + 0.5*(*mMin);
		Scalar myX = (*mMax)[0] - myMid[0];
		Scalar myY = (*mMax)[1] - myMid[1];
		Scalar myZ = (*mMax)[2] - myMid[2];
		Point otherMid = 0.5*(*other.mMax) + 0.5*(*other.mMin);
		Scalar oX = (*other.mMax)[0] - otherMid[0];
		Scalar oY = (*other.mMax)[1] - otherMid[1];
		Scalar oZ = (*other.mMax)[2] - otherMid[2];
		Vector between =  otherMid - myMid;
		return (fabs( between[0] ) < oX + myX) &&
			(fabs( between[1] ) < oY + myY) &&
			(fabs( between[2] ) < oZ + myZ);
	}
	////////////////////////////////////////////////////////////////////////////////////
	
	
	
	
	
	///////////////////////////////////////////////////////////////////////////////////
	//
	//	BoundingBox::rayIntersection
	//  Parameters:
	//	r-> our Ray to test the collision with
	//  tnear -> a float to return the near collision scaler
	//	tfar -> a float to return the far collision scaler
	//
	//	General Idea:
	//	We Pass (a Ray) and see if it collides with the 6 planes of 
	//  our AxisAlignedBoundingBox (Axis Aligned Bunding Box).  If it does then we return a near and far 
	//	scaler values which you could use to scale the dirction Vector for the Collision
	//  points.
	//
	///////////////////////////////////////////////////////////////////////////////////
	bool AxisAlignedBoundingBox::rayIntersect( const Ray &r, Scalar &tnear, Scalar &tfar)
	{
		Scalar t0, t1;
		const Object &rd = r.getDirection();
		const Object &ro = r.getOrigin();
		
		t0=tnear=-BIG;
		t1=tfar=BIG;
	
			
		for( int i = 0; i < 3 ; ++i ) {
			Scalar invRayDir = 1.f / rd[i];
			Scalar tNear = ((*mMin)[i] - ro[i]) * invRayDir;
			Scalar tFar = ((*mMax)[i] - ro[i]) * invRayDir;
			if( tNear > tFar ) {
				Scalar tmp = tNear;
				tNear = tFar;
				tFar = tmp;
			}
			t0 = tNear > t0 ? tNear : t0;
			t1 = tFar < t1 ? tFar : t1;
			if( t0 > t1 ) return false;
		}
		tnear = t0;
		tfar = t1;
		return true;
	}
	///////////////////////////////////////////////////////////////////////////////////
	
	Scalar AxisAlignedBoundingBox::getLength()
	{
		return ((*mMax)-(*mMin)).length();
	}

	
} // end Affine namespace

