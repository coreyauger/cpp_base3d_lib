//
//   Copyright (C) 2004 by Lakin Wecker And Corey Auger
//   nikal@nucleus.com
//
//   This program is free software; you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation; either version 2 of the License, or
//   (at your option) any later version.
//
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.
//
//   You should have received a copy of the GNU General Public License
//   along with this program; if not, write to the
//   Free Software Foundation, Inc.,
//   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA. 
//

#ifndef _TRIANGLE_H
#define _TRIANGLE_H


//------------------------------------------------------------------------------
// Project includes
//------------------------------------------------------------------------------
#include <memory>

#include "Constants.h"
#include "Point.h"
#include "Vector.h"
#include "Ray.h"
#include "Scalar.h"
//------------------------------------------------------------------------------
// Object Declaration
//------------------------------------------------------------------------------
namespace Affine {
/**
 * Traingle class.... How many corners? .... THREE !!
 */
	class Triangle
	{
		private:
			std::auto_ptr< Point >		mPointA;
			std::auto_ptr< Point >		mPointB;
			std::auto_ptr< Point >		mPointC;
			std::auto_ptr< Vector > 	mNormal;
		
		public:
			/**
			* Constructor taking three points
			*/
			Triangle( const Point &a, const Point &b, const Point &c );	
			/**
			* Copy constructor
			*/		
			Triangle( const Triangle &source );
			/**
			* Virtual Destructor		
			*/
			virtual ~Triangle();
			/**
			* Intersection with a Ray, this method takes an optional tNear and tFar and returns whether there was or was not
			* an intersection with the object.
			* If there was an intersection, intersect will contain the closest point
			* that intersects within >= tNear, <= tFar.
			*/
			virtual bool intersect( const Ray &r, Scalar &t, Scalar &u, Scalar &v, const Scalar &tNear = BIG, const Scalar &tFar = SMALL) const;
			inline const Vector& getNormal( ) const;
			const Triangle &operator=( const Triangle &other );
			/**
			* Overaloaded array access.
			*/
			Point& operator[]( const unsigned int i ) const;
			
	};

}// End Affine namespace


#endif	//_TRIANGLE_H
