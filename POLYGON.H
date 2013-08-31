/*
 *	Author: Corey Auger (corey@coreyauger.com)
 *
 *	Polygon
 *	
 *	TODO:
 *	not sure how i want to alloc mem for polys.  One idea is to have a 
 *	static vector/vecNormals list and a dynamic list for objects created 
 *  on the fly... then link to them.
 *
 *	That is going to take some work/thinking for when split function ect..
 *	
 */
#ifndef _POLYGON
#define _POLYGON

#include <memory>
#include <vector>
#include "Vector.h"
#include "Plane.h"
#include "AxisAlignedBoundingBox.h"
#include "Ray.h"


namespace Affine{

	class Polygon : public Plane
	{
	private:
		std::vector< Point >	mVerticies;
		std::auto_ptr< Vector >	mNormal;
		unsigned int		mNumVerticies;
	
	public:
		Polygon( const Vector& norm, const Point& point ) : Plane( norm, point ){};
	//	Polygon( const unsigned int num=0 );
	//	Polygon( const Polygon& inSource );
	//	virtual ~Polygon();
		/*
		int	classify( const Polygon& inPoly)const;		// classify this poly to one passed in
		int	classify( const Plane& inPlane)const;		// classify this poly to infinit split plane
		void	split( const Plane &inSplitter, Polygon &outFront, Polygon &outBack);
		AxisAlignBoundingBox*	getPolygonAABB()const;		// return an AABB for this poly
		*/
	};



}// end Affine namespace
#endif
