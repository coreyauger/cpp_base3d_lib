//
//   Copyright (C) 2004 by Lakin Wecker and Corey Auger
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

#ifndef _POINT_H_
#define _POINT_H_

#include "Object.h"
#include <iostream>
namespace Affine {
/**
 * An affine point, which inherits from an affine object.
 */
class Point : public Object
{
	public:
		/**
		 * Default constructor which creates itself as an affine point
		 * at the origin.
		 */
		Point(const Scalar x=0.0, const Scalar y=0.0, const Scalar z=0.0);
		/**
		 * Default constructor which creates itself from another affine object.
		 */
		Point( const Object &other );

		/**
		 * The contructor, which is virtual so superclasses can inherit from
		 * it appropriately.
		 */
		virtual ~Point();

		//------------------------------------------------------------------
		// Overloaded operators.
		//------------------------------------------------------------------
		/**
		 * Overloaded assignment operator.
		 * @param other The other object you wish to assign to this Point.
		 * @return Point a constant reference *this
		 */
		const Point &operator=( const Object &other );
		/**
		 * Overloaded output operator.
		 */
		friend std::ostream &operator<<( std::ostream &out, const Point &other ) {
			out << "[" << other[0] << ","
					<< other[1] << ","
					<< other[2] << ","
					<< other[3] << "]";
			return out;
		}
		
	protected:
};

}//end Namespace Affine
#endif	//_POINT_H_

