/*
 *	Author: Corey Auger (corey@coreyauger.com)
 *
 *	AxisAlignedBoundingBox
 *
 */
#ifndef AXISALIGNEDBOUNDINGBOX_H
#define AXISALIGNEDBOUNDINGBOX_H

#include <memory>
#include "Scalar.h"
#include "Point.h"
#include "Vector.h"
#include "Ray.h"
#include <GL/gl.h>
#include <GL/glu.h>

namespace Affine{

	class AxisAlignedBoundingBox
	{
	private:
		std::auto_ptr< Point >	mMax; 			// the most positive x,y,z Point
		std::auto_ptr< Point > 	mMin;			// the most negative x,y,z point
		
	public:

		AxisAlignedBoundingBox();			// Create BoundingBox with default values
		AxisAlignedBoundingBox( const AxisAlignedBoundingBox& inSource );	// copy constructor
		virtual ~AxisAlignedBoundingBox() {};		// virtual destructor
		void	reset();				// reset the BoundingBox to Default values
		void	addPoint(const Point &p);		// Check if this is MAX or MIN to be added to AxisAlignedBoundingBox
		void	addPoint(const Scalar &x, const Scalar &y, const Scalar &z);
		bool	rayIntersect( const Ray &r, Scalar &tnear, Scalar &tfar);
		Scalar	getLength();
		bool	inBox( Object &test );
		void	scale(const Scalar sx, const Scalar sy, const Scalar sz);
		bool    overlaps( const AxisAlignedBoundingBox &other );
	
	};

	
} // end Affine namespace

#endif
